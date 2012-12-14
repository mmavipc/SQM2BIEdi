#include "Unit.h"

#include "StringFuncs.h"

Unit::Unit(Group *grp) : m_dX(0), m_dY(0), m_dZ(0), m_dAzimuth(0), strType(), m_bPlayable(false), m_bLeader(false)
{
}

void Unit::DeserializeSQM(std::istream &in)
{
	std::string strLine;
	std::getline(in, strLine);
	unsigned short scope = 1;

	while(scope != 0)
	{
		std::getline(in, strLine);

		scope += CharCount(strLine, '{');
		scope -= CharCount(strLine, '}');

		size_t eqPos = strLine.find('=');
		std::string strCmd = RemoveWhitespace(strLine.substr(0, eqPos));
		std::string strArg = strLine.substr(eqPos+1, strLine.size()-1);
		if(strCmd == "position[]")
		{
			strArg = StringReplace(strArg, "{", "");
			size_t commaPos = strArg.find(',');
			m_dX = atof(strArg.substr(0, commaPos).c_str());

			strArg = strArg.substr(commaPos+1, strArg.length());
			commaPos = strArg.find(',');
			m_dZ = atof(strArg.substr(0, commaPos).c_str());

			strArg = strArg.substr(commaPos+1, strArg.length());
			commaPos = strArg.find("};");
			m_dY = atof(strArg.substr(0, commaPos).c_str());
		}
		else if(strCmd == "azimut")
		{
			m_dAzimuth = atof(strArg.substr(0, strArg.length()-1).c_str());
		}
		else if(strCmd == "special")
		{
			//TODO: Fill this in
		}
		else if(strCmd == "vehicle")
		{
			strType = strArg.substr(0, strArg.length()-1);
		}
		else if(strCmd == "player")
		{
			if(strArg == "\"PLAY CDG\";" || strArg == "\"PLAYER COMMANDER\";")
			{
				m_bPlayable = true;
			}
		}
		else if(strCmd == "leader")
		{
			if(strArg == "1;")
			{
				m_bLeader = 1;
			}
		}
	}
}