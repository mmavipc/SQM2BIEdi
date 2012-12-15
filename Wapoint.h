#include <istream>
#include <ostream>

#include <string>
#include <vector>

class Group;

class Waypoint
{
	public:
		static std::vector<Waypoint*> DeserializeWaypoints(std::istream &in, Group *group);
		Waypoint(Group *grp, unsigned short ID);
		void DeserializeSQM(std::istream &in);
		void SerializeBiEdi(std::ostream &out);
	private:
		Group *m_grp;

		unsigned short m_ID;

		double m_dX;
		double m_dY;
		double m_dZ;

		std::string m_strCombatMode;
		std::string m_strFormation;
		std::string m_strSpeed;
		std::string m_strCombat;
		std::string m_strShowWP;
		std::string m_strType;
};