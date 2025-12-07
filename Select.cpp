#include "Select.h"
#include "algorithm"
#include "iostream"
#include "iomanip"
#include "Exceptions.h"

Select::Select(TableMK2 *pt, Slicer *parse) : Statment(pt, parse), con(parse->condition){
    vector<string> requestedcolumns = (parse->selector == "*" ? table->getcolumns() : TableMK2::columnmaker("("+parse->selector+")"));
    for_each(requestedcolumns.begin(), requestedcolumns.end(), [pt, this](string &column)->void{ /// Provera pozicije i postojanja kolona
        auto tmp = find(pt->getcolumns().begin(), pt->getcolumns().end(), column);
        if (tmp == pt->getcolumns().end()) {
            throw ColunERROR(column);
        }
        columnindex.push_back(tmp - pt->getcolumns().begin());
    });
}

void Select::execute() {
    const int width = 20;
    const char separator = ' ';
    for_each(columnindex.begin(), columnindex.end(), [this](int index){
        cout << left << setw(width) << setfill(separator) << table->getcolumns()[index];
    });
    cout << endl;
    for_each(table->getdata().begin(), table->getdata().end(), [this](vector<string> &row){
        if (con(row, table->getcolumns()))
            for_each(columnindex.begin(), columnindex.end(), [row](int index){
                cout << left << setw(width) << setfill(separator) << row[index];
            });
        cout << endl;
    });
    cout << endl;
}