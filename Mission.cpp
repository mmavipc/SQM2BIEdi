#include "Mission.h"
#include "StringFuncs.h"

Mission::Mission() : m_intel(NULL)
{
}

void Mission::DeserializeSQM(std::istream &in)
{
	//testing only
	SeekToPhrase("class Intel", in);
	Intel intel;
	intel.DeserializeSQM(in);
}