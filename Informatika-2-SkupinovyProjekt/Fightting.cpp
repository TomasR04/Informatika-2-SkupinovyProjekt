#include "Fighting.h"
#include "Controls.h"
#include "Player.h"
#include "Item.h"
#include "Map.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

static bool isRandomSeeded = false;


static void seedRandomOnce()
{
    if (!isRandomSeeded)
    {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        isRandomSeeded = true;
    }
}

bool Fighting::startFight(Player& player)
{
    seedRandomOnce();

    
    string enemyName = "Goblin";
    int enemyHp = 50;
    int enemyDamageMin = 6;
    int enemyDamageMax = 12;

	Item selectedWeapon = Item("", 0, 0, 0, Item::Type::FOOD);

    cout << "Vyber zbraò:"<< endl;
	vector<Item> inventory = player.getInventar();
	vector<Item> weapons;
	weapons.push_back(Item("Pìst", 0, 5, 0, Item::Type::MELEE_WEAPON)); // defaultní zbraò
	for (const auto& item : inventory) {
		if (item.type == Item::Type::MELEE_WEAPON || item.type == Item::Type::RANGED_WEAPON) {
			weapons.push_back(item);
		}
	}
	for (size_t i = 0; i < weapons.size(); ++i) {
		cout << i + 1 << ". " << weapons[i].name << " (DMG bonus: " << weapons[i].value << ")\n";
	}
	int weaponChoice;
	cout << "> ";
	cin >> weaponChoice;
	if (weaponChoice >= 1 && weaponChoice <= static_cast<int>(weapons.size())) {
		selectedWeapon = weapons[weaponChoice - 1];
		cout << "Vybral jsi zbraò: " << selectedWeapon.name << "\n";
	}
	else {
		cout << "Neplatná volba, použiješ pìst.\n";
		selectedWeapon = Item("Pìst", 0, 5, 0, Item::Type::MELEE_WEAPON);
	}


    cout << "\n============================\n";
    cout << "  !!! SOUBOJ ZACINA !!!\n";
    cout << "  Nepøítel: " << enemyName << " (HP: " << enemyHp << ")\n";
    cout << "============================\n";

    Controls::gameState = Controls::FIGHTING;

    while (Controls::gameState == Controls::FIGHTING &&
        player.getHp() > 0 &&
        enemyHp > 0)
    {
        cout << "\n--- STAV ---\n";
        cout << player.getJmeno() << " " << player.getPrijmeni()
            << " | HP: " << player.getHp() << "/" << player.getMaxHp()
            << " | Stamina: " << player.getStamina() << "/" << player.getMaxStamina() << "\n";
        cout << enemyName << " | HP: " << enemyHp << "\n\n";

        cout << "Vyber akci:\n";
        cout << "  a  - lehký útok (stamina 10)\n";
        cout << "  h  - silný útok (stamina 25, vìtší dmg)\n";
        cout << "  r  - odpoèinek (obnoví trochu stamina)\n";
        cout << "  run - pokus o útìk\n";
        cout << "> ";

        string cmd;
        cin >> cmd;

        bool playerActed = false;   // jestli hráè skuteènì nìco udìlal (tøeba ne kvùli nedostatku staminy)
        bool wantsToRun = false;  // jestli se hráè pokusil utéct

        // získáme bonus z vybavené zbranì
        int weaponBonus = selectedWeapon.value;

        // === TAH HRÁÈE ===
        if (cmd == "a" || cmd == "A" || cmd == "attack")
        {
            int cost = 10;
            if (!player.useStamina(cost))
            {
                cout << "Nemas dost staminy na lehký útok!\n";
            }
            else
            {
                int base = 10 + (std::rand() % 6); // 10–15
                int dmg = base + weaponBonus;
                enemyHp -= dmg;
                cout << "Zasáhl jsi " << enemyName << " za " << dmg;
                if (weaponBonus > 0) cout << " (" << base << " + zbraò " << weaponBonus << ")";
                cout << " DMG!\n";
                playerActed = true;
            }
        }
        else if (cmd == "h" || cmd == "H" || cmd == "heavy")
        {
            int cost = 25;
            if (!player.useStamina(cost))
            {
                cout << "Nemas dost staminy na silný útok!\n";
            }
            else
            {
                int hitChance = std::rand() % 100; // 0–99
                if (hitChance < 70) // 70% šance, že trefí
                {
                    int base = 22 + (std::rand() % 9); // 22–30
                    // u tìžkého útoku mùžeme zbraní pøièíst tøeba celý bonus * 2 (volitelné) — zatím použijeme 1×
                    int dmg = base + weaponBonus;
                    enemyHp -= dmg;
                    cout << "Silny útok! Dal jsi " << dmg;
                    if (weaponBonus > 0) cout << " (" << base << " + zbraò " << weaponBonus << ")";
                    cout << " DMG!\n";
                }
                else
                {
                    cout << "Silný útok minul!\n";
                }
                playerActed = true;
            }
        }
        else if (cmd == "r" || cmd == "R" || cmd == "rest")
        {
            int amount = 15 + (std::rand() % 6); // 15–20
            player.setStamina(player.getStamina() + amount);
            cout << "Odpoèíváš a obnovuješ " << amount << " staminy.\n";
            playerActed = true;
        }
        else if (cmd == "run")
        {
            wantsToRun = true;
            int chance = std::rand() % 100; // 0–99
            if (chance < 60)
            {
                cout << "Úspešnì se ti podaøilo utéct!\n";
                Controls::gameState = Controls::TRAVELING;
                return true; // pøežil a utekl
            }
            else
            {
                cout << "Nepodaøilo se ti utéct!\n";
                // nepøítel tì pak v tomto kole normálnì udeøí
            }
        }
        else
        {
            cout << "Neplatná akce, zkus to znovu.\n";
        }

        // Nepøítel mrtvý po útoku hráèe?
        if (enemyHp <= 0)
        {
            cout << "\n" << enemyName << " byl poražen!\n";
            cout << "Získáváš 20 zlata.\n";
            player.pridejZlato(20);
			//smazáni nepøítele z mapy
			Map::overwriteTile(Controls::x, Controls::y, " ?? ");
            Controls::gameState = Controls::TRAVELING;
            return true; 
        }

        // === TAH NEPØÍTELE (pokud hráè ještì žije a neodešel) ===
        if (player.getHp() > 0 && Controls::gameState == Controls::FIGHTING)
        {
            int dmg = enemyDamageMin + (std::rand() % (enemyDamageMax - enemyDamageMin + 1));
            cout << enemyName << " tì útoèí za " << dmg << " DMG.\n";
            player.damage(dmg);
        }

        // Kontrola smrti hráèe
        if (player.getHp() <= 0)
        {
            cout << "\nByl jsi poražen!\n";
            cout << "GAME OVER.\n";

            exit(0);
        }
    }

    // Pokud cyklus skonèil z jiných dùvodù
    return (player.getHp() > 0);
}
