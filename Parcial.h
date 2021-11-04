#ifndef PARCIAL_II_PARCIAL_H
#define PARCIAL_II_PARCIAL_H

#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <fstream> //Librería de flujo de entrada / salida para operar en archivos.
#include <vector> //Librería para manejar vectores
#include <algorithm> //Librería para usar la funcion sort.
#include <numeric> //Librería para usar la funcion iota.
#include <stdio.h>

using namespace std;



/*
* Funcion AbrirCSV
* De esta funcion se crea la tabla a partir del .csv
*/
vector<vector<string>> AbrirCSV(string path) {
    ifstream csv;
    csv.open(path);
    if (!csv.is_open()) {
        cout << "No se pudo abrir el archivo" << endl;
} else {
    cout << "El archivo se abrio correctamente" << endl;
    }

    int index;
    vector<vector<string>> tabla;
    string linea, palabra;
    vector<string> filas;


    while (getline(csv, linea)) { //Obtenemos los string del csv
        filas.clear();
        stringstream lineStream(linea); //Declaramos una variable de tipo stringstream, para poder extraer los strings y manipular la data
        index = 0;
        while (getline(lineStream, palabra, ',')) { //Leemos cada palabra del dataset, separada por coma
            //2 = edad, 5 = nombre de provincia, 12 = SI o NO en cui, 14 = fallecido, 20 = clasificacion, 21 = idProvincia
            if (index == 2 || index == 5 || index == 12 || index == 13 || index == 14 || index == 20 || index == 21) { //Tomamos los índices de columnas que nos interesan
                if (palabra.size() > 0) { //Si existe alguna palabra
                    palabra = palabra.substr(1, palabra.size() - 2); //La colocamos en la variable palabra sin las " "
                } else {
                    palabra = "null"; //Sino le asignamos "null", para que no quede vacía
                }
                filas.push_back(palabra); //Insertamos las palabras en el vector row que corresponde a las filas de la nueva tabla
            }
            index++;
        }
        tabla.push_back(filas);
    }
    return tabla;
}

/*
 * Funcion -estad
 * Devuelve las estadisticas de los casos
 */
void estadisticas(vector<vector<string>> *tabla) {
    int infectados = 0, fallecidos = 0 , casos_totales = (*tabla).size() - 1; //Tamanio hasta el index del last element.
    int i, j;

    for (i = 1; i < (*tabla).size(); i++) {
        if ((*tabla)[i][5] == "Confirmado")
            infectados++;
        if ((*tabla)[i][4] == "SI")
        fallecidos++;
        }


    cout << "Casos totales " << casos_totales << endl;
    cout << "Total de infectados " << infectados << endl;
    cout << "Cantidad total de fallecidos: " << fallecidos << endl;
    cout << "% infectados por muestras: " << ((float) infectados / (float) casos_totales) * 100 << "%" << endl;
    cout << "% de fallecidos por infectados: " << ((float) fallecidos / (float) infectados) * 100 << "%" << endl;

    vector<vector<string>> tabla_temporal;
    for (i = 0; i < 110; i = i + 10) {
        tabla_temporal.clear();
        infectados = 0;
        fallecidos = 0;
        for (j = 1; j < (*tabla).size(); j++) {
            if ((*tabla)[j][0] != "null") {
                if (stoi((*tabla)[j][0]) >= i && stoi((*tabla)[j][0]) < i + 10)
                    tabla_temporal.push_back((*tabla)[j]);
            }
        }
        for (j = 1; j < tabla_temporal.size(); j++) {
            if (tabla_temporal[j][5] == "Confirmado")
                infectados++;
            if (tabla_temporal[j][4] == "SI")
                fallecidos++;
        }


        cout << "Rango etario de " << i << " a " << i + 9 << " anios: " << endl;
        cout << "Total de infectados " << infectados << endl;
        cout << "Total de fallecidos " << fallecidos << endl;

    }
}

/*
 *
 */
void casosSegunProvincias(int Arg, vector<vector<string>> *tabla) {
    vector<string> provincias;
    provincias.clear();

    bool bandera;
    for (int i = 1; i < (*tabla).size(); i++) {
        if ((*tabla)[i][1] != "null" && (*tabla)[i][1] !="SIN ESPECIFICAR") {
            if (provincias.empty()) //Y si el vector esta vacio nos devuelve un true
                provincias.push_back((*tabla)[i][1]); //Le pusheamos los datos de las provincias
            else {
                bandera = false; //Sino seteamos la bandera bandera como falsa
                for (int j = 0; j < provincias.size(); j++) {//Recorremos el vector
                    if (provincias[j] ==
                        (*tabla)[i][1]) { //y comparamos los valores de la tabla original y el vector
                        bandera = true;
                    }
                }
                if (!bandera)//Si el booleano es verdadero porque coincidieron los datos
                    provincias.push_back((*tabla)[i][1]);//Agregamos los datos de las provincias
            }

        }
    }

    //Segunda parte de la funcion:
    vector<int> Casos_Totales;
    Casos_Totales.clear();
    int fallecidos = 0;
    for (int j = 0; j < provincias.size(); j++) {
        for (int i = 1; i < (*tabla).size(); i++) {//Recorro la tabla
            if ((*tabla)[i][5] == "Confirmado" && provincias[j] == (*tabla)[i][1]) {
                fallecidos++;
            }
        }
        Casos_Totales.push_back(fallecidos);
        fallecidos = 0;
    }

    std::vector<std::size_t> index(provincias.size());
    std::iota(index.begin(), index.end(), 0);
    std::sort(index.begin(), index.end(), [&](size_t a, size_t b) { return Casos_Totales[a] > Casos_Totales[b]; });

    /*
     * Funcion que lee el argumento "n" y ordena los datos
     */
    if (Arg != false) {
        for (int i = index[0] - 1; i < Arg; ++i) {
            std::cout << provincias[i] << endl;
        }
    } else {
        for (int i : index) {
            std::cout << provincias[i] << endl;
        }
    }
}

