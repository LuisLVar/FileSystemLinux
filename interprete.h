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
    void crearReporte(string path, string name, string id);

    //----------------------------- FASE 2 ----------------------------//
    void fmkfs(std::vector<std::string> commandArray);
    void flogin(std::vector<std::string> commandArray);
    void flogout();
    void fmkgrp(std::vector<std::string> commandArray);
    void frmgrp(std::vector<std::string> commandArray);
    void fmkusr(std::vector<std::string> commandArray);
    void frmusr(std::vector<std::string> commandArray);
    void fchmod(std::vector<std::string> commandArray);
    void fmkfile(std::vector<std::string> commandArray);
    void fcat(std::vector<std::string> commandArray);
    void frem(std::vector<std::string> commandArray);
    void fedit(std::vector<std::string> commandArray);
    void fren(std::vector<std::string> commandArray);
    void fmkdir(std::vector<std::string> commandArray);
    void fcp(std::vector<std::string> commandArray);
    void fmv(std::vector<std::string> commandArray);
    void ffind(std::vector<std::string> commandArray);
    void fchown(std::vector<std::string> commandArray);
    void fchgrp(std::vector<std::string> commandArray);
    void fpause();
    void frecovery(std::vector<std::string> commandArray);
    void floss(std::vector<std::string> commandArray);
};

#endif // INTERPRETE_H
