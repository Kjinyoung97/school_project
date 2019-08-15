#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int i,Count,COUNT;
char A[10] = "  ";				//������ ����� ���� �迭 ����
char B[10] = "����";			
char C[10] = "������";			//������ ���� ��Ȳ�� ������ �迭 ����


void User_Add(FILE *User_file, FILE *Video_file);		//����� �߰� �Լ�
void Video_Add(FILE *User_file, FILE *Video_file);		//���� �߰� �Լ�
void Search_User(FILE *User_file);						//����� �˻� �Լ�
void Search_Video(FILE *Video_file);					//���� �˻� �Լ�
void Print_User(FILE *User_file);						//����� ��ü ��� �Լ�
void Print_Video(FILE *Video_file);						//���� ��ü ��� �Լ�
void Have_Video(FILE *Video_file);						//�������� ������ ����ϴ� �Լ�
void Rent_Video(FILE *User_file, FILE *Video_file);		//�뿩�� ����ϴ� �Լ�
void Return_Video(FILE *User_file, FILE *Video_file);	//�ݳ��� ����ϴ� �Լ�
void Write(FILE *User_file, FILE *Video_file, int Count, int COUNT);		//���Ͽ� �����͸� ���� ������  �ϴ� �Լ�
void Not_Have_Video(FILE *Video_file);										//�뿩���̶� �����ϰ����� ���� ������ ����ϴ� �Լ� (��ü �׽�Ʈ��)
void Write2(FILE *User_file, FILE *Video_file,int Count, int COUNT);		//���Ͽ� �����͸� ���� ������  �ϴ� �Լ�2
void User_Delete(FILE *User_file);											//����� ���� ���� �Լ�
void Video_Delete(FILE *Video_file);										//���� ���� ���� �Լ�

typedef struct User {			//����� ������ ����ϴ� ����ü ����
	char name[20];				//�̸��� ����
	char number[20];			//��ȭ��ȣ ����
	char video1[20];			//�뿩�� ���� ��Ȳ 1~3
	char video2[20];
	char video3[20];
}USER;

typedef struct Video {			//���� ������ ����ϴ� ����ü ����
	char name[20];				//�̸��� ����
	char number[20];			//��Ϲ�ȣ ����
	char have[10];				//���� ������Ȳ�� �˻��� �迭
}VIDEO;

USER data8;
VIDEO data9;


void main(FILE *User_file, FILE *Video_file) {

	fopen_s(&Video_file, "Video_file.bin", "ab+");				//������������� ����. ���� ������ ������� �ű� ����
	if (Video_file == NULL) {									//���� ���� Ȥ�� ���⿡ ������ ��� 
		puts("�Է��� ���� ������ �� �� �����ϴ�.\n");			//�����޼��� ���
		exit(1);												//���α׷� ����
	}


	fopen_s(&User_file, "User_file.bin", "ab+");				//���� �������� ����. ���� ������ ������� �ű� ����
	if (User_file == NULL) {									//���� ���� Ȥ�� ���⿡ ������ ��� 
		puts("�Է��� ���� ������ �� �� �����ϴ�.\n");			//�����޼��� ���
		exit(1);												//���α׷� ����
	}

	fclose(User_file);
	fclose(Video_file);

	Main_Print(User_file,Video_file);							//�����Լ����� �޴������� ����ϴ� �Լ��� ȣ���Ѵ�.
}

