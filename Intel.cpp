#include "Intel.h"

#include <string>
#include <cassert>

#include "StringFuncs.h"

Intel::Intel() : m_dOvercast(-1), m_dOvercastWanted(-1), m_dFog(-1), m_dFogWanted(-1),
	m_hour(-1), m_minute(-1), m_month(-1), m_year(-1), m_day(-1)
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
		<< "	{" << std::endl;
	if(m_dOvercast != -1)
		out << "		OVERCAST=\"" << m_dOvercast << "\";" << std::endl;
	if(m_dOvercastWanted != -1)
		out << "		OVERCAST_WANTED=\"" << m_dOvercastWanted << "\";" << std::endl;
	if(m_dFog != -1)
		out << "		FOG=\"" << m_dFog << "\";" << std::endl;
	if(m_dFogWanted != -1)
		out << "		FOG_WANTED=\"" << m_dFogWanted << "\";" << std::endl;
	if(m_year != -1)
		out << "		YEAR=\"" << m_year << "\";" << std::endl;
	if(m_month != -1)
		out << "		MONTH=\"" << (unsigned int)m_month << "\";" << std::endl;
	if(m_day != -1)
		out << "		DAY=\"" << (unsigned int)m_day << "\";" << std::endl;
	if(m_hour != -1)
		out << "		HOUR=\"" << (unsigned int)m_hour << "\";" << std::endl;
	if(m_minute != -1)
		out << "		MINUTE=\"" << (unsigned int)m_minute << "\";" << std::endl;
	out << "	};" << std::endl;
	out << "};"  << std::endl;
}