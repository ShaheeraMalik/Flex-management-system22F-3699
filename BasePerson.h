#ifndef BASEPERSON_H
#define BASEPERSON_H

#include <string>

class BasePerson {
protected:
    // Member variables...
public:
    BasePerson(/* parameters */);
    virtual void signIn() = 0;
    virtual void viewDetails() const = 0;
    virtual void editDetails() = 0;
    // ... Other virtual functions
};

#endif // BASEPERSON_H
