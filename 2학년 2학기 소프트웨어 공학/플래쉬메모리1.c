#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LSN {		//매핑 테이블을 생성할 구조체 생성
	int data;
	struct LSN *link;
}LSN;
	
typedef struct MEMORY{		//문자열을 저장할 구조체 생성
	char data[20];			//문자열은 최대 20바이트까지 저장가능
}MEMORY;

typedef struct BLOCK{		//블럭구분을 위한 구조체 생성
	struct MEMORY MEmory[32];		// 블럭에는 메모리 구조체가 32개 포함되어있음.
}BLOCK;

int Secter,block;		//섹터 수와 블록 수를 정할 변수 선언

LSN *lsn;				//lsn을 나타낼 구조체 선언
MEMORY *memory;			//메모리 구조체
LSN *psn;				//psn을 나타낼 구조체 선언
BLOCK *blo;				//블럭을 나타내는 구조체 선언	
	
char A[20] = "  ";			//삭제처리를 담당할 공백 문자열 선언
int Write = 0, Erase = 0;	//읽기 쓰기 횟수를 측정하는 변수선언

void init();				//섹터와 블록을 생성하고 초기화하는 함수
void Flash_read();			//저장된 데이터와 매핑 테이블을 출력하는 함수
void Flash_write();			//데이터를 저장하는 함수
void Flash_erase();			//저장되어있는 데이터를 지우는 함수

void init(){

	int size;		//메모리의 크기를 정하는 변수 선언
	int i,w,j;		

		printf("메모리는 몇MB 입니까? (2MB단위)\n");
		scanf("%d", &size);		

		Secter = (size * 1024) / 512;		//MB를 바이트로 변환 후 나누어서 섹터 수 구함
		block = (Secter / 32 ) +1;			//섹터를 32개로 나누어서 블록 수 구하기. 여분 블록 하나 추가 생성.

		printf("%d MB크기의 플래쉬 메모리 생성\n\n", size);
		printf("섹터의 갯수 %d\n", Secter);
		printf("생성된 블럭의 갯수 %d (여분 블록 하나 포함) \n", block);
	
		lsn = (LSN *)malloc(sizeof(LSN)*Secter);		
		psn = (LSN *)malloc(sizeof(LSN)*Secter);
		memory = (MEMORY *)malloc(sizeof(MEMORY));
		blo = (BLOCK *)malloc(sizeof(BLOCK)*block);				//각각에 필요한 메모리 동적할당

		for (i = 0; i < Secter; i++) {
			lsn[i].data = 0 + i;					//lsn테이블 값 설정
			psn[i].data = (Secter - 1) - i;			//psn테이블 값 설정

			if (i >=32 ){
				w = i/31;							//몇번지의 블록인지	
				j = i%31;							//w블록의 몇번째 섹터인지
				strcpy(blo[w].MEmory[j].data,A);	//블럭 초기화
			}
			else {									//i가 32미만이면 무조껀 0번째 블록이므로
				j = i%31;							//블럭의 섹터 수 
				strcpy(blo[0].MEmory[j].data,A);	//블럭 초기화
			}

			lsn[i].link = psn[i].data;				//lsn의 link는 psn의 data를 가리키도록 설정.


		}
}

