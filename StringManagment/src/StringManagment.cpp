#include "StringManagment.hpp"
#include <locale>
#include <vector>

using namespace std;

namespace sm {
std::string WSTS(std::wstring const& text) // WStringToString
{
    std::locale const loc("");
    wchar_t const* from = text.c_str();
    std::size_t const len = text.size();
    std::vector<char> buffer(len + 1);
    std::use_facet<std::ctype<wchar_t>>(loc).narrow(from, from + len, '_', &buffer[0]);
    return std::string(&buffer[0], &buffer[len]);
}

std::wstring STWS(std::string const& text) // StringToWtring
{
    return wstring(begin(text), end(text));
}

// const TCHAR* S2TCharP(std::string s) // stringToTCharPointer
// {
//     std::basic_string<TCHAR> converted(s.begin(), s.end());
//     return converted.c_str();
// }

std::string RemoveWSBegin(const std::string& s, const std::string ws)
{
    auto begin = s.find_first_not_of(ws);

    if(begin == string::npos)
        return "";

    return s.substr(begin);
}

std::string RemoveWSEnd(const std::string& s, const std::string ws)
{
    return s.substr(0, s.find_last_not_of(ws) + 1);
}

std::string RemoveWSBeginEnd(const std::string& s, const std::string ws)
{
    const auto begin = s.find_first_not_of(ws);
    if(begin == string::npos)
        return "";

    const auto end = s.find_last_not_of(ws) + 1;
    return s.substr(begin, (end - begin));
}

std::wstring RemoveWSBeginEndW(const std::wstring& s, const std::wstring ws)
{
    const auto begin = s.find_first_not_of(ws);
    if(begin == wstring::npos)
        return L"";

    const auto end = s.find_last_not_of(ws) + 1;
    return s.substr(begin, (end - begin));
}

std::string RemoveDoubleWS(std::string s, const std::string fill, const std::string ws)
{
    auto begin = s.find_first_of(ws);

    while(begin != std::string::npos) {
        const auto end = s.find_first_not_of(ws, begin);

        s.replace(begin, end - begin, fill);

        const auto newStart = begin + fill.length();
        begin = s.find_first_of(ws, newStart);
    }

    return s;
}

std::wstring RemoveDoubleWSW(std::wstring s, const std::wstring fill, const std::wstring ws)
{
    auto begin = s.find_first_of(ws);

    while(begin != std::wstring::npos) {
        const auto end = s.find_first_not_of(ws, begin);

        s.replace(begin, end - begin, fill);

        const auto newStart = begin + fill.length();
        begin = s.find_first_of(ws, newStart);
    }

    return s;
}
} // namespace sm