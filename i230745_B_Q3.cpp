#include "i230745_B_Q3.h"

//Making a change
CourseIns::CourseIns(string key)
{
	name = key;
	Ins = new string[6]{};
}

CourseIns::~CourseIns()
{
	delete[] Ins;
	Ins = nullptr;
}

void CourseIns::operator+=(string name)
{
	if (this->name == "EXCEPTION-CASE")
		return;

	// Do not add name if it already exists
	for (int i = 0; i < this->Insnum; i++)
		if (Ins[i] == name)
			return;

	// if name is not already present
	// search for an empty slot and add name  
	for (int i = 0; i < 6; i++)
		if (Ins[i] == "")
		{
			Ins[i] = name;
			Insnum++;
			return;
		}

	// No Empty Slot found
	cout << "List-" << this->name << " Is Full\n";
}

void CourseIns::operator-=(string name)
{
	if (this->name == "EXCEPTION-CASE")
		return;

	// Search for name in Instructor-list
	// Remove it and decrement counter if found
	bool found = false;
	for (int i = 0; i < 6; i++)
		if (Ins[i] == name)
		{
			Ins[i] = "";
			Insnum--;
			found = true;
		}

	// Return if name is not found
	if (!found)
	{
		cout << name << " Does not exist in this list\n";
		return;
	}

	// Adjust Instructor-list to fill empty space
	string* New = new string[6]{};
	for (int i = 0, j = 0; i < 6; i++)
		if (Ins[i] != "")
		{
			New[j] = Ins[i];
			j++;
		}

	delete[] Ins;
	Ins = New;

}

void CourseIns::operator=(string name)
{
	(*this) += name;
}

string CourseIns::getCourseName() const
{
	return name;
}

string* CourseIns::getInsList() const
{
	return Ins;
}

int CourseIns::getInsNum() const
{
	return Insnum;
}




CAList::CAList():Exception(7)
{
	List[7] = new CourseIns("EXCEPTION-CASE");
}

CAList::~CAList()
{
	keynum = 0;
	for (int i = 0; i < 8; i++)
		delete List[i];
	
}

void CAList::AddKey(string keyname)
{
	// Case: Key-list is full
	if (keynum == 7)
	{
		// Call removeKey() to search for an empty key (key with no instructors) 
		// Delete the empty key, creating an empty key slot
		// Add the new key to this empty slot
		this->removeKey();
		for (int i = 6; i >= 0; i--)
			if (List[i] == nullptr)
			{
				List[i] = new CourseIns(keyname);
				keynum++;
				return;
			}

		// Return if removeKey() could not find any empty key
		cout << "Maximum keys (i.e 7) have already been assigned\n";
		return;
	}
	
	// Add a new key to the array of keys
	// Increment counter 
	this->List[keynum] = new CourseIns(keyname);
	this->keynum++;
}

CourseIns& CAList::operator[](string keyname)
{
	// Search for Key in C-List
	for (int i = 0; i < this->keynum ; i++)
		if (keyname == this->List[i]->getCourseName())
			return *(this->List[i]);

	// If not found create a new list
	this->AddKey(keyname);

	// Return Newly Added List
	for (int i = 0; i < this->keynum; i++)
		if (keyname == this->List[i]->getCourseName())
			return *(this->List[i]);
	
	// If All Keys Have Already Been Assigned Return A Dummy Object To Prevent Segmentation Fault
	return *List[Exception];
}

ostream& operator<<(ostream& output, CAList& ListObject)
{
	
	string str = "\n[ ";
	for (int i = 0; i < ListObject.keynum; i++)
	{
			str += ListObject.List[i]->getCourseName();
			str += " : { ";
			for (int j = 0; j < ListObject.List[i]->getInsNum(); j++)
			{
				str += ListObject.List[i]->getInsList()[j];

				if (j != ListObject.List[i]->getInsNum() - 1)
					str += ", ";
			}
			str += " },";
			if (i != ListObject.keynum - 1)
				str += "\n";
	}
	str += " ]\n";
	
	output << str;
	return output;
}

void CAList::operator=(CAList& B)	
{
	// Delete the content of the left CAlist
	for (int i = keynum - 1; i >= 0; i--)
	{
		delete this->List[i];
		this->List[i] = NULL;
	}
	this->keynum = 0;

	// Add the same Keys as the right List (B)
	for (int i = 0; i < B.keynum; i++)
		this->AddKey(B.List[i]->getCourseName());

	// Add the same instructors as the right key for each key
	for (int i = 0; i < this->keynum; i++)
		for (int j = 0; j < B.List[i]->getInsNum(); j++)
			(*this)[List[i]->getCourseName()] += B.List[i]->getInsList()[j];
}

CAList& CAList::operator+(CAList& B)
{
	// Call removKey() for both functions to remove empty keys
	this->removeKey();
	B.removeKey();

	// Create a Copy of the first CAlist (*this) 
	CAList* temp = new CAList;
	*temp = *this;

	// Add all those instructors/Keys which are not common
	for (int i = 0; i < B.keynum; i++)
		for (int j = 0; j < B.List[i]->getInsNum(); j++)
			(*temp)[B.List[i]->getCourseName()] += B.List[i]->getInsList()[j];

	// Return updated temp list
	return *temp;
}

CAList& CAList::operator-(CAList& B)
{
	// Call removKey() for both functions to remove empty keys
	this->removeKey();
	B.removeKey();

	// Create a Copy of the first CAlist (*this)
	CAList* temp = new CAList;
	*temp = *this;
	
	// find which keys are common among both CAlists
	// for each of these such keys remove all common instructors
	for (int i = 0; i < keynum; i++)
		for (int j = 0; j < B.keynum; j++)
			if (temp->List[i]->getCourseName() == B.List[j]->getCourseName())
				for (int k = 0; k < B.List[j]->getInsNum(); k++)
					(*temp)[List[i]->getCourseName()] -= B.List[j]->getInsList()[k];
		
	// Return Updated temp List
	temp->removeKey();
	return *temp;
}

void CAList::removeKey()
{
	
	CAList* temp = new CAList;
	int limit = keynum;
	bool EarlyReturn = true;
	
	// Search for Key with no instructors
	// If found delete it, and update keynum counter
	for (int i = 0; i < limit; i++)
		if (this->List[i]->getInsNum() == 0)
		{
			delete List[i];
			List[i] = NULL;
			keynum--;
			EarlyReturn = false;
		}

	// If no empty key is found then no point in executing the remaining code
	if (EarlyReturn)
		return;

	// If empty key was found and deleted, adjust the list to fill empty space creatd
	for (int i = 0, k = 0; i < 7; i++)
		if (List[i] != NULL)
		{
			temp->List[k] = List[i];
			List[i] = NULL;
			k++;
		}

	for (int i = 0; i < keynum; i++)
		List[i] = temp->List[i];
}