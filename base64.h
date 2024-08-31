#include <iostream>
#include <string>
#include <stdio.h>
#include <cmath>
#include <vector>

class base64{

public:

	// Encode a string of text to base64
	// returns a string in base64
	static std::string toBase64(const std::string& data);

	// Takes a string representing a binary number
	// encodes to base64
	// returns in string format
	static std::string binaryToBase64(const std::string& data);

	// Decode base64 data in string format to a vector representing 
	// binary format with a boolean vector
	// returns boolean vector
	static std::vector<bool> bitsVector(const std::string& data);

	// Decode base64 to binary string
	// returns a string that contains the binary number
	// returns string
	static std::string binaryString(const std::string& data);

	// Decode base64 to text (ASCII)
	// returns string
	static std::string text(const std::string& data);

private:
	// string to char array
	static char* toCharArray(int length, std::string in);

	// return ascii value of character
	static int getASCII(char c);

	// return array of ascii values from character array
	static int* toAsciiArray(const char* charArray, int len);

	// converts integer array to binary array represented with a boolean vector
	static std::vector<bool> toBinArray(int* intArray, int len);

	// converts string to binary array represented with a boolean vector
	static std::vector<bool> toBinArray(std::string data);

	// converts integer vector to binary array represented with a boolean vector
	static std::vector<bool> toBinArray(const std::vector<int>& B);

	// converts binary array to base64 character
	// group by 6 bits --> one base64 character
	// add remaining character
	// add padding w/ '='
	static std::string toBase64(const std::vector<bool>& pC, int len);

	// character to decimal
	static int toDecimal(char n);

	// convert binary array to integer array
	// return integer vector
	static std::vector<int> toDecimal(const std::vector<bool>& B);

	// convert character array to string
	// return string
	static std::string toText(const std::vector<int>& C);
};