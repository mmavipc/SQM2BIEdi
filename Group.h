#pragma once
#include <vector>
#include <istream>
#include <ostream>

class Unit;

class Group
{
	public:
		Group(unsigned short ID);
		void DeserializeSQM(std::istream &in);
		void SerializeBiEdi(std::ostream &out);
	private:
		std::vector<Unit*> m_units;
		unsigned short m_ID;
};