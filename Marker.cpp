#include "Marker.h"

#include "StringFuncs.h"

Marker::Marker(unsigned short ID) : m_ID(ID), m_dX(0), m_dY(0), m_dZ(0), m_dAngle(0), m_dA(1), m_dB(1),
	m_strType(), m_strMarkerType(), m_strColor(), m_strFill(), m_strText(), m_strName()
{
}

void Marker::DeserializeSQM(std::istream &in)
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
		else if(strCmd == "angle")
		{
			m_dAngle = atof(strArg.substr(0, strArg.length()-1).c_str());
		}
		else if(strCmd == "a")
		{
			m_dA = atof(strArg.substr(0, strArg.length()-1).c_str());
		}
		else if(strCmd == "b")
		{
			m_dB = atof(strArg.substr(0, strArg.length()-1).c_str());
		}
		else if(strCmd == "type")
		{
			m_strType = strArg.substr(1, strArg.length()-3);
		}
		else if(strCmd == "markerType")
		{
			m_strMarkerType = strArg.substr(1, strArg.length()-3);
		}
		else if(strCmd == "colorName")
		{
			m_strColor = strArg.substr(1, strArg.length()-3);
		}
		else if(strCmd == "fillName")
		{
			m_strFill = strArg.substr(1, strArg.length()-3);
		}
		else if(strCmd == "text")
		{
			m_strText = strArg.substr(1, strArg.length()-3);
		}
		else if(strCmd == "name")
		{
			m_strName = strArg.substr(1, strArg.length()-3);
		}
	}
}

void Marker::SerializeBiEdi(std::ostream &out)
{
	out << "class _marker_" << m_ID << std::endl
		<< "{" << std::endl
		<< "	objectType=\"marker\";" << std::endl
		<< "	class Arguments" << std::endl
		<< "	{" << std::endl
		<< "		POSITION=\"[" << m_dX << "," << m_dY << "," << 0 << "]\";" << std::endl //z = 0 because in biedi z = above ground-ness
		<< "		NAME=\"" << m_strName << "\";" << std::endl
		<< "		TYPE=\"" << m_strType << "\";" << std::endl;
	if(m_dAngle != -1)
		out << "		ANGLE=\"" << m_dAngle << "\";" << std::endl;
	if(m_dA != -1)
		out << "		A=\"" << m_dA << "\";" << std::endl;
	if(m_dB != -1)
		out << "		B=\"" << m_dB << "\";" << std::endl;
	if(m_strMarkerType != "")
		out << "		MARKER_TYPE=\"" << m_strMarkerType << "\";" << std::endl;
	if(m_strColor != "")
		out << "		COLOR=\"" << m_strColor << "\";" << std::endl;
	if(m_strFill != "")
		out << "		FILL=\"" << m_strFill << "\";" << std::endl;
	if(m_strText != "")
		out << "		TEXT=\"" << m_strText << "\";" << std::endl;
	out << "	};" << std::endl
		<< "};" << std::endl;
}