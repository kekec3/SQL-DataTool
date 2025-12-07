#pragma once

#include "TableMK2.h"

class DataBase {

private:
    string name;
    vector<TableMK2> tables;


public:
    DataBase(string name);
    string GetName();
    vector<TableMK2>& GetData();
    void CreateTable(string name, string columnsinfo);
    void DropTable(string name);
    TableMK2* GetTabel(string name);
    void ShowTables();
};

