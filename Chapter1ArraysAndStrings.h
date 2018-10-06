#pragma once

// 1.1 Is Unique
// Implement an algorithm to determine if a string has all unique characters.
bool allUniqueChars(const std::string & a) {
	// string must repeat if length is > # of available unique chars
	if (a.length() > UCHAR_MAX) return false;

	bool charInString[UCHAR_MAX] = { 0 };

	for (uint32 i = 0; i < a.length(); ++i) {
		if (charInString[a[i]]) return false;
		charInString[a[i]] = true;
	}

	return true;
}

// 1.1.2 Is Unique (pt 2)
//  What if you cannot use additional data structures?
bool allUniqueChars_NoDataStructure(const std::string & a) {
	// string must repeat if length is > # of available unique chars
	if (a.length() > UCHAR_MAX) return false;

	uint64 charInString = 0;
	for (uint32 i = 0; i < a.length(); ++i) {
		uint64 charAsChoppedAsciiIndex = 1 << (a[i] - 'A');
		if ((charInString & charAsChoppedAsciiIndex) > 0) return false;
		charInString = charInString | charAsChoppedAsciiIndex;
	}

	return true;
}

//const string stringA = "Hello World";
//const string stringB = "Just once";
//
//cout << "StringA: " << stringA << endl;
////cout << "StringB: " << stringB << endl;
//if (allUniqueChars_NoDataStructure(stringA)) {
//	cout << "That string had all unique characters.\n";
//}
//else {
//	cout << "That string had repeated characters.\n";
//}

// 1.2 Check Permutations
// Given two strings, write a method to decide if one is a permutation of the other.
bool arePermutations(const std::string & a, const std::string & b) {
	uint32 aLength = a.length();
	uint32 bLength = b.length();

	if (aLength != bLength) return false;

	int32 stringACharCount[UCHAR_MAX] = { 0 };

	for (uint32 i = 0; i < aLength; ++i) {
		++stringACharCount[a[i]];
	}

	for (uint32 i = 0; i < bLength; ++i) {
		--stringACharCount[b[i]];
		if (stringACharCount[b[i]] < 0) return false;
	}

	return true;
}

//const string stringA = "Hello World";
//const string stringB = "World Hello";
//
//cout << "StringA: " << stringA << endl;
//cout << "StringB: " << stringB << endl;
//if (arePermutations(stringA, stringB)) {
//	cout << "These strings are permutations.\n";
//}
//else {
//	cout << "These string are not permutations.\n";
//}

// 1.3 URLify
// Write a method to replace all spaces in a string with '%20'.
// You may assume that the string has sufficient space at the end
// to hold additional characters, and that you are given the 'true'
// length of the string.
void replaceSpacesWithURLEncoding(std::string & a) {
	if (a.length() == 0) return;

	uint32 endOfString = a.length() - 1;
	uint32 endOfWords = endOfString;
	while (a[endOfWords] == ' ') {
		--endOfWords;
	}

	while (endOfString != endOfWords) {
		if (a[endOfWords] == ' ') {
			a[endOfString--] = '0';
			a[endOfString--] = '2';
			a[endOfString--] = '%';
			endOfWords--;
		}
		else {
			a[endOfString--] = a[endOfWords--];
		}
	}
}

//string stringA = "Mr John Smith    ";
//
//cout << "StringA: " << stringA << endl;
//replaceSpacesWithURLEncoding(stringA);
//cout << "StringA (URL encoded): " << stringA << endl;

// 1.4 Pallindrome Permutation
// Given a string, write a function to check if it is a permutation of a palindrome. 
// A palindrome is a word or phrase that is the same forwards and backwards. 
// A permutation is a rearrangement of letters. 
// The palindrome does not need to be limited to just dictionary words.
bool isPallindromePermutation(const std::string & a) {
	uint32 oddCount = 0;
	bool oddCountInString[UCHAR_MAX] = { 0 };

	uint32 numChars = a.length();
	for (uint32 i = 0; i < a.length(); ++i) {
		if (a[i] == ' ') {
			--numChars;
			continue;
		}

		oddCountInString[a[i]] = !oddCountInString[a[i]];
		if (oddCountInString[a[i]]) {
			++oddCount;
		}
		else {
			--oddCount;
		}
	}

	bool stringIsEven = (numChars % 2) == 0;
	if ((stringIsEven && oddCount == 0) ||
		(!stringIsEven && oddCount == 1)) {
		return true;
	}

	return false;
}

