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

struct MEMORY MEMORY2[128];            //데이터 백업용
struct MEMORY MEMORY[20000];
struct LBN LBN[158];
struct PBN PBN[158];



void init(struct MEMORY *MEMORY, struct LBN *LBN, struct PBN *PBN);
void Table_print(struct MEMORY *MEMORY, struct LBN *LBN, struct PBN *PBN);
void Trace(FILE *trace);


void main(FILE *trace) {
	int k;

	while (1) {
		printf("원하는 메뉴 선택\t1. 초기 설정 \t2. 매핑 테이블 출력\t3. trace  \t4. 종료\n\n");
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

	printf("설정할메모리의 크기를 입력하세요. (KB단위, 최대 9900KB )\n");
	scanf("%d", &KB);

	if ((KB > 10000) || (KB<1)) {
		printf("에러.1KB와 9900KB사이로 입력하세요\n\n");
		exit(1);
	}


	KB = KB + 64;            //숨겨진 여분 블록의 크기만큼 추가적으로 계산
	Byte = KB * 1024;
	sector = Byte / 512;
	block = sector / 128;
	if (sector % 128 != 0) block = block + 1;
	sector2 = sector - 128;         //사용자가 매핑테이블에서 사용할 수 있는 섹터는 여분블록을 제외한 섹터 

	printf("\n입력된 메모리의 크기는 %dB 입니다. %d개의 섹터, %d개의 블록, 추가적인 1개의 여분블록이 생성되었습니다. \n\n", Byte, sector, block);



	for (int i = 0; i < sector; i++) {

		block = i / 128;         //몫
		offset = i % 128;      //나머지

		MEMORY[i].data[0] = "  ";
		printf("\nMEMORY[%d]는 %d번째 블록\n", i, block);
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
			printf("%d 번 블록 %d번 오프셋의 데이터 유효 여부 %s\n", w / 128, w % 128, MEMORY[w].data);
		}
	}
	if ((strcmp(MEMORY2[count].data, "0") == 0) || (strcmp(MEMORY2[count].data, "X") == 0)) {
		printf("여분블록 155번 블록 %d번 오프셋의 데이터 유효 여부 %s\n", count, MEMORY2[count].data);
	}

	//for (int e = 0; e < sector; e++) printf("%s", MEMORY[e].data);
	printf("\n\n쓰기 연산 %d회 , 지우기 연산 %d회\n", WriteCount, EraseCount);
}

void Trace(FILE *trace) {

	int count;
	int spar;
	char check1[2] = "O";
	char check2[2] = "X";

	fopen_s(&trace, "trace.txt", "r");            //사용자이진파일 오픈. 만약 파일이 없을경우 신규 생성

	if (trace == NULL) {                           //파일 생성 혹은 열기에 실패한 경우 
		puts("입력을 위한 파일을 열 수 없습니다.\n");         //에러메세지 출력
		exit(1);                                    //프로그램 종료
	}

	fseek(trace, 0, SEEK_SET);

	while (!feof(trace)) {
		while (fgets(Reding, sizeof(Reding), trace)) {
			strcpy(commend, strtok(Reding, "\t"));
			strcpy(sector_number, strtok(NULL, "\t"));

			//printf("%s%s\n\n", sector_number,commend);
			CINT3 = atoi(sector_number);
			printf("입력받은 LSN %d\t", CINT3);

			CINT3_block = CINT3 / 128;
			CINT3_offset = CINT3 % 128;

			for (int u = 0; u < block; u++) {
				if (CINT3_block == LBN[u].lbn) {						//입력받은 값의 블록번호와 일치하는 LBN을 찾고
					if ((strcmp(MEMORY[CINT3].data, "O") != 0) && (strcmp(MEMORY[CINT3].data, "X") != 0)) {		//그 들어온값의 섹터가 아무런 값도 적혀있지 않다면
						printf("%d번 블록 오프셋 %d번에 저장되었습니다. \n\n", CINT3_block, PBN[u].pbn_offset[CINT3_offset]);
						strcpy(MEMORY[CINT3].data, "O");
						WriteCount++;
						PBN[CINT3_block].pbn = PBN_block;
						PBN_block++;
					}
					else {
						printf("이미 저장된 값이 있어 저장하지 못했습니다. 여분 블록에 저장합니다.\n");
						if ((strcmp(MEMORY[19840 + CINT3_offset].data, "O") != 0) && (strcmp(MEMORY[19840 + CINT3_offset].data, "X") != 0)) {
							(strcpy(MEMORY[19840 + CINT3_offset].data, "O") == 0);
							WriteCount++;
							printf("여유블록 155번 블록 오프셋 %d번에 저장되었습니다", CINT3_offset);
							strcpy(MEMORY[CINT3].data, "X");
							PBN[155].pbn = PBN_block;
							PBN_block++;
						}
						else {
							printf("여분블록의 알맞는 오프셋에 이미 데이터가 저장되어있습니다. 병합작업을 수행합니다.\n\n");
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
							printf("%d번 블록 오프셋 %d번에 저장되었습니다.\n\n", CINT3_block, PBN[u].pbn_offset[CINT3_offset]);
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