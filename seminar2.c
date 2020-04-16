#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)  


typedef struct lesson {
	char title[8];
	unsigned long length;	/*total length of characters in the text file*/
}lesson;

typedef struct
{
	char name[8];
	char lesson_title[8];
	char gross_speed[8];
	char accuracy[8];
	char score[8];
	int  usernum;
}user;


FILE* userlist;	/*user list file*/
int nusers; /*user number*/
FILE* fllist;	/*lesson list file*/
FILE* fuser;	/*current user data file*/
lesson cl;	/*current lesson*/
user cu;	/*current user*/


//파일에 몇개의 데이터가 있는지 계산
int datanum(FILE* fp) {
	int filesize;
	int n;
	fseek(fp, 0, SEEK_END);
	filesize = ftell(fp);
	n = filesize / sizeof(user);

	return n;
}


void loadFiles(void) {

	FILE* data;
	int n = 3;
	lesson l1;
	if ((userlist = fopen("userlist.txt", "rb+")) == NULL)	/*if file is not created or is missing*/
	{
		printf("\n\nFile does not exist..\n Creating new...");
		userlist = fopen("userlist.txt", "wb");	/*then create it*/
		nusers = 0;	/*no users yet*/
		fwrite(&nusers, sizeof(int), 1, userlist);
		fclose(userlist);
		userlist = fopen("userlist.txt", "rb+");
	}
	else	/*userlist.dat exists,*/
	{
		fread(&nusers, sizeof(int), 1, userlist);	/*read*/
	}
	if ((data = fopen("data.txt", "rb")) == NULL)
	{
		data = fopen("data.txt", "wb");
		fclose(data);
	}
	else fclose(data);

	fllist = fopen("lessonlist.txt", "wb");
	fwrite(&n, sizeof(int), 1, fllist);
	strcpy(l1.title, "atoz");
	l1.length = 448;
	fwrite(&l1, sizeof(lesson), 1, fllist);
	strcpy(l1.title, "hooks");
	l1.length = 1757;
	fwrite(&l1, sizeof(lesson), 1, fllist);
	fclose(fllist);


}



int listUser(void) {
	
	int i;
	char userfilename[12];	/*including a period & extension*/
	if (nusers == 0)
	{
		printf("\n\nNo users exist...");
		printf("\npress any key to continue...");
		getch();
		return -1;
	}
	printf("\nno. of users: %d", nusers);

	fseek(userlist, sizeof(int), SEEK_SET);
	for (i = 1; i <= nusers; i++)	/*list them*/
	{
		fread(&cu, sizeof(user), 1, userlist);	/*read*/
		printf("\n(%d) %.8s", i, cu.name);
		// fseek(fulist,sizeof(user),SEEK_SET);
	}
	/*now allow the use to select correct user name from the list*/
	
	return 0;
}

int userSelectMenu(void) {
	return 0;
}


void createUser(void) {


	printf("=========================== \n");
	printf("  ADD A NEW USER \n");
	printf("Name :");
	scanf("%s", cu.name);
	printf("lesson_title : ");
	scanf("%s", cu.lesson_title);
	printf("gross_speed : ");
	scanf("%s", cu.gross_speed);
	printf("accuracy : ");
	scanf("%s", cu.accuracy);
	printf("score : ");
	scanf("%s", cu.score);
	printf("=========================== \n");
	nusers++;
	cu.usernum = nusers;
	fseek(userlist, 0, SEEK_END);
	fwrite(&cu, sizeof(user), 1, userlist);// 파일에 data위치의 데이타 size *n개 쓰기

	//printf(userfilename, "%s.dat", cu.name);
	//fuser = fopen(userfilename, "wb");			/*create file*/
	//fclose(fuser);
	//fuser = fopen(userfilename, "r+b");


}





int listLesson(void) {
	lesson l1, l2, l3;
	int n;
	int option;
	char filename[12];
	/*open the lesson list file and list them all*/
	fllist = fopen("lessonlist.dat", "rb");
	fread(&n, sizeof(int), 1, fllist);
	printf("\nnumber of lesson: %d", n);/*3 lessons only*/
	fread(&l1, sizeof(lesson), 1, fllist);	/*read*/
	printf("\n(1) %.8s %ld characters", l1.title, l1.length);
	fread(&l2, sizeof(lesson), 1, fllist);	/*read*/
	printf("\n(2) %.8s %ld characters", l2.title, l2.length);
	fread(&l3, sizeof(lesson), 1, fllist);	/*read*/
	/*now allow the use to select correct user name from the list*/
	

}
void Session() {
	//직접 속도 계산하는 타자연습 구현하는부분인거같음
}
int mainmenu(void) {
	int menunum;
	while (1)
	{
		printf("***MAIN MENU***\n\n");
		printf("<1> Select User\n");
		printf("<2> Stastics\n");
		printf("<3> View User Records\n");
		printf("<4> About\n");
		printf("<5> Quit\n");
		printf("Enter the choice : ");

		scanf("%d", &menunum);

		switch (menunum) {
		case 1: createUser();
			loadFiles();
			userSelectMenu();
			break;
		case 2: listUser();
			break;
		case 3: listLesson();
			break;
		case 4: printf("\n\n매우 어려운 과제였습니다. 그래도 수고한 팀원에게 박수를 보냅니다.\n\n");
			break;
		}
		if (menunum == 5) {
			printf("\n\n 질문 있으실까요? \n 이상 마치겠습니다.\n\n");
			break;
		}
	}

}

void main() {
	mainmenu();
	
}
