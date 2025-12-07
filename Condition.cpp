#include "Condition.h"
#include "regex"
#include "iostream"
#include "stdlib.h"
#include "Exceptions.h"

Condition::Condition(std::string conditions) {
    if (conditions.empty()) {
        isvalid = false;
        return;
    }
    regex r0("^\\s*([^AND]+)\\s*(AND)?(.*)"); /// Hvata jedan uslov
    regex r1("^(\\w+)\\s*([<>=])\\s*([^\\s]+)\\s*"); /// Hvata elemente jednog uslova
    smatch m, m2;
    vector<string> vec;
    vec.resize(3);
    string tmps;
    while (regex_match(conditions, m, r0)) {
        tmps = m[1];
        if (!regex_match(tmps, m2, r1)) {
            /// Lose napisan uslov
            throw ConditionERROR(tmps);
        }
        vec[0] = m2[1];
        vec[1] = m2[2];
        vec[2] = m2[3];
        conarray.push_back(vec);
        conditions = m[3];
    }
}

bool Condition::operator()(vector<std::string> row, vector<std::string> columns) {
    if (!isvalid) return true;
    regex r0("^'([^']+)'$"); /// Hvata rec pod navodnicima
    regex r1("^-?[0-9]+\\.?[0-9]*$");  /// Hvata broj
    smatch m;
    bool result = true;
    for_each(conarray.begin(), conarray.end(), [&row, &columns, &m, &r0, &r1, &result](vector<string> con){
        if (!result) return;
        auto tmp = find(columns.begin(), columns.end(), con[0]);
        if (tmp == columns.end()) {
            /// Nepostojeca kolona
            throw ColunERROR(con[0]);
        }
        if (regex_match(con[2], m, r1)) {
            /// Radi se o borju
            float f1 = stof(row[tmp - columns.begin()]);
            float f2 = stof(con[2]);
            switch (con[1][0]) {
                case '=':
                    result = f1 == f2; break;
                case '<':
                    result = f1 < f2; break;
                case '>':
                    result = f1 > f2; break;
            }
        } else if (regex_match(con[2], m, r0)) {
            /// Radi se o reci
            switch (con[1][0]) {
                case '=':
                    result = row[tmp - columns.begin()] == m[1]; break;
                case '<':
                    result = row[tmp - columns.begin()] < m[1]; break;
                case '>':
                    result = row[tmp - columns.begin()] > m[1]; break;
            }
        } else {
            /// Pogresno naveden parametar
            throw ParametarERROR(con[2]);
        }
    });
    return result;
}