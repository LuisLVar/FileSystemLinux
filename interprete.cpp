#include "interprete.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cctype>
#include "mkdisk.h"
#include "rmdisk.h"
#include "fdisk.h"
#include "mount.h"
#include "rep.h"
#include "mkfs.h"
#include "login.h"
#include "group.h"
#include "user.h"
#include "archivo.h"
#include "carpeta.h"
#include "change.h"
#include "ext3.h"
#include <fstream>
#include <sstream>

using namespace std;

Mount montaje;

Interprete::Interprete()
{
}

void Interprete::interpretar()
{
    bool finalizar = false;
    string inicio = "Bienvenido a la consola de comandos... ('x' para finalizar)";
    cout << inicio << endl;
    string comando;
    getline(cin, comando);

    if (comando == "x")
    {
        finalizar = true;
    }
    else
    {
        Interprete::lineaComando(comando);
    }

    while (finalizar != true)
    {
        cout << "Insertar comando: " << endl;
        getline(cin, comando);
        if (comando == "x")
        {
            finalizar = true;
        }
        else
        {
            if (comando != "")
            {
                Interprete::lineaComando(comando);
            }
        }
    }
}

void Interprete::lineaComando(string comando)
{
    //cout << "Comando: " << comando << endl;

    bool comentario = false;

    vector<string> commandArray;
    stringstream total(comando);
    string tmp;

    while (getline(total, tmp, ' '))
    {
        commandArray.push_back(tmp);
    }

    char comentarioLetra = commandArray[0].at(0);

    if (comentarioLetra == '#')
    {
        comentario = true;
    }

    if (comentario)
    {
        //cout << "Has escrito un comentario" << endl;
        cout << comando << endl;
    }
    else
    {
        Interprete::ejecutarComando(commandArray);
    }
}

void Interprete::ejecutarComando(vector<string> commandArray)
{
    string data = Interprete::toLowerCase(commandArray[0]);
    if (data == "exec")
    {
        Interprete::fexec(commandArray); //DONE
    }
    else if (data == "mkdisk")
    {
        Interprete::fmkDisk(commandArray); //DONE - REVISAR CAMBIO EN EL SIZE DEL DISCO.
    }
    else if (data == "rmdisk")
    {
        Interprete::frmDisk(commandArray); //DONE
    }
    else if (data == "fdisk")
    {
        Interprete::ffDisk(commandArray); //DONE
    }
    else if (data == "mount")
    {
        Interprete::fmount(commandArray); //DONE
    }
    else if (data == "unmount")
    {
        Interprete::funmount(commandArray); //DONE
    }
    else if (data == "rep")
    {
        Interprete::frep(commandArray); //DONE
    }
    else if (data == "mkfs")
    {
        Interprete::fmkfs(commandArray); //PENDIENTE
    }
    else if (data == "login")
    {
        Interprete::flogin(commandArray); //PENDIENTE
    }
    else if (data == "logout")
    {
        Interprete::flogout(); //PENDIENTE
    }
    else if (data == "mkgrp")
    {
        Interprete::fmkgrp(commandArray); //PENDIENTE
    }
    else if (data == "rmgrp")
    {
        Interprete::frmgrp(commandArray); //PENDIENTE
    }
    else if (data == "mkusr")
    {
        Interprete::fmkusr(commandArray); //PENDIENTE
    }
    else if (data == "rmusr")
    {
        Interprete::frmusr(commandArray); //PENDIENTE
    }
    else if (data == "chmod")
    {
        Interprete::fchmod(commandArray); //PENDIENTE
    }
    else if (data == "mkfile")
    {
        Interprete::fmkfile(commandArray); //PENDIENTE
    }
    else if (data == "cat")
    {
        Interprete::fcat(commandArray); //PENDIENTE
    }
    else if (data == "rem")
    {
        Interprete::frem(commandArray); //PENDIENTE
    }
    else if (data == "edit")
    {
        Interprete::fedit(commandArray); //PENDIENTE
    }
    else if (data == "ren")
    {
        Interprete::fren(commandArray); //PENDIENTE
    }
    else if (data == "mkdir")
    {
        Interprete::fmkdir(commandArray); //PENDIENTE
    }
    else if (data == "cp")
    {
        Interprete::fcp(commandArray); //PENDIENTE
    }
    else if (data == "mv")
    {
        Interprete::fmv(commandArray); //PENDIENTE
    }
    else if (data == "find")
    {
        Interprete::ffind(commandArray); //PENDIENTE
    }
    else if (data == "chown")
    {
        Interprete::fchown(commandArray); //PENDIENTE
    }
    else if (data == "chgrp")
    {
        Interprete::fchgrp(commandArray); //PENDIENTE
    }
    else if (data == "pause")
    {
        Interprete::fpause(); //DONE
    }
    else if (data == "recovery")
    {
        Interprete::frecovery(commandArray); //PENDIENTE
    }
    else if (data == "loss")
    {
        Interprete::floss(commandArray); //PENDIENTE
    }
    else
    {
        Interprete::errorComando(commandArray[0], 1);
    }
}

