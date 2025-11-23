#pragma once
#include <string>
#include <vector>
#include <ostream>
class Player //Franta
{
public:
	Player();
	Player(const std::string& jmeno, const std::string& prijmeni, int hp, int stamina, int maxHp, int maxStamina, const std::vector<std::string>& inventar);
	 
	const std::string& getJmeno() const;
	const std::string& getPrijmeni() const;
	int getHp() const;
	int getStamina() const;
	int getMaxHp() const;
	int getMaxStamina() const;
	int getZlato() const;
	const std::vector<std::string>& getInventar() const;

	void setJmeno(const std::string& jmeno);
	void setPrijmeni(const std::string& prijmeni);
	void setHp(int hp);
	void setStamina(int stamina);
	void setMaxHp(int maxHp);
	void setMaxStamina(int maxStamina);
	void setZlato(int amount);
	void pridejZlato(int amount);


	void pridejInventar(const std::string& polozka);
	bool odeberInventar(const std::string& polozka);

	void damage(int amount);
	void heal(int amount);
	bool useStamina(int amount);
	bool odeberZlato(int amount);

	std::string toString() const;
	friend std::ostream& operator<<(std::ostream& os, const Player& player);

private:
	std::string m_jmeno;
	std::string m_prijmeni;
	int m_hp;
	int m_stamina;
	int m_maxHp;
	int m_maxStamina;
	int m_zlato;
	std::vector<std::string> m_inventar;
};


