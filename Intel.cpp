#include "Intel.h"

#include <string>
#include <cassert>

#include "StringFuncs.h"

Intel::Intel() : m_dOvercast(0), m_dOvercastWanted(0), m_dFog(0), m_dFogWanted(0),
	m_hour(0), m_minute(0), m_month(0), m_year(0), m_day(0)
{
}

void Intel::DeserializeSQM(std::istream &in)
{
	std::string strLine;
	std::getline(in, strLine);
	assert(strLine != "{");
	unsigned short scope = 1;

	while(scope != 0)
	{
		std::getline(in, strLine);

		scope += CharCount(strLine, '{');
		scope -= CharCount(strLine, '}');

		size_t eqPos = strLine.find('=');
		std::string strCmd = RemoveWhitespace(strLine.substr(0, eqPos));
		std::string strArg = strLine.substr(eqPos+1, strLine.size()-1);

		if(strCmd == "startWeather")
		{
			m_dOvercast = atof(strArg.c_str());
		}
		else if(strCmd == "forecastWeather")
		{
			m_dOvercastWanted = atof(strArg.c_str());
		}
		else if(strCmd == "year")
		{
			m_year = atoi(strArg.c_str());
		}
		else if(strCmd == "month")
		{
			m_month = atoi(strArg.c_str());
		}
		else if(strCmd == "day")
		{
			m_day = atoi(strArg.c_str());
		}
		else if(strCmd == "hour")
		{
			m_hour = atoi(strArg.c_str());
		}
		else if(strCmd == "minute")
		{
			m_minute = atoi(strArg.c_str());
		}
	}
}

void Intel::SerializeBiEdi(std::ostream &out)
{
	out << "class _intel_1" << std::endl
		<< "{" << std::endl
		<< "	objectType=\"intel\";" << std::endl
		<< "	class Arguments" << std::endl
		<< "	{" << std::endl
		<< "		OVERCAST=\"" << m_dOvercast << "\";" << std::endl
		<< "		OVERCAST_WANTED=\"" << m_dOvercastWanted << "\";" << std::endl
		<< "		FOG=\"" << m_dFog << "\";" << std::endl
		<< "		FOG_WANTED=\"" << m_dFogWanted << "\";" << std::endl
		<< "		YEAR=\"" << m_year << "\";" << std::endl
		<< "		MONTH=\"" << (unsigned int)m_month << "\";" << std::endl
		<< "		DAY=\"" << (unsigned int)m_day << "\";" << std::endl
		<< "		HOUR=\"" << (unsigned int)m_hour << "\";" << std::endl
		<< "		MINUTE=\"" << (unsigned int)m_minute << "\";" << std::endl
		<< "	};" << std::endl
		<< "};"  << std::endl;
}