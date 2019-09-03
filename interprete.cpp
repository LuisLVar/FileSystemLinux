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
#include <fstream>
#include <sstream>

using namespace std;

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
        Interprete::fmkDisk(commandArray); //DONE
    }
    else if (data == "rmdisk")
    {
        Interprete::frmDisk(commandArray); //DONE
    }
    else if (data == "fdisk")
    {
        Interprete::ffDisk(commandArray); //PENDIENTE
        //cout << "Entro fdisk" << endl;
    }
    else if (data == "mount")
    {
        Interprete::fmount(commandArray); //PENDIENTE
        //cout << "Entro mount" << endl;
    }
    else if (data == "unmount")
    {
        Interprete::funmount(commandArray); //PENDIENTE
        //cout << "Entro unmount" << endl;
    }
    else if (data == "rep")
    {
        Interprete::frep(commandArray); //PENDIENTE
        //cout << "Entro rep" << endl;
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
    //cout << "Entro mkDisk" << endl;
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
    //cout << "Entro rmDisk" << endl;
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
    //cout << "Entro fDisk" << endl;

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
    //cout << "Entro mount" << endl;
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
    Interprete::montaje.montarParticion(path, name);
}

void Interprete::funmount(vector<string> commandArray)
{
    //cout << "Entro unmount" << endl;

    string id = Interprete::getAtributo(commandArray[1]);
    ;
    cout << "ID: " << id << endl;
    Interprete::montaje.desmontarParticion(toLowerCase(id));
}

void Interprete::frep(vector<string> commandArray)
{
    //cout << "Entro rep" << endl;
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
    Interprete::crearReporte(path, toLowerCase(name), toLowerCase(id));
}

