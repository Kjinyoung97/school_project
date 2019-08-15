#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable : 4996)
int KB, Byte, sector, block, j, offset, sector2;

int CINT3;

int WriteCount = 0;
int EraseCount = 0;

int psn_sector = 0;

typedef struct MEMORY {
	char data[2];
};


int lsn[20000];


int psn[20000];



char commend[2];
char sector_number[6];

char Reding[10];

struct MEMORY MEMORY2[128];            //������ �����
struct MEMORY MEMORY[20000];



void init(struct MEMORY *MEMORY, int *lsn, int *psn);
void Table_print(struct MEMORY *MEMORY, int *lsn, int *psn);
void Trace(FILE *trace);


void main(FILE *trace) {
	int k;

	while (1) {
		printf("���ϴ� �޴� ����\t1. �ʱ� ���� \t2. ���� ���̺� ���\t3. trace  \t4. ����\n\n");
		scanf("%d", &k);

		switch (k) {
		case 1:
			init(MEMORY, lsn,psn);
			break;
		case 2:
			Table_print(MEMORY,lsn,psn);
			break;
		case 3:
			Trace(trace);
			break;
		case 4:
			exit(1);
		}
	}
}

void init(struct MEMORY *MEMORY, int *lsn, int *psn) {

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

		j = i / 128;         //��
		offset = i % 128;      //������



			MEMORY[i].data[0] = "  ";

			psn[i] = -1;
			lsn[i] = i;

		printf("\n\nMEMORY[%d]�� %d��° ���\n", i, j);


	}
}

void Table_print(struct MEMORY *MEMORY, int *lsn, int *psn) {
	for (int i = 0; i < 12558; i++) {
		if (psn != -1) {
			printf("LSN = %d , PSN = %d \n", lsn[i], psn[i]);
			
		}
	}
	for (int m = 0; m < sector; m++) {
		if ((strcmp(MEMORY[m].data, "O") == 0) || (strcmp(MEMORY[m].data, "X") == 0))
			printf("PSN %d ������ ��ȿ ���� %s\n", psn[m], MEMORY[m].data);
	}

	printf("\n\n���� ���� %dȸ , ����� ���� %dȸ\n", WriteCount, EraseCount);
}

void Trace(FILE *trace) {

	int count;

	int block2;
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

			for (int u = 0; u < sector2; u++) {

				if (CINT3 == lsn[u]) {
					if ((strcmp(MEMORY[u].data,check1) == 0) || (strcmp(MEMORY[u].data, check2) == 0)) {
						printf("�̹� ����� �����Ͱ� ����. ���� ��Ͽ� ����. ���� ��ġ�� ����ȿ ó��\t");
						strcpy(MEMORY[u].data, "X");
						
						for (int k = 0; k < sector; k++) {
							if ((strcmp(MEMORY[k].data, check1) ==1 ) || (strcmp(MEMORY[k].data, check2) ==1)) {
								printf("���� ���� PSN %d�� �����Ͽ���.\n",k);
								strcpy(MEMORY[k].data, "O");
								WriteCount++;
								psn[k] = psn_sector;
								psn_sector++;
								
								break;
							}
							if (k == sector - 1) {
								printf("���� ����� ����. �����۾� ����.\n\n");
								block2 = u / 128;
								count = 0;
								for (int w = block2 * 128; w < block2 * 129; w++) {
									if (strcmp(MEMORY[w].data, "O") == 0) {
										strcpy(MEMORY2[count].data, MEMORY[w].data);
										WriteCount++;
										printf("%s\n\n, MEMORY[w]);
									}
									strcpy(MEMORY[w].data,"  ");
									
									if (strcmp(MEMORY2[count].data, "O") == 0) {
										strcpy(MEMORY[w].data, MEMORY2[count].data);
										WriteCount++;
									}
									strcpy(MEMORY2[count].data, "  ");	
									count++;
								}							
								EraseCount++;
								psn[k] = psn_sector;
								psn_sector++;
								strcpy(MEMORY[u].data, "O");
								WriteCount++;
								break;
							}
						}

						break;
					}
					psn[u] = psn_sector;
					psn_sector++;
					printf("Ʈ���̽� ���Ͽ��� ���� ����� ������ %d�� LSN %d�� ���ε� PSN %d�� �����Ͽ���. \n", CINT3, lsn[u],psn[u]);
					strcpy(MEMORY[u].data, "O");
					WriteCount++;
					break;
				}
			}
			fflush(stdin);
		}

	}
	fclose(trace);
}