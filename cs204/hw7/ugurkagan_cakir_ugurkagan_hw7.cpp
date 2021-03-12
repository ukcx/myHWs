
//Name: Ugur Kagan Cakir

#include <iostream>
#include <string>

using namespace std;

unsigned char PermuteTheUnsignedChar (unsigned char c)		//this function rearranges the bits in char in a special order
{
	unsigned char index_7 = (c << 1) & 0x80;		
	unsigned char index_6 = (c << 2) & 0x40;		
	unsigned char index_5 = (c >> 2) & 0x20;		//each char represents only 1 bit of the result char
	unsigned char index_4 = (c >> 1) & 0x10;		//other than the index numberth bit, all bits are 0 for these chars
	unsigned char index_3 = (c << 1) & 0x08;
	unsigned char index_2 = (c << 2) & 0x04;
	unsigned char index_1 = (c >> 2) & 0x02; 
	unsigned char index_0 = (c >> 1) & 0x01;

	unsigned char result = (index_0 + index_1 + index_2 + index_3 + index_4 + index_5 + index_6 + index_7);//resulted char has ith bit of each index_i char 

	return result;			
}

int main()
{
	string key, plain_text;						//plain text is the text to be encrypted, key is used in encryption process

	cout << "*** Welcome to the Simple Data Encryption Application ***" << endl;
	cout << "Please enter the encryption key: ";
	getline(cin,key);							//key is taken with all chars including blank char

	cout << "Please enter the plaintext to be encrypted: ";

	while(getline(cin, plain_text))				//plain text is taken with all chars including blank char
	{
		unsigned char c;

		cout << "Ciphertext: " ;
		for(int i = 0; i < plain_text.size(); i++)
		{
			c = plain_text[i];
			c = PermuteTheUnsignedChar(c);			//c's bits are rearranged
			c = c ^ key [i % key.size()];			//XOR operation between c and key's corresponding character
			cout << hex << (int)c;					//since c is unsigned char, there is no value lose while converting to int
		}

		cout << "\n\n";		
		cout << "Please enter the plaintext to be encrypted: ";
	}
	
	return 0;
}