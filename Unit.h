#pragma once
#include <istream>
#include <ostream>

#include <string>

class Group;

class Unit
{
	public:
		Unit(Group *grp);
		void DeserializeSQM(std::istream &in);
		void SerializeBiEdi(std::ostream &out);
	private:
		double m_dX;
		double m_dY;
		double m_dZ;

		double m_dAzimuth;

		std::string m_strType;

		bool m_bPlayable;

		bool m_bLeader;

		std::string m_strRank;

		double m_dSkill;

		std::string m_strInit;
};