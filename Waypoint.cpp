#include "Wapoint.h"
#include "Group.h"

#include "StringFuncs.h"

std::vector<Waypoint*> Waypoint::SerializeWaypoints(std::istream &in)
{
	std::vector<Waypoint*> ret;
	std::string strLine;
	std::getline(in, strLine);
	std::getline(in, strLine);

	strLine = StringReplace(strLine, "\x09", "");
	strLine = StringReplace(strLine, "items=", "");
	strLine = StringReplace(strLine, ";", "");
	ret.reserve(atoi(strLine.c_str()));

	return ret;
}

Waypoint::Waypoint(Group *grp, unsigned short ID): m_grp(grp), m_ID(ID)
{
}

void Waypoint::DeserializeSQM(std::istream &in)
{
}