#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable : 4996)
int KB, Byte, A_sector,sector, R_sector, sector, R_block_count;
//A_sector = ��ȿ ������(ó�� ������ ������)�� �����ϴ� �⺻���� ���弽��, R_sector = ��ü ����� ���� �� , A_block = A_sector�� ��ϼ� , R_block = ��ü ����� �� 

int CINT3,CINT3_block,CINT3_offset;



int WriteCount = 0;
int EraseCount = 0;

typedef struct ANAND {
	char data[20];		//�������� ��ȿ ���θ� �ۼ�
	char spae[2];			//�������� ���� ������ ��Ÿ��
}ANAND;					//������ ���� + ���� ���� �̷��� �ؼ� �ϳ��� ���͸� ��Ÿ���� ����ü


ANAND A_DATA[13000];		//��ȿ ������ ���� 9135�� �� 142���� ���
ANAND A_NAND[20000];			//��ü ������ ���� 865�� �� 13���� ���
ANAND C_DATA[64];			//������ �����

char commend[2];		//�ɰ��� �ӽ÷� W�� ������ ���ڿ�
char sector_number[6];	//�ɰ��� ���� ��ȣ�� �ӽ÷� ������ ���ڿ�

char Reding[10];

int lsn[14280];


int psn[14280];

char commend[2];
char sector_number[6];

void init();
void Table_print();
void Trace(FILE *trace);
void margin();

void main(FILE *trace) {
	int k;

	while (1) {
		printf("���ϴ� �޴� ����\t1. �ʱ� ���� \t2. ���� ���̺� ���\t3. ����  \t4. trace\n\n");
		scanf("%d", &k);

		switch (k) {
		case 1:
			init();
			break;
		case 2:
			Table_print();
			break;
		case 3:
			exit(1);
		case 4:
			Trace(trace);
			break;
		}
	}
}

void init() {


	int w;

	A_sector = 13000;
	R_sector = 1280;
	sector = 14280;

	for (int i = 0; i < sector; i++) {

		psn[i] = sector-i;
		lsn[i] = i;

	}

	for (int k = 0; k < 1280; k++) {
		A_NAND[k].data[0] = "  ";
	}
	for (int q = 0; q < 13000; q++) {
		A_DATA[q].data[0] = "  ";
	}
	printf("�ʱ� ���� �Ϸ�\n");
	printf("\n�޸��� ũ��� �� 6.5BM �Դϴ�. %d���� ��ȿ �����͸� �����ϴ� ����, %d���� ��ü ���͸� �����ϴ�. \n\n", A_sector, R_sector);
}

void Table_print() {
	for (int i = 0; i < 12558; i++) {
		if (psn[i] != -1) {
			printf("LSN = %d , PSN = %d \n", lsn[i], psn[i]);

		}
	}
	for (int m = 0; m < A_sector; m++) {
		if ((strcmp(A_DATA[m].data, "O") == 0) || (strcmp(A_DATA[m].data, "X") == 0))
			printf("A_DATA %d ������ ��ȿ ���� %s\n", m, A_DATA[m].data);
	}
	printf("==============================================================\n");
	for (int n = 0; n < 20000; n++) {
		if ((strcmp(A_NAND[n].data, "O") == 0) || (strcmp(A_NAND[n].data, "X") == 0))
			printf("A_NAND %d ������ ��ȿ ���� %s\n", n, A_NAND[n].data);
	}

	printf("\n\n���� ���� %dȸ , ����� ���� %dȸ\n", WriteCount, EraseCount);
}