int Main_Print(FILE *User_file, FILE *Video_file) {				//������ �޴��� ������ �� �ִ� ����â�� ����ϴ� �Լ�


	fopen_s(&Video_file, "Video_file.bin", "rb+");				//���� ���� �������� ����. ���� ������ ������� �ű� ����
	if (Video_file == NULL) {									//���� ���� Ȥ�� ���⿡ ������ ��� 
		puts("�Է��� ���� ������ �� �� �����ϴ�.\n");			//�����޼��� ���
		exit(1);												//���α׷� ����
	}


	fopen_s(&User_file, "User_file.bin", "rb+");				//���� ���� �������� ����. ���� ������ ������� �ű� ����
	if (User_file == NULL) {									//���� ���� Ȥ�� ���⿡ ������ ��� 
		puts("�Է��� ���� ������ �� �� �����ϴ�.\n");			//�����޼��� ���
		exit(1);												//���α׷� ����
	}

	printf("\t\t==============����� ����� �����ϼ���============== \n\n");
	printf("\t1.������߰�\t2.�����߰�\t3.����� �˻�\t4.�����˻�\n\t5.�뿩���� ���� ���\t\t6.�뿩\t\t7.�ݳ�\n\t8.����� ��������\t9.���� ��������\t10.���α׷� ����\n\n\t11.����� ���� ��ü���\t\t12.���� ���� ��ü���\n ");
	printf("\t\t==================================================== \n\n");

	scanf_s("%d", &i);											//����ڰ� ������ i�� �����Ѵ�.

	switch (i)													//����ڰ� ��� ������ i���� ����Ͽ� switch��.
	{

	case 1 :
	
			
		User_Add(User_file,Video_file);
		fclose(User_file);
		fclose(Video_file);
		Main_Print(User_file, Video_file);

	case 2 :

		Video_Add(User_file, Video_file);
		fclose(User_file);
		fclose(Video_file);
		Main_Print(User_file, Video_file);

	case 3 :
	
		Search_User(User_file);
		fclose(User_file);
		fclose(Video_file);
		Main_Print(User_file, Video_file);

	case 4 :

		Search_Video(Video_file);
		fclose(User_file);
		fclose(Video_file);
		Main_Print(User_file, Video_file);

	case 5 :

		Have_Video(Video_file);
		fclose(User_file);
		fclose(Video_file);
		Main_Print(User_file, Video_file);


	case 6 :

		Rent_Video(User_file,Video_file);
		fclose(User_file);
		fclose(Video_file);
		Main_Print(User_file, Video_file);


	case 7 :
		
		Return_Video(User_file, Video_file);
		fclose(User_file);
		fclose(Video_file);
		Main_Print(User_file, Video_file);

	case 8 :

		User_Delete(User_file);
		fclose(User_file);
		fclose(Video_file);
		Main_Print(User_file, Video_file);

	case 9 :

		Video_Delete(Video_file);
		fclose(User_file);
		fclose(Video_file);
		Main_Print(User_file, Video_file);

	case 10 :

		
		exit(1);
		break;

	case 11:
		Print_User(User_file);
		fclose(User_file);
		fclose(Video_file);
		Main_Print(User_file, Video_file);

	case 12:
		Print_Video(Video_file);
		fclose(User_file);
		fclose(Video_file);
		Main_Print(User_file, Video_file);

	case 13 :

		Not_Have_Video(Video_file);
		fclose(User_file);
		fclose(Video_file);
		Main_Print(User_file, Video_file);


	default:												//������ �� �̿ܿ� ���� �Է¹����� �����޼��� ���.
		printf("�߸��� ���Դϴ�. �ٽ� �Է��ϼ���");
		break;
	}
}

void User_Add(FILE *User_file, FILE *Video_file) {			//����� �߰� �Լ�

	USER data;												
	int count = 0;											//���� ������ ��ġ�� ���� �� ���� count ���� �� �ʱ�ȭ
	

	fseek(User_file, 0, SEEK_SET);							//���� �������� ��ġ�� ���� ������������ �ű��
	fflush(stdin);											//ǥ�� �������ġ�� ���۸� ��� ��

	getchar();

	while (!feof(User_file)) {								//������ ���� ���� �� �� ���� �ݺ��Ͽ� 
		fread(&data, sizeof(data), 1, User_file);			//���� �������� ��ġ���� �о ����ü data�� ����.									
		count++;											//�ѹ� �о�ö����� count�� �� 1�� ����
			if (strcmp(data.name, "  ") == 0) {
			//���� �о� �� ��(data.name)�� ���� ��ĭ�� �����ϴٸ� (����ó���� �Ǿ��ٸ�) (��ĭ�� �ƴ� ��ĭ�� ������ �������� ���ϴ°��� ����)

			printf("\n======�ű� �Է� ����(����)======\n\n");			//����ڿ��� ������ �����Ѱ��� �������� ������ �������ִٴ°� ����ó���� �ڸ���.

			printf("�̸��� �Է��ϼ���.\n");						//����ڰ� �̸��� �Է��ϰ� ����
			gets(data.name);									//�Է¹������� data.name�� ����

			printf("�޴��� ��ȣ�� �Է��ϼ���\n");				//�޴��� ��ȣ�� �Է��ϰ� ����
			gets(data.number);									//��ȣ�� �Է¹޾� data.number�� ����

			strcpy(data.video1, A);								//���� �뿩 ��Ȳ 1~3�� ���� �迭 A, �� �������� ����.
			strcpy(data.video2, A);
			strcpy(data.video3, A);

			fseek(User_file, 0L, SEEK_END);								//���������� �����͸� ������ �� ���� ��ġ��Ű��
			fseek(User_file, ((count - 1) * sizeof(data)), SEEK_SET);	//������������ (ī������ �� -1) * ����ü�� ũ�� ��ŭ �����͸� �̵���Ų��.
			fwrite(&data, sizeof(data), 1, User_file);					//�װ��� �Ʊ� �Է¹��� �ڷḦ ������ ����ü data�� �����. �� ������ ���� ������ ���� �Է¹��� �����͸� ���� ����
			
			printf("�̸� : %s ��ȭ��ȣ : %s �뿩��Ȳ %s %s %s \n\n", data.name, data.number, data.video1, data.video2, data.video3);

			break;

		
		}

		else {													//������ �� ĭ ������ ���� ã�� ���Ѵٸ� (�����Ǿ� ����ó�� �� �����Ͱ� ���ٸ�)
			
			printf("�̸��� �Է��ϼ���.\n");						//����ڰ� �̸��� �Է��ϰ� ����
			gets(data.name);									//�Է¹������� data.name�� ����

			printf("�޴��� ��ȣ�� �Է��ϼ���\n");				//�޴��� ��ȣ�� �Է��ϰ� ����
			gets(data.number);									//��ȣ�� �Է¹޾� data.number�� ����

			strcpy(data.video1, A);								//���� �뿩 ��Ȳ 1~3�� ���� �迭 A, �� �������� ����.
			strcpy(data.video2, A);
			strcpy(data.video3, A);
			

			fseek(User_file, 0L, SEEK_END);							//���������� �����͸� ������ �� ���� ��ġ��Ű��
			fwrite(&data, sizeof(data), 1, User_file);				//�װ��� �Ʊ� �Է¹��� �ڷḦ ������ ����ü data�� �����. �� ������ ���� ������ ���� �Է¹��� �����͸� ���� ����

			printf("�̸� : %s ��ȭ��ȣ : %s �뿩��Ȳ %s %s %s \n\n", data.name, data.number, data.video1, data.video2, data.video3);
			
		}
		break;
	}
		strcpy(data8.name,data.name);								//���������� ����Ǿ��ִ� ����� �Լ� data8 �� data�� ������ ���� ������.
		strcpy(data8.number,data.number);
		strcpy(data8.video1,data.video1);
		strcpy(data8.video2,data.video2);
		strcpy(data8.video3,data.video3);

}

