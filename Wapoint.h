#include <istream>
#include <ostream>

#include <string>
#include <vector>

class Group;

class Waypoint
{
	public:
		static std::vector<Waypoint*> DeserializeWaypoints(std::istream &in);
		Waypoint(Group *grp, unsigned short ID);
		void DeserializeSQM(std::istream &in);
		void SerializeBiEdi(std::ostream &out);
	private:
		Group *m_grp;

		unsigned short m_ID;
};