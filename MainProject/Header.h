#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
using namespace std;

struct Staff
{
	string firstName, lastName, gender, email, user, pass;
};

struct Date
{
	string day, month, year;
};

struct Data
{
	string StudentID, firstName, lastName, gender, dateOfBirth, SocialID;
	int indexClass, indexStu;
	Data* dataNext;
};

struct Course
{
	Date startDate, endDate;
	string CourseID, CourseName, StaffName, NumOfCredit, Day1, Day2, Session1, Session2;
	int maxStu = 50, NumOfStu = 0;
	Course* CourseNext;
	Data* studentInfo = NULL; 
};

struct Student
{
	int numOfSubject; 
	string num, StudentID, firstName, lastName, gender, dateOfBirth, SocialID, pass;
	Course* enrolled = nullptr;
};

struct Class
{
	string nameOfClass = "";
	Student* student;
	int numOfStudent;
};

struct Semester
{
	Course* course = NULL;
	Date startDate, endDate;
};

struct Schoolyear
{
	Semester semester[3];
	string schoolYear = "";
	Class* Class;
	Schoolyear* yearNext;
	int numOfClass;
	Course courseRegis[3];
};

void gotoxy(int, int);

void inputAccount(string&, string&);

void loadAccountStaff(Staff*&, int&);

void loadAccountStu(Schoolyear*&);

bool checkUserStaff(string);

bool checkUserStudent(string);

int loginSystem(string, string, Schoolyear*&, Staff*, int);

void viewInfo(int, Schoolyear*, Staff*);

void changePass(int, Schoolyear*, Staff*, int);

void createNewYear(string);

void createNewClass(string, Class*&, int&);

void loadInfoStudent(Schoolyear*&);

bool checkDateSemester(Schoolyear*&, int&);

void createSemester(Schoolyear*&, int&);

bool checkDateRegis1(Schoolyear*&, int&);

bool checkDateRegis2(Schoolyear*&, int&);

bool checkDateRegis2(Schoolyear*&, int&);

void createCourseRegistration(Schoolyear*&, int&);

void addCourse(Course*&);

void viewCourse(Course*, int&);

void updateCourse(Schoolyear*, int);

void deleteCourse(Schoolyear*&, int);

void loadInfoCourse(Schoolyear*&, int&);

void saveInfoCourse(Course*&, string);

void enrollCourse(Schoolyear*, Course*, int, int&, string);

void viewListEnrollCourse(string);

void removeCourseEnrolled(Schoolyear*, Course*, int);

void viewListClasses(Class*&);

void viewListStudentInClass(Schoolyear*);

void viewListStudentInCourse(Schoolyear*, int);