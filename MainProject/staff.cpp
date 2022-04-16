#include "staff.h"
#include <string>
using namespace std;

void gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

void clear()
{
	for (int i = 0; i < 118; ++i) {
		for (int j = 3; j < 39; ++j)
		{
			gotoxy(i, j);
			cout << char(32);
		}
	}
	cout << endl;
}

void InputAccount(string& Name, string& Pass)
{
	cout << "Please enter your username: ";
	cin >> Name;
	cout << "Please enter your password: ";
	cin >> Pass;
	cout << endl;
}

void AddYear(Schoolyear*& Year) 
{
	if (!Year) Year = new Schoolyear;
	cout << "Input school year: ";
	cin >> Year->NumOfYear;
	cout << endl;
	cout << "Input number of classes: ";
	cin >> Year->NumOfClass;
	cin.ignore();
	Year->CLass = new Class[Year->NumOfClass];
	for (int i = 0; i < Year->NumOfClass; i++)
	{
		while (true)
		{
			cout << "Input name of the class: ";
			getline(cin, Year->CLass[i].NameOfClass);
			ifstream in(Year->CLass[i].NameOfClass + ".csv");
			if (in.is_open()) break;
			else
			{
				cout << "Can not open files to load data!!!";
			}
		}
		string temp;
		ifstream in(Year->CLass[i].NameOfClass + ".csv");
		getline(in, temp, ',');
		Year->CLass[i].NumOfStudent = stoi(temp);
		Year->CLass[i].Stu = new Student[stoi(temp)];
		getline(in, temp);
		for (int j = 0; j < Year->CLass[i].NumOfStudent; j++)
		{
			getline(in, Year->CLass[i].Stu[j].Num, ',');
			getline(in, Year->CLass[i].Stu[j].StudentID, ',');
			getline(in, Year->CLass[i].Stu[j].FirstName, ',');
			getline(in, Year->CLass[i].Stu[j].Name, ',');
			getline(in, Year->CLass[i].Stu[j].Sex, ',');
			getline(in, Year->CLass[i].Stu[j].DOB, ',');
			getline(in, Year->CLass[i].Stu[j].ID, ',');
			getline(in, Year->CLass[i].Stu[j].Pass);
			Year->CLass[i].Stu[j].Registered = nullptr;
		}
		cout << "Load data of class " << Year->CLass[i].NameOfClass << " successfully" << endl;
	}
	Year->YearNext = nullptr;
}

int CheckLogin(string Name, string Pass, Schoolyear*& Year, Teacher* Staff, int NumOfStaff)
{
	if (Name[0] >= 'a' && Name[0] <= 'z')
	{
		int i = 0;
		for (i; i < NumOfStaff; i++)
		{
			if (Name == Staff[i].Acc && Pass == Staff[i].Pass)
				return i + 1;
		}
		return 0;
	}
	else if (Name[0] >= 'A' && Name[0] <= 'Z')
		return 0; 
	else if (Name[0] >= 48 && Name[0] <= 57 && Name.length() == 8)
	{
		if (Year == nullptr) return 0;
		else
		{
			for (int i = 0; i < Year->NumOfClass; i++)
				for (int j = 0; j < Year->CLass[i].NumOfStudent; j++)
					if (Name == Year->CLass[i].Stu[j].StudentID && Year->CLass[i].Stu[j].Pass == Pass)
						return (i + 1) * 100 + j + 1;
			return 0;
		}
	}
	else return 0;
}

void InputStaff(Teacher*& S, int& NumOfS){
	ifstream in("StaffAcc.csv");
	string temp;
	getline(in, temp, ',');
	NumOfS = stoi(temp);
	S = new Teacher[stoi(temp)];
	getline(in, temp);
	for (int i = 0; i < NumOfS; i++)
	{
		getline(in, S[i].FirstName, ',');
		getline(in, S[i].Name, ',');
		getline(in, S[i].Sex, ',');
		getline(in, S[i].Email, ',');
		getline(in, S[i].Acc, ',');
		getline(in, S[i].Pass);
	}
}