void Video_Add(FILE *User_file, FILE *Video_file) {					//������ �߰��ϴ� �Լ� 

	VIDEO data2,data3;
	int count = 0;

	fseek(Video_file, 0, SEEK_SET);							//���� �������� ��ġ�� ���� ������������ �ű��
	fflush(stdin);											//ǥ�� �������ġ�� ���۸� ��� ��

	getchar();

	while (!feof(Video_file)) {								//������ ���� ���� �� �� ���� �ݺ��Ͽ� 
		fread(&data3, sizeof(data3), 1, Video_file);		//���� �������� ��ġ���� �о ����ü data�� ����.
		count++;											//�ѹ� �о�ö����� count�� �� 1�� ����
		if (strcmp(data3.name, "  ") == 0) {
			//���� �о� �� ��(data3.name)�� ���� ��ĭ�� �����ϴٸ� (����ó���� �Ǿ��ٸ�) (��ĭ�� �ƴ� ��ĭ�� ������ �������� ���ϴ°��� ����)

			printf("\n======�ű� �Է� ����(����)======\n\n");			//����ڿ��� ������ �����Ѱ��� �������� ������

			printf("�̸��� �Է��ϼ���.\n");						//����ڰ� �̸��� �Է��ϰ� ����
			gets(data2.name);									//�Է¹������� data2.name�� ����

			printf("��� ��ȣ�� �Է��ϼ���\n");					//��Ϲ�ȣ�� �Է��ϰ� ����
			gets(data2.number);									//��ȣ�� �Է¹޾� data2.number�� ����

			strcpy(data2.have, B);								//���� ���� ��Ȳ�� ����ϴ� data2.have�� �迭 B (=����)�� �پ����

			fseek(Video_file, 0L, SEEK_END);							//���������� �����͸� ������ �� ���� ��ġ��Ű��
			fseek(Video_file, ((count - 1) * sizeof(data2)), SEEK_SET);	//(ī������ �� -1) * ����ü�� ũ�� ��ŭ �����͸� ������ �̵���Ų��.
			fwrite(&data2, sizeof(data2), 1, Video_file);				//�װ��� �Ʊ� �Է¹��� �ڷḦ ������ ����ü data�� �����. �� ������ ���� ������ ���� �Է¹��� �����͸� ���� ����

			printf("�̸� : %s ��Ϲ�ȣ : %s ������Ȳ %s \n\n", data2.name, data2.number, data2.have);

		}

		else {													//������ �� ĭ ������ ���� ã�� ���Ѵٸ� (�����Ǿ� ����ó�� �� �����Ͱ� ���ٸ�)

			printf("�̸��� �Է��ϼ���.\n");						//����ڰ� �̸��� �Է��ϰ� ����
			gets(data2.name);									//�Է¹������� data2.name�� ����

			printf("��� ��ȣ�� �Է��ϼ���\n");					//��� ��ȣ�� �Է��ϰ� ����
			gets(data2.number);									//��ȣ�� �Է¹޾� data2.number�� ����

			strcpy(data2.have, B);								//���� ���� ��Ȳ�� ����ϴ� data2.have�� �迭 B (=����)�� �پ����

			fseek(Video_file, 0, SEEK_END);								//���������� �����͸� ������ �� ���� ��ġ��Ű��
			fwrite(&data2, sizeof(data2), 1, Video_file);				//�װ��� �Ʊ� �Է¹��� �ڷḦ ������ ����ü data2�� �����

			printf("�̸� : %s ��Ϲ�ȣ : %s ������Ȳ %s \n\n", data2.name, data2.number, data2.have);

			break;
		}
		break;
	}
}

