#ifndef LOGIN_H
#define LOGIN_H

#include "mount.h"
#include "interprete.h"

class Login
{
public:
    Login();
    void iniciarSesion(string usr, string pwd, string id);
    void cerrarSesion();
};

#endif // LOGIN_H