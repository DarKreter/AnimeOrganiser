#ifndef ENTERTAINMENT_H
#define ENTERTAINMENT_H

#include <iostream>
#include <stdint.h>
#include <string>
#include <unistd.h>

namespace ent {

class Format_t {
    // Constants
    constexpr static char const* begin_sequence = "\033[";
    constexpr static char const* end_sequence = "m";
    constexpr static char const* rgb_sequence = "2;";
    constexpr static char const* reset_sequence = "\033[0m";

    enum Ground : uint8_t {
        foreground = 3,
        background
    };

public:
    // Enumerate types
    struct Color {
        enum basic : uint8_t {
            black,
            red,
            green,
            yellow,
            blue,
            purple,
            cyan,
            white,
            rgb,
            none
        } color;
        struct RGB_t {
            uint8_t red, green, blue;
        } RGB;

        Color(basic _color, RGB_t _rgb = {0, 0, 0}) : color{_color}, RGB{_rgb} { ; }
        Color(const Color& another) : color{another.color}, RGB{another.RGB} { ; }
    };

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
    std::string Sequence() const;
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
