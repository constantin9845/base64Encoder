#include <iostream>
#include <string>
#include <stdio.h>
#include <cmath>

const char base64Dictionary[] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
    '+', '/'
};

char ascii[] = {
        '\x00', '\x01', '\x02', '\x03', '\x04', '\x05', '\x06', '\x07', '\x08', '\x09', '\x0A', '\x0B', '\x0C', '\x0D', '\x0E', '\x0F',
        '\x10', '\x11', '\x12', '\x13', '\x14', '\x15', '\x16', '\x17', '\x18', '\x19', '\x1A', '\x1B', '\x1C', '\x1D', '\x1E', '\x1F',
        '\x20', '\x21', '\x22', '\x23', '\x24', '\x25', '\x26', '\x27', '\x28', '\x29', '\x2A', '\x2B', '\x2C', '\x2D', '\x2E', '\x2F',
        '\x30', '\x31', '\x32', '\x33', '\x34', '\x35', '\x36', '\x37', '\x38', '\x39', '\x3A', '\x3B', '\x3C', '\x3D', '\x3E', '\x3F',
        '\x40', '\x41', '\x42', '\x43', '\x44', '\x45', '\x46', '\x47', '\x48', '\x49', '\x4A', '\x4B', '\x4C', '\x4D', '\x4E', '\x4F',
        '\x50', '\x51', '\x52', '\x53', '\x54', '\x55', '\x56', '\x57', '\x58', '\x59', '\x5A', '\x5B', '\x5C', '\x5D', '\x5E', '\x5F',
        '\x60', '\x61', '\x62', '\x63', '\x64', '\x65', '\x66', '\x67', '\x68', '\x69', '\x6A', '\x6B', '\x6C', '\x6D', '\x6E', '\x6F',
        '\x70', '\x71', '\x72', '\x73', '\x74', '\x75', '\x76', '\x77', '\x78', '\x79', '\x7A', '\x7B', '\x7C', '\x7D', '\x7E', '\x7F',
        '\x80', '\x81', '\x82', '\x83', '\x84', '\x85', '\x86', '\x87', '\x88', '\x89', '\x8A', '\x8B', '\x8C', '\x8D', '\x8E', '\x8F',
        '\x90', '\x91', '\x92', '\x93', '\x94', '\x95', '\x96', '\x97', '\x98', '\x99', '\x9A', '\x9B', '\x9C', '\x9D', '\x9E', '\x9F',
        '\xA0', '\xA1', '\xA2', '\xA3', '\xA4', '\xA5', '\xA6', '\xA7', '\xA8', '\xA9', '\xAA', '\xAB', '\xAC', '\xAD', '\xAE', '\xAF',
        '\xB0', '\xB1', '\xB2', '\xB3', '\xB4', '\xB5', '\xB6', '\xB7', '\xB8', '\xB9', '\xBA', '\xBB', '\xBC', '\xBD', '\xBE', '\xBF',
        '\xC0', '\xC1', '\xC2', '\xC3', '\xC4', '\xC5', '\xC6', '\xC7', '\xC8', '\xC9', '\xCA', '\xCB', '\xCC', '\xCD', '\xCE', '\xCF',
        '\xD0', '\xD1', '\xD2', '\xD3', '\xD4', '\xD5', '\xD6', '\xD7', '\xD8', '\xD9', '\xDA', '\xDB', '\xDC', '\xDD', '\xDE', '\xDF',
        '\xE0', '\xE1', '\xE2', '\xE3', '\xE4', '\xE5', '\xE6', '\xE7', '\xE8', '\xE9', '\xEA', '\xEB', '\xEC', '\xED', '\xEE', '\xEF',
        '\xF0', '\xF1', '\xF2', '\xF3', '\xF4', '\xF5', '\xF6', '\xF7', '\xF8', '\xF9', '\xFA', '\xFB', '\xFC', '\xFD', '\xFE', '\xFF'
};


char* toCharArray(int length, std::string in){
	char *pA = new char[length];

	for(int i = 0; i < length; i++){
		pA[i] = in[i];
	}

	return pA;
}

int getASCII(char c){
	return int(c);
}

int* toAsciiArray(char* charArray, int len){
	int *pB = new int[len];

	for(int i = 0; i < len; i++){
		pB[i] = getASCII(charArray[i]);
	}

	return pB;
}

char* toBinArray(int* intArray, int len){
	char *pC = new char[len*8];

	int locationIndex=7;

	for(int i = 0; i < len; i++){
		int n = intArray[i];

		for(int j = locationIndex; j > locationIndex-8; j--){
			int digit = n%2;
			n = n/2;

			if(digit == 1){
				pC[j] = '1';
			}
			else{
				pC[j] = '0';
			}
		}

		locationIndex+=8;
	}

	return pC;
}

// SEGMENTATION ERROR
std::string toBase64(char* charArray, int len){
	std::string result = "";

	if(len < 24){
		std::cout<<"short "<<len;
	}
	else{
		int batch = 0;
		for(int i = 0; i < len; i+=24, batch++){
			if((len-i)<24){
				break;
			}
			for(int j = i; j < i+24; j+=6){
				
				int decimal = 0;
				int power = 5;
				for(int k = j; k<j+6; k++){

					if(charArray[k] == '1'){
						decimal += pow(2,power);
					}
					power--;
				}
				result += base64Dictionary[decimal];
			}
		}

		//Remaining bits after each full 24 bit batch
		int charsLeft = len-(batch*24);
		int pads = 4-(charsLeft/6)-1;

		for(int j = batch*24; j < j+charsLeft; j+=6){
			if((len-j)<6){
				break;
			}

			int decimal = 0;
			int power = 5;
			for(int k = j; k<j+6; k++){

				if(charArray[k] == '1'){
					decimal += pow(2,power);
				}
				power--;
			}

			result += base64Dictionary[decimal];
		}

		// left over bits that form character
		int remainingBitsIndex = (batch*24)+(charsLeft/6)*6;

		if(remainingBitsIndex != len){
			int decimal = 0;
			int power = 5;

			for(int j = remainingBitsIndex; j <len; j++){

				if(charArray[j] == '1'){
					decimal+=pow(2,power);
				}
				power--;
			}

			result += base64Dictionary[decimal];

			for(int j = 0; j < pads; j++){
				result+='=';
			}
		}

	}

	return result;

	//1. group every 24 bits (3x8)
	//2. divide each group into 4x6 bit sections
	//3. last 24 bit set --> might not have enough data to make 24 bits
	// 	--> for every missing 6 bit section --> add '=' to result
	//4. each ~6 chunk --> decimal
	//5. each decimal --> map to base64
}







//1. get text block as input ***

//2. store in char array ***

//4. encode each char to ascii value ***

//5. convert each value to binary --> each will be 8 bits ***

//6. divide whole thing in chunks of 6 bits

//3. fill up with special character to have len of array %3

//7. convert each chunk to decimal value

//8. map each number to base64 equivalent.


int main(int argc, char* argv[]){

	//USAGE: after compiling  --> main (g++ to64.cpp -o main)
	//		 ./main 

	std::string input = argv[1];

	int dataLen = input.size();

	char *A = toCharArray(dataLen, input);

	int* B = toAsciiArray(A, dataLen);

	delete[] A;
	A = nullptr;

	char* C = toBinArray(B, dataLen);
	dataLen = dataLen*8;

	delete[] B;
	B = nullptr;

	

	std::string result = toBase64(C, dataLen);

	std::cout<<"Base64: "<<std::endl;
	std::cout<<result<<std::endl;

	return 0;
}