#include <iostream>

class StringBuffer {

//private:
public:
	char* _strbuf;                                   //buffer to store the original string
	int _length;                                       //length of the string

public:
	StringBuffer();  //default constructor
	~StringBuffer();                //destructor; would delete the allocated buffer
	//StringBuffer(const StringBuffer&);              //constructor for shallow copying
	StringBuffer(char*, int);   //constructor to convert a char* to StringBuffer
	char charAt(int) const;   //returns the character at the passed index
	int length() const;                            //returns the length of the buffer
	void reserve(int);                             //allocates memory for the string, according to the passed character length
	void append(char);                          //appends a single character at the end

	void print() { // only for testing purposes

		for (int i = 0; i < _length; i++) {
			std::cout << _strbuf[i];
		}
		std::cout << std::endl;
		std::cout << "Length: " << _length << std::endl;
	}

};

StringBuffer::~StringBuffer() { //destructor; would delete the allocated buffer

	delete [] _strbuf;

}

StringBuffer::StringBuffer() {
	_strbuf = new char();
	_length = 0;
}

StringBuffer::StringBuffer(char* newString, int length){ //constructor to convert a char* to StringBuffer
	_strbuf = newString;
	_length = length;
}

char StringBuffer::charAt(int index) const { //returns the character at the passed index

	return _strbuf[index];

}

int StringBuffer::length() const { //returns the length of the buffer
	return _length;
}

void StringBuffer::reserve(int length) { //allocates memory for the string, according to the passed character length
	
	//if (_length >= 0) {
	//	delete [] _strbuf; // delete previous data, if there was, to prevent mem leak.
	//	_length = 0;
	//}
	
	//delete[] _strbuf; ?? not working...

	_strbuf = new char[length];
	_length = length; // garbage value in the end. Also, mem leak is present, since prev. data not deleted
}

void StringBuffer::append(char newChar) { //appends a single character at the end

	char* newString = new char[_length+1]; // make new string of length+1 (+1 for new char) 

	strcpy_s(newString, sizeof newString,_strbuf); // copy the data into _strbuf
	newString[_length] = newChar; // append new char
	delete [] _strbuf; // delete previous data
	_strbuf = newString; // assign pointer to new data (newString and _strbuf pointing to same!)
	_length++; // increment length

}

int main(void) {

	StringBuffer *newString = new StringBuffer();
	newString->print();

	std::cout << "Appending 'c'..." << std::endl;
	newString->append('c');
	newString->print();

	//newString->reserve(7);
	newString->print();

	

}