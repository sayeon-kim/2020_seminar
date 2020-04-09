#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)      
#define DELETED ""

typedef struct Student {
	char address[20];
	char phone[20];
	char name[20];
	char email[20];
}student;

#define FILENAME "data.txt"

void menu() {
	printf("     Main Menu \n");
	printf("\n--------------------------\n ");
	printf("[1] Add a new Contact \n");
	printf("[2] List all Contacts \n");
	printf("[3] Search for contact \n");
	printf("[4] Edit a Contact \n");
	printf("[5] Delete a Contact \n");
	printf("[6] 이스터에그 \n");
	printf("[0] Exit \n");
	printf("\n--------------------------\n ");
	printf("Enter the choice : ");

}
//파일에 몇개의 데이터가 있는지 계산
int datanum(FILE* fp) {
	int filesize;
	int n;
	fseek(fp, 0, SEEK_END);
	filesize = ftell(fp);
	n = filesize / sizeof(student);

	return n;
}

//display
void view_data(student* data)
{
	printf("Name-%s \n전화번호-%s,  \nAddress : %s\nEmail-%s \n\n", data->name, data->phone, data->address, data->email);
	printf("========================\n");
}

//파일 추가
void add(FILE* fp) {
	student data;
	printf("=========================== \n");
	printf("  ADD A NEW CONTACT\n");
	printf("Name :");
	scanf("%s", data.name);
	printf("Phone : ");
	scanf("%s", data.phone);
	printf("Address : ");
	scanf("%s", data.address);
	printf("Email : ");
	scanf("%s", data.email);
	printf("=========================== \n");



	fseek(fp, 0, SEEK_END); //끝으로 이동
	fwrite(&data, sizeof(data), 1, fp);// 파일에 data위치의 데이타 size *n개 쓰기
}


void list(FILE* fp)
{
	student data;
	int nd;
	nd = datanum(fp);
	printf("=========================== \n");
	printf("  LIST OF CONTACTS\n");





	fseek(fp, 0, SEEK_SET);
	while (nd--) {
		fread(&data, sizeof(data), 1, fp);//파일에서 data 위치로 size * n개 읽기
		view_data(&data);
	}
	printf("=========================== \n");
}

void search(FILE* fp) {
	student data;
	char search_name[20]; //찾을 이름
	int n;
	int nd;

	printf("=========================== \n");
	printf("  SEARCH FOR CONTACT\n");
	nd = datanum(fp);

	printf("search name :");
	scanf("%s", search_name);
	printf("\n");
	printf("---contact ---");
	fseek(fp, 0, SEEK_SET); //처음으로 이동
	for (n = 0; n < nd; n++) {
		fread(&data, sizeof(data), 1, fp);
		if (strcmp(data.name, search_name) == 0)break;
	}

	view_data(&data);
}

void contact(student* data) {
	while (getchar() != '\n');
	//fflush(stdin);// 입력버퍼인 stdin 을 지워준다.  이것보다는 위에  while문을 사용하는게 좋다.
	//원래대로는 fflush 함수의 인자로 stdin 이 전달될 수 없지만 visual studio에서만 예외적으로 허용되어있다.
	//실제로 다른 컴파일러에서는 사용 no
	printf("Name :");
	gets(data->name);
}
void update_data(student* data) {
	printf("Name :");
	gets(data->name);
	printf("Phone :");
	gets(data->phone);
	printf("Address :");
	gets(data->address);
	printf("Email :");
	gets(data->email);
	
}


void edit(FILE* fp, int n) {
	//n은 변경할 record 번호

	student new_data, origin_data;
	int nd;
	printf("=========================== \n");
	printf("  EDIT A CONTACT\n");
	printf("변경할 데이터 이름 \n");
	contact(&new_data);

	nd = datanum(fp);
	fseek(fp, 0, SEEK_SET);

	for (n = 0; n < nd; n++) {
		fread(&origin_data, sizeof(origin_data), 1, fp);
		if (strcmp(origin_data.name, new_data.name) == 0)
			break;

	}

	printf(" New data 입력\n");
	update_data(&new_data);

	fseek(fp, sizeof(new_data)*n, SEEK_SET);
	fwrite(&new_data, sizeof(new_data), 1, fp);
	
	
}

void delete(FILE* fp, int n) {
	student delete_data = {DELETED,DELETED,DELETED,DELETED};
	student new_data, origin_data;

	int choose;
	int nd;

	printf("============================\n");
	printf("  DELETE A CONTACT\n");
	//삭제할 번호 = n
	contact(&new_data);
	nd = datanum(fp);
	
	fseek(fp, 0, 0);

	for (n = 0; n < nd; n++) {
		fread(&origin_data, sizeof(origin_data), 1, fp);
		if (strcmp(origin_data.name, new_data.name) == 0)
			break;
	}

	printf("DELETE 1/0 : ");
	scanf("%d", &choose);
	printf("\n");

	if (choose == 1) {
		fseek(fp, sizeof(new_data) * n, SEEK_SET);
		fwrite(&delete_data, sizeof(delete_data), 1, fp);
		printf("CONTACT IS DELETED! \n");
	}
	else if (choose == 0)return;

}


void main() {
	FILE* fp;
	int menunum;
	int sequence = -1; // 변경/삭제대상 record 번호

	if ((fp = fopen(FILENAME, "r+b")) == NULL) {
		//파일 이 없으면 
		fp = fopen(FILENAME, "w+b");
		if (fp == NULL) {
			printf("파일을 열 수 업습니다.. \n");
			exit(0);
		}
	}

	while (1) {
		do {
			menu();
			scanf("%d", &menunum);
		} while (menunum!=0 &&(menunum < 1 || menunum >7));
		if (menunum == 0)break;
		switch (menunum) {
			case 1: add(fp);
				break;
			case 2: list(fp);
				break;
			case 3: search(fp);
				break;
			case 4: edit(fp,sequence);
				sequence = -1;
				break;
			case 5: delete(fp, sequence);
				break;
			case 6: printf(" -----이스터에그-----\n");
					printf("이예진 김사연 화이팅*^^*~~!!!!!!!!!!!!!!!!!!!!\n");
				break;
		
		}
	}
}
