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

int main(int argc, char **argv) {
    string path = "D:\\User\\Desktop\\Coding\\Parcial II\\Covid19Casos.csv";
    vector<vector<string>> nueva_tabla = abrirArchivos(path);

    estad(&nueva_tabla);
}



