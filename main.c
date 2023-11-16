/*

Started from : 3/10/2023 (  7: 39 PM)
Ended at     : 4/10/2023 ( 11: 44 PM)

Creator : LIM CUAN HEI
Class   : DFT Y1S1 Group 7 (year 2023)

Hour total spend : less than 24 (hour)


* There's some dirty useless code inside (repeated code)
* Due to lazy issue i am not going to remove those code
* Please remvoe it by yourself
* Assignment 2023 AACS1074 Programming Concepts and Design I

*/

// YouTube video 
// https://youtu.be/_QHUAPbdjC8?si=QrYY6kdhHFx5oHlm

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning (disable:4996)

#define ADMIN_ID "lim"
#define ADMIN_PASSWORD "123"

void intro();
void logo();
void menu();
void select(int selection);
void admin();
void adminPage();
void generateMarks();
void resultTable(char course[6][8], char grade[6][3], float gpa[4]);
void inputResult(int indexStudent);
int courseValidation(char courseCode[8], char grade[3]);
int creditHourValidation(char hour);
float gradeConvertor(char grade[3]);
int creditHourConvertor(char hour);
void studentInformation(int studentIndex);
void removeStudent(int studentIndex);
void student();
void studentRegister();
void studentLogin(char studentID[10], char studentPassword[50]);
int registeredStudent(char studentName[5000][50], char studentID[5000][10], char studentProgram[5000][8], int removeOrGenerate);


int adminIdCorrect = 0, STUDENTCREDITHOUR[5000][6]; //This is for re-enter admin password without re-entering admin ID
int numOfRegisteredStd = 0;
char STUDENTNAME[5000][50], STUDENTBIRTH[5000][11], STUDENTID[5000][10], STUDENTPROGRAM[5000][8], STUDENTPASSWORD[5000][50], STUDENTAGE[5000][3], STUDENTCOURSE[5000][6][8], STUDENTGRADE[5000][6][3]; // Sorry sir i am lazy to follow camel casing
float STUDENTGPA[5000][4], STUDENTPOINTS[5000][6];
char enter[50]; // for enter and back to menu use [useless]
char lastUpdate[100];
time_t t;


void main() {
	int i, x;
	intro();
	t = time(NULL);
	strftime(lastUpdate, sizeof(lastUpdate), "%c", localtime(&t)); //update the time at first before the admin updated student result.
	for (i = 0; i < 5000; i++) {
		strcpy(STUDENTNAME[i], "");
		strcpy(STUDENTNAME[i], "");
		strcpy(STUDENTBIRTH[i], "");
		strcpy(STUDENTID[i], "");
		strcpy(STUDENTPROGRAM[i], "");
		strcpy(STUDENTPASSWORD[i], "");
		for (x = 0; x < 6; x++) {
			strcpy(STUDENTCOURSE[i][x], "       ");
			strcpy(STUDENTGRADE[i][x], "  ");
		}
	}
	menu();
}

void intro() {
	char line1[] = " __            _____________     __       __ ",
		 line2[] = "|  |          |   __________|   |  |     |  |",
		 line3[] = "|  |          |  |              |  |_____|  |",
		 line4[] = "|  |          |  |              |   _____   |",
		 line5[] = "|  |          |  |              |  |     |  |",
		 line6[] = "|  |_______   |  |__________    |  |     |  |",
		 line7[] = "|__________|  |_____________|   |__|     |__|",
		 line8[] = "---------------------------------------------";

	printf("%s\n", line7); _sleep(200); system("cls");
	printf("%s\n%s\n",line6, line7); _sleep(200); system("cls");
	printf("%s\n%s\n%s\n", line5, line6, line7); _sleep(200); system("cls");
	printf("%s\n%s\n%s\n%s\n", line4, line5, line6, line7); _sleep(200); system("cls");
	printf("%s\n%s\n%s\n%s\n%s\n", line3, line4, line5, line6, line7); _sleep(200); system("cls");
	printf("%s\n%s\n%s\n%s\n%s\n%s\n", line2, line3, line4, line5, line6, line7); _sleep(200); system("cls");
	printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n", line1, line2, line3, line4, line5, line6, line7); _sleep(700); system("cls");
	printf("%s\n%s\n%s\n%s\n\n%s\n%s\n%s\n", line2, line3, line4, line8, line8, line5, line6); _sleep(400); system("cls");
	printf("%s\n%s\n%s\n\n\n%s\n%s\n%s\n", line3, line4, line8, line8, line5, line6); _sleep(400); system("cls");
	printf("%s\n%s\n\n\n\n\n%s\n%s\n", line4, line8, line8, line5); _sleep(400); system("cls");
	printf("%s\n\n\n\n\n\n\n%s\n", line8, line8); _sleep(400); system("cls");
}

