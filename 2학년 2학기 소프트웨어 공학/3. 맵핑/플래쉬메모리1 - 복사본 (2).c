#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LSN {
	int data;
	struct LSN *link;
}LSN;

typedef struct MEMORY{
	char data[20];
}MEMORY;

typedef struct BLOCK{
	struct MEMORY MEmory[32];
}BLOCK;

int Secter,block;

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

void init(){

	int size;
	int i,w,j;

		printf("메모리는 몇MB 입니까? (2MB단위)\n");
		scanf("%d", &size);

		Secter = (size * 1024) / 512;
		block = (Secter / 32 ) +1;

		printf("섹터의 갯수 %d\n", Secter);
		printf("생성된 블럭의 갯수 %d (여분 블록 하나 포함) \n", block+1);
	
		lsn = (LSN *)malloc(sizeof(LSN)*Secter);
		psn = (LSN *)malloc(sizeof(LSN)*Secter);
		memory = (MEMORY *)malloc(sizeof(MEMORY));
		blo = (BLOCK *)malloc(sizeof(BLOCK)*block);

		for (i = 0; i < Secter; i++) {
			lsn[i].data = 0 + i;
			psn[i].data = (Secter - 1) - i;

			if (i >=32 ){
				w = i/31;		//몇번지의 블록인지
				j = i%31;		//w블록의 몇번째 섹터인지
				strcpy(blo[w].MEmory[j].data,A);	//블럭 초기화
			}
			else {
				j = i%31;
				strcpy(blo[0].MEmory[j].data,A);	//블럭 초기화
				strcpy(blo[block].MEmory[i].data, A);		//여분블럭 초기화
			}

			lsn[i].link = psn[i].data;
		}
}

void Flash_read() {

	int q, i, j, w,count=0;
	
	for (i = 0; i < Secter; i++) {
		printf("lsn의 값 %d\t psn의 값%d\t\n", lsn[i].data, psn[i].data);
	}
	for (q = 0; q < Secter; q++) {
		if (q >= 32) {
			w = q / 31;		//몇번지의 블록인지
			j = q % 31;		//w블록의 몇번째 섹터인지
			if (strcmp(blo[w].MEmory[j].data, A) != 0) {
				count++;
				printf("저장된 문자열 : %s\n", blo[w].MEmory[j].data);
				printf("lsn %d번과 연결된 psn %d 번, %d 번 블럭 %d 번째 섹터에 저장되어있습니다.\n", lsn[q].link, q, w, j);
			}
		}
		else {
			j = q % 31;
			if (strcmp(blo[0].MEmory[j].data, A) != 0) {
				count++;
				printf("저장된 문자열 : %s\n", blo[0].MEmory[j].data);
				printf("lsn %d번과 연결된 psn %d 번, 0 번 블럭 %d 번째 섹터에 저장되어있습니다.\n", lsn[q].link, q, j);
			}
		}
	}
	if (count == 0)
		printf("\n저장된 데이터가 없습니다.\n");
}

void Flash_write (){

	int k,Q,w,j;
	char save[20];

	printf("저장할 위치(lsn 위치)를 입력하시오.");
	scanf("%d",&k);

	if ((k < 0) || (k >= Secter)) {
		printf("\n\n유효한 위치가 아닙니다. 프로그램 종료.");
		exit(1);
	}

	printf("저장할 문자열을 입력하시오.");
	scanf("%s",&save);

	Q=lsn[k].link;

	if (Q >=32 ){
				w = Q/31;		//몇번지의 블록인지
				j = Q%31;		//w블록의 몇번째 섹터인지
				if (strcmp(blo[w].MEmory[j].data, A) != 0) {
					printf("이미 저장되어있는 데이터가 있습니다. 저장되지 않음.\n");
				}
				else {
					strcpy(blo[w].MEmory[j].data, save);
					printf("lsn %d번과 연결된 psn %d 번, %d 번 블럭 %d 번째 섹터에 저장되었습니다.\n", k, Q, w, j);
				}
			}
			else {
				j = Q%31;
				if (strcmp(blo[0].MEmory[j].data, A) != 0) {
					printf("이미 저장되어있는 데이터가 있습니다. 저장되지 않음.\n");
				}
				else {
					strcpy(blo[0].MEmory[j].data, save);
					printf("lsn %d번과 연결된 psn %d 번, 0번 블럭 %d 번째 섹터에 저장되었습니다.\n", k, Q, j);
				}
			}
}

