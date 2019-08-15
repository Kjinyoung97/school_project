#include <stdio.h>
#include <string.h>
#include <stdlib.h>				

int j,i = 0;					//�������� i,j����
FILE *N_file = NULL;			//������ ����Ű�� ������
char search[20];				//�˻��Ҷ� ����� ���ڿ��� ������ �迭 ����
char RE_name[20];				//�����Ҷ� �ӽ÷� ���ڿ��� �����س��� �迭 ����					
 
typedef struct numberbook {		//����ü ����
	char name[20];				//�̸��� ����
	char number[20];			//��ȭ��ȣ ����
	char cut_number[300];		//�����ȣ ����
}NUMBERBOOK;					//����ü�� ���ο� Ÿ�� NUMBERBOOK���� ����

void Main_Print(int i);				//ù ȭ��(�޴�����)�� ����� �Լ�
void modify_number();				//���� �˻��Ͽ� �������� â�� ���� �Լ�
void New_number(FILE *N_file);		//�űԹ�ȣ�� �����ϴ� �Լ�
void delete_number();				//����Ǿ��ִ� ��ȣ�� �����ϴ� �Լ�
void see_number();					//���ݱ��� ����Ǿ� �ִ� ��ȣ���� ����ϴ� �Լ�
void Name_Modify_Number(FILE *N_file);		//������ ������ �̸����� �˻��Ͽ� �����ϴ� �Լ�
void Cut_Modify_Number(FILE *N_file);		//������ ������ �����ȣ�� �˻��Ͽ� �����ϴ� �Լ�
void print_record(NUMBERBOOK);				//�̸�, ��ȭ��ȣ, �����ȣ�� ����ϴ� �Լ�
void Cut_Delet_Number(FILE *N_file);				//������ ������ �����ȣ�� �˻��Ͽ� �����ϴ� �Լ�
void Name_Delete_Number(FILE *N_file);				//������ ������ �̸����� �˻��Ͽ� �����ϴ� �Լ�

void main() {

	Main_Print(1);								//�����Լ����� �޴������� ����ϴ� �Լ��� ȣ���Ѵ�.

}

void Main_Print(int i) {
	printf("���ϴ� �޴��� �����ϼ���\n\n");		
	printf("1. �ű� ���� ����\t2. ��������\t3. ���� ����\t4. ��ȭ��ȣ�� ����\t5. ���α׷�����\n\n");
	scanf_s("%d", &i);							//����ڰ� ���ϴ� �޴��� ������
	switch (i)									//�Է¹��� i�� ���� ���� ����
	{
	case 1: 
		New_number(N_file);						//�ű����� ������ ����ϴ� �Լ� ȣ��
		break;									//swithc�� Ż��(����ؼ� 2,3,4�� ���ķ� �������� �ʰ�)
	case 2: 
		{
		modify_number();						//������ ����ϴ� �Լ� ȣ��
		break;}
	case 3: 
		{delete_number();						//������ ����ϴ� �Լ� ȣ��
		break;}
	case 4: 
		{
		see_number();							//��ü ����� ����ϴ� �Լ� ȣ��
		break;
		}
	case 5: exit(1);							//���α׷� ����
	default:									//���� 1~5�� �ƴ� �ٸ� ���� �Էµ� ��� �ٽ� �Է��Ұ��� �䱸
		printf("========�ùٸ� ��ȣ�� �ٽ� �����ϼ���========\n");		//���� �޼��� ���
		Main_Print(1);							//�ٽ� ù ����ȭ���� ����ϴ� �Լ� ȣ��
	}
}

void New_number(FILE *N_file) {					//�ű� ������ �����ϴ� �Լ�

	/* ���� �̸��� ����ó��(������ ���)�Ǿ� ���� ��� �װ��� �����͸� ���� ����� ������� �Ϸ������� 
	���������� w(�����) ������� ���� �� ��� ����ó���� �κ� �Ӹ� �ƴ϶� �� ������ ����Ǿ��ִ� �����ͱ��� ����
	����ó���Ǿ� a+�� ���� ������ �Ʒ��� �߰��ϴ� ������� ����Ǿ����ϴ�. ������ �˻��Ͽ� �� �κп� �����͸�
	�ִ°ͱ��� ���������� �� �޵κκб��� ���� ���� �ϳ��� ��޵Ǿ� ��������⿡ �� ����� �����߽��ϴ�.*/

	NUMBERBOOK data;			//�Է¹޾Ƽ� ������ ����ü data���� 
	NUMBERBOOK data2;

	fopen_s(&N_file, "N_file.bin", "a+");				//�������� ����. ���� ������ ������� �ű� ����
	if (N_file == NULL) {								//���� ���� Ȥ�� ���⿡ ������ ��� 
		puts("�Է��� ���� ������ �� �� �����ϴ�.\n");		//�����޼��� ���
		exit(1);											//���α׷� ����
	}
	else {												//���� ���� or ���⿡ ������ ���
		puts("��ȭ��ȣ�� ������ �ʿ��� ������ ���� or ���� �߽��ϴ�.\n");		//���� �޼��� ���
	}

	fflush(stdin);										//stdin(ǥ�� ����� ��ġ)���۸� ���
	getchar();											
	//�Ⱦ��� �̸��� �Է��� ���� ���� �ٷ� �̸��Է��ϼ��� ��ȣ�Է��ϼ��� ���ÿ� �߱淡 �ѹ��� ����� �־����ϴ�

	printf("\n======�ű� �Է� ����======\n\n");			//����ڿ��� ������ �����Ѱ��� �������� ������

	printf("�̸��� �Է��ϼ���.\n");						//����ڰ� �̸��� �Է��ϰ� ����
	gets(data.name);									//�Է¹������� data.name�� ����

	printf("�޴��� ��ȣ�� �Է��ϼ���\n");				//�޴��� ��ȣ�� �Է��ϰ� ����
	gets(data.number);									//��ȣ�� �Է¹޾� data.number�� ����

	printf("������ �����ȣ�� �Է��ϼ���.");			//�����ȣ�� �Է��ϰ� ����
	gets(data.cut_number);								//�Է¹��� �����ȣ�� data.cut_number�� ����


	fseek(N_file, 0, SEEK_END);							//���������� �����͸� ������ �� ���� ��ġ��Ű��
	fwrite(&data, sizeof(data), 1, N_file);				//�װ��� �Ʊ� �Է¹��� �ڷḦ ������ ����ü data�� �����

	fclose(N_file);										//���� �ݱ�

	Main_Print(1);										//�ٽ� ùȭ������ ���ư���.
}


