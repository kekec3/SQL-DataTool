#include "DataBase.h"
#include "regex"
#include "iostream"
#include "Slicer.h"
#include "Select.h"
#include "Exceptions.h"

DataBase::DataBase(std::string name) {
    regex r0("^[\\w0-9]+$");
    smatch m;
    if (!regex_match(name, m, r0)) {
        /// Lose ime baze
        throw NameERROR(name, false, false);
    }
    this->name = name;
}

string DataBase::GetName() {return name;}

vector<TableMK2>& DataBase::GetData() {return tables;}

void DataBase::CreateTable(std::string name, std::string columnsinfo) {
    ///Provera ispravnosti naziva tabele
    regex r0("^[a-zA-Z]+$");
    smatch m;
    if (!regex_match(name, m, r0)){
        ///Greska u imenu
        throw NameERROR(name, false, false);
    }
    if (!tables.empty() && tables.end() != find_if(tables.begin(), tables.end(), [name](TableMK2 t)->bool {return name == t.getname();})) {
        ///Greska vec postoji
        throw NameERROR(name, false, true);
    }
    ///Dodavanje nove tabele
    tables.push_back(TableMK2(name, TableMK2::columnmaker(columnsinfo)));
}

void DataBase::DropTable(std::string name) {
    auto tmp = find_if(tables.begin(), tables.end(), [name](TableMK2 t)->bool {return name == t.getname();});
    if (tmp == tables.end()) {
        /// Nepostojeca tabela
        throw NameERROR(name, true, false);
    }
    tables.erase(tmp);

}

TableMK2 *DataBase::GetTabel(std::string name) {
    auto tmp = find_if(tables.begin(), tables.end(), [name](TableMK2 t)->bool {return name == t.getname();});
    if (tmp == tables.end()) {
        /// Nepostojeca tabela
        throw NameERROR(name, true, false);
    }
    return &(*tmp);
}

void DataBase::ShowTables() {
    for_each(tables.begin(), tables.end(), [](TableMK2 &table){
        Slicer *tmp = new Slicer("SELECT * FROM " + table.getname());
        Select(&table, tmp).execute();
        delete tmp;
        cout << endl;
    });
}