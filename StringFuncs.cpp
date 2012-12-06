#include "StringFuncs.h"

std::string SeekToPhrase(const std::string &strPhrase, std::istream &iStream)
{
	std::string strLine;
	std::getline(iStream, strLine);
	while(strLine.find(strPhrase) == std::string::npos && !iStream.eof())
	{
		std::getline(iStream, strLine);
	};
	return strLine;
}

std::string RemoveWhitespace(const std::string &str)
{
	std::string strOut;
	for(size_t i = 0; i < str.size(); i++)
	{
		char c = str[i];
		if(c == '\n' || c == '\r' || c == '\x09' || c == ' ')
		{
			continue;
		}
		strOut += c;
	}
	return strOut;
}

std::string StringReplace(std::string str, const std::string &strReplace, const std::string &strWith, unsigned int count)
{
	size_t pos = str.find(strReplace);
	for(unsigned int i = 0; pos != std::string::npos && (i < count || count == 0); i++)
	{
		str.replace(pos, strReplace.size(), strWith);
		pos = str.find(strReplace);
	}
	return str;
}