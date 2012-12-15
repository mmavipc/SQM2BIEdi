#pragma once
#include <vector>
#include <istream>
#include <ostream>
#include <string>

class Unit;
class Waypoint;

class Center
{
	public:
		static Center* GetCenter(std::string strSide);
		static const std::vector<Center*> GetCenters();
		std::string GetSide();
		const unsigned short GetID();
	private:
		Center(std::string strSide, unsigned short id);
		std::string m_strSide;
		unsigned short m_id;
};

class Group
{
	public:
		Group(unsigned short ID);
		void DeserializeSQM(std::istream &in);
		void SerializeBiEdi(std::ostream &out);
		const unsigned short GetID();
	private:
		std::vector<Unit*> m_units;
		std::vector<Waypoint*> m_waypoints;
		unsigned short m_ID;
		Center* m_center;
};