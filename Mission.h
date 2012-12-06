#pragma once //fuck you x-platformability, this is so much easier
#include <istream>
#include <ostream>

#include "Intel.h"
class Mission
{
	public:
		Mission();
		void DeserializeSQM(std::istream &in);
	private:
		Intel *m_intel;
};