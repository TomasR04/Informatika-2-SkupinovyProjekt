# ⚔️ Žoldnéřova cesta (Mercenary's Journey)

**Informatika 2 - Skupinový Projekt**

Jednoduchá textová RPG adventura v C++, ve které hráč ovládá bývalého žoldnéře hledajícího slávu a bohatství. Hra kombinuje průzkum otevřeného světa, tahové souboje se správou staminy a ekonomický systém.

---

## 👥 Členové skupiny
* **Tomáš Rosenbaum**
* **Jan Vavřina**
* **Filip František Rajdl**
* **Jakub Vitásek**
* **Šimon Šestořád**
* **František Ileš**

---

## 🎮 Herní mechaniky

Hra běží kompletně v konzoli, využívá `GameState` systém pro přepínání mezi průzkumem, bojem a obchodem.

### 1. Průzkum a Mapa 🗺️
Hráč se pohybuje po mřížkové mapě vykreslované pomocí UTF-8 znaků. Každé políčko může spustit specifickou událost.

* **Pohyb:** Hráč se pohybuje po mapě, mapa se překresluje po každém kroku.
* **Legenda mapy:**
    * `●` – Pozice hráče
    * `🌲` – Les (volný pohyb)
    * `🌱` – Pláň
    * `🍺` – Hospoda (Spustí **Obchod**)
    * `E` / `B` – Nepřítel / Boss (Spustí **Souboj**)
    * `🏰` / `🕳️` – Vstupy do jiných lokací (Hrad, Podzemí)
    * `#` – Zeď (nepróchodná)

### 2. Soubojový systém (Fighting) ⚔️
Souboje jsou **tahové**. Hráč musí taktizovat a hlídat si hladinu **Staminy**.

* **Příprava:** Před bojem si hráč vybere zbraň z inventáře. Každá zbraň přidává bonus k poškození.
* **Akce v boji:**
    * **Lehký útok (`a`):** Stojí **10** staminy. Menší poškození, ale jistý zásah.
    * **Těžký útok (`h`):** Stojí **25** staminy. Velké poškození, ale **30% šance na minutí**.
    * **Odpočinek (`r`):** Obnoví náhodné množství staminy (15–20).
    * **Útěk (`run`):** 60% šance na bezpečný návrat na mapu.
* **Nepřítel:** Útočí automaticky každé kolo. Pokud hráč vyhraje, získá **zlato** a nepřítel zmizí z mapy.

### 3. Obchodování a Ekonomika 💰
Když hráč vstoupí do hospody (`🍺`), hra se přepne do obchodního módu.

* **Nákup:** Hráč může za nasbírané zlato nakupovat lepší vybavení (meče, brnění) nebo zásoby.
* **Prodej:** Hráč může prodat libovolný předmět z inventáře (výkupní cena je 50 % původní ceny).
* **Inventář:** Předměty jsou spravovány třídou `Item` a ukládají se do vektoru hráče.

### 4. Statistiky postavy (Player) 📊
Hráč má dynamické statistiky:
* **HP (Životy):** Klesají při zásahu. 0 HP = Konec hry.
* **Stamina:** Platidlo pro útoky v boji.
* **Zlato:** Měna pro obchod.

---

## 🕹️ Ovládání

### Na mapě (Cestování)
| Klávesa | Akce |
| :--- | :--- |
| **W** | Pohyb nahoru |
| **S** | Pohyb dolů |
| **A** | Pohyb doleva |
| **D** | Pohyb doprava |
| **exit** | Ukončení hry |

### V boji (Fighting)
| Klávesa | Akce | Popis |
| :--- | :--- | :--- |
| **a** | **A**ttack (Lehký) | Jistý zásah, malá cena staminy. |
| **h** | **H**eavy (Těžký) | Vysoké DMG, risk minutí. |
| **r** | **R**est (Odpočinek) | Obnovení energie. |
| **run** | Útěk | Pokus o opuštění souboje. |

### V obchodě (Trading)
| Příkaz | Akce |
| :--- | :--- |
| **[číslo]** | Koupit předmět dle nabídky (např. `1`, `2`...) |
| **p [název]** | Prodat předmět (např. `p Meč`) |
| **exit** | Odejít z obchodu zpět na mapu |

---

## 🛠️ Technické detaily
* **Jazyk:** C++
* **Prostředí:** Visual Studio (Solution `.sln`)
* **Kódování:** UTF-8 (Vyžaduje `SetConsoleOutputCP(CP_UTF8)` pro správné zobrazení emotikonů v konzoli).
* **Architektura:**
    * `main.cpp`: Hlavní smyčka a inicializace.
    * `Controls`: Řízení stavů (`TRAVELING`, `FIGHTING`, `TRADING`) a vstupů.
    * `Map`: Definice 2D polí pro různé lokace.
    * `Fighting`: Logika soubojů, RNG a AI nepřítele.
    * `Shop`: Ekonomický systém.
    * `Item`: Definice předmětů (Zbraně, Jídlo, Lektvary).

## 🚀 Jak spustit
1. Otevřete soubor `.sln` ve Visual Studiu.
2. Ujistěte se, že je projekt nastaven na sestavení pro konzoli.
3. Spusťte pomocí **Local Windows Debugger** (nebo klávesou **F5**).