#include <iostream>

namespace A {
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
}
A::StringBuffer::~StringBuffer() { //destructor; would delete the allocated buffer

	delete[] _strbuf;

}

A::StringBuffer::StringBuffer() {
	_strbuf = new char();
	_length = 0;
}

A::StringBuffer::StringBuffer(char* newString, int length) { //constructor to convert a char* to StringBuffer
	_strbuf = newString;
	_length = length;
}

char A::StringBuffer::charAt(int index) const { //returns the character at the passed index


	if (_length == 0 || index >= _length || index < 0) {
		std::cout << "Invalid index accessed." << std::endl;
		return ' ';
		
	}
	else
		return _strbuf[index];

}

int A::StringBuffer::length() const { //returns the length of the buffer
	return _length;
}

void A::StringBuffer::reserve(int length) { //allocates memory for the string, according to the passed character length

	char* mystring = new char[_length + length];
	for (int i = 0; i < _length; i++)
	{
		mystring[i] = _strbuf[i];
	}
	//mystring[_length] = newChar;
	delete[] _strbuf;
	_strbuf = new char[_length + 1];
	_length+= length;
	for (int i = 0; i < _length; i++)
	{
		_strbuf[i] = mystring[i];
	}
	delete[] mystring;

}

void A::StringBuffer::append(char newChar) { //appends a single character at the end

	//_strbuf;
	//_length;

	char* mystring = new char[_length + 1];
	for (int i = 0; i < _length; i++)
	{
		mystring[i] = _strbuf[i];
	}
	mystring[_length] = newChar;
	delete[] _strbuf;
	_strbuf = new char[_length + 1];
	_length++;
	for (int i = 0; i < _length; i++)
	{
		_strbuf[i] = mystring[i];
	}
	delete[] mystring;

}

namespace B {
	class StringBuffer {

	};
}

int main(void) {

	A::StringBuffer *newString = new A::StringBuffer();
	newString->print();

	std::cout << "Appending 'c'..." << std::endl;
	newString->append('c');
	newString->print();
	newString->append('f');
	newString->print();
	newString->append('g');
	newString->print();
	newString->append('h');
	newString->print();
	newString->append('i');
	newString->print();
	std::cout << std::endl;
	std::cout << newString->charAt(0) << std::endl;
	std::cout << newString->charAt(1) << std::endl;
	std::cout << newString->charAt(2) << std::endl;
	std::cout << newString->charAt(3) << std::endl;
	std::cout << newString->charAt(4) << std::endl;
	std::cout << newString->charAt(5) << std::endl;

	
	std::cout << newString->_length << std::endl;
	newString->reserve(10);
	std::cout << newString->_length << std::endl;


}