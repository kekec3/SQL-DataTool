#pragma once
#include "vector"
#include "string"

using namespace std;

class Condition {

private:
    vector<vector<string>> conarray;
    bool isvalid = true;

public:
    Condition(string conditions);
    bool operator()(vector<string> row, vector<string> columns);

};
