#include <stdio.h>
#include <string.h>

#define MAX_SEATS 2
#define MAX_WAITLIST 5

typedef struct {
    int id;
    char name[50];
} Student;

Student enrolled[MAX_SEATS];
int enrolledCount = 0;

Student waitlist[MAX_WAITLIST];
int front = 0, rear = -1, waitlistCount = 0;

void enrollStudent(int id, char name[]) {
    if (enrolledCount < MAX_SEATS) {
        enrolled[enrolledCount].id = id;
        strcpy(enrolled[enrolledCount].name, name);
        enrolledCount++;
        printf("✅ %s enrolled successfully!\n", name);
    } else if (waitlistCount < MAX_WAITLIST) {
        rear = (rear + 1) % MAX_WAITLIST;
        waitlist[rear].id = id;
        strcpy(waitlist[rear].name, name);
        waitlistCount++;
        printf("⚠️ Seats full! %s added to Waitlist.\n", name);
    } else {
        printf("❌ Error: Course and Waitlist are completely full!\n");
    }
}

void dropStudent(int id) {
    int foundIndex = -1;
    for (int i = 0; i < enrolledCount; i++) {
        if (enrolled[i].id == id) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        printf("🗑️ Student %s dropped from course.\n", enrolled[foundIndex].name);
        
        // Shift remaining enrolled students
        for (int i = foundIndex; i < enrolledCount - 1; i++) {
            enrolled[i] = enrolled[i + 1];
        }
        enrolledCount--;

        // Promote from waitlist if available
        if (waitlistCount > 0) {
            Student promoted = waitlist[front];
            front = (front + 1) % MAX_WAITLIST;
            waitlistCount--;

            enrolled[enrolledCount] = promoted;
            enrolledCount++;
            printf("🎉 Promoted from Waitlist: %s now Enrolled!\n", promoted.name);
        }
    } else {
        printf("❌ Student ID not found in enrolled list.\n");
    }
}

void displayStatus() {
    printf("\n--- Current Status ---\n");
    printf("Enrolled Students (%d/%d):\n", enrolledCount, MAX_SEATS);
    for (int i = 0; i < enrolledCount; i++) {
        printf("ID: %d | Name: %s\n", enrolled[i].id, enrolled[i].name);
    }

    printf("\nWaitlist Queue (%d/%d):\n", waitlistCount, MAX_WAITLIST);
    for (int i = 0; i < waitlistCount; i++) {
        int idx = (front + i) % MAX_WAITLIST;
        printf("ID: %d | Name: %s\n", waitlist[idx].id, waitlist[idx].name);
    }
    printf("----------------------\n");
}

int main() {
    enrollStudent(101, "Sri Krishna");
    enrollStudent(102, "Arun");
    enrollStudent(103, "Karthik"); // Goes to waitlist
    
    displayStatus();

    dropStudent(101); // Sri Krishna drops, Karthik gets promoted
    
    displayStatus();
    return 0;
}