void Search_User(FILE *User_file) {							//����� �˻��� ����ϴ� �Լ�

	
	USER data2;
	char search[20];

	int count = 0;											//���Ƚ���� �����ϴ� ���� count�� �����ϰ� 0���� �ʱ�ȭ
	COUNT = 0;												//���� �������� ��ġ�� ������ ���� COUNT�� �����ϰ� 0���� �ʱ�ȭ

	fseek(User_file, 0, SEEK_SET);							//�������� ��ġ�� ������ ó������
	fflush(stdin);											//ǥ������� ��ġ�� ���۸� ���
	getchar();												//������ ���½ð�(�ٷ� �ȳѾ��)���� ���

	printf("�˻��� ����� �̸��� �Է��ϼ���\n\n");			//����ڰ� ������ ����� �̸��� �Է��ϰ� ����
	gets(search);											//�� �Է��� �̸��� search�� ����

	while (!feof(User_file)) {								//������ ���� �ƴϸ� �ݺ�
		fread(&data2, sizeof(data2), 1, User_file);			//���� �������� ��ġ���� �ڷḦ �о ����ü data2�� ����.
		COUNT++;											//�ѹ� �о�ö����� COUNT�� �� 1�� ����
		if (strcmp(data2.name, search) == 0) {			    //data2.name�� search�� ���� ������������ ����
			count++;
			printf("�̸� : %s ��ȭ��ȣ : %s �뿩��Ȳ %s %s %s \n\n", data2.name, data2.number, data2.video1, data2.video2, data2.video3);
			
			strcpy(data8.name,data2.name);
			strcpy(data8.number,data2.number);				//���������� ����Ǿ��ִ� ����� �Լ� data8 �� data2�� ������ ���� ������.
			strcpy(data8.video1,data2.video1);
			strcpy(data8.video2,data2.video2);
			strcpy(data8.video3,data2.video3);

			break;
		}
	}
	if (count == 0) printf("�˻���� ����\n\n");			//count (=����� Ƚ��)�� 0�̸� �˻�������� ���.

}

void Search_Video(FILE *Video_file) {						//���� �˻��� �̿��ϴ� ����

	Count = 0;												//���� �������� ��ġ�� ������ ���� Count�� �����ϰ� 0���� �ʱ�ȭ

	VIDEO data2;
	char search[20];
	int k;
	int count = 0;

	fseek(Video_file, 0, SEEK_SET);							//�������� ��ġ�� ������ ó������
	fflush(stdin);											//ǥ������� ��ġ�� ���۸� ���
	getchar();												//������ ���½ð�(�ٷ� �ȳѾ��)���� ���

	printf("1. �̸����ΰ˻� \t 2. ��Ϲ�ȣ�� �˻�\n\n");
	scanf_s("%d", &k);

	switch (k) {


	case 1:
	{

		printf("�˻��� ������ �̸��� �Է��ϼ���\n\n");			//����ڰ� �˻��� ����� �̸��� �Է��ϰ� ����
		getchar();
		gets(search);												//�� �Է��� �̸��� search�� ����

		while (!feof(Video_file)) {									//������ ���� �ƴϸ� �ݺ�
			fread(&data2, sizeof(data2), 1, Video_file);			//���� �������� ��ġ���� �ڷḦ �о ����ü data2�� ����.											
			Count++;												//�ѹ� �о�ö����� Count�� �� 1�� ����
			if (strcmp(data2.name, search) == 0) {				    //data2.name�� search�� ���� ������������ ����
				count++;
				printf("\n�̸� : %s ��Ϲ�ȣ : %s ������Ȳ %s \n\n", data2.name, data2.number, data2.have);
				break;
			}
		}
		if (count == 0) printf("�˻���� ����\n\n");				//������ �ݺ������� count�� 0�̸� (=�ѹ��� ã�� ���Ͽ�����) ������� ���
		break;
	}

	case 2:
	{

		fflush(stdin);
		getchar();

		printf("�˻��� ������ ��Ϲ�ȣ�� �Է��ϼ���\n\n");			//����ڰ� ������ ����� ��Ϲ�ȣ�� �Է��ϰ� ����
		gets(search);													//�� �Է��� ��Ϲ�ȣ�� search�� ����

		while (!feof(Video_file)) {										//������ ���� �ƴϸ� �ݺ�
			fread(&data2, sizeof(data2), 1, Video_file);				//���� �������� ��ġ���� �ڷḦ �о ����ü data2�� ����.	
			Count++;													//�ѹ� �о�ö����� Count�� �� 1�� ����
			if (strcmp(data2.number, search) == 0) {				    //data2.name�� search�� ���� ������������ ����
				count++;	
				printf("�̸� : %s ��Ϲ�ȣ : %s ������Ȳ %s \n\n", data2.name, data2.number, data2.have);
				break;
			}
		}
		if (count == 0) printf("�˻���� ����\n\n");
		break;
	}

	default:
		break;
	}

	strcpy(data9.name,data2.name);
	strcpy(data9.number,data2.number);
	strcpy(data9.have,data2.have);
}