void Flash_erase() {

	int k,Q,w,j,u,z;

	printf("\n삭제할 위치(lsn 위치)를 입력하십시오.");
	scanf("%d", &k);

	if ((k < 0) || (k >= Secter)) {
		printf("\n\n유효한 위치가 아닙니다. 프로그램 종료.");
		exit(1);
	}
	
	Q = lsn[k].link;

	if (Q >= 32) {
		w = Q / 31;		//몇번지의 블록인지
		j = Q % 31;		//w블록의 몇번째 섹터인지

		if (strcmp(blo[w].MEmory[j].data, A) == 0) {
			printf("\n\n이미 데이터가 비어있는 위치입니다. 프로그램을 종료합니다.\n");
			exit(1);
		}

		printf("\n해당 위치를 제외한 소속 블럭을 백업합니다.\n");

		printf("\n삭제할 섹터만을 제외하고 블럭을 여분 블록에 복사. 기존 블록 전부 삭제처리.\n\n");
		for (u = 0; u < 32; u++) {
			if (u != j) {
				strcpy(blo[block].MEmory[u].data, blo[w].MEmory[u].data);
				strcpy(blo[w].MEmory[u].data, A);
				printf("%d 번 블럭 %d 번째 섹터를 %d번 블럭 %d 번째 섹터에 복사 \n", w, u, block, u);
			}
				}

		printf("\n삭제할 위치를 제외하고 여분 블록에 있는 데이터들을 기존의 블럭 위치로 복사\n\n");
		for (z = 0; z < 32; z++) {
			strcpy(blo[w].MEmory[z].data, blo[block].MEmory[z].data);
			printf("%d 블럭 %d 번째 섹터를 %d번 블럭 %d 번째 섹터에 복사 \n", block, z, w, z);

			if (z == 0) printf("\n 여분 블록의 복사하고 남은 데이터 삭제\n");

			printf("%d번 블록 %d 번째 섹터 삭제 중\n\n", block, z);
			strcpy(blo[block].MEmory[z].data, A);

			if (z == j) {
				printf("\n\n삭제완료 \n\n");
				break;
			}
		}
		printf("\nlsn %d번과 연결된 psn %d 번, %d 번 블럭 %d 번째 섹터가 삭제처리되었습니다.\n", k, Q, w, j);
	}
	else {
		j = Q % 31;

		if (strcmp(blo[0].MEmory[j].data, A) == 0) {
			printf("\n\n이미 데이터가 비어있는 위치입니다. 프로그램을 종료합니다.\n");
			exit(1);
		}

		printf("\n삭제할 위치를 제외한 블럭들을 여분 블록에 복사\n\n");


		printf("\n해당 위치를 제외한 소속 블럭을 백업합니다.\n");

		for (u = 0; u < 32; u++) {
			if (u != j) {
				strcpy(blo[block].MEmory[u].data, blo[0].MEmory[u].data);
				strcpy(blo[0].MEmory[u].data, A);
				printf("0 번 블럭 %d 번째 섹터를 %d번 블럭 %d 번째 섹터에 복사 \n", u, block, u);
			}
		}
		
		printf("\n여분 블록에 있는 데이터들을 기존의 블럭 위치로 복사\n\n");
		for (z = 0; z < 32; z++) {

			if (z == 0) printf("\n 여분 블록의 복사하고 남은 데이터 삭제\n");

			strcpy(blo[0].MEmory[z].data, blo[block].MEmory[z].data);
			printf("%d 블럭 %d 번째 섹터를 0번 블럭 %d 번째 섹터에 복사, 여분블록 %d 섹터 삭제완료 \n", block, z, z,z);


			strcpy(blo[block].MEmory[z].data, A);
			
		}
		printf("lsn %d번과 연결된 psn %d 번, 0번 블럭 %d 번째 섹터가 삭제처리되었습니다.\n", k, Q, j);

	}

}

void main() {
	int u,o;

	init();

	while (1) {
		printf("실행할 기능을 선택하세요.\t1.출력\t2.데이터 쓰기\t3.데이터 삭제\t4.프로그램종료\n");
		scanf("%d", &u);

		switch (u)
		{

		case 1:
			Flash_read();
			break;

		case 2:
			Flash_write();
			break;

		case 3:
			Flash_erase();
			break;

		case 4: 
			free(lsn);
			free(psn);
			free(memory);
			free(blo);
			exit(1);
			break;

		default:
			printf("잘못된 값이 입력되었습니다. 다시 입력하십시오.");
			break;
		}
	}
}