void ViewIn(int x, Schoolyear* Year, Teacher* Staff)
{
	if (x < 100)
	{
		cout << "FullName: " << Staff[x - 1].FirstName << " " << Staff[x - 1].Name << endl;
		cout << "Sex: " << Staff[x - 1].Sex << endl;
		cout << "Email: " << Staff[x - 1].Email << endl;
	}
	else
	{
		cout << "FullName: " << Year->CLass[x / 100 - 1].Stu[x % 100 - 1].FirstName << Year->CLass[x / 100 - 1].Stu[x % 100 - 1].Name << endl;
		cout << "Class: " << Year->CLass[x / 100 - 1].NameOfClass << endl;
		cout << "Student ID: " << Year->CLass[x / 100 - 1].Stu[x % 100 - 1].StudentID << endl;
		cout << "Date of Birth: " << Year->CLass[x / 100 - 1].Stu[x % 100 - 1].DOB << endl;
		cout << "Sex: " << Year->CLass[x / 100 - 1].Stu[x % 100 - 1].Sex << endl;
		cout << "Social ID: " << Year->CLass[x / 100 - 1].Stu[x % 100 - 1].ID << endl;
		cout << "Pass" << Year->CLass[x / 100 - 1].Stu[x % 100 - 1].Pass << endl;
	}
}

void ChangePass(Schoolyear* Year, Teacher* S, int x, int NumOfS)
{
	string Pass;
	while (true)
	{
		cout << "Please enter your new Pass: ";
		cin >> Pass;
		cin.ignore();
		cout << "Please enter your new Pass: ";
		string temp;
		getline(cin, temp);
		if (temp != Pass)
		{
			cout << "Input error. Please input again your new Pass!!!" << endl;
			Pass = "";
		}
		else break;
	}
	if (x < 100) S[x - 1].Pass = Pass;
	else Year->CLass[x / 100 - 1].Stu[x % 100 - 1].Pass = Pass;
	if (x < 100)
	{
		ofstream out("StaffAcc.csv", ios::trunc);
		out << NumOfS << ",,,,," << endl;
		for (int i = 0; i < NumOfS; i++)
		{
			out << S[i].FirstName << "," << S[i].Name << "," << S[i].Sex << "," << S[i].Email << "," << S[i].Acc << "," << S[i].Pass << endl;
		}
	}
	else
	{
		ofstream out(Year->CLass[x / 100 - 1].NameOfClass + ".csv", ios::trunc);
		out << Year->CLass[x / 100 - 1].NumOfStudent << ",,,,,,," << endl;
		for (int i = 0; i < Year->CLass[x / 100 - 1].NumOfStudent; i++)
		{
			out << Year->CLass[x / 100 - 1].Stu[i].Num << "," << Year->CLass[x / 100 - 1].Stu[i].StudentID << "," << Year->CLass[x / 100 - 1].Stu[i].FirstName << ","
				<< Year->CLass[x / 100 - 1].Stu[i].Name << "," << Year->CLass[x / 100 - 1].Stu[i].Sex << "," << Year->CLass[x / 100 - 1].Stu[i].DOB << ","
				<< Year->CLass[x / 100 - 1].Stu[i].ID << "," << Year->CLass[x / 100 - 1].Stu[i].Pass << endl;
		}
	}
	cout << "Your Pass was changed successfully." << endl;
}

void AddSem(Schoolyear*& Year, int& x)
{
	string temp;
	cout << "Please enter school year: ";
	cin >> temp;
	cout << endl;
	while (Year && temp != Year->NumOfYear)
	{
		Year = Year->YearNext;
	}
	if (!Year)
	{
		cout << "This year is not valid. Please enter again: " << endl;
		return;
	}
	cout << "Please enter semester: ";
	cin >> x;
	cin.ignore();
	x = x - 1;
	cout << "The form of date is dd/mm/yyyy." << endl;
	cout << "Please enter start date of this semester: ";
	getline(cin, Year->Sem[x].StartSem);
	cout << endl;
	cout << "Please enter end date of this semester: ";
	getline(cin, temp);
	cout << endl;
	Year->Sem[x].EndSem.day = (int)temp[0] * 10 + (int)temp[1] - 528;
	Year->Sem[x].EndSem.month = (int)temp[3] * 10 + (int)temp[4] - 528;
	Year->Sem[x].EndSem.year = (int)temp[6] * 1000 + (int)temp[7] * 100 + (int)temp[8] * 10 + (int)temp[9] - 53328;
}

