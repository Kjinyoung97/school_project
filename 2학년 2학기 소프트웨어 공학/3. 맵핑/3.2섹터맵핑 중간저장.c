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

	printf("메모리는 몇MB 입니까? (2MB단위)\n");
	scanf("%d", &size);

	Secter = (size * 1024) / 512;
	block = (Secter / 32) + 3;
	Secter2 = block * 32;

	printf("섹터의 갯수 %d\n", Secter);
	printf("생성된 블럭의 갯수 %d (여분 블록 두개 포함, 0번블록 = 삭제를 위한 블록, 1번블록 = 여분블록) \n", block);

	lsn = (LSN *)malloc(sizeof(LSN)*Secter2);
	psn = (LSN *)malloc(sizeof(LSN)*Secter2);
	memory = (MEMORY *)malloc(sizeof(MEMORY)*Secter2);
	blo = (BLOCK *)malloc(sizeof(BLOCK)*block);

	for (i = 0; i <= Secter2; i++) {
		lsn[i].data = 0 + i;
		psn[i].data = (Secter2 - 1) - i;

		if (i >= 32) {
			w = i / 32;		//몇번지의 블록인지
			j = i % 32;		//w블록의 몇번째 섹터인지
			strcpy(blo[w].MEmory[j].data, A);	//블럭 초기화

		}
		else {
			j = i % 32;
			strcpy(blo[block].MEmory[j].data, A);	//블럭 초기화
			strcpy(blo[0].MEmory[i].data, A);		//여분블럭 초기화
			strcpy(blo[1].MEmory[i].data, A);
		}

		lsn[i].link = psn[i].data;
	}
}

void Print_table() {		//매핑테이블을 출력하는 함수
	int i;
	for (i = 0; i < Secter; i++) {
		printf("lsn의 값 %d\t psn의 값%d\t\n", lsn[i].data, psn[i].data);
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
			w = q / 32;		//몇번지의 블록인지
			j = q % 32;		//w블록의 몇번째 섹터인지
			if (strcmp(blo[w+1].MEmory[j].data, A) != 0) {
				count++;
				printf("저장된 문자열 : %s\n", blo[w+1].MEmory[j].data);
				printf("lsn %d번과 연결된 psn %d 번, %d 번 블럭 %d 번째 섹터에 저장되어있습니다.\n", lsn[q].link, q, w+1, j);
			}
		}
		else if (block == 3) {
			w = q / 32;
			j = q % 32;
			if (strcmp(blo[w+1].MEmory[j].data, A) != 0) {
				count++;
				printf("저장된 문자열 : %s\n", blo[w+1].MEmory[j].data);
				printf("lsn %d번과 연결된 psn %d 번, %d 번 블럭 %d 번째 섹터에 저장되어있습니다.\n", lsn[q].link, q,w+1, j);
			}
		}
	}
	if (count == 0)
		printf("\n저장된 데이터가 없습니다.\n");
}

void Flash_write() {

	int k, Q, w, j,i,count;
	char save[20];

	printf("저장할 위치(lsn 위치)를 입력하시오.");
	scanf("%d", &k);

	if ((k < 0) || (k >= Secter)) {
		printf("\n\n유효한 위치가 아닙니다. 프로그램 종료.");
		exit(1);
	}

	printf("저장할 문자열을 입력하시오.");
	scanf("%s", &save);

	Q = lsn[k].link;

	if (block > 3) {
		w = Q / 32;		//몇번지의 블록인지
		j = Q % 32;		//w블록의 몇번째 섹터인지
		if (strcmp(blo[w+2].MEmory[j].data, A) != 0) {
			printf("이미 저장되어있는 데이터가 있습니다. 여분 블록에 저장합니다.\n");
			for (i = 0; i < 32; i++) {
				if (strcmp(blo[1].MEmory[i].data, A) == 0) {
					strcpy(blo[1].MEmory[i].data, save);
					printf("저장완료.\n\n\n");
					psn[k].data = 32 + i;
					break;
					}
			}
			if (i == 32) {
				printf("모든 여분공간이 꽉 찼습니다. 여분공간을 비워야 합니다.\n\n");
				Flash_erase(k);
			}
		}
		else {
			strcpy(blo[w+2].MEmory[j].data, save);
			printf("lsn %d번과 연결된 psn %d 번, %d 번 블럭 %d 번째 섹터에 저장되었습니다.\n", k, Q, w+2, j);
		}
	}
	else if(block == 3) {
		j = Q % 32;
		if (strcmp(blo[block].MEmory[j].data, A) != 0) {
			printf("이미 저장되어있는 데이터가 있습니다. 여분 블록에 저장합니다.\n");
			for (i = 0; i < 32; i++) {
				if (strcmp(blo[1].MEmory[i].data, A) == 0) {
					strcpy(blo[1].MEmory[i].data, save);
					printf("저장완료.\n\n\n");
					psn[k].data = 32 + i;
					break;
				}
			}
			if (i == 32) {
				printf("모든 여분공간이 꽉 찼습니다. 여분공간을 비워야 합니다.\n\n");
				Flash_erase(k);
			}
		}
		else {
			strcpy(blo[block].MEmory[j].data, save);
			printf("lsn %d번과 연결된 psn %d 번, %d번 블럭 %d 번째 섹터에 저장되었습니다.\n", k, Q,block, j);
		}
	}
}

