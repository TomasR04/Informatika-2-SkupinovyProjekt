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
	m_inventar() {
}

Player::Player(const std::string& jmeno, const std::string& prijmeni, int hp, int stamina, int maxHp, int maxStamina, const std::vector<std::string>& inventar)
	: m_jmeno(jmeno),
	m_prijmeni(prijmeni),
	m_hp(hp),
	m_stamina(stamina),
	m_maxHp(maxHp),
	m_maxStamina(maxStamina),
	m_inventar(inventar)
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
const std::vector<std::string>& Player::getInventar() const { return m_inventar; }

void Player::setJmeno(const std::string& jmeno) { m_jmeno = jmeno; }
void Player::setPrijmeni(const std::string& prijmeni) { m_prijmeni = prijmeni; }

void Player::setHp(int hp) {
	m_hp = hp;
	if (m_hp < 0) m_hp = 0;
	if (m_hp > m_maxHp) m_hp = m_maxHp;
}

void Player::setStamina(int stamina) {
	m_stamina = stamina;
	if (m_stamina < 0) m_stamina = 0;
	if (m_stamina > m_maxStamina) m_stamina = m_maxStamina;
}

void Player::setMaxHp(int maxHp) {
	m_maxHp = maxHp;
	if (m_hp > m_maxHp) m_hp = m_maxHp;
}

void Player::setMaxStamina(int maxStamina) {
	m_maxStamina = maxStamina;
	if (m_stamina > m_maxStamina) m_stamina = m_maxStamina;
}

// inventáø
void Player::pridejInventar(const std::string& polozka) {
	m_inventar.push_back(polozka);
}

bool Player::odeberInventar(const std::string& polozka) {
	auto it = std::find(m_inventar.begin(), m_inventar.end(), polozka);
	if (it != m_inventar.end()) {
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
	m_hp += amount;
	if (m_hp > m_maxHp) m_hp = m_maxHp;
}

bool Player::useStamina(int amount) {
	if (amount <= 0) return true;
	if (m_stamina >= amount) {
		m_stamina -= amount;
		return true;
	}
	return false;
}

// výpis
std::string Player::toString() const {
	std::ostringstream oss;
	oss << m_jmeno << " " << m_prijmeni
		<< " | HP: " << m_hp << "/" << m_maxHp
		<< " | Stamina: " << m_stamina << "/" << m_maxStamina
		<< " | Inventáø: [";

	for (size_t i = 0; i < m_inventar.size(); ++i) {
		oss << m_inventar[i];
		if (i + 1 < m_inventar.size()) oss << ", ";
	}
	oss << "]";
	return oss.str();
}

std::ostream& operator<<(std::ostream& os, const Player& p) {
	os << p.toString();
	return os;
}
