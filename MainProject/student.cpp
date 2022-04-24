#include "Header.h"
#include <fstream>
using namespace std;

void enrollCourse(Schoolyear* year, Course* course, int user, int& numOfOption) {
	int option;
	int i = user - 1;
	int j = user - 1;
	Course* courseEnroll = year->Class[i].student[j].enrolled;
	while (courseEnroll != NULL && courseEnroll->CourseNext != NULL) {
		courseEnroll = courseEnroll->CourseNext;
	}
	while (true) {
	enrollSession:
		Data* infoCourseCur = NULL;
		int numOfSubject = 1;
		Course* courseCur = course;
		viewCourse(courseCur, numOfSubject);
		numOfSubject--;
		cout << "Enter the no of the course you want to enroll in (input 0 to stop enroll): ";
		cin >> option;
		while (option > numOfSubject || option < 0) {
			cout << "Invalid input. Enter again: ";
			cin >> option;
			if (option == 0) {
				return;
			}
		}
		if (option == 0) {
			return;
		}
		int count = 1;
		while (courseCur != NULL && count != option) {
			courseCur = courseCur->CourseNext;
			count++;
		}
		if (courseCur != NULL) {
			Course* conflictEnroll = year->Class[i].student[j].enrolled;
			while (conflictEnroll != NULL) {
				if (conflictEnroll->Day1 == courseCur->Day1) {
					if (conflictEnroll->Session1 == courseCur->Session1) {
						cout << "The course you want to enroll in is conflicted with another course. Enter again!!!" << endl;
						goto enrollSession;
					}
				}
				if (conflictEnroll->Day2 == courseCur->Day2) {
					if (conflictEnroll->Session2 == courseCur->Session2) {
						cout << "The course you want to enroll in is conflicted with another course. Enter again!!!" << endl;
						goto enrollSession;
					}
				}
				conflictEnroll = conflictEnroll->CourseNext;
			}
			Data* dataOfStudent = courseCur->studentInfo;
			while (dataOfStudent != NULL && dataOfStudent->StudentID != year->Class[i].student[j].StudentID) {
				dataOfStudent = dataOfStudent->dataNext;
			}
			if (dataOfStudent == NULL && conflictEnroll == NULL) {
				if (courseCur->NumOfStu < courseCur->maxStu) {
					Data* tempData = new Data;
					tempData->indexClass = i;
					tempData->indexStu = j;
					tempData->StudentID = year->Class[i].student[j].StudentID;
					tempData->firstName = year->Class[i].student[j].firstName;
					tempData->lastName = year->Class[i].student[j].lastName;
					tempData->gender = year->Class[i].student[j].gender;
					tempData->dateOfBirth = year->Class[i].student[j].dateOfBirth;
					tempData->SocialID = year->Class[i].student[j].SocialID;
					tempData->dataNext = NULL;
					if (courseCur->studentInfo == NULL || courseCur->studentInfo->StudentID > tempData->StudentID) {
						tempData->dataNext = courseCur->studentInfo;
						courseCur->studentInfo = tempData;
					}
					else {
						infoCourseCur = courseCur->studentInfo;	
						while (infoCourseCur->dataNext != NULL && infoCourseCur->dataNext->StudentID < tempData->StudentID) {
							infoCourseCur = infoCourseCur->dataNext;
						}
						tempData->dataNext =infoCourseCur->dataNext;
						infoCourseCur->dataNext = tempData;
					}
					if (courseEnroll != NULL) {
						courseEnroll->CourseNext = new Course;
						courseEnroll = courseEnroll->CourseNext;
					}
					else {
						year->Class[i].student[j].enrolled = new Course;
						courseEnroll = year->Class[i].student[j].enrolled;
					}
					courseEnroll->CourseID = courseCur->CourseID;
					courseEnroll->CourseName = courseCur->CourseName;
					courseEnroll->StaffName = courseCur->StaffName;
					courseEnroll->NumOfCredit = courseCur->NumOfCredit;
					courseEnroll->Day1 = courseCur->Day1;
					courseEnroll->Session1 = courseCur->Session1;
					courseEnroll->Day2 = courseCur->Day2;
					courseEnroll->Session2 = courseCur->Session2;
					numOfOption++;
					courseCur->NumOfStu++;
					courseEnroll->NumOfStu = courseCur->NumOfStu;
					courseEnroll->CourseNext = NULL;
				}
				else {
					cout << "Your course your want to enroll is full of student. Please enter another course!!!" << endl;
					goto enrollSession;
				}

			}
			else {
				cout << "You have registerd this course. Please enter another course!!!" << endl;
				goto enrollSession;
			}
		}
	}
}

