//
// Created by alpat on 05.05.2023.
//
#include "utils.h"

namespace utils
{
	std::vector<std::string> SplitString(const std::string& sText, const std::string& sSplitPattern)
	{
		std::vector<std::string> substrings;

		size_t szStart = 0;
		size_t szEnd   = sText.find(sSplitPattern);
		while (szEnd != std::string::npos)
		{
			substrings.push_back(sText.substr(szStart, szEnd - szStart));

			szStart = szEnd + sSplitPattern.size();
			szEnd   = sText.find(sSplitPattern, szStart);
		}
		substrings.push_back(sText.substr(szStart));

		return substrings;
	}
}
