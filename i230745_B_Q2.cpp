#include "i230745_B_Q2.h"

String::String() 
{
	Data = nullptr;
	len = 0;
};

String::String(const char* str)
{
	while (str[len] != '\0')
		len++;

	Data = new char[len + 1] {};
	for (int i = 0; i < len; i++)
		Data[i] = str[i];
}

String::String(const String& ref)
{
	len = ref.len;
	Data = new char[len + 1] {};

	for (int i = 0; i < len; i++)
		Data[i] = ref.Data[i];
}

String::String(int x)
{
	Data = new char[x + 1] {};
	len = 0;
}

String::~String()
{
	delete[] Data;
}

char* String::getdata() const
{
	return Data;
}

const char String::operator[](int i) const
{
	if (i < 0)
		return Data[len + i ];

	else
		return Data[i];
}

String String::operator+(const String& str)
{
	
	String* temp = new String(*this);
	delete[] this->Data;
	this->Data = new char[temp->len + str.len + 1] {};

	for (int i = 0; i < temp->len; i++)
		this->Data[i] = temp->Data[i];

	for (int i = temp->len, j = 0; j < str.len; j++, i++)
		this->Data[i] = str.Data[j];

	this->len = temp->len + str.len;
	
	delete temp;
	return *this;
}

String String::operator+(const char& str)
{
	String* temp = new String(*this);
	delete[] this->Data;
	this->len++;
	this->Data = new char[this->len + 1] {};

	for (int i = 0; i < this->len - 1; i++)
		this->Data[i] = temp->Data[i];

	this->Data[this->len - 1] = str;

	delete temp;
	return *this;
}

String String::operator+(const char* str)
{
	String temp(str);
	return (*this + temp);
}

String String::operator-(const char& str)
{
	// count the number of times str is repeated *this
	int count = 0;
	for (int i = 0; i < len; i++)
		if (this->Data[i] == str)
			count++;

	// use temp to temporarily store data of *this
	String temp(*this);
	delete[] this->Data;

	// Assign *this the new length after removing the repeated characters
	// Copy content of temp back into *this but skipping any instances of str
	this->len = len - count;
	this->Data = new char[len + 1] {};
	for (int i = 0, j = 0; i < temp.len; i++)
		if (temp.Data[i] != str)
		{
			this->Data[j] = temp.Data[i];
			j++;
		}

	return *this;
}

String String::operator-(const String& substr)
{
	
	for (int i = 0; i < this->len; i++)
	{
		bool flag = true;
		for (int j = 0; j < substr.len; j++)
			if (this->Data[j + i] != substr.Data[j])
			{
				flag = false;
				break;
			}

		if (flag)
			for (int k = i; k < i + substr.len; k++)
				this->Data[k] = '#';
	}

	*this - '#';

	return *this;

}

String String::operator-(const char* str)
{
	String temp(str);
	return (*this - temp);

}

String& String::operator=(const String& str)
{

	delete[] this->Data;

	this->len = str.len;
	this->Data = new char[len + 1] {};
	
	for (int i = 0; i < len; i++)
		this->Data[i] = str.Data[i];

	return *this;
}

String& String::operator=(char* str)
{
	String temp(str);
	return (*this = temp);
}

bool String::operator==(const String& ref) const
{
	// Check String length 
	if (this->len != ref.len)
		return false;

	// Check String char by char
	for (int i = 0; i < this->len; i++)
		if (this->Data[i] != ref.Data[i])
			return false;

	return true;
}

bool String::operator==(const char* ref) const
{
	String test(ref);
	return (*this == test);
}

bool String::operator!()
{
	for (int i = 0; i < len; i++)
		if (this->Data[i] != '\0')
			return false;

	return true;
}

int String::operator()(char ref) const
{
	for (int i = 0; i < len; i++)
		if (this->Data[i] == ref)
			return i;

	return -1;
}

int String::operator()(const String& ref) const
{
	for (int i = 0; i < len; i++)
	{
		bool found = true;
		for (int j = 0; j < ref.len; j++)
			if (this->Data[i + j] != ref.Data[j])
			{
				found = false;
				break;
			}

		if (found)
			return i;
	}

	return -1;
}

int String::operator()(const char* ref) const
{
	String temp(ref);
	return (*this)(temp);
}

String::operator int() const
{
	return len;
}

ostream& operator<<(ostream& output, const String& str)
{
	if (str.getdata() != nullptr)
		output << str.getdata() << '\n';

	else
		output << "";
	return output;
}

istream& operator>>(istream& input, String& str)
{
	char* temp = new char[600] {};
	input >> temp;
	String tempo(temp);
	delete[] temp;

	str = tempo;
	
	
	return input;
}