#include <iostream>
#include <fstream>
#include <sstream>
#include "string.h"
#include <vector>

using namespace std;

void chopCSV(string fileName, int lines)
{

    string newName = fileName.substr(0, fileName.find(".csv"));
    newName += to_string(lines) + ".csv";

    fstream fin, fout;
    fin.open("./" + fileName, ios::in);
    fout.open("./" + newName, ios::out);

    string line, word;
    for (int i = 0; i < lines; i++)
    {
        getline(fin, line);
        fout << line << "\n";
    }
}

void exploreCSV(string fileName)
{
    int colsOfInterest[] = {0, 2, 3, 12, 13, 14, 17, 20};
    int nColumns = sizeof(colsOfInterest) / sizeof(colsOfInterest[0]);

    fstream fin;
    fin.open("./" + fileName, ios::in);

    vector<string> row;
    string line, word;
    int confirmed = 0;
    int total = -1;

    while (getline(fin, line))
    {
        total++;
        row.clear();
        stringstream s(line);
        while (getline(s, word, ','))
        {
            if (word.size() > 0)
            {
                word = word.substr(1, word.size() - 2);
            }
            else
            {
                word = "NA";
            }
            row.push_back(word);
        }


        if (row[20].compare("Confirmado") == 0 || total==0)
        {
            for (int i = 0; i < nColumns; i++)
            {
                cout << row[colsOfInterest[i]] << " ";
            }
            confirmed++;
            cout << endl;
        }
    }

    cout << "Casos confirmados: " << confirmed << " de " << total << " casos registrados." << endl;
}

void exploreHeaders(string fileName)
{
    
    fstream fin;
    
    fin.open("./" + fileName, ios::in);
    
    string headers, header;
    getline(fin, headers);

    stringstream s(headers);
    while (getline(s, header, ','))
    {
        cout << header << endl;
    }
}

int main(int argc, char **argv)
{

    cout << "Cantidad de argumentos: " << argc << endl;
    for (int i = 0; i < argc; i++)
    {
        cout << "Argumento " << i << ": " << argv[i] << endl;

        if(strcmp(argv[i], "-file") == 0){
            cout << "Nombre del Archivo: " << argv[i+1] << endl;
            //exploreHeaders(argv[i+1]);
            //exploreCSV(argv[i+1]);
            //chopCSV(argv[i+1],1000);
            break;
        }
        
    }

    return 0;
}