void modify_number() {									//������ ����ϴ� �Լ�
	printf("\n======���� ���� ����======\n\n");			//����ڰ� ������ �����Ͽ����� ����ڿ��� ������

	fopen_s(&N_file, "N_file.bin", "rb+");				//������ rb+ (�а� ���� �߰����)�� ����
	if(N_file==NULL) {									//������ ���µ� ������ ���
		puts("���� ���� ����");							//���� �޼��� ��� ��
		exit(1);										//���α׷� ����
	}

	printf("1. �̸����� ã��\n2.�����ȣ�� ã��\n3. ����ȭ������\n\n");		//����ڰ� �������� �˻��Ͽ� �������� ���ñ��� �ο�
	scanf_s("%d", &j);														//����ڰ� ������ ���� �����Ͽ� 

	switch (j)											//switch������ ������ ���� ���� ���� �Լ��� ȣ���Ѵ�
	{
	case 1:												//1�� ������ ���
		Name_Modify_Number(N_file);						//�̸����� ã�� �����ϴ� �Լ��� ȣ���Ѵ�
		Main_Print(1);									//�̸����� �����ϴ� �Լ��� ������� ù ȭ������ �ٽ� ���ư���.
	case 2 :											//2�� ������ ���
		Cut_Modify_Number(N_file);						//�����ȣ�� ã�� �����ϴ� �Լ��� ȣ���Ѵ�.
		Main_Print(1);									//�����ȣ�� �����ϴ� �Լ��� ���� ��� �ٽ� ô ȭ������ ���󰣴�.
	case 3: Main_Print(1);								//3�� ������ ��� �ٽ� ����ȭ������ ���ư���(�߸� ������ ���)
	default:											//1~3 �̿��� ���� �Է� �Ѱ��
		printf("��ȣ �Է� ���� �ٽ� �Է��ϼ���\n\n");		//���� �޼����� ����Ѵ�.
		fclose(N_file);										//�����ִ� ������ �ݰ�
		modify_number();									//�ڱ� �ڽ��� �ٽ� ȣ���Ͽ� ���Է��ϰ� �Ѵ�.
		}
}

void delete_number() {										//������ ����ϴ� �Լ��� ȣ���Ѵ�.
	printf("\n======���� ���� ����======\n\n");				//����ڿ��� ����ڰ� ������ �����ߴ��� �����ش�.

	fopen_s(&N_file, "N_file.bin", "rb+");					//������ rb+(�а� ���� �߰����)�� ����.
	if (N_file == NULL) {									//������ ����� ������ ���� ���
		puts("���� ���� ����");								//�����޼����� ����ϰ� 
		exit(1);											//���α׷��� �����Ѵ�.
	}

	printf("1. �̸����� ã��\n2.�����ȣ�� ã��\n3. ����ȭ������\n\n");		//����ڿ��� �������� ã�Ƽ� �������� ���ñ� �ο�
	scanf_s("%d", &j);														//����ڰ� �����Ѱ� ���� j�� ����
	
	switch (j)											//�Է¹��� j ������ switch�� �۵�
	{	
	case 1:												//j���� 1�� ���
		Name_Delete_Number(N_file);						//�̸����� �˻��Ͽ� �����ϴ� �Լ� ȣ��
		Main_Print(1);									//�̸����� �����ϴ� �Լ��� ������ ùȭ������ ��������
	case 2:												//j���� 2�� ���
		Cut_Delet_Number(N_file);						//�����ȣ�� �˻��Ͽ� �����ϴ� �Լ� ȣ��
		Main_Print(1);									//�����ȣ�� �����ϴ� �Լ��� ������ ùȭ������ ��������
	case 3: Main_Print(1);								//j���� 3�� ��� ùȭ������ ��������
	default:												//1~3���� �ٸ� ���� �Էµȴٸ�
		printf("��ȣ �Է� ���� �ٽ� �Է��ϼ���");			//�����޼����� ����� ��
		fclose(N_file);										//�����ִ� ������ �ݰ�
		delete_number();									//�ڱ� �ڽ��� �Լ��� �ٽ� ȣ���Ͽ� �ٽ� �����ϰ� �Ѵ�.
	}
}

void Cut_Delet_Number(FILE *N_file) {				//�����ȣ�� �˻��Ͽ� �����ϴ� �Լ�
		
	NUMBERBOOK data2;								//������ �о�ͼ� �� �� ������ 

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

void Name_Delete_Number(FILE *N_file) {

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

void Name_Modify_Number(FILE *N_file) {

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

void Cut_Modify_Number(FILE *N_file){

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