#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable : 4996)
int KB, Byte, sector, block, block, offset, sector2;

int CINT3;
int CINT3_block, CINT3_offset;
int PBN_block = 0;

int WriteCount = 0;
int EraseCount = 0;



typedef struct MEMORY {
	char data[2];
};

int block_number[157];

typedef struct LBN {
	int lbn;
	int lbn_offset[128];
};

typedef struct PBN {
	int pbn;
	int pbn_offset[128];
};


char commend[2];
char sector_number[6];

char Reding[10];

struct MEMORY MEMORY2[128];            //������ �����
struct MEMORY MEMORY[20000];
struct LBN LBN[158];
struct PBN PBN[158];



void init(struct MEMORY *MEMORY, struct LBN *LBN, struct PBN *PBN);
void Table_print(struct MEMORY *MEMORY, struct LBN *LBN, struct PBN *PBN);
void Trace(FILE *trace);


void main(FILE *trace) {
	int k;

	while (1) {
		printf("���ϴ� �޴� ����\t1. �ʱ� ���� \t2. ���� ���̺� ���\t3. trace  \t4. ����\n\n");
		scanf("%d", &k);

		switch (k) {
		case 1:
			init(MEMORY, LBN, PBN);
			break;
		case 2:
			Table_print(MEMORY, LBN, PBN);
			break;
		case 3:
			Trace(trace);
			break;
		case 4:
			exit(1);
		}
	}
}

void init(struct MEMORY *MEMORY, struct LBN *LBN, struct PBN *PBN) {

	printf("�����Ҹ޸��� ũ�⸦ �Է��ϼ���. (KB����, �ִ� 9900KB )\n");
	scanf("%d", &KB);

	if ((KB > 10000) || (KB<1)) {
		printf("����.1KB�� 9900KB���̷� �Է��ϼ���\n\n");
		exit(1);
	}


	KB = KB + 64;            //������ ���� ����� ũ�⸸ŭ �߰������� ���
	Byte = KB * 1024;
	sector = Byte / 512;
	block = sector / 128;
	if (sector % 128 != 0) block = block + 1;
	sector2 = sector - 128;         //����ڰ� �������̺��� ����� �� �ִ� ���ʹ� ���к���� ������ ���� 

	printf("\n�Էµ� �޸��� ũ��� %dB �Դϴ�. %d���� ����, %d���� ���, �߰����� 1���� ���к���� �����Ǿ����ϴ�. \n\n", Byte, sector, block);



	for (int i = 0; i < sector; i++) {

		block = i / 128;         //��
		offset = i % 128;      //������

		MEMORY[i].data[0] = "  ";
		printf("\nMEMORY[%d]�� %d��° ���\n", i, block);
		//printf("%s", MEMORY[i].data);

	}
	for (int w = 0; w <= block; w++) {
		PBN[w].pbn =-1;
		LBN[w].lbn = w;

		for (int q = 0; q < 128; q++) {
			LBN[w].lbn_offset[q] = q;
			PBN[w].pbn_offset[q] = q;
		}

	}
}

void Table_print(struct MEMORY *MEMORY, struct LBN *LBN, struct PBN *PBN) {
	int count = 0;
	for (int i = 0; i <= block; i++) {
		for (int k = 0; k < 128; k++) {
			//printf("lbn = %d , pbn = %d , lbn offset = %d, pbn offset = %d \n", LBN[i].lbn, PBN[i].pbn, LBN[i].lbn_offset[k], PBN[i].pbn_offset[k]);
		}
		if(PBN[i].pbn != -1)
		printf("lbn = %d , pbn = %d\n", LBN[i].lbn, PBN[i].pbn);
	}
	for (int w = 0; w < sector; w++) {
		if ((strcmp(MEMORY[w].data, "O") == 0) || (strcmp(MEMORY[w].data, "X") == 0)) {
			printf("%d �� ��� %d�� �������� ������ ��ȿ ���� %s\n", w / 128, w % 128, MEMORY[w].data);
		}
	}
	if ((strcmp(MEMORY2[count].data, "0") == 0) || (strcmp(MEMORY2[count].data, "X") == 0)) {
		printf("���к�� 155�� ��� %d�� �������� ������ ��ȿ ���� %s\n", count, MEMORY2[count].data);
	}

	//for (int e = 0; e < sector; e++) printf("%s", MEMORY[e].data);
	printf("\n\n���� ���� %dȸ , ����� ���� %dȸ\n", WriteCount, EraseCount);
}

