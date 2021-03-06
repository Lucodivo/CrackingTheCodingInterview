#include <iostream>
#include <climits>
#include <string>
#include <vector>
#include <stdint.h>

#include "CrackingTheCodingInterview.h"
#include "Chapter1ArraysAndStrings.h"

int main()
{
	std::string fullString = "potential";
	std::string rot = "ntialpote";
	std::cout << "Full string: " << fullString << std::endl;
	std::cout << "Potential rotation: " << rot << std::endl;

	if (isStringRotation(fullString, rot)) {
		std::cout << "It is a rotation.\n";
	}
	else {
		std::cout << "It is NOT a rotation.\n";
	}
}