#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LSN {
	int data;
	struct LSN *link;
}LSN;

typedef struct MEMORY {
	char data[20];
}MEMORY;

typedef struct BLOCK {
	struct MEMORY MEmory[32];
}BLOCK;

int Secter,Secter2, block;

LSN *lsn;
MEMORY *memory;
LSN *psn;
BLOCK *blo;

char A[20] = "  ";
int Write = 0, Erase = 0;

void init();
void Flash_read();
void Flash_write();
void Flash_erase();
void FTL_read();

void init() {

	int size;
	int i, w, j;

	printf("�޸𸮴� ��MB �Դϱ�? (2MB����)\n");
	scanf("%d", &size);

	Secter = (size * 1024) / 512;
	block = (Secter / 32) + 2;
	Secter2 = block * 32;

	printf("������ ���� %d\n", Secter);
	printf("������ ���� ���� %d (���� ��� �Ѱ� ����, 0����� = ���к��) \n", block);

	lsn = (LSN *)malloc(sizeof(LSN)*Secter2);
	psn = (LSN *)malloc(sizeof(LSN)*Secter2);
	memory = (MEMORY *)malloc(sizeof(MEMORY)*Secter2);
	blo = (BLOCK *)malloc(sizeof(BLOCK)*block);

	for (i = 0; i <= Secter2; i++) {
		lsn[i].data = 0 + i;
		psn[i].data = (Secter2 - 1) - i;
		psn[i].link = NULL;

		if (i >= 32) {
			w = i / 32;		//������� �������
			j = i % 32;		//w����� ���° ��������
			strcpy(blo[w].MEmory[j].data, A);	//�� �ʱ�ȭ

		}
		else {
			j = i % 32;
			strcpy(blo[block].MEmory[j].data, A);	//�� �ʱ�ȭ
			strcpy(blo[0].MEmory[i].data, A);		//���к� �ʱ�ȭ
		}

		lsn[i].link = psn[i].data;
	}
}

void Print_table() {		//�������̺��� ����ϴ� �Լ�
	int i;
	for (i = 0; i < Secter; i++) {
		printf("lsn�� �� %d\t psn�� ��%d\t\n", lsn[i].data, psn[i].data);
	}
}

void FTL_read() {
	Flash_read();
}

void Flash_read() {
	int q, j, w, count = 0;

	for (q = 0; q < Secter2; q++) {
			w = q / 32;		//������� �������
			j = q % 32;		//w����� ���° ��������
			if (strcmp(blo[w].MEmory[j].data, A) != 0) {
				count++;
				printf("����� ���ڿ� : %s\n", blo[w].MEmory[j].data);
				printf("lsn %d���� ����� psn %d ��, %d �� �� %d ��° ���Ϳ� ����Ǿ��ֽ��ϴ�.\n", lsn[q].link, q, w, j);
		}
	}
	if (count == 0)
		printf("\n����� �����Ͱ� �����ϴ�.\n");
}

void Flash_write() {

	int k, Q, w, j,i,count;
	char save[20];

	printf("������ ��ġ(lsn ��ġ)�� �Է��Ͻÿ�.");
	scanf("%d", &k);

	if ((k < 0) || (k >= Secter)) {
		printf("\n\n��ȿ�� ��ġ�� �ƴմϴ�. ���α׷� ����.");
		exit(1);
	}

	printf("������ ���ڿ��� �Է��Ͻÿ�.");
	scanf("%s", &save);

	Q = lsn[k].link;

		w = Q / 32;		//������� �������
		j = Q % 32;		//w����� ���° ��������
		if (strcmp(blo[w].MEmory[j].data, A) != 0) {
			printf("�̹� ����Ǿ��ִ� �����Ͱ� �ֽ��ϴ�. ���� ��Ͽ� �����մϴ�.\n");
			for (i = 0; i < 32; i++) {
				if (strcmp(blo[0].MEmory[i].data, A) == 0) {
					strcpy(blo[0].MEmory[i].data, save);
					printf("����Ϸ�.\n\n\n");
					psn[k].data = 32 + i;
					Write++;
					break;
					}
			}
			if (i == 32) {
				printf("��� ���а����� �� á���ϴ�. ���а����� ����� �մϴ�.\n\n");
				Flash_erase();
				strcpy(blo[0].MEmory[0].data, save);
				Write++;
			}
		}
		else {
			strcpy(blo[w].MEmory[j].data, save);
			printf("lsn %d���� ����� psn %d ��, %d �� �� %d ��° ���Ϳ� ����Ǿ����ϴ�.\n", k, Q, w, j);
			Write++;
		}
}

void Flash_erase() {

	int u;

		for (u = 0; u < 32; u++) {
				strcpy(blo[0].MEmory[u].data, A);
				printf("0�� ��(������ �����) %d ��° ���͸� ������ \n", u);
				Erase++;
		}
}

void FTL_write() {
	Flash_write();
}

void main() {
	int u, o,w,j;

	init();

	while (1) {
		printf("������ ����� �����ϼ���.\t1.����Ǿ��ִ� ������ ���\t2.������ ����\t3.���� ���̺� ���\t4.���α׷�����\n");
		scanf("%d", &u);

		switch (u)
		{

		case 1:
			FTL_read();
			break;

		case 2:
			Write = 0;
			Erase = 0;
			FTL_write();
			printf("\n���⿬�� %d��, �������� %d��\n", Write, Erase);
			break;

		case 3:
			Print_table();
			break;

		case 4:
			for (o = 0; o <= Secter2; o++) {
				if (lsn[o].data != NULL)
					free(lsn[o].data);
				free(psn[o].data);
				if (o >= 32) {
					w = o / 31;		//������� �������
					j = o % 31;		//w����� ���° ��������
					free(blo[w].MEmory[j].data);	//�� �ʱ�ȭ
				}
				else {
					j = o % 31;
					free(blo[0].MEmory[j].data);	//�� �ʱ�ȭ
					free(blo[block].MEmory[j].data);		//���к� �ʱ�ȭ
					free(blo[block-1].MEmory[j].data);
				}
				free(lsn[o].link);
			}
			exit(1);
			break;

		default:
			printf("�߸��� ���� �ԷµǾ����ϴ�. �ٽ� �Է��Ͻʽÿ�.");
			break;
		}
	}
}