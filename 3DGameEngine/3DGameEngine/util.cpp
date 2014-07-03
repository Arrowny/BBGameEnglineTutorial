#include "util.h"
#include <SDL/SDL.h>

void Util::Sleep(int milliseconds)
{
	SDL_Delay(milliseconds);
}

std::vector<std::string> Util::Split(const std::string& s, char delim)
{
	std::vector<std::string> elems;
        
    const char* cstr = s.c_str();
    unsigned int strLength = (unsigned int)s.length();
    unsigned int start = 0;
    unsigned int end = 0;
        
    while(end <= strLength)
    {
        while(end <= strLength)
        {
            if(cstr[end] == delim)
                break;
            end++;
        }
            
        elems.push_back(s.substr(start, end - start));
        start = end + 1;
        end = start;
    }
        
    return elems;
}

std::vector<std::string> Util::RemoveEmptyStrings(const std::vector<std::string>& sVec)
{
	std::vector<std::string> output;

	for (unsigned int ii = 0; ii < sVec.size(); ii++)
	{
		if (sVec[ii] != "")
		{
			output.push_back(sVec[ii]);
		}
	}

	return output;
}