void logo() {
	printf("\t\t __________ \n");
	printf("\t\t|          |\n");
	printf("\t\t|   LOGO   |\n");
	printf("\t\t|__________|\n\n");
}

void menu() {
	int selection;
	system("cls");
	logo();
	printf("Please select the funtion by using its number : \n\n");
	printf("(Student must register an account first)\n\n");

	printf("[0] Exit\n");
	printf("[1] Admin\n");
	printf("[2] Student\n\n");

	printf("Please input your selection > ");
	scanf("%d", &selection);
	rewind(stdin);
	select(selection);

}

void select(int select) {
	char quit;
	if (select == 0) {
		printf("Are you sure you want to exit ? [Y/N] \n");
		printf(">");
		quit = getchar();
		rewind(stdin);
		if (quit == 'Y' || quit == 'y')
			system("exit");
		else {
			system("cls");
			menu();
		}
	}
	else if (select == 1) {
		adminIdCorrect = 0;
		admin();
	}

	else if (select == 2)
		student();
	else {
		printf("[Invalid input]");
		_sleep(1000);
		system("cls");
		menu();
	}
}

void admin() {
	char adminIdInput[50], adminPswdInput[50];
	system("cls");
	logo();
	printf("[ You can always press [0] to return to the menu ]\n\n");
	printf("[ Please sign in to your admin account ]\n\n");
	if (adminIdCorrect == 0) {
		printf("Admin ID : ");
		gets(adminIdInput);
		rewind(stdin);
	}
	else {
		printf("Admin ID : lim\n");
		strcpy(adminIdInput, ADMIN_ID);
	}

	if (strcmp(adminIdInput, ADMIN_ID) == 0) {
		printf("Admin Password : ");
		gets(adminPswdInput);
		rewind(stdin);
		if (strcmp(adminPswdInput, ADMIN_PASSWORD) == 0)
			adminPage();
		else if (strcmp(adminPswdInput, "0") == 0)
			menu();
		else {
			printf("[ Invalid Admin Password ]");
			_sleep(1000);
			adminIdCorrect = 1;
			admin();
		}
	}
	else if (adminIdInput[0] == '0') {
		system("cls");
		menu();
		return 0;
	}
	else {
		printf("[ Invalid Admin ID ]");
		_sleep(1000);
		system("cls");
		admin();
	}
}

void adminPage() {
	int select;
	system("cls");
	logo();
	printf("[ You can always press [0] to return to the menu page ]\n\n");
	printf("[ You had successfully logged into administrator account ]\n\n");
	printf("Select the following function with its number :\n\n");
	printf("[1] Generate student marks\n");
	printf("[2] View student information\n");
	printf("[3] Remove a student\n\n");
	printf("Please input your selection > ");
	scanf("%d", &select);
	rewind(stdin);

	if (select == 0)
		menu();
	else if (select == 1)
		generateMarks();
	else if (select == 2) {
		system("cls");
		logo();
		printf("[Select the student by it's index number]\n");
		printf("----------------------------------------------------\n");
		studentInformation(registeredStudent(STUDENTNAME, STUDENTID, STUDENTPROGRAM, 3));
	}
	else if (select == 3) {
		system("cls");
		logo();
		printf("[Select the student by it's index number]\n");
		printf("----------------------------------------------------\n");
		removeStudent(registeredStudent(STUDENTNAME, STUDENTID, STUDENTPROGRAM, 2));
	}

	else {
		printf("[ Invalid input ]");
		_sleep(1000);
		adminPage();
	}

}