void Interprete::fexec(vector<string> commandArray)
{
    string pathCommand = Interprete::getPath(commandArray);
    string path = Interprete::getAtributo(pathCommand);
    path.erase(remove(path.begin(), path.end(), '\"'), path.end());
    //Scout << "Path: " << path << endl;
    Interprete::leerArchivo(path);
}

void Interprete::fmkDisk(vector<string> commandArray)
{
    string size = "";
    string fit = "";
    string unit = "";
    string path = "";

    for (int i = 0; i < commandArray.size(); i++)
    {
        string comando = Interprete::toLowerCase(commandArray[i].substr(1, 4));
        if (comando == "size")
        {
            size = Interprete::getAtributo(commandArray[i]);
        }
        else if (comando == "fit=")
        {
            fit = Interprete::getAtributo(commandArray[i]);
        }
        else if (comando == "unit")
        {
            unit = Interprete::getAtributo(commandArray[i]);
        }
        else if (comando == "path")
        {
            if (commandArray[i].substr(6, 1) != "\"")
            {
                path = Interprete::getAtributo(commandArray[i]);
            }
            else
            {
                path = Interprete::getFullPath(commandArray, i);
            }
        }
    }

    /*cout << "Size = " << size << endl;
    cout << "Fit = " << fit << endl;
    cout << "Unit = " << unit << endl;
    cout << "Path = " << path << endl;*/

    mkDisk disco;
    disco.crearDisco(size, fit, unit, path);
}

void Interprete::frmDisk(vector<string> commandArray)
{
    string pathCommand = Interprete::getPath(commandArray);
    string path = Interprete::getAtributo(pathCommand);
    path.erase(remove(path.begin(), path.end(), '\"'), path.end());
    //cout << "Path a eliminar: " << path << endl;
    cout << "Seguro que deseas eliminar el disco? [s/n]" << endl;
    string respuesta;
    cin >> respuesta;
    if (respuesta == "s")
    {
        rmDisk disco;
        disco.eliminarDisco(path);
    }
    else
    {
        cout << "Comando cancelado" << endl;
    }
}

void Interprete::ffDisk(vector<string> commandArray)
{

    string size = "";
    string unit = "";
    string path = "";
    string fit = "";
    string type = "";
    string cdelete = "";
    string name = "";
    string add = "";

    for (int i = 0; i < commandArray.size(); i++)
    {
        string comando = Interprete::toLowerCase(commandArray[i].substr(1, 4));
        string comandoDelete = Interprete::toLowerCase(commandArray[i].substr(1, 6));
        if (comando == "size")
        {
            size = Interprete::getAtributo(commandArray[i]);
        }
        else if (comando == "fit=")
        {
            fit = Interprete::getAtributo(commandArray[i]);
        }
        else if (comando == "unit")
        {
            unit = Interprete::getAtributo(commandArray[i]);
        }
        else if (comando == "type")
        {
            type = Interprete::getAtributo(commandArray[i]);
        }
        else if (comandoDelete == "delete")
        {
            cdelete = Interprete::getAtributo(commandArray[i]);
        }
        else if (comando == "add=")
        {
            add = Interprete::getAtributo(commandArray[i]);
        }
        else if (comando == "name")
        {
            name = Interprete::getAtributo(commandArray[i]);
        }
        else if (comando == "path")
        {
            if (commandArray[i].substr(6, 1) != "\"")
            {
                path = Interprete::getAtributo(commandArray[i]);
            }
            else
            {
                path = Interprete::getFullPath(commandArray, i);
            }
        }
    }

    if (unit == "")
    {
        unit = "K";
    }
    if (type == "")
    {
        type = "P";
    }
    if (fit == "")
    {
        fit = "WF";
    }

    fDisk disco;
    disco.administrarParticion(size, unit, path, fit, type, cdelete, name, add);
}

