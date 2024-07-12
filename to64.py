
def toBinary(x):
	binNumber = ""
	temp = x

	while temp != 0:
		r = temp%2
		temp = temp/2

		if r != 0:
			binNumber = "1"+binNumber
			print(binNumber)
		else:
			binNumber = "0"+binNumber
			print(binNumber)

	t = "0b"+binNumber
	binNumber = t
	return binNumber


base64_chars = [
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
    '+', '/'
]


test = "Heyy"
padding = len(test)%3

while len(test)%3 != 0:
	test += "="

print(test)
asciiChars = []

inBytes = bytes(test, 'ascii')
for i in inBytes:
	asciiChars.append(i)

print(toBinary(1))