void Print_User(FILE *User_file) {						//����Ǿ��ִ� ����� �������� ����Ѵ�.

	printf("����� ���� ��ü���\n\n");

	USER data3;											//����ϴµ� ���Ͽ��� ����ü�� �о�ͼ� �� ����ü�� ������ data3 ����

	int count = 0;										//��� ����� �̷�� ������ �˻��� ���� count ���

	fseek(User_file, 0, SEEK_SET);									//�������� ��ġ�� �����ǽ����������� �ű�

	while (fread(&data3, sizeof(data3), 1, User_file)) {			//���ϳ����� �о���� ���� ��� �ݺ�
		if (!strcmp(data3.name, "  ") == 0) {				//data3.name�� "  " (�����ĭ)(=������ ������)�� ���Ͽ� ���� �ʴٸ� ���� 
			printf("�̸� : %s ��ȭ��ȣ : %s �뿩��Ȳ %s %s %s \n\n", data3.name, data3.number, data3.video1, data3.video2, data3.video3);							//�о�� ����ü data3�� ���
			count++;										//����ѹ��� count���� 1�� ����
		}
		if (SEEK_END == 1) break;							//���� �������� ��ġ�� ������ ���̸� �ݺ� ����
	}
	if (count == 0) printf("����� ������ �����ϴ�.\n\n");
	//���� count�� ���� 1�� ���������ʾҴٸ�, �� ���� �����̰ų� ����� �����Ͱ����ٸ� ����� ���� ���ٴ� �޼��� ���


}

void Print_Video(FILE *Video_file) {						//����� ������ ������ ����ϴ� 

	printf("���� ���� ��ü��� \n\n");

	VIDEO data3;											//����ϴµ� ���Ͽ��� ����ü�� �о�ͼ� �� ����ü�� ������ data3 ����

	int count = 0;											//��� ����� �̷�� ������ �˻��� ���� count ���

	fseek(Video_file, 0, SEEK_SET);									//�������� ��ġ�� �����ǽ����������� �ű�

	while (fread(&data3, sizeof(data3), 1, Video_file)) {			//���ϳ����� �о���� ���� ��� �ݺ�
		if (!strcmp(data3.name, "  ") == 0) {						//data3.name�� "  " (�����ĭ)(=������ ������)�� ���Ͽ� ���� �ʴٸ� ���� 
			printf("�̸� : %s ��Ϲ�ȣ : %s ������Ȳ %s \n\n", data3.name, data3.number, data3.have);						//�о�� ����ü data3�� ���
			count++;										//����ѹ��� count���� 1�� ����
		}
		if (SEEK_END == 1) break;							//���� �������� ��ġ�� ������ ���̸� �ݺ� ����
	}
	if (count == 0) printf("����� ������ �����ϴ�.\n\n");
	//���� count�� ���� 1�� ���������ʾҴٸ�, �� ���� �����̰ų� ����� �����Ͱ����ٸ� ����� ���� ���ٴ� �޼��� ���

}

void Not_Have_Video(FILE *Video_file) {
	
	VIDEO data2;
	int count = 0;

	fseek(Video_file, 0, SEEK_SET);	

	while (fread(&data2, sizeof(data2), 1, Video_file)) {			//���� �������� ��ġ���� �ڷḦ �о ����ü data2�� ����.		
			if ((strcmp(data2.have,C) == 0)&& (!strcmp(data2.name, "  ") == 0)){			//����(���� ó��)�� �ƴϰ� ���ÿ� ������Ȳ�� �̺����� ��쿡 ����
				printf("�̸� : %s ��Ϲ�ȣ : %s ������Ȳ %s \n\n", data2.name, data2.number, data2.have);
				count++;											//�ѹ� ����Ҷ����� count�� �� 1�� ����
			}
	}
	if(count==0) printf("�뿩���� ������ �����ϴ�.\n\n");			//�ѹ��� ��� �� ���̾����� �뿩���� ������ ���ٰ� ���
}

