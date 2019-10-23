#include <iostream>
#include <sstream>
#include <filesystem>
#include <ctime>

namespace fs = std::filesystem;

bool SwapFile(const char* name1, const char* name2);

int main()
{
	enum
	{
		BUFFER_SIZE = 1024
	};
	char fileName1[BUFFER_SIZE];
	char fileName2[BUFFER_SIZE];
	while (true)
	{
		// first filename
		while (!std::cin.eof())
		{
			std::cout << "Input 1st filename :\n >> ";
			std::cin.getline(fileName1, sizeof(fileName1));
			if (fs::exists(fs::path(fileName1)))
			{
				break;
			}
		}
		// second filename
		while (!std::cin.eof())
		{
			std::cout << "And 2nd filename :\n >> ";
			std::cin.getline(fileName2, sizeof(fileName2));
			if (fs::exists(fs::path(fileName2)))
			{
				break;
			}
		}
		// end with EOF
		if (std::cin.eof())
		{
			break;
		}
		// swap
		if (SwapFile(fileName1, fileName2))
		{
			std::cout << "\n** File Swapped! **\n";
		}
		std::cout << '\n';
	}
	return 0;
}

bool SwapFile(const char* name1, const char* name2)
{
	fs::path path1(name1);
	fs::path path2(name2);
	// same path
	if (path1 == path2)
	{
		return true;
	}
	// temporary path
	time_t timer;
	time(&timer);
	std::stringstream ss;
	ss << static_cast<unsigned int>(timer);
	fs::path pathTemp(name1);
	pathTemp += '.';
	pathTemp += ss.str();
	// filesystem_error exception handling
	try
	{
		fs::rename(path1, pathTemp);
		fs::rename(path2, path1);
		fs::rename(pathTemp, path2);
	}
	catch (fs::filesystem_error& err)
	{
		// cancel rename
		if (fs::exists(pathTemp))
		{
			fs::rename(pathTemp, path1);
		}
		std::cout << "\n** " << err.what() << " **\n";
		return false;
	}
	return true;
}