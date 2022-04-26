#include "Header.h"
#include <string>
using namespace std;

int main() {
	Schoolyear* yearHead1 = NULL, *yearHead2 = NULL, * yearNode1 = NULL, * yearNode2 = NULL;
	Staff* staff;
	string username, password;
	int option, numOfStaff, semester = 0;
	bool checkUser;
	loadAccountStaff(staff, numOfStaff);
	checkUser = true;
	ifstream in("StudentAccount.csv");
	if (in.is_open()) {
		if (yearHead1 == NULL)
		{
			loadAccountStu(yearHead1);
			yearNode1 = yearHead1;
			checkUser = false;
		}
		else
		{
			loadAccountStu(yearNode1->yearNext);
			yearNode1 = yearNode1->yearNext;
			checkUser = false;
		}
	}
	do {
		system("cls");
		inputAccount(username, password);
		int user = loginSystem(username, password, yearNode1, staff, numOfStaff);
		if (user == 0) {
			cout << "Your username or password is incorrect!!!" << endl;
			password = "";
			yearNode1 = yearHead1;
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
					int numOfSubStu;
					if (checkUser == false) {
						yearNode2 = yearHead1;
						loadInfoCourse(yearNode2, semester, numOfSubStu);
					}
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
							enrollCourse(yearNode1, yearNode2->semester[semester].course, user, yearNode1->Class[user - 1].student[user - 1].numOfSubject, numOfSubStu);
						}
						else if (optionEnroll == 2) {
							system("cls");
							int option2;
							while (true) {
								cout << "1. View list of your new enroll course." << endl;
								cout << "2. View list of your old enroll course." << endl;
								cout << "Enter your option: ";
								cin >> option2;
								if (option2 == 1) {
									int numOfSubject;
									viewCourse(yearNode1->Class[user - 1].student[user - 1].enrolled, numOfSubject);
									break;
								}
								else {
									viewListEnrollCourse(yearNode1->Class[user - 1].student[user - 1].StudentID, numOfSubStu);
									break;
								}
							}
						}
						else if (optionEnroll == 3) {
							system("cls");
							removeCourseEnrolled(yearNode1, yearNode2->semester[semester].course, user, numOfSubStu);
						}
						else {
							saveInfoCourse(yearNode1->Class[user - 1].student[user - 1].enrolled, yearNode1->Class[user - 1].student[user - 1].StudentID, numOfSubStu);
							break;
						}
					}
				}
			}
			else if (option == 4) {
				system("cls");
				if (user < 0) {
					string schoolYear;
					Class* Class;
					int numOfClass;
					system("cls");
					createNewClass(schoolYear, Class, numOfClass);
				}
				else {
					int numOfSub;
					viewListEnrollCourse(yearNode1->Class[user - 1].student[user - 1].StudentID, numOfSub);
				}
			}
			else if (option == 5) {
				system("cls");
				if (user < 0) {
					if (yearHead1 == NULL)
					{
						loadInfoStudent(yearHead1);
						yearNode1 = yearHead1;
					}
					else
					{
						loadInfoStudent(yearNode1->yearNext);
						yearNode1 = yearNode1->yearNext;
					}
				}
				else {
					Class* classes;
					viewListClasses(classes);
				}
			}
			else if (option == 6) {
				system("cls");
				if (user < 0)
				{
					yearNode2 = yearHead1;
					createSemester(yearNode2, semester);
				}
				else {
					viewListStudentInClass(yearHead1);
				}
			}
			else if (option == 7) {
				system("cls");
				int numOfSubj;
				if (user < 0) {
					int option1;
					while (true) {
						cout << "1. Create a new semester." << endl;
						cout << "2. Load the old data." << endl;
						cout << "Enter your option: ";
						cin >> option1;
						if (option1 == 1) {
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
									addCourse(yearNode2, semester, numOfSubj);
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
									deleteCourse(yearNode2, semester, numOfSubj);
								}
								else {
									saveInfoCourseStaff(yearNode2->semester[semester].course, yearNode2, semester, numOfSubj);
									break;
								}
							}
							break;
						}
						else {
							loadInfoCourse(yearNode2, semester, numOfSubj);
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
									addCourse(yearNode2, semester, numOfSubj);
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
									deleteCourse(yearNode2, semester, numOfSubj);
								}
								else {
									saveInfoCourseStaff(yearNode2->semester[semester].course, yearNode2, semester, numOfSubj);
									break;
								}
							}
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
				yearNode1 = yearHead1;
				break;
			}
		}
		password = "";
	} while (true);
	delete[]staff;
	return 0;
}