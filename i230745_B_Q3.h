#pragma once
#include<string>
#include<iostream>
using namespace std;


class CourseIns {

	string* Ins = nullptr;
	string name = "";
	int Insnum = 0;

public:
	CourseIns(string key);
	~CourseIns();

	string getCourseName() const;
	string* getInsList() const;
	int getInsNum() const;

	void operator+=(string name);
	void operator=(string name);
	void operator-=(string name);

};

class CAList
{
	CourseIns* List[8]{};
	int keynum = 0;
	const int Exception;
	
	void removeKey();
	void AddKey(string keyname); 
	
public:
	CAList();
	~CAList();

	CourseIns& operator[](string keyname);
	void operator=(CAList& oprnd);
	CAList& operator+(CAList& oprnd);
	CAList& operator-(CAList& oprnd);
	friend ostream& operator<<(ostream& output, CAList& ListObject);
};


/*

temp:

[0]->OOP->  Dr.ALi   Ms.Hida   Mr.Shams 
[1]->DLD->  Mr.Amir   Mr.Shams 
[2]->ALGO->  Mr.Owais
[3]->PAK-STD->  Mr.Ajmal   Ms.Gul   Ms.Memoona
[4]->ISL->  Dr.Tayab   Ms.Sobia   Mr.Usman   Ms.Gul   Mr.Anas

oprnd:

[0]->ALGO->  Mr.Owais
[1]->OOP->  Mr.Shehryar   Mr.Jahaz   Dr.Ali
[2]->PAK-STD->  Mr.Ajmal   Ms.Gul   Ms.Memoona
[3]->ISL->  Dr.Tayab   Ms.Sobia   Mr.Usman   Ms.Gul   Mr.Anas










int main()
{
	// assume CAList is the name of class

	CAList tt, tt2, tt3; 	
	
	// operator[] is used to get "entry" against given "key" from CAList and
	// can be used in following context with operator= to create/refresh an entry
	
	tt["OOP"] = "Dr.Ali";
	tt["OOP"] = "Mr.Shehryar";
	tt["OOP"] = "Ms.Hida";
	tt["OOP"] = "Mr.Shams";
	tt["DLD"] = "Mr.Amir";
	tt["DLD"] = "Mr.Shams";
	tt["DLD"] = "Dr.Mehwish";
	cout<<tt; 
	//output should look like: 
	[ OOP : { Dr.Ali,Mr.Shehryar ,Ms.Hida,Mr.Shams},
	DLD : { Mr.Amir,Mr.Shams,Dr.Mehwish } ]

	// operator+= with an "entry" is used to add new "value" against a given "key".
	// if entry with given "key" does not exist then new entry is created in
	CAList.
	
	// Following operators += and = perform the same operation
	tt2["Algo"] = "Mr.Owais";
	tt2["OOP"] = "Mr.Shehryar";
	tt2["Pak Stds"] = "Mr.Ajmal";
	tt2["Pak Stds"] += "Ms.Gul";
	tt2["Pak Stds"] = "Ms.Memoona";
	tt2["Islamiat"] = "Dr.Tayab";
	tt2["Islamiat"] += "Ms.Sobia";
	tt2["Islamiat"] = "Mr.Usman";
	tt2["Islamiat"] += "Ms.Gul";
	tt2["Islamiat"] += "Mr.Anas";

	// following statement creates a new entry in CAList, and then adds
	values to it
	// operator+ is also used to add two (CAList)s and return a new CAList.
	// operator= is used to assign one List to another(deep copy).
	
	tt3 = tt + tt2; 
	// tt3 now looks like the CAList in figure above! (same as set union operation)
	// At this stage tt, tt2, and tt3 look like following respectively:
	
	tt:

	[ OOP : { Dr.Ali, Mr.Shehryar,Ms.Hida,Mr.Shams},
	DLD : { Mr.Amir,Mr.Shams,Dr.Mehwish } ]

	tt2:

	[ Algo : { Mr.Owais },
	OOP : {Mr.Shehryar },
	Pak Stds : { Mr.Ajmal,Ms.Gul,Ms.Memoona} ,
	Islamiat : { Dr.Tayab,Ms.Sobia,Mr.Usman,Ms.Gul,Mr.Anas }]

	tt3:

	[ OOP : { Dr.Ali, Mr.Shehryar,Ms.Hida,Mr.Shams},
	DLD : { Mr.Amir,Mr.Shams,Dr.Mehwish },
	Algo : {Mr.Owais },
	Pak Stds : { Mr.Ajmal,Ms.Gul,Ms.Memoona} ,
	Islamiat : { Dr.Tayab,Ms.Sobia,Mr.Usman,Ms.Gul,Mr.Anas }]

	//This Operation will work similar to the set difference operation
	tt4 = tt - tt2; 
	
	tt4 :

	[OOP:{ Dr.Ali, Ms.Hida, Mr.Shams},
	DLD : { Mr.Amir, Mr.Shams, Dr.Mehwish }] 

	return 0;
	}

*/