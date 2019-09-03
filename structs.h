#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>

using namespace std;

class Structs
{
public:
    Structs();
    typedef struct particion
    {
        char Estado = '0';
        char type = ' ';
        char fit = ' ';
        int part_start = 0;
        int size = 0;
        char name[16] = "";
    } Particion; //typedef

    typedef struct MBR_Disco
    {
        int size;
        char date[20];
        int disk_signature;
        char fit;
        Particion mbr_particiones[4];
    } MBR;

    typedef struct EBR_Logical
    {
        char Estado = '0';
        char fit = ' ';
        int part_start = 0;
        int size = 0;
        int part_next = -1;
        char name[16] = "Inicial";
    } EBR; //typedef

};

#endif // STRUCTS_H