/*
 *
 */
void fallecidos_provincias(int Arg, vector<vector<string>> *tabla) {//ANDA BIEN
    vector<string> provincias;
    provincias.clear();

    bool ban;
    for (int i = 1; i < (*tabla).size(); i++) {
        if ((*tabla)[i][1] != "null" && (*tabla)[i][1] != "SIN ESPECIFICAR") {
            if (provincias.empty())
                provincias.push_back((*tabla)[i][1]);
            else {
                ban = false;
                for (int j = 0; j < provincias.size(); j++) {
                    if (provincias[j] == (*tabla)[i][1]) {
                        ban = true;
                    }
                }
                if (!ban)
                    provincias.push_back((*tabla)[i][1]);
            }
        }
    }

    vector<int> Total_Fallecidos;
    Total_Fallecidos.clear();
    int Total_muertos = 0;
    for (int j = 0; j < provincias.size(); j++) {
        for (int i = 1; i < (*tabla).size(); i++) {
            if ((*tabla)[i][4] == "SI" && provincias[j] == (*tabla)[i][1]) {
                Total_muertos++;
            }
        }
        Total_Fallecidos.push_back(Total_muertos);
        Total_muertos = 0;
    }

    /*
     * Funcion iota: Llena el rango (index.begin y index.end) con valores secuencialmente crecientes,
     * comenzando con el value y evaluando repetidamente el ++value
     * Funcion sort: sirve para hacer una orden de comparación.
     * Nos permite acceder a los datos del vector y ordenarlos de menor a mayor.
     */
    std::vector<std::size_t> index(provincias.size());
    std::iota(index.begin(), index.end(), 0);
    std::sort(index.begin(), index.end(), [&](size_t a, size_t b) { return Total_Fallecidos[a] > Total_Fallecidos[b]; });

    /*
 * Funcion que lee el argumento "n" y ordena los datos
 */
    if (Arg != false) {
        for (int i = index[0] - 1; i < Arg; ++i) {
            cout << provincias[i] << "\n";
        }
    } else {
        for (int i : index) {
            cout << provincias[i] << "\n";
        }
    }
}

/*
 * Funcion que muestra los datos de las personas en base a sus años
 */
void casos_edad(int Arg, vector<vector<string>> *tabla) {
    vector<string> edad;
    vector<string> provincias;
    provincias.clear();
    edad.clear();


    for (int i = 1; i < (*tabla).size(); i++) {
        if ((*tabla)[i][0] != "null")  {
            edad.push_back((*tabla)[i][0]);
            }
        }

    for (int i = 1; i < (*tabla).size(); i++) {
        if ((*tabla)[i][1] != "null") {
            provincias.push_back((*tabla)[i][1]);
            }
    }
    for (int i = 0; i < edad.size(); i++) {
        cout << edad[i] << " / " << provincias[i] << endl;
    }
}



/*
 * Funcion casos_cui
 * Muestra las fechas de cuidados intensivos
 */
void casos_cui(vector<vector<string>> *tabla) {
    vector<string> fecha;
    vector<string> edad;
    vector<string> provincia;
    fecha.clear();
    edad.clear();
    provincia.clear();
    bool ban;
    for (int i = 1; i < (*tabla).size(); i++) {
        if ((*tabla)[i][3] != "null") {
            if (fecha.empty()) {
                fecha.push_back((*tabla)[i][3]);
            } else {
                ban = false;
                for (int j = 0; j < fecha.size(); j++) {
                    if (fecha[j] == (*tabla)[i][3]) {
                        ban = true;
                    }
                }
                if (!ban)
                    fecha.push_back((*tabla)[i][3]);
            }
        }
    }

    for (int i = 0; i < fecha.size(); i++) {
        cout << fecha[i] << endl;
    }
}

/*
Funcion str2int
Convierte string a int para el uso de los argumentos
*/
constexpr unsigned int str2int(const char *str, int h = 0) {
    return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

#endif //PARCIAL_II_PARCIAL_H
