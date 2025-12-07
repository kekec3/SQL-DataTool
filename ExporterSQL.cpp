#include "fstream"
#include "iostream"
#include "algorithm"
#include "ExporterSQL.h"
#include "Exceptions.h"

void ExporterSQL::Export(DataBase *DB, std::string path) {
    ofstream out(path + ".sql", ios::trunc);
    if (!out.is_open()) {
        /// Greska
        throw FileERROR(path);
    }
    /// Nije potrebno
    //out << "CREATE DATABASE " + DB->GetName() + ";" << endl;

    for_each(DB->GetData().begin(), DB->GetData().end(), [&out](TableMK2 &table){
        string builder = "(";
        string values = "";
        for (int i = 0; i < table.getcolumns().size(); i++){
            if (i) builder += ',';
            builder += table.getcolumns()[i] + ' ';
        }
        builder += ")";
        /// Upit
        out << "CREATE TABLE " + table.getname() + " " + builder + ";\n";
        for_each(table.getdata().begin(), table.getdata().end(), [&out, &table, &values](vector<string> &row){
            if (row != *table.getdata().begin()) values += ", ";
            values += '(';
            for (int i = 0; i < row.size(); i++){
                if (i)  values += ',';
                values += "'" + row[i] + "'";
            }
            values += ')';
        });
        /// Upit samo ako postoje vrednosti
        if (!values.empty()) out << "INSERT INTO " + table.getname() + " " + builder + " VALUES " + values + ";\n";
    });
    out.close();
}