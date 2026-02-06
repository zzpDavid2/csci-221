#include <stdint.h>
#include <stddef.h>

#ifndef ROSTER_H
#define ROSTER_H

typedef enum role_t {
    STUDENT=0,
    INSTRUCTOR=1,
    TEACHING_ASSISTANT=2,
    OBSERVER=3
} role_t;

typedef union grade_t {
    uint8_t percentage; // A percentage grade (0-100)
    char* letter_grade; // Two-letter grade (e.g., "A+", "B-", etc.)
} grade_t;

typedef struct entry_t {
    int32_t id; // Unique identifier for the roster
    role_t role; // Role of the person in the roster (e.g., student, instructor, etc.)
    grade_t grade; // Grade of the student (if applicable)
} entry_t;
/*
A struct to represent a roster of students.
The struct has three fields:
- id: an integer representing the unique identifier of the roster
- role: an enum representing the role of the person in the roster (e.g., student, instructor, etc.)
- grade: a union representing the grade of the student.
*/

#endif // ARRAY_H
