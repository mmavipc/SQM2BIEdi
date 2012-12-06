#pragma once
#include <string>

std::string SeekToPhrase(const std::string &strPhrase, std::istream &iStream);
std::string RemoveWhitespace(const std::string &str);
std::string StringReplace(std::string str, const std::string &strReplace, const std::string &strWith, unsigned int count = 0);