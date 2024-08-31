# Base 64 Encoder

A c++ library to convert text/binary data to base64 and reverse.

## Usage

The library has five available functions for the user

```java
// Convert string to base64
std::string B = "test string";

std::string result1 = base64::toBase64(B);
```

```java
// Takes a string representing a binary number 
// Converts to base64
std::string C = "0111010001100101011100110111010000100000011100110111010001110010011010010110111001100111";

std::string result2 = base64::binaryToBase64(C);
```

```java
// Convert base64 string to a boolean vector
// represent the data in binary 
std::vector<bool> decode1 = base64::bitsVector(result1);
```

```java
// Convert base64 string to text in binary format
std::string decode2 = base64::binaryString(result1);
```

```java
// Convert base64 string to text format
std::string decode3 = base64::text(result1);
```

## Additional guidelines

Invalid characters in base64 data will be skipped in conversion to text
-No errors

## Example

```java
#include "base64.h"

int main(){

  std::string B = "test string";

  std::string result1 = base64::toBase64(B);

  std::cout<<"From text: "<<result1<<std::endl;


  std::string decode3 = base64::text(result1);

  std::cout<<"From 64 to ascii text: "<<decode3<<std::endl;

  return 0;
}
```

```output
From text: dGVzdCBzdHJpbmc=

From 64 to ascii text: test string
```