void generateMarks() {
	int indexStudent, selection;
	system("cls");
	logo();
	printf("[ You can always press [0] to return to the menu page ]\n\n");
	printf("[ Please select the student with using its index number ]\n\n");
	printf("-----------------------------------------------------------\n\n");
	indexStudent = registeredStudent(STUDENTNAME, STUDENTID, STUDENTPROGRAM, 1);

	system("cls");
	logo();
	printf("[ Generating Student %s Result ]\n\n", STUDENTNAME[indexStudent]);
	printf("Student Name  : %s\n", STUDENTNAME[indexStudent]);
	printf("Student ID    : %s\n", STUDENTID[indexStudent]);
	printf("Stuent Course : %s\n\n\n", STUDENTPROGRAM[indexStudent]);

	if (strcmp(STUDENTCOURSE[indexStudent][0], "       ") != 0) {
		resultTable(STUDENTCOURSE[indexStudent], STUDENTGRADE[indexStudent], STUDENTGPA[indexStudent]);
		printf("[Result has been generated]\n");
		printf("Do you want to regenerate the result ? \n\n");
		printf("[1] Regenerate \\ Edit \n");
		printf("[2] Select other student \n\n");
		printf("Input your selection > ");
		scanf("%d", &selection);
		rewind(stdin);
		if (selection == 0)
			adminPage();
		else if (selection == 1)
			inputResult(indexStudent);
		else if (selection == 2)
			generateMarks();
		else {
			printf("[Invalid input]");
			_sleep(1000);
			generateMarks();
		}
	}
	else
		inputResult(indexStudent);
}

void resultTable(char course[6][8], char grade[6][3], float gpa[4]) {
	printf(" _________________________________________________ \n");
	printf("|Result                                           |\n");
	printf("|_________________________________________________|\n");
	printf("|Semester 1                                       |\n");
	printf("|                                                 |\n");
	printf("|1.  %7.7s                            |  %c | %-2s |\n", course[0], course[0][6], grade[0]);
	printf("|2.  %7.7s                            |  %c | %-2s |\n", course[1], course[1][6], grade[1]);
	printf("|_________________________________________________|\n");
	printf("|Semester 2                                       |\n");
	printf("|                                                 |\n");
	printf("|3.  %7.7s                            |  %c | %-2s |\n", course[2], course[2][6], grade[2]);
	printf("|4.  %7.7s                            |  %c | %-2s |\n", course[3], course[3][6], grade[3]);
	printf("|_________________________________________________|\n");
	printf("|Semester 3                                       |\n");
	printf("|                                                 |\n");
	printf("|5.  %7.7s                            |  %c | %-2s |\n", course[4], course[4][6], grade[4]);
	printf("|6.  %7.7s                            |  %c | %-2s |\n", course[5], course[5][6], grade[5]);
	printf("|_________________________________________________|\n\n");
	printf("GPA semester 1 > %.2f\n", gpa[0]);
	printf("GPA semester 2 > %.2f\n", gpa[1]);
	printf("GPA semester 3 > %.2f\n", gpa[2]);
	printf("CGPA           > %.2f\n", gpa[3]);

}

