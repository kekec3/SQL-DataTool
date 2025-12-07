#pragma once
#include "Statment.h"
#include "string"

class Update : public Statment{
private:
    vector<vector<string>> changes;

public:
    Update(TableMK2* pt, Slicer *parse);
    void execute() override;
};

