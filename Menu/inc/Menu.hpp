#ifndef MENU_H
#define MENU_H

#include <forward_list>
#include <functional>
#include <iostream>
#include <queue>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>

#ifdef _WIN32
#include <Windows.h>
#include <conio.h>
#include <process.h>
#else
#include <curses.h>
#include <fcntl.h>
#include <pthread.h>
#include <termios.h>
#include <unistd.h>

#endif

#define DEFAULT_UP_KEYBOARD_KEYS                                                                   \
    {                                                                                              \
        87, 119, 65                                                                                \
    } // W w ↑
#define DEFAULT_DOWN_KEYBOARD_KEYS                                                                 \
    {                                                                                              \
        83, 115, 66                                                                                \
    } // S s ↓
#define DEFAULT_IN_KEYBOARD_KEYS                                                                   \
    {                                                                                              \
        10                                                                                         \
    } // ENTER (13 on Windows)
#define DEFAULT_BACK_KEYBOARD_KEYS                                                                 \
    {                                                                                              \
        27, 127                                                                                    \
    } // ESC, BACKSPACE (8 on widnows)

#include "Entertainment.hpp"
// Chryste ale to jest shitty rozwiązanie, na załączenie tych zmiennych tutaj i w
// SubtitleEpisodeManagment, bo tam są zmienne globalne, a tu define tego samego xDDD
#define errorColor ent::darkRed
#define SIColor ent::blue
#define userColor ent::lime
#define dataColor ent::darkBlue

