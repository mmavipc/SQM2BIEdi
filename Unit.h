#pragma once
#include <istream>
#include <ostream>

class Group;

class Unit
{
	public:
		Unit(Group *grp);
		void DeserializeSQM(std::istream &in);
		void SerializeBiEdi(std::ostream &out);
};