void inputResult(int indexStudent) {
	int i = 0, valid = 0, hour21 = 0;
	char course[8], grade[2], lastChar;
	float totalCreditHour = 0, totalCreditPoint = 0;

	while (i < 6) {
		valid = 0;
		rewind(stdin);
		system("cls");
		logo();
		printf("[ You can always press [0] to escape ]\n\n");
		printf("Student Name    : %s\n", STUDENTNAME[indexStudent]);
		printf("Student ID      : %s\n", STUDENTID[indexStudent]);
		printf("Student Program : %s\n\n", STUDENTPROGRAM[indexStudent]);

		resultTable(STUDENTCOURSE[indexStudent], STUDENTGRADE[indexStudent], STUDENTGPA[indexStudent]);
		printf("%d. Enter course code [eg. AAA1004] > ", i + 1);
		gets(course);
		rewind(stdin);
		printf("Enter the grade for the course [A, A-, B+, B, B-, C+, C, F] > ");
		gets(grade);
		rewind(stdin);
		grade[0] = toupper(grade[0]);
		valid = courseValidation(course, grade);
		if (valid == 0) {
			strcpy(STUDENTCOURSE[indexStudent][i], course);
			strcpy(STUDENTGRADE[indexStudent][i], grade);
		}

		i -= valid;
		i++;
	}

	for (i = 0; i < 6; i++) {
		STUDENTPOINTS[indexStudent][i] = gradeConvertor(STUDENTGRADE[indexStudent][i]);
		STUDENTCREDITHOUR[indexStudent][i] = creditHourConvertor(STUDENTCOURSE[indexStudent][i][6]);
		hour21 += STUDENTCREDITHOUR[indexStudent][i];
	}

	if (hour21 < 21) {
		for (i = 0; i < 6; i++) {
			valid = 0;
			system("cls");
			logo();
			printf("[ERROR : The total credit hour must hit at least 21 hour]\n");
			printf("[ You can always press [0] to escape ]\n\n");
			printf("Student Name    : %s\n", STUDENTNAME[indexStudent]);
			printf("Student ID      : %s\n", STUDENTID[indexStudent]);
			printf("Student Program : %s\n\n", STUDENTPROGRAM[indexStudent]);

			resultTable(STUDENTCOURSE[indexStudent], STUDENTGRADE[indexStudent], STUDENTGPA[indexStudent]);

			printf("Please re-enter the course credit hour for [%s] [1 ~ 9] > ", STUDENTCOURSE[indexStudent][i]);
			scanf("%c", &lastChar);
			rewind(stdin);
			valid = creditHourValidation(lastChar);
			if (valid == 0) {
				STUDENTCOURSE[indexStudent][i][6] = lastChar;
			}
			i -= valid;
		}
		hour21 = 0;
	}

	for (i = 0; i < 6; i++) {
		STUDENTCREDITHOUR[indexStudent][i] = creditHourConvertor(STUDENTCOURSE[indexStudent][i][6]);
		hour21 += STUDENTCREDITHOUR[indexStudent][i];
	}
	if (hour21 < 21) {
		system("cls");
		printf("[Due to student credit hour after re-entered still below 21 system will automatically generate the credit hour]\n");
		_sleep(2000);
		for (i = 0; i < 6; i += 2) {
			STUDENTCOURSE[indexStudent][i][6] = '4';
			STUDENTCOURSE[indexStudent][i + 1][6] = '3';
		}
	}
	for (i = 0; i < 6; i++) {
		STUDENTCREDITHOUR[indexStudent][i] = creditHourConvertor(STUDENTCOURSE[indexStudent][i][6]);
	}
	STUDENTGPA[indexStudent][0] = (STUDENTPOINTS[indexStudent][0] * STUDENTCREDITHOUR[indexStudent][0] + STUDENTPOINTS[indexStudent][1] * STUDENTCREDITHOUR[indexStudent][1]) / (STUDENTCREDITHOUR[indexStudent][0] + STUDENTCREDITHOUR[indexStudent][1]);
	STUDENTGPA[indexStudent][1] = (STUDENTPOINTS[indexStudent][2] * STUDENTCREDITHOUR[indexStudent][2] + STUDENTPOINTS[indexStudent][3] * STUDENTCREDITHOUR[indexStudent][3]) / (STUDENTCREDITHOUR[indexStudent][2] + STUDENTCREDITHOUR[indexStudent][3]);
	STUDENTGPA[indexStudent][2] = (STUDENTPOINTS[indexStudent][4] * STUDENTCREDITHOUR[indexStudent][4] + STUDENTPOINTS[indexStudent][5] * STUDENTCREDITHOUR[indexStudent][5]) / (STUDENTCREDITHOUR[indexStudent][4] + STUDENTCREDITHOUR[indexStudent][5]);
	for (i = 0; i < 6; i++) {
		totalCreditHour += STUDENTCREDITHOUR[indexStudent][i];
		totalCreditPoint += STUDENTPOINTS[indexStudent][i] * STUDENTCREDITHOUR[indexStudent][i];
	}
	STUDENTGPA[indexStudent][3] = totalCreditPoint / totalCreditHour;

	system("cls");
	logo();
	printf("[ You can always press [0] to escape ]\n\n");
	printf("Student Name    : %s\n", STUDENTNAME[indexStudent]);
	printf("Student ID      : %s\n", STUDENTID[indexStudent]);
	printf("Student Program : %s\n\n", STUDENTPROGRAM[indexStudent]);

	resultTable(STUDENTCOURSE[indexStudent], STUDENTGRADE[indexStudent], STUDENTGPA[indexStudent]);
	/* Retrieve the current time */
	t = time(NULL);
	/* Output the current year into the result string */
	strftime(lastUpdate, sizeof(lastUpdate), "%c", localtime(&t));
	printf("\nPress [ENTER] to return to admin page > ");
	gets(enter);
	rewind(stdin);
	adminPage();
}

