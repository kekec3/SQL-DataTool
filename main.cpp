#include <iostream>
#include "Select.h"
#include "Slicer.h"
#include "DataBase.h"
#include "Insert.h"
#include "algorithm"
#include "Delete.h"
#include "Update.h"
#include "string"
#include "ExporterKekec.h"
#include "ExporterSQL.h"
#include "Exceptions.h"


int main() {
    int choice;
    DataBase* DB;
    bool saved;
    string name;
    Slicer *reptosecko;
    ExporterKekec keksport;
    Exporter *eksport;
    Statment *statment;
    TableMK2 *currenttable;


    /// Inicijalizacija
    while (true) {
        try {
            cout << "Dobordošli u mali simulator sql baza podataka." << endl << "Zelite li:\n"
                                                                                "1. Da kreirate novu bazu podataka.\n"
                                                                                "2. Učitate postojeću bazu podataka.\n"
                                                                                "(pritisniti zeljeni taster):\n";
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(256, '\n');
                cout << "Molim unesite broj!" << endl;
                continue;
            }
            cin.ignore(1);
            switch (choice) {
                case 1:
                    cout << "Molim unesite ime baze:" << endl;
                    getline(cin, name);
                    DB = new DataBase(name);
                    saved = false;
                    break;
                case 2:
                    cout << "Molim unesite apsolutnu putanju fajla:" << endl;
                    cin >> name;
                    DB = keksport.Import(name);
                    saved = true;
                    cout << "Baza je uspešno učitana." << endl;
                    break;
                default:
                    cout << "Molim unesite validu komandu!\n" << endl;
            }
            if (choice == 1 || choice == 2) break;
        } catch (const NameERROR &e) {
            if (e.noexists) cout << "Tražena tabele ne postoji: " << e.what() << endl;
            else if (e.redundant) cout << "Zadata tabela već postoji: " << e.what() << endl;
            else cout << "Nedozvoljeno imenovanje: " << e.what() << endl <<  "(samo slova su dozvoljena)" << endl;
        } catch (const exception &e) {
            cout << e.what() << endl;
        }
    }
    /// Glavna interakcija sa korisnikom
    while (true) {
        try {
            cout << "Molim odaberite zaljenu opciju:\n"
                    "1. Izvrši upit.\n"
                    "2. Eksportuj bazu.\n"
                    "3. Kraj rada.\n"
                    "(pritisnite zeljeni taster):\n";
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(256, '\n');
                cout << "Molim unesite broj!" << endl;
                continue;
            }
            switch (choice) {
                case 1:
                    cout << "Unesite upit u jedno mredu:\n";
                    cin.ignore(1);
                    getline(cin, name);
                    reptosecko = new Slicer(name);
                    switch (reptosecko->comand) {
                        case CREATE:
                            DB->CreateTable(reptosecko->table, reptosecko->datarest);
                            saved = false;
                            break;
                        case DROP:
                            DB->DropTable(reptosecko->table);
                            saved = false;
                            break;
                        case SHOW:
                            DB->ShowTables();
                            break;
                        default:
                            currenttable = DB->GetTabel(reptosecko->table);

                    }
                    switch (reptosecko->comand) {
                        case SELECT:
                            statment = new Select(currenttable, reptosecko);
                            break;
                        case INSERT:
                            statment = new Insert(currenttable, reptosecko);
                            saved = false;
                            break;
                        case UPDATE:
                            statment = new Update(currenttable, reptosecko);
                            saved = false;
                            break;
                        case DELETE:
                            statment = new Delete(currenttable, reptosecko);
                            saved = false;
                            break;
                    }
                    if (!(reptosecko->comand == CREATE || reptosecko->comand == DROP || reptosecko->comand == SHOW)) {
                        statment->execute();
                        delete statment;
                    }
                    break;
                case 3:
                    if (!saved) {
                        while (true) {
                            cout << "Baza nije sacuvana!!!\nZelite li da je eksportujete:\n"
                                    "1. Da\n2. Ne\n(pritisniti zeljeni taster):\n";
                            if (!(cin >> choice)) {
                                cin.clear();
                                cin.ignore(256, '\n');
                                cout << "Molim unesite broj!" << endl;
                                continue;
                            }
                            switch (choice) {
                                case 1:
                                    break;
                                case 2:
                                    delete DB;
                                    return 0;
                                default:
                                    cout << "Molim unesite validu komandu!\n" << endl;
                            }
                            if (choice == 1) break;
                        }
                    } else {
                        delete DB;
                        return 0;
                    }
                case 2:
                    while (true) {
                        cout << "U kom formatu zelite da sacuvate bazu:\n"
                                "1. Interesantan format.\n"
                                "2. SQL format.\n"
                                "(pritisniti zeljeni taster):\n";
                        cin.ignore(1);
                        cin >> choice;
                        switch (choice) {
                            case 1:
                                eksport = &keksport;
                                break;
                            case 2:
                                eksport = new ExporterSQL();
                                break;
                            default:
                                cout << "Molim unesite validu komandu!\n" << endl;
                        }
                        if (choice == 1 || choice == 2) break;
                    }
                    cout << "Molim unesite apsolutnu putanju fajla za izvoz:" << endl;
                    cin >> name;
                    eksport->Export(DB, name);
                    cout << "Baza je uspešno eksportovana." << endl;
                    saved = true;
                    break;
                default:
                    cout << "Molim unesite validu komandu!\n" << endl;
            }
        } catch (const NameERROR &e) {
          if (e.noexists) cout << "Tražena tabele ne postoji: " << e.what() << endl;
          else if (e.redundant) cout << "Zadata tabela već postoji: " << e.what() << endl;
          else cout << "Nedozvoljeno imenovanje: " << e.what() << endl <<  "(samo slova su dozvoljena)" << endl;
        } catch (const exception &e) {
            cout << e.what() << endl;
        }
    }
}

// D:\Desktop\Baza-keckec