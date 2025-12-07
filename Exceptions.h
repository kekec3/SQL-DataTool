#pragma once
#include "exception"
#include "string"

using namespace std;

class ConditionERROR : public exception {
private:
    string massage;
public:
    ConditionERROR(string s) {massage = "Loše navedeni uslovi: " + s;};
    const char * what() const noexcept override {return massage.c_str();}
};

class ColunERROR : public exception {
private:
    string massage;
public:
    ColunERROR(string s) {massage = "Loše navedena kolona: " + s;};
    const char * what() const noexcept override {return massage.c_str();}
};

class ParametarERROR : public exception {
private:
    string massage;
public:
    ParametarERROR(string s) {massage = "Loše navedena parametar: " + s;};
    const char * what() const noexcept override {return massage.c_str();}
};

class NameERROR : public exception {
private:
    string massage;

public:
    bool noexists;
    bool redundant;
    NameERROR(string s, bool e, bool r) : massage(s), noexists(e), redundant(r) {};
    const char * what() const noexcept override {return massage.c_str();}
};

class FileERROR : public exception {
private:
    string massage;
public:
    FileERROR(string s) : massage(s) {};
    const char * what() const noexcept override {return massage.c_str();}
};

class StatmentERROR : public exception {
private:
    string massage;
public:
    StatmentERROR(string s) {massage = "Nije poznata zahtevana naredba: " + s;};
    const char * what() const noexcept override {return massage.c_str();}
};
