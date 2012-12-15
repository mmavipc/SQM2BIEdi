#pragma once
#pragma once
#include <istream>
#include <ostream>

#include <string>

class Marker
{
	public:
		Marker(unsigned short ID);
		void DeserializeSQM(std::istream &in);
		void SerializeBiEdi(std::ostream &out);
	private:
		unsigned short m_ID;

		double m_dX;
		double m_dY;
		double m_dZ;

		double m_dAngle;
		double m_dA;
		double m_dB;

		std::string m_strType;
		std::string m_strMarkerType;
		std::string m_strColor;
		std::string m_strFill;
		std::string m_strText;

		std::string m_strName;
};