void Trace(FILE *trace) {

	int count, K, Q, Y = 0;
	int spar;
	char check1[2] = "O";
	char check2[2] = "X";

	fopen_s(&trace, "trace.txt", "r");            //Ʈ���̽� ���� ����

	if (trace == NULL) {                           //���� ���� Ȥ�� ���⿡ ������ ��� 
		puts("�Է��� ���� ������ �� �� �����ϴ�.\n");         //�����޼��� ���
		exit(1);                                    //���α׷� ����
	}

	fseek(trace, 0, SEEK_SET);			//Ŀ���� ������ ���� ó������ �ű�

	R_block_count = 0;

	while (!feof(trace)) {				//������ ���� �ƴ� ��� ��� �ݺ�
		while (fgets(Reding, sizeof(Reding), trace)) {			//�� ���徿 �о�ͼ� �迭 Reding�� �ӽ÷� ����
			strcpy(commend, strtok(Reding, "\t"));				//Reding�� ������ �����Ͽ� �ɰ��� �պκ��� commend�� ����
			strcpy(sector_number, strtok(NULL, "\t"));			//�ɰ��� �������� sector_number�� ����

																//printf("%s%s\n\n", sector_number,commend);
			CINT3 = atoi(sector_number);						//char ���ڿ� ���¸� int������ ��ȯ ���� ��.
			printf("�Է¹��� LSN %d\t", CINT3);

			CINT3_block = CINT3 / 64;							//��� ���� ���͹�ȣ�� ����� ��ȣ�� �������� ����
			CINT3_offset = CINT3 % 64;

			for (int u = 0; u < A_sector; u++) {
				if (CINT3 == lsn[u]) {							//�Է¹��� ���� ��Ϲ�ȣ�� ��ġ�ϴ� LBN�� ã��
					if ((strcmp(A_DATA[CINT3].data, "O") != 0) && (strcmp(A_DATA[CINT3].data, "X") != 0)) {		//�� ���°��� ���Ͱ� �ƹ��� ���� �������� �ʴٸ�
						printf("%d�� ��� ������ %d���� ����Ǿ����ϴ�. \n\n", CINT3_block, CINT3_offset);
						strcpy(A_DATA[CINT3].data, "O");
						WriteCount++;

					}
					else {
						//printf("\n\n%s\n\n", A_DATA[CINT3].data);
						strcpy(A_DATA[CINT3].data, "X");
						if (CINT3_block < R_block_count) {

						}
						else {
							printf("�ű� ��ü ��� �ʿ�\n");
							R_block_count++;
						}
						for (int i = CINT3_block; i <= R_block_count; i++) {
							K = (i * 64) + (CINT3_offset);
							//printf("%d\t %d\t %d\n", K, R_block_count, CINT3_block);
							if ((strcmp(A_NAND[K].data, "O") != 0) && (strcmp(A_NAND[K].data, "X") != 0)) {
								strcpy(A_NAND[K].data, "O");
								printf("��ü ���%d�� %d���Ϳ� ���� �Ϸ�\n\n", i, CINT3_offset);
								WriteCount++;
								break;
							}
							if (i == R_block_count) {
								printf("�Ҵ�� ��ü ��Ͽ��� �̹� �����Ͱ� ������. �ű� ��ü ��� �ʿ�\n");
								R_block_count++;
								strcpy(A_NAND[K + 64].data, "O");
								printf("��ü ���%d�� %d���Ϳ� ���� �Ϸ�\n\n", i + 1, CINT3_offset);
								WriteCount++;
								break;
							}
						}

					}
				}

				//if (R_block_count > 18) margin();
			}
		}
	}
}

void margin() {

	int Y = 0;

	printf("\n\n================��ü ��� ���� �ʰ�. ���� �۾� �ʿ�================\n\n");

	while (Y <= R_block_count) {
		for (int Q = 0; Q < 64; Q++) {
			for (int T = Q; T <= 13000; T + 64) {
				if (strcmp(A_DATA[T].data, "O") == 0) {
					strcpy(C_DATA[T].data, A_DATA[T].data);
					strcpy(A_DATA[T].data, "  ");
					WriteCount++;
					break;
				}
			}
			for (int Z = Q; Z <= 1280; Z + 64) {
				if (strcmp(A_NAND[Z].data, "O") == 0) {
					strcpy(C_DATA[Z].data, A_NAND[Z].data);
					strcpy(A_NAND[Z].data, "  ");
					WriteCount++;
					break;
				}
			}

		}
		for (int w = 0; w < 64; w++) {
			int E = (Y * 64) + w;
			strcpy(A_DATA[E].data,C_DATA[w].data);
			Y++;
			WriteCount++;
		}
		EraseCount++;
	}

	R_block_count = 0;
}