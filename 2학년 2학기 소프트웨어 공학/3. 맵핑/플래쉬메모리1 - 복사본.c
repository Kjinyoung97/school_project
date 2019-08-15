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

void init(FILE *TABLE_file, FILE *MEMORY_file);
void Flash_read(FILE *TABLE_file, FILE *MEMORY_file);
void Flash_write(FILE *TABLE_file, FILE *MEMORY_file);

void init(FILE *TABLE_file, FILE *MEMORY_file){

	fopen_s(&TABLE_file, "TABLE_file.bin", "rb+");				//사용자이진파일 오픈. 만약 파일이 없을경우 신규 생성
	if (TABLE_file == NULL) {									//파일 생성 혹은 열기에 실패한 경우 
		puts("입력을 위한 파일을 열 수 없습니다.\n");			//에러메세지 출력
		exit(1);												//프로그램 종료
	}

	fopen_s(&MEMORY_file, "MEMORY_file.bin", "rb+");				//사용자이진파일 오픈. 만약 파일이 없을경우 신규 생성
	if (MEMORY_file == NULL) {									//파일 생성 혹은 열기에 실패한 경우 
		puts("입력을 위한 파일을 열 수 없습니다.\n");			//에러메세지 출력
		exit(1);												//프로그램 종료
	}

	int size;
	int i,w,j;
	char A[20] = "  ";

		printf("메모리는 몇MB 입니까? (2MB단위)\n");
		scanf("%d", &size);

		Secter = (size * 1024) / 512;
		block = (Secter / 32 ) +1;

		printf("섹터의 갯수 %d\n", Secter);
	
		lsn = (LSN *)malloc(sizeof(LSN)*Secter);
		psn = (LSN *)malloc(sizeof(LSN)*Secter);
		memory = (MEMORY *)malloc(sizeof(MEMORY));
		blo = (BLOCK *)malloc( sizeof(BLOCK)*block);

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
			}

			fwrite(&blo, sizeof(blo), 1, MEMORY_file);
			fwrite(&lsn, sizeof(lsn), 1, TABLE_file);
			fwrite(&psn, sizeof(psn), 1, TABLE_file);
			lsn[i].link = psn[i].data;


		}

		free(lsn);
		free(psn);
		free(memory);
		free(blo);
}

void Flash_read(FILE *TABLE_file, FILE *MEMORY_file) {

	int q, i, j, w;
	LSN *K;

	K = (LSN *)malloc(sizeof(LSN));
	while (!feof(TABLE_file)) {
		fread(&K, sizeof(K), 1, TABLE_file);
		printf("lsn의 값 %d \n\n", K);
		fread(&K, sizeof(K), 1, TABLE_file);
		printf("psn의 값 %d \n\n", K);
	}
	for (i = 0; i < Secter; i++) {
		printf("lsn의 값 %d\t psn의 값%d\t\n", lsn[i].data, psn[i].data);
	}
	for (q = 0; q < Secter; q++) {
		if (i >= 32) {
			w = i / 31;		//몇번지의 블록인지
			j = i % 31;		//w블록의 몇번째 섹터인지
			printf("저장된 문자열 : %s\n", blo[w].MEmory[j].data);
		}
		else {
			j = i % 31;
			printf("저장된 문자열 : %s\n", blo[0].MEmory[j].data);
		}
	}

	free(K);

}

void Flash_write (FILE *TABLE_file, FILE *MEMORY_file){


	int k,Q,w,j;
	char save[20];

	printf("저장할 위치를 입력하시오.");
	scanf("%d",&k);

	printf("저장할 문자열을 입력하시오.");
	scanf("%s",&save);

	Q=lsn[k].link;

	if (Q >=32 ){
				w = Q/31;		//몇번지의 블록인지
				j = Q%31;		//w블록의 몇번째 섹터인지
				strcpy(blo[w].MEmory[j].data, save);
				printf("%d 번 블럭 %d 번째 섹터에 저장되었습니다.\n",w,j);
			}
			else {
				j = Q%31;
				strcpy(blo[0].MEmory[j].data, save);
				printf("0번 블럭 %d 번째 섹터에 저장되었습니다.\n",j);
			}
}


void main(FILE *TABLE_file,FILE *MEMORY_file) {

	fopen_s(&TABLE_file, "TABLE_file.bin", "ab+");				//사용자이진파일 오픈. 만약 파일이 없을경우 신규 생성
	if (TABLE_file == NULL) {									//파일 생성 혹은 열기에 실패한 경우 
		puts("입력을 위한 파일을 열 수 없습니다.\n");			//에러메세지 출력
		exit(1);												//프로그램 종료
	}

	fopen_s(&MEMORY_file, "MEMORY_file.bin", "ab+");			//사용자이진파일 오픈. 만약 파일이 없을경우 신규 생성
	if (MEMORY_file == NULL) {									//파일 생성 혹은 열기에 실패한 경우 
		puts("입력을 위한 파일을 열 수 없습니다.\n");			//에러메세지 출력
		exit(1);												//프로그램 종료
	}
	

	fclose(TABLE_file);
	fclose(MEMORY_file);

	init(TABLE_file,MEMORY_file);
	Flash_read(TABLE_file, MEMORY_file);
	Flash_write(TABLE_file, MEMORY_file);
	Flash_read(TABLE_file, MEMORY_file);
}