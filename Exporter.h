#pragma once
#include "DataBase.h"

class Exporter {

public:
    virtual void Export(DataBase* DB, string path);
    virtual DataBase* Import(string path);
    virtual ~Exporter() = 0;
};

