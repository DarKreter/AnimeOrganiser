#include "Entertainment.hpp"
#include <math.h>

using namespace std;
namespace ent {

string Format_t::Sequence() const
{
    std::string sequence = begin_sequence;

    for(uint8_t i = 0; i < 7; i++)              // Check each mode
        if(int(pow(2, i)) & mode)               // if flag is set
            sequence += to_string(i + 3) + ";"; // add this mode

    if(foregroundColor != none) { // one of colors
                                  // do standard color
        sequence += to_string((int)foreground) + to_string((int)foregroundColor) + ";";
        if(foregroundColor == rgb) // eventually add rgb sequence
            sequence += rgb_sequence + to_string((int)fRGB.red) + ";" + to_string((int)fRGB.green) +
                        ";" + to_string((int)fRGB.blue) + ";";
    }

    if(backgroundColor != none) { // one of colors
                                  // do standard color
        sequence += to_string((int)background) + to_string((int)backgroundColor) + ";";
        if(backgroundColor == rgb) // eventually add rgb sequence
            sequence += rgb_sequence + to_string((int)bRGB.red) + ";" + to_string((int)bRGB.green) +
                        ";" + to_string((int)bRGB.blue) + ";";
    }

    sequence.erase(sequence.end() - 1);
    sequence += end_sequence;
    // cout << sequence.substr(1) << endl;
    return sequence;
}

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

void Format_t::SetFColor(Color _color, RGB _rgb)
{
    foregroundColor = _color;
    fRGB = _rgb;
}
void Format_t::SetBColor(Color _color, RGB _rgb)
{
    backgroundColor = _color;
    bRGB = _rgb;
}

std::ostream& operator<<(std::ostream& stream, const Format_t& _format)
{
    stream << _format.Sequence();
    return stream;
}

} // namespace ent