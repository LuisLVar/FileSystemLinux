#ifndef USER_H
#define USER_H

#include "login.h"

class User
{
public:
    User();
    void makeUser(string usr, string pwd, string grp);
    void removeUser(string usr);
    void changeMod(string path, string ugo, int r);
};

#endif // USER_H