#ifndef ENTERTAINMENT_H
#define ENTERTAINMENT_H

#include <iostream>
#include <string>
#include <unistd.h>

namespace ent {

/**
 * Class used for ANSI escape sequence formatting
 * Created object has overloaded operator<< with ostream, so usage is just 'printing' format object
 * Foreground/background 4bit/24bit(8bit RGB) colors supported with "Format_t::Color"
 * Formatting like underline, blinking, italic font are also supported with "Format_t::Mode"
 */
class Format_t {
    // Constants
    constexpr static char const* begin_sequence = "\033["; // Start sequence of every escape seq
    constexpr static char const* end_sequence = "m";
    constexpr static char const* rgb_sequence = "2;";        // neccessary for rgb 24bit color
    constexpr static char const* reset_sequence = "\033[0m"; // reset to default

    // 3 - foreground, 4 - background
    enum Ground : uint8_t {
        foreground = 3,
        background
    };

public:
    // Enumerate types
    struct Color {
        // 4bit colors values (0-7)
        enum basic : uint8_t {
            black,
            red,
            green,
            yellow,
            blue,
            purple,
            cyan,
            white,
            rgb, // For RGB choose color as 8, and pass 3 bit values
            none
        } color;
        struct RGB_t {
            uint8_t red, green, blue;
        } RGB;

        Color(basic _color, RGB_t _rgb = {0, 0, 0}) : color{_color}, RGB{_rgb} { ; }
        Color(const Color& another) : color{another.color}, RGB{another.RGB} { ; }
    };

    // commented values are sequences, but mode supported combining all option in one variable so
    // each value is stored on separated bits
    enum Mode : uint8_t {
        normal = 0,
        italic = 1,       // 3;
        underline = 2,    // 4;
        slowBlinking = 4, // 5;
        fastBlinking = 8, // 6;
        reverse = 16,     // 7;
        hide = 32,        // 8;
        cross_out = 64    // 9;
    };
    // To combine Mode options
    friend Mode operator|(const Mode& mode1, const Mode& mode2)
    {
        return Mode(uint8_t(mode1) | uint8_t(mode2));
    }

private:
    // private variables
    Color foregroundColor = Color::none, backgroundColor = Color::none;
    uint8_t mode;

public:
    // Access functions
    void SetFColor(Color _color) { foregroundColor = _color; }
    void SetBColor(Color _color) { backgroundColor = _color; }
    void SetMode(Mode _mode) { mode = uint8_t(_mode); }
    Color GetFColor() { return foregroundColor; }
    Color GetBColor() { return backgroundColor; }
    Mode GetMode() { return (Mode)mode; }
    // Return sequence to put on stream
    std::string Sequence() const;
    // Print reset sequence
    static void Reset() { std::cout << reset_sequence; }

    Format_t(Color fgc, Mode m = normal, Color bgc = Color::none)
        : foregroundColor{fgc}, backgroundColor{bgc}, mode{m}
    {
        ;
    }

    friend std::ostream& operator<<(std::ostream& stream, const Format_t& _format);
};

/*
    Wyswietla jakis znak podana ilosc razy z podanym odstepem czasowym
    @param ile czasu ma byc pomiedzy kolejnymi znakami [ms]
    @param ile znakow ma sie wypisac
    @param Jaki to ma byc znak | domniemanie '.'
*/
void Dots(int, int = 3, char = '.');

/*
    Symuluje dzialanie wiatraka na jednym polu w konsoli uzywaja znakow / | \ -
    @param okresla ile razy ma sie obrocic wiatraczek
    @param okresla ile ms ma byc odstepu pomiedzy kolejnymi charami
*/
void Fan(int, int);

} // namespace ent

#endif // !ENTERTAINMENT_H
