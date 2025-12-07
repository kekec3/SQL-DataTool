#include "Exporter.h"

class ExporterSQL : public Exporter {

public:
    void Export(DataBase* DB, string path);
    /// nije podrzan uvoz SQL fajla
    ~ExporterSQL() = default;
};