int courseValidation(char courseCode[8], char grade[3]) {
	if (strlen(courseCode) != 7) {
		printf("[Invalid course]");
		_sleep(1000);
		return 1;
	}
	if (strcmp(grade, "A") == 0 || strcmp(grade, "A-") == 0 || strcmp(grade, "B+") == 0 || strcmp(grade, "B") == 0 || strcmp(grade, "B-") == 0 || strcmp(grade, "C+") == 0 || strcmp(grade, "C") == 0 || strcmp(grade, "F") == 0)
		return 0;
	else {
		printf("[Invalid Grade]");
		_sleep(1000);
		return 1;
	}

	return creditHourValidation(courseCode[6]);
}

float gradeConvertor(char grade[3]) {
	if (strcmp(grade, "A") == 0)
		return 4.0;
	else if (strcmp(grade, "A-") == 0)
		return 3.75;
	else if (strcmp(grade, "B+") == 0)
		return 3.50;
	else if (strcmp(grade, "B") == 0)
		return 3;
	else if (strcmp(grade, "B-") == 0)
		return 2.75;
	else if (strcmp(grade, "C+") == 0)
		return 2.5;
	else if (strcmp(grade, "C") == 0)
		return 2.0;
	else
		return 0;
}

int creditHourValidation(char courseCode) {
	switch (courseCode) {
	case'1':
	case'2':
	case'3':
	case'4':
	case'5':
	case'6':
	case'7':
	case'8':
	case'9':
		return 0;
		break;
	default:
		printf("[Invalid course]");
		_sleep(1000);
		return 1;
	}
}

int creditHourConvertor(char hour) {
	switch (hour) {
	case'1':
		return 1;
		break;
	case'2':
		return 2;
		break;
	case'3':
		return 3;
		break;
	case'4':
		return 4;
		break;
	case'5':
		return 5;
		break;
	case'6':
		return 6;
		break;
	case'7':
		return 7;
		break;
	case'8':
		return 8;
		break;
	case'9':
		return 9;
		break;
	default:
		return 0;
	}
}

void studentInformation(int studentIndex) {
	system("cls");
	logo();
	printf("----------------------------------------------\n");
	printf("[View student information]\n\n");
	printf("Student Name      : %s\n", STUDENTNAME[studentIndex]);
	printf("Student ID        : %s\n", STUDENTID[studentIndex]);
	printf("Student Programme : %s\n", STUDENTPROGRAM[studentIndex]);
	printf("Student Birth     : %s\n", STUDENTBIRTH[studentIndex]);
	printf("student Password  : %s\n", STUDENTPASSWORD[studentIndex]);
	if (strcmp(STUDENTCOURSE[studentIndex][0], "       ") == 0) {
		printf("Student Result    : Not Yet Generated\n\n");
		printf("(Press [ENTER] to return admin page)");
		gets(enter);
		rewind(stdin);
		adminPage();
	}
		
	else {
		printf("Student Result   : Generated\n\n");
		printf("Student GPA (Semester 1) : %.2f\n", STUDENTGPA[studentIndex][0]);
		printf("Student GPA (Semester 2) : %.2f\n", STUDENTGPA[studentIndex][1]);
		printf("Student GPA (Semester 3) : %.2f\n", STUDENTGPA[studentIndex][2]);
		printf("Student CGPA             : %.2f\n", STUDENTGPA[studentIndex][3]);
		if (STUDENTGPA[studentIndex][3] < 2) {
			printf("Student Status           : FAILED\n\n");
		}
			
		else {
			printf("Student Status           : PASSED\n\n");
		}
		printf("(Press [ENTER] to return admin page)");
		gets(enter);
		rewind(stdin);
		adminPage();
	}
}

void removeStudent(int studentIndex) {
	char yesNo;
	system("cls");
	logo();
	printf("Student Name      : %s\n", STUDENTNAME[studentIndex]);
	printf("Student ID        : %s\n", STUDENTID[studentIndex]);
	printf("Student Programme : %s\n\n", STUDENTPROGRAM[studentIndex]);

	printf("Are you sure you want to remove this student [Y/N] > ");
	yesNo = getchar();
	yesNo = toupper(yesNo);
	if (yesNo == 'Y') {
		strcpy(STUDENTID[studentIndex], "Canceled");
		printf("\n[Student cancelled]\n");
		printf("(Press [ENTER] to return admin page)");
		gets(enter);
		rewind(stdin);
		adminPage();
	}


	else if (yesNo == 'N') {
		system("cls");
		logo();
		printf("[Select the student by it's index number]\n");
		printf("----------------------------------------------------\n");
		removeStudent(registeredStudent(STUDENTNAME, STUDENTID, STUDENTPROGRAM, 2));
	}
	else {
		printf("[Invalid input]\n");
		_sleep(700);
		system("cls");
		removeStudent(studentIndex);
	}
}

