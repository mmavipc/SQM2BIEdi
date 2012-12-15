#pragma once
#include <istream>
#include <ostream>

#include <string>

class Vehicle
{
	public:
		Vehicle(unsigned short ID);
		void DeserializeSQM(std::istream &in);
		void SerializeBiEdi(std::ostream &out);
	private:
		unsigned short m_ID;

		double m_dX;
		double m_dY;
		double m_dZ;

		double m_dAzimuth;

		std::string m_strType;

		std::string m_strInit;

		std::string m_strLock;

		double m_dHealth;
		double m_dAmmo;
		double m_dFuel;
};