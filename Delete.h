#pragma once
#include "Statment.h"
#include "Condition.h"

class Delete : public Statment{

private:
    Condition cond;

public:
    Delete(TableMK2* pt, Slicer *parse);
    void execute() override;
};

