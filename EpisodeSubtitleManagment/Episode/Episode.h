#ifndef EPISODE_H
#define EPISODE_H

#include "../File/File.h"
#include <vector>

namespace file
{
	class Episode
		:public file::File
	{
	private:
		static inline int offset;
		static inline std::vector<std::string> extensions = { "mp4", "mkv" };

	public:
		Episode(std::wstring n)
			:File(n)
		{
			;
		}
		static void Offset(int of) { offset = of; }
		static int Offset() { return offset; }
		static std::vector<std::string>& Extensions() { return extensions; }

		void FindEpNumber() { this->File::FindEpNumber(offset); }
	};
}


#endif // !EPISODE_H