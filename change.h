#ifndef CHANGE_H
#define CHANGE_H

#include "login.h"

class Change
{
public:
    Change();
    void changeOwner(string path, int r, string usr);
    void changeGroup(string usr, string grp);
};

#endif // CHANGE_H