namespace menu {
using WskaznikNaFunkcjeMenu = std::function<void(void)>;
using keyboardKey = unsigned char;
using emblem = char;
using position = short;

enum Color_e : uint8_t {
    black,
    darkBlue,
    green,
    turquoise,
    darkRed,
    purple,
    shitDillyPink,
    silver,
    gray,
    blue,
    lime,
    cyan,
    red,
    pink,
    yellow,
    white
};

constexpr short DEFAULT_MENU_REFRESH_TIME = 20'000; //[us]
constexpr Color_e DEFAULT_BACKGROUND_COLOR = black;
constexpr Color_e DEFAULT_FOREGROUND_COLOR = white;
// On windows we got one sequence (224 and then arrow number)
constexpr emblem DEFAULT_SPECIAL_KEY_SYMBOL_1 = 27; // 224; for windows
constexpr emblem DEFAULT_SPECIAL_KEY_SYMBOL_2 = 91; // 224; for windows

const Color_e DEFAULT_MENU_LOGO_FORE = Color_e(SIColor);
constexpr Color_e DEFAULT_MENU_LOGO_BACK = black;
const Color_e DEFAULT_MENU_OPTION_NOT_CHOOSEN_FORE = Color_e(dataColor);
const Color_e DEFAULT_MENU_OPTION_CHOOSEN_FORE = Color_e(userColor);
constexpr Color_e DEFAULT_MENU_OPTION_NOT_CHOOSEN_BACK = black;
constexpr Color_e DEFAULT_MENU_OPTION_CHOOSEN_BACK = black;

#define DEFAULT_MENU_COLOR_SET                                                                     \
    {                                                                                              \
        menu::DEFAULT_MENU_LOGO_FORE, menu::DEFAULT_MENU_LOGO_BACK,                                \
            menu::DEFAULT_MENU_OPTION_CHOOSEN_FORE, menu::DEFAULT_MENU_OPTION_NOT_CHOOSEN_FORE,    \
            menu::DEFAULT_MENU_OPTION_CHOOSEN_BACK, menu::DEFAULT_MENU_OPTION_NOT_CHOOSEN_BACK     \
    }

void ChangeColor(Color_e, Color_e = DEFAULT_BACKGROUND_COLOR);
void ClearScreen(Color_e = DEFAULT_FOREGROUND_COLOR, Color_e = DEFAULT_BACKGROUND_COLOR);
void setCursor(const position, const position);

void* MenuBuforChecker(void*);
void StartNewThread(void* (*)(void*), pthread_t&, void* = nullptr);
int kbhit(void);
/*
lol
*/
class Menu_t {
    /**
    NIE MOZNA STWORZYC OBIEKTU TEJ KLASY TYLKO WSKAZNIK I STWORZYC ZA POMOCA CreateMenu nowy obiekt
    (INACZEJ LAMBDA NIE ZLAPIE OBIEKTU JAKI WLASNIE SIE TWORZY CZYLI MENU SAMEGO W SOBIE)
    zobacz example na dole

    CreateMenu:
        (size_t -> okresla ile lini odstepu ma byc pomiedzy kolejnymi opcjami w menu,

         uint_least8_t -> Oznacza ile wierszy od gory konsoli ma sie wyswietlac menu,

         uint_least8_t -> Oznacza ile kolumn od lewej krawedzi konsoli ma sie wyswietlac menu,

         string logo   -> Wysylamy stringa z logiem i tyle xD

         std::initializer_list<std::pair<string,WskaznikNaFunkcjeMenu>> -> {string,
    wskaznikNaFunkcje lub Funktor}, sa to kolejne opcje menu: tekst i funkcja do wywolania podczas
    potwierdzenia wykonania tej opcji) Funkcja ma nic nie zwracac i nie przyjmowac argumentow

        std::initializer_list<keyboardKey> -> {kolejneChary} oznacza znaki dla ktorych ma byc
    wybierana wyzsza opcja w MENU Wybranie opcji jeden wyzszej

        std::initializer_list<keyboardKey> -> {kolejneChary} oznacza znaki dla ktorych ma byc
    wybierana nizsza opcja w MENU Wybranie opcji jeden nizszej

        std::initializer_list<keyboardKey> -> {kolejneChary} oznacza znaki dla ktorych ma byc
    wybierana opcja w MENU i wykonywane dzialania tej opcji Zatwierdzenie opcji

        std::initializer_list<keyboardKey> -> {kolejneChary} oznacza znaki dla ktorych ma byc
    cofniete MENU (powrot do poprzedniego) WOLNO TYLKO JEST TO MENU JEST NESTED

        std::vector<Color_e> -> kolory poukladane w kolejnosci oznaczaja jakiego koloru ma byc logo,
    jakiego koloru ma byc napis gdy opcja jest wybrana lub gdy nie jest wybrana | zobacz linia 45
    Menu.h

    Zeby uruchomic menu nalezy uruchomic jej funkcje skladowa .StartMenu()

    Aby dostac sie do pojedynczej opcji MENU nalezy uzyc operatora []

    JESLI AKCJA POD WYBRANA OPCJA MENU MA POZOSTAC W MENU NIE NALEZY NA KONIEC TEJ FUNKCJI DODAWAC
    NIC

    JESLI AKCJA POD WYBRANA OPCJA MENU MA WROCIC DO MENU KTORE BYLO WCZESNIEJ NALEZY WYWOLAC
    .GoUpper()

    JESLI AKCJA POD WYBRANA OPCJA MENU MA ZAKONCZYC DZIALANIE MENU I TYLE NALEZY WYWOLAC .Die()

    JESLI AKCJA POD WYBRANA OPCJA MENU MA ODSWIEZYC CALE MENU UZYWAMY FUNKCJI SKLADOWEJ .Refresh()
    w sumie cholera jedna wie po co to jest bo nawet nie dziala

    JESLI TA AKCJA MA ZMIENIC TEXT OBECNEJ OPCJI NALEZY UZYC FUNKCJI SKLADOWEJ ->Text(string) DLA
    ODPOWIEDNIEJ OPCJI, DO KTOREJ DOSTAJEMY SIE POPRZEZ []

    ZEBY ZMIENIC AKCJE DANEGO ELEMENU UZYWAMY .ChangeAction(WskaznikNaFunkcjeMenu); GDZIE WYSYLAMY
    AKCJE DO WYKONANIA

    EXAMPLE:

        menu::Menu_t* confirming = menu::Menu_t::CreateMenu
            (1, 1, 7, "Dzialasz?",
                { {"Tak ",     [&confirming]() { menu::ClearScreen();  confirming->Die(); }},
                 {"Nie" ,  []() {exit(0); } } },
                DEFAULT_UP_KEYBOARD_KEYS, DEFAULT_DOWN_KEYBOARD_KEYS, DEFAULT_IN_KEYBOARD_KEYS, {},
                DEFAULT_MENU_COLOR_SET);

    NIE ZAPOMNIJ O ZWOLNIENIU PAMIECI!!!
        confirming->DeleteMenu();

    */
    pthread_t thread;

