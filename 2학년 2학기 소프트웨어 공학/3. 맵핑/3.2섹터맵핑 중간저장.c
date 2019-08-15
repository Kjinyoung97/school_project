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
	block = (Secter / 32) + 3;
	Secter2 = block * 32;

	printf("������ ���� %d\n", Secter);
	printf("������ ���� ���� %d (���� ��� �ΰ� ����, 0����� = ������ ���� ���, 1����� = ���к��) \n", block);

	lsn = (LSN *)malloc(sizeof(LSN)*Secter2);
	psn = (LSN *)malloc(sizeof(LSN)*Secter2);
	memory = (MEMORY *)malloc(sizeof(MEMORY)*Secter2);
	blo = (BLOCK *)malloc(sizeof(BLOCK)*block);

	for (i = 0; i <= Secter2; i++) {
		lsn[i].data = 0 + i;
		psn[i].data = (Secter2 - 1) - i;

		if (i >= 32) {
			w = i / 32;		//������� �������
			j = i % 32;		//w����� ���° ��������
			strcpy(blo[w].MEmory[j].data, A);	//�� �ʱ�ȭ

		}
		else {
			j = i % 32;
			strcpy(blo[block].MEmory[j].data, A);	//�� �ʱ�ȭ
			strcpy(blo[0].MEmory[i].data, A);		//���к� �ʱ�ȭ
			strcpy(blo[1].MEmory[i].data, A);
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
	Print_table();
}

void Flash_read() {
	int q, j, w, count = 0;

	for (q = 0; q < Secter2; q++) {
		if (block > 3) {
			w = q / 32;		//������� �������
			j = q % 32;		//w����� ���° ��������
			if (strcmp(blo[w+1].MEmory[j].data, A) != 0) {
				count++;
				printf("����� ���ڿ� : %s\n", blo[w+1].MEmory[j].data);
				printf("lsn %d���� ����� psn %d ��, %d �� �� %d ��° ���Ϳ� ����Ǿ��ֽ��ϴ�.\n", lsn[q].link, q, w+1, j);
			}
		}
		else if (block == 3) {
			w = q / 32;
			j = q % 32;
			if (strcmp(blo[w+1].MEmory[j].data, A) != 0) {
				count++;
				printf("����� ���ڿ� : %s\n", blo[w+1].MEmory[j].data);
				printf("lsn %d���� ����� psn %d ��, %d �� �� %d ��° ���Ϳ� ����Ǿ��ֽ��ϴ�.\n", lsn[q].link, q,w+1, j);
			}
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

	if (block > 3) {
		w = Q / 32;		//������� �������
		j = Q % 32;		//w����� ���° ��������
		if (strcmp(blo[w+2].MEmory[j].data, A) != 0) {
			printf("�̹� ����Ǿ��ִ� �����Ͱ� �ֽ��ϴ�. ���� ��Ͽ� �����մϴ�.\n");
			for (i = 0; i < 32; i++) {
				if (strcmp(blo[1].MEmory[i].data, A) == 0) {
					strcpy(blo[1].MEmory[i].data, save);
					printf("����Ϸ�.\n\n\n");
					psn[k].data = 32 + i;
					break;
					}
			}
			if (i == 32) {
				printf("��� ���а����� �� á���ϴ�. ���а����� ����� �մϴ�.\n\n");
				Flash_erase(k);
			}
		}
		else {
			strcpy(blo[w+2].MEmory[j].data, save);
			printf("lsn %d���� ����� psn %d ��, %d �� �� %d ��° ���Ϳ� ����Ǿ����ϴ�.\n", k, Q, w+2, j);
		}
	}
	else if(block == 3) {
		j = Q % 32;
		if (strcmp(blo[block].MEmory[j].data, A) != 0) {
			printf("�̹� ����Ǿ��ִ� �����Ͱ� �ֽ��ϴ�. ���� ��Ͽ� �����մϴ�.\n");
			for (i = 0; i < 32; i++) {
				if (strcmp(blo[1].MEmory[i].data, A) == 0) {
					strcpy(blo[1].MEmory[i].data, save);
					printf("����Ϸ�.\n\n\n");
					psn[k].data = 32 + i;
					break;
				}
			}
			if (i == 32) {
				printf("��� ���а����� �� á���ϴ�. ���а����� ����� �մϴ�.\n\n");
				Flash_erase(k);
			}
		}
		else {
			strcpy(blo[block].MEmory[j].data, save);
			printf("lsn %d���� ����� psn %d ��, %d�� �� %d ��° ���Ϳ� ����Ǿ����ϴ�.\n", k, Q,block, j);
		}
	}
}

void Flash_erase(int k) {

	int Q, w, j, u, z;

	if ((k < 0) || (k >= Secter)) {
		printf("\n\n��ȿ�� ��ġ�� �ƴմϴ�. ���α׷� ����.");
		exit(1);
	}

	Q = lsn[k].link;

	if (Q >= 32) {
		w = Q / 32;		//������� �������
		j = Q % 32;		//w����� ���° ��������

		if (strcmp(blo[w+2].MEmory[j].data, A) == 0) {
			printf("\n\n�̹� �����Ͱ� ����ִ� ��ġ�Դϴ�. ���α׷��� �����մϴ�.\n");
			exit(1);
		}

		printf("\n�ش� ��ġ�� ������ �Ҽ� ���� ����մϴ�.\n");

		printf("\n������ ���͸��� �����ϰ� ���� ���� ��Ͽ� ����. ���� ��� ���� ����ó��.\n\n");
		for (u = 0; u < 32; u++) {
			if (u != j) {
				strcpy(blo[0].MEmory[u].data, blo[w+2].MEmory[u].data);
				strcpy(blo[w+2].MEmory[u].data, A);
				printf("%d �� �� %d ��° ���͸� 0�� �� %d ��° ���Ϳ� ���� \n", w, u,  u);
			}
		}

		printf("\n������ ��ġ�� �����ϰ� ���� ��Ͽ� �ִ� �����͵��� ������ �� ��ġ�� ����\n\n");
		for (z = 0; z < 32; z++) {
			strcpy(blo[w+2].MEmory[z].data, blo[0].MEmory[z].data);
			printf("%d �� %d ��° ���͸� 0�� �� %d ��° ���Ϳ� ���� \n", w+2, z, z);

			if (z == 0) printf("\n ���� ����� �����ϰ� ���� ������ ����\n");

			printf("0�� ��� %d ��° ���� ���� ��\n\n", z);
			strcpy(blo[0].MEmory[z].data, A);

			if (z == j) {
				printf("\n\n�����Ϸ� \n\n");
				break;
			}
		}
		printf("\nlsn %d���� ����� psn %d ��, %d �� �� %d ��° ���Ͱ� ����ó���Ǿ����ϴ�.\n", k, Q, w+2, j);
	}
	else {
		j = Q % 31;

		if (strcmp(blo[block].MEmory[j].data, A) == 0) {
			printf("\n\n�̹� �����Ͱ� ����ִ� ��ġ�Դϴ�. ���α׷��� �����մϴ�.\n");
			exit(1);
		}

		printf("\n������ ��ġ�� ������ ������ ���� ��Ͽ� ����\n\n");


		printf("\n�ش� ��ġ�� ������ �Ҽ� ���� ����մϴ�.\n");

		for (u = 0; u < 32; u++) {
			if (u != j) {
				strcpy(blo[0].MEmory[u].data, blo[block].MEmory[u].data);
				strcpy(blo[block].MEmory[u].data, A);
				printf("%d �� �� %d ��° ���͸� 0�� �� %d ��° ���Ϳ� ���� \n", block,u,u);
			}
		}

		printf("\n���� ��Ͽ� �ִ� �����͵��� ������ �� ��ġ�� ����\n\n");
		for (z = 0; z < 32; z++) {

			if (z == 0) printf("\n ���� ����� �����ϰ� ���� ������ ����\n");

			strcpy(blo[block].MEmory[z].data, blo[0].MEmory[z].data);
			printf("0�� �� %d ��° ���͸� %d�� �� %d ��° ���Ϳ� ����, ���к�� %d ���� �����Ϸ� \n", z, block, z);


			strcpy(blo[block].MEmory[z].data, A);

		}
		printf("lsn %d���� ����� psn %d ��, %d�� �� %d ��° ���Ͱ� ����ó���Ǿ����ϴ�.\n", k, Q,block, j);

	}

}

void FTL_write() {
	Flash_write();
}

void main() {
	int u, o,w,j;

	init();

	while (1) {
		printf("������ ����� �����ϼ���.\t1.���\t2.������ ����\t3.������ ����\t4.���α׷�����\n");
		scanf("%d", &u);

		switch (u)
		{

		case 1:
			FTL_read();
			break;

		case 2:
			FTL_write();
			break;

		case 4:
			for (o = 0; o < Secter2; o++) {
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