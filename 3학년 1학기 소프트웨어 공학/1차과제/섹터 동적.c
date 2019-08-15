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

struct MEMORY MEMORY2[128];            //데이터 백업용
struct MEMORY MEMORY[20000];



void init(struct MEMORY *MEMORY, int *lsn, int *psn);
void Table_print(struct MEMORY *MEMORY, int *lsn, int *psn);
void Trace(FILE *trace);


void main(FILE *trace) {
	int k;

	while (1) {
		printf("원하는 메뉴 선택\t1. 초기 설정 \t2. 매핑 테이블 출력\t3. trace  \t4. 종료\n\n");
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

		j = i / 128;         //몫
		offset = i % 128;      //나머지



			MEMORY[i].data[0] = "  ";

			psn[i] = -1;
			lsn[i] = i;

		printf("\n\nMEMORY[%d]는 %d번째 블록\n", i, j);


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
			printf("PSN %d 데이터 유효 여부 %s\n", psn[m], MEMORY[m].data);
	}

	printf("\n\n쓰기 연산 %d회 , 지우기 연산 %d회\n", WriteCount, EraseCount);
}

void Trace(FILE *trace) {

	int count;

	int block2;
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

			for (int u = 0; u < sector2; u++) {

				if (CINT3 == lsn[u]) {
					if ((strcmp(MEMORY[u].data,check1) == 0) || (strcmp(MEMORY[u].data, check2) == 0)) {
						printf("이미 저장된 데이터가 있음. 여분 블록에 저장. 기존 위치는 비유효 처리\t");
						strcpy(MEMORY[u].data, "X");
						
						for (int k = 0; k < sector; k++) {
							if ((strcmp(MEMORY[k].data, check1) ==1 ) || (strcmp(MEMORY[k].data, check2) ==1)) {
								printf("여분 섹터 PSN %d에 저장하였음.\n",k);
								strcpy(MEMORY[k].data, "O");
								WriteCount++;
								psn[k] = psn_sector;
								psn_sector++;
								
								break;
							}
							if (k == sector - 1) {
								printf("여분 블록이 없음. 병합작업 수행.\n\n");
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
					printf("트레이스 파일에서 접근 명령이 떨어진 %d을 LSN %d와 매핑된 PSN %d에 저장하였음. \n", CINT3, lsn[u],psn[u]);
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