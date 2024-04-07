#pragma once
#include<iostream>
using namespace std;


class String {
	char* Data = nullptr;
	int len = 0;

public:
	
	String();
	String(const char* str);
	String(const String&);
	String(int x);
	char* getdata() const;

	// Sub - script Operators
	const char operator[](int i) const;

	// Arithmetic Operators
	String operator+(const String& str);
	String operator+(const char& str);
	String operator+(const char* str);

	String operator-(const String& substr);
	String operator-(const char& str);
	String operator-(const char* str);

	// Assignment Operators
	String& operator=(const String&);
	String& operator=(char*);

	// Logical Operators
	bool operator==(const String&) const;
	bool operator==(const char*) const;

	// Boolean Not Operator
	bool operator!(); 

	// Function-Call Operators	
	int operator()(char) const;
	int operator()(const String&) const;
	int operator()(const char*) const;

	operator int() const;	
	~String();
};
istream& operator>>(istream& input, String& str); 
ostream& operator<<(ostream& output, const String& str);

