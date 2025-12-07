#include "Slicer.h"
#include "regex"
#include "Exceptions.h"

command decoder(string s) {
    if (s == "CREATE TABLE") return CREATE; else if (s == "SELECT") return SELECT; else if (s == "INSERT INTO") return INSERT;
    else if (s == "DROP TABLE") return DROP; else if (s == "UPDATE") return UPDATE; else if (s == "DELETE FROM") return DELETE;
    else if (s == "SHOW TABLES") return SHOW;
    else return FAULT;
}


Slicer::Slicer(std::string s) {
    string working = s;
    smatch m;
    regex r1("^(CREATE TABLE"
            "|SELECT"
            "|INSERT INTO"
            "|DROP TABLE"
            "|UPDATE"
            "|DELETE FROM"
            "|SHOW TABLES)\\s*(.*);?", std::regex_constants::icase);
    // Hvatanje Naredbe
    if (regex_match(working, m, r1)) {
        string str = m[1];
        transform(str.begin(), str.end(), str.begin(), ::toupper);
        comand = decoder(str);
        working = m[2];
    }
    else {
        //Losa naredba
        throw StatmentERROR(s.substr(0));
    }
    // Hvatanje selektora ukoliko ga ima
    if (comand == SELECT){
        regex r2("^(.*)(\\s+FROM\\s+)(.*)", std::regex_constants::icase);
        regex_match(working, m, r2);
        selector = m[1];
        working = m[3];

    }
    // Hvatanje naziva tabele
    regex r2("^([a-zA-Z]+)(\\s*)(.*)");
    regex_match(working, m, r2);
    table = m[1];
    working = m[3];

    // Hvatanje where uslova ukoliko postoji
    regex r3("(.*\\s*)(WHERE\\s+)(.*)", std::regex_constants::icase);
    if(regex_match(working, m, r3)) {
        condition = m[3];
        working = m[1];
    }
    datarest = working;
}