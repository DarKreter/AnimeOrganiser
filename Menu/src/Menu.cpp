#include "Menu.hpp"

using namespace std;

namespace menu {
void ChangeColor([[maybe_unused]] Color_e f, [[maybe_unused]] Color_e b)
{
    // SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
    //                         static_cast<int>(f) + static_cast<int>(b) * 16);
}

void ClearScreen(Color_e fore, Color_e back)
{
    usleep(100'000);
    ChangeColor(fore, back);
    system("clear");
}

void setCursor(const position x, const position y)
{

#ifdef _WIN32
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
#else
    printf("\033[%d;%dH", y + 1, x + 1);
#endif
}

void StartNewThread(void* (*Funkcja)(void*), pthread_t& thread, void* argList)
{
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    pthread_create(&thread, &attr, Funkcja, (void*)argList);

    pthread_attr_destroy(&attr);
}

void* MenuBuforChecker(void*)
{
    // hide user input
    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    while(true) {
        usleep(DEFAULT_MENU_REFRESH_TIME);

        if(kbhit())
            Menu_t::bufor.push(getchar());

        if(!Menu_t::isAnyMenuActive) {
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // restore user input
            return 0;
        }
    }
}

Menu_t* Menu_t::CreateMenu(size_t sBL, uint_least8_t liine, uint_least8_t sl, string logoo,
                           std::vector<std::pair<string, WskaznikNaFunkcjeMenu>> lisst,
                           std::initializer_list<keyboardKey> upp,
                           std::initializer_list<keyboardKey> downn,
                           std::initializer_list<keyboardKey> inn,
                           std::initializer_list<keyboardKey> backk, std::vector<Color_e> colorr)
{
    Menu_t* nowy = new Menu_t(sBL, liine, sl, logoo, lisst, upp, downn, inn, backk, colorr);
    return nowy;
}

Menu_t* Menu_t::CreateMenu(size_t sBL, uint_least8_t liine, uint_least8_t sl, string logoo,
                           std::initializer_list<std::pair<string, WskaznikNaFunkcjeMenu>> lisst,
                           std::initializer_list<keyboardKey> upp,
                           std::initializer_list<keyboardKey> downn,
                           std::initializer_list<keyboardKey> inn,
                           std::initializer_list<keyboardKey> backk, std::vector<Color_e> colorr)
{
    Menu_t* nowy = new Menu_t(sBL, liine, sl, logoo, lisst, upp, downn, inn, backk, colorr);
    return nowy;
}

Menu_t::Menu_t(size_t sBL, uint_least8_t liine, uint_least8_t sl, string logoo,
               std::vector<std::pair<string, WskaznikNaFunkcjeMenu>> lisst,
               std::initializer_list<keyboardKey> upp, std::initializer_list<keyboardKey> downn,
               std::initializer_list<keyboardKey> inn, std::initializer_list<keyboardKey> backk,
               std::vector<Color_e> colorr)
    : choice{0}, hmo{static_cast<uint_least8_t>(lisst.size())}, symetryLine{sl}, maxWidth{0},
      upLine{liine}, up{static_cast<std::forward_list<keyboardKey>>(upp)},
      down{static_cast<std::forward_list<keyboardKey>>(downn)},
      in{static_cast<std::forward_list<keyboardKey>>(inn)},
      back{static_cast<std::forward_list<keyboardKey>>(backk)}, optionChoosenFore{colorr[2]},
      optionNotChoosenFore{colorr[3]}, optionChoosenBack{colorr[4]},
      optionNotChoosenBack{colorr[5]}, logoFore{colorr[0]}, logoBack{colorr[1]}
{
    string roboczy;
    std::istringstream strumien(logoo);
    while(getline(strumien, roboczy))
        logo.push_back(roboczy);

    int i = liine + logo.size() + sBL;
    size_t* sizee = const_cast<size_t*>(&maxWidth);
    for(auto x : lisst) {
        menuList.push_back(MenuOption_t(x.first, x.second, i, this));
        i += sBL + 1;
        if(*sizee < x.first.size())
            *sizee = x.first.size();
    }
    *sizee = (*sizee / 2) + 2 + symetryLine;
}

Menu_t::Menu_t(size_t sBL, uint_least8_t liine, uint_least8_t sl, string logoo,
               std::initializer_list<std::pair<string, WskaznikNaFunkcjeMenu>> lisst,
               std::initializer_list<keyboardKey> upp, std::initializer_list<keyboardKey> downn,
               std::initializer_list<keyboardKey> inn, std::initializer_list<keyboardKey> backk,
               std::vector<Color_e> colorr)
    : Menu_t(sBL, liine, sl, logoo,
             static_cast<std::vector<std::pair<string, WskaznikNaFunkcjeMenu>>>(lisst), upp, downn,
             inn, backk, colorr)
{
    ;
}

char Menu_t::GetChar()
{
    while(bufor.empty()) {
        usleep(DEFAULT_MENU_REFRESH_TIME);
    }

    char temp = bufor.front();
    bufor.pop();

    return temp;
}

uint_least8_t Menu_t::CheckKeyboard()
{
    keyboardKey znak;
    try {
        while(true) {
            znak = GetChar();
            // if(znak == DEFAULT_SPECIAL_KEY_SYMBOL)
            //     znak = GetChar();
            if(znak == DEFAULT_SPECIAL_KEY_SYMBOL_1) {
                znak = GetChar();
                if(znak == DEFAULT_SPECIAL_KEY_SYMBOL_2)
                    znak = GetChar();
            }

            for(auto x : up)
                if(x == znak && choice != 0)
                    return choice--;

            for(auto x : down)
                if(x == znak && choice != hmo - 1)
                    return choice++;

            for(auto x : back)
                if(x == znak)
                    GoUpper();

            for(auto x : in)
                if(x == znak) {
                    if(menuList[choice].Action())
                        menuList[choice].Action()();
                    return choice;
                }
        }
    }

    catch(SpecialAction_t& spa) {
        if(spa() == SpecialAction_t::refreshAll) {
            WriteLogo();
            for(auto menuu : menuList)
                menuu.Active(false);
        }

        if(spa() == SpecialAction_t::goToPreviousMenu)
            throw SpecialAction_t{SpecialAction_t::refreshAll};

        if(spa() == SpecialAction_t::destroy)
            throw spa;
    }
}

void Menu_t::MenuOption_t::Active(bool active)
{
    setCursor(0, line);
    std::cout << string(who->maxWidth, ' ');
    if(active)
        ChangeColor(who->optionChoosenFore, who->optionChoosenBack);
    else
        ChangeColor(who->optionNotChoosenFore, who->optionNotChoosenBack);
    std::cout << '\r' << string(who->symetryLine - (text.length() / 2), ' ')
              << (active == true ? "-" : " ") << text;
}

void Menu_t::WriteLogo()
{
    setCursor(0, upLine);

    ChangeColor(logoFore, logoBack);

    for(auto lol : logo)
        cout << string(symetryLine - (lol.length() / 2) + 1, ' ') << lol << endl;
}

void Menu_t::StartMenu()
{
    ClearScreen();
    WriteLogo();
    ClearBufor();

    if(++isAnyMenuActive == 1) // zadne nie bylo aktywne odpalamy watek
        menu::StartNewThread(menu::MenuBuforChecker, thread);

    for(auto menuu : menuList)
        menuu.Active(false);

    menuList[choice].Active(true);

    while(true) {
        try {
            menuList[CheckKeyboard()].Active(false);
            menuList[choice].Active(true);
        }
        catch(SpecialAction_t& spa) {
            if(spa() == SpecialAction_t::destroy)
                return;

            throw spa;
        }
    }
}

void Menu_t::MenuOption_t::Text(string x, bool u)
{
    text = x;
    if(size_t temp = ((text.length() / 2) + 2 + who->symetryLine); temp > who->maxWidth) {
        size_t* sizee = const_cast<size_t*>(&(who->maxWidth));
        *sizee = temp;
    }
    Active(u);
}

void Menu_t::ClearBufor() {}

void Menu_t::GoUpper()
{
    ClearScreen();
    throw SpecialAction_t{SpecialAction_t::goToPreviousMenu};
}

void Menu_t::Die()
{
    isAnyMenuActive--; // Jak wyjdzie zero to watek sie przerwie
    pthread_join(thread, NULL);
    throw SpecialAction_t{SpecialAction_t::destroy};
}

void Menu_t::Refresh() { throw SpecialAction_t{SpecialAction_t::refreshAll}; }

int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

} // namespace menu
