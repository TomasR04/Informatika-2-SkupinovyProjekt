#pragma once
#include <string>
#include <vector>
#include <ostream>
#include "Item.h"
#include <algorithm>
using namespace std;
class Player //Franta
{
public:
    Player();
    Player(const std::string& jmeno, const std::string& prijmeni, int hp, int stamina, int maxHp, int maxStamina, vector<Item> inventory);

    const std::string& getJmeno() const;
    const std::string& getPrijmeni() const;
    int getHp() const;
    int getStamina() const;
    int getMaxHp() const;
    int getMaxStamina() const;
    int getZlato() const;
    vector<Item> getInventar() const;

    void setJmeno(const std::string& jmeno);
    void setPrijmeni(const std::string& prijmeni);
    void setHp(int hp);
    void setStamina(int stamina);
    void setMaxHp(int maxHp);
    void setMaxStamina(int maxStamina);
    void setZlato(int amount);
    void pridejZlato(int amount);

    void pridejInventar(Item polozka);
    bool odeberInventar(Item polozka);
    void pridejInventar(const std::string& itemName);
    bool odeberInventar(const std::string& itemName);

    

    void damage(int amount);
    void heal(int amount);
    bool useStamina(int amount);
    bool odeberZlato(int amount);

    std::string toString() const;
    friend std::ostream& operator<<(std::ostream& os, const Player& player);
	static void useItem(Player player, int index);

private:
    std::string m_jmeno;
    std::string m_prijmeni;
    int m_hp;
    int m_stamina;
    int m_maxHp;
    int m_maxStamina;
    int m_zlato;
    vector<Item> m_inventar;

    int m_equippedIndex = -1; // index do m_inventar; -1 = nic
};

// Global player instance declared in main translation unit
extern Player hranyHrac;