//string stringA = "contznotc";
//
//cout << "StringA: " << stringA << endl;
//replaceSpacesWithURLEncoding(stringA);
//if (isPallindromePermutation(stringA)) {
//	cout << "StringA is a permutation of a pallindrome.\n";
//}
//else {
//	cout << "StringA is NOT a permutation of a pallindrome.\n";
//}

// 1.5 One Away
// There are three types of edits that can be performed on strings:
// insert a character, remove a character, or replace a character.
// Given two strings, write a function to check if they are one edit
// (or zero edits) away.
bool oneEditAway(std::string a, std::string b) {

	if (b.length() > a.length()) {
		swap(a, b);
	}

	int lengthDiff = a.length() - b.length();
	if (lengthDiff == 1) { // insert/remove
		bool singleDiff = false;
		for (uint32 i = 0; i < a.length(); ++i) {
			uint32 j = i - int(singleDiff);
			if (a[i] != b[j]) {
				if (singleDiff) return false;
				singleDiff = true;
			}
		}
	}
	else if (lengthDiff == 0) { // replace character
		bool singleDiff = false;
		for (uint32 i = 0; i < a.length(); ++i) {
			if (a[i] != b[i]) {
				if (singleDiff) return false;
				singleDiff = true;
			}
		}
	}
	else {
		return false;
	}

	return true;
}

//string stringA = "contznotc";
//string stringB = "contznatc";
//
//cout << "stringA: " << stringA << std::endl;
//cout << "stringB: " << stringB << std::endl;
//if (oneEditAway(stringA, stringB)) {
//	cout << "The strings are one edit away! \n";
//}
//else {
//	cout << "The strings are NOT one edit away! \n";
//}

// 1.6 String Compression
// Implement a method to perform basic string compression using the counts of repeated characters.
// For example, the string aabcccccaaa would become a2b1c5a3. If the "compressed" string would not
// become smaller than the original string, your method should return the original string. You can
// assume the string has only uppercase and lowercase letters (a-z).
std::string stringCompression(const std::string & a) {
	if (a.length() < 3) {
		return a;
	}

	const uint32 uniqueLimit = a.length() / 2;
	char * compressedChars = new char[uniqueLimit];
	char * compressedCount = new char[uniqueLimit];

	compressedChars[0] = a[0];
	compressedCount[0] = 1;
	uint32 compressedIndex = 0;
	for (uint32 i = 1; i < a.length(); ++i) {
		if (a[i] == compressedChars[compressedIndex]) {
			++compressedCount[compressedIndex];
		}
		else {
			++compressedIndex;
			if (compressedIndex >= uniqueLimit) {
				return a;
			}
			compressedChars[compressedIndex] = a[i];
			compressedCount[compressedIndex] = 1;
		}
	}

	std::string compressedString((compressedIndex * 2) + 3, '\0');
	for (int i = 0; i <= compressedIndex; ++i) {
		compressedString[i * 2] = compressedChars[i];
		compressedString[(i * 2) + 1] = '0' + compressedCount[i];
	}

	delete compressedChars;
	delete compressedCount;

	return compressedString;
}

//string stringA = "aaaaaabbbbbcccccabab";
//string stringB = "abcacbacbacbacbacccc";
//
//cout << "stringA: " << stringA << std::endl;
//cout << "Compressed: " << stringCompression(stringA) << std::endl;
//cout << "stringB: " << stringB << std::endl;
//cout << "Compressed: " << stringCompression(stringB) << std::endl;

