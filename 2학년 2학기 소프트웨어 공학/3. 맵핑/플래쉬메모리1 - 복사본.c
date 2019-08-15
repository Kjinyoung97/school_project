#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LSN {
	int data;
	struct LSN *link;
}LSN;

typedef struct MEMORY{
	char data[20];
}MEMORY;

typedef struct BLOCK{
	struct MEMORY MEmory[32];
}BLOCK;

int Secter,block;

LSN *lsn;
MEMORY *memory;
LSN *psn;
BLOCK *blo;

void init(FILE *TABLE_file, FILE *MEMORY_file);
void Flash_read(FILE *TABLE_file, FILE *MEMORY_file);
void Flash_write(FILE *TABLE_file, FILE *MEMORY_file);

void init(FILE *TABLE_file, FILE *MEMORY_file){

	fopen_s(&TABLE_file, "TABLE_file.bin", "rb+");				//������������� ����. ���� ������ ������� �ű� ����
	if (TABLE_file == NULL) {									//���� ���� Ȥ�� ���⿡ ������ ��� 
		puts("�Է��� ���� ������ �� �� �����ϴ�.\n");			//�����޼��� ���
		exit(1);												//���α׷� ����
	}

	fopen_s(&MEMORY_file, "MEMORY_file.bin", "rb+");				//������������� ����. ���� ������ ������� �ű� ����
	if (MEMORY_file == NULL) {									//���� ���� Ȥ�� ���⿡ ������ ��� 
		puts("�Է��� ���� ������ �� �� �����ϴ�.\n");			//�����޼��� ���
		exit(1);												//���α׷� ����
	}

	int size;
	int i,w,j;
	char A[20] = "  ";

		printf("�޸𸮴� ��MB �Դϱ�? (2MB����)\n");
		scanf("%d", &size);

		Secter = (size * 1024) / 512;
		block = (Secter / 32 ) +1;

		printf("������ ���� %d\n", Secter);
	
		lsn = (LSN *)malloc(sizeof(LSN)*Secter);
		psn = (LSN *)malloc(sizeof(LSN)*Secter);
		memory = (MEMORY *)malloc(sizeof(MEMORY));
		blo = (BLOCK *)malloc( sizeof(BLOCK)*block);

		for (i = 0; i < Secter; i++) {
			lsn[i].data = 0 + i;
			psn[i].data = (Secter - 1) - i;

			if (i >=32 ){
				w = i/31;		//������� �������
				j = i%31;		//w����� ���° ��������
				strcpy(blo[w].MEmory[j].data,A);	//�� �ʱ�ȭ
			}
			else {
				j = i%31;
				strcpy(blo[0].MEmory[j].data,A);	//�� �ʱ�ȭ
			}

			fwrite(&blo, sizeof(blo), 1, MEMORY_file);
			fwrite(&lsn, sizeof(lsn), 1, TABLE_file);
			fwrite(&psn, sizeof(psn), 1, TABLE_file);
			lsn[i].link = psn[i].data;


		}

		free(lsn);
		free(psn);
		free(memory);
		free(blo);
}

void Flash_read(FILE *TABLE_file, FILE *MEMORY_file) {

	int q, i, j, w;
	LSN *K;

	K = (LSN *)malloc(sizeof(LSN));
	while (!feof(TABLE_file)) {
		fread(&K, sizeof(K), 1, TABLE_file);
		printf("lsn�� �� %d \n\n", K);
		fread(&K, sizeof(K), 1, TABLE_file);
		printf("psn�� �� %d \n\n", K);
	}
	for (i = 0; i < Secter; i++) {
		printf("lsn�� �� %d\t psn�� ��%d\t\n", lsn[i].data, psn[i].data);
	}
	for (q = 0; q < Secter; q++) {
		if (i >= 32) {
			w = i / 31;		//������� �������
			j = i % 31;		//w����� ���° ��������
			printf("����� ���ڿ� : %s\n", blo[w].MEmory[j].data);
		}
		else {
			j = i % 31;
			printf("����� ���ڿ� : %s\n", blo[0].MEmory[j].data);
		}
	}

	free(K);

}

void Flash_write (FILE *TABLE_file, FILE *MEMORY_file){


	int k,Q,w,j;
	char save[20];

	printf("������ ��ġ�� �Է��Ͻÿ�.");
	scanf("%d",&k);

	printf("������ ���ڿ��� �Է��Ͻÿ�.");
	scanf("%s",&save);

	Q=lsn[k].link;

	if (Q >=32 ){
				w = Q/31;		//������� �������
				j = Q%31;		//w����� ���° ��������
				strcpy(blo[w].MEmory[j].data, save);
				printf("%d �� �� %d ��° ���Ϳ� ����Ǿ����ϴ�.\n",w,j);
			}
			else {
				j = Q%31;
				strcpy(blo[0].MEmory[j].data, save);
				printf("0�� �� %d ��° ���Ϳ� ����Ǿ����ϴ�.\n",j);
			}
}


void main(FILE *TABLE_file,FILE *MEMORY_file) {

	fopen_s(&TABLE_file, "TABLE_file.bin", "ab+");				//������������� ����. ���� ������ ������� �ű� ����
	if (TABLE_file == NULL) {									//���� ���� Ȥ�� ���⿡ ������ ��� 
		puts("�Է��� ���� ������ �� �� �����ϴ�.\n");			//�����޼��� ���
		exit(1);												//���α׷� ����
	}

	fopen_s(&MEMORY_file, "MEMORY_file.bin", "ab+");			//������������� ����. ���� ������ ������� �ű� ����
	if (MEMORY_file == NULL) {									//���� ���� Ȥ�� ���⿡ ������ ��� 
		puts("�Է��� ���� ������ �� �� �����ϴ�.\n");			//�����޼��� ���
		exit(1);												//���α׷� ����
	}
	

	fclose(TABLE_file);
	fclose(MEMORY_file);

	init(TABLE_file,MEMORY_file);
	Flash_read(TABLE_file, MEMORY_file);
	Flash_write(TABLE_file, MEMORY_file);
	Flash_read(TABLE_file, MEMORY_file);
}