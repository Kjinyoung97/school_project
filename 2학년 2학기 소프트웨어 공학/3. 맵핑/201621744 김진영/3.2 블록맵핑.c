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

	printf("메모리는 몇MB 입니까? (2MB단위)\n");
	scanf("%d", &size);

	Secter = (size * 1024) / 512;
	block = (Secter / 32) + 2;
	Secter2 = block * 32;

	printf("섹터의 갯수 %d\n", Secter);
	printf("생성된 블럭의 갯수 %d (여분 블록 한개 포함) \n", block);

	lsn = (LSN *)malloc(sizeof(LSN)*block);
	psn = (LSN *)malloc(sizeof(LSN)*block);
	memory = (MEMORY *)malloc(sizeof(MEMORY)*Secter2);
	blo = (BLOCK *)malloc(sizeof(BLOCK)*block);

	for (i = 0; i < block; i++) {
		lsn[i].data = 0 + i;
		psn[i].data = (block - 1)-i;
		psn[i].link = NULL;

	for (q = 0; q <= Secter2; q++) {
			w = q / 32;		//몇번지의 블록인지
			j = q % 32;		//w블록의 몇번째 섹터인지
			strcpy(blo[w].MEmory[j].data, A);	//블럭 초기화
		lsn[i].link = psn[i].data;
		}
	}
}

void Print_table() {		//매핑테이블을 출력하는 함수
	int i;
	for (i = 0; i < block-1; i++) {
		printf("lbn의 값 %d\t pbn의 값%d\t\n", lsn[i].data, lsn[i].link);
	}
}

void FTL_read() {
	Flash_read();
}

void Flash_read() {
	int q, j, w, count = 0;

	for (q = 0; q < Secter2; q++) {
			w = q / 32;		//몇번지의 블록인지
			j = q % 32;		//w블록의 몇번째 섹터인지
			if (strcmp(blo[w].MEmory[j].data, A) != 0) {
				count++;
				printf("저장된 문자열 : %s\n", blo[w].MEmory[j].data);
				printf("%d번째 블럭(=psb값) %d섹터에 저장되어있음\n.",w,j);
			}

	}
	if (count == 0)
		printf("\n저장된 데이터가 없습니다.\n");
}

void Flash_write() {

	int k,Q,j,R,b;
	char save[20];

	printf("저장할 위치를 입력하시오.");
	scanf("%d", &k);

	if ((k < 0) || (k >= Secter)) {
		printf("\n\n유효한 위치가 아닙니다. 프로그램 종료.");
		exit(1);
	}

	printf("저장할 문자열을 입력하시오.");
	scanf("%s", &save);

	b = k / 32;
	j = k % 32;
	Q = lsn[b].link;
	R = lsn[block-1].link;

	if (strcmp(blo[Q].MEmory[j].data, A) != 0) {
		printf("이미 저장되어있는 데이터가 있습니다. 여분 블록에 저장합니다.\n");
		Flash_erase(save, k);
			
		}
		else {
			strcpy(blo[Q].MEmory[j].data, save);
			printf("lbn %d와 오프셋 %d를 가지고 %d 번 블록 %d번 섹터에 저장되었음.\n", b, j, Q, j);
			Write++;
		}
	}

void Flash_erase(char save[],int k) {

	int b,R,Q, w, j, u, z;

	b = k / 32;
	j = k % 32;
	Q = lsn[b].link;					//기존 물리적 위치
	R = lsn[block - 1].link;			//여분 물리적 위치

	if ((k < 0) || (k >= Secter)) {
		printf("\n\n유효한 위치가 아닙니다. 프로그램 종료.");
		exit(1);
	}

		printf("\n해당 위치를 제외한 소속 블럭을 백업합니다.\n");

		printf("\n중복된 섹터만을 제외하고 블럭을 여분 블록에 복사. 기존 블록 전부 삭제처리.\n\n");
		for (u = 0; u < 32; u++) {
			if (u != j) {
				if (strcmp(blo[Q].MEmory[u].data, A) != 0) {
					strcpy(blo[R].MEmory[u].data, blo[Q].MEmory[u].data);
					printf("%d 번 블럭 %d 번째 섹터를 %d번 블럭 %d 번째 섹터에 복사 \n",Q, u, R, u);
					Write++;
				}
			}
			else if (j == u) {
				strcpy(blo[R].MEmory[u].data, save);		//여분 블록의 중복된 섹터의 자리에는 새로운 문자열 저장
				printf("중복된 위치 변경 및 저장완료\n");
				Write++;
			}
			if (strcmp(blo[Q].MEmory[u].data, A) != 0) {
				strcpy(blo[Q].MEmory[u].data, A);		//기존블록 삭제처리
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
		printf("실행할 기능을 선택하세요.\t1.저장되어있는 데이터 출력\t2.데이터 쓰기\t3.매핑 테이블 출력\t4.프로그램종료\n");
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
			printf("\n쓰기연산 %d번, 삭제연산 %d번\n", Write, Erase);
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
					free(blo[0].MEmory[j].data);	//블럭 초기화
					free(blo[block].MEmory[j].data);		//여분블럭 초기화
					free(blo[block - 1].MEmory[j].data);
				}
				free(lsn[o].link);
			}
			exit(1);
			break;

		default:
			printf("잘못된 값이 입력되었습니다. 다시 입력하십시오.");
			break;
		}
	}
}