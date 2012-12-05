#pragma once
#include <istream>
#include <ostream>
#include <string>
class Intel
{
	public:
		void DeserializeSQM(std::istream &in);
		void SerializeBiEdi(std::ostream &out);
	private:
		double dOvercast;
		double dOvercastWanted;
		double dFog;
		double dFogWanted;
		unsigned short year;
		unsigned char month;
		unsigned char day;
		unsigned char hour;
		unsigned char minute;
};