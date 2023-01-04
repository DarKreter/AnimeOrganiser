#ifndef MENU_H
#define MENU_H

#include "Entertainment.hpp"
#include <forward_list>
#include <functional>
#include <queue>

#ifdef _WIN32
#include <conio.h>
#include <process.h>
#include <Windows.h>

#else
#include <fcntl.h>
#include <pthread.h>
#include <termios.h>
#endif

#define DEFAULT_UP_KEYBOARD_KEYS \
{                                \
87, 119, 65                      \
}  // W w ↑
#define DEFAULT_DOWN_KEYBOARD_KEYS \
{                                  \
83, 115, 66                        \
}  // S s ↓
#define DEFAULT_IN_KEYBOARD_KEYS \
{                                \
10                               \
}  // ENTER (13 on Windows)
#define DEFAULT_BACK_KEYBOARD_KEYS \
{                                  \
27, 127                            \
}  // ESC, BACKSPACE (8 on widnows)

namespace menu {
using WskaznikNaFunkcjeMenu = std::function<void(void)>;
using keyboardKey			= unsigned char;
using emblem				= char;
using position				= short;

constexpr short DEFAULT_MENU_REFRESH_TIME = 20'000;	 //[us]
#define DEFAULT_COLOR ent::Format_t(ent::Format_t::Color::white)
// On windows we got one sequence (224 and then arrow number)
constexpr emblem DEFAULT_SPECIAL_KEY_SYMBOL_1 = 27;	 // 224; for windows
constexpr emblem DEFAULT_SPECIAL_KEY_SYMBOL_2 = 91;	 // 224; for windows

#define DEFAULT_MENU_LOGO \
ent::Format_t(ent::Format_t::Color(ent::Format_t::Color::rgb, {255, 255, 255}))
#define DEFAULT_MENU_OPTION_NOT_CHOOSEN \
ent::Format_t(ent::Format_t::Color(ent::Format_t::Color::rgb, {156, 113, 161}))
#define DEFAULT_MENU_OPTION_CHOOSEN \
ent::Format_t(ent::Format_t::Color(ent::Format_t::Color::rgb, {255, 0, 127}))

#define DEFAULT_MENU_COLOR_SET                                                   \
{                                                                                \
DEFAULT_MENU_LOGO, DEFAULT_MENU_OPTION_CHOOSEN, DEFAULT_MENU_OPTION_NOT_CHOOSEN, \
}

void ClearScreen(ent::Format_t format = DEFAULT_COLOR);
void setCursor(const position, const position);

void *MenuBuforChecker(void *);
void StartNewThread(void *(*) (void *), pthread_t &, void * = nullptr);
int kbhit(void);
/*
lol
*/
class Menu_t {
	/**
	NIE MOZNA STWORZYC OBIEKTU TEJ KLASY TYLKO WSKAZNIK I STWORZYC ZA POMOCA CreateMenu
	nowy obiekt (INACZEJ LAMBDA NIE ZLAPIE OBIEKTU JAKI WLASNIE SIE TWORZY CZYLI MENU
	SAMEGO W SOBIE) zobacz example na dole

	CreateMenu:
		(size_t -> okresla ile lini odstepu ma byc pomiedzy kolejnymi opcjami w menu,

		 uint_least8_t -> Oznacza ile wierszy od gory konsoli ma sie wyswietlac menu,

		 uint_least8_t -> Oznacza ile kolumn od lewej krawedzi konsoli ma sie wyswietlac
	menu,

		 string logo   -> Wysylamy stringa z logiem i tyle xD

		 std::initializer_list<std::pair<string,WskaznikNaFunkcjeMenu>> -> {string,
	wskaznikNaFunkcje lub Funktor}, sa to kolejne opcje menu: tekst i funkcja do wywolania
	podczas potwierdzenia wykonania tej opcji) Funkcja ma nic nie zwracac i nie przyjmowac
	argumentow

		std::initializer_list<keyboardKey> -> {kolejneChary} oznacza znaki dla ktorych ma
	byc wybierana wyzsza opcja w MENU Wybranie opcji jeden wyzszej

		std::initializer_list<keyboardKey> -> {kolejneChary} oznacza znaki dla ktorych ma
	byc wybierana nizsza opcja w MENU Wybranie opcji jeden nizszej

		std::initializer_list<keyboardKey> -> {kolejneChary} oznacza znaki dla ktorych ma
	byc wybierana opcja w MENU i wykonywane dzialania tej opcji Zatwierdzenie opcji

		std::initializer_list<keyboardKey> -> {kolejneChary} oznacza znaki dla ktorych ma
	byc cofniete MENU (powrot do poprzedniego) WOLNO TYLKO JEST TO MENU JEST NESTED

		std::vector<Color_e> -> kolory poukladane w kolejnosci oznaczaja jakiego koloru ma
	byc logo, jakiego koloru ma byc napis gdy opcja jest wybrana lub gdy nie jest wybrana
	| zobacz linia 45 Menu.h

	Zeby uruchomic menu nalezy uruchomic jej funkcje skladowa .StartMenu()

	Aby dostac sie do pojedynczej opcji MENU nalezy uzyc operatora []

	JESLI AKCJA POD WYBRANA OPCJA MENU MA POZOSTAC W MENU NIE NALEZY NA KONIEC TEJ FUNKCJI
	DODAWAC NIC

	JESLI AKCJA POD WYBRANA OPCJA MENU MA WROCIC DO MENU KTORE BYLO WCZESNIEJ NALEZY
	WYWOLAC .GoUpper()

	JESLI AKCJA POD WYBRANA OPCJA MENU MA ZAKONCZYC DZIALANIE MENU I TYLE NALEZY WYWOLAC
	.Die()

	JESLI AKCJA POD WYBRANA OPCJA MENU MA ODSWIEZYC CALE MENU UZYWAMY FUNKCJI SKLADOWEJ
	.Refresh() w sumie cholera jedna wie po co to jest bo nawet nie dziala

	JESLI TA AKCJA MA ZMIENIC TEXT OBECNEJ OPCJI NALEZY UZYC FUNKCJI SKLADOWEJ
	->Text(string) DLA ODPOWIEDNIEJ OPCJI, DO KTOREJ DOSTAJEMY SIE POPRZEZ []

	ZEBY ZMIENIC AKCJE DANEGO ELEMENU UZYWAMY .ChangeAction(WskaznikNaFunkcjeMenu); GDZIE
	WYSYLAMY AKCJE DO WYKONANIA

	EXAMPLE:

		menu::Menu_t* confirming = menu::Menu_t::CreateMenu
			(1, 1, 7, "Dzialasz?",
				{ {"Tak ",     [&confirming]() { menu::ClearScreen();  confirming->Die();
	}},
				 {"Nie" ,  []() {exit(0); } } },
				DEFAULT_UP_KEYBOARD_KEYS, DEFAULT_DOWN_KEYBOARD_KEYS,
	DEFAULT_IN_KEYBOARD_KEYS, {}, DEFAULT_MENU_COLOR_SET);

	NIE ZAPOMNIJ O ZWOLNIENIU PAMIECI!!!
		confirming->DeleteMenu();

	*/
	pthread_t thread;

