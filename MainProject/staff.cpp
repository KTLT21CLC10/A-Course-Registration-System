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

void loadAccountStaff(Staff*& staff, int& numOfStaff) {
	ifstream finStaff("StaffAccount.csv");
	string tempStaff;
	getline(finStaff, tempStaff, ',');
	numOfStaff = stoi(tempStaff);
	staff = new Staff[stoi(tempStaff)];
	getline(finStaff, tempStaff);
	for (int i = 0; i < numOfStaff; i++) {
		getline(finStaff, staff[i].firstName, ',');
		getline(finStaff, staff[i].lastName, ',');
		getline(finStaff, staff[i].gender, ',');
		getline(finStaff, staff[i].email, ',');
		getline(finStaff, staff[i].user, ',');
		getline(finStaff, staff[i].pass);
	}
}

void loadAccountStu(Schoolyear*& year) {
	if (year == NULL) {
		year = new Schoolyear;
	}
	ifstream finStu("StudentAccount.csv");
	if (finStu.is_open()) {
		string numOfClass, numOfStu, nameOfClass;
		getline(finStu, numOfClass, ',');
		year->numOfClass = stoi(numOfClass);
		year->Class = new Class[year->numOfClass];
		getline(finStu, numOfClass);
		for (int i = 0; i < year->numOfClass; i++) {
			getline(finStu, nameOfClass, ',');
			year->Class[i].nameOfClass = nameOfClass;
			getline(finStu, nameOfClass);
			getline(finStu, numOfStu, ',');
			if (numOfStu == ",,,,,,") {
				continue;
			}
			else {
				year->Class[i].numOfStudent = stoi(numOfStu);
				year->Class[i].student = new Student[stoi(numOfStu)];
				getline(finStu, numOfStu);
				for (int j = 0; j < year->Class[i].numOfStudent; j++) {
					getline(finStu, year->Class[i].student[j].num, ',');
					getline(finStu, year->Class[i].student[j].StudentID, ',');
					getline(finStu, year->Class[i].student[j].firstName, ',');
					getline(finStu, year->Class[i].student[j].lastName, ',');
					getline(finStu, year->Class[i].student[j].gender, ',');
					getline(finStu, year->Class[i].student[j].dateOfBirth, ',');
					getline(finStu, year->Class[i].student[j].SocialID, ',');
					getline(finStu, year->Class[i].student[j].pass);
					year->Class[i].student[j].enrolled = NULL;
				}
			}
		}
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
		cout << "Full Name: " << staff[(-1 * user) - 1].firstName << " " << staff[(-1 * user) - 1].lastName << endl;
		cout << "Gender: " << staff[(-1 * user) - 1].gender << endl;
		cout << "Email: " << staff[(-1 * user) - 1].email << endl;
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
		staff[(-1 * user) - 1].pass = pass;
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

void createNewClass(string schoolYear, Class*& classes, int& numOfClass) {
	while (true) {
		cout << "Enter the year you want to create several classes: ";
		cin >> schoolYear;
		ifstream fin(schoolYear + ".csv");
		if (fin.is_open()) {
			break;
		}
		else {
			cout << "Your school year has not been created!!!" << endl;
		}
	}
	cout << "Enter number of class you want to create: ";
	cin >> numOfClass;
	classes = new Class[numOfClass];
	cout << "Enter name of classes you want to create: " << endl;
	ofstream fout(schoolYear + ".csv");
	fout << numOfClass << ",," << endl;
	for (int i = 0; i < numOfClass; i++) {
		cout << "Enter class " << i + 1 << ": ";
		cin >> classes[i].nameOfClass;
		fout << i + 1 << "," << classes[i].nameOfClass << "," << endl;
		ofstream fout(classes[i].nameOfClass + ".csv");
		cout << "Class " << classes[i].nameOfClass << " was created successfully!!!" << endl;
	}
}

void loadInfoStudent(Schoolyear*& year) {
	if (year == NULL) {
		year = new Schoolyear;
	}
	while (true) {
		cout << "Enter your school year you created to load information: ";
		cin >> year->schoolYear;
		ifstream fin(year->schoolYear + ".csv");
		if (fin.is_open()) {
			break;
		}
		else {
			cout << "Your school year has not been created!!!" << endl;
		}
	}
	string numOfClass, tempNum;
	ifstream finYear(year->schoolYear + ".csv");
	ofstream fout("StudentAccount.csv");
	getline(finYear, numOfClass, ',');
	year->numOfClass = stoi(numOfClass);
	fout << numOfClass << ",,,,,,," << endl;
	year->Class = new Class[year->numOfClass];
	getline(finYear, tempNum);
	for (int i = 0; i < year->numOfClass; i++) {
		string tempNo;
		getline(finYear, tempNo, ',');
		getline(finYear, year->Class[i].nameOfClass);
		
		string temp;
		ifstream fin(year->Class[i].nameOfClass + ".csv");
		getline(fin, temp, ',');
		if (temp == "\n") {
			cout << "Your class " << year->Class[i].nameOfClass << " do not have information to load!!!" << endl;
		}
		else {
			fout << year->Class[i].nameOfClass << ",,,,,,," << endl;
			fout << temp << ",,,,,,," << endl;
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
				fout << year->Class[i].student[j].num << "," << year->Class[i].student[j].StudentID << ","
					<< year->Class[i].student[j].firstName << "," << year->Class[i].student[j].lastName << ","
					<< year->Class[i].student[j].gender << "," << year->Class[i].student[j].dateOfBirth << ","
					<< year->Class[i].student[j].SocialID << "," << year->Class[i].student[j].pass << endl;
			}
			cout << "Load information of class " << year->Class[i].nameOfClass << " successfully!!!" << endl;
		}
	}
	year->yearNext = NULL;
}

bool checkDateSemester(Schoolyear*& year, int& semester) {
	int schoolYearStart = (int)(year->schoolYear[0]) * 1000 + (int)(year->schoolYear[1]) * 100 + (int)(year->schoolYear[2]) * 10 + (int)(year->schoolYear[3]) - 53328;
	int schoolYearEnd = (int)(year->schoolYear[5]) * 1000 + (int)(year->schoolYear[6]) * 100 + (int)(year->schoolYear[7]) * 10 + (int)(year->schoolYear[8]) - 53328;
	if (semester == 0) {
		if (stoi(year->semester[semester].startDate.year) == schoolYearStart && stoi(year->semester[semester].endDate.year) == schoolYearStart) {
			if ((stoi(year->semester[semester].startDate.month) >= 9) && (stoi(year->semester[semester].endDate.month) <= 12) && (stoi(year->semester[semester].startDate.month) < stoi(year->semester[semester].endDate.month))) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else if (semester == 1) {
		if (stoi(year->semester[semester].startDate.year) == schoolYearEnd && stoi(year->semester[semester].endDate.year) == schoolYearEnd) {
			if ((stoi(year->semester[semester].startDate.month) >= 1) && (stoi(year->semester[semester].endDate.month) <= 4) && (stoi(year->semester[semester].startDate.month) < stoi(year->semester[semester].endDate.month))) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		if (stoi(year->semester[semester].startDate.year) == schoolYearEnd && stoi(year->semester[semester].endDate.year) == schoolYearEnd) {
			if ((stoi(year->semester[semester].startDate.month) >= 5) && (stoi(year->semester[semester].endDate.month) <= 8) && (stoi(year->semester[semester].startDate.month) < stoi(year->semester[semester].endDate.month))) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	return false;
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
	while (true) {
		cout << "Enter start date of this semester: " << endl;
		cout << "Enter start day: ";
		cin >> year->semester[semester].startDate.day;
		cout << "Enter start month: ";
		cin >> year->semester[semester].startDate.month;
		cout << "Enter start year: ";
		cin >> year->semester[semester].startDate.year;
		cout << "Enter end date of this semester: " << endl;
		cout << "Enter end day: ";
		cin >> year->semester[semester].endDate.day;
		cout << "Enter end month: ";
		cin >> year->semester[semester].endDate.month;
		cout << "Enter end year: ";
		cin >> year->semester[semester].endDate.year;
		if (checkDateSemester(year, semester)) {
			break;
		}
		else {
			cout << "Your date of semester is invalid. Please enter again!!!" << endl;
		}
	}
	string startDateSem = year->semester[semester].startDate.day + "/" + year->semester[semester].startDate.month + "/" + year->semester[semester].startDate.year;
	cout << "Start date of this semester is: " << startDateSem << endl;
	string endDateSem = year->semester[semester].endDate.day + "/" + year->semester[semester].endDate.month + "/" + year->semester[semester].endDate.year;
	cout << "End date of this semester is: " << endDateSem << endl;
	ofstream fout(schoolYear + "_" + to_string(semester + 1) + ".csv");
	cout << "Your semester was created successfully!!!" << endl;
}

bool checkDateRegis1(Schoolyear*& year, int& semester) {
	if (stoi(year->courseRegis[semester].startDate.year) <= stoi(year->semester[semester].startDate.year)) {
		if (stoi(year->courseRegis[semester].startDate.month) <= stoi(year->semester[semester].startDate.month)) {
			if (stoi(year->courseRegis[semester].startDate.day) <= stoi(year->semester[semester].startDate.day)) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
}

bool checkDateRegis2(Schoolyear*& year, int& semester) {
	if (stoi(year->courseRegis[semester].endDate.year) <= stoi(year->semester[semester].endDate.year)) {
		if (stoi(year->courseRegis[semester].endDate.month) <= stoi(year->semester[semester].endDate.month)) {
			if (stoi(year->courseRegis[semester].endDate.day) <= stoi(year->semester[semester].endDate.day)) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	return false;
}

bool checkDateRegis3(Schoolyear*& year, int& semester) {
	if (stoi(year->courseRegis[semester].startDate.year) <= stoi(year->courseRegis[semester].endDate.year)) {
		if (stoi(year->courseRegis[semester].startDate.month) <= stoi(year->courseRegis[semester].endDate.month)) {
			if (stoi(year->courseRegis[semester].startDate.day) <= stoi(year->courseRegis[semester].endDate.day)) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	return false;
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
	while (true) {
		cout << "Enter again start date of this semester you created: " << endl;
		cout << "Enter start day: ";
		cin >> year->semester[semester].startDate.day;
		cout << "Enter start month: ";
		cin >> year->semester[semester].startDate.month;
		cout << "Enter start year: ";
		cin >> year->semester[semester].startDate.year;
		cout << "Enter again end date of this semester you created: " << endl;
		cout << "Enter end day: ";
		cin >> year->semester[semester].endDate.day;
		cout << "Enter end month: ";
		cin >> year->semester[semester].endDate.month;
		cout << "Enter end year: ";
		cin >> year->semester[semester].endDate.year;
		if (checkDateSemester(year, semester)) {
			cout << "Enter start date of this course registration: " << endl;
			cout << "Enter start day: ";
			cin >> year->courseRegis[semester].startDate.day;
			cout << "Enter start month: ";
			cin >> year->courseRegis[semester].startDate.month;
			cout << "Enter start year: ";
			cin >> year->courseRegis[semester].startDate.year;
			cout << "Enter end date of this course registration: " << endl;
			cout << "Enter end day: ";
			cin >> year->courseRegis[semester].endDate.day;
			cout << "Enter end month: ";
			cin >> year->courseRegis[semester].endDate.month;
			cout << "Enter end year: ";
			cin >> year->courseRegis[semester].endDate.year;
			if (checkDateRegis1(year, semester) && checkDateRegis2(year, semester) && checkDateRegis3(year, semester)) {
				break;
			}
			else {
				cout << "Your date you inputed is invalid. Please enter again!!!" << endl;
			}
		}
		else {
			cout << "Your date of semester is invalid. Please enter again!!!" << endl;
		}
	}
	string startDateSem = year->semester[semester].startDate.day + "/" + year->semester[semester].startDate.month + "/" + year->semester[semester].startDate.year;
	string startDateCou = year->courseRegis[semester].startDate.day + "/" + year->courseRegis[semester].startDate.month + "/" + year->courseRegis[semester].startDate.year;
	cout << "Start date of this semester is: " << startDateSem << " and this course registration is: " << startDateCou << endl;
	string endDateSem = year->semester[semester].endDate.day + "/" + year->semester[semester].endDate.month + "/" + year->semester[semester].endDate.year;
	string endDateCou = year->courseRegis[semester].endDate.day + "/" + year->courseRegis[semester].endDate.month + "/" + year->courseRegis[semester].endDate.year;
	cout << "End date of this semester is: " << endDateSem << " and this course registration is: " << endDateCou << endl;
	string temp;
	ifstream fin(schoolYear + "_" + to_string(semester + 1) + ".csv");
	if (!fin.is_open()) {
		cout << "Load data failed. Make sure you was create this semester!!!" << endl;
	}
	else {
		ofstream fout("Data of " + schoolYear + "_" + to_string(semester + 1) + ".csv");
		Course* courseCur = NULL;
		getline(fin, temp, ',');
		int numOfSubject = stoi(temp);
		fout << numOfSubject << ",,,,,,,," << endl;
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
			fout << courseCur->CourseID << "," << courseCur->CourseName << ","
				<< courseCur->StaffName << "," << courseCur->NumOfCredit << ","
				<< courseCur->NumOfStu << "," << courseCur->Day1 << ","
				<< courseCur->Session1 << "," << courseCur->Day2 << "," << courseCur->Session2 << endl;
		}
		cout << "Load data of course successfully." << endl << endl;
	}
}

void addCourse(Schoolyear*& year, int& semester, int& no) {
	int numOfSubject;
	Course* tempCourse = new Course;
	viewCourse(year->semester[semester].course, numOfSubject);
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
	tempCourse->CourseNext = year->semester[semester].course;
	year->semester[semester].course = tempCourse;
	numOfSubject++;
	cout << "Add new course successfully!!!" << endl;
	no = numOfSubject;
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

void deleteCourse(Schoolyear*& year, int semester, int& no) {
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
			numOfSubject--;
		}
	}
	else {
		cout << "Invalid input. Please enter again!!!" << endl;
	}
	no = numOfSubject;
}

void saveInfoCourseStaff(Course*& course, Schoolyear*& year, int& semester, int& numOfSubject) {
	string temp;
	ofstream fout("Data of " + year->schoolYear + "_" + to_string(semester + 1) + ".csv");
	fout << numOfSubject << ",,,,,,,," << endl;
	while (course != NULL) {
		fout << course->CourseID << "," << course->CourseName << ","
			<< course->StaffName << "," << course->NumOfCredit << ","
			<< course->NumOfStu << "," << course->Day1 << ","
			<< course->Session1 << "," << course->Day2 << "," << course->Session2 << endl;
		course = course->CourseNext;
	}
}