// 1.7 Rotate Matrix
// Given an image represented by an NxN matrix, where each pixel in the image is
// 4 bytes, write a method to rotate the image by 90 degrees.
void rotateSquareMatrix(uint32 * matrix, const uint32 dimen) {
	const uint32 matrixLength = dimen * dimen;
	uint32 * tmpMatrix = new uint32[matrixLength];
	std::copy(matrix, matrix + matrixLength, tmpMatrix);

	for (int i = 0; i < dimen; ++i) {
		uint32 rowOffset = i * dimen;
		for (int colOffset = 0; colOffset < dimen; ++colOffset) {
			uint32 replacementValue = *(tmpMatrix + (dimen * (dimen - colOffset - 1)) + i);
			*(matrix + rowOffset + colOffset) = replacementValue;
		}
	}

	delete tmpMatrix;
}

// 1.7.2 Rotate Matrix
// Can you do this in place?
void rotateSquareMatrixInPlace(uint32 * matrix, const uint32 dimen) {
	for (uint32 startColAndRow = 0; startColAndRow < (dimen / 2); ++startColAndRow) {
		uint32 endCol = dimen - 1 - startColAndRow;
		for (uint32 col = startColAndRow; col < endCol; col++) {
			uint32 upperLeftOffset = (startColAndRow * dimen) + col;
			uint32 upperRightOffset = (col * dimen) + endCol;
			uint32 lowerRightOffset = (dimen * (dimen - startColAndRow)) - 1 - col;
			uint32 lowerLeftOffset = ((dimen - col - 1) * dimen) + startColAndRow;

			uint32 tmp = *(matrix + upperLeftOffset);
			swap(tmp, *(matrix + upperRightOffset));
			swap(tmp, *(matrix + lowerRightOffset));
			swap(tmp, *(matrix + lowerLeftOffset));
			*(matrix + upperLeftOffset) = tmp;
		}
	}
}

//const uint32 dimen = 5;
//uint32 matrix[dimen][dimen] = {
//	{0,1,2,3,4},
//	{5,6,7,8,9},
//	{10,11,12,13,14},
//	{15,16,17,18,19},
//	{20,21,22,23,24}
//};
//rotateSquareMatrixInPlace((uint32 *)matrix, dimen);
//printRectMatrix((uint32 *)matrix, dimen, dimen);

// 1.8 Zero Matrix
// Write an algorithm such that if an element in an MxN matrix is 0, it's entire row and column are set to 0.
void zeroMatrix(uint32 * matrix, uint32 numRows, uint32 numCols) {

	bool * zeroRows = new bool[numRows]();
	bool * zeroCols = new bool[numCols]();

	for (uint32 i = 0; i < numRows; ++i) {
		uint32 rowOffset = i * numCols;
		for (uint32 j = 0; j < numCols; ++j) {
			if (*(matrix + rowOffset + j) == 0) {
				zeroRows[i] = true;
				zeroCols[j] = true;
			}
		}
	}

	for (uint32 i = 0; i < numRows; ++i) {
		uint32 rowOffset = i * numCols;
		for (uint32 j = 0; j < numCols; ++j) {
			if (zeroRows[i] || zeroCols[j]) {
				*(matrix + rowOffset + j) = 0;
			}
		}
	}

	delete zeroRows;
	delete zeroCols;
}

//const uint32 numRows = 4;
//const uint32 numCols = 5;
//uint32 matrix[numRows][numCols] = {
//	{0,1,2,3,4},
//	{5,6,7,8,9},
//	{10,11,0,13,14},
//	{15,16,17,3,19}
//};
//zeroMatrix((uint32 *)matrix, numRows, numCols);
//printRectMatrix((uint32 *)matrix, numRows, numCols);

// 1.9 String Rotationo
// Assume you have a method isSubstring which checks if one words is a substring
// of another. Given two strings, s1 and s2, write code to check if s2 is a rotation
// of s1 using only one call to isSubstring (e.g. "waterbottle" is a rotation of "erbottlewat").
bool isStringRotation(std::string s1, std::string s2) {
	if (s1.length() != s2.length()) {
		return false;
	}

	s1.append(s1);
	return isSubstring(s1, s2);
}

//std::string fullString = "potential";
//std::string rot = "ntialpote";
//std::cout << "Full string: " << fullString << std::endl;
//std::cout << "Potential rotation: " << rot << std::endl;
//
//if (isStringRotation(fullString, rot)) {
//	std::cout << "It is a rotation.\n";
//}
//else {
//	std::cout << "It is NOT a rotation.\n";
//}