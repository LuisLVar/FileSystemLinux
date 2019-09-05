#ifndef MKFS_H
#define MKFS_H

#include "mount.h"
#include "interprete.h"

class Mkfs
{
public:
    Mkfs();
    void formatearFS(string id, string type, string fs);
};

#endif // MKFS_H