#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "roster.h"

int main (void) {
    
    entry_t entry1 = {12345, STUDENT, .grade.percentage = 85};
    entry_t entry2 = {67890, INSTRUCTOR, .grade.letter_grade = "A+"};

    printf("Roster Entry 1: ID=%d, Role=%d, Grade=%d%%\n", entry1.id, entry1.role, entry1.grade.percentage);
    printf("Roster Entry 2: ID=%d, Role=%d, Grade=%s\n", entry2.id, entry2.role, entry2.grade.letter_grade);

    return 0;
}
