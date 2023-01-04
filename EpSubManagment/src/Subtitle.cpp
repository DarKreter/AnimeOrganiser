#include "Subtitle.hpp"

namespace file {
std::string Subtitle::NewName()
{
	return File::NewNameWithoutExt() +
		   ".pl.srt";  // + GetFileExtension(); //TAK SIE DZIEJE BO PLEX
					   // MUSI MIEC .SRT ZEBY POBIERAC JE
}
}  // namespace file