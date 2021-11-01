#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;


vector<vector<string>> abrirArchivos(string path) {
    ifstream csv;//Crea variable de tipo ifstream
    csv.open(path);//Abre el archivo en el directorio indicado por path
    if ( ! csv.is_open() ) {
        cout << " Falla en lectura del archivo. " << endl;
    }
    else {
        cout << " Lectura del archivo correcta. " << endl;
    }

    vector<vector<string>> nueva_tabla;
    vector<string> filas;
    string linea, word;
    int index;

    while(getline(csv, linea)){ //Leemos cada string del csv
        filas.clear();
        stringstream lineStream(linea); //Declaramos una variable de tipo stringstream, para poder extraer los strings (manipular la data)
        index = 0;
        while(getline(lineStream, word, ',')){ //Leemos cada palabra del dataset, separada por coma
            //2 = edad, 5 = nombre de provincia, 12 = SI o NO en cui, 14 = fallecido, 20 = clasificacion, 21 = idProvincia
            if(index == 2 || index == 5 || index == 12 || index == 13 || index == 14 || index == 20 || index == 21){ //Tomamos los índices de columnas que nos interesan
                if(word.size() > 0){ //Si existe alguna palabra
                    word = word.substr(1, word.size()-2 ); //La colocamos en la variable word sin las " "
                }else{
                    word = "null"; //Sino le asignamos "null", para que no quede vacía
                }
                filas.push_back(word); //Insertamos las palabras en el vector row que corresponde a las filas de la nueva tabla
            }
            index++;
        }
        nueva_tabla.push_back(filas);
    }
    return nueva_tabla;
}

void estad(vector<vector<string>> *nueva_tabla) {
    int contagiados = 0;
    int muertos = 0;
    int casos_totales = (*nueva_tabla).size()-1; //Tamanio hasta el index del last element.
    int i, j;

    for(i=1; i<(*nueva_tabla).size(); i++){ //Recorremos la nueva tabla segun su tamaño
        if((*nueva_tabla)[i][5] == "Confirmado")  //En la columna 5, comparamos si el valor de la fila es "Confirmado"
            contagiados++; //Sumo al contador de infectados
            if ((*nueva_tabla)[i][4] == "SI")//En la columna 4, comparamos si el valor de la fila es "SI"
                muertos++;//Sumo al contador fallecidos
    }

    cout << "Cantidad total de muestras: " << casos_totales << endl;
    cout << "Cantidad total de infectados: " << contagiados << endl;
    cout << "Cantidad total de fallecidos: " << muertos << endl;
    cout << "% infectados por muestras: " << ((float)contagiados/(float)casos_totales)*100 << "%" << endl;
    cout << "% de fallecidos por infectados: " << ((float)muertos/(float)contagiados)*100 << "%" << endl;

    vector<vector<string>> tmpnueva_tabla; //Genero una tabla temporal
    for(i=0; i<110; i=i+10){ //recorro por cada grupo etario, de 0 a 19 años
        tmpnueva_tabla.clear();
        contagiados = 0;
        muertos = 0;
        for(j=1; j<(*nueva_tabla).size(); j++){ //recorro toda la tabla original
            if((*nueva_tabla)[j][0] != "null"){ //si el valor encontrado no es nulo
                if(stoi((*nueva_tabla)[j][0]) >= i && stoi((*nueva_tabla)[j][0]) < i+10) //y cumple con las condiciones de que el valor este dentro del grupo etario
                    tmpnueva_tabla.push_back((*nueva_tabla)[j]); //agrego a la tabla temporal el valor en la tabla original
            }
        }
        for(j=1; j<tmpnueva_tabla.size(); j++){ //recorremos la tabla temporal segun su tamaño
            if(tmpnueva_tabla[j][5] == "Confirmado") //en la columna 5, comparamos si el valor de la fila es "Confirmado"
                contagiados++; //sumo al contador infectado
                if (tmpnueva_tabla[j][4] == "SI") //en la columna 4, comparamos si el valor de la fila es "SI"
                    muertos++; //sumo al contador fallecido
        }
        cout << endl;
        cout << "Rango de edades: " << i << " a " << i+9 << " anios: " << endl;
        cout << "Cantidad de infectados: " << contagiados << endl;
        cout << "Cantidad de muertes:  " << muertos << endl;
    }
}







#ifndef PARCIAL_II_PARCIAL_H
#define PARCIAL_II_PARCIAL_H

#endif //PARCIAL_II_PARCIAL_H