void CreateCourse(Schoolyear*& Year, int& x)
{
	string temp;
	cout << "Please enter school year you created: ";
	cin >> temp;
	cout << endl;
	while (Year && temp != Year->NumOfYear)
	{
		Year = Year->YearNext;
	}
	if (!Year)
	{
		cout << "This year is not valid. Please enter again: " << endl;
		return;
	}
	cout << "Please enter semester you created: ";
	cin >> x;
	cin.ignore();
	x = x - 1;
	cout << "The form of date is dd/mm/yyyy." << endl;

	cout << "Please enter the date start to register course: ";
	getline(cin, temp);
	cout << endl;

	Year->Sem[x].StartReg.day = (int)temp[0] * 10 + (int)temp[1] - 528;
	Year->Sem[x].StartReg.month = (int)temp[3] * 10 + (int)temp[4] - 528;
	Year->Sem[x].StartReg.year = (int)temp[6] * 1000 + (int)temp[7] * 100 + (int)temp[8] * 10 + (int)temp[9] - 53328;

	cout << "Please enter the date end to register course: ";
	getline(cin, temp);
	cout << endl;

	Year->Sem[x].EndReg.day = (int)temp[0] * 10 + (int)temp[1] - 528;
	Year->Sem[x].EndReg.month = (int)temp[3] * 10 + (int)temp[4] - 528;
	Year->Sem[x].EndReg.year = (int)temp[6] * 1000 + (int)temp[7] * 100 + (int)temp[8] * 10 + (int)temp[9] - 53328;
	ifstream in(Year->NumOfYear + "_" + to_string(x + 1) + ".csv");

	if (!in.is_open())
	{
		cout << "Input fail.";
	}
	else
	{
		Course* Cur = nullptr;
		while (!in.eof())
		{
			if (!Year->Sem[x].pCourse)
			{
				Year->Sem[x].pCourse = new Course;
				Cur = Year->Sem[x].pCourse;
			}
			else
			{
				Cur->pNext = new Course;
				Cur = Cur->pNext;
			}
			getline(in, Cur->CourseID, ',');
			getline(in, Cur->NameOfCourse, ',');
			getline(in, Cur->NameOfTeacher, ',');
			getline(in, Cur->NumOfCredit, ',');
			getline(in, Cur->Day1, ',');
			getline(in, Cur->Session1, ',');
			getline(in, Cur->Day2, ',');
			getline(in, Cur->Session2);
			Cur->NumOfStu = 0;
			Cur->pNext = nullptr;
		}
		cout << "Input successfully." << endl << endl;
	}
}

void AddCou(Course*& Cou)
{
	Course* temp = new Course;
	temp->NumOfStu = 0;
	cout << "Please enter course ID: ";
	cin >> temp->CourseID;
	cin.ignore();

	cout << "Please enter Name of course: ";
	getline(cin, temp->NameOfCourse);

	cout << "Please enter teacher Name: ";
	getline(cin, temp->NameOfTeacher);

	cout << "Please enter number of credits: ";
	getline(cin, temp->NumOfCredit);

	cout << "Please enter day 1: ";
	getline(cin, temp->Day1);

	cout << "Please enter session 1: ";
	getline(cin, temp->Session1);

	cout << "Please enter day 2: ";
	getline(cin, temp->Day2);

	cout << "Please enter session 2: ";
	getline(cin, temp->Session2);

	temp->pNext = Cou;
	Cou = temp;
	cout << "Add new course successfully" << endl;
}

