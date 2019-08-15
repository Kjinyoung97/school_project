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

int Secter, Secter2, block;

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
	int i, w, j,l,q;

	printf("�޸𸮴� ��MB �Դϱ�? (2MB����)\n");
	scanf("%d", &size);

	Secter = (size * 1024) / 512;
	block = (Secter / 32) + 2;
	Secter2 = block * 32;

	printf("������ ���� %d\n", Secter);
	printf("������ ���� ���� %d (���� ��� �Ѱ� ����) \n", block);

	lsn = (LSN *)malloc(sizeof(LSN)*block);
	psn = (LSN *)malloc(sizeof(LSN)*block);
	memory = (MEMORY *)malloc(sizeof(MEMORY)*Secter2);
	blo = (BLOCK *)malloc(sizeof(BLOCK)*block);

	for (i = 0; i < block; i++) {
		lsn[i].data = 0 + i;
		psn[i].data = (block - 1)-i;
		psn[i].link = NULL;

	for (q = 0; q <= Secter2; q++) {
			w = q / 32;		//������� �������
			j = q % 32;		//w����� ���° ��������
			strcpy(blo[w].MEmory[j].data, A);	//�� �ʱ�ȭ
		lsn[i].link = psn[i].data;
		}
	}
}

void Print_table() {		//�������̺��� ����ϴ� �Լ�
	int i;
	for (i = 0; i < block-1; i++) {
		printf("lbn�� �� %d\t pbn�� ��%d\t\n", lsn[i].data, lsn[i].link);
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
				printf("%d��° ��(=psb��) %d���Ϳ� ����Ǿ�����\n.",w,j);
			}

	}
	if (count == 0)
		printf("\n����� �����Ͱ� �����ϴ�.\n");
}

void Flash_write() {

	int k,Q,j,R,b;
	char save[20];

	printf("������ ��ġ�� �Է��Ͻÿ�.");
	scanf("%d", &k);

	if ((k < 0) || (k >= Secter)) {
		printf("\n\n��ȿ�� ��ġ�� �ƴմϴ�. ���α׷� ����.");
		exit(1);
	}

	printf("������ ���ڿ��� �Է��Ͻÿ�.");
	scanf("%s", &save);

	b = k / 32;
	j = k % 32;
	Q = lsn[b].link;
	R = lsn[block-1].link;

	if (strcmp(blo[Q].MEmory[j].data, A) != 0) {
		printf("�̹� ����Ǿ��ִ� �����Ͱ� �ֽ��ϴ�. ���� ��Ͽ� �����մϴ�.\n");
		Flash_erase(save, k);
			
		}
		else {
			strcpy(blo[Q].MEmory[j].data, save);
			printf("lbn %d�� ������ %d�� ������ %d �� ��� %d�� ���Ϳ� ����Ǿ���.\n", b, j, Q, j);
			Write++;
		}
	}

void Flash_erase(char save[],int k) {

	int b,R,Q, w, j, u, z;

	b = k / 32;
	j = k % 32;
	Q = lsn[b].link;					//���� ������ ��ġ
	R = lsn[block - 1].link;			//���� ������ ��ġ

	if ((k < 0) || (k >= Secter)) {
		printf("\n\n��ȿ�� ��ġ�� �ƴմϴ�. ���α׷� ����.");
		exit(1);
	}

		printf("\n�ش� ��ġ�� ������ �Ҽ� ���� ����մϴ�.\n");

		printf("\n�ߺ��� ���͸��� �����ϰ� ���� ���� ��Ͽ� ����. ���� ��� ���� ����ó��.\n\n");
		for (u = 0; u < 32; u++) {
			if (u != j) {
				if (strcmp(blo[Q].MEmory[u].data, A) != 0) {
					strcpy(blo[R].MEmory[u].data, blo[Q].MEmory[u].data);
					printf("%d �� �� %d ��° ���͸� %d�� �� %d ��° ���Ϳ� ���� \n",Q, u, R, u);
					Write++;
				}
			}
			else if (j == u) {
				strcpy(blo[R].MEmory[u].data, save);		//���� ����� �ߺ��� ������ �ڸ����� ���ο� ���ڿ� ����
				printf("�ߺ��� ��ġ ���� �� ����Ϸ�\n");
				Write++;
			}
			if (strcmp(blo[Q].MEmory[u].data, A) != 0) {
				strcpy(blo[Q].MEmory[u].data, A);		//������� ����ó��
				Erase++;
			}
		}
		lsn[b].link = R;
		lsn[block - 1].link = Q;
}

void FTL_write() {
	Flash_write();
}

void main() {
	int u, o, w, j;

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
			for (o = 0; o <= block; o++) {
				if (lsn[o].data != NULL)
					free(lsn[o].data);
				free(lsn);
				if (psn[o].data != NULL) {
					free(psn[o].data);
					free(psn[o].link);
				}
				free(psn);
				if (o >= 32) {
					w = o / 31;		
					j = o % 31;		
					free(blo[w].MEmory[j].data);	
				}
				else {
					j = o % 31;
					free(blo[0].MEmory[j].data);	//�� �ʱ�ȭ
					free(blo[block].MEmory[j].data);		//���к� �ʱ�ȭ
					free(blo[block - 1].MEmory[j].data);
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