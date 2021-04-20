#include "Subtitle.h"

namespace file
{
    std::wstring Subtitle::NewName()
    {
        return File::NewNameWithoutExt() + L".pl.srt";  // + GetFileExtension(); //TAK SIE DZIEJE BO PLEX MUSI MIEC .SRT ZEBY POBIERAC JE
    }
}