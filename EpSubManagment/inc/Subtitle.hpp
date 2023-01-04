#ifndef SUBTITLE_H
#define SUBTITLE_H

#include "File.hpp"
#include <vector>

namespace file {
class Subtitle: public file::File {
private:
	static inline int offset;
	static inline std::vector<std::string> extensions = {"*.ass", "*.srt", "*.txt",
														 "*.ssa"};

public:
	Subtitle(std::string n): File(n) { ; }

	std::string NewName();
	static inline std::vector<std::string> folders = {"sub", "subs", "napisy",
													  "subtitles"};
	static void Offset(int of) { offset = of; }
	static int Offset() { return offset; }
	static std::vector<std::string> &Extensions() { return extensions; }

	void FindEpNumber() { this->File::FindEpNumber(offset); }
};

};	// namespace file

#endif	// !SUBTITLE_H