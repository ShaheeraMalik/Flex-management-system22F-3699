#ifndef STUDENT_H
#define STUDENT_H

#include "BasePerson.h"

class Student : public BasePerson {
    std::string studentId;
    // ... Other member variables

public:
    Student(/* parameters */);
    // ... Overridden and other member functions
};

#endif // STUDENT_H
