#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable : 4996)
int KB, Byte, A_sector, block, A_block, R_block, offset, sector, R_sector,sector,R_block_count;
//A_sector = 유효 데이터(처음 들어오는 데이터)를 저장하는 기본적인 저장섹터, R_sector = 대체 블록의 섹터 수 , A_block = A_sector의 블록수 , R_block = 대체 블록의 수 

int CINT3_block,CINT3_offset,CINT3;

int WriteCount = 0;
int EraseCount = 0;

typedef struct LBN {
	int lbn;
	int lbn_offset[64];
};

typedef struct PBN {
	int pbn;
	int pbn_offset[64];
};


typedef struct ANAND {
	char data[20];		//데이터의 유효 여부를 작성
	char spae;			//데이터의 여분 영역을 나타냄
}ANAND;					//데이터 영역 + 여분 영역 이렇게 해서 하나의 섹터를 나타내는 구조체


ANAND A_DATA[13000];		//유효 데이터 섹터 9135개 약 142개의 블록
ANAND A_NAND[1280];		//대체 데이터 섹터 865개 약 13개의 블록
ANAND C_DATA[64];

char commend[2];		//쪼개서 임시로 W를 저장할 문자열
char sector_number[6];	//쪼개서 섹터 번호를 임시로 저장할 문자열

char Reding[10];

struct LBN LBN[250];
struct PBN PBN[250];



void init(ANAND *A_DATA, struct LBN *LBN,struct PBN *PBN, ANAND *A_NAND);
void Table_print(ANAND *A_DATA, struct LBN *LBN, struct PBN *PBN, ANAND *A_NAND);
void Trace(FILE *trace);


void main(FILE *trace) {
	int k;

	while (1) {
		printf("원하는 메뉴 선택\t1. 초기 설정 \t2. 매핑 테이블 출력\t3. trace  \t4. 종료\n\n");
		scanf("%d", &k);

		switch (k) {
		case 1:
			init(A_DATA, LBN, PBN,A_NAND);
			break;
		case 2:
			Table_print(A_DATA, LBN, PBN,A_NAND);
			break;
		case 3:
			Trace(trace);
			break;
		case 4:
			exit(1);
			
		}
		
	}
	
}

void init(ANAND *A_DATA, struct LBN *LBN, struct PBN *PBN, ANAND *A_NAND) {

	int w;

	KB = 9135;
	Byte = KB * 1024;
	A_sector = 13000;
	R_sector = 1280;
	sector = 14280;

	A_block = A_sector / 64;
	R_block = R_sector / 64;

	for (int i = 0; i < A_sector; i++) {

		A_DATA[i].data[0] = "  ";		//i번쨰 섹터의 데이터를 공백으로 초기화
		//printf("\nA_DATA[%d]는 %d번째 블록\n", i, block);
		//printf("%s", MEMORY[i].data);
	}
	for (int z = 0; z < sector; z++) {

		block = z / 64;         //몫  = 블록 번호
		offset = z % 64;      //나머지 = 오프셋
	}

	for (w = 0; w <= block; w++) {
		PBN[w].pbn = block - w;
		LBN[w].lbn = w;


		for (int q = 0; q < 64; q++) {
			LBN[w].lbn_offset[q] = q;
			PBN[w].pbn_offset[q] = q;
		}

	}
	printf("초기 설정 완료\n");
	printf("\n메모리의 크기는 약 6.5BM 입니다. %d개의 유효 데이터를 저장하는 섹터, %d개의 블록, %d개의 대체 블록을 가집니다. \n\n", A_sector, block, R_block);
}

