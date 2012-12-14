#include "Group.h"
#include <string>
#include <cassert>

#include "StringFuncs.h"
#include "Unit.h"

std::vector<Center*> centerList;

Center::Center(std::string strSide) : m_strSide(strSide)
{
}

Center* Center::GetCenter(std::string strSide)
{
	for(unsigned char i = 0; i < centerList.size(); i++)
	{
		if(centerList[i]->m_strSide == strSide)
		{
			return centerList[i];
		}
	}
	Center *center = new Center(strSide);
	centerList.resize(centerList.size()+1);
	centerList[centerList.size()-1] = center;
	return center;
}

const std::vector<Center*> Center::GetCenters()
{
	return centerList;
}

Group::Group(unsigned short ID) : m_units(), m_ID(ID), m_center(NULL)
{
}

void Group::DeserializeSQM(std::istream &in)
{
	std::string strLine;
	std::getline(in, strLine);
	assert(strLine != "{");
	std::getline(in, strLine);

	strLine = StringReplace(strLine, "\x09", "");
	strLine = StringReplace(strLine, "side=\"", "");
	strLine = StringReplace(strLine, "\";", "");

	if(strLine == "WEST")
	{
		m_center = Center::GetCenter("WEST");
	}
	else if(strLine == "EAST")
	{
		m_center = Center::GetCenter("EAST");
	}
	else if(strLine == "GUER")
	{
		m_center = Center::GetCenter("GUER");
	}
	else if(strLine == "CIV")
	{
		m_center = Center::GetCenter("CIV");
	}
	else if(strLine == "LOGIC")
	{
		m_center = Center::GetCenter("LOGIC");
	}
	else if(strLine == "ENEMY")
	{
		m_center = Center::GetCenter("ENEMY");
	}
	
	std::getline(in, strLine);//class Vehicles
	std::getline(in, strLine);//{
	std::getline(in, strLine);//items=bla

	strLine = StringReplace(strLine, "\x09", "");
	strLine = StringReplace(strLine, "items=", "");
	strLine = StringReplace(strLine, ";", "");
	m_units.reserve(atoi(strLine.c_str()));

	unsigned int scope = 2;
	while(scope != 0)
	{
		std::getline(in, strLine);
		scope += CharCount(strLine, '{');
		scope -= CharCount(strLine, '}');
		strLine = StringReplace(strLine, "\x09", "");
		if(strLine.find("class Item") != std::string::npos)
		{
			m_units.resize(m_units.size()+1);
			static unsigned short id = 0;
			Unit *unit = new Unit(this);
			id++;
			unit->DeserializeSQM(in);
			m_units[m_units.size()-1] = unit;
		}
	}
}