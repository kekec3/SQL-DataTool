#include "TableMK2.h"
#include "regex"
#include "iostream"
#include "Exceptions.h"

TableMK2::TableMK2(std::string name, vector<std::string> columns) : name(name), columns(columns){
    width = columns.size();
}

string TableMK2::getname() const {
    return name;
}

vector<string> &TableMK2::getcolumns() {
    return columns;
}

vector<vector<string>> &TableMK2::getdata() {
    return data;
}

void TableMK2::insert(vector<string> value) {
    data.push_back(value);
}

void TableMK2::erase(int x) {
    auto pos = data.begin();
    while (x) {
        pos++;
        x--;
    }
    data.erase(pos);
}

vector<string> TableMK2::columnmaker(string columnsinfo) {
    ///Formiranje kolona tabele
    regex r1("^\\(\\s*([a-zA-Z0-9]+)\\s*(.*)\\)"); /// Hvata listu parametara u zagradama i prvi parametar
    smatch m;
    vector<string> columns;
    string othercolumns;
    if (regex_match(columnsinfo, m, r1)) {
        columns.push_back(m[1]);
        othercolumns = m[2];
        regex r2("^,\\s*([a-zA-Z0-9]+)(.*)"); /// Hvata naredni parametar odvojen zarezom
        while (regex_match(othercolumns, m, r2)) {
            columns.push_back(m[1]);
            othercolumns = m[2];
        }
        regex r3("^\\s*");
        if (!regex_match(othercolumns, m, r3)){
            ///Postoji visak ili neuparljivi parametar
            throw ParametarERROR(othercolumns);
        }
    } else {
        ///Nije odgovarajuci format
        throw ParametarERROR(columnsinfo);
    }
    return columns;
}
