#include "Header.h"
CIlist::CIlist() {
    Inslist = new string[6]{};
    count2 = 0; // Initialize count2 to 0
}

CIlist::CIlist(string str) {
    Inslist = new string[6]{};
    course = str;
    count2 = 0; // Initialize count2 to 0
}

CIlist::~CIlist() {
    delete[] Inslist;
    
}

string CIlist::getCourse() {
    return course;
}

void CIlist::setCourse(string str) {
    course = str;
}

int CIlist::getCount() {
    return count2;
}

string* CIlist::getInslist() {
    return Inslist;
}

void CIlist::operator+= (string str) {
    Inslist[count2] = str;
    count2++;
}

void CIlist::operator-= (string str) {
    for (int i = 0; i < count2; ++i) {
        if (Inslist[i] == str) {
            for (int j = i; j < count2 - 1; ++j) {
                Inslist[j] = Inslist[j + 1];
            }
            count2--;
            return;
        }
    }
}

void CIlist::operator= (string str) {
    bool found = false;
    for (int i = 0; i < count2; ++i) {
        if (Inslist[i] == str) {
            found = true;
            break;
        }
    }
    if (!found) {
        Inslist[count2] = str;
        count2++;
    }
}

CAlist::CAlist() {
    for (int i = 0; i < 7; ++i)
        Courselist[i] = nullptr;
    count1 = 0; // Initialize count1 to 0
}

CAlist::~CAlist() {
    for (int i = 0; i < count1; ++i) {
        delete Courselist[i];
        Courselist[i] = NULL;
    }
}

CIlist* CAlist::getCIlist() {
    return *Courselist; // Return first element of Courselist
}

CIlist& CAlist::operator[] (string str) {
    for (int i = 0; i < count1; ++i) {
        if (Courselist[i]->getCourse() == str) {
            return *Courselist[i];
        }
    }

    if (count1 < 7) {
        CIlist* newEntry = new CIlist(str);
        Courselist[count1] = newEntry;
        count1++;
        return *newEntry;
    }
    else {
        cout << "Error: Maximum number of keys reached (7 keys allowed)." << endl;
        // You should handle this error case properly, maybe throw an exception
    }
}

void CAlist::operator= (CAlist& course) {
   
    for (int i = 0; i < count1; ++i) {
        delete Courselist[i];
        Courselist[i] = NULL;
    }
    count1 = 0;
    for (int i = 0; i < course.count1; ++i) {
        for (int j = 0; j < course.Courselist[i]->getCount(); j++) {
            (*this)[course.Courselist[i]->getCourse()] += course.Courselist[i]->getInslist()[j];
        }

    }
}

CAlist& CAlist::operator+ (CAlist& calist) {
    CAlist* result = new CAlist;
    
    for (int i = 0; i < count1; ++i) {
        for (int j = 0; j < Courselist[i]->getCount(); ++j)
            (*result)[Courselist[i]->getCourse()] = Courselist[i]->getInslist()[j];
    }

    for (int i = 0; i < calist.count1; ++i) {
        for (int j = 0; j < calist.Courselist[i]->getCount(); j++)
            (*result)[calist.Courselist[i]->getCourse()] = calist.Courselist[i]->getInslist()[j];
    }
    return *result;
}

CAlist& CAlist::operator- (CAlist& calist) {
    CAlist* result = new CAlist;
    *result = *this;

    for (int i = 0; i < result->count1; i++)
    {
        for (int j = 0; j < calist.count1; j++)
        {
            if (result->Courselist[i]->getCourse() == calist.Courselist[j]->getCourse())
            {
                for (int k = 0; k < calist.Courselist[j]->getCount(); k++)
                    (*result)[Courselist[i]->getCourse()] -= calist.Courselist[j]->getInslist()[k];

                break;
            }
        }

    }

    return *result;
}

ostream& operator<< (ostream& os, const CAlist& calist) {
    os << "[ ";
    for (int i = 0; i < calist.count1; ++i) {
        os << calist.Courselist[i]->getCourse() << " : { ";
        for (int j = 0; j < calist.Courselist[i]->getCount(); ++j) {
            os << calist.Courselist[i]->getInslist()[j];
            if (j < calist.Courselist[i]->getCount() - 1)
                os << ", ";
        }
        os << " }";
        if (i < calist.count1 - 1)
            os << ", \n";
        
    }
    os << " ]";
    return os;
}