void student() {
	int select;
	char studentID[10], studentPswd[50];
	system("cls");
	logo();
	printf("[ You can always press [0] to return to the menu page ]\n\n");
	printf("Please select the funtion by using its number : \n\n");
	printf("[1] Register\n");
	printf("[2] Log In\n\n");
	printf("Input your selection > ");
	scanf("%d", &select);
	rewind(stdin);
	if (select == 0)
		menu();
	else if (select == 1)
		studentRegister();
	else if (select == 2) {
		system("cls");
		logo();
		printf("[ Student log in page ]\n");
		printf("Student ID [KPKL00001] : ");
		scanf("%s", &studentID);
		rewind(stdin);
		if (studentID == 0)
			student();
		printf("Student Password : ");
		gets(studentPswd);
		rewind(stdin);
		if (strcmp(studentPswd, "0") == 0) {
			student();
		}
		studentLogin(studentID, studentPswd);
	}
	else {
		printf("[ Invalid input ]");
		_sleep(1000);
		student();
	}
}

void studentRegister() {
	int i, birthValid = 0, programmeValid = 0;
	char name[50], birth[11], course[8], password[50];
	char studentIdTemp[10] = "KPKL", idTemp[6];
	system("cls");
	logo();
	printf("[ You can always press [0] to return to the menu page ]\n\n");
	printf("Name : ");
	gets(name);
	rewind(stdin);
	do {
		birthValid = 0;
		printf("Birth eg. [24/08/2005] : ");
		gets(birth);
		rewind(stdin);
		for (i = 0; i < strlen(birth); i++) {
			if (birth[i] == '/')
				birthValid += 1;

			else if (birth[i] != '/') {

				if ((i == strlen(birth) - 1) && birthValid != 2) {
					printf("[Birth format error]\n\n");

				}
			}

		}
	} while (birthValid != 2);
	do {
		programmeValid = 0;
		printf("Course [DFT , DCS , DIS] : ");
		gets(course);
		rewind(stdin);
		for (i = 0; i < strlen(course); i++) {
			course[i] = toupper(course[i]);
		}
		if (strcmp(course, "DFT") == 0 || strcmp(course, "DCS") == 0 || strcmp(course, "DIS") == 0)
			programmeValid = 1;
		else
			printf("[Invalid Programme]\n\n");
	} while (programmeValid != 1);

	printf("Password : ");
	gets(password);
	rewind(stdin);
	for (i = 0; i < 3; i++) {
		course[i] = toupper(course[i]);
	}

	strcpy(STUDENTNAME[numOfRegisteredStd], name);
	strcpy(STUDENTBIRTH[numOfRegisteredStd], birth);
	strcpy(STUDENTPROGRAM[numOfRegisteredStd], course);
	strcpy(STUDENTPASSWORD[numOfRegisteredStd], password);
	sprintf(idTemp, "%05d", numOfRegisteredStd + 1);
	strcat(studentIdTemp, idTemp);
	strcpy(STUDENTID[numOfRegisteredStd], studentIdTemp);
	system("cls");
	logo();
	printf("\n[Account created successfully]\n\n");
	printf("Student Name      : %s\n", STUDENTNAME[numOfRegisteredStd]);
	printf("Student ID        : %s\n", STUDENTID[numOfRegisteredStd]);
	printf("Student Birth     : %s\n", STUDENTBIRTH[numOfRegisteredStd]);
	printf("Student Programme : %s\n", STUDENTPROGRAM[numOfRegisteredStd]);
	printf("Password          : %s\n\n\n", STUDENTPASSWORD[numOfRegisteredStd]);

	numOfRegisteredStd += 1;
	printf("Press [ENTER] to return back to student page > ");
	gets(enter);
	rewind(stdin);
	student();
}