void ViewCou(Course* Cou, int& t, int& i)
{
	clear();
	int k = 1;
	int y = 16, a = 20;
	Course* Cur = Cou;
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
	cout << "Number of Students";
	gotoxy(a, 15);
	cout << "Session";
	while (Cur)
	{
		int x = 20;
		gotoxy(6, y);
		cout << k;
		gotoxy(8, y);
		cout << Cur->CourseID;
		gotoxy(x, y);
		x = x + 30;
		cout << Cur->NameOfCourse;
		gotoxy(x, y);
		x = x + 13;
		cout << Cur->NameOfTeacher;
		gotoxy(x, y);
		x = x + 14;
		cout << Cur->NumOfCredit;
		gotoxy(x, y);
		x = x + 15;
		cout << Cur->NumOfStu << "/" << 50;
		gotoxy(x, y);
		cout << "Thu " << Cur->Day1 << " Ca " << Cur->Session1 << " Thu " << Cur->Day2 << " Ca " << Cur->Session2;
		y = y + 1;
		Cur = Cur->pNext;
		k++;
		cout << endl;
	}
	t = y;
	i = k;
}

void UpdateCou(Schoolyear* Year, int Se)
{
	Course* Cur = Year->Sem[Se].pCourse;
	int count = 1, t, option;
	ViewCou(Year->Sem[Se].pCourse, t, count);
	t++;
	cout << "Please enter the course you want to update:";
	cin >> option;
	cin.ignore();
	Cur = Year->Sem[Se].pCourse;
	for (int i = 1; i < option; i++)
	{
		Cur = Cur->pNext;
	}
	cout << "You are choosing:" << Cur->NameOfCourse;
	cout << "1. Name of Teacher. ";
	cout << "2. Number of Credits. ";
	cout << "3. Present students enrolled. ";
	cout << "4. Day 1. ";
	cout << "5. Session 1. ";
	cout << "6. Day 2. ";
	cout << "7. Session 2. ";
	cout << "Enter your option: ";
	cin >> option;
	cin.ignore();
	switch (option)
	{
	case 1:
		cout << "Please Change the Name of teacher: ";
		getline(cin, Cur->NameOfTeacher);
		break;
	case 2:
		cout << "Please Change the number of credits: ";
		getline(cin, Cur->NumOfCredit);
		break;
	case 3:
		cout << "Please Change the student enrolled: ";
		cin >> Cur->NumOfStu;
		break;
	case 4:
		cout << "Please Change the day 1: ";
		getline(cin, Cur->Day1);
		break;
	case 5:
		cout << "Please Change the session 1: ";
		getline(cin, Cur->Session1);
		break;
	case 6:
		cout << "Please Change the day 2: ";
		getline(cin, Cur->Day2);
		break;
	case 7:
		cout << "Please Change the session 2: ";
		getline(cin, Cur->Session2);
		break;
	default:
		break;
	}
	cout << "Update course successfully";
}

void SaveInfoCou(Schoolyear* Year, int sem)
{
	Course* Cur = Year->Sem[sem].pCourse;
	ofstream course;
	course.open(Year->NumOfYear + "_" + (char)(sem + 49) + ".csv", ios::trunc);
	while (Cur != nullptr)
	{
		course << Cur->NameOfTeacher << "," << Cur->NumOfCredit << "," << Cur->NumOfStu << "," << Cur->Day1 << "," << Cur->Session1 << "," << Cur->Day2 << "," << Cur->Session2 << "\n";
		Cur = Cur->pNext;
	}
	course.close();
}

void DeleteCou(Schoolyear*& Year, int Se)
{
	Course* Cur = Year->Sem[Se].pCourse;
	int count = 1, t, option;
	ViewCou(Year->Sem[Se].pCourse, t, count);
	t++;
	cout << "Please enter the course you want to update:";
	cin >> option;
	cin.ignore();
	Cur = Year->Sem[Se].pCourse;
	if (option <= count)
	{
		if (option == 1)
		{
			Year->Sem[Se].pCourse = Year->Sem[Se].pCourse->pNext;
			delete Cur;
		}
		else
		{
			for (int i = 2; i < option; i++)
			{
				Cur = Cur->pNext;
			}

			Course* temp = Cur->pNext;
			Cur->pNext = Cur->pNext->pNext;
			delete temp;
			cout << "Delete course successfully.";
			//SaveInfoCourse(Year, sem); //Goi lai ham Save de luu thong tin vao file csv
		}
	}
	else
	{
		cout << "This course is not delted";
	}
}

