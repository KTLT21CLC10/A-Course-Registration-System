#include "staff.h"
#include <string>

int main()
{
	Schoolyear* YearHead = NULL, * YearCur1 = NULL, * YearCur2 = NULL;
	Teacher* Staff;
	string username, password;
	Date Today;
	Now(Today);
	int option1, NumOfStaff, sem = 0;
	InputStaff(Staff, NumOfStaff);
	do
	{
		Now(Today);
		InputAccount(username, password);
		int x = CheckLogin(username, password, YearCur1, Staff, NumOfStaff);
		if (x == 0)
		{
			cout << "Your username or password is incorrect!!!" << endl;
			password = "";
			YearCur1 = YearHead;
			continue;
		}
		else
		{
			cout << "You log in successfully!!!" << endl << endl;
		}
		string* str1;
		int k;
		if (x < 100)k = 10;
		else
		{
			k = 9;
			/*if (CheckDateRegister(Today, YearCur2->Sem[sem].StartReg, YearCur2->Sem[sem].EndReg)) k = 6;
			else k = 4;
			if (CheckImport(YearCur1, x)) k = 5;*/
		}
		str1 = new string[k];
		str1[0] = "Log out";
		str1[1] = "View info";
		str1[2] = "Change password";
		if (x < 100)
		{
			str1[3] = "Add new year and load information of student";
			str1[4] = "Create semester";
			str1[5] = "Create course and load information of course";
			str1[6] = "Add a course";
			str1[7] = "View list of courses";
			str1[8] = "Update course";
			str1[9] = "Delete course";
		}
		else
		{
			str1[3] = "Course Registration";
			str1[4] = "View list of your courses";
			str1[5] = "View list of class";
			str1[6] = "View list of students in class";
			str1[7] = "View list of course";
			str1[8] = "View list of students in a course";
		}
		int option1 = 1;
		while (option1 != 0)
		{
			for (int i = 1; i < k; i++) {
				cout << i << ". " << str1[i] << endl;
			}
			cout << "0. " << str1[0] << endl;
			cout << "Input your option: ";
			cin >> option1;
			switch (option1)
			{
				case 1:
				{
					system("cls");
					ViewIn(x, YearCur1, Staff);
					break;
				}
				case 2:
				{
					system("cls");
					ChangePass(YearCur1, Staff, x, NumOfStaff);  
					break;
				}
				case 3:
				{
					system("cls");
					if (x < 100)
					{
						if (YearHead == nullptr)
						{
							AddYear(YearHead);
							YearCur1 = YearHead;
						}
						else
						{
							AddYear(YearCur1->YearNext);
							YearCur1 = YearCur1->YearNext;
						}
					}
					else
					{
						int choice;
						while (true) {
							cout << "1. Enroll in a course" << endl;
							cout << "2. View list of enrolled course" << endl;
							cout << "3. Remove a course from enrolled list" << endl;
							cout << "0. Back" << endl;
							cout << "Enter your choice: ";
							cin >> choice;
							if (choice == 1) {
								CourseEnroll(YearCur1, YearCur2->Sem[sem].pCourse, x, YearCur1->CLass[x / 100 - 1].Stu[x % 100 - 1].NumOfOpt);
							}
							else if (choice == 2) {
								int t, i;
								ViewCou(YearCur1->CLass[x / 100 - 1].Stu[x % 100 - 1].Registered, t, i);
							}
							else if (choice == 3) {
								RemoveCourseEnrolled(YearCur1, YearCur2->Sem[sem].pCourse, x);
							}
							else {
								break;
							}
						}
					}
					break;
				}
				case 4:
				{
					system("cls");
					if (x < 100)
					{
						YearCur2 = YearHead;
						AddSem(YearCur2, sem);
					}
					else
					{
						int t, i;
						ViewCou(YearCur1->CLass[x / 100 - 1].Stu[x % 100 - 1].Registered, t, i);
					}
					break;
				}
				case 5:
				{
					system("cls");
					if (x < 100)
					{
						if (CheckDateEndSemester(Today, YearCur2->Sem[sem].EndSem))
							CreateCourse(YearCur2, sem);
						else
							cout << "Your date end semester is invalid!!!" << endl;
					}
					else
					{
						ViewListClasses(YearHead);
					}
					break;
				}
				case 6:
				{
					system("cls");
					if (x < 100) {
						AddCou(YearCur2->Sem[sem].pCourse);
					}
					else {
						ViewListStudentInClass(YearHead);
					}
					break;
				}
				case 7:
				{
					system("cls");
					if (x < 100) {
						int t;
						ViewCou(YearCur2->Sem[sem].pCourse, t, t);
					}
					else {
						int t;
						ViewCou(YearCur2->Sem[sem].pCourse, t, t);
					}
					break;
				}
				case 8:
				{
					system("cls");
					if (x < 100) {
						UpdateCou(YearCur2, sem);
					}
					else {
						ViewListStudentInCourse(YearCur2, sem);
					}
					break;
				}
				case 9:
				{
					system("cls");
					DeleteCou(YearCur2, sem);
					break;
				}
				case 0:
				{
					YearCur1 = YearHead;
					break;
				}
			}
			password = "";
		}
		delete[]str1;
	} while (true);
	delete[]Staff;
	return 0;
}