void removeCourseEnrolled(Schoolyear* year, Course* course, int user) {
	int i = user - 1;
	int j = user - 1;
	Data* infoCourseCur = NULL;
	Course* courseEnroll = year->Class[i].student[j].enrolled;
	Course* courseCur = course;
	if (courseEnroll == NULL) {
		return;
	}
	int option, numOfSubject = 1;
	viewCourse(courseEnroll, numOfSubject);
	numOfSubject--;
	cout << "Input num of the course to remove: ";
	cin >> option;
	Course* tempData = NULL;
	if (option == 1) {
		year->Class[i].student[j].enrolled = year->Class[i].student[j].enrolled->CourseNext;
		tempData = courseEnroll;
	}
	else {
		int count = 1;
		while (courseEnroll->CourseNext != NULL && count != option - 1) {
			courseEnroll = courseEnroll->CourseNext;
			count++;
		}
		if (courseEnroll->CourseNext != NULL) {
			tempData = courseEnroll->CourseNext;
			courseEnroll->CourseNext = tempData->CourseNext;
		}
	}
	while (courseCur != NULL && courseCur->CourseID != tempData->CourseID) {
		courseCur = courseCur->CourseNext;
	}
	delete tempData;
	if (courseCur != NULL) {
		infoCourseCur = courseCur->studentInfo;
		if (infoCourseCur->StudentID == year->Class[i].student[j].StudentID) {
			courseCur->studentInfo = courseCur->studentInfo->dataNext;
			delete infoCourseCur;
		}
		else {
			while (infoCourseCur->dataNext != NULL && infoCourseCur->dataNext->StudentID != year->Class[i].student[j].StudentID) {
				infoCourseCur = infoCourseCur->dataNext;
			}
			if (infoCourseCur->dataNext != NULL) {
				Data* temp = infoCourseCur->dataNext;
				infoCourseCur->dataNext = temp->dataNext;
				delete temp;
			}
		}
		courseCur->NumOfStu--;
		year->Class[i].student[j].numOfSubject--;
	}
	cout << "Remove course you enrolled succesfully!!!" << endl;
}

void viewListClasses(Schoolyear* year) {
	string schoolYear;
	cout << "Enter the year you want to view the list of classes: ";
	cin >> schoolYear;
	cout << endl;
	while (year != NULL) {
		if (schoolYear == year->schoolYear) {
			for (int i = 0; i < year->numOfClass; i++) {
				cout << i + 1 << "." << year->Class[i].nameOfClass;
				cout << endl;
			}
			break;
		}
		year = year->yearNext;
	}
	if (year == NULL) {
		cout << "Invalid input. The year you entered was not created!!!" << endl;
	}
}

void viewListStudentInClass(Schoolyear* year) {
	string nameClass;
	cout << "Enter the name of class you want to view list of students: ";
	cin >> nameClass;
	while (year != NULL) {
		for (int i = 0; i < year->numOfClass; i++) {
			if (nameClass == year->Class[i].nameOfClass) {
				int no = 1;
				int y = 16, a = 13;
				cout << endl;
				gotoxy(8, 15);
				cout << "No";
				gotoxy(a, 15);
				a = a + 15;
				cout << "Student ID";
				gotoxy(a, 15);
				a = a + 30;
				cout << "Full Name";
				gotoxy(a, 15);
				a = a + 10;
				cout << "Gender";
				gotoxy(a, 15);
				a = a + 22;
				cout << "Date of Birth";
				gotoxy(a, 15);
				cout << "Social ID";
				for (int j = 0; j < year->Class[i].numOfStudent; j++) {
					int x = 13;
					gotoxy(8, y);
					cout << no;
					gotoxy(x, y);
					x = x + 15;
					cout << year->Class[i].student[j].StudentID;
					gotoxy(x, y);
					x = x + 30;
					cout << year->Class[i].student[j].firstName << " " << year->Class[i].student[j].lastName;
					gotoxy(x, y);
					x = x + 10;
					cout << year->Class[i].student[j].gender;
					gotoxy(x, y);
					x = x + 22;
					cout << year->Class[i].student[j].dateOfBirth;
					gotoxy(x, y);
					cout << year->Class[i].student[j].SocialID;
					y = y + 1;
				}
				cout << endl << endl;
				return;
			}
		}
		year = year->yearNext;
	}
	if (year == NULL) {
		cout << "Invalid input. The name of class you entered was not created!!!" << endl;
	}
}

void viewListStudentInCourse(Schoolyear* year, int semester) {
	string courseID;
	cout << "Enter the course ID you want to view: ";
	cin >> courseID;
	Course* courseCur = year->semester[semester].course;
	while (courseCur != NULL) {
		if (courseID == courseCur->CourseID) {
			Data* dataCur;
			dataCur = courseCur->studentInfo;
			int no = 1;
			int y = 16, a = 13;
			cout << endl;
			gotoxy(8, 15);
			cout << "No";
			gotoxy(a, 15);
			a = a + 15;
			cout << "Student ID";
			gotoxy(a, 15);
			a = a + 30;
			cout << "Full Name";
			gotoxy(a, 15);
			a = a + 10;
			cout << "Gender";
			gotoxy(a, 15);
			a = a + 22;
			cout << "Date of Birth";
			gotoxy(a, 15);
			cout << "Social ID";
			while (no <= courseCur->NumOfStu) {
				int x = 13;
				gotoxy(8, y);
				cout << no;
				gotoxy(x, y);
				x = x + 15;
				cout << dataCur->StudentID;
				gotoxy(x, y);
				x = x + 30;
				cout << dataCur->firstName << " " << dataCur->lastName;
				gotoxy(x, y);
				x = x + 10;
				cout << dataCur->gender;
				gotoxy(x, y);
				x = x + 22;
				cout << dataCur->dateOfBirth;
				gotoxy(x, y);
				cout << dataCur->SocialID;
				y = y + 1;
				dataCur = dataCur->dataNext;
				no++;
			}
			cout << endl;
			return;
		}
		courseCur = courseCur->CourseNext;
	}
	if (courseCur == NULL) {
		cout << "Invalid input. The course ID you entered was not created!!!" << endl;
	}
}