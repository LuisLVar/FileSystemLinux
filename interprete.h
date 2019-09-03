#ifndef INTERPRETE_H
#define INTERPRETE_H

#include <string>
#include <vector>
#include "mount.h"

class Interprete
{
public:
    Interprete();
    void interpretar();
    void lineaComando(std::string comando);
    void ejecutarComando(std::vector<std::string> comando);
    void fexec(std::vector<std::string> commandArray);
    void fmkDisk(std::vector<std::string> commandArray);
    void frmDisk(std::vector<std::string> commandArray);
    void ffDisk(std::vector<std::string> commandArray);
    void fmount(std::vector<std::string> commandArray);
    void funmount(std::vector<std::string> commandArray);
    void frep(std::vector<std::string> commandArray);
    void errorComando(std::string error, int linea);
    std::string getAtributo(std::string comando);
    std::string getPath(std::vector<std::string> commandArray);
    std::string getFullPath(std::vector<std::string> commandArray, int j);

    std::string toLowerCase(std::string comando);
    void leerArchivo(std::string path);
    Mount montaje;
    void crearReporte(string path, string name, string id);

};

#endif // INTERPRETE_H
