#pragma once
#include<iostream>
#include<cstring>
using namespace std;

class CIlist {
private:
    string* Inslist; // instructors storing list
    string course; // course name storing
    int count2; // counter for instructors
public:
    CIlist();
    CIlist(string str);
    ~CIlist(); // Destructor to deallocate memory
    string getCourse();
    void setCourse(string str);
    int getCount();
    string* getInslist();
    void operator+= (string str); // addition of new value
    void operator-= (string str); // elimination of a value
    void operator=(string str); // addition of new values there already value is not stored
};

class CAlist {
private:
    CIlist* Courselist[7]{}; // list of course name or keys
    int count1; // counter for courses
public:
    CAlist();
    ~CAlist(); // Destructor to deallocate memory
    CIlist* getCIlist();
    CIlist& operator[](string str); // creating new key
    void operator=(CAlist& course); // deep copy
    CAlist& operator+(CAlist& str); //union
    CAlist& operator-(CAlist& str); //difference
    friend ostream& operator<<(ostream& os, const CAlist& calist); //ouutput overloading
};