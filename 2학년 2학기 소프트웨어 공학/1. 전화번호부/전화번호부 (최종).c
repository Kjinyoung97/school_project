#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

int j,i = 0;
FILE *N_file = NULL;			//������ ����Ű�� ������
char search[20];
char RE_name[20];
int R_count;
 
typedef struct numberbook {		//����ü ����
	char name[20];
	char number[20];
	char cut_number[300];
}NUMBERBOOK;					//����ü�� ���ο� Ÿ�� NUMBERBOOK���� ����

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
	printf("���ϴ� �޴��� �����ϼ���\n\n");
	printf("1. �ű� ���� ����\t2. ��������\t3. ���� ����\t4. ��ȭ��ȣ�� ����\t5. ���α׷�����\n\n");
	scanf_s("%d", &i);
	switch (i)		//�Է¹��� i�� ���� ���� ����
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
		printf("========�ùٸ� ��ȣ�� �ٽ� �����ϼ���========\n");
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
		puts("�Է��� ���� ������ �� �� �����ϴ�.\n");
		exit(1);
	}
	else {
		puts("��ȭ��ȣ�� ������ �ʿ��� ������ ���� or ���� �߽��ϴ�.\n");
	}

	fflush(stdin);
	getchar();

	printf("\n======�ű� �Է� ����======\n\n");

	printf("�̸��� �Է��ϼ���.\n");
	gets(data.name);

	printf("�޴��� ��ȣ�� �Է��ϼ���\n");
	gets(data.number);

	printf("������ �����ȣ�� �Է��ϼ���.");
	gets(data.cut_number);


	fseek(N_file, 0, SEEK_END);
	fwrite(&data, sizeof(data), 1, N_file);

	fclose(N_file);

	Main_Print(i);
}


void modify_number() {
	printf("\n======���� ���� ����======\n\n");

	fopen_s(&N_file, "N_file.bin", "rb+");
	if(N_file==NULL) {
		puts("���� ���� ����");
		exit(1);
	}

	printf("1. �̸����� ã��\n2.�����ȣ�� ã��\n3. ����ȭ������\n\n");
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
	default:printf("��ȣ �Է� ���� �ٽ� �Է��ϼ���");
		}

	fclose(N_file);
}

void delete_number() {
	printf("\n======���� ���� ����======\n\n");

	fopen_s(&N_file, "N_file.bin", "rb+");
	if (N_file == NULL) {
		puts("���� ���� ����");
		exit(1);
	}

	printf("1. �̸����� ã��\n2.�����ȣ�� ã��\n3. ����ȭ������\n\n");
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
	default:printf("��ȣ �Է� ���� �ٽ� �Է��ϼ���");
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

	printf("������ ����� �����ȣ�� �Է��ϼ���\n\n");
	gets(search);

	fseek(N_file, 0, SEEK_SET);
	fflush(stdin);
	while (!feof(N_file)) {
		fread(&data2, sizeof(data2), 1, N_file);		//���� ��ġ���� �о ����ü data�� ����.
		count++;
		if (strcmp(data2.cut_number, search) == 0) {			//data.name�� search�� ���� ������������ ����
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

	printf("������ ����� �̸��� �Է��ϼ���\n\n");
	gets(search);

	fseek(N_file, 0, SEEK_SET);
	fflush(stdin);
	while (!feof(N_file)) {
		fread(&data2, sizeof(data2), 1, N_file);		//���� ��ġ���� �о ����ü data�� ����.
		count++;
		if (strcmp(data2.name, search) == 0) {			//data.name�� search�� ���� ������������ ����
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
	puts("���� ���� ����");
	exit(1);
	}

	printf("\n=====��ȭ��ȣ�� ���� ����======\n\n");
	
	fseek(N_file, 0, SEEK_SET);

	while(fread(&data3, sizeof(data3), 1, N_file)){
		if (!strcmp(data3.name, "  ") == 0) {
			print_record(data3);
			count++;
		}
		if (SEEK_END == 1) break;
	}
	if (count == 0) printf("����� ������ �����ϴ�.\n\n");
	fclose(N_file);

	Main_Print(1);

}

void print_record(NUMBERBOOK data) {
	printf("�̸� %s\t��ȭ��ȣ %s\t�����ȣ %s\n\n", data.name, data.number, data.cut_number);
}

void search_record(FILE *N_file) {

	NUMBERBOOK data2;

	int count=0;

	fseek(N_file, 0, SEEK_SET);
	fflush(stdin);
	getchar();

	printf("������ ����� �̸��� �Է��ϼ���\n\n");
	gets(search);

	fseek(N_file, 0, SEEK_SET);
	fflush(stdin);
	while (!feof(N_file)) {
		fread(&data2, sizeof(data2), 1, N_file);		//���� ��ġ���� �о ����ü data�� ����.
		count++;
		if (strcmp(data2.name, search) == 0) {		   //data.name�� search�� ���� ������������ ����
		print_record(data2);

		printf("�ٲ� �̸��� �Է��ϼ���\n\n");
		gets(RE_name);

		strcpy(data2.name,RE_name);

		fflush(stdin);
		printf("�ٲ� ��ȣ�� �Է��ϼ��� \n\n");
		gets(RE_name);

		strcpy(data2.number,RE_name);

		fflush(stdin);
		printf("�ٲ� �����ȣ�� �Է��ϼ��� \n\n");
		gets(RE_name);

		strcpy(data2.cut_number,RE_name);

			
		fseek(N_file,0L,SEEK_END);
		fseek(N_file,((count-1) * sizeof(data2)),SEEK_SET);
		fwrite(&data2, sizeof(data2), 1, N_file);
		
		break;		//�ݺ��� ��Ż
		}
	}
	fclose(N_file);
}

void search_record2(FILE *N_file){

	NUMBERBOOK data2;

	int count = 0;

	fflush(stdin);
	getchar();

	printf("������ ����� �����ȣ�� �Է��ϼ���\n\n");
	gets(search);

	fseek(N_file, 0, SEEK_SET);
	fflush(stdin);
	while (!feof(N_file)) {
		fread(&data2, sizeof(data2), 1, N_file);			//�о ����ü data�� ����.
		count++;
		if (strcmp(data2.cut_number, search) == 0) {		//data.cut_number�� search�� ���� ������������ ����
		print_record(data2);

		printf("�ٲ� �̸��� �Է��ϼ���\n\n");
		gets(RE_name);

		strcpy(data2.name,RE_name);

		fflush(stdin);
		printf("�ٲ� ��ȣ�� �Է��ϼ��� \n\n");
		gets(RE_name);

		strcpy(data2.number,RE_name);

		fflush(stdin);
		printf("�ٲ� �����ȣ�� �Է��ϼ��� \n\n");
		gets(RE_name);

		strcpy(data2.cut_number,RE_name);

			
		fseek(N_file,0L,SEEK_END);
		fseek(N_file,((count-1) * sizeof(data2)),SEEK_SET);
		fwrite(&data2, sizeof(data2), 1, N_file);
		
		break;		//�ݺ��� ��Ż
		}
	}
	fclose(N_file);
}