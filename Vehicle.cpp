#include "Vehicle.h"

#include "StringFuncs.h"

Vehicle::Vehicle(unsigned short ID) : m_ID(ID), m_dX(0), m_dY(0), m_dZ(0), m_dAzimuth(0), m_strType(),
	m_strInit(), m_dHealth(-1), m_dAmmo(-1), m_dFuel(-1), m_strLock()
{
}

void Vehicle::DeserializeSQM(std::istream &in)
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
			m_strType = strArg.substr(1, strArg.length()-3);
		}
		else if(strCmd == "init")
		{
			m_strInit = strArg.substr(1, strArg.length()-3);
		}
		else if(strCmd == "lock")
		{
			m_strLock = strArg.substr(1, strArg.length()-3);
		}
		else if(strCmd == "health")
		{
			m_dHealth = atof(strArg.substr(0, strArg.length()-1).c_str());
		}
		else if(strCmd == "ammo")
		{
			m_dAmmo = atof(strArg.substr(0, strArg.length()-1).c_str());
		}
		else if(strCmd == "fuel")
		{
			m_dFuel = atof(strArg.substr(0, strArg.length()-1).c_str());
		}
	}
}

void Vehicle::SerializeBiEdi(std::ostream &out)
{
	out << "class _vehicle_" << m_ID << std::endl
		<< "{" << std::endl
		<< "	objectType=\"vehicle\";" << std::endl
		<< "	class Arguments" << std::endl
		<< "	{" << std::endl
		<< "		POSITION=\"[" << m_dX << "," << m_dY << "," << 0 << "]\";" << std::endl //z = 0 because in biedi z = above ground-ness
		<< "		TYPE=\"" << m_strType << "\";" << std::endl;
	if(m_dAzimuth != -1)
		out << "		AZIMUT=\"" << m_dAzimuth << "\";" << std::endl;
	if(m_dHealth != -1)
		out << "		HEALTH=\"" << m_dHealth << "\";" << std::endl;
	if(m_dAmmo != -1)
		out << "		AMMO=\"" << m_dAmmo << "\";" << std::endl;
	if(m_dFuel != -1)
		out << "		FUEL=\"" << m_dFuel << "\";" << std::endl;
	if(m_strInit != "")
		out << "		INIT=\"" << m_strInit << "\";" << std::endl;
	if(m_strLock != "")
		out << "		LOCK=\"" << m_strLock << "\";" << std::endl;
	out << "	};" << std::endl
		<< "};" << std::endl;
}