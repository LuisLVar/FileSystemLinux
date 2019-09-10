#ifndef ARCHIVO_H
#define ARCHIVO_H

#include "login.h"

class Archivo
{
public:
    Archivo();
    void makeFile(string path, int p, string size, string cont);
    void showContent(string file); //CAT
    void removeFile(string path);
    void editFile(string path, string cont); //Append

};

#endif // ARCHIVO_H