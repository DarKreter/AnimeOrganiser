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

    if(foregroundColor.color != Color::none) { // one of colors
                                               // do standard color
        sequence += to_string((int)foreground) + to_string((int)foregroundColor.color) + ";";
        if(foregroundColor.color == Color::rgb) // eventually add rgb sequence
            sequence += rgb_sequence + to_string((int)foregroundColor.RGB.red) + ";" +
                        to_string((int)foregroundColor.RGB.green) + ";" +
                        to_string((int)foregroundColor.RGB.blue) + ";";
    }

    if(backgroundColor.color != Color::none) { // one of colors
                                               // do standard color
        sequence += to_string((int)background) + to_string((int)backgroundColor.color) + ";";
        if(backgroundColor.color == Color::rgb) // eventually add rgb sequence
            sequence += rgb_sequence + to_string((int)backgroundColor.RGB.red) + ";" +
                        to_string((int)backgroundColor.RGB.green) + ";" +
                        to_string((int)backgroundColor.RGB.blue) + ";";
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

std::ostream& operator<<(std::ostream& stream, const Format_t& _format)
{
    Format_t::Reset();
    stream << _format.Sequence();
    return stream;
}

} // namespace ent