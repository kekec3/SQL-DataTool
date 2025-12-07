#pragma once
#include "Statment.h"

class Insert : public Statment{
private:
    vector<string> columns;
    vector<int> index;
    string values;


public:
    Insert(TableMK2* pt, Slicer *parse);
    void execute() override;
};

