#include "Unit.h"
#include "Group.h"

#include "StringFuncs.h"

Unit::Unit(Group *grp, unsigned short ID) : m_dX(0), m_dY(0), m_dZ(0), m_dAzimuth(-1), m_strType(), m_bPlayable(false), m_bLeader(false),
	m_dSkill(-1), m_strInit(), m_strDesc(), m_dHealth(-1), m_dAmmo(-1), m_ID(ID), m_grp(grp), m_bPlayer(false), m_dPlacement(0),
	m_strName(), m_strSpecial(), m_strAge()
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
			m_strSpecial = strArg.substr(1, strArg.length()-3);
		}
		else if(strCmd == "vehicle")
		{
			m_strType = strArg.substr(1, strArg.length()-3);
		}
		else if(strCmd == "player")
		{
			if(strArg == "\"PLAY CDG\";")
			{
				m_bPlayable = true;
			}
			else if(strArg == "\"PLAYER COMMANDER\";")
			{
				m_bPlayer = true;
			}
		}
		else if(strCmd == "leader")
		{
			if(strArg == "1;")
			{
				m_bLeader = 1;
			}
		}
		else if(strCmd == "rank")
		{
			m_strRank = strArg.substr(1, strArg.length()-3);
		}
		else if(strCmd == "skill")
		{
			m_dSkill = atof(strArg.substr(0, strArg.length()-1).c_str());
		}
		else if(strCmd == "init")
		{
			m_strInit = strArg.substr(1, strArg.length()-3);
		}
		else if(strCmd == "description")
		{
			m_strDesc = strArg.substr(1, strArg.length()-3);
		}
		else if(strCmd == "health")
		{
			m_dHealth = atof(strArg.substr(0, strArg.length()-1).c_str());
		}
		else if(strCmd == "ammo")
		{
			m_dAmmo = atof(strArg.substr(0, strArg.length()-1).c_str());
		}
		else if(strCmd == "placement")
		{
			m_dPlacement = atof(strArg.substr(0, strArg.length()-1).c_str());
		}
		else if(strCmd == "text")
		{
			m_strName = strArg.substr(1, strArg.length()-3);
		}
		else if(strCmd == "age")
		{
			m_strAge = strArg.substr(1, strArg.length()-3);
		}
	}
}

void Unit::SerializeBiEdi(std::ostream &out)
{
	out << "class _unit_" << m_ID << std::endl
		<< "{" << std::endl
		<< "	objectType=\"unit\";" << std::endl
		<< "	class Arguments" << std::endl
		<< "	{" << std::endl
		<< "		POSITION=\"[" << m_dX << "," << m_dY << "," << m_dZ << "]\";" << std::endl //a list of values inside quotes, what?
		<< "		GROUP=\"_group_" << m_grp->GetID() << "\";" << std::endl
		<< "		TYPE=\"" << m_strType << "\";" << std::endl;
	if(m_dSkill != -1)
		out << "		SKILL=\"" << m_dSkill << "\";" << std::endl;
	if(m_dAzimuth != -1)
		out << "		AZIMUT=\"" << m_dAzimuth << "\";" << std::endl;
	if(m_dHealth != -1)
		out << "		HEALTH=\"" << m_dHealth << "\";" << std::endl;
	if(m_dAmmo != -1)
		out << "		AMMO=\"" << m_dAmmo << "\";" << std::endl;
	if(m_strInit != "")
		out << "		INIT=\"" << m_strInit << "\";" << std::endl;
	if(m_strRank != "")
		out << "		RANK=\"" << m_strRank << "\";" << std::endl;
	if(m_bPlayer)
		out << "		PLAYER=\"true\";" << std::endl;
	if(m_bPlayable)
		out << "		PLAYABLE=\"true\";" << std::endl;
	if(m_bLeader)
		out << "		LEADER=\"true\";" << std::endl;
	if(m_dPlacement)
		out << "		PLACEMENT=\"" << m_dPlacement << "\";" << std::endl;
	if(m_strName != "")
		out << "		NAME=\"" << m_strName << "\";" << std::endl;
	if(m_strAge != "")
		out << "		AGE=\"" << m_strAge << "\";" << std::endl;
	if(m_strSpecial != "")
		out << "		SPECIAL=\"" << m_strSpecial << "\";" << std::endl;
	out << "	};" << std::endl
		<< "};" << std::endl;
	//TODO: mess around in 3d editor and find correct names for the rest of the values
}