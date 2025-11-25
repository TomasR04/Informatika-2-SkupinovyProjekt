#include "Player.h"
#include <algorithm>
#include <sstream>
#include <iostream>
//Franta

Player::Player()
    : m_jmeno(""),
    m_prijmeni(""),
    m_hp(100),
    m_stamina(100),
    m_maxHp(100),
    m_maxStamina(100),
    m_inventar(),
    m_zlato(100),
    m_equippedIndex(-1)
{
}

Player::Player(const std::string& jmeno, const std::string& prijmeni, int hp, int stamina, int maxHp, int maxStamina, vector<Item> inventar)
    : m_jmeno(jmeno),
    m_prijmeni(prijmeni),
    m_hp(hp),
    m_stamina(stamina),
    m_maxHp(maxHp),
    m_maxStamina(maxStamina),
    m_inventar(inventar),
    m_zlato(1000),
    m_equippedIndex(-1)
{
    if (m_maxHp < 0) m_maxHp = 0;
    if (m_maxStamina < 0) m_maxStamina = 0;

    if (m_hp > m_maxHp) m_hp = m_maxHp;
    if (m_hp < 0) m_hp = 0;

    if (m_stamina > m_maxStamina) m_stamina = m_maxStamina;
    if (m_stamina < 0) m_stamina = 0;
}

const std::string& Player::getJmeno() const { return m_jmeno; }
const std::string& Player::getPrijmeni() const { return m_prijmeni; }
int Player::getHp() const { return m_hp; }
int Player::getStamina() const { return m_stamina; }
int Player::getMaxHp() const { return m_maxHp; }
int Player::getMaxStamina() const { return m_maxStamina; }
vector<Item> Player::getInventar() const { return m_inventar; }

void Player::setJmeno(const std::string& jmeno) { m_jmeno = jmeno; }
void Player::setPrijmeni(const std::string& prijmeni) { m_prijmeni = prijmeni; }

void Player::setHp(int hp) {
    m_hp = hp;
    if (m_hp < 0) m_hp = 0;
    if (m_hp > m_maxHp) m_hp = m_maxHp;
}

void Player::setStamina(int stamina) {
    hranyHrac.m_stamina = stamina;
    if (m_stamina < 0) m_stamina = 0;
    if (m_stamina > m_maxStamina) hranyHrac.m_stamina = m_maxStamina;
}

void Player::setMaxHp(int maxHp) {
    m_maxHp = maxHp;
    if (m_hp > m_maxHp) m_hp = m_maxHp;
}

void Player::setMaxStamina(int maxStamina) {
    m_maxStamina = maxStamina;
    if (m_stamina > m_maxStamina) m_stamina = m_maxStamina;
}


void Player::pridejInventar(Item polozka) {
    m_inventar.push_back(polozka);
}

bool Player::odeberInventar(Item polozka) {
    auto it = std::find(m_inventar.begin(), m_inventar.end(), polozka);
    if (it != m_inventar.end()) {
        int idx = static_cast<int>(std::distance(m_inventar.begin(), it));
        
        if (idx == m_equippedIndex) m_equippedIndex = -1;
        else if (idx >= 0 && idx < m_equippedIndex) --m_equippedIndex; 
        m_inventar.erase(it);
        return true;
    }
    return false;
}

// convenience overloads using item name
void Player::pridejInventar(const std::string& itemName) {
    // create a simple Item with default values; this may be replaced with a factory lookup
    Item it(itemName, 0, 0, 0, Item::Type::FOOD);
    pridejInventar(it);
}



bool Player::odeberInventar(const std::string& itemName) {
    auto it = std::find_if(m_inventar.begin(), m_inventar.end(), [&](const Item& i) { return i.name == itemName; });
    if (it != m_inventar.end()) {
        int idx = static_cast<int>(std::distance(m_inventar.begin(), it));
        if (idx == m_equippedIndex) m_equippedIndex = -1;
        else if (idx >= 0 && idx < m_equippedIndex) --m_equippedIndex;
        m_inventar.erase(it);
        return true;
    }
    return false;
}



// akce
void Player::damage(int amount) {
    if (amount <= 0) return;
    m_hp -= amount;
    if (m_hp < 0) m_hp = 0;
}

void Player::heal(int amount) {
    if (amount <= 0) return;
    hranyHrac.m_hp += amount;
    if (hranyHrac.m_hp > m_maxHp) hranyHrac.m_hp = m_maxHp;
}

bool Player::useStamina(int amount) {
    if (amount <= 0) return true;
    if (m_stamina >= amount) {
        m_stamina -= amount;
        return true;
    }
    return false;
}


std::string Player::toString() const {
	
	std::ostringstream oss;
	oss << m_jmeno << " " << m_prijmeni << " | HP: " << m_hp << "/" << m_maxHp
		<< " | Stamina: " << m_stamina << "/" << m_maxStamina
		<< " | Zlato: " << m_zlato << " zl" << std::endl;
	oss << "Inventář: "<<endl;
	if (m_inventar.empty()) {
		oss << "prázdný";
	}
	else {
		for (size_t i = 0; i < m_inventar.size(); ++i) {
			oss << i << ". " << m_inventar[i].name;
			if (i < m_inventar.size() - 1) {
				oss << endl;
			}
		}
	}



    
    return oss.str();
}

void Player::useItem(Player player, int index) {
      if (index < 0 || index >= static_cast<int>(player.getInventar().size())) {
        std::cout << "Neplatný index položky!" << std::endl;
		return;
        }
    Item item = player.getInventar()[index];
    switch (item.type) {
    case Item::Type::FOOD:
        player.heal(item.value);
        std::cout << "Snědl jsi " << item.name << " a obnovil " << item.value << " HP." << std::endl;
        break;
    case Item::Type::POTION:
        player.heal(item.value);
		player.setStamina(player.getStamina() + item.value);
		std::cout << "Vypil jsi " << item.name << " a obnovil " << item.value << " HP a Staminu." << std::endl;
        break;
    default:
        std::cout << "Tuto položku nelze použít!" << std::endl;
        return;
    }
	player.odeberInventar(item);
}

/*std::ostream& operator<<(std::ostream& os, const Player& p) {
    os << p.toString();
    return os;
}*/

int Player::getZlato() const {
    return m_zlato;
}

void Player::setZlato(int amount) {
    m_zlato = amount;
    if (m_zlato < 0) m_zlato = 0;
}

void Player::pridejZlato(int amount) {
    if (amount > 0) {
        m_zlato += amount;
    }
}

bool Player::odeberZlato(int amount) {
    if (amount > 0 && m_zlato >= amount) {
        m_zlato -= amount;
        return true; 
    }
    return false; 
}

void Player::pridatZlato(int amount) {
    if (amount > 0) {
        m_zlato += amount;
    }
}
