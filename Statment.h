#pragma once
#include "TableMK2.h"
#include "Slicer.h"

class Statment {

protected:
    TableMK2* table;
    Slicer *parse;

public:
    virtual void execute() = 0;
    Statment(TableMK2* pt, Slicer *parse);
};
