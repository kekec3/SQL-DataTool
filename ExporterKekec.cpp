#include "ExporterKekec.h"
#include "fstream"
#include "iostream"
#include "algorithm"
#include "regex"
#include "Exceptions.h"

void ExporterKekec::Export(DataBase *DB, string path) {
    ofstream out(path, ios::trunc);
    if (!out.is_open()) {
        /// greska
        throw FileERROR(path);
    }
    out << DB->GetName() << endl;
    for_each(DB->GetData().begin(), DB->GetData().end(), [&out](TableMK2 &table){
        out << table.getname() + " (";
        for (int i = 0; i < table.getcolumns().size(); i++){
            if (i) out << ',';
            out << table.getcolumns()[i];
        }
        out << ')';
        for_each(table.getdata().begin(), table.getdata().end(), [&out](vector<string> &row){
            out << " (";
            for (int i = 0; i < row.size(); i++){
                if (i) out << ',';
                out << row[i];
            }
            out << ')';
        });
        out << endl;
    });
    out.close();
}

DataBase *ExporterKekec::Import(std::string path) {
    ifstream in(path + ".txt");
    if (!in.is_open()) {
        /// greska
        throw FileERROR(path);
    }
    string line;
    if (!getline(in, line)) {
        //// greskao u formatu
        throw FileERROR("Problem unutar fajla!");
    }
    DataBase *DB = new DataBase(line);
    regex r0("[\\(\\)\\w,0-9]+");
    smatch m;
    string name;
    while (getline(in, line)) {
        for(sregex_iterator i = sregex_iterator(line.begin(), line.end(), r0); i != sregex_iterator(); ++i) {
            m = *i;
            if (i == sregex_iterator(line.begin(), line.end(), r0)) { /// Naziv tabele
                name = m[0];
            } else if (i == ++sregex_iterator(line.begin(), line.end(), r0)) { /// Kolone
                DB->CreateTable(name, m[0]);
            } else {    /// Podaci
                string tmp = m[0];
                DB->GetTabel(name)->insert(TableMK2::columnmaker(m[0]));
            }
        }
    }
    in.close();
    return DB;
}