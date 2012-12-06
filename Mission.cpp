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
		strLine = RemoveWhitespace(strLine);
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
	}
}