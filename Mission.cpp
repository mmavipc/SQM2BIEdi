#include "Mission.h"
#include "StringFuncs.h"
#include <iostream>

Mission::Mission() : m_intel(NULL)
{
}

void Mission::DeserializeSQM(std::istream &in)
{
	SeekToPhrase("class Mission", in);
	SeekToPhrase("{", in);
	while(!in.eof())
	{
		std::string strLine;
		std::getline(in, strLine);
		strLine = StringReplace(strLine, "\x09", "");
		strLine = StringReplace(strLine, "\r", "");
		strLine = StringReplace(strLine, "\n", "");
		//prepare for the madness
		if(strLine == "addOns[]=")
		{
			while(RemoveWhitespace(strLine) != "};") //skip it for now
			{
				std::getline(in, strLine);
			}
		}
		else if(strLine == "addOnsAuto[]=")
		{
			while(RemoveWhitespace(strLine) != "};") //same thing
			{
				std::getline(in, strLine);
			}
		}
		else if(strLine == "class Intel")
		{
			if(m_intel != NULL)
			{
				std::cout << "WARNING: DUPLICATE INTEL";
			}
			else
			{
				m_intel = new Intel;
			}
			m_intel->DeserializeSQM(in);
		}
		else if(strLine == "class Groups")
		{
			//parser-ception
			std::getline(in, strLine);//{
			std::getline(in, strLine);
			strLine = StringReplace(strLine, "\x09", "");
			strLine = StringReplace(strLine, "items=", "");
			strLine = StringReplace(strLine, ";", "");
			m_groups.reserve(atoi(strLine.c_str()));
			unsigned int scope = 1;
			while(scope != 0)
			{
				std::getline(in, strLine);
				scope += CharCount(strLine, '{');
				scope -= CharCount(strLine, '}');
				strLine = StringReplace(strLine, "\x09", "");
				if(strLine.find("class Item") != std::string::npos)
				{
					m_groups.resize(m_groups.size()+1);
					static unsigned short id = 0;
					Group *group = new Group(id);
					id++;
					group->DeserializeSQM(in);
					m_groups[m_groups.size()-1] = group;
				}
			}
		}
	}
}

void Mission::SerializeBiEdi(std::ostream &out)
{
	out << "class _prefix_0" << std::endl << "{" << std::endl << "	objectType=\"prefix\";"
		<< std::endl << "	class Arguments" << std::endl << "	{" << std::endl
		<< "	};" << std::endl << "};" << std::endl;
	if(m_intel != NULL)
	{
		out << "class _intel_1" << std::endl
			<< "{" << std::endl
			<< "	objectType=\"intel\";" << std::endl
			<< "	class Arguments" << std::endl
			<< "	{" << std::endl
			<< "		OVERCAST=\"" << m_intel->m_dOvercast << "\";" << std::endl
			<< "		OVERCAST_WANTED=\"" << m_intel->m_dOvercastWanted << "\";" << std::endl
			<< "		FOG=\"" << m_intel->m_dFog << "\";" << std::endl
			<< "		FOG_WANTED=\"" << m_intel->m_dFogWanted << "\";" << std::endl
			<< "		YEAR=\"" << m_intel->m_year << "\";" << std::endl
			<< "		MONTH=\"" << (unsigned int)m_intel->m_month << "\";" << std::endl
			<< "		DAY=\"" << (unsigned int)m_intel->m_day << "\";" << std::endl
			<< "		HOUR=\"" << (unsigned int)m_intel->m_hour << "\";" << std::endl
			<< "		MINUTE=\"" << (unsigned int)m_intel->m_minute << "\";" << std::endl
			<< "	};" << std::endl
			<< "};"  << std::endl;
	}
}