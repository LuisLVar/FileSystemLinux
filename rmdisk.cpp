#include "rmdisk.h"
#include "structs.h"
#include <iostream>

using namespace std;

rmDisk::rmDisk()
{
}

void rmDisk::eliminarDisco(string path)
{
    if (remove(path.c_str()) == 0)
    {
        cout << "Disco eliminado" << endl;
    }
    else
    {
        cout << "Disco no existente" << endl;
    }
}