void Have_Video(FILE *Video_file) {									//�������� ���� ���

	VIDEO data2;
	int count = 0;

	fseek(Video_file, 0, SEEK_SET);

	while (fread(&data2, sizeof(data2), 1, Video_file)) {									//���� �������� ��ġ���� �ڷḦ �о ����ü data2�� ����.
		if ((strcmp(data2.have, C) != 0) && (!strcmp(data2.name, "  ") == 0)){				//����(���� ó��)�� �ƴϰ� ���ÿ� ������Ȳ�� �̺����� �ƴ� ��쿡 ����
			printf("�̸� : %s ��Ϲ�ȣ : %s ������Ȳ %s \n\n", data2.name, data2.number, data2.have);			
			count++;																		//�ѹ� ����Ҷ����� count�� �� 1�� ����
		}
	}
	if (count == 0) printf("�뿩������ ������ �����ϴ�.\n\n");							//�ѹ��� ������� ���� ��� �뿩������ ������ ���ٴ� �޼��� ���
}
	
void Rent_Video(FILE *User_file, FILE *Video_file){											//�뿩�� ����ϴ� �Լ�
				
	COUNT = 0;
	Count = 0;

	int z;

	int count=0 ;

	printf("�ű� ����� �Դϱ�?\n");
	printf("1. �� \t\t2. �ƴϿ�\n\n");
	scanf_s("%d",&z);

	fflush(stdin);

	switch (z) {
	case 1: {
		printf("����� �߰����� �������ּ���\n\n");
	
		break;
	}
	case 2: {

		printf("���� ����� �˻�\n");
		Search_User(User_file);					//����� �˻� �Լ� ȣ��
		if ((!strcmp(data8.video1, A) == 0) && (!strcmp(data8.video3, A) == 0) && (!strcmp(data8.video2, A) == 0)) {		
			/* �뿩 ��Ȳ�� ������ ������ count�� ���� ������Ŵ.*/
			++count;													//�ѹ� �о�ö����� count�� �� 1�� ����
			break;
		}
		if (count != 0) {		//count�� ���� 0 �̾ƴ϶�� �� 1�� ���������� 3���� ���� ���ȴٸ� �ݳ����� �����ϵ��� �޼��� ����ϰ� ���α׷�����
			printf("���� ������ �ݳ����� �������ּ���.\n");
			exit(1);
		}

		printf("�뿩�� ������ �˻��մϴ�\n");
		Search_Video(Video_file);


		if ((strcmp(data9.have, B) == 0)) {
			strcpy(data9.have, C);


			printf("�̸� : %s ��Ϲ�ȣ : %s ������Ȳ %s \n\n", data9.name, data9.number, data9.have);
			printf("\n\n�뿩�Ϸ�\n\n");

			Write(User_file, Video_file,Count,COUNT);

			break;
		}
		else {
			printf("�������� ������ �ƴմϴ�.\n\n");
			exit(1);
		}
		break;
	}
	
	default :
		printf("�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���.\n");
		exit(1);
	}
}

void Return_Video(FILE *User_file, FILE *Video_file) {		//���� �ݳ��� ���� �Լ�

	Count = 0;

	int count = 0;
	int u=0;

	printf("�ݳ��� ������� ���� �˻� \n");
	Search_User(User_file);
	if ((strcmp(data8.video1, A) == 0) && (strcmp(data8.video3, A) == 0) && (strcmp(data8.video2, A) == 0)) {
		++count;													//������� ���� �뿩 ��Ȳ�� ���� �����϶� count �� 1 ����
	}
	if (count != 0) {												//count�� ���� 0�� �ƴҰ�� �޼����� ����ϰ� ���α׷� ����
		printf("�뿩�� ������ �����ϴ�.");
		exit(1);
	}

	printf("�ݳ��� ������ �����ϼ���\n");							//������� ���� �뿩��Ȳ�� ����ϰ� ���߿� �ݳ��� ������ �����ϵ��� ����
	printf("1.%s 2.%s 3.%s\n\n", data8.video1, data8.video2, data8.video3);
	scanf_s("%d", &u);												//����ڰ� �����Ѱ��� u�� ����


	switch (u) {													//u�� �����Ѱɷ� switch�� ȣ��
	case 1:
		while (!feof(Video_file)) {									//������ ���� �ƴϸ� �ݺ�
			fread(&data9, sizeof(data9), 1, Video_file);
			Count++;
			if (strcmp(data8.video1, data9.name)==0) {				//1���� �����Ѱ�� ���� 1�� ��
				printf("%s\t %s", data9.name, data9.have);
				break;
			}
		}
		break;
	case 2:
		while (!feof(Video_file)) {									//������ ���� �ƴϸ� �ݺ�
			fread(&data9, sizeof(data9), 1, Video_file);
			Count++;
			if (strcmp(data8.video2, data9.name)==0) {				//2���� �����Ѱ�� ���� ��Ȳ 2�� ��
				printf("%s\t %s", data9.name, data9.have);
				break;
			}
		}
		break;
	case 3:
		while (!feof(Video_file)) {									//������ ���� �ƴϸ� �ݺ�
			fread(&data9, sizeof(data9), 1, Video_file);
			Count++;
			if (strcmp(data8.video3, data9.name) == 0) {			//3���� �����Ѱ�� ���� ��Ȳ 3�� ��
				printf("%s\t %s", data9.name, data9.have);
				break;
			}
		}
		break;

	default: {
		printf("error\n\n");
		exit(1);
	}
	}

	if (strcmp(data9.have, C) == 0) {				//�ݳ��Ϸ��� ������ �̺���, �� �뿩��(=C) �϶��� ����

		strcpy(data9.have, B);						//���� ���� ��Ȳ�� B(=����)�� �ٲ�


		printf("�̸� : %s ��Ϲ�ȣ : %s ������Ȳ %s \n\n", data9.name, data9.number, data9.have);
		printf("\n\n�ݳ��Ϸ�\n\n");

		Write2(User_file, Video_file,Count,COUNT);	//���Ͽ� ����ü�� ���� �Լ� ȣ��
	}
	else {											//�뿩���� �ƴ϶�� �޼����� ����� ����
		printf("�������� ������ �ƴմϴ�.\n\n");
		exit(1);
	}
}

