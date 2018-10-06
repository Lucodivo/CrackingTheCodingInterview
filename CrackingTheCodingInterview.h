#pragma once

typedef int32_t int32;
typedef int64_t int64;

typedef uint32_t uint32;
typedef uint64_t uint64;

#define ArrayCount(Array) (sizeof(Array) / sizeof((Array)[0]))

template<class T>
void swap(T & left, T & right) {
	T tmp = left;
	left = right;
	right = tmp;
}

void printRectMatrix(const uint32 * matrix, const uint32 numRows, const uint32 numCols) {
	for (int i = 0; i < numRows; ++i) {
		uint32 rowOffset = i * numCols;
		for (int colOffset = 0; colOffset < numCols; ++colOffset) {
			std::cout << *(matrix + rowOffset + colOffset) << "\t";
		}
		std::cout << std::endl;
	}
}

bool isSubstring(std::string fullString, std::string potentialSubString) {
	if (potentialSubString.length() > fullString.length()) {
		return false;
	}

	std::vector<uint32> potSubStringIndices;;
	for (uint32 i = 0; i < fullString.length(); ++i) {
		for (uint32 j = 0; j < potSubStringIndices.size();) {
			uint32 * subStringIndex = &potSubStringIndices[j];
			if (fullString[i] == potentialSubString[*subStringIndex]) {
				++*subStringIndex;
				if (*subStringIndex == potentialSubString.length()) {
					return true;
				}
				++j;
			}
			else {
				potSubStringIndices.erase(potSubStringIndices.begin() + j);
			}
		}
		if (fullString[i] == potentialSubString[0]) {
			potSubStringIndices.push_back(1);
		}
	}

	return false;
}