void Interprete::fmount(vector<string> commandArray)
{
    string name = "";
    string path = "";
    for (int i = 0; i < commandArray.size(); i++)
    {
        string comando = Interprete::toLowerCase(commandArray[i].substr(1, 4));
        if (comando == "name")
        {
            name = Interprete::getAtributo(commandArray[i]);
        }
        else if (comando == "path")
        {
            if (commandArray[i].substr(6, 1) != "\"")
            {
                path = Interprete::getAtributo(commandArray[i]);
            }
            else
            {
                path = Interprete::getFullPath(commandArray, i);
            }
        }
    }
    montaje.montarParticion(path, name);
}

void Interprete::funmount(vector<string> commandArray)
{

    string id = Interprete::getAtributo(commandArray[1]);
    ;
    cout << "ID: " << id << endl;
    montaje.desmontarParticion(toLowerCase(id));
}

void Interprete::frep(vector<string> commandArray)
{
    string name = "";
    string path = "";
    string id = "";
    for (int i = 0; i < commandArray.size(); i++)
    {
        string comando = Interprete::toLowerCase(commandArray[i].substr(1, 4));
        string comandoID = Interprete::toLowerCase(commandArray[i].substr(1, 2));
        if (comando == "name")
        {
            name = Interprete::getAtributo(commandArray[i]);
        }
        else if (comandoID == "id")
        {
            id = Interprete::getAtributo(commandArray[i]);
        }
        else if (comando == "path")
        {
            if (commandArray[i].substr(6, 1) != "\"")
            {
                path = Interprete::getAtributo(commandArray[i]);
            }
            else
            {
                path = Interprete::getFullPath(commandArray, i);
            }
        }
    }
    //Rep reporte;
    //Interprete::crearReporte(path, toLowerCase(name), toLowerCase(id));
    Rep reporte;
    reporte.crearReporte(path, toLowerCase(name), toLowerCase(id));
}

void Interprete::errorComando(string error, int linea)
{
    cout << "Error en el comando: " << error << endl;
}

string Interprete::getAtributo(string comando)
{
    vector<string> commandArray;
    stringstream total(comando);
    string tmp;

    while (getline(total, tmp, '='))
    {
        commandArray.push_back(tmp);
    }
    if (!commandArray[1].empty())
    {
        return commandArray[1];
    }
    else
    {
        cout << "Error en recoleccion de atributo" << endl;
    }
}

string Interprete::getPath(vector<string> commandArray)
{
    string path = commandArray[1];
    for (int i = 2; i < commandArray.size(); i++)
    {
        path = path + " " + commandArray[i];
    }
    if (path.substr(path.size() - 1, 1) == " ")
    {
        path = path.substr(0, path.size() - 1);
    }
    return path;
}

string Interprete::getFullPath(vector<string> commandArray, int j)
{
    string path = commandArray[j].substr(6, commandArray[j].size() - 5);
    for (int i = j + 1; i < commandArray.size(); i++)
    {
        if (commandArray[i].substr(0, 1) != "-")
        {
            path = path + " " + commandArray[i];
        }
        else
        {
            break;
        }
    }
    if (path.substr(path.size() - 1, 1) == " ")
    {
        path = path.substr(0, path.size() - 1);
    }

    path.erase(remove(path.begin(), path.end(), '\"'), path.end());

    return path;
}

string Interprete::toLowerCase(string comando)
{
    string data = comando;
    transform(data.begin(), data.end(), data.begin(),
              [](unsigned char c) { return std::tolower(c); });
    return data;
}

void Interprete::leerArchivo(string path)
{

    ifstream infile(path.c_str());

    std::string comando;
    while (std::getline(infile, comando))
    {
        std::istringstream iss(comando);
        //cout << line << endl;
        if (comando != "" && comando != "\n")
        {
            cout << comando << endl;
            Interprete::lineaComando(comando);
        }
    }
}

//------------------------------------------SEGUNDA FASE  - FILE SYSTEM ---------------------------------------------//