void Write(FILE *User_file, FILE *Video_file,int Count,int COUNT) {


	fseek(Video_file, 0L, SEEK_END);								//���� �������� ��ġ�� ���� �� ������ �̵���Ű��
	fseek(Video_file, ((Count - 1) * sizeof(data9)), SEEK_SET);		//������ �����������κ��� ������ count�� -1 ��ŭ ����ü(data2)�� ũ�⿡ ���� �� �� ��ŭ �����͸� ������ �̵���Ų��
	fwrite(&data9, sizeof(data9), 1, Video_file);

	printf("�̸� : %s ��ȭ��ȣ : %s �뿩��Ȳ %s %s %s \n\n", data8.name, data8.number, data8.video1, data8.video2, data8.video3);

	if (strcmp(data8.video1, A) == 0) {								//������� ���� �뿩 ��Ȳ�� �����ΰ��� ã�Ƽ� �װ��� ����� ����
		strcpy(data8.video1, data9.name);
		fseek(User_file, 0L, SEEK_END);						
		fseek(User_file, ((COUNT - 1) * sizeof(data8)), SEEK_SET);	
		fwrite(&data8, sizeof(data8), 1, User_file);
	}
	else if (strcmp(data8.video2, A) == 0) {
		strcpy(data8.video2, data9.name);
		fseek(User_file, 0L, SEEK_END);						
		fseek(User_file, ((COUNT - 1) * sizeof(data8)), SEEK_SET);		
		fwrite(&data8, sizeof(data8), 1, User_file);
	}
	else if (strcmp(data8.video3, A) == 0) {
		strcpy(data8.video3, data9.name);
		fseek(User_file, 0L, SEEK_END);						
		fseek(User_file, ((COUNT - 1) * sizeof(data8)), SEEK_SET);		
		fwrite(&data8, sizeof(data8), 1, User_file);
	}
	else printf("error\n\n");

}

void Write2(FILE *User_file, FILE *Video_file,int Count, int COUNT) {

	fseek(Video_file, 0L, SEEK_END);						
	fseek(Video_file, ((Count - 1) * sizeof(data9)), SEEK_SET);		
	fwrite(&data9, sizeof(data9), 1, Video_file);

	printf("�̸� : %s ��ȭ��ȣ : %s �뿩��Ȳ %s %s %s \n\n", data8.name, data8.number, data8.video1, data8.video2, data8.video3);

	if (strcmp(data8.video1, data9.name) == 0) {							//������� ���� �뿩 ��Ȳ�� �ݳ��� ������ ���� �̸��� �������� ã�Ƽ� �װ��� ����� ����
		strcpy(data8.video1, A);
		fseek(User_file, 0L, SEEK_END);						
		fseek(User_file, ((COUNT-1) * sizeof(data8)), SEEK_SET);		
		fwrite(&data8, sizeof(data8), 1, User_file);
	}
	else if (strcmp(data8.video2, data9.name) == 0) {
		strcpy(data8.video2, A);
		fseek(User_file, 0L, SEEK_END);						
		fseek(User_file, ((COUNT-1) * sizeof(data8)), SEEK_SET);		
		fwrite(&data8, sizeof(data8), 1, User_file);
	}
	else if (strcmp(data8.video3, data9.name) == 0) {
		strcpy(data8.video3, A);
		fseek(User_file, 0L, SEEK_END);						
		fseek(User_file, ((COUNT-1) * sizeof(data8)), SEEK_SET);		
		fwrite(&data8, sizeof(data8), 1, User_file);
	}
	else printf("error\n\n");

}

