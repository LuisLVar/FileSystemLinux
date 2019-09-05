#include "fdisk.h"
#include <string>
#include "structs.h"
#include <iostream>
#include <string.h>
#include <algorithm>
#include <fstream>

fDisk::fDisk()
{
}

void fDisk::administrarParticion(string size, string unit, string path,
                                 string fit, string type, string cdelete, string name, string add)
{
    if (unit == "")
    {
        unit = "K";
    }
    if (fit == "")
    {
        fit = "W";
    }
    if (type == "")
    {
        type = "P";
    }

    //Add to Partition
    if (add != "")
    {
        fDisk::addParticion(add, unit, name, path); //ESPERA
    }
    else if (cdelete != "") //Delete Partition
    {
        fDisk::deleteParticion(cdelete, path, name); //ALMOST DONE
    }
    else //Create a Partition
    {
        fDisk::createPartition(size, unit, name, path, fit, type);
    }
}

void fDisk::createPartition(string size, string unit, string name, string path, string fit, string type)
{ // Fit: BF, FF, WF. Default:(WF)   -  Type: P, E, L.   Default: (P)   -   Unit: B, K, M.  Default: (K)

    Structs::Particion partition;

    int numSize = stoi(size);

    if (unit == "M" || unit == "m")
    {
        numSize = numSize * 1024 * 1024;
    }
    else if (unit == "K" || unit == "k")
    {
        numSize = numSize * 1024;
    }
    else if (unit == "B" || unit == "b")
    {
    }
    else
    {
        cout << "Error en la unidad de la particion" << endl;
    }

    if (numSize < 0)
    {
        cout << "Error, tamanio del disco demasiado grande." << endl;
        return;
    }

    partition.Estado = '1';
    partition.fit = fit[0];
    strcpy(partition.name, name.c_str());
    partition.part_start = 0;
    partition.size = numSize;
    partition.type = toupper(type[0]);

    if (type == "P")
    {
    }
    else if (type == "E")
    {
    }
    else if (type == "L" || type == "l")
    {
        cout << "Particion Logica"<<endl;
        return;
    }
    else
    {
        cout << "Error en el tipo de particion" << endl;
    }

    Structs::MBR discoEditar;
    FILE *bfile2 = fopen(path.c_str(), "rb+");
    if (bfile2 != NULL)
    {
        fseek(bfile2, 0, SEEK_SET);
        fread(&discoEditar, sizeof(discoEditar), 1, bfile2);
    }
    else
    {
        cout << "Error. Path no existente." << endl;
        return;
    }
    fclose(bfile2);

    /* Check that it worked */
    //cout << "Disco Leido:\nSize: " << discoEditar.size << "\nDate: " << discoEditar.date << "\nFit: " << discoEditar.fit << endl;

    //Editar disco.

    bool discoLLeno = true;
    int conteoExtendida = 0;
    bool tamanioPasado = false;
    int part_startExtendida = 0;
    bool ultimaParticion = false;

    //Valida numero de extendidas
    for (int i = 0; i < 4; i++)
    {
        if (discoEditar.mbr_particiones[i].type == 'E')
        {
            conteoExtendida++;
        }
    }

    //Valida si el disco esta lleno
    for (int i = 0; i < 4; i++)
    {
        if (discoEditar.mbr_particiones[i].Estado == '0')
        {
            discoLLeno = false;
            break;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        if (discoEditar.mbr_particiones[i].Estado != '0')
        {
            if (!(partition.type == 'E' && conteoExtendida > 0))
            {
                //AJUSTE
                char ajuste = toupper(discoEditar.fit);
                //PRIMER AJUSTE
                if (i == 0)
                {
                    if (discoEditar.mbr_particiones[i].part_start - sizeof(Structs::MBR) >= partition.size)
                    {
                        partition.part_start = sizeof(Structs::MBR);
                        break;
                    }
                }
                else
                {
                    if (discoEditar.mbr_particiones[i].part_start - (discoEditar.mbr_particiones[i - 1].part_start + discoEditar.mbr_particiones[i - 1].size) >= partition.size)
                    {
                        partition.part_start = discoEditar.mbr_particiones[i - 1].part_start + discoEditar.mbr_particiones[i - 1].size;

                        break;
                    }
                }

                //Es extendida, creo de una el EBR.
                if (discoEditar.mbr_particiones[i].type == 'E')
                {
                    part_startExtendida = discoEditar.mbr_particiones[i].part_start;
                }
            }
            else
            {
                cout << "Error: ya existe una particion extendida, no puedes crear otra." << endl;
                tamanioPasado = true;
            }
        }
        else
        {
            if (i == 0)
            {
                //PRIMERA POSICION
                partition.part_start = sizeof(Structs::MBR);
                break;
            }
            else
            {
                //ULTIMA POSICION
                ultimaParticion = true;
                break;
            }
        }
    }

    for (int i = 0; i < 4; i++)
    {
        if (discoEditar.mbr_particiones[i].Estado != '1')
        {
            if (ultimaParticion)
            {
                partition.part_start = discoEditar.mbr_particiones[i - 1].part_start + discoEditar.mbr_particiones[i - 1].size;
                if (discoEditar.size < (partition.part_start + partition.size))
                {
                    tamanioPasado = true;
                }
            }
            discoEditar.mbr_particiones[i] = partition;
            break;
        }
    }

    //METODO DE ORDENAMIENTO BURBUJA.
    Structs::Particion aux;
    for (int i = 1; i < 4; i++)
    {
        for (int j = 0; j < 4 - i; j++)
        {
            if ((discoEditar.mbr_particiones[j].part_start > discoEditar.mbr_particiones[j + 1].part_start) && discoEditar.mbr_particiones[j + 1].Estado != '0')
            {
                aux = discoEditar.mbr_particiones[j + 1];
                discoEditar.mbr_particiones[j + 1] = discoEditar.mbr_particiones[j];
                discoEditar.mbr_particiones[j] = aux;
            }
        }
    }

    if (!discoLLeno && !tamanioPasado)
    {
        FILE *bfile = fopen(path.c_str(), "rb+");
        if (bfile != NULL)
        {
            fseek(bfile, 0, SEEK_SET);
            fwrite(&discoEditar, sizeof(Structs::MBR), 1, bfile);

            //Crea primer EBR. - Siempre lo crea.
            if (part_startExtendida != 0)
            {
                fseek(bfile, 0, SEEK_SET);
                Structs::EBR logica;
                logica.part_start = part_startExtendida;
                strcpy(logica.name, "AhPerro");
                fseek(bfile, logica.part_start, SEEK_SET);
                fwrite(&logica, sizeof(Structs::EBR), 1, bfile);
            }
            //mkDisk::crearRaid(&disco, path);
        }
        fclose(bfile);

       /* cout << "<<------------------------ PARTICIONES ---------------------------->>" << endl;*/
        for (int i = 0; i < 4; i++)
        {
           /*cout << "<< ------------------- " << i << " -------------------" << endl;
            cout << "Estado: " << discoEditar.mbr_particiones[i].Estado << endl;
            cout << "Nombre: " << discoEditar.mbr_particiones[i].name << endl;
            cout << "Fit: " << discoEditar.mbr_particiones[i].fit << endl;
            cout << "Part_start: " << discoEditar.mbr_particiones[i].part_start << endl;
            cout << "Size: " << discoEditar.mbr_particiones[i].size << endl;
            cout << "Type: " << discoEditar.mbr_particiones[i].type << endl;*/
            if (discoEditar.mbr_particiones[i].type == 'E')
            {
                Structs::EBR logicaR;
                FILE *bfilel = fopen(path.c_str(), "rb+");
                if (bfilel != NULL)
                {
                    fseek(bfilel, 0, SEEK_SET);
                    fseek(bfilel, discoEditar.mbr_particiones[i].part_start, SEEK_SET);
                    fread(&logicaR, sizeof(Structs::EBR), 1, bfilel);
                }
                fclose(bfilel);
               // cout << "<< -------------------- Particion Logica --------------------->> " << endl;
                //cout << "Name Logica: " << logicaR.name << endl;
            }
        }
        fDisk::actualizarRaid(path);
    }
    else
    {
        if (discoLLeno)
        {
            cout << "Error: numero de particiones maximas creadas." << endl;
        }
        else
        {
            cout << "Error: tamanio de la particion sobre pasa el disco." << endl;
        }
    }
}

void fDisk::deleteParticion(string cdelete, string path, string name)
{ //Full or Fast
    cout << "Seguro que deseas eliminar la particion? [s/n]" << endl;
    string respuesta;
    cin >> respuesta;
    if (respuesta == "s")
    {
        if (fDisk::toLowerCase(cdelete) == "fast")
        {
            Structs::MBR discoEditar;
            FILE *bfile2 = fopen(path.c_str(), "rb+");
            if (bfile2 != NULL)
            {
                fseek(bfile2, 0, SEEK_SET);
                fread(&discoEditar, sizeof(discoEditar), 1, bfile2);

                //ELIMINANDO FAST
                for (int i = 0; i < 4; i++)
                {
                    if (strcmp(discoEditar.mbr_particiones[i].name, name.c_str()) == 0)
                    {
                        discoEditar.mbr_particiones[i].Estado = '0';
                        cout << "Particion eliminada correctamente./Fast" << endl;
                        int j = i;
                        Structs::Particion aux;
                        while (j != 3)
                        {
                            if (discoEditar.mbr_particiones[j + 1].Estado != '0')
                            {
                                aux = discoEditar.mbr_particiones[j];
                                discoEditar.mbr_particiones[j] = discoEditar.mbr_particiones[j + 1];
                                discoEditar.mbr_particiones[j + 1] = aux;
                            }
                            j++;
                        }
                        break;
                    }
                }

                fseek(bfile2, 0, SEEK_SET);
                fwrite(&discoEditar, sizeof(Structs::MBR), 1, bfile2);
            }
            else
            {
                cout << "Error: Path no existente en la eliminacion de particion." << endl;
                return;
            }
            fclose(bfile2);
            fDisk::actualizarRaid(path);
        }
        else if (fDisk::toLowerCase(cdelete) == "full")
        {
            Structs::MBR discoEditar;
            FILE *bfile2 = fopen(path.c_str(), "rb+");
            if (bfile2 != NULL)
            {
                fseek(bfile2, 0, SEEK_SET);
                fread(&discoEditar, sizeof(discoEditar), 1, bfile2);

                //ELIMINANDO FULL
                for (int i = 0; i < 4; i++)
                {
                    if (strcmp(discoEditar.mbr_particiones[i].name, name.c_str()) == 0)
                    {
                        discoEditar.mbr_particiones[i].Estado = '0';
                        discoEditar.mbr_particiones[i].fit = ' ';
                        strcpy(discoEditar.mbr_particiones[i].name, "");
                        discoEditar.mbr_particiones[i].part_start = 0;
                        discoEditar.mbr_particiones[i].size = 0;
                        discoEditar.mbr_particiones[i].type = ' ';

                        cout << "Particion eliminada correctamente. /Full" << endl;
                        int j = i;
                        Structs::Particion aux;
                        while (j != 3)
                        {
                            if (discoEditar.mbr_particiones[j + 1].Estado != '0')
                            {
                                aux = discoEditar.mbr_particiones[j];
                                discoEditar.mbr_particiones[j] = discoEditar.mbr_particiones[j + 1];
                                discoEditar.mbr_particiones[j + 1] = aux;
                            }
                            j++;
                        }
                        break;
                    }
                }

                fseek(bfile2, 0, SEEK_SET);
                fwrite(&discoEditar, sizeof(Structs::MBR), 1, bfile2);
            }
            else
            {
                cout << "Error: Path no existente en la eliminacion de particion." << endl;
                return;
            }
            fclose(bfile2);
            fDisk::actualizarRaid(path);
        }
        else
        {
            cout << "Error: Valor de delete es incorrecto." << endl;
        }
    }
    else
    {
        cout << "Comando cancelado" << endl;
    }
}

void fDisk::addParticion(string add, string unit, string name, string path)
{ // Positive or negative number
    int addSize = stoi(add);

    if (unit == "M" || unit == "m")
    {
        addSize = addSize * 1024 * 1024;
    }
    else if (unit == "K" || unit == "k")
    {
        addSize = addSize * 1024;
    }
    else if (unit == "B" || unit == "b")
    {
    }
    else
    {
        cout << "Error en la unidad de la particion" << endl;
    }

    Structs::MBR discoEditar;
    FILE *bfile2 = fopen(path.c_str(), "rb+");
    if (bfile2 != NULL)
    {
        fseek(bfile2, 0, SEEK_SET);
        fread(&discoEditar, sizeof(Structs::MBR), 1, bfile2);

        for (int i = 0; i < 4; i++)
        {
            if (strcmp(discoEditar.mbr_particiones[i].name, name.c_str()) == 0)
            {
                if (((discoEditar.mbr_particiones[i].size + (addSize)) > 0))
                {
                    if (discoEditar.mbr_particiones[i + 1].part_start != 0)
                    {
                        if (((discoEditar.mbr_particiones[i].size + (addSize) + discoEditar.mbr_particiones[i].part_start) <=
                             discoEditar.mbr_particiones[i + 1].part_start))
                        {
                            discoEditar.mbr_particiones[i].size = discoEditar.mbr_particiones[i].size + (addSize);
                            cout << "Size modificado correctamente" << endl;
                            break;
                        }
                        else
                        {
                            cout << "Error: size incorrecta, sobrepasa limite de particiones." << endl;
                        }
                    }
                    else
                    {
                        if ((discoEditar.mbr_particiones[i].size + (addSize) + discoEditar.mbr_particiones[i].part_start) <= discoEditar.size)
                        {
                            discoEditar.mbr_particiones[i].size = discoEditar.mbr_particiones[i].size + (addSize);
                            cout << "Size modificado correctamente" << endl;
                            break;
                        }
                        else
                        {
                            cout << "Error: size incorrecta, sobrepasa limite de disco." << endl;
                        }
                    }
                }
                else
                {
                    cout << "Error: Size menor a cero, no se puede reducir." << endl;
                }
            }
        }
        fseek(bfile2, 0, SEEK_SET);
        fwrite(&discoEditar, sizeof(Structs::MBR), 1, bfile2);
    }
    else
    {
        cout << "Error: Path no existente en la eliminacion de particion." << endl;
        return;
    }
    fclose(bfile2);
    fDisk::actualizarRaid(path);
}

void fDisk::primerAjuste()
{
    /*else //SIN AJUSTE
                {
                    if (i == 0)
                    {
                        partition.part_start = sizeof(Structs::MBR);
                    }
                    else
                    {
                        partition.part_start = discoEditar.mbr_particiones[i - 1].part_start + discoEditar.mbr_particiones[i - 1].size;
                    }
                    if (discoEditar.size < (partition.part_start + partition.size))
                    {
                        tamanioPasado = true;
                    }
                    discoEditar.mbr_particiones[i] = partition;
                }*/
}

void fDisk::mejorAjuste() {}

void fDisk::peorAjuste() {}

string fDisk::toLowerCase(string comando)
{
    string data = comando;
    transform(data.begin(), data.end(), data.begin(),
              [](unsigned char c) { return std::tolower(c); });
    return data;
}

void fDisk::actualizarRaid(string pathD)
{
    string path = pathD.substr(0, pathD.size() - 5);
    path = path + "_ra1.disk";

    std::ifstream srce(pathD.c_str(), std::ios::binary);
    std::ofstream dest(path.c_str(), std::ios::binary);
    dest << srce.rdbuf();
}
