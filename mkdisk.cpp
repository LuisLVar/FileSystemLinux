#include "mkdisk.h"
#include <string>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <fstream>

mkDisk::mkDisk()
{
}

void mkDisk::crearDisco(string size, string fit, string unit, string path)
{
    time_t t;
    struct tm *tm;
    char fechayhora[20];

    t = time(NULL);
    tm = localtime(&t);
    strftime(fechayhora, 20, "%Y/%m/%d %H:%M:%S", tm);

    if (fit == "")
    {
        fit = "F";
    }
    if (unit == "")
    {
        unit = "M";
    }

    int numSize = stoi(size);

    if (unit == "M" || unit == "m")
    {
        numSize = numSize * 1024 * 1024;
    }
    else
    {
        numSize = numSize * 1024;
    }

    if (numSize < 0)
    {
        cout << "Error, tamanio del disco demasiado grande." << endl;
        return;
    }

    Structs::MBR disco;
    disco.size = numSize;
    strcpy(disco.date, fechayhora);
    disco.fit = toupper(fit[0]);
    disco.disk_signature = rand() % 100;

    FILE *validar = fopen(path.c_str(), "r");
    if (validar != NULL)
    {
        cout << "Disco ya existente., validar path" << endl;
        fclose(validar);
        return;
    }
    //cout << "Nuevo disco: \nSize: " << disco.size << "\ndate: " << disco.date << "\nFit: " << disco.fit << "\nDisk_Signature: " << disco.disk_signature << endl;
   // cout << "Bits del MBR: " << sizeof(Structs::MBR) << endl;

   // cout << "Path: " << path << endl;
    int isNulo = 0;
    FILE *bfile = fopen(path.c_str(), "wb");
    if (bfile != NULL)
    {
        fwrite("\0", 1, 1, bfile);
        fseek(bfile, numSize - 1, SEEK_SET);
        fwrite("\0", 1, 1, bfile);
        rewind(bfile);
        fwrite(&disco, sizeof(Structs::MBR), 1, bfile);
        mkDisk::crearRaid(&disco, path);
    }
    else
    {
        isNulo = 1;
        cout << "Path creado exitosamente" << endl;
        //Creo la carpeta de la direccion.
        string comando1 = "mkdir -p \"" + path + "\"";
        string comando2 = "rmdir \"" + path + "\"";
        system(comando1.c_str());
        system(comando2.c_str());

        bfile = fopen(path.c_str(), "wb");
        fwrite("\0", 1, 1, bfile);
        fseek(bfile, numSize - 1, SEEK_SET);
        fwrite("\0", 1, 1, bfile);
        rewind(bfile);
        fwrite(&disco, sizeof(Structs::MBR), 1, bfile);
        mkDisk::crearRaid(&disco, path);
    }
    fclose(bfile);
}

void mkDisk::crearRaid(Structs::MBR *disco, string pathD)
{
    string path = pathD.substr(0, pathD.size() - 5);
    path = path + "_ra1.disk";

    /*FILE *bfile = fopen(path.c_str(), "wb");
    fwrite("\0", 1, 1, bfile);
    fseek(bfile, disco->size - 1, SEEK_SET);
    fwrite("\0", 1, 1, bfile);
    rewind(bfile);
    fwrite(&disco, sizeof(Structs::MBR), 1, bfile);

    fclose(bfile);*/

    std::ifstream srce(pathD.c_str(), std::ios::binary);
    std::ofstream dest(path.c_str(), std::ios::binary);
    dest << srce.rdbuf();
}