void Flash_read() {

	int q, i, j, w,count=0;
	
	for (i = 0; i < Secter; i++) {
		printf("lsn의 값 %d\t psn의 값%d\t\n", lsn[i].data, psn[i].data);
	}
	for (q = 0; q < Secter; q++) {
		if (q >= 32) {
			w = q / 31;												//몇번지의 블록인지
			j = q % 31;												//w블록의 몇번째 섹터인지
			if (strcmp(blo[w].MEmory[j].data, A) != 0) {			//공백과 비교하여 공백이 아닐때만 실행.
				count++;											//출력 횟수를 측정하는 count 변수 1증가
				printf("저장된 문자열 : %s\n", blo[w].MEmory[j].data);		//출력 실행
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
	if (count == 0)									//count 변수가 0이면 즉, 한번도 출력되지 않았으면
		printf("\n저장된 데이터가 없습니다.\n");		
}

void Flash_write (){

	int k,Q,w,j;
	char save[20];

	printf("저장할 위치(lsn 위치)를 입력하시오.");
	scanf("%d",&k);

	if ((k < 0) || (k >= Secter)) {								//범위를 벗어난 값을 입력하였거나 정수가 아닌 경우 에러 메세지 출력과 함께 종료
		printf("\n\n유효한 위치가 아닙니다. 프로그램 종료.");
		exit(1);
	}

	printf("저장할 문자열을 입력하시오.");
	scanf("%s",&save);

	Q=lsn[k].link;					// = psn[k].data  연결리스트를 통해 Q에 저장.

	if (Q >=32 ){
				w = Q/31;		//몇번지의 블록인지
				j = Q%31;		//w블록의 몇번째 섹터인지
				if (strcmp(blo[w].MEmory[j].data, A) != 0) {				//공백과 비교하여 공백이 아니면 이미 저장되어 있는 데이터가 있다는것이므로
					printf("이미 저장되어있는 데이터가 있습니다. 저장되지 않음.\n");		//에러메세지 출력.
				}
				else {
					strcpy(blo[w].MEmory[j].data, save);				//공백일때만 저장함.
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
		w = Q / 31;						//몇번지의 블록인지
		j = Q % 31;						//w블록의 몇번째 섹터인지

		if (strcmp(blo[w].MEmory[j].data, A) == 0) {			//삭제하기전 이미 공백인지 검사
			printf("\n\n이미 데이터가 비어있는 위치입니다. 프로그램을 종료합니다.\n");		//이미 공백이면 에러메세지 출력. 프로그램 종료
			exit(1);
		}

		printf("\n해당 위치를 제외한 소속 블럭을 백업합니다.\n");

		printf("\n삭제할 위치를 제외한 블럭들을 여분 블록에 복사\n\n");
		for (u = 0; u < 32; u++) {
			strcpy(blo[block].MEmory[j].data,blo[w].MEmory[j].data);
			printf("%d 번 블럭 %d 번째 섹터를 %d번 블럭 %d 번째 섹터에 복사 \n",w, j,block,u);
		}
		
		strcpy(blo[block].MEmory[j].data, A);
		printf("\n삭제할 위치를 제외하고 여분 블록에 있는 데이터들을 기존의 블럭 위치로 복사\n\n");
		for (z = 0; z < 32; z++) {
			strcpy(blo[w].MEmory[z].data, blo[block].MEmory[z].data);
			printf("%d 블럭 %d 번째 섹터를 %d번 블럭 %d 번째 섹터에 복사 \n", block, z, w, z);

			if (z == 0) printf("\n 여분 블록의 복사하고 남은 데이터 삭제\n");

			printf("%d번 블록 %d 번째 섹터 삭제 중\n\n", block, z);
			strcpy(blo[block].MEmory[z].data, A);

			if (z == 31) printf("\n\n삭제완료 \n\n");
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
			strcpy(blo[block].MEmory[j].data, blo[0].MEmory[j].data);
			printf("0 번 블럭 %d 번째 섹터를 %d번 블럭 %d 번째 섹터에 복사 \n",  j, block, u);
		}
		strcpy(blo[block].MEmory[j].data, A);
		printf("\n삭제할 위치를 제외하고 여분 블록에 있는 데이터들을 기존의 블럭 위치로 복사\n\n");
		for (z = 0; z < 32; z++) {
			strcpy(blo[0].MEmory[z].data, blo[block].MEmory[z].data);
			printf("%d 블럭 %d 번째 섹터를 0번 블럭 %d 번째 섹터에 복사 \n", block, u, z);

			if (z == 0) printf("\n 여분 블록의 복사하고 남은 데이터 삭제\n");

			printf("%d번 블록 %d 번째 섹터 삭제 중\n", block, z);
			strcpy(blo[block].MEmory[z].data, A);

			if (z == 31) printf("\n\n삭제완료 \n\n");
		}
		printf("lsn %d번과 연결된 psn %d 번, 0번 블럭 %d 번째 섹터가 삭제처리되었습니다.\n", k, Q, j);

	}

}


void main() {
	int u;

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

		default:
			printf("잘못된 값이 입력되었습니다. 다시 입력하십시오.");
			break;
		}
	}

}