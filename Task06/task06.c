#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 20
#define MAX_SALES 100
#define NAME_LEN 40
#define COMBO_PARTS 3

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef enum {
    PACKAGED,
    COOKED,
    COMBO
} ItemKind;

typedef struct {
    Date expiry;
} PackagedInfo;

typedef struct {
    int prepared_hour;
    int prepared_minute;
} CookedInfo;

typedef struct {
    int component_ids[COMBO_PARTS];
    int component_count;
} ComboInfo;

typedef struct {
    int id;
    char name[NAME_LEN];
    ItemKind kind;
    float price;
    int stock;
    union {
        PackagedInfo packaged;
        CookedInfo cooked;
        ComboInfo combo;
    } details;
} Item;

typedef struct {
    int item_id;
    char item_name[NAME_LEN];
    int quantity;
    float revenue;
} Sale;

static Item inventory[MAX_ITEMS];
static int item_count = 0;
static Sale sales[MAX_SALES];
static int sale_count = 0;

int add_item(const Item *item)
{
    if (item == NULL || item_count >= MAX_ITEMS) {
        return 0;
    }
    inventory[item_count++] = *item;
    return 1;
}

Item *find_item(int id)
{
    int i;
    for (i = 0; i < item_count; i++) {
        if (inventory[i].id == id) {
            return &inventory[i];
        }
    }
    return NULL;
}

static int is_leap_year(int year)
{
    return (year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0));
}

static int date_to_serial(Date date)
{
    static const int days_before_month[12] = {
        0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
    };
    int previous_years = date.year - 1;
    int days = previous_years * 365 + previous_years / 4
             - previous_years / 100 + previous_years / 400;

    days += days_before_month[date.month - 1] + date.day;
    if (date.month > 2 && is_leap_year(date.year)) {
        days++;
    }
    return days;
}

int is_within_two_days(Date today, Date expiry)
{
    int today_serial;
    int expiry_serial;

    if (today.month < 1 || today.month > 12 || expiry.month < 1 || expiry.month > 12 ||
        today.day < 1 || today.day > 31 || expiry.day < 1 || expiry.day > 31) {
        return 0;
    }

    today_serial = date_to_serial(today);
    expiry_serial = date_to_serial(expiry);
    return expiry_serial >= today_serial && expiry_serial - today_serial <= 2;
}

int record_sale(int item_id, int quantity)
{
    Item *item;
    Sale *sale;
    int i;

    if (quantity <= 0) {
        printf("Invalid quantity.\n");
        return 0;
    }

    item = find_item(item_id);
    if (item == NULL) {
        printf("Item %d not found.\n", item_id);
        return 0;
    }

    if (item->kind == COMBO) {
        for (i = 0; i < item->details.combo.component_count; i++) {
            Item *component = find_item(item->details.combo.component_ids[i]);
            if (component == NULL || component->stock < quantity) {
                printf("Insufficient component stock for combo %s.\n", item->name);
                return 0;
            }
        }
    } else if (item->stock < quantity) {
        printf("Insufficient stock for %s. Available: %d\n", item->name, item->stock);
        return 0;
    }

    if (sale_count >= MAX_SALES) {
        printf("Sales record is full.\n");
        return 0;
    }

    /* Update stock only after all checks have succeeded. */
    if (item->kind == COMBO) {
        for (i = 0; i < item->details.combo.component_count; i++) {
            Item *component = find_item(item->details.combo.component_ids[i]);
            component->stock -= quantity;
        }
    } else {
        item->stock -= quantity;
    }

    sale = &sales[sale_count++];
    sale->item_id = item->id;
    (void)snprintf(sale->item_name, sizeof sale->item_name, "%s", item->name);
    sale->quantity = quantity;
    sale->revenue = item->price * (float)quantity;

    printf("Sale recorded: %s x%d = %.2f\n",
           item->name, quantity, sale->revenue);
    return 1;
}

void show_expiry_warnings(Date today)
{
    int i;

    printf("Expiry warnings (within 2 days):\n");
    for (i = 0; i < item_count; i++) {
        if (inventory[i].kind == PACKAGED &&
            is_within_two_days(today, inventory[i].details.packaged.expiry)) {
            printf("%s expires on %02d/%02d/%04d\n",
                   inventory[i].name,
                   inventory[i].details.packaged.expiry.day,
                   inventory[i].details.packaged.expiry.month,
                   inventory[i].details.packaged.expiry.year);
        }
    }
}

void sort_sales_by_revenue(void)
{
    int i;
    int j;

    for (i = 0; i < sale_count - 1; i++) {
        for (j = 0; j < sale_count - i - 1; j++) {
            if (sales[j].revenue < sales[j + 1].revenue) {
                Sale temp = sales[j];
                sales[j] = sales[j + 1];
                sales[j + 1] = temp;
            }
        }
    }
}

void print_sales_summary(void)
{
    int i;

    sort_sales_by_revenue();
    printf("Sales summary (highest revenue first):\n");
    for (i = 0; i < sale_count; i++) {
        printf("%s | quantity %d | revenue %.2f\n",
               sales[i].item_name, sales[i].quantity, sales[i].revenue);
    }
}

int main(void)
{
    Item items[] = {
        {1, "Juice", PACKAGED, 30.0f, 10, {.packaged = {{20, 11, 2026}}}},
        {2, "Sandwich", COOKED, 50.0f, 5, {.cooked = {10, 30}}},
        {3, "Combo Meal", COMBO, 75.0f, 0,
         {.combo = {{1, 2}, 2}}}
    };
    Date today = {19, 11, 2026};
    size_t i;

    for (i = 0; i < sizeof items / sizeof items[0]; i++) {
        if (!add_item(&items[i])) {
            printf("Could not load inventory.\n");
            return 1;
        }
    }

    (void)record_sale(1, 2);   /* Normal packaged-item sale. */
    (void)record_sale(2, 1);   /* Normal cooked-item sale. */
    (void)record_sale(2, 99);  /* Insufficient stock test. */
    (void)record_sale(3, 1);   /* Combo consumes one of each component. */

    show_expiry_warnings(today);
    print_sales_summary();

    return 0;
}
