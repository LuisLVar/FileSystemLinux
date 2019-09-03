#ifndef MKDISK_H
#define MKDISK_H
#include <string>
#include "structs.h"

using namespace std;

class mkDisk
{
public:
    mkDisk();
    void crearDisco(string size, string fit, string unit, string path);
    void crearRaid(Structs::MBR * disco, string path);
};

#endif // MKDISK_H