void User_Delete(FILE *User_file) {						//����ڸ� �����ϴ� �Լ�

	USER data2;											//������ �о�ͼ� �� �� �������� ������ ����ü data2 ���� 
	char A[20] = "  ";									//�������� ���� (����ó��) ���ڿ� �迭 A ����
	char search[20];
	
	int count = 0;												//�������� ��ġ�� ������ ���� count�� �����ϰ� 0���� �ʱ�ȭ

	fseek(User_file, 0, SEEK_SET);								//�������� ��ġ�� ������ ó������
	fflush(stdin);												//ǥ������� ��ġ�� ���۸� ���
	getchar();													//������ ���½ð�(�ٷ� �ȳѾ��)���� ���

	printf("������ ����� �̸��� �Է��ϼ���\n\n");				//����ڰ� ������ ����� �̸��� �Է��ϰ� ����
	gets(search);												//�� �Է��� �̸��� search�� ����

	while (!feof(User_file)) {									//������ ���� �ƴϸ� �ݺ�
		fread(&data2, sizeof(data2), 1, User_file);				//���� �������� ��ġ���� �ڷḦ �о ����ü data2�� ����.
		count++;												//�ѹ� �о�ö����� count�� �� 1�� ����
		if (strcmp(data2.name, search) == 0) {					//data2.name�� search�� ���� ������������ ����
			
			strcpy(data2.name, A);								//�� ����ü.name�� A(����)�� �ٿ��־� �̸��� ����ó���� ���ش�
			strcpy(data2.number, A);							//�����ϰ� �� ����ü.number�� A(����)�� �ٿ��־� ��ȭ��ȣ�� ����ó���Ѵ�.
			strcpy(data2.video1,A);								//�� �о�� ����ü .video�� A(����)�� �ٿ��־� ���� �뿩 ��Ȳ�� ����ó���Ѵ�.
			strcpy(data2.video2, A);
			strcpy(data2.video3, A);

			fseek(User_file, 0L, SEEK_END);						
			fseek(User_file, ((count - 1) * sizeof(data2)), SEEK_SET);			
			fwrite(&data2, sizeof(data2), 1, User_file);					

			break;											
		}
	}
}

void Video_Delete(FILE *Video_file) {						//������ ������ �����ϴ� �Լ�

	VIDEO data2;											//������ �о�ͼ� �� �� �������� ������ ����ü data2 ���� 
	char A[20] = "  ";										//�������� ���� (����ó��) ���ڿ� �迭 A ����
	char B[10] = "  ";										//�������� ���� (����ó��) ���ڿ� �迭 B ����
	char search[20];

	int count = 0;											//�������� ��ġ�� ������ ���� count�� �����ϰ� 0���� �ʱ�ȭ

	fseek(Video_file, 0, SEEK_SET);							//�������� ��ġ�� ������ ó������
	fflush(stdin);											//ǥ������� ��ġ�� ���۸� ���
	getchar();												//������ ���½ð�(�ٷ� �ȳѾ��)���� ���

	printf("������ ������ �̸��� �Է��ϼ���\n\n");		//����ڰ� ������ ����� �̸��� �Է��ϰ� ����
	gets(search);											//�� �Է��� �̸��� search�� ����

	while (!feof(Video_file)) {								//������ ���� �ƴϸ� �ݺ�
		fread(&data2, sizeof(data2), 1, Video_file);		//���� �������� ��ġ���� �ڷḦ �о ����ü data2�� ����.
		count++;											//�ѹ� �о�ö����� count�� �� 1�� ����
		if (strcmp(data2.name, search) == 0) {			    //data2.name�� search�� ���� ������������ ����

			strcpy(data2.name, A);							//�� ����ü.name�� A(����)�� �ٿ��־� �̸��� ����ó���� ���ش�
			strcpy(data2.number, A);						//�����ϰ� �� ����ü.number�� A(����)�� �ٿ��־� ��ȭ��ȣ�� ����ó���Ѵ�.
			strcpy(data2.have, B);							//�� �о�� ����ü.have�� B(����)�� �ٿ��־� ������Ȳ�� ����ó���Ѵ�.
	
			fseek(Video_file, 0L, SEEK_END);						
			fseek(Video_file, ((count - 1) * sizeof(data2)), SEEK_SET);			
			fwrite(&data2, sizeof(data2), 1, Video_file);				

			break;										
		}
	}
}