void Flash_erase(int k) {

	int Q, w, j, u, z;

	if ((k < 0) || (k >= Secter)) {
		printf("\n\n유효한 위치가 아닙니다. 프로그램 종료.");
		exit(1);
	}

	Q = lsn[k].link;

	if (Q >= 32) {
		w = Q / 32;		//몇번지의 블록인지
		j = Q % 32;		//w블록의 몇번째 섹터인지

		if (strcmp(blo[w+2].MEmory[j].data, A) == 0) {
			printf("\n\n이미 데이터가 비어있는 위치입니다. 프로그램을 종료합니다.\n");
			exit(1);
		}

		printf("\n해당 위치를 제외한 소속 블럭을 백업합니다.\n");

		printf("\n삭제할 섹터만을 제외하고 블럭을 여분 블록에 복사. 기존 블록 전부 삭제처리.\n\n");
		for (u = 0; u < 32; u++) {
			if (u != j) {
				strcpy(blo[0].MEmory[u].data, blo[w+2].MEmory[u].data);
				strcpy(blo[w+2].MEmory[u].data, A);
				printf("%d 번 블럭 %d 번째 섹터를 0번 블럭 %d 번째 섹터에 복사 \n", w, u,  u);
			}
		}

		printf("\n삭제할 위치를 제외하고 여분 블록에 있는 데이터들을 기존의 블럭 위치로 복사\n\n");
		for (z = 0; z < 32; z++) {
			strcpy(blo[w+2].MEmory[z].data, blo[0].MEmory[z].data);
			printf("%d 블럭 %d 번째 섹터를 0번 블럭 %d 번째 섹터에 복사 \n", w+2, z, z);

			if (z == 0) printf("\n 여분 블록의 복사하고 남은 데이터 삭제\n");

			printf("0번 블록 %d 번째 섹터 삭제 중\n\n", z);
			strcpy(blo[0].MEmory[z].data, A);

			if (z == j) {
				printf("\n\n삭제완료 \n\n");
				break;
			}
		}
		printf("\nlsn %d번과 연결된 psn %d 번, %d 번 블럭 %d 번째 섹터가 삭제처리되었습니다.\n", k, Q, w+2, j);
	}
	else {
		j = Q % 31;

		if (strcmp(blo[block].MEmory[j].data, A) == 0) {
			printf("\n\n이미 데이터가 비어있는 위치입니다. 프로그램을 종료합니다.\n");
			exit(1);
		}

		printf("\n삭제할 위치를 제외한 블럭들을 여분 블록에 복사\n\n");


		printf("\n해당 위치를 제외한 소속 블럭을 백업합니다.\n");

		for (u = 0; u < 32; u++) {
			if (u != j) {
				strcpy(blo[0].MEmory[u].data, blo[block].MEmory[u].data);
				strcpy(blo[block].MEmory[u].data, A);
				printf("%d 번 블럭 %d 번째 섹터를 0번 블럭 %d 번째 섹터에 복사 \n", block,u,u);
			}
		}

		printf("\n여분 블록에 있는 데이터들을 기존의 블럭 위치로 복사\n\n");
		for (z = 0; z < 32; z++) {

			if (z == 0) printf("\n 여분 블록의 복사하고 남은 데이터 삭제\n");

			strcpy(blo[block].MEmory[z].data, blo[0].MEmory[z].data);
			printf("0번 블럭 %d 번째 섹터를 %d번 블럭 %d 번째 섹터에 복사, 여분블록 %d 섹터 삭제완료 \n", z, block, z);


			strcpy(blo[block].MEmory[z].data, A);

		}
		printf("lsn %d번과 연결된 psn %d 번, %d번 블럭 %d 번째 섹터가 삭제처리되었습니다.\n", k, Q,block, j);

	}

}

void FTL_write() {
	Flash_write();
}

void main() {
	int u, o,w,j;

	init();

	while (1) {
		printf("실행할 기능을 선택하세요.\t1.출력\t2.데이터 쓰기\t3.데이터 삭제\t4.프로그램종료\n");
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
					w = o / 31;		//몇번지의 블록인지
					j = o % 31;		//w블록의 몇번째 섹터인지
					free(blo[w].MEmory[j].data);	//블럭 초기화
				}
				else {
					j = o % 31;
					free(blo[0].MEmory[j].data);	//블럭 초기화
					free(blo[block].MEmory[j].data);		//여분블럭 초기화
					free(blo[block-1].MEmory[j].data);
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