void Table_print(ANAND *A_DATA, struct LBN *LBN, struct PBN *PBN,ANAND *A_NAND) {
	int i,count = 0;
	for (i = 0; i <= block; i++) {
		for (int k = 0; k < 64; k++) {
			printf("lbn = %d , pbn = %d , lbn offset = %d, pbn offset = %d \n", LBN[i].lbn, PBN[i].pbn, LBN[i].lbn_offset[k], PBN[i].pbn_offset[k]);
		}
	}
	for (int w = 0; w < sector; w++) {
		if ((strcmp(A_DATA[w].data, "O") == 0) || (strcmp(A_DATA[w].data, "X") == 0)) {
			printf("%d 번 블록 %d번 오프셋의 데이터 유효 여부 %s\n", w / 128, w % 128, A_DATA[w].data);
		}
	}
	if ((strcmp(A_NAND[count].data, "0") == 0) || (strcmp(A_NAND[count].data, "X") == 0)) {
		printf("여분블록 155번 블록 %d번 오프셋의 데이터 유효 여부 %s\n", count, A_NAND[count].data);
	}

	//for (int e = 0; e < sector; e++) printf("%s", MEMORY[e].data);
	printf("\n\n쓰기 연산 %d회 , 지우기 연산 %d회\n", WriteCount, EraseCount);
}


void Trace(FILE *trace) {

	int count,K,Y=0;
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

			for (int u = 0; u < block; u++) {
				if (CINT3_block == LBN[u].lbn) {						//입력받은 값의 블록번호와 일치하는 LBN을 찾고
					if ((strcmp(A_DATA[CINT3].data, "O") != 0) && (strcmp(A_DATA[CINT3].data,"X") != 0)) {		//그 들어온값의 섹터가 아무런 값도 적혀있지 않다면
						printf("%d번 블록 오프셋 %d번에 저장되었습니다. \n\n", CINT3_block, PBN[u].pbn_offset[CINT3_offset]);
						strcpy(A_DATA[CINT3].data, "O");
						strcpy(A_DATA[CINT3].spae, CINT3_offset);
						WriteCount++;
						
					}
					else {
						printf("\n\n%s\n\n", A_DATA[CINT3].data);
						strcpy(A_DATA[CINT3].data, "X");
						if (CINT3_block < R_block_count) {
					
						}
						else {
							printf("신규 대체 블록 필요 \n");
							R_block_count++;
						}
						for (int i = CINT3_block; i <= R_block_count; i++) {
							K = (i * 64) + (CINT3_offset);
							printf("%d\t %d\t %d\n", K, R_block_count, CINT3_block);
							if ((strcmp(A_NAND[K].data, "O") != 0) && (strcmp(A_NAND[K].data,"X") != 0)) {
								strcpy(A_NAND[K].data, "O");
								strcpy(A_NAND[K].spae, CINT3_offset);
								printf("대체 블록%d번 %d섹터에 저장 완료\n\n", i, CINT3_offset);
								WriteCount++;
								break;
							}
							if (i == R_block_count) {
								printf("할당된 대체 블록에도 이미 데이터가 존재함. 신규 대체 블록 필요\n");
								R_block_count++;
								strcpy(A_NAND[K+64].data, "O");
								strcpy(A_NAND[K+64].spae, CINT3);
								printf("대체 블록%d번 %d섹터에 저장 완료\n\n", i+1, CINT3_offset);
								WriteCount++;
								break;
							}
						}
					
					}
				}			
				if (R_block_count > 18) {
				printf("\n\n================대체 블록 갯수 초과. 병합 작업 필요================\n\n");
				while (Y < 64) {
					for (int T = 0; T <= 13000; T++) {
						if (strcmp(A_DATA[T].data, "O") == 0) {
							strcpy(C_DATA[Y].data, A_DATA[T].data);
							Y++;
						}
					}
					for (int Z = 0; Z <= 1280; Z++) {
						if (strcmp(A_NAND[Z].data, "O") == 0) {
							strcpy(C_DATA[Y].data, A_DATA[Z].data);
							Y++;
						}
					}
				}
				for(int X=0;X )
				
				}
			}
		}
	}
		
	fclose(trace);
}