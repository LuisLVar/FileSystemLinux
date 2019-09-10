#ifndef CARPETA_H
#define CARPETA_H

#include "login.h"

class Carpeta
{
public:
    Carpeta();
    void renameFile(string path, string name);
    void makeDirectory(string path, int p);
    void copyFile(string path, string dest);
    void moveFile(string path, string dest);
    void findFile(string path, string name);
};

#endif // CARPETA_H