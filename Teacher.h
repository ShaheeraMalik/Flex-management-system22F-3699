#ifndef TEACHER_H
#define TEACHER_H

#include "BasePerson.h"

class Teacher : public BasePerson {
    std::string teacherId;
    // ... Other member variables

public:
    Teacher(/* parameters */);
    // ... Overridden and other member functions
};

#endif // TEACHER_H
