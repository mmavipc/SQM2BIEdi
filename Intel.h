#pragma once
#include <istream>
#include <ostream>
class Intel
{
	friend class Mission;
	public:
		Intel();
		void DeserializeSQM(std::istream &in);
		void SerializeBiEdi(std::ostream &out);
	private:
		double m_dOvercast;
		double m_dOvercastWanted;
		double m_dFog;
		double m_dFogWanted;
		unsigned short m_year;
		unsigned char m_month;
		unsigned char m_day;
		unsigned char m_hour;
		unsigned char m_minute;
};