void Interprete::fmkfs(vector<string> commandArray)
{
    string id = "";
    string type = "";
    string fs = "";

    for (int i = 0; i < commandArray.size(); i++)
    {
        string comando = Interprete::toLowerCase(commandArray[i].substr(1, 4));
        string comando2 = Interprete::toLowerCase(commandArray[i].substr(1, 2));
        if (comando == "type")
        {
            type = Interprete::getAtributo(commandArray[i]);
        }
        else if (comando2 == "id")
        {
            id = Interprete::getAtributo(commandArray[i]);
        }
        else if (comando2 == "fs")
        {
            fs = Interprete::getAtributo(commandArray[i]);
        }
    }

    if (fs == "")
    {
        fs = "2fs";
    }

    Mkfs fileSystem;
    fileSystem.formatearFS(id, type, fs);
}

//-------------------------------------------- SESIONES ------------------------------//

void Interprete::flogin(vector<string> commandArray)
{
    string usr = "";
    string pwd = "";
    string id = "";

    for (int i = 0; i < commandArray.size(); i++)
    {
        string comando = Interprete::toLowerCase(commandArray[i].substr(1, 3));
        if (comando == "usr")
        {
            usr = Interprete::getAtributo(commandArray[i]);
        }
        else if (comando == "pwd")
        {
            pwd = Interprete::getAtributo(commandArray[i]);
        }
        else if (comando == "id=")
        {
            id = Interprete::getAtributo(commandArray[i]);
        }
    }

    Login log;
    log.iniciarSesion(usr, pwd, id);
}

void Interprete::flogout()
{
    Login log;
    log.cerrarSesion();
}

//------------------------------------------- GRUPOS -----------------------------------//

void Interprete::fmkgrp(vector<string> commandArray)
{
    string name = "";

    for (int i = 0; i < commandArray.size(); i++)
    {
        string comando = Interprete::toLowerCase(commandArray[i].substr(1, 4));
        if (comando == "name")
        {
            name = Interprete::getAtributo(commandArray[i]);
        }
    }

    Group grupo;
    grupo.makeGroup(name);
}
void Interprete::frmgrp(vector<string> commandArray)
{
    string name = "";

    for (int i = 0; i < commandArray.size(); i++)
    {
        string comando = Interprete::toLowerCase(commandArray[i].substr(1, 4));
        if (comando == "name")
        {
            name = Interprete::getAtributo(commandArray[i]);
        }
    }
    Group grupo;
    grupo.removeGroup(name);
}

//------------------------------------------- USUARIOS -----------------------------------//
void Interprete::fmkusr(vector<string> commandArray)
{
    string usr = "";
    string pwd = "";
    string grp = "";

    for (int i = 0; i < commandArray.size(); i++)
    {
        string comando = Interprete::toLowerCase(commandArray[i].substr(1, 3));
        if (comando == "usr")
        {
            usr = Interprete::getAtributo(commandArray[i]);
        }
        else if (comando == "pwd")
        {
            pwd = Interprete::getAtributo(commandArray[i]);
        }
        else if (comando == "grp")
        {
            grp = Interprete::getAtributo(commandArray[i]);
        }
    }

    User usuario;
    usuario.makeUser(usr, pwd, grp);
}
void Interprete::frmusr(vector<string> commandArray)
{
    string usr = "";

    for (int i = 0; i < commandArray.size(); i++)
    {
        string comando = Interprete::toLowerCase(commandArray[i].substr(1, 3));
        if (comando == "usr")
        {
            usr = Interprete::getAtributo(commandArray[i]);
        }
    }
    User usuario;
    usuario.removeUser(usr);
}

//------------------------------------------- PERMISOS - USERS -----------------------------------//
void Interprete::fchmod(vector<string> commandArray)
{
    string path = "";
    string ugo = "";
    int r = 0;

    for (int i = 0; i < commandArray.size(); i++)
    {
        string comando = Interprete::toLowerCase(commandArray[i].substr(1, 4));
        string comandoR = Interprete::toLowerCase(commandArray[i].substr(1, 1));
        if (comando == "path")
        {
            if (commandArray[i].substr(6, 1) != "\"")
            {
                path = Interprete::getAtributo(commandArray[i]);
            }
            else
            {
                path = Interprete::getFullPath(commandArray, i);
            }
        }
        else if (comando == "ugo=")
        {
            ugo = Interprete::getAtributo(commandArray[i]);
        }
        else if (comandoR == "r")
        {
            r = 1;
        }
    }

    User usuario;
    usuario.changeMod(path, ugo, r);
}

