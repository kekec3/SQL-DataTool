#include "Exporter.h"
#include "iostream"

void Exporter::Export(DataBase *DB, string path) {
    cout << "Trazeni export format nije podrzan!" << endl;
}

DataBase *Exporter::Import(std::string path) {
    cout << "Trazeni impot format nije podrzan!" << endl;
    return nullptr;
}

Exporter::~Exporter(){

}