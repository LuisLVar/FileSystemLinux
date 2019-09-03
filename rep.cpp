#include "rep.h"
#include <fstream>
#include "mount.h"
#include "interprete.h"

Rep::Rep()
{
}

void Rep::crearReporte(string path, string name, string id)
{
    //Mount montaje1 = Interprete::montaje;
   // montaje.leerMontajes();


    if (name == "mbr")
    {
    }
    else if (name == "disk")
    {
    }
    else
    {
        cout << "Error: nombre de reporte incorrecto." << endl;
    }

    string codigo = "digraph G { " 
                    " start_here [label=\"it's me " 
                    " (start here)\"];" 
                    " start_here -> 2017; " 
                    " bloglife1 [label=\"create more blog\"];" 
                    " bloglife2 [label=\"make more money\"];" 
                    " bloglife3 [label=\"become rich\"];" 
                    " life_goal1[label=\"married with someone\"];" 
                    " life_goal2[label=\"have a baby\"];" 
                    " life_goal3[label=\"happy life\"];" 
                    " 2017 -> bloglife1 -> bloglife2 -> bloglife3;" 
                    " 2017 -> life_goal1 -> life_goal2;" 
                    " 0node [shape=box,style=filled,color=\".7 .3 1.0\"];" 
                    " life_goal2 -> life_goal3" 
                    " }";


    string path1 = path;
    string pathPng = path1.substr(0, path1.size() - 4);
    pathPng = pathPng + ".png";

   /* std::ofstream outfile(path1);

    outfile << codigo.c_str() << endl;

    outfile.close();

    string comando = "dot -Tpng "+path1+" -o "+pathPng;

    system(comando.c_str());*/
}
