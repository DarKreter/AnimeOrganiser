#include "Entertainment.hpp"

using namespace std;

namespace ent {
void Dots(int czas, int howManyTimes, char znak)
{
    for(int i = 1; i <= howManyTimes; i++) {
        sleep(czas);
        std::cout << znak;
    }
    sleep(czas);
}

void Fan(int howLong, int breakTime)
{
    char tab[] = {'\\', '-', '/', '|'};
    for(int i = 0; i < howLong; i++) {
        cout << tab[i % 4] << "\b" << flush;
        usleep(breakTime);
    }
}

void ChangeColor([[maybe_unused]] Color f, [[maybe_unused]] Color b)
{
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            static_cast<int>(f) + static_cast<int>(b) * 16);
#endif
}
} // namespace ent