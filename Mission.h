#pragma once //fuck you x-platformability, this is so much easier
#include <istream>
#include <ostream>
#include <vector>

#include "Intel.h"
#include "Group.h"
#include "Vehicle.h"

class Mission
{
	public:
		Mission();
		void DeserializeSQM(std::istream &in);
		void SerializeBiEdi(std::ostream &out);
	private:
		Intel *m_intel;
		std::vector<Group*> m_groups;
		std::vector<Vehicle*> m_vehicles;
};