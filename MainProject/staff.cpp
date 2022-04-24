#include "Header.h"
#include <string>
#include <fstream>
#include <windows.h>
#include <conio.h>
using namespace std;

void gotoxy(int x, int y) {
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

void inputAccount(string& username, string& password) {
	cout << "Enter your username: ";
	cin >> username;
	cout << "Enter your password: ";
	cin >> password;
	cout << endl;
}

void loadInfoStaff(Staff*& staff, int& numOfStaff) {
	ifstream fin("StaffAccount.csv");
	string temp;
	getline(fin, temp, ',');
	numOfStaff = stoi(temp);
	staff = new Staff[stoi(temp)];
	getline(fin, temp);
	for (int i = 0; i < numOfStaff; i++) {
		getline(fin, staff[i].firstName, ',');
		getline(fin, staff[i].lastName, ',');
		getline(fin, staff[i].gender, ',');
		getline(fin, staff[i].email, ',');
		getline(fin, staff[i].user, ',');
		getline(fin, staff[i].pass);
	}
}

bool checkUserStaff(string username) {
	for (int i = 0; i < username.size(); i++) {
		if (username[i] < 'a' || username[i] > 'z') {
			return false;
		}
	}
	return true;
}

bool checkUserStudent(string username) {
	for (int i = 0; i < username.size(); i++) {
		if ((username[i] <= 48 || username[i] >= 57) && username.size() != 8) {
			return false;
		}
	}
	return true;
}

int loginSystem(string username, string password, Schoolyear*& year, Staff* staff, int numOfStaff) {
	if (checkUserStaff(username)) {
		for (int i = 0; i < numOfStaff; i++) {
			if (username == staff[i].user && password == staff[i].pass) {
				cout << "Log in successfully!!!" << endl;
				cout << "Hello " << staff[i].firstName << " " << staff[i].lastName << "!!!" << endl;
				cout << "Welcome you to my course tragistation system!!!" << endl << endl;
				return -(i + 1);
			}
		}
	}
	else if (checkUserStudent(username)) {
		for (int i = 0; i < year->numOfClass; i++) {
			for (int j = 0; j < year->Class[i].numOfStudent; j++) {
				if (username == year->Class[i].student[j].StudentID && password == year->Class[i].student[j].pass) {
					cout << "Log in successfully!!!" << endl;
					cout << "Hello " << year->Class[i].student[j].firstName << " " << year->Class[i].student[j].lastName << "!!!" << endl;
					cout << "Welcome you to my course tragistation system!!!" << endl << endl;;
					return (i + 1);
				}
			}
		}
	}
	return 0;
}

void viewInfo(int user, Schoolyear* year, Staff* staff) {
	if (user < 0) {
		cout << "Full Name: " << staff[-1 * (user - 1)].firstName << " " << staff[-1 * (user - 1)].lastName << endl;
		cout << "Gender: " << staff[-1 * (user - 1)].gender << endl;
		cout << "Email: " << staff[-1 * (user - 1)].email << endl;
	}
	else {
		cout << "Full Name: " << year->Class[user - 1].student[user - 1].firstName << " " << year->Class[user - 1].student[user - 1].lastName << endl;
		cout << "Class: " << year->Class[user - 1].nameOfClass << endl;
		cout << "Student ID: " << year->Class[user - 1].student[user - 1].StudentID << endl;
		cout << "Gender: " << year->Class[user - 1].student[user - 1].gender << endl;
		cout << "Date of Birth: " << year->Class[user - 1].student[user - 1].dateOfBirth << endl;
		cout << "Social ID: " << year->Class[user - 1].student[user - 1].SocialID << endl;
	}
}

void changePass(int user, Schoolyear* year, Staff* staff, int numOfStaff) {
	string pass, temp;
	while (true) {
		cout << "You want to change your password!!!" << endl;
		cout << "Please enter your new password: ";
		cin >> pass;
		cout << "Please enter your new password: ";
		cin >> temp;
		if (temp != pass) {
			cout << "Error!!! Your new password don't match. Please enter again." << endl;
			pass = "";
		}
		else {
			break;
		}
	}
	if (user < 0) {
		staff[-1 * (user - 1)].pass = pass;
	}
	else {
		year->Class[user - 1].student[user - 1].pass = pass;
	}
	if (user < 0) {
		ofstream fout("StaffAccount.csv", ios::trunc);
		fout << numOfStaff << ",,,,," << endl;
		for (int i = 0; i < numOfStaff; i++) {
			fout << staff[i].firstName << "," << staff[i].lastName << "," << staff[i].gender << "," << staff[i].email << "," << staff[i].user << "," << staff[i].pass << endl;
		}
	}
	else {
		ofstream fout(year->Class[user - 1].nameOfClass + ".csv", ios::trunc);
		fout << year->Class[user - 1].numOfStudent << ",,,,,,," << endl;
		for (int i = 0; i < year->Class[user - 1].numOfStudent; i++) {
			fout << year->Class[user - 1].student[user - 1].num << ","
				<< year->Class[user - 1].student[user - 1].StudentID << ","
				<< year->Class[user - 1].student[user - 1].firstName << ","
				<< year->Class[user - 1].student[user - 1].lastName << ","
				<< year->Class[user - 1].student[user - 1].gender << ","
				<< year->Class[user - 1].student[user - 1].dateOfBirth << ","
				<< year->Class[user - 1].student[user - 1].SocialID << ","
				<< year->Class[user - 1].student[user - 1].pass << endl;
		}
	}
	cout << "Your password was changed successfully!!!" << endl << endl;
}

void createNewYear(string schoolyear) {
	cout << "Enter your new school year: ";
	cin >> schoolyear;
	ofstream fout(schoolyear + ".csv");
	cout << "Create new school year successfully!!!" << endl;
}

void createNewClass(Class*& classes, int& numOfClass) {
	cout << "Enter number of class you want to create: ";
	cin >> numOfClass;
	classes = new Class[numOfClass];
	cout << "Enter name of classes you want to create: " << endl;
	for (int i = 0; i < numOfClass; i++) {
		cout << "Enter class " << i + 1 << ": ";
		cin >> classes[i].nameOfClass;
		ofstream fout(classes[i].nameOfClass + ".csv");
		cout << "Class " << classes[i].nameOfClass << " was created successfully!!!" << endl;
	}
}

void loadInfoStudent(Schoolyear*& year) {
	if (year == NULL) {
		year = new Schoolyear;
	}
	while (true) {
		cout << "Enter your school year you created: ";
		cin >> year->schoolYear;
		ifstream fin(year->schoolYear + ".csv");
		if (fin.is_open()) {
			break;
		}
		else {
			cout << "Your school year has not been created!!!" << endl;
		}
	}
	cout << "Enter number of classes you want to load info: ";
	cin >> year->numOfClass;
	cin.ignore();
	year->Class = new Class[year->numOfClass];
	for (int i = 0; i < year->numOfClass; i++) {
		while (true) {
			cout << "Enter name of the classes: ";
			getline(cin, year->Class[i].nameOfClass);
			ifstream fin(year->Class[i].nameOfClass + ".csv");
			if (fin.is_open()) {
				break;
			}
			else {
				cout << "Your class has not been created!!!" << endl;
			}
		}
		string temp;
		ifstream fin(year->Class[i].nameOfClass + ".csv");
		if (fin.peek() == std::ifstream::traits_type::eof()) {
			cout << "No information to load!!! Please choose another class" << endl;
		}
		else {
			getline(fin, temp, ',');
			year->Class[i].numOfStudent = stoi(temp);
			year->Class[i].student = new Student[stoi(temp)];
			getline(fin, temp);
			for (int j = 0; j < year->Class[i].numOfStudent; j++) {
				getline(fin, year->Class[i].student[j].num, ',');
				getline(fin, year->Class[i].student[j].StudentID, ',');
				getline(fin, year->Class[i].student[j].firstName, ',');
				getline(fin, year->Class[i].student[j].lastName, ',');
				getline(fin, year->Class[i].student[j].gender, ',');
				getline(fin, year->Class[i].student[j].dateOfBirth, ',');
				getline(fin, year->Class[i].student[j].SocialID, ',');
				getline(fin, year->Class[i].student[j].pass);
				year->Class[i].student[j].enrolled = NULL;
			}
			cout << "Load information of class " << year->Class[i].nameOfClass << " successfully!!!" << endl;
		}
	}
	year->yearNext = NULL;
}

void createSemester(Schoolyear*& year, int& semester) {
	string schoolYear;
	cout << "Enter new school year: ";
	cin >> schoolYear;
	cout << endl;
	cout << "Enter new semester: ";
	cin >> semester;
	cin.ignore();
	semester--;
	cout << "Enter start date of this semester: " << endl;
	cout << "Enter start day: "; 
	cin >> year->semester[semester].startDate.day;
	cout << "Enter start month: ";
	cin >> year->semester[semester].startDate.month;
	cout << "Enter start year: ";
	cin >> year->semester[semester].startDate.year;
	string startDateSem = year->semester[semester].startDate.day + "/" + year->semester[semester].startDate.month + "/" + year->semester[semester].startDate.year;
	cout << "Start date of this semester is: " << startDateSem << endl;
	cout << "Enter end date of this semester: " << endl;
	cout << "Enter end day: ";
	cin >> year->semester[semester].endDate.day;
	cout << "Enter end month: ";
	cin >> year->semester[semester].endDate.month;
	cout << "Enter end year: ";
	cin >> year->semester[semester].endDate.year;
	string endDateSem = year->semester[semester].endDate.day + "/" + year->semester[semester].endDate.month + "/" + year->semester[semester].endDate.year;
	cout << "End date of this semester is: " << endDateSem << endl;
	ofstream fout(schoolYear + "_" + to_string(semester + 1) + ".csv");
	cout << "Your semester was created successfully!!!" << endl;
}

void createCourseRegistration(Schoolyear*& year, int& semester) {
	string schoolYear;
	cout << "Please enter school year you created: ";
	cin >> schoolYear;
	cout << endl;
	while (year != NULL && schoolYear != year->schoolYear) {
		year = year->yearNext;
	}
	if (year == NULL) {
		cout << "Your school year was not created. Please enter again!!!" << endl;
		return;
	}
	cout << "Please enter semester you created: ";
	cin >> semester;
	cin.ignore();
	semester--;
	string day, month, yearr;
	cout << "Enter start date of this course registration: " << endl;
	cout << "Enter start day: ";
	cin >> day;
	cout << "Enter start month: ";
	cin >> month;
	cout << "Enter start year: ";
	cin >> yearr;
	string startDateCou = day + "/" + month + "/" + yearr;
	cout << "Start date of this course registration is: " << startDateCou << endl;
	cout << "Enter end date of this course registration: " << endl;
	cout << "Enter end day: ";
	cin >> day;
	cout << "Enter end month: ";
	cin >> month;
	cout << "Enter end year: ";
	cin >> yearr;
	string endDateCou = day + "/" + month + "/" + yearr;
	cout << "End date of this course registration is: " << endDateCou << endl;
	string temp;
	ifstream fin(schoolYear + "_" + to_string(semester + 1) + ".csv");
	if (!fin.is_open()) {
		cout << "Load data failed. Make sure you was create this semester!!!" << endl;
	}
	else {
		Course* courseCur = NULL;
		getline(fin, temp, ',');
		int numOfSubject = stoi(temp);
		getline(fin, temp);
		for (int i = 0;i < numOfSubject; i++) {
			if (year->semester[semester].course == NULL) {
				year->semester[semester].course = new Course;
				courseCur = year->semester[semester].course;
			}
			else {
				courseCur->CourseNext = new Course;
				courseCur = courseCur->CourseNext;
			}
			getline(fin, courseCur->CourseID, ',');
			getline(fin, courseCur->CourseName, ',');
			getline(fin, courseCur->StaffName, ',');
			getline(fin, courseCur->NumOfCredit, ',');
			getline(fin, courseCur->Day1, ',');
			getline(fin, courseCur->Session1, ',');
			getline(fin, courseCur->Day2, ',');
			getline(fin, courseCur->Session2);
			courseCur->NumOfStu = 0;
			courseCur->CourseNext = NULL;
		}
		cout << "Load data of course successfully." << endl << endl;
	}
}

void addCourse(Course*& course) {
	Course* tempCourse = new Course;
	cout << "Enter information of the course you want to add: " << endl;
	tempCourse->NumOfStu = 0;
	cout << "Enter course ID: ";
	cin >> tempCourse->CourseID;
	cin.ignore();
	cout << "Enter name of course: ";
	getline(cin, tempCourse->CourseName);
	cout << "Enter name of teacher: ";
	getline(cin, tempCourse->StaffName);
	cout << "Enter number of credits: ";
	getline(cin, tempCourse->NumOfCredit);
	cout << "Enter day 1: ";
	getline(cin, tempCourse->Day1);
	cout << "Enter session 1: ";
	getline(cin, tempCourse->Session1);
	cout << "Enter day 2: ";
	getline(cin, tempCourse->Day2);
	cout << "Enter session 2: ";
	getline(cin, tempCourse->Session2);
	tempCourse->CourseNext = course;
	course = tempCourse;
	cout << "Add new course successfully!!!" << endl;
}

void viewCourse(Course* course, int& noCourse) {
	int no = 1;
	int y = 16, a = 20;
	Course* courseCur = course;
	cout << endl;
	gotoxy(8, 15);
	cout << "Course ID";
	gotoxy(a, 15);
	a = a + 30;
	cout << "Name of course";
	gotoxy(a, 15);
	a = a + 10;
	cout << "Teacher";
	gotoxy(a, 15);
	a = a + 10;
	cout << "Credits";
	gotoxy(a, 15);
	a = a + 22;
	cout << "Number of students";
	gotoxy(a, 15);
	cout << "Day of week and session";
	while (courseCur != NULL) {
		int x = 20;
		gotoxy(6, y);
		cout << no;
		gotoxy(8, y);
		cout << courseCur->CourseID;
		gotoxy(x, y);
		x = x + 30;
		cout << courseCur->CourseName;
		gotoxy(x, y);
		x = x + 13;
		cout << courseCur->StaffName;
		gotoxy(x, y);
		x = x + 14;
		cout << courseCur->NumOfCredit;
		gotoxy(x, y);
		x = x + 15;
		cout << courseCur->NumOfStu << "/" << 50;
		gotoxy(x, y);
		cout << "On " << courseCur->Day1 << " in " << courseCur->Session1 << " and " << courseCur->Day2 << " in " << courseCur->Session2;
		y = y + 1;
		courseCur = courseCur->CourseNext;
		no++;
		cout << endl;
	}
	noCourse = no;
}

void updateCourse(Schoolyear* year, int semester) {
	Course* courseCur = year->semester[semester].course;
	int numOfSubject = 1, option;
	viewCourse(year->semester[semester].course, numOfSubject);
	numOfSubject--;
	cout << "Enter the no of course you want to update: ";
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
	cin.ignore();
	courseCur = year->semester[semester].course;
	for (int i = 1; i < option; i++) {
		courseCur = courseCur->CourseNext;
	}
	cout << "The name of course you want to update is:" << courseCur->CourseName << endl;
	cout << "1. Name of teacher." << endl;
	cout << "2. Number of credits." << endl;
	cout << "3. Number of student enrolled the course." << endl;
	cout << "4. Day 1." << endl;
	cout << "5. Session 1." << endl;
	cout << "6. Day 2." << endl;
	cout << "7. Session 2." << endl;
	cout << "Enter your option you want to update: ";
	cin >> option;
	cin.ignore();
	if (option == 1) {
		cout << "Enter the new name of teacher: ";
		cin >> courseCur->StaffName;
	}
	else if (option == 2) {
		cout << "Enter the new number of credits: ";
		cin >> courseCur->NumOfCredit;
	}
	else if (option == 3) {
		cout << "Enter the new number of students enrolled the course: ";
		cin >> courseCur->NumOfStu;
	}
	else if (option == 4) {
		cout << "Enter the new day 1: ";
		cin >> courseCur->Day1;
	}
	else if (option == 5) {
		cout << "Enter the new session of day 1: ";
		cin >> courseCur->Session1;
	}
	else if (option == 6) {
		cout << "Enter the new day 2: ";
		cin >> courseCur->Day2;
	}
	else if (option == 7) {
		cout << "Enter the new session of day 2: ";
		cin >> courseCur->Session2;
	}
	cout << "Update course successfully!!!" << endl;
}

void deleteCourse(Schoolyear*& year, int semester) {
	Course* courseCur = year->semester[semester].course;
	int numOfSubject = 1, option;
	viewCourse(year->semester[semester].course, numOfSubject);
	numOfSubject--;
	cout << "Enter the course you want to delete: ";
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
	cin.ignore();
	courseCur = year->semester[semester].course;
	if (option <= numOfSubject) {
		if (option == 1) {
			year->semester[semester].course = year->semester[semester].course->CourseNext;
			delete courseCur;
		}
		else {
			for (int i = 2; i < option; i++) {
				courseCur = courseCur->CourseNext;
			}
			Course* tempCourse = courseCur->CourseNext;
			courseCur->CourseNext = courseCur->CourseNext->CourseNext;
			delete tempCourse;
			cout << "Delete course successfully!!!" << endl;
		}
	}
	else {
		cout << "Invalid input. Please enter again!!!" << endl;
	}
}

