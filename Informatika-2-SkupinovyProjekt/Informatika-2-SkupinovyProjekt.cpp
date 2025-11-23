// Informatika-2-SkupinovyProjekt.cpp : Tento soubor obsahuje funkci main. Provádění programu se tam zahajuje a ukončuje.
//

#include "UI.h"
#include "Controls.h"
#include "Windows.h"
#include <iostream>
#include <string>


void SetUp() {
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	std::ios_base::sync_with_stdio(false);
}
int main()
{
	SetUp();
	
	/*UI::showMap();
	Controls::moveDown();
	cout << "-----------------" << std::endl;
	UI::showMap();*/
	
	string input = "";
	bool running = true;
	while (running) {
		UI::showMap();
		
		cin >> input;
		Controls::processInput(input);
		UI::showMap();
		
	}
    
}



// Spuštění programu: Ctrl+F5 nebo nabídka Ladit > Spustit bez ladění
// Ladění programu: F5 nebo nabídka Ladit > Spustit ladění

// Tipy pro zahájení práce:
//   1. K přidání nebo správě souborů použijte okno Průzkumník řešení.
//   2. Pro připojení ke správě zdrojového kódu použijte okno Team Explorer.
//   3. K zobrazení výstupu sestavení a dalších zpráv použijte okno Výstup.
//   4. K zobrazení chyb použijte okno Seznam chyb.
//   5. Pokud chcete vytvořit nové soubory kódu, přejděte na Projekt > Přidat novou položku. Pokud chcete přidat do projektu existující soubory kódu, přejděte na Projekt > Přidat existující položku.
//   6. Pokud budete chtít v budoucnu znovu otevřít tento projekt, přejděte na Soubor > Otevřít > Projekt a vyberte příslušný soubor .sln.
