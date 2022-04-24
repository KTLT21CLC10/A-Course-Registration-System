#include "Header.h"
#include <string>
using namespace std;

int main() {
	Schoolyear* yearHead = NULL, * yearNode1 = NULL, * yearNode2 = NULL;
	Staff* staff;
	string username, password;
	int option, numOfStaff, semester = 0;
	loadInfoStaff(staff, numOfStaff);
	do {
		system("cls");
		inputAccount(username, password);
		int user = loginSystem(username, password, yearNode1, staff, numOfStaff);
		if (user == 0) {
			cout << "Your username or password is incorrect!!!" << endl;
			password = "";
			yearNode1 = yearHead;
			continue;
		}
		while (true) {
			if (user == -1) {
				cout << "1. View your profile information." << endl;
				cout << "2. Change your password" << endl;
				cout << "3. Add new year" << endl;
				cout << "4. Add several classes" << endl;
				cout << "5. Load data of students" << endl;
				cout << "6. Create semester" << endl;
				cout << "7. Create course registration and load information of course" << endl;
				cout << "0. Log out of the system" << endl;
			}
			else {
				cout << "1. View your profile information." << endl;
				cout << "2. Change your password" << endl;
				cout << "3. Course Registration" << endl;
				cout << "4. View list of your courses" << endl;
				cout << "5. View list of class" << endl;
				cout << "6. View list of students in class" << endl;
				cout << "7. View list of courses" << endl;
				cout << "8. View list of students in a course" << endl;
				cout << "0. Log out of the system" << endl;
			}
			cout << "Enter your option: ";
			cin >> option;
			if (option == 1) {
				system("cls");
				viewInfo(user, yearNode1, staff);
			}
			else if (option == 2) {
				system("cls");
				changePass(user, yearNode1, staff, numOfStaff);
			}
			else if (option == 3) {
				system("cls");
				if (user < 0) {
					string schoolYear;
					createNewYear(schoolYear);
				}
				else {
					int optionEnroll;
					while (true) {
						cout << "1. Enroll in a course" << endl;
						cout << "2. View list of enrolled course" << endl;
						cout << "3. Remove a course from enrolled list" << endl;
						cout << "0. Back" << endl;
						cout << "Enter your choice: ";
						cin >> optionEnroll;
						if (optionEnroll == 1) {
							system("cls");
							enrollCourse(yearNode1, yearNode2->semester[semester].course, user, yearNode1->Class[user - 1].student[user - 1].numOfSubject);
						}
						else if (optionEnroll == 2) {
							system("cls");
							int numOfSubject;
							viewCourse(yearNode1->Class[user - 1].student[user - 1].enrolled, numOfSubject);
						}
						else if (optionEnroll == 3) {
							system("cls");
							removeCourseEnrolled(yearNode1, yearNode2->semester[semester].course, user);
						}
						else {
							break;
						}
					}
				}
			}
			else if (option == 4) {
				system("cls");
				if (user < 0) {
					Class* Class;
					int numOfClass;
					system("cls");
					createNewClass(Class, numOfClass);
				}
				else {
					int numOfSubject;
					viewCourse(yearNode1->Class[user - 1].student[user - 1].enrolled, numOfSubject);
				}
			}
			else if (option == 5) {
				system("cls");
				if (user < 0) {
					if (yearHead == NULL)
					{
						loadInfoStudent(yearHead);
						yearNode1 = yearHead;
					}
					else
					{
						loadInfoStudent(yearNode1->yearNext);
						yearNode1 = yearNode1->yearNext;
					}
				}
				else {
					viewListClasses(yearHead);
				}
			}
			else if (option == 6) {
				system("cls");
				if (user < 0)
				{
					yearNode2 = yearHead;
					createSemester(yearNode2, semester);
				}
				else {
					viewListStudentInClass(yearHead);
				}
			}
			else if (option == 7) {
				system("cls");
				if (user < 0) {
					createCourseRegistration(yearNode2, semester);
					int optionSub;
					while (true) {
						cout << "1. Add a course" << endl;
						cout << "2. View list of courses" << endl;
						cout << "3. Update course" << endl;
						cout << "4. Delete course" << endl;
						cout << "0. Back" << endl;
						cout << "Enter your choice: ";
						cin >> optionSub;
						if (optionSub == 1) {
							system("cls");
							addCourse(yearNode2->semester[semester].course);
						}
						else if (optionSub == 2) {
							system("cls");
							int numOfSub;
							viewCourse(yearNode2->semester[semester].course, numOfSub);
						}
						else if (optionSub == 3) {
							system("cls");
							updateCourse(yearNode2, semester);
						}
						else if (optionSub == 4) {
							system("cls");
							deleteCourse(yearNode2, semester);
						}
						else {
							break;
						}
					}
				}
				else {
					int numOfSubject;
					viewCourse(yearNode2->semester[semester].course, numOfSubject);
				}
			}
			else if (option == 8) {
				system("cls");
				viewListStudentInCourse(yearNode2, semester);
			}
			else {
				yearNode1 = yearHead;
				break;
			}
		}
		password = "";
	} while (true);
	delete[]staff;
	return 0;
}