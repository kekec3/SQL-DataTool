#include "Update.h"
#include "regex"
#include "Condition.h"
#include "iostream"
#include "Exceptions.h"

Update::Update(TableMK2 *pt, Slicer *parse) : Statment(pt, parse){
    string tmps = parse->datarest;
    tmps = tmps.substr(3);
    regex r0("^,?\\s*(\\w+)\\s*=\\s*('(\\w+)'|[-\\d\\.]+)\\s*(.*)"); /// Hvata trazenu izmenu
    smatch m;
    vector<string> vec;
    vec.resize(2);
    while (regex_match(tmps, m, r0)) {
        vec[0] = m[1];
        vec[1] = m[3];
        if (m[3] == "") vec[1] = m[2];
        changes.push_back(vec);
        tmps = m[4];
    }
}

void Update::execute() {
    Condition cond(parse->condition);
    for_each(table->getdata().begin(), table->getdata().end(), [&cond, this](vector<string> &row){
       if (cond(row, table->getcolumns())) {
           for_each(changes.begin(), changes.end(), [&row, this](vector<string> change){
               auto it = find(table->getcolumns().begin(), table->getcolumns().end(), change[0]);
               if (it == table->getcolumns().end()) {
                   /// Losa kolona
                   throw ColunERROR(change[0]);
               }
               row[it - table->getcolumns().begin()] = change[1];
           });
       }
    });
}