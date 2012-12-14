// SQM2BIEdi.cpp : Defines the entry point for the console application.
//

#include <fstream>
#include <iostream>
#include <string>

#include "Mission.h"

int main(int argc, char* argv[])
{
	Mission mis;

	std::fstream inFile;
	inFile.open("mission.sqm", std::ios_base::in);

	mis.DeserializeSQM(inFile);
	mis.SerializeBiEdi(std::cout);//std::cout for testing purposes
	return 0;
}