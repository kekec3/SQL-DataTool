#pragma once
#include "Statment.h"
#include "Condition.h"


class Select : public Statment {

private:
    vector<int> columnindex;
    Condition con;

public:
    Select(TableMK2* pt, Slicer *parse);
    void execute() override;

};

