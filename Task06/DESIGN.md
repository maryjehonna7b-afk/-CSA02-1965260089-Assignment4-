# Task 6 – College Canteen Inventory and Billing

## Stage 1 – Interpret the problem

### Entities and data
- **Date:** day, month and year.
- **Canteen item:** ID, name, kind, price and stock.
- **Packaged item:** expiry date.
- **Cooked item:** preparation hour and minute.
- **Combo item:** up to three component item IDs.
- **Sale:** sold item ID/name, quantity and revenue.

### Testable requirements
1. A valid item can be added until the inventory capacity is reached.
2. A sale with a positive quantity and sufficient stock reduces stock.
3. A sale with insufficient stock is rejected and stock remains unchanged.
4. A packaged item expiring today, tomorrow or the day after is listed in the warning.
5. A combo sale checks every component before reducing any component stock.
6. The sales summary is sorted from highest revenue to lowest revenue.

## Stage 2 – Data model

`Item` is the main structure. It contains a tagged union whose active member depends on `Item.kind`:
- `PACKAGED` → `PackagedInfo`
- `COOKED` → `CookedInfo`
- `COMBO` → `ComboInfo`

The inventory and sales are arrays of structures. The expiry date is a nested structure within packaged-item details. The union avoids allocating all variant-specific fields for every item.

## Stage 3 – Critical decisions

- Validate quantity, item existence and stock before changing inventory.
- For a combo, check all components first, then deduct component stock only after every check passes.
- Compare date fields using a `Date` structure. The included demonstration helper intentionally assumes the same month and year; a production version should convert dates to a serial day count or use a full calendar comparison across month/year boundaries.
- Inventory and sales arrays/counts are `static` file-scope data in this demonstration so helper functions can access shared state. A larger design should place them in a `Canteen` structure and pass a pointer to each function.

## Stage 4 – Structure and function design

Important prototypes in `task06.c`:
```c
int add_item(const Item *item);
Item *find_item(int id);
int record_sale(int item_id, int quantity);
void show_expiry_warnings(Date today);
void print_sales_summary(void);
```

### Pseudocode – Record a sale

```text
ALGORITHM RecordSale(itemID, quantity)
BEGIN
    IF quantity <= 0 THEN
        DISPLAY invalid quantity
        RETURN failure
    END IF
    item ← FIND itemID
    IF item does not exist THEN
        DISPLAY item not found
        RETURN failure
    END IF
    IF item is a combo THEN
        FOR each component in combo
            IF component does not exist OR component stock < quantity THEN
                DISPLAY insufficient component stock
                RETURN failure
            END IF
        END FOR
    ELSE
        IF item stock < quantity THEN
            DISPLAY insufficient stock
            RETURN failure
        END IF
    END IF
    CHECK sales capacity
    UPDATE stock for item or all combo components
    revenue ← item price × quantity
    APPEND sale record
    DISPLAY sale recorded
END
```

### Pseudocode – Expiry warning

```text
ALGORITHM ExpiryWarning(inventory, count, today)
BEGIN
    FOR each item in inventory
        IF item kind is PACKAGED THEN
            IF expiry date is from today through today + 2 days THEN
                DISPLAY item name and expiry date
            END IF
        END IF
    END FOR
END
```

## Stage 5 – Demonstration and expected behaviour

With the supplied sample data and date:
- Juice x2 is accepted; stock decreases from 10 to 8.
- Sandwich x1 is accepted; stock decreases from 5 to 4.
- Sandwich x99 is rejected as insufficient stock; stock remains 4.
- Combo x1 is accepted; one juice and one sandwich are deducted.
- Juice expiring on 20/11/2026 is warned because it is within two days of 19/11/2026.
- Summary is sorted by revenue descending: Combo Meal (75.00), Juice (60.00), Sandwich (50.00).

The program's printed order and values should be checked against your own run.

## Linked-list alternative and complexity

A linked list stores each item in a dynamically allocated node with a `next` pointer:
- Add at the head: O(1).
- Search by ID: O(n).
- Remove after locating the node: O(n) search; unlink itself is O(1).
- Array search: O(n); insertion at the end is O(1) while capacity remains; deleting an element may require O(n) shifting.
- Linked-list nodes use extra memory for the pointer and allocator overhead, and have less cache locality. Arrays use contiguous storage and are simple to traverse and sort.
- The current revenue sort is bubble sort, O(s²) time for s sales and O(1) extra space. A linked list could be sorted by relinking nodes, but it would still require O(s²) time with a simple bubble/insertion method or O(s log s) with merge sort.

## Limitations to explain in viva

This is an educational prototype, not a production billing system. It uses fixed capacities, a simple same-month expiry comparison, and does not implement tax, discounts, payment methods or persistent storage. Extend and test these if your instructor requires them.
