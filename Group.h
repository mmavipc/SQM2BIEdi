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
		std::string GetSide();
	private:
		Center(std::string strSide);
		std::string m_strSide;
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