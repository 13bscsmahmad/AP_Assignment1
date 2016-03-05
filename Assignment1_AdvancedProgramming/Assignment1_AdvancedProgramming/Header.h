#pragma once


# define _CRT_SECURE_NO_WARNINGS

#include <iostream>

namespace copied {
	class StringBuffer {

	private:
		char * _strbuf;
		int _length;
		int _bufsize;

	public:
		StringBuffer();
		~StringBuffer();
		StringBuffer(const StringBuffer&);
		StringBuffer(char*, int);
		char charAt(int) const;
		int length() const;
		void reserve(int);
		void append(char);

		/* Operater Overloading*/
		StringBuffer& operator= (const StringBuffer& that);


	};

	StringBuffer::StringBuffer() {
		_length = -1;
		_strbuf = NULL;
		_bufsize = -1;
	}

	StringBuffer::StringBuffer(char* charArray, int length) {

		_strbuf = charArray;
		_length = length;
		_bufsize = length;

	}

	StringBuffer::~StringBuffer() {
		if (_strbuf != NULL) {
			//cout << "Deleting strbuf " << &_strbuf;
			delete[] _strbuf;
		}
	}

	StringBuffer::StringBuffer(const StringBuffer& that) {

		std::cout << "Going into copy constructor..." << std::endl;

		// deep copy

		this->_strbuf = new char[that._bufsize];
		this->_bufsize = that._bufsize;
		this->_length = that._length;

		for (int i = 0; i < that.length(); i++) {
			this->_strbuf[i] = that._strbuf[i];
		}



	}

	char StringBuffer::charAt(int index) const {

		if (index >= 0 && index < _length) {
			return _strbuf[index];
		}
		throw "AccessNotAllowedException";
	}

	int StringBuffer::length() const {

		// returns -1 if not initialized
		return _length;
	}

	void StringBuffer::reserve(int size) {
		if (_strbuf != NULL) {
			delete[] _strbuf;
		}

		_strbuf = new char[size];
		_length = 0;
		_bufsize = size;
	}


	void StringBuffer::append(char c) {

		// check buffer size before appending

		if (_length < _bufsize) {
			_strbuf[_length] = c;
			_length++;
		}
		else {

			std::cout << "Buffer size too small. Resizing buffer..." << std::endl;

			StringBuffer newStringBuffer;
			newStringBuffer.reserve(_bufsize + _bufsize);
			//newStringBuffer._bufsize = _bufsize+_bufsize; // double the buffer size
			//newStringBuffer._length = _length + 1; // increase length because appending character

			for (int i = 0; i < _length; i++)
			{
				newStringBuffer.append(_strbuf[i]);
			}
			newStringBuffer.append(c);

			// delete old

			delete[] _strbuf;


			_length = 0;

			_bufsize += _bufsize; // double the bufsize
			_strbuf = new char[_bufsize];


			for (int i = 0; i < newStringBuffer._length; i++)
			{
				_strbuf[i] = newStringBuffer._strbuf[i];
				_length++;
			}



		}


	}

	StringBuffer& StringBuffer::operator= (const StringBuffer& that) {

		std::cout << "Going into overloading func..." << std::endl;

		if (this != &that) {
			this->_strbuf = new char[that._bufsize];
			this->_bufsize = that._bufsize;

			for (int i = 0; i < that.length(); i++) {
				this->_strbuf[i] = that._strbuf[i];
			}

			this->_length = that._length;
		}

		return *this;
	}

}

namespace refcount {

	class StringBuffer {
	public:
		StringBuffer();  //default constructor
		~StringBuffer();                //destructor; would delete the allocated buffer
		StringBuffer(const StringBuffer&);              //constructor for shallow copying
		StringBuffer(char*, int);   //constructor to convert a char* to StringBuffer
		char charAt(int) const;   //returns the character at the passed index
		int length() const;                            //returns the length of the buffer
		void reserve(int);                             //allocates memory for the string, according to the passed character length
		void append(char);                          //appends a single character at the end
		int* _refcount;
	private:
		char* _strbuf;                                   //buffer to store the original string
		int _length;                                       //length of the string
	};

