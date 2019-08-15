#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

int j,i = 0;
FILE *N_file = NULL;			//파일을 가리키는 포인터
char search[20];
char RE_name[20];
int R_count;
 
typedef struct numberbook {		//구조체 선언
	char name[20];
	char number[20];
	char cut_number[300];
}NUMBERBOOK;					//구조체를 새로운 타입 NUMBERBOOK으로 묶음

void Main_Print(int i);
void modify_number();
void New_number(FILE *N_file);
void delete_number();
void see_number();
void search_record(FILE *N_file);
void search_record2(FILE *N_file);
void print_record(NUMBERBOOK);
void SE_record2(FILE *N_file);
void SE_record(FILE *N_file);

void main() {

	Main_Print(i);
	New_number(N_file);

}

void Main_Print(int i) {
	printf("원하는 메뉴를 선택하세요\n\n");
	printf("1. 신규 정보 저장\t2. 정보수정\t3. 정보 삭제\t4. 전화번호부 보기\t5. 프로그램종료\n\n");
	scanf_s("%d", &i);
	switch (i)		//입력받은 i의 값에 따라 실행
	{
	case 1: 
		New_number(N_file);
		break;
	case 2: 
		{
		modify_number();
		break;}
	case 3: 
		{delete_number();
		break;}
	case 4: 
		{
		see_number();
		break;
		}
	case 5: exit(1);
	default: 
		printf("========올바른 번호를 다시 선택하세요========\n");
		Main_Print(i);
		break;
	}
}

void New_number(FILE *N_file) {

	NUMBERBOOK data;
	NUMBERBOOK data2;

	int count = 0;

	fopen_s(&N_file, "N_file.bin", "a+");
	if (N_file == NULL) {
		puts("입력을 위한 파일을 열 수 없습니다.\n");
		exit(1);
	}
	else {
		puts("전화번호부 구동에 필요한 파일을 생성 or 오픈 했습니다.\n");
	}

	fflush(stdin);
	getchar();

	printf("\n======신규 입력 선택======\n\n");

	printf("이름을 입력하세요.\n");
	gets(data.name);

	printf("휴대폰 번호를 입력하세요\n");
	gets(data.number);

	printf("설정할 단축번호를 입력하세요.");
	gets(data.cut_number);


	fseek(N_file, 0, SEEK_END);
	fwrite(&data, sizeof(data), 1, N_file);

	fclose(N_file);

	Main_Print(i);
}


void modify_number() {
	printf("\n======정보 수정 선택======\n\n");

	fopen_s(&N_file, "N_file.bin", "rb+");
	if(N_file==NULL) {
		puts("파일 열기 오류");
		exit(1);
	}

	printf("1. 이름으로 찾기\n2.단축번호로 찾기\n3. 메인화면으로\n\n");
	scanf_s("%d", &j);

	switch (j)
	{
	case 1: 
		search_record(N_file);
		Main_Print(i);
	case 2 :
		search_record2(N_file);
		Main_Print(i);
	case 3: Main_Print(i);
	default:printf("번호 입력 오류 다시 입력하세요");
		}

	fclose(N_file);
}

void delete_number() {
	printf("\n======정보 삭제 선택======\n\n");

	fopen_s(&N_file, "N_file.bin", "rb+");
	if (N_file == NULL) {
		puts("파일 열기 오류");
		exit(1);
	}

	printf("1. 이름으로 찾기\n2.단축번호로 찾기\n3. 메인화면으로\n\n");
	scanf_s("%d", &j);

	switch (j)
	{
	case 1:
		SE_record(N_file);
		Main_Print(i);
	case 2:
		SE_record2(N_file);
		Main_Print(i);
	case 3: Main_Print(i);
	default:printf("번호 입력 오류 다시 입력하세요");
		break;
	}

	fclose(N_file);

}

void SE_record2(FILE *N_file) {

	NUMBERBOOK data2;
	char A[20] = "  ";
	char B[300] = "  ";

	int count = 0;

	fseek(N_file, 0, SEEK_SET);
	fflush(stdin);
	getchar();

	printf("삭제할 사람의 단축번호를 입력하세요\n\n");
	gets(search);

	fseek(N_file, 0, SEEK_SET);
	fflush(stdin);
	while (!feof(N_file)) {
		fread(&data2, sizeof(data2), 1, N_file);		//현재 위치에서 읽어서 구조체 data에 저장.
		count++;
		if (strcmp(data2.cut_number, search) == 0) {			//data.name에 search와 같은 내용이있으면 실행
			print_record(data2);

			strcpy(data2.name,A);
			strcpy(data2.number,A);
			strcpy(data2.cut_number,B);

			fseek(N_file,0L,SEEK_END);
			fseek(N_file,((count-1) * sizeof(data2)),SEEK_SET);
			fwrite(&data2, sizeof(data2), 1, N_file);

			break;
		}
	}
		fclose(N_file);
}

