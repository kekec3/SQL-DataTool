#pragma once

#include <stdio.h>
#include "string"

using namespace std;

enum command {
    FAULT,
    CREATE, DROP, SELECT, INSERT, UPDATE, DELETE, SHOW
};

class Slicer {

public:
    command comand;
    string table;
    string selector;
    string condition;
    string datarest;

    Slicer(string s);
};