	StringBuffer::StringBuffer() {

		_strbuf = nullptr;
		_length = 0;
		_refcount = new int;
		*_refcount = 1;

	}

	StringBuffer::~StringBuffer() { // destructor

									//check for refcount value
		if (*_refcount == 1) {
			*_refcount = 0;
			delete[] _strbuf;
			delete[] _refcount;
		}
		else {
			*_refcount--;
		}

	}

	StringBuffer::StringBuffer(const StringBuffer& that) {

		// increase _refcount
		*_refcount++;

		// shallow copy
		std::cout << "Going into copy constructor..." << std::endl;

		// deep copy

		this->_strbuf = new char[that._length];
		this->_length = that._length;


		for (int i = 0; i < that.length(); i++) {
			this->_strbuf[i] = that._strbuf[i];
		}

	}

	StringBuffer::StringBuffer(char* receivedChar, int length) {

		this->_strbuf = receivedChar;
		this->_length = length;

	}

	char StringBuffer::charAt(int index) const {

		if (index >= 0 && index < _length) {
			return _strbuf[index];
		}
		throw "AccessNotAllowedException";

	}

	int StringBuffer::length() const {
		return _length;
	}

	void StringBuffer::reserve(int size) {
		if (_strbuf != NULL) {
			delete[] _strbuf;
		}

		_strbuf = new char[size];
		_length = size;

	}

	void StringBuffer::append(char c) {

		// Implement COW if *_refcount > 1

		if (*_refcount == 1) {
			_strbuf[_length] = c;
		}
		else {
			*_refcount--;
			_refcount = new int();


			// copy data

			char* temp = new char[_length];
			strncpy(temp, _strbuf, _length);
			_strbuf = new char[_length];
			strncpy(_strbuf, temp, _length);
			_strbuf[_length] = c;
			_length++;

			delete[] temp;

		}

	}
}

namespace owned {

	class StringBuffer {

	public:
		StringBuffer();  //default constructor
		~StringBuffer();                //destructor; would delete the allocated buffer
		StringBuffer(const StringBuffer&);              //constructor for shallow copying
		StringBuffer(char*, int);   //constructor to convert a char* to StringBuffer
		char charAt(int) const;   //returns the character at the passed index
		int length() const;                            //returns the length of the buffer
		void reserve(int);                             //allocates memory for the string, according to the passed character length
		void append(char);                          //appends a single character at the end

		mutable bool owner;
	private:
		char* _strbuf;                                   //buffer to store the original string
		int _length;                                       //length of the string
		int _bufsize;
	};

	StringBuffer::StringBuffer() {
		_strbuf = nullptr;
		_length = 0;
		_bufsize = 0;
		// owner = true at reserve()
	}

	StringBuffer::StringBuffer(char* charArray, int length) {

		_strbuf = charArray;
		_length = length;
		_bufsize = length;

	}

	void StringBuffer::reserve(int size) {
		if (_strbuf != NULL) {
			delete[] _strbuf;
		}

		_strbuf = new char[size];
		_bufsize = size;

		owner = true;

	}

	StringBuffer::~StringBuffer() {

		// Only delete if owner. Else, leave it as it is.

		if (_strbuf != NULL && owner) {

			delete[] _strbuf;
		}
	}

	StringBuffer::StringBuffer(const StringBuffer& that) {

		std::cout << "Going into copy constructor..." << std::endl;

		// deep copy

		this->_strbuf = new char[that._length];
		this->_length = that._length;


		for (int i = 0; i < that.length(); i++) {
			this->_strbuf[i] = that._strbuf[i];
		}

		// steal ownership

		if (that.owner) {
			that.owner = false;
		}

		this->owner = true;

	}

	int StringBuffer::length() const {
		return _length;
	}

	char StringBuffer::charAt(int index) const {

		if (index >= 0 && index < _length) {
			return _strbuf[index];
		}
		throw "AccessNotAllowedException";

	}

	void StringBuffer::append(char c) {

		_strbuf[_length] = c;
		_length++;

	}


}

