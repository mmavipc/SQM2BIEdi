// SQM2BIEdi.cpp : Defines the entry point for the console application.
//

#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

#include "Mission.h"

class MyBuf : public std::streambuf
{
	private:
		std::fstream fout;
	public:
		MyBuf() : std::streambuf(), fout()
		{
			fout.open("mission.biedi", std::ios_base::out | std::ios_base::trunc);
		}
		~MyBuf()
		{
			std::cout.flush();
			fout.close();
		}
	protected:
		virtual traits_type::int_type overflow(traits_type::int_type c = traits_type::eof())
		{
			if(c != EOF)
			{
				std::cout << (char)c;
				fout << (char)c;
			}
			return 0;
		}

		virtual std::streamsize xsputn ( const char * s, std::streamsize n )
		{
			std::cout.write(s, n);
			fout.write(s, n);
			return n;
		}
};

int main(int argc, char* argv[])
{
	Mission mis;

	std::fstream inFile;
	inFile.open("mission.sqm", std::ios_base::in);

	mis.DeserializeSQM(inFile);
	std::ostream os(new MyBuf());
	mis.SerializeBiEdi(os);//std::cout for testing purposes
	os.flush();
	return 0;
}