    class MenuOption_t;
    friend MenuOption_t;
    friend void* MenuBuforChecker(void*);

    std::vector<MenuOption_t> menuList;
    uint_least8_t choice;
    const uint_least8_t hmo; // HowManyOptions
    const uint_least8_t symetryLine;
    const size_t maxWidth;
    const uint_least8_t upLine;

    static inline std::queue<char> bufor;
    static inline uint8_t isAnyMenuActive = 0;

    std::forward_list<keyboardKey> up;
    std::forward_list<keyboardKey> down;
    std::forward_list<keyboardKey> in;
    std::forward_list<keyboardKey> back;
    std::vector<std::string> logo;

    Color_e optionChoosenFore, optionNotChoosenFore, optionChoosenBack, optionNotChoosenBack,
        logoFore, logoBack;

    uint_least8_t CheckKeyboard();
    void WriteLogo();

    struct SpecialAction_t {
        enum Action_e {
            refreshAll,
            goToPreviousMenu,
            destroy
        };

        Action_e what;

        Action_e operator()() { return what; }
    };

    virtual ~Menu_t() { ; }

    Menu_t(size_t, uint_least8_t, uint_least8_t, std::string,
           std::initializer_list<std::pair<std::string, WskaznikNaFunkcjeMenu>>,
           std::initializer_list<keyboardKey>, std::initializer_list<keyboardKey>,
           std::initializer_list<keyboardKey>, std::initializer_list<keyboardKey>,
           std::vector<Color_e>);

    Menu_t(size_t, uint_least8_t, uint_least8_t, std::string,
           std::vector<std::pair<std::string, WskaznikNaFunkcjeMenu>>,
           std::initializer_list<keyboardKey>, std::initializer_list<keyboardKey>,
           std::initializer_list<keyboardKey>, std::initializer_list<keyboardKey>,
           std::vector<Color_e>);

public:
    static char GetChar();

    void StartMenu();

    void DeleteMenu() { delete this; }

    static Menu_t* CreateMenu(size_t, uint_least8_t, uint_least8_t, std::string,
                              std::initializer_list<std::pair<std::string, WskaznikNaFunkcjeMenu>>,
                              std::initializer_list<keyboardKey>,
                              std::initializer_list<keyboardKey>,
                              std::initializer_list<keyboardKey>,
                              std::initializer_list<keyboardKey>, std::vector<Color_e>);

    static Menu_t* CreateMenu(size_t, uint_least8_t, uint_least8_t, std::string,
                              std::vector<std::pair<std::string, WskaznikNaFunkcjeMenu>>,
                              std::initializer_list<keyboardKey>,
                              std::initializer_list<keyboardKey>,
                              std::initializer_list<keyboardKey>,
                              std::initializer_list<keyboardKey>, std::vector<Color_e>);

    MenuOption_t& operator[](int i) { return menuList[i]; }

    void Die();
    void GoUpper();
    void Refresh();

private:
    void ClearBufor();

    class MenuOption_t {
        Menu_t* who;
        std::string text;
        uint_least8_t line;
        WskaznikNaFunkcjeMenu action;

    public:
        MenuOption_t(std::string x, WskaznikNaFunkcjeMenu ac, uint_least8_t y, Menu_t* z)
            : who{z}, text{x}, line{y}, action{ac}
        {
        }
        void Active(bool);
        WskaznikNaFunkcjeMenu Action() { return action; }
        void Text(std::string, bool = true);
        void ChangeAction(WskaznikNaFunkcjeMenu x) { action = x; }
    };
};

} // namespace menu

#endif // MENU_H
