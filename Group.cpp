#include "Group.h"
#include <string>
#include <cassert>

#include "StringFuncs.h"
#include "Unit.h"

Group::Group(unsigned short ID) : m_units(), m_ID(ID)
{
}

void Group::DeserializeSQM(std::istream &in)
{
	std::string strLine;
	std::getline(in, strLine);
	assert(strLine != "{");
	std::getline(in, strLine);

	strLine = StringReplace(strLine, "\x09", "");
	strLine = StringReplace(strLine, "items=", "");
	strLine = StringReplace(strLine, ";", "");
	m_units.reserve(atoi(strLine.c_str()));

	unsigned int scope = 1;
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