void Now(Date& Today)
{
	time_t now = time(0);
	tm* ltm = localtime(&now);
	Today.year = 1900 + ltm->tm_year;
	Today.month = 1 + ltm->tm_mon;
	Today.day = ltm->tm_mday;
}

bool CheckDateRegister(Date Today, Date StartReg, Date EndReg)
{
	if (Today.year >= StartReg.year && Today.year <= EndReg.year) {
		if (Today.month >= StartReg.month && Today.month <= EndReg.month) {
			if (Today.day >= StartReg.day && Today.day <= EndReg.day) {
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
		return false;
	}
}

bool CheckDateEndSemester(Date Today, Date EndSem)
{
	if (Today.year > EndSem.year)
		return true;
	else if (Today.year == EndSem.year)
	{
		if (Today.month > EndSem.month)
			return true;
		else if (Today.month == EndSem.month)
			if (Today.day > EndSem.day)
				return true;
	}
	return false;
}

bool CheckImport(Schoolyear* Year, int x)
{
	if (!Year->CLass[x / 100 - 1].Stu[x % 100 - 1].Registered) return false;
	if (Year->CLass[x / 100 - 1].Stu[x % 100 - 1].Registered->Score.Final == "") return false;
	return true;
}

void CourseEnroll(Schoolyear* Year, Course* CourseHead, int x, int& NumOfOpt)
{
	int opt;
	int j = (x / 100) - 1;
	int k = (x % 100) - 1;
	Course* ListEnroll = Year->CLass[j].Stu[k].Registered;
	while (ListEnroll != nullptr && ListEnroll->pNext != nullptr)
	{
		ListEnroll = ListEnroll->pNext;
	}
	while (NumOfOpt != 5)
	{
	Enroll:
		Data* InfoCur = nullptr;
		int i = 1;
		Course* CourseCur = CourseHead;
		int t = 0;
		ViewCou(CourseCur, t, i);
		t++;
		i--;
		cout << "Register(0.stop): ";
		cin >> opt;
		while (opt > i || opt < 0)
		{
			cout << "Error. Register again: ";
			cout << "     ";
			cin >> opt;
			if (opt == 0)return;
		}

		if (opt == 0) return;


		int count = 1;
		while (CourseCur != nullptr && count != opt)
		{

			CourseCur = CourseCur->pNext;
			count++;

		}

		if (CourseCur != nullptr)
		{
			Course* EnrollMove = Year->CLass[j].Stu[k].Registered;
			while (EnrollMove != nullptr)
			{
				if (EnrollMove->Day1 == CourseCur->Day1)
				{
					if (EnrollMove->Session1 == CourseCur->Session1)
					{
						cout << "Conflicted with another course. Register again: " << endl;
						goto Enroll;
					}
				}
				if (EnrollMove->Day2 == CourseCur->Day2)
				{
					if (EnrollMove->Session2 == CourseCur->Session2)
					{
						cout << "Conflicted with another course. Register again:" << endl;
						goto Enroll;
					}
				}

				EnrollMove = EnrollMove->pNext;

			}
			Data* InfoMove = CourseCur->DataOfStu;
			while (InfoMove != nullptr && InfoMove->StudentID != Year->CLass[j].Stu[k].StudentID)
			{
				InfoMove = InfoMove->pNext;
			}

			if (InfoMove == nullptr && EnrollMove == nullptr)
			{
				if (CourseCur->NumOfStu < CourseCur->MaxStu)
				{

					Data* temp = new Data;
					temp->j = j;
					temp->k = k;
					temp->StudentID = Year->CLass[j].Stu[k].StudentID;
					temp->FirstName = Year->CLass[j].Stu[k].FirstName;
					temp->Name = Year->CLass[j].Stu[k].Name;
					temp->Sex = Year->CLass[j].Stu[k].Sex;
					temp->DOB = Year->CLass[j].Stu[k].DOB;
					temp->ID = Year->CLass[j].Stu[k].ID;
					temp->pNext = nullptr;


					if (CourseCur->DataOfStu == nullptr || CourseCur->DataOfStu->StudentID > temp->StudentID)
					{
						temp->pNext = CourseCur->DataOfStu;
						CourseCur->DataOfStu = temp;
					}
					else
					{
						InfoCur = CourseCur->DataOfStu;

						while (InfoCur->pNext != nullptr && InfoCur->pNext->StudentID < temp->StudentID)
						{
							InfoCur = InfoCur->pNext;
						}


						temp->pNext = InfoCur->pNext;
						InfoCur->pNext = temp;
					}


					if (ListEnroll != nullptr)
					{
						ListEnroll->pNext = new Course;
						ListEnroll = ListEnroll->pNext;
					}

					else
					{

						Year->CLass[j].Stu[k].Registered = new Course;
						ListEnroll = Year->CLass[j].Stu[k].Registered;
					}

					ListEnroll->CourseID = CourseCur->CourseID;
					ListEnroll->NameOfCourse = CourseCur->NameOfCourse;
					ListEnroll->NameOfTeacher = CourseCur->NameOfTeacher;
					ListEnroll->NumOfCredit = CourseCur->NumOfCredit;
					ListEnroll->Day1 = CourseCur->Day1;
					ListEnroll->Session1 = CourseCur->Session1;
					ListEnroll->Day2 = CourseCur->Day2;
					ListEnroll->Session2 = CourseCur->Session2;

					NumOfOpt++;
					CourseCur->NumOfStu++;
					ListEnroll->NumOfStu = CourseCur->NumOfStu;

					ListEnroll->pNext = nullptr;

				}

				else
				{
					cout << "Course is full. Register again: " << endl;
					goto Enroll;
				}

			}
			else
			{
				cout << "You have registered this course. Register again: " << endl;
				goto Enroll;
			}

		}

	}
}

void ViewListEnrolled(Schoolyear* Year, int x)
{
	int i = 1;
	int j = (x / 100) - 1;
	int k = (x % 100) - 1;
	Course* CourseCur = Year->CLass[j].Stu[k].Registered;
	while (CourseCur != nullptr)
	{
		cout << i << "." << CourseCur->CourseID << endl;
		cout << CourseCur->NameOfCourse << endl;
		cout << CourseCur->NameOfTeacher << endl;
		cout << CourseCur->NumOfCredit << endl;
		cout << CourseCur->Day1 << '/' << CourseCur->Session1 << endl;
		cout << CourseCur->Day2 << '/' << CourseCur->Session2 << endl;
		cout << CourseCur->NumOfStu << '/' << CourseCur->MaxStu << endl;
		CourseCur = CourseCur->pNext;
		i++;
	}
}

void RemoveCourseEnrolled(Schoolyear* Year, Course* CourseHead, int x)
{
	int j = (x / 100) - 1;
	int k = (x % 100) - 1;
	Data* InfoCur = nullptr;
	Course* ListEnroll = Year->CLass[j].Stu[k].Registered;
	Course* CourseCur = CourseHead;
	if (ListEnroll == nullptr) return;
	int optRemv, t = 0, i = 1;
	ViewCou(ListEnroll, t, i);
	t++; i--;
	cout << "Input num of the course to remove:";
	cin >> optRemv;
	Course* temp = nullptr;
	if (optRemv == 1)
	{
		Year->CLass[j].Stu[k].Registered = Year->CLass[j].Stu[k].Registered->pNext;
		temp = ListEnroll;
	}
	else
	{
		int count = 1;
		while (ListEnroll->pNext != nullptr && count != optRemv - 1)
		{
			ListEnroll = ListEnroll->pNext;
			count++;
		}

		if (ListEnroll->pNext != nullptr)
		{
			temp = ListEnroll->pNext;
			ListEnroll->pNext = temp->pNext;
		}
	}


	while (CourseCur != nullptr && CourseCur->CourseID != temp->CourseID)
	{
		CourseCur = CourseCur->pNext;
	}

	delete temp;

	if (CourseCur != nullptr)
	{
		InfoCur = CourseCur->DataOfStu;

		if (InfoCur->StudentID == Year->CLass[j].Stu[k].StudentID)
		{

			CourseCur->DataOfStu = CourseCur->DataOfStu->pNext;
			delete InfoCur;
		}
		else
		{
			while (InfoCur->pNext != nullptr && InfoCur->pNext->StudentID != Year->CLass[j].Stu[k].StudentID)
			{
				InfoCur = InfoCur->pNext;
			}

			if (InfoCur->pNext != nullptr)
			{
				Data* temp = InfoCur->pNext;
				InfoCur->pNext = temp->pNext;
				delete temp;
			}
		}
		CourseCur->NumOfStu--;
		Year->CLass[j].Stu[k].NumOfOpt--;
	}
	cout << "Remove course succesfully." << endl;
}

void ViewListClasses(Schoolyear* Year)
{
	string year = "";
	cout << "Enter the year you want to view class: ";
	cin >> year;
	cout << endl;
	while (Year != nullptr)
	{
		if (year == Year->NumOfYear)
		{
			for (int i = 0; i < Year->NumOfClass; i++)
			{
				cout << i + 1 << "." << Year->CLass[i].NameOfClass;
				cout << endl << endl;
			}

			break;
		}
		Year = Year->YearNext;
	}
	if (Year == nullptr)
	{
		cout << "The entered year is not available" << endl;
	}

}

void ViewListStudentInClass(Schoolyear* Year)
{
	string NameClass = "";
	cout << "Enter the Name class you want to view: ";
	cin >> NameClass;
	while (Year != nullptr)
	{
		for (int i = 0; i < Year->NumOfClass; i++)
		{
			if (NameClass == Year->CLass[i].NameOfClass)
			{
				clear();
				int k = 1;
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
				for (int j = 0; j < Year->CLass[i].NumOfStudent; j++)
				{
					int x = 13;
					gotoxy(8, y);
					cout << k;
					gotoxy(x, y);
					x = x + 15;
					cout << Year->CLass[i].Stu[j].StudentID;
					gotoxy(x, y);
					x = x + 30;
					cout << Year->CLass[i].Stu[j].FirstName << " " << Year->CLass[i].Stu[j].Name;
					gotoxy(x, y);
					x = x + 10;
					cout << Year->CLass[i].Stu[j].Sex;
					gotoxy(x, y);
					x = x + 22;
					cout << Year->CLass[i].Stu[j].DOB;
					gotoxy(x, y);
					cout << Year->CLass[i].Stu[j].ID;
					y = y + 1;
				}
				cout << endl << endl;
				return;
			}
		}
		Year = Year->YearNext;
	}
	if (Year == nullptr)
	{
		cout << "The entered Name of is not available" << endl;
	}
}

void ViewListStudentInCourse(Schoolyear* Year, int sem)
{
	string CourseID = "";
	cout << "Enter the course ID you want to view:";
	cin >> CourseID;
	Course* CourseCur = Year->Sem[sem].pCourse;
	while (CourseCur != nullptr)
	{
		if (CourseID == CourseCur->CourseID)
		{
			Data* Cur;
			Cur = CourseCur->DataOfStu;
			clear();
			int k = 1;
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
			while (k <= CourseCur->NumOfStu)
			{
				int x = 13;
				gotoxy(8, y);
				cout << k;
				gotoxy(x, y);
				x = x + 15;
				cout << Cur->StudentID;
				gotoxy(x, y);
				x = x + 30;
				cout << Cur->FirstName << " " << Cur->Name;
				gotoxy(x, y);
				x = x + 10;
				cout << Cur->Sex;
				gotoxy(x, y);
				x = x + 22;
				cout << Cur->DOB;
				gotoxy(x, y);
				cout << Cur->ID;
				y = y + 1;
				Cur = Cur->pNext;
				k++;
			}
			cout << endl << endl;
			return;
		}
		CourseCur = CourseCur->pNext;
	}
	if (CourseCur == nullptr)
	{
		cout << "The entered course is not available" << endl;
	}
}