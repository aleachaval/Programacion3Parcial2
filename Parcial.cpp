//
// Created by User on 31/10/2021.
//

#include "Parcial.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

/*
Funcion main
Funcion principal que se encarga de cargar los argumentos y comandar el programa
*/
int main(int argc, char **argv) {
    string path = "D:\\User\\Desktop\\Coding\\Parcial II\\Covid19Casos1000.csv";
    vector<vector<string>> nueva_tabla = AbrirCSV(path);
    int edad=1;
    for (int i = 1; i < argc; i++) {
        switch (str2int(argv[i])){
            case str2int("-estad"):
                estadisticas(&nueva_tabla);
                break;
                case str2int("-p_casos"):
                    casosSegunProvincias(atoi(argv[i + 1]), &nueva_tabla);
                    break;
                    case str2int("-p_muertes"):
                        fallecidos_provincias(atoi(argv[i + 1]), &nueva_tabla);
                        break;
                        case str2int ("-casos_edad"):
                            casos_edad(atoi(argv[i + 1]), &nueva_tabla, edad);
                            break;
                        case str2int ("-casos_cui"):
                            casos_cui(&nueva_tabla);
                            break;
                            default:
                                break;
        }
    }

    return 0;
}



