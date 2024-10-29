	#include "StudentList.h"

	// Define a constructor to initialize the list. The list starts with no Students
    StudentList::StudentList() {
	head = nullptr;
    tail = nullptr;
    numStudents = 0;
	}

	// return the number of students currently in the list
	int StudentList::listSize() {
		return numStudents;
	}

	//add a Node with a student to the front (head) of the list.
	void StudentList::addFront(Student s) {
		Node* newNode = new Node(s);
    if (numStudents == 0) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    numStudents++;
	}

	//add a Node with a student to the back (tail) of the list.
	void StudentList::addBack(Student s) {
		Node* newNode = new Node(s);
    if (numStudents == 0) {
        head = tail = newNode;
    } else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    numStudents++;
	}

	//Print out the names of each student in the list.
	void StudentList::printList() {
		Node* temp = head;
    while (temp != nullptr) {
        cout << "Name: " << temp->data.name << ", ID: " << temp -> data.id << ", GPA: " <<temp->data.GPA<<endl;
        temp = temp->next;
    }
	}

	// Remove the Node with the student at the back (tail) of the list
	// should not fail if list is empty! Print an error message if this occurs
	// Don't forget that your head and tail pointers will be null pointers if the list is empty
	void StudentList::popBack() {
		 if (numStudents == 0) return; 
    if (numStudents == 1) {
        delete tail; 
        head = tail = nullptr;
    } else {
        Node* temp = tail;
        tail = tail->prev;
        delete temp; 
        tail->next = nullptr; 
    }
    numStudents--; 
    }
    
	// Remove the Node with the student at the front (head) of the list
	// should not fail if list is empty! Print an error message if this occurs
	// Don't forget that your head and tail pointers will be null pointers if the list is empty
	void StudentList::popFront() {
		 if (numStudents == 0) return; 
    if (numStudents == 1) {
        delete head; 
        head = tail = nullptr;
    } else {
        Node* temp = head;
        head = head->next;
        delete temp; 
        head->prev = nullptr; 
    }
    numStudents--; 
}
	

	//insert a student at the position "index".
	// for this list, count head as index 0
	// if index is outside of current list range, 
	// print a message and insert the student at the back of the list
	// the previous Node at your target index should be moved forward. "For exampe, Node with student at index i, becomes index i+1" 
	// Remember that you already have methods that can add students to the front or back of list if needed! Don't repeat this code.
	void StudentList::insertStudent(Student s, int index) {
		 if (index < 0 || index > numStudents) return; 
    if (index == 0) {
        addFront(s); 
        return;
    }
    if (index == numStudents) {
        addBack(s); 
        return;
    }
    Node* newNode = new Node(s);
    Node* temp = head;
    for (int i = 0; i < index - 1; i++) {
        temp = temp->next; 
    }
    newNode->next = temp->next; 
    newNode->prev = temp;
    temp->next->prev = newNode; 
    temp->next = newNode; 
    numStudents++;
	}

	//find the student with the given id number and return them
	// if no student matches, print a message 
	// and create and return a dummy student object
	Student StudentList::retrieveStudent(int idnumber) {
		Node* temp = head;
    while (temp != nullptr) {
        if (temp->data.id == idnumber) {
            return temp->data; 
        }
        temp = temp->next; 
    }
    return Student();
	}

	// Remove a Node with a student from the list with a given id number
	// If no student matches, print a message and do nothing
	void StudentList::removeStudentById(int idnumber) {
		Node* temp = head;
    while (temp != nullptr) {
        if (temp->data.id == idnumber) {
            if (temp->prev) {
                temp->prev->next = temp->next; 
            } else {
                head = temp->next; 
            }
            if (temp->next) {
                temp->next->prev = temp->prev; 
            } else {
                tail = temp->prev; 
            }
            delete temp; 
            numStudents--; 
            return;
        }
        temp = temp->next; 
    }
	}

	//Change the gpa of the student with given id number to newGPA
	void StudentList::updateGPA(int idnumber, float newGPA) {
		Node* temp = head;
    while (temp != nullptr) {
        if (temp->data.id == idnumber) {
            temp->data.GPA = newGPA; 
            return;
        }
        temp = temp->next; 
    }
	}

	//Add all students from otherList to this list.
	//otherlist should be empty after this operation.
	/*
	For example, if the list has 3 students:
	s1 <-> s2 <-> s3
	and otherList has 2 students
	s4 <-> s5
	then after mergeList the currently list should have all 5 students
	s1 <-> s2 <-> s3 <-> s4 <-> s5
	and otherList should be empty and have zero students.
	*/
	void StudentList::mergeList(StudentList &otherList) {
		if (otherList.numStudents == 0) return; 
    if (numStudents == 0) {
        head = otherList.head; 
        tail = otherList.tail;
    } else {
        tail->next = otherList.head;
        otherList.head->prev = tail; 
        tail = otherList.tail; 
    }
    numStudents += otherList.numStudents; 
    otherList.head = otherList.tail = nullptr;
	}

	//create a StudentList of students whose gpa is at least minGPA.
	//Return this list.  The original (current) list should
	//not be modified (do not remove the students from the original list).
	StudentList StudentList::honorRoll(float minGPA) {
		StudentList honorList;
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data.GPA >= minGPA) {
            honorList.addBack(temp->data); 
        }
        temp = temp->next; 
    }
    return honorList;
	}
