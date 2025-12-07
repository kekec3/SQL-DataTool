#include "Delete.h"
#include "algorithm"

Delete::Delete(TableMK2 *pt, Slicer *parse) : Statment(pt, parse), cond(parse->condition){}

void Delete::execute() {
    table->getdata().erase(
            remove_if(table->getdata().begin(),
                           table->getdata().end(),
                           [this](vector<string> &row){return cond(row, table->getcolumns());}),
           table->getdata().end());
}

