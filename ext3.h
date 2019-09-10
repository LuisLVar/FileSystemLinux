#ifndef EXT3_H
#define EXT3_H

#include "login.h"

class Ext3
{
public:
    Ext3();
    void recoveryFS(string id);
    void simulateLoss(string id);
};

#endif // EXT3_H