void Trace(FILE *trace) {

	int count;
	int spar;
	char check1[2] = "O";
	char check2[2] = "X";

	fopen_s(&trace, "trace.txt", "r");            //������������� ����. ���� ������ ������� �ű� ����

	if (trace == NULL) {                           //���� ���� Ȥ�� ���⿡ ������ ��� 
		puts("�Է��� ���� ������ �� �� �����ϴ�.\n");         //�����޼��� ���
		exit(1);                                    //���α׷� ����
	}

	fseek(trace, 0, SEEK_SET);

	while (!feof(trace)) {
		while (fgets(Reding, sizeof(Reding), trace)) {
			strcpy(commend, strtok(Reding, "\t"));
			strcpy(sector_number, strtok(NULL, "\t"));

			//printf("%s%s\n\n", sector_number,commend);
			CINT3 = atoi(sector_number);
			printf("�Է¹��� LSN %d\t", CINT3);

			CINT3_block = CINT3 / 128;
			CINT3_offset = CINT3 % 128;

			for (int u = 0; u < block; u++) {
				if (CINT3_block == LBN[u].lbn) {						//�Է¹��� ���� ��Ϲ�ȣ�� ��ġ�ϴ� LBN�� ã��
					if ((strcmp(MEMORY[CINT3].data, "O") != 0) && (strcmp(MEMORY[CINT3].data, "X") != 0)) {		//�� ���°��� ���Ͱ� �ƹ��� ���� �������� �ʴٸ�
						printf("%d�� ��� ������ %d���� ����Ǿ����ϴ�. \n\n", CINT3_block, PBN[u].pbn_offset[CINT3_offset]);
						strcpy(MEMORY[CINT3].data, "O");
						WriteCount++;
						PBN[CINT3_block].pbn = PBN_block;
						PBN_block++;
					}
					else {
						printf("�̹� ����� ���� �־� �������� ���߽��ϴ�. ���� ��Ͽ� �����մϴ�.\n");
						if ((strcmp(MEMORY[19840 + CINT3_offset].data, "O") != 0) && (strcmp(MEMORY[19840 + CINT3_offset].data, "X") != 0)) {
							(strcpy(MEMORY[19840 + CINT3_offset].data, "O") == 0);
							WriteCount++;
							printf("������� 155�� ��� ������ %d���� ����Ǿ����ϴ�", CINT3_offset);
							strcpy(MEMORY[CINT3].data, "X");
							PBN[155].pbn = PBN_block;
							PBN_block++;
						}
						else {
							printf("���к���� �˸´� �����¿� �̹� �����Ͱ� ����Ǿ��ֽ��ϴ�. �����۾��� �����մϴ�.\n\n");
							spar = 0;
							EraseCount++;
							for (int z = CINT3_block * 128; z < CINT3_block * 129; z++) {
								if (strcmp(MEMORY[z].data, "0") == 0) {
									strcpy(MEMORY2[spar].data, MEMORY[z].data);
									WriteCount++;
								}
								strcpy(MEMORY[z].data, "  ");

								if (strcmp(MEMORY2[spar].data, "O") == 0) {
									strcpy(MEMORY[z].data, MEMORY2[spar].data);
									WriteCount++;
									strcpy(MEMORY[spar].data, "  ");

									spar++;
								}
							}
							WriteCount++;
							strcpy(MEMORY[CINT3].data, "O");
							printf("%d�� ��� ������ %d���� ����Ǿ����ϴ�.\n\n", CINT3_block, PBN[u].pbn_offset[CINT3_offset]);
							PBN[CINT3_block].pbn = PBN_block;
							PBN_block++;
						}
					}
				}
			}
		}
	}

	fclose(trace);
}