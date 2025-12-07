#pragma once

#include "string"
#include "vector"
#include "array"

using namespace std;

class TableMK2{
private:
    int width;
    string name;
    vector<vector<string>> data; // ne idealan pristup, bilo bi bolje da je fiksna sirina tabele ali upotreba array pravi VELIKE probleme
    vector<string> columns;

public:
    TableMK2(string name, vector<string> columns);
    string getname() const;
    vector<string>& getcolumns();
    vector<vector<string>> &getdata();
    void insert(vector<string> value);
    void erase(int x);

    static vector<string> columnmaker(string columnsinfo);
};