void SE_record(FILE *N_file) {

	NUMBERBOOK data2;
	char A[20] = "  ";
	char B[300] = "  ";

	int count = 0;

	fseek(N_file, 0, SEEK_SET);
	fflush(stdin);
	getchar();

	printf("삭제할 사람의 이름을 입력하세요\n\n");
	gets(search);

	fseek(N_file, 0, SEEK_SET);
	fflush(stdin);
	while (!feof(N_file)) {
		fread(&data2, sizeof(data2), 1, N_file);		//현재 위치에서 읽어서 구조체 data에 저장.
		count++;
		if (strcmp(data2.name, search) == 0) {			//data.name에 search와 같은 내용이있으면 실행
			print_record(data2);

			strcpy(data2.name,A);
			strcpy(data2.number,A);
			strcpy(data2.cut_number,B);

			fseek(N_file,0L,SEEK_END);
			fseek(N_file,((count-1) * sizeof(data2)),SEEK_SET);
			fwrite(&data2, sizeof(data2), 1, N_file);

			break;
		}
	}
		fclose(N_file);
}

void see_number() {
	NUMBERBOOK data3;

	int count = 0;

	fopen_s(&N_file, "N_file.bin", "r");
	if(N_file==NULL) {
	puts("파일 열기 오류");
	exit(1);
	}

	printf("\n=====전화번호부 보기 선택======\n\n");
	
	fseek(N_file, 0, SEEK_SET);

	while(fread(&data3, sizeof(data3), 1, N_file)){
		if (!strcmp(data3.name, "  ") == 0) {
			print_record(data3);
			count++;
		}
		if (SEEK_END == 1) break;
	}
	if (count == 0) printf("출력할 파일이 없습니다.\n\n");
	fclose(N_file);

	Main_Print(1);

}

void print_record(NUMBERBOOK data) {
	printf("이름 %s\t전화번호 %s\t단축번호 %s\n\n", data.name, data.number, data.cut_number);
}

void search_record(FILE *N_file) {

	NUMBERBOOK data2;

	int count=0;

	fseek(N_file, 0, SEEK_SET);
	fflush(stdin);
	getchar();

	printf("수정할 사람의 이름을 입력하세요\n\n");
	gets(search);

	fseek(N_file, 0, SEEK_SET);
	fflush(stdin);
	while (!feof(N_file)) {
		fread(&data2, sizeof(data2), 1, N_file);		//현재 위치에서 읽어서 구조체 data에 저장.
		count++;
		if (strcmp(data2.name, search) == 0) {		   //data.name에 search와 같은 내용이있으면 실행
		print_record(data2);

		printf("바꿀 이름을 입력하세요\n\n");
		gets(RE_name);

		strcpy(data2.name,RE_name);

		fflush(stdin);
		printf("바꿀 번호를 입력하세요 \n\n");
		gets(RE_name);

		strcpy(data2.number,RE_name);

		fflush(stdin);
		printf("바꿀 단축번호를 입력하세요 \n\n");
		gets(RE_name);

		strcpy(data2.cut_number,RE_name);

			
		fseek(N_file,0L,SEEK_END);
		fseek(N_file,((count-1) * sizeof(data2)),SEEK_SET);
		fwrite(&data2, sizeof(data2), 1, N_file);
		
		break;		//반복문 이탈
		}
	}
	fclose(N_file);
}

void search_record2(FILE *N_file){

	NUMBERBOOK data2;

	int count = 0;

	fflush(stdin);
	getchar();

	printf("수정할 사람의 단축번호을 입력하세요\n\n");
	gets(search);

	fseek(N_file, 0, SEEK_SET);
	fflush(stdin);
	while (!feof(N_file)) {
		fread(&data2, sizeof(data2), 1, N_file);			//읽어서 구조체 data에 저장.
		count++;
		if (strcmp(data2.cut_number, search) == 0) {		//data.cut_number에 search와 같은 내용이있으면 실행
		print_record(data2);

		printf("바꿀 이름을 입력하세요\n\n");
		gets(RE_name);

		strcpy(data2.name,RE_name);

		fflush(stdin);
		printf("바꿀 번호를 입력하세요 \n\n");
		gets(RE_name);

		strcpy(data2.number,RE_name);

		fflush(stdin);
		printf("바꿀 단축번호를 입력하세요 \n\n");
		gets(RE_name);

		strcpy(data2.cut_number,RE_name);

			
		fseek(N_file,0L,SEEK_END);
		fseek(N_file,((count-1) * sizeof(data2)),SEEK_SET);
		fwrite(&data2, sizeof(data2), 1, N_file);
		
		break;		//반복문 이탈
		}
	}
	fclose(N_file);
}