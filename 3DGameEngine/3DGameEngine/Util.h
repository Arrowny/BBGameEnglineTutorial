#pragma once

#ifndef WIN32
#include <unistd.h>
#endif

#ifdef WIN32
#define SNPRINTF _snprintf_s
#else
#define SNPRINTF snprintf
#endif

#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))
#define INVALID_VALUE 0xFFFFFFFF

#include <vector>
#include <string>
#include <GL\glew.h>
#include <unordered_map>
#include <string>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#define ZERO_MEM(a) std::memset(a, 0, sizeof(a))


namespace Util
{
	void Sleep(int milliseconds);
	std::vector<std::string> Split(const std::string &s, char delim);
	std::vector<std::string> RemoveEmptyStrings(const std::vector<std::string>& sVec);
	bool StartsWith(const std::string& stringToCheck, const std::string& check);

	// trim from start
	static inline std::string &ltrim(std::string &s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
		return s;
	}

	// trim from end
	static inline std::string &rtrim(std::string &s) {
		s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
		return s;
	}

	// trim from both ends
	static inline std::string &trim(std::string &s) {
		return ltrim(rtrim(s));
	}

};
