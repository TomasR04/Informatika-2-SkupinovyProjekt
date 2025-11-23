#include "Shop.h"
#include <iostream>
#include <algorithm>

using namespace std;

// Nastavení cen
vector<Zbozi> Shop::nabidka = {
    {"Pivo", 15},
    {"Mec", 150},
    {"Lektvar", 50},
    {"Chleb", 10}
};

int Shop::dejCenu(string nazev) {
    for (const auto& z : nabidka) {
        if (z.nazev == nazev) return z.cena / 2; // Výkup za polovinu
    }
    return 1;
}

void Shop::start(Player& hrac) {
    bool nakupuje = true;
    string vstup;

    while (nakupuje) {
        system("cls"); // Vyčistí obrazovku
        cout << "--- HOSPODA U KRIGLU ---" << endl;
        cout << "Zlato: " << hrac.getZlato() << endl;
        cout << "Batoh: " << hrac.toString() << endl;
        cout << "------------------------" << endl;
        
        // Výpis zboží
        for (size_t i = 0; i < nabidka.size(); i++) {
            cout << i + 1 << ". " << nabidka[i].nazev << " (" << nabidka[i].cena << " zl)" << endl;
        }

        cout << "\nNAPIS: cislo (nakup), 'p nazev' (prodej), 'exit' (odchod)" << endl;
        cout << "> ";
        cin >> vstup;

        if (vstup == "exit") {
            nakupuje = false;
        }
        else if (vstup == "p") {
            string co; cin >> co;
            if (hrac.odeberInventar(co)) {
                int cena = dejCenu(co);
                hrac.pridejZlato(cena);
                cout << "Prodal jsi " << co << " za " << cena << endl;
            } else {
                cout << "To nemas!" << endl;
            }
            system("pause");
        }
        else {
            try {
                int id = stoi(vstup) - 1;
                if (id >= 0 && id < nabidka.size()) {
                    if (hrac.odeberZlato(nabidka[id].cena)) {
                        hrac.pridejInventar(nabidka[id].nazev);
                        cout << "Koupeno!" << endl;
                    } else cout << "Nemas penize!" << endl;
                }
            } catch (...) {}
            system("pause");
        }
    }
}