//------------------------------------------- ARCHIVOS -----------------------------------//
void Interprete::fmkfile(vector<string> commandArray)
{
    string path = "";
    string size = "";
    string cont = "";
    int p = 0;

    for (int i = 0; i < commandArray.size(); i++)
    {
        string comando = Interprete::toLowerCase(commandArray[i].substr(1, 4));
        string comandoP = Interprete::toLowerCase(commandArray[i].substr(1, 1));
        if (comando == "path")
        {
            if (commandArray[i].substr(6, 1) != "\"")
            {
                path = Interprete::getAtributo(commandArray[i]);
            }
            else
            {
                path = Interprete::getFullPath(commandArray, i);
            }
        }
        else if (comando == "size")
        {
            size = Interprete::getAtributo(commandArray[i]);
        }
        else if (comando == "cont")
        {
            cont = Interprete::getAtributo(commandArray[i]);
        }
        else if (comandoP == "p")
        {
            p = 1;
        }
    }

    Archivo file;
    file.makeFile(path, p, size, cont);
}
void Interprete::fcat(vector<string> commandArray)
{
    string path = "";

    for (int i = 0; i < commandArray.size(); i++)
    {
        string comando = Interprete::toLowerCase(commandArray[i].substr(1, 4));
        if (comando == "file")
        {
            if (commandArray[i].substr(6, 1) != "\"")
            {
                path = Interprete::getAtributo(commandArray[i]);
            }
            else
            {
                path = Interprete::getFullPath(commandArray, i);
            }
        }
    }

    Archivo file;
    file.showContent(path);
}
void Interprete::frem(vector<string> commandArray)
{
    string path = "";

    for (int i = 0; i < commandArray.size(); i++)
    {
        string comando = Interprete::toLowerCase(commandArray[i].substr(1, 4));
        if (comando == "path")
        {
            if (commandArray[i].substr(6, 1) != "\"")
            {
                path = Interprete::getAtributo(commandArray[i]);
            }
            else
            {
                path = Interprete::getFullPath(commandArray, i);
            }
        }
    }

    Archivo file;
    file.removeFile(path);
}
void Interprete::fedit(vector<string> commandArray)
{
    string path = "";
    string cont = "";

    for (int i = 0; i < commandArray.size(); i++)
    {
        string comando = Interprete::toLowerCase(commandArray[i].substr(1, 4));
        if (comando == "path")
        {
            if (commandArray[i].substr(6, 1) != "\"")
            {
                path = Interprete::getAtributo(commandArray[i]);
            }
            else
            {
                path = Interprete::getFullPath(commandArray, i);
            }
        }
        else if (comando == "cont")
        {
            cont = Interprete::getAtributo(commandArray[i]);
        }
    }

    Archivo file;
    file.editFile(path, cont);
}

//------------------------------------------- CARPETAS -----------------------------------//

void Interprete::fren(vector<string> commandArray)
{
    string path = "";
    string name = "";

    for (int i = 0; i < commandArray.size(); i++)
    {
        string comando = Interprete::toLowerCase(commandArray[i].substr(1, 4));
        if (comando == "path")
        {
            if (commandArray[i].substr(6, 1) != "\"")
            {
                path = Interprete::getAtributo(commandArray[i]);
            }
            else
            {
                path = Interprete::getFullPath(commandArray, i);
            }
        }
        else if (comando == "name")
        {
            name = Interprete::getAtributo(commandArray[i]);
        }
    }

    Carpeta directory;
    directory.renameFile(path, name);
}

