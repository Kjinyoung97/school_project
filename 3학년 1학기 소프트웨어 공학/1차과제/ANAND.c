#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable : 4996)
int KB, Byte, A_sector,sector, R_sector, sector, R_block_count;
//A_sector = 유효 데이터(처음 들어오는 데이터)를 저장하는 기본적인 저장섹터, R_sector = 대체 블록의 섹터 수 , A_block = A_sector의 블록수 , R_block = 대체 블록의 수 

int CINT3,CINT3_block,CINT3_offset;



int WriteCount = 0;
int EraseCount = 0;

typedef struct ANAND {
	char data[20];		//데이터의 유효 여부를 작성
	char spae[2];			//데이터의 여분 영역을 나타냄
}ANAND;					//데이터 영역 + 여분 영역 이렇게 해서 하나의 섹터를 나타내는 구조체


ANAND A_DATA[13000];		//유효 데이터 섹터 9135개 약 142개의 블록
ANAND A_NAND[20000];			//대체 데이터 섹터 865개 약 13개의 블록
ANAND C_DATA[64];			//데이터 백업용

char commend[2];		//쪼개서 임시로 W를 저장할 문자열
char sector_number[6];	//쪼개서 섹터 번호를 임시로 저장할 문자열

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
		printf("원하는 메뉴 선택\t1. 초기 설정 \t2. 매핑 테이블 출력\t3. 종료  \t4. trace\n\n");
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
	printf("초기 설정 완료\n");
	printf("\n메모리의 크기는 약 6.5BM 입니다. %d개의 유효 데이터를 저장하는 섹터, %d개의 대체 섹터를 가집니다. \n\n", A_sector, R_sector);
}

void Table_print() {
	for (int i = 0; i < 12558; i++) {
		if (psn[i] != -1) {
			printf("LSN = %d , PSN = %d \n", lsn[i], psn[i]);

		}
	}
	for (int m = 0; m < A_sector; m++) {
		if ((strcmp(A_DATA[m].data, "O") == 0) || (strcmp(A_DATA[m].data, "X") == 0))
			printf("A_DATA %d 데이터 유효 여부 %s\n", m, A_DATA[m].data);
	}
	printf("==============================================================\n");
	for (int n = 0; n < 20000; n++) {
		if ((strcmp(A_NAND[n].data, "O") == 0) || (strcmp(A_NAND[n].data, "X") == 0))
			printf("A_NAND %d 데이터 유효 여부 %s\n", n, A_NAND[n].data);
	}

	printf("\n\n쓰기 연산 %d회 , 지우기 연산 %d회\n", WriteCount, EraseCount);
}

void Trace(FILE *trace) {

	int count, K, Q, Y = 0;
	int spar;
	char check1[2] = "O";
	char check2[2] = "X";

	fopen_s(&trace, "trace.txt", "r");            //트레이스 파일 오픈

	if (trace == NULL) {                           //파일 생성 혹은 열기에 실패한 경우 
		puts("입력을 위한 파일을 열 수 없습니다.\n");         //에러메세지 출력
		exit(1);                                    //프로그램 종료
	}

	fseek(trace, 0, SEEK_SET);			//커서를 파일의 제일 처음으로 옮김

	R_block_count = 0;

	while (!feof(trace)) {				//파일의 끝이 아닐 경우 계속 반복
		while (fgets(Reding, sizeof(Reding), trace)) {			//한 문장씩 읽어와서 배열 Reding에 임시로 저장
			strcpy(commend, strtok(Reding, "\t"));				//Reding을 탭으로 구분하여 쪼개서 앞부분을 commend에 저장
			strcpy(sector_number, strtok(NULL, "\t"));			//쪼개진 나머지를 sector_number에 저장

																//printf("%s%s\n\n", sector_number,commend);
			CINT3 = atoi(sector_number);						//char 문자열 상태를 int형으로 변환 시켜 줌.
			printf("입력받은 LSN %d\t", CINT3);

			CINT3_block = CINT3 / 64;							//명령 받은 섹터번호로 블록의 번호와 오프셋을 구함
			CINT3_offset = CINT3 % 64;

			for (int u = 0; u < A_sector; u++) {
				if (CINT3 == lsn[u]) {							//입력받은 값의 블록번호와 일치하는 LBN을 찾고
					if ((strcmp(A_DATA[CINT3].data, "O") != 0) && (strcmp(A_DATA[CINT3].data, "X") != 0)) {		//그 들어온값의 섹터가 아무런 값도 적혀있지 않다면
						printf("%d번 블록 오프셋 %d번에 저장되었습니다. \n\n", CINT3_block, CINT3_offset);
						strcpy(A_DATA[CINT3].data, "O");
						WriteCount++;

					}
					else {
						//printf("\n\n%s\n\n", A_DATA[CINT3].data);
						strcpy(A_DATA[CINT3].data, "X");
						if (CINT3_block < R_block_count) {

						}
						else {
							printf("신규 대체 블록 필요\n");
							R_block_count++;
						}
						for (int i = CINT3_block; i <= R_block_count; i++) {
							K = (i * 64) + (CINT3_offset);
							//printf("%d\t %d\t %d\n", K, R_block_count, CINT3_block);
							if ((strcmp(A_NAND[K].data, "O") != 0) && (strcmp(A_NAND[K].data, "X") != 0)) {
								strcpy(A_NAND[K].data, "O");
								printf("대체 블록%d번 %d섹터에 저장 완료\n\n", i, CINT3_offset);
								WriteCount++;
								break;
							}
							if (i == R_block_count) {
								printf("할당된 대체 블록에도 이미 데이터가 존재함. 신규 대체 블록 필요\n");
								R_block_count++;
								strcpy(A_NAND[K + 64].data, "O");
								printf("대체 블록%d번 %d섹터에 저장 완료\n\n", i + 1, CINT3_offset);
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

	printf("\n\n================대체 블록 갯수 초과. 병합 작업 필요================\n\n");

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