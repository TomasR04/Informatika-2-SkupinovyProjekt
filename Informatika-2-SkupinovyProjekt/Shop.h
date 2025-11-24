#pragma once
#include "Player.h"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

struct Zbozi {
    std::string nazev;
    int cena;
};

class Shop {
public:
    static void start(Player& hrac);

private:
    // helper that returns a reference to the shop inventory stored in a function-local static
    static std::vector<Zbozi>& getNabidka();
    static int dejCenu(const std::string& nazev);
};

// Implementation in header (inline) so the shop is usable without relying on a separate TU.
inline std::vector<Zbozi>& Shop::getNabidka() { 
    static std::vector<Zbozi> nabidka = {
        {"Pivo", 15},
        {"Mec", 150},
        {"Lektvar", 50},
        {"Chleb", 10}
    };
    return nabidka;
}

inline int Shop::dejCenu(const std::string& nazev) {
    for (const auto& z : getNabidka()) {
        if (z.nazev == nazev) return z.cena / 2; // Výkup za polovinu
    }
    return 1;
}

inline void Shop::start(Player& hrac) {
    bool nakupuje = true;
    std::string vstup;

    while (nakupuje) {
        system("cls"); // Vyèistí obrazovku
        std::cout << "--- HOSPODA U KRIGLU ---" << std::endl;
        std::cout << "Zlato: " << hrac.getZlato() << std::endl;
        std::cout << "Batoh: " << hrac.toString() << std::endl;
        std::cout << "------------------------" << std::endl;
        
        // Výpis zboží
        auto& nabidka = getNabidka();
        for (size_t i = 0; i < nabidka.size(); i++) {
            std::cout << i + 1 << ". " << nabidka[i].nazev << " (" << nabidka[i].cena << " zl)" << std::endl;
        }

        std::cout << "\nNAPIS: cislo (nakup), 'p nazev' (prodej), 'exit' (odchod)" << std::endl;
        std::cout << "> ";
        std::cin >> vstup;

        if (vstup == "exit") {
            nakupuje = false;
        }
        else if (vstup == "p") {
            std::string co; std::cin >> co;
            if (hrac.odeberInventar(co)) {
                int cena = dejCenu(co);
                hrac.pridejZlato(cena);
                std::cout << "Prodal jsi " << co << " za " << cena << std::endl;
            } else {
                std::cout << "To nemas!" << std::endl;
            }
            system("pause");
        }
        else {
            try {
                int id = std::stoi(vstup) - 1;
                if (id >= 0 && id < (int)nabidka.size()) {
                    if (hrac.odeberZlato(nabidka[id].cena)) {
                        hrac.pridejInventar(nabidka[id].nazev);
                        std::cout << "Koupeno!" << std::endl;
                    } else std::cout << "Nemas penize!" << std::endl;
                }
            } catch (...) {}
            system("pause");
        }
    }
}