void Interprete::fmkdir(vector<string> commandArray)
{
    string path = "";
    int p = 0;

    for (int i = 0; i < commandArray.size(); i++)
    {
        string comando = Interprete::toLowerCase(commandArray[i].substr(1, 4));
        string comandoP = Interprete::toLowerCase(commandArray[i].substr(1, 1));
        if (comando == "path")
        {
            if (commandArray[i].substr(6, 1) != "\"")
            {
                path = Interprete::getAtributo(commandArray[i]);
            }
            else
            {
                path = Interprete::getFullPath(commandArray, i);
            }
        }
        else if (comandoP == "p")
        {
            p = 1;
        }
    }

    Carpeta directory;
    directory.makeDirectory(path, p);
}
void Interprete::fcp(vector<string> commandArray)
{
    string path = "";
    string dest = "";

    for (int i = 0; i < commandArray.size(); i++)
    {
        string comando = Interprete::toLowerCase(commandArray[i].substr(1, 4));
        if (comando == "path")
        {
            if (commandArray[i].substr(6, 1) != "\"")
            {
                path = Interprete::getAtributo(commandArray[i]);
            }
            else
            {
                path = Interprete::getFullPath(commandArray, i);
            }
        }
        else if (comando == "dest")
        {
            if (commandArray[i].substr(6, 1) != "\"")
            {
                dest = Interprete::getAtributo(commandArray[i]);
            }
            else
            {
                dest = Interprete::getFullPath(commandArray, i);
            }
        }
    }

    Carpeta directory;
    directory.copyFile(path, dest);
}
void Interprete::fmv(vector<string> commandArray)
{
    string path = "";
    string dest = "";

    for (int i = 0; i < commandArray.size(); i++)
    {
        string comando = Interprete::toLowerCase(commandArray[i].substr(1, 4));
        if (comando == "path")
        {
            if (commandArray[i].substr(6, 1) != "\"")
            {
                path = Interprete::getAtributo(commandArray[i]);
            }
            else
            {
                path = Interprete::getFullPath(commandArray, i);
            }
        }
        else if (comando == "dest")
        {
            if (commandArray[i].substr(6, 1) != "\"")
            {
                dest = Interprete::getAtributo(commandArray[i]);
            }
            else
            {
                dest = Interprete::getFullPath(commandArray, i);
            }
        }
    }

    Carpeta directory;
    directory.moveFile(path, dest);
}
void Interprete::ffind(vector<string> commandArray)
{
    string path = "";
    string name = "";

    for (int i = 0; i < commandArray.size(); i++)
    {
        string comando = Interprete::toLowerCase(commandArray[i].substr(1, 4));
        if (comando == "path")
        {
            if (commandArray[i].substr(6, 1) != "\"")
            {
                path = Interprete::getAtributo(commandArray[i]);
            }
            else
            {
                path = Interprete::getFullPath(commandArray, i);
            }
        }
        else if (comando == "name")
        {
            name = Interprete::getAtributo(commandArray[i]);
        }
    }

    Carpeta directory;
    directory.findFile(path, name);
}

//------------------------------------------- CHANGES -----------------------------------//
void Interprete::fchown(vector<string> commandArray)
{
    string path = "";
    string usr = "";
    int r = 0;

    for (int i = 0; i < commandArray.size(); i++)
    {
        string comando = Interprete::toLowerCase(commandArray[i].substr(1, 4));
        string comandoP = Interprete::toLowerCase(commandArray[i].substr(1, 1));
        if (comando == "path")
        {
            if (commandArray[i].substr(6, 1) != "\"")
            {
                path = Interprete::getAtributo(commandArray[i]);
            }
            else
            {
                path = Interprete::getFullPath(commandArray, i);
            }
        }
        else if (comando == "usr=")
        {
            usr = Interprete::getAtributo(commandArray[i]);
        }
        else if (comandoP == "r")
        {
            r = 1;
        }
    }

    Change cambio;
    cambio.changeOwner(path, r, usr);
}
void Interprete::fchgrp(vector<string> commandArray)
{
    string grp = "";
    string usr = "";

    for (int i = 0; i < commandArray.size(); i++)
    {
        string comando = Interprete::toLowerCase(commandArray[i].substr(1, 3));
        if (comando == "usr")
        {
            usr = Interprete::getAtributo(commandArray[i]);
        }
        else if (comando == "grp")
        {
            grp = Interprete::getAtributo(commandArray[i]);
        }
    }

    Change cambio;
    cambio.changeGroup(usr, grp);
}

//------------------------------------------- EXT3/JOURNALING -----------------------------------//
void Interprete::frecovery(vector<string> commandArray)
{
    string id = "";

    for (int i = 0; i < commandArray.size(); i++)
    {
        string comando = Interprete::toLowerCase(commandArray[i].substr(1, 2));
        if (comando == "id")
        {
            id = Interprete::getAtributo(commandArray[i]);
        }
    }

    Ext3 fileSystem;
    fileSystem.recoveryFS(id);
}
void Interprete::floss(vector<string> commandArray)
{
    string id = "";

    for (int i = 0; i < commandArray.size(); i++)
    {
        string comando = Interprete::toLowerCase(commandArray[i].substr(1, 2));
        if (comando == "id")
        {
            id = Interprete::getAtributo(commandArray[i]);
        }
    }

    Ext3 fileSystem;
    fileSystem.simulateLoss(id);
}

void Interprete::fpause()
{
    cout << "Comando pause: presiona una tecla para continuar..." << endl;
    getchar();
}