void Interprete::errorComando(string error, int linea)
{
    cout << "Error en el comando: " << error << ", linea: " << linea << endl;
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

void Interprete::crearReporte(string path, string name, string id)
{
    //Mount montaje1 = Interprete::montaje;
    //montaje.leerMontajes();

    char letra = id.c_str()[2];
    char numero = id.c_str()[3];
    bool existePath = false;
    int numeroInt = (int)numero - 48;

    char pathDisco[100] = "";

    for (int i = 0; i < 26; i++)
    {
        if (montaje.discos[i].letra == letra)
        {
            strcpy(pathDisco, montaje.discos[i].path);
            existePath = true;
            break;
        }
    }

    if (!existePath)
    {
        cout << "Error: id no existe, path no existente." << endl;
        return;
    }

    Structs::MBR discoEditar;
    FILE *bfile2 = fopen(pathDisco, "rb+");
    if (bfile2 != NULL)
    {
        rewind(bfile2);
        fread(&discoEditar, sizeof(discoEditar), 1, bfile2);
    }
    else
    {
        cout << "Error. Path no existente, disco no existente." << endl;
        return;
    }
    fclose(bfile2);

    if (name == "mbr")
    {
        string codigoInterno = "";
        string size = to_string(discoEditar.size);
        string date(discoEditar.date);
        string firma = to_string(discoEditar.disk_signature);
        string fit = "";
        fit.push_back(discoEditar.fit);

        codigoInterno = "<TR>\n"
                        "<TD><B>MBR_Tamanio</B></TD>\n"
                        "<TD>" +
                        size + "</TD>\n"
                               "</TR>\n"
                               "<TR>\n"
                               "<TD><B>MBR_Fecha_Creacion</B></TD>\n"
                               "<TD>" +
                        date + "</TD>\n"
                               "</TR>\n"
                               "<TR>\n"
                               "<TD><B>MBR_Disk_Signature</B></TD>\n"
                               "<TD>" +
                        firma + "</TD>\n"
                                "</TR>\n"
                                "<TR>\n"
                                "<TD><B>MBR_Disk_Fit</B></TD>\n"
                                "<TD>" +
                        fit + "</TD>\n"
                              "</TR>\n";

        string codigoParticiones = "";
        for (int i = 0; i < 4; i++)
        {
            if (discoEditar.mbr_particiones[i].Estado == '1')
            {
                string size = to_string(discoEditar.mbr_particiones[i].size);
                string name(discoEditar.mbr_particiones[i].name);
                string Estado = "";
                Estado.push_back(discoEditar.mbr_particiones[i].Estado);
                string fit = "";
                fit.push_back(discoEditar.mbr_particiones[i].fit);
                string type = "";
                type.push_back(discoEditar.mbr_particiones[i].type);
                string part_start = to_string(discoEditar.mbr_particiones[i].part_start);
                string indice = to_string((i + 1));

                codigoParticiones = codigoParticiones +
                                    "<TR>\n"
                                    "<TD><B>part_Estado_" +
                                    indice + "</B></TD>\n"
                                             "<TD>" +
                                    Estado + "</TD>\n"
                                             "</TR>\n"
                                             "<TR>\n"
                                             "<TD><B>part_Type_" +
                                    indice + "</B></TD>\n"
                                             "<TD>" +
                                    type + "</TD>\n"
                                           "</TR>\n"
                                           "<TR>\n"
                                           "<TD><B>part_Fit_" +
                                    indice + "</B></TD>\n"
                                             "<TD>" +
                                    fit + "</TD>\n"
                                          "</TR>\n"
                                          "<TR>\n"
                                          "<TD><B>part_Start_" +
                                    indice + "</B></TD>\n"
                                             "<TD>" +
                                    part_start + "</TD>\n"
                                                 "</TR>\n"
                                                 "<TR>\n"
                                                 "<TD><B>part_Name_" +
                                    indice + "</B></TD>\n"
                                             "<TD>" +
                                    name + "</TD>\n"
                                           "</TR>\n";
            }
        }

        string codigo = "digraph  {\n"
                        "graph[ratio = fill];\n"
                        " node [label=\"\N\", fontsize=15, shape=plaintext];\n"
                        "graph [bb=\"0,0,352,154\"];\n"
                        "arset [label=<\n"
                        " <TABLE ALIGN=\"LEFT\">\n"
                        "<TR>\n"
                        " <TD><B>Nombre</B></TD>\n"
                        "<TD><B> Valor </B></TD>\n"
                        "</TR>\n" +
                        codigoInterno +
                        codigoParticiones +
                        "</TABLE>\n"
                        ">, ];\n"
                        "}";

        string path1 = path;
        string pathPng = path1.substr(0, path1.size() - 4);
        pathPng = pathPng + ".png";

        FILE *validar = fopen(path1.c_str(), "r");
        if (validar != NULL)
        {
            std::ofstream outfile(path1);
            outfile << codigo.c_str() << endl;
            outfile.close();
            string comando = "dot -Tpng " + path1 + " -o " + pathPng;

            system(comando.c_str());
            fclose(validar);
        }
        else
        {
            string comando1 = "mkdir -p \"" + path + "\"";
            string comando2 = "rmdir \"" + path + "\"";
            system(comando1.c_str());
            system(comando2.c_str());

            std::ofstream outfile(path1);
            outfile << codigo.c_str() << endl;
            outfile.close();
            string comando = "dot -Tpng " + path1 + " -o " + pathPng;
            system(comando.c_str());
        }
    }
    else if (name == "disk")
    {
        string codigoInterno = "";
        string size = to_string(discoEditar.size);
        string date(discoEditar.date);
        string firma = to_string(discoEditar.disk_signature);
        string fit = "";
        fit.push_back(discoEditar.fit);
        int acumulado = 0;

        string codigoParticiones = "";
        for (int i = 0; i < 4; i++)
        {
            if (discoEditar.mbr_particiones[i].Estado == '1')
            {
                string name(discoEditar.mbr_particiones[i].name);
                string Estado = "";
                Estado.push_back(discoEditar.mbr_particiones[i].Estado);
                string type = "";
                type.push_back(discoEditar.mbr_particiones[i].type);
                int porcentaje = ((discoEditar.mbr_particiones[i].size * 100) / discoEditar.size);
                acumulado = acumulado + porcentaje;
                string porcentajeString = to_string(porcentaje);

                if (type == "P" || type == "L")
                {
                    codigoParticiones = codigoParticiones +
                                        "<TD>    <TABLE BORDER=\"0\">\n"
                                        "<TR><TD>" +
                                        name + " (" + type + ")"
                                                             "</TD></TR>\n"
                                                             "<TR><TD>" +
                                        porcentajeString + "%</TD></TR>\n"
                                                           "</TABLE>\n"
                                                           "</TD>\n";
                }
                else if (type == "E")
                {
                    codigoParticiones = codigoParticiones +
                                        "<TD> <TABLE BORDER=\"1\">\n"
                                                                 "<TR><TD>"+name + " (EXTENDIDA)</TD></TR>\n"
                                                                 "<TR><TD><TABLE ALIGN=\"LEFT\">\n"
                                                                 "<TR>\n"
                                                                 "<TD>EBR</TD>\n"
                                                                 "<TD>"+porcentajeString+"%</TD>\n"
                                                                 "</TR></TABLE></TD></TR>\n"
                                                                 "</TABLE></TD>\n";

                }
            }
        }

        int libre = 100 - acumulado;
        string libreString = to_string(libre);
        if(acumulado<100){
                    codigoParticiones = codigoParticiones +
                                        "<TD>    <TABLE BORDER=\"0\">\n"
                                        "<TR><TD> Libre "
                                                             "</TD></TR>\n"
                                                             "<TR><TD>" +libreString + "%</TD></TR>\n"
                                                           "</TABLE>\n"
                                                           "</TD>\n";

        }

        string codigo = "digraph  {\n"
                        "graph[ratio = fill];\n"
                        " node [label=\"\N\", fontsize=15, shape=plaintext];\n"
                        "graph [bb=\"0,0,352,154\"];\n"
                        "arset [label=<\n"
                        " <TABLE ALIGN=\"LEFT\">\n"
                        "<TR>\n"
                        "<TD>MBR</TD>\n" +
                        codigoParticiones +
                        "</TR>\n" +
                        "</TABLE>\n"
                        ">, ];\n"
                        "}";

        string path1 = path;
        string pathPng = path1.substr(0, path1.size() - 4);
        pathPng = pathPng + ".png";

        FILE *validar = fopen(path1.c_str(), "r");
        if (validar != NULL)
        {
            std::ofstream outfile(path1);
            outfile << codigo.c_str() << endl;
            outfile.close();
            string comando = "dot -Tpng " + path1 + " -o " + pathPng;

            system(comando.c_str());
            fclose(validar);
        }
        else
        {
            string comando1 = "mkdir -p \"" + path + "\"";
            string comando2 = "rmdir \"" + path + "\"";
            system(comando1.c_str());
            system(comando2.c_str());

            std::ofstream outfile(path1);
            outfile << codigo.c_str() << endl;
            outfile.close();
            string comando = "dot -Tpng " + path1 + " -o " + pathPng;
            system(comando.c_str());
        }
    }
    else
    {
        cout << "Error: nombre de reporte incorrecto." << endl;
    }
}