void studentLogin(char studentLoginID[10], char studentPassword[50]) {
	int accountFound = 0, studentIndex, i;
	printf("\n\nLoading ...\n");
	_sleep(500); //just for waiting purpose not really usees
	for (i = 0; i < 4; i++) {
		studentLoginID[i] = toupper(studentLoginID[i]);
	}
	for (i = 0; i < 5000; i++) {
		if (strcmp(studentLoginID, STUDENTID[i]) == 0) {
			accountFound = 1;
			studentIndex = i;
			i = 5000;
		}
	}
	if (accountFound == 1) {
		if (strcmp(studentPassword, STUDENTPASSWORD[studentIndex]) == 0) {
			system("cls");
			logo();
			printf("[ Successfully logged in ]\n\n");
			printf("Student Name      : %s\n", STUDENTNAME[studentIndex]);
			printf("Student ID        : %s\n", STUDENTID[studentIndex]);
			printf("Student Programme : %s\n", STUDENTPROGRAM[studentIndex]);
			if (strcmp(STUDENTCOURSE[studentIndex][0], "       ") == 0) {
				printf("\nDear %s,\n\n", STUDENTNAME[studentIndex]);
				printf("\tSorry %s , we not yet uploaded your result. \n\tPlease kindly wait for the admin to input. \n\n", STUDENTNAME[studentIndex]);
				printf("Last update from Admin at :%s\n\n", lastUpdate);
				printf("\n(Press [ENTER] to return student page)\n");
				gets(enter);
				student();
			}
			resultTable(STUDENTCOURSE[studentIndex], STUDENTGRADE[studentIndex], STUDENTGPA[studentIndex]);

			printf("(Press [ENTER] to return menu page)");
			gets(enter);
			rewind(stdin);
			menu();
		}
		else {
			printf("[Wrong Password]\n\n");
			printf("(Press [ENTER] to return student page)");
			gets(enter);
			student();
		}
	}
	else if (accountFound == 0) {
		system("cls");
		logo();
		printf("[ Sorry, you might be kicked out from the school or you had not registered your account ]\n\n");
		printf("(Press [ENTER] to return student page)\n");
		gets(enter);
		rewind(stdin);
		student();
	}
}

int registeredStudent(char studentName[5000][50], char studentID[5000][10], char studentProgram[5000][8], int removeOrGenerate) { //that 5000 is due to the question is required only 5000 student
	int i, haveStudent = 1, chooseStudent;
	if (strcmp(studentName[0], "") == 0) {
		printf("\n[No student has registered yet]\n\n");
		haveStudent = 0;
		printf("(Press [ENTER] to return admin page)");
		gets(enter);
		rewind(stdin);
		adminPage();
	}

	if (haveStudent != 0) {
		system("cls");
		logo();
		printf("[Select the student by it's index number]\n");
		printf("----------------------------------------------------\n");
		printf(" ___________________________________________________ \n");
		printf("|%6s  |%20s |%10s |%7s |\n", "Index", "Student Name", "Student ID", "Program");
		printf("|___________________________________________________|\n");
		for (i = 0; i < numOfRegisteredStd; i++) {
			printf("|%6d. |", i + 1);
			printf("%20s |", studentName[i]);
			printf("%10s |", studentID[i]);
			printf("%7s |", studentProgram[i]);
			printf("\n");
		}
		printf("|___________________________________________________|\n");
		printf("\nPlease select the student > ");
		scanf("%d", &chooseStudent);
		rewind(stdin);
	}
	
	if (chooseStudent == 0)
		adminPage();
	else if (chooseStudent > 0 && chooseStudent <= numOfRegisteredStd) {
		chooseStudent -= 1;
		return chooseStudent;
	}
	else {
		if (removeOrGenerate == 1) {
			printf("[Invalid input]\n");
			_sleep(1000);
			generateMarks();
		}
		else if (removeOrGenerate == 2) {
			printf("[Invalid input]\n");
			_sleep(1000);
			logo();
			removeStudent(registeredStudent(STUDENTNAME, STUDENTID, STUDENTPROGRAM, 2));
		}
		else if (removeOrGenerate == 3) {
			
			printf("[Invalid input]\n");
			_sleep(1000);
			system("cls");
			studentInformation(registeredStudent(STUDENTNAME, STUDENTID, STUDENTPROGRAM, 3));
		}

	}

}
