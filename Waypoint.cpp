#include "Wapoint.h"
#include "Group.h"

#include "StringFuncs.h"

std::vector<Waypoint*> Waypoint::DeserializeWaypoints(std::istream &in, Group *group)
{
	std::vector<Waypoint*> ret;
	std::string strLine;
	std::getline(in, strLine);
	std::getline(in, strLine);

	strLine = StringReplace(strLine, "\x09", "");
	strLine = StringReplace(strLine, "items=", "");
	strLine = StringReplace(strLine, ";", "");
	ret.reserve(atoi(strLine.c_str()));

	unsigned int scope = 1;
	while(scope != 0)
	{
		std::getline(in, strLine);
		scope += CharCount(strLine, '{');
		scope -= CharCount(strLine, '}');
		strLine = StringReplace(strLine, "\x09", "");
		if(strLine.find("class Item") != std::string::npos)
		{
			ret.resize(ret.size()+1);
			static unsigned short id = 0;
			Waypoint *wp = new Waypoint(group, id);
			id++;
			wp->DeserializeSQM(in);
			ret[ret.size()-1] = wp;
		}
	}

	return ret;
}

Waypoint::Waypoint(Group *grp, unsigned short ID): m_grp(grp), m_ID(ID), m_dX(0), m_dY(0), m_dZ(0), m_strCombatMode(),
	m_strFormation(), m_strSpeed(), m_strCombat(), m_strShowWP(), m_strType()
{
}

void Waypoint::DeserializeSQM(std::istream &in)
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
		else if(strCmd == "combatMode")
		{
			m_strCombatMode = strArg.substr(1, strArg.length()-3);
		}
		else if(strCmd == "formation")
		{
			m_strFormation = strArg.substr(1, strArg.length()-3);;
		}
		else if(strCmd == "speed")
		{
			m_strSpeed = strArg.substr(1, strArg.length()-3);;
		}
		else if(strCmd == "combat")
		{
			m_strCombat = strArg.substr(1, strArg.length()-3);;
		}
		else if(strCmd == "showWP")
		{
			m_strShowWP = strArg.substr(1, strArg.length()-3);;
		}
		else if(strCmd == "classEffects")
		{
			SeekToPhrase("{", in);// skip for now
			SeekToPhrase("};", in);
		}
		else if(strCmd == "type")
		{
			m_strType = strArg.substr(1, strArg.length()-3);;
		}
		//TODO: Mess around with all options and fill in the rest
	}
}