	class MenuOption_t;
	friend MenuOption_t;
	friend void *MenuBuforChecker(void *);
	friend void Capture(int);

	std::vector<MenuOption_t> menuList;
	uint_least8_t choice;
	const uint_least8_t hmo;  // HowManyOptions
	const uint_least8_t symetryLine;
	const size_t maxWidth;
	const uint_least8_t upLine;

	static inline termios oldTerminalSetup;
	static inline std::queue<char> bufor;
	static inline uint8_t isAnyMenuActive = 0;

	std::forward_list<keyboardKey> up;
	std::forward_list<keyboardKey> down;
	std::forward_list<keyboardKey> in;
	std::forward_list<keyboardKey> back;
	std::vector<std::string> logo;

	ent::Format_t optionChoosen, optionNotChoosen, logoF;

	uint_least8_t CheckKeyboard();
	void WriteLogo();

	virtual ~Menu_t() { ; }

	Menu_t(size_t, uint_least8_t, uint_least8_t, std::string,
		   std::initializer_list<std::pair<std::string, WskaznikNaFunkcjeMenu>>,
		   std::initializer_list<keyboardKey>, std::initializer_list<keyboardKey>,
		   std::initializer_list<keyboardKey>, std::initializer_list<keyboardKey>,
		   std::vector<ent::Format_t>);

	Menu_t(size_t, uint_least8_t, uint_least8_t, std::string,
		   std::vector<std::pair<std::string, WskaznikNaFunkcjeMenu>>,
		   std::initializer_list<keyboardKey>, std::initializer_list<keyboardKey>,
		   std::initializer_list<keyboardKey>, std::initializer_list<keyboardKey>,
		   std::vector<ent::Format_t>);

public:
	struct SpecialAction_t {
		enum Action_e {
			refreshAll,
			goToPreviousMenu,
			destroy
		};

		Action_e what;

		Action_e operator()() { return what; }
	};

	static char GetChar();

	void StartMenu();

	void DeleteMenu() { delete this; }

	static Menu_t *
		CreateMenu(size_t, uint_least8_t, uint_least8_t, std::string,
				   std::initializer_list<std::pair<std::string, WskaznikNaFunkcjeMenu>>,
				   std::initializer_list<keyboardKey>, std::initializer_list<keyboardKey>,
				   std::initializer_list<keyboardKey>, std::initializer_list<keyboardKey>,
				   std::vector<ent::Format_t>);

	static Menu_t *CreateMenu(size_t, uint_least8_t, uint_least8_t, std::string,
							  std::vector<std::pair<std::string, WskaznikNaFunkcjeMenu>>,
							  std::initializer_list<keyboardKey>,
							  std::initializer_list<keyboardKey>,
							  std::initializer_list<keyboardKey>,
							  std::initializer_list<keyboardKey>,
							  std::vector<ent::Format_t>);

	MenuOption_t &operator[](int i) { return menuList[i]; }

	void Die();
	void GoUpper();
	void Refresh();

private:
	void ClearBufor();

	class MenuOption_t {
		Menu_t *who;
		std::string text;
		uint_least8_t line;
		WskaznikNaFunkcjeMenu action;

	public:
		MenuOption_t(std::string x, WskaznikNaFunkcjeMenu ac, uint_least8_t y, Menu_t *z)
			: who {z}, text {x}, line {y}, action {ac}
		{}
		void Active(bool);
		WskaznikNaFunkcjeMenu Action() { return action; }
		void Text(std::string, bool = true);
		void ChangeAction(WskaznikNaFunkcjeMenu x) { action = x; }
	};
};

}  // namespace menu

#endif	// MENU_H
