#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100
#define NAME_LEN 50
#define PHONE_LEN 16

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    int systolic;
    int diastolic;
} BloodPressure;

typedef struct {
    char name[NAME_LEN];
    int age;
    char phone[PHONE_LEN];
    BloodPressure bp;
    Date visit_date;
} Patient;

static Patient patients[MAX_PATIENTS];
static int patient_count = 0;

/* Accepts a pointer so that the supplied patient is copied into the register. */
int addPatient(const Patient *new_patient)
{
    if (new_patient == NULL || patient_count >= MAX_PATIENTS) {
        return 0;
    }

    patients[patient_count] = *new_patient;
    patient_count++;
    return 1;
}

void printPatient(const Patient *p)
{
    if (p == NULL) {
        return;
    }

    printf("%-20s Age:%d Phone:%s BP:%d/%d Visit:%02d/%02d/%04d\n",
           p->name, p->age, p->phone,
           p->bp.systolic, p->bp.diastolic,
           p->visit_date.day, p->visit_date.month,
           p->visit_date.year);
}

int main(void)
{
    Patient p1 = {
        "Ananya", 21, "9876543210",
        {120, 80}, {19, 11, 2026}
    };
    Patient p2 = {
        "Karthik", 35, "9123456780",
        {130, 85}, {18, 11, 2026}
    };

    if (!addPatient(&p1) || !addPatient(&p2)) {
        printf("Could not add patient: register full or invalid input.\n");
        return 1;
    }

    printf("Patient register (%d records)\n", patient_count);
    for (int i = 0; i < patient_count; i++) {
        printPatient(&patients[i]);
    }

    return 0;
}
