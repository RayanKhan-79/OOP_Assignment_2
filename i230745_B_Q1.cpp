#include "i230745_B_Q1.h"


Shop::Shop(const Shop& other)
{
	
	// Call add_Conatiner with the parameters of the other Shop
	// Repeat till nullptr of other shop is found
	this->start = nullptr;
	Container* ptr = other.start;
	while (ptr != nullptr)
	{
		this->add_Container(ptr->name, ptr->containerno);
		ptr = ptr->link;
	}
}

Shop::~Shop()
{
	// Go to the last non-NULL link and start deletion from there
	// move backwards and keep deleting till start is reached
	Container* ptr = nullptr;
	while (start->link != nullptr)
	{
		ptr = start;
		while (ptr->link->link != nullptr)
			ptr = ptr->link;

		delete[] ptr->link->name;
		delete ptr->link;
		ptr->link = nullptr;
	}

	// delete start
	if (start->link == nullptr)
	{
		delete[] start->name;
		delete start;
	}
}

void Shop::findContainer(int containerindex)
{
	
	Container* ptr = start;
	while (ptr != nullptr)
	{
		if (ptr->containerno == containerindex)
		{
			cout << ptr->name << "\n";
			return;
		}

		ptr = ptr->link;
	}

}

void Shop::findContainer(int containerindex1, int containerindex2)
{
	Container* ptr = start;
	while (ptr != nullptr)
	{
		if (ptr->containerno >= containerindex1 && ptr->containerno <= containerindex2)
		{
			cout << ptr->name << "\n";
		}

		ptr = ptr->link;
	}

}

void Shop::remove_Duplicate()
{
	Container* ptr = start;
	Container* S_ptr = start;
	Container* F_ptr = start->link;

	while (ptr->link != nullptr)
	{
		while (F_ptr != nullptr)
		{

			bool match = true;
			for (int i = 0; ptr->name[i] != '\0'; i++)
				if (ptr->name[i] != F_ptr->name[i])
				{
					match = false;
					break;
				}

			if (match && ptr->containerno == F_ptr->containerno)
			{
				S_ptr->link = F_ptr->link;
				delete[] F_ptr->name;
				delete F_ptr;
				F_ptr = S_ptr->link;
			}

			else
			{
				S_ptr = S_ptr->link;
				F_ptr = F_ptr->link;
			}
		}

		ptr = ptr->link;
		S_ptr = ptr;

		if (ptr != nullptr)
			F_ptr = ptr->link;
		
		else break;

	}
}

void Shop::Sort_Chain()
{

	int count = 0;
	for (Container* ptr = start; ptr != nullptr; ptr = ptr->link)
		count++;

	// create temporary arrays holding shop information in sorted order
	// S_ID will have the sorted container_numbers
	Container* temp = start;
	int* S_ID = new int[count] {};
	for (int i = 0; i < count; i++, temp = temp->link)
		S_ID[i] = temp->containerno;

	for (int i = 0; i < count; i++)
		for (int j = 0; j < count - 1; j++)
			if (S_ID[j] > S_ID[j + 1])
			{
				int temp = S_ID[j];
				S_ID[j] = S_ID[j + 1];
				S_ID[j + 1] = temp;
			}

	// list will have names of items sorted by their container_numbers present in S_ID
	temp = start;
	char** list = new char* [count];
	for (int i = 0; i < count; i++)
		for (Container* temp = start; temp != nullptr; temp = temp->link)
			if (S_ID[i] == temp->containerno)
			{
				list[i] = temp->name;
			}
	// reassign the shop object values based on this sorted order

	delete start;
	start = nullptr;
	for (int i = 0; i < count; i++)
		this->add_Container(list[i], S_ID[i]);

	delete[] list;
	delete[] S_ID;
}

void Shop::delete_Chain(int containerindex)
{
	Container* F_ptr = start->link;

	// Case 1 deletion at first conatiner,
	// Delete Start and reassign it to Fast_pointer (F_ptr)
	if (start->containerno == containerindex)
	{
		delete start;
		start = F_ptr;
	}

	// if start was the only container then return
	if (start == nullptr)
		return;

	// Case 2 deletion in the middle 
	// Fast pointer will find the container to be deleted first 
	// Slow pointer will point to the next container after Fast pointer
	// Delete Fast Pointer

	Container* ptr = start;
	F_ptr = ptr->link;
	while (ptr->link != nullptr)
	{

		while (F_ptr != nullptr && F_ptr->containerno != containerindex)
		{
			ptr = ptr->link;
			F_ptr = F_ptr->link;
		}

		if (F_ptr == nullptr)
			return;

		ptr->link = F_ptr->link;
		delete[] F_ptr->name;
		delete F_ptr;
		if (ptr != nullptr)
			F_ptr = ptr->link;
	}
}

void Shop::print_Shop()
{
	if (start == nullptr)
		return;

	Container* ptr = start;
	while (ptr != nullptr)
	{
		cout << ptr->name << "-" << ptr->containerno << "\n";
		ptr = ptr->link;
	}
}

void Shop::update_name_at_containerNumber(int index, char* newName)
{
	// traverse the list using temporary pointer ptr till NULL
	// when when parameter-index and containerno of a container match
	// assign new name using deep-copying
	Container* ptr = start;
	while (ptr != nullptr)
	{
		if (ptr->containerno == index)
		{
			int len = 0;
			while (newName[len] != '\0')
				len++;

			delete[] ptr->name;
			ptr->name = new char[len + 1] {};

			for (int i = 0; i < len; i++)
				(ptr->name)[i] = newName[i];

		}
		ptr = ptr->link;
	}
	
}

void Shop::add_Container(char* name, int containerindex)
{
	// If start is NULL make assign it a new container
	// assign this container the index and name
	if (start == nullptr)
	{
		start = new Container;
		start->containerno = containerindex;
		
		// name deep-copy assignmnet 
		int len = 0;
		while (name[len] != '\0')
			len++;

		start->name = new char[len + 1] {};

		for (int i = 0; i < len; i++)
			(start->name)[i] = name[i];
	}

	// If start has already been assigned a container
	// traverse through the list using a new pointer ptr starting form start
	// when ptr->link reaches NULL assign it the new container there and set values for name and index
	else
	{
		Container* ptr = start;
		while (ptr->link != nullptr)
			ptr = ptr->link;

		ptr->link = new Container;
		ptr->link->containerno = containerindex;
		
		// name deep-copy assignment
		int len = 0;
		while (name[len] != '\0')
			len++;

		ptr->link->name = new char[len + 1] {};

		for (int i = 0; i < len; i++)
			(ptr->link->name)[i] = name[i];

	}
};