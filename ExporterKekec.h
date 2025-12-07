#pragma once
#include "Exporter.h"

class ExporterKekec : public Exporter {

public:
    void Export(DataBase* DB, string path) override;
    DataBase* Import(string path) override;
    ~ExporterKekec() override = default;
};

