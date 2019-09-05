#include "rep.h"
#include <fstream>


extern Mount montaje;

Rep::Rep()
{
    //Rep::montaje = montaje;
}

void Rep::crearReporte(string path, string name, string id)
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
                                        "<TR><TD>" +
                                        name + " (EXTENDIDA)</TD></TR>\n"
                                               "<TR><TD><TABLE ALIGN=\"LEFT\">\n"
                                               "<TR>\n"
                                               "<TD>EBR</TD>\n"
                                               "<TD>" +
                                        porcentajeString + "%</TD>\n"
                                                           "</TR></TABLE></TD></TR>\n"
                                                           "</TABLE></TD>\n";
                }
            }
        }

        int libre = 100 - acumulado;
        string libreString = to_string(libre);
        if (acumulado < 100)
        {
            codigoParticiones = codigoParticiones +
                                "<TD>    <TABLE BORDER=\"0\">\n"
                                "<TR><TD> Libre "
                                "</TD></TR>\n"
                                "<TR><TD>" +
                                libreString + "%</TD></TR>\n"
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