#include "base64.h"


// string of text data --> base64
std::string base64::toBase64(const std::string& data){

	// create char array
	char* A = toCharArray(data.size(), data);

	// create ascii array
	int* B = toAsciiArray(A, data.size());

	delete[] A;
	A=nullptr;

	// create binary array
	std::vector<bool> C = toBinArray(B, data.size());

	delete[] B;
	B = nullptr;

	std::string result = toBase64(C, C.size());

	return result;
}

// string of binary numbers --> base64
std::string base64::binaryToBase64(const std::string& data){
	// create binary array
	std::vector<bool> C = toBinArray(data);

	std::string result = toBase64(C, C.size());

	return result;
}

// decode base64 to boolean vector
std::vector<bool> base64::bitsVector(const std::string& data){

	// base64 char to decimal number
	std::vector<int> A;

	for(int i = 0; i < data.size(); i++){
		int temp = toDecimal(data[i]);
		if(temp > 0){
			A.push_back(temp);
		}
	}

	//store bits of each decimal
	//remove 2 leading zeros of each number
	// if -1 --> padding
	// skips unknown characters
	std::vector<bool> B = toBinArray(A);

	return B;
}

// decode base64 to binary string
std::string base64::binaryString(const std::string& data){
	// base64 char to decimal number
	std::vector<int> A;

	for(int i = 0; i < data.size(); i++){
		int temp = toDecimal(data[i]);
		if(temp > 0){
			A.push_back(temp);
		}
	}

	//store bits of each decimal
	//remove 2 leading zeros of each number
	// if -1 --> padding
	// skips unknown characters
	std::vector<bool> B = toBinArray(A);

	std::string result = "";

	for(int i = 0; i < B.size(); i++){
		if(B[i] == true){
			result += '1';
		}
		else{
			result += '0';
		}
	}

	return result;
}

// decode to ascii text format
std::string base64::text(const std::string& data){
	// base64 char to decimal number
	std::vector<int> A(data.size());

	for(int i = 0; i < data.size(); i++){
		A[i] = toDecimal(data[i]);
	}

	//store bits of each decimal
	//remove 2 leading zeros of each number
	// if -1 --> padding
	// skips unknown characters
	std::vector<bool> B = toBinArray(A);

	// form decimal numbers from each 8 bit section
	std::vector<int> C = toDecimal(B);

	// form original text from ascii table;
	std::string result = toText(C);

	return result;
}


int base64::toDecimal(char n){
	const char base64Dictionary[] = {
	    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 
	    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 
	    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 
	    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 
	    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
	    '+', '/'
	};

	for(int i = 0; i < 64; i++){
		if(base64Dictionary[i] == n){
			return i;
		}

		if(n == '='){
			return -1;
		}
	}

	return -2;
}

// to decimal from 8 bit binary
// check for when size of B is not multiple of 8
std::vector<int> base64::toDecimal(const std::vector<bool>& B){

	std::vector<int> C;
	int index = 0;

	for(int i = 0; i < B.size(); i+=8){

		int power = 0;
		int decimal = 0;

		for(int j = i+7; j>=i; j--){
			if(B[j] == true){
				decimal += pow(2,power);
			}
			power++;
		}
		if(decimal != 0){
			C.push_back(decimal);
		}
		
		index++;
	}
	return C;
}

std::string base64::toText(const std::vector<int>& C){
	std::string result = "";

	for(int i = 0; i < C.size(); i++){
		result+=char(C[i]);
	}

	return result;
}

char* base64::toCharArray(int length, std::string in){
	char *pA = new char[length];

	for(int i = 0; i < length; i++){
		pA[i] = in[i];
	}

	return pA;
}

int base64::getASCII(char c){
	return int(c);
}

int* base64::toAsciiArray(const char* charArray, int len){
	int *pB = new int[len];

	for(int i = 0; i < len; i++){
		pB[i] = getASCII(charArray[i]);
	}

	return pB;
}

std::vector<bool> base64::toBinArray(int* intArray, int len){

	std::vector<bool> pC(len*8);

	int locationIndex=7;

	for(int i = 0; i < len; i++){
		int n = intArray[i];

		for(int j = locationIndex; j > locationIndex-8; j--){
			int digit = n%2;
			n = n/2;

			if(digit == 1){
				pC[j] = true;
			}
			else{
				pC[j] = false;
			}
		}

		locationIndex+=8;
	}

	return pC;
}

//  removes 2 leading zeros
std::vector<bool> base64::toBinArray(const std::vector<int>& B){

	std::vector<bool> pC(B.size()*6);

	int locationIndex=5;

	for(int i = 0; i < B.size(); i++){
		int n = B[i];

		if(n <= 0){
			continue;
		}

		for(int j = locationIndex; j > locationIndex-6; j--){
			int digit = n%2;
			n = n/2;

			if(digit == 1){
				pC[j] = true;
			}
			else{
				pC[j] = false;
			}
		}


		locationIndex+=6;
	}

	return pC;
}

std::vector<bool> base64::toBinArray(std::string data){

	std::vector<bool> pC(data.size());

	for(int i = 0; i < data.size(); i++){
		if(data[i] == '1'){
			pC[i] = true;
		}
		else{
			pC[i] = false;
		}
	}

	return pC;
}

std::string base64::toBase64(const std::vector<bool>& pC, int len){
	std::string result = "";

	const char base64Dictionary[] = {
	    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 
	    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 
	    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 
	    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 
	    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
	    '+', '/'
	};

	int batch = 0;
	for(int i = 0; i < len; i+=24, batch++){
		if((len-i)<24){
			break;
		}
		for(int j = i; j < i+24; j+=6){
			
			int decimal = 0;
			int power = 5;
			for(int k = j; k<j+6; k++){

				if(pC[k] == true){
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

			if(pC[k] == true){
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

			if(pC[j] == true){
				decimal+=pow(2,power);
			}
			power--;
		}

		result += base64Dictionary[decimal];

		for(int j = 0; j < pads; j++){
			result+='=';
		}
	}

	return result;

}