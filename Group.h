#pragma once
#include <vector>
#include <istream>
#include <ostream>
#include <string>

class Unit;

class Center
{
	public:
		static Center* GetCenter(std::string strSide);
		static const std::vector<Center*> GetCenters();
		std::string GetSide();
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
	private:
		std::vector<Unit*> m_units;
		unsigned short m_ID;
		Center* m_center;
};