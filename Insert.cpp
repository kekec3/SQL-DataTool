#include "Insert.h"
#include "regex"
#include "iostream"
#include "Exceptions.h"

Insert::Insert(TableMK2 *pt, Slicer *parse) : Statment(pt, parse){
    regex r0("^(.*)\\s+VALUES\\s+(.*)"); /// Hvata kolone i listu vrednosti
    smatch m;
    if (!regex_match(parse->datarest, m, r0)) {
        /// Greska parametri
        throw ParametarERROR(parse->datarest);
    }
    values = m[2];
    columns = TableMK2::columnmaker(m[1]);
    if (columns.size() != pt->getcolumns().size()){
        /// Greska kolone
        throw ColunERROR(m[1]);
    }
    /// Provera rasporedjenosti i postojanja kollona
    for_each(columns.begin(), columns.end(), [pt, this](string &column)->void{
        auto tmp = find(pt->getcolumns().begin(), pt->getcolumns().end(), column);
        if (tmp == pt->getcolumns().end()) {
            throw ColunERROR(column);
        }
        index.push_back(tmp - pt->getcolumns().begin());
    });
}

void Insert::execute() {
    regex r0("^\\s*\\(([^)]+)\\)\\s*,?(.*)"); /// Hvata jednu listu vrednosti
    regex r1("^\\s*'([^']+)'\\s*,?(.*)"); /// Hvata jednu vrednost
    regex r3("^\\s*$"); /// Proverava ostatak
    vector<string> tmp;
    tmp.resize(columns.size());
    smatch m, m2;
    string tmps;
    while (regex_match(values, m, r0)) {
        tmps = m[1];
        for (int i = 0; i < columns.size(); i++) {
            if (!regex_match(tmps, m2, r1)) {
                /// Greska vrednost
                throw ParametarERROR(tmps);
            }
            tmp[index[i]] = m2[1];
            tmps = m2[2];
        }
        table->insert(tmp);
        values = m[2];
    }
    if (!regex_match(values, m, r3)) {
        /// Greska vrednosti
        throw ParametarERROR(values);
    }
}