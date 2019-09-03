#ifndef FDISK_H
#define FDISK_H
#include <string>

using namespace std;

class fDisk
{
public:
    fDisk();
    void administrarParticion(string size, string unit, string path, string fit, string type,
                              string cdelete, string name, string add);
    void deleteParticion(string cdelete, string path, string name);
    void addParticion(string add, string unit, string name, string path);
    void createPartition(string size, string unit, string name, string path, string fit, string type);
    void primerAjuste();
    void peorAjuste();
    void mejorAjuste();
    string toLowerCase(string comando);
    void actualizarRaid(string pathD);
};

#endif // FDISK_H
