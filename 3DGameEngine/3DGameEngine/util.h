#ifndef UTIL_H
#define UTIL_H

//#include <stdio.h>
//#include <GL/glew.h>
//
//#define GL_CHECK(x) do{
//    x;
//    GLenum glerr = glGetError();
//    if (glerr != GL_NO_ERROR) 
//	{
//        printf("OpenGL error: %d, file: %s, line: %d", glerr, __FILE__, __LINE__);
//    }
//} while (0)

#ifndef WIN32
#include <unistd.h>
#endif

#ifdef WIN32
#define SNPRINTF _snprintf_s
#else
#define SNPRINTF snprintf
#endif

//#define ZERO_MEM(a) memset(a,0,sizeof(a))
//#define SAFE_DELETE(p) if(p) {delete p; p = NULL;}
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

class MeshResource;
class TextureResource;
class ShaderResource;

extern std::unordered_map<std::string, MeshResource*> meshResourceMap;
extern std::unordered_map<std::string, unsigned int>  meshResourceCount;
extern std::unordered_map<std::string, TextureResource*> texResourceMap;
extern std::unordered_map<std::string, unsigned int>  texResourceCount;
extern std::unordered_map<std::string, ShaderResource*> loadedShaders;
extern std::unordered_map<std::string, unsigned int>  loadedShadersCount;

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

#endif
