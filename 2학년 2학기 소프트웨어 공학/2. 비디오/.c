#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int i,Count,COUNT;
char A[10] = "  ";				//삭제에 사용할 공백 배열 선언
char B[10] = "보유";			
char C[10] = "대출중";			//비디오의 보유 현황을 보여줄 배열 선언


void User_Add(FILE *User_file, FILE *Video_file);		//사용자 추가 함수
void Video_Add(FILE *User_file, FILE *Video_file);		//비디오 추가 함수
void Search_User(FILE *User_file);						//사용자 검색 함수
void Search_Video(FILE *Video_file);					//비디오 검색 함수
void Print_User(FILE *User_file);						//사용자 전체 출력 함수
void Print_Video(FILE *Video_file);						//비디오 전체 출력 함수
void Have_Video(FILE *Video_file);						//보유중인 비디오를 출력하는 함수
void Rent_Video(FILE *User_file, FILE *Video_file);		//대여를 담당하는 함수
void Return_Video(FILE *User_file, FILE *Video_file);	//반납을 담당하는 함수
void Write(FILE *User_file, FILE *Video_file, int Count, int COUNT);		//파일에 데이터를 쓰는 역할을  하는 함수
void Not_Have_Video(FILE *Video_file);										//대여중이라 보유하고있지 않은 비디오를 출력하는 함수 (자체 테스트용)
void Write2(FILE *User_file, FILE *Video_file,int Count, int COUNT);		//파일에 데이터를 쓰는 역할을  하는 함수2
void User_Delete(FILE *User_file);											//사용자 정보 삭제 함수
void Video_Delete(FILE *Video_file);										//비디오 정보 삭제 함수

typedef struct User {			//사용자 정보를 담당하는 구조체 선언
	char name[20];				//이름을 저장
	char number[20];			//전화번호 저장
	char video1[20];			//대여한 비디오 현황 1~3
	char video2[20];
	char video3[20];
}USER;

typedef struct Video {			//비디오 정보를 담당하는 구조체 선언
	char name[20];				//이름을 저장
	char number[20];			//등록번호 저장
	char have[10];				//비디오 보유현황을 검사할 배열
}VIDEO;

USER data8;
VIDEO data9;


void main(FILE *User_file, FILE *Video_file) {

	fopen_s(&Video_file, "Video_file.bin", "ab+");				//사용자이진파일 오픈. 만약 파일이 없을경우 신규 생성
	if (Video_file == NULL) {									//파일 생성 혹은 열기에 실패한 경우 
		puts("입력을 위한 파일을 열 수 없습니다.\n");			//에러메세지 출력
		exit(1);												//프로그램 종료
	}


	fopen_s(&User_file, "User_file.bin", "ab+");				//비디오 이진파일 오픈. 만약 파일이 없을경우 신규 생성
	if (User_file == NULL) {									//파일 생성 혹은 열기에 실패한 경우 
		puts("입력을 위한 파일을 열 수 없습니다.\n");			//에러메세지 출력
		exit(1);												//프로그램 종료
	}

	fclose(User_file);
	fclose(Video_file);

	Main_Print(User_file,Video_file);							//메인함수에서 메뉴선택을 담당하는 함수를 호출한다.
}

int Main_Print(FILE *User_file, FILE *Video_file) {				//각각의 메뉴를 선택할 수 있는 선택창을 출력하는 함수


	fopen_s(&Video_file, "Video_file.bin", "rb+");				//비디오 파일 이진파일 오픈. 만약 파일이 없을경우 신규 생성
	if (Video_file == NULL) {									//파일 생성 혹은 열기에 실패한 경우 
		puts("입력을 위한 파일을 열 수 없습니다.\n");			//에러메세지 출력
		exit(1);												//프로그램 종료
	}


	fopen_s(&User_file, "User_file.bin", "rb+");				//유저 파일 이진파일 오픈. 만약 파일이 없을경우 신규 생성
	if (User_file == NULL) {									//파일 생성 혹은 열기에 실패한 경우 
		puts("입력을 위한 파일을 열 수 없습니다.\n");			//에러메세지 출력
		exit(1);												//프로그램 종료
	}

	printf("\t\t==============사용할 기능을 선택하세요============== \n\n");
	printf("\t1.사용자추가\t2.비디오추가\t3.사용자 검색\t4.비디오검색\n\t5.대여가능 비디오 출력\t\t6.대여\t\t7.반납\n\t8.사용자 정보삭제\t9.비디오 정보삭제\t10.프로그램 종료\n\n\t11.사용자 정보 전체출력\t\t12.비디오 정보 전체출력\n ");
	printf("\t\t==================================================== \n\n");

	scanf_s("%d", &i);											//사용자가 고른것을 i에 저장한다.

	switch (i)													//사용자가 골라서 저장한 i값을 사용하여 switch문.
	{

	case 1 :
	
			
		User_Add(User_file,Video_file);
		fclose(User_file);
		fclose(Video_file);
		Main_Print(User_file, Video_file);

	case 2 :

		Video_Add(User_file, Video_file);
		fclose(User_file);
		fclose(Video_file);
		Main_Print(User_file, Video_file);

	case 3 :
	
		Search_User(User_file);
		fclose(User_file);
		fclose(Video_file);
		Main_Print(User_file, Video_file);

	case 4 :

		Search_Video(Video_file);
		fclose(User_file);
		fclose(Video_file);
		Main_Print(User_file, Video_file);

	case 5 :

		Have_Video(Video_file);
		fclose(User_file);
		fclose(Video_file);
		Main_Print(User_file, Video_file);


	case 6 :

		Rent_Video(User_file,Video_file);
		fclose(User_file);
		fclose(Video_file);
		Main_Print(User_file, Video_file);


	case 7 :
		
		Return_Video(User_file, Video_file);
		fclose(User_file);
		fclose(Video_file);
		Main_Print(User_file, Video_file);

	case 8 :

		User_Delete(User_file);
		fclose(User_file);
		fclose(Video_file);
		Main_Print(User_file, Video_file);

	case 9 :

		Video_Delete(Video_file);
		fclose(User_file);
		fclose(Video_file);
		Main_Print(User_file, Video_file);

	case 10 :

		
		exit(1);
		break;

	case 11:
		Print_User(User_file);
		fclose(User_file);
		fclose(Video_file);
		Main_Print(User_file, Video_file);

	case 12:
		Print_Video(Video_file);
		fclose(User_file);
		fclose(Video_file);
		Main_Print(User_file, Video_file);

	case 13 :

		Not_Have_Video(Video_file);
		fclose(User_file);
		fclose(Video_file);
		Main_Print(User_file, Video_file);


	default:												//정해진 값 이외에 값을 입력받으면 에러메세지 출력.
		printf("잘못된 값입니다. 다시 입력하세요");
		break;
	}
}

void User_Add(FILE *User_file, FILE *Video_file) {			//사용자 추가 함수

	USER data;												
	int count = 0;											//파일 포인터 위치를 제어 할 변수 count 선언 및 초기화
	

	fseek(User_file, 0, SEEK_SET);							//파일 포인터의 위치를 파일 시작지점으로 옮기고
	fflush(stdin);											//표준 입출력장치의 버퍼를 비운 후

	getchar();

	while (!feof(User_file)) {								//파일의 끝에 도달 할 때 까지 반복하여 
		fread(&data, sizeof(data), 1, User_file);			//현재 포인터의 위치에서 읽어서 구조체 data에 저장.									
		count++;											//한번 읽어올때마다 count의 값 1씩 증가
			if (strcmp(data.name, "  ") == 0) {
			//만약 읽어 온 값(data.name)이 공백 두칸과 동일하다면 (삭제처리가 되었다면) (한칸이 아닌 두칸인 이유는 띄워쓰기와 비교하는것을 방지)

			printf("\n======신규 입력 선택(공백)======\n\n");			//사용자에게 본인이 선택한것이 무엇인지 보여줌 공백이있다는건 삭제처리된 자리임.

			printf("이름을 입력하세요.\n");						//사용자가 이름을 입력하게 유도
			gets(data.name);									//입력받은것을 data.name에 저장

			printf("휴대폰 번호를 입력하세요\n");				//휴대폰 번호도 입력하게 유도
			gets(data.number);									//번호를 입력받아 data.number에 저장

			strcpy(data.video1, A);								//비디오 대여 현황 1~3을 전부 배열 A, 즉 공백으로 만듬.
			strcpy(data.video2, A);
			strcpy(data.video3, A);

			fseek(User_file, 0L, SEEK_END);								//이진파일의 포인터를 파일의 맨 끝에 위치시키고
			fseek(User_file, ((count - 1) * sizeof(data)), SEEK_SET);	//시작지점부터 (카운터의 값 -1) * 구조체의 크기 만큼 포인터를 이동시킨다.
			fwrite(&data, sizeof(data), 1, User_file);					//그곳에 아까 입력받은 자료를 저장한 구조체 data를 써넣음. 즉 공백인 곳에 데이터 위에 입력받은 데이터를 덮어 씌움
			
			printf("이름 : %s 전화번호 : %s 대여현황 %s %s %s \n\n", data.name, data.number, data.video1, data.video2, data.video3);

			break;

		
		}

		else {													//공백이 두 칸 연속인 곳을 찾지 못한다면 (삭제되어 공백처리 된 데이터가 없다면)
			
			printf("이름을 입력하세요.\n");						//사용자가 이름을 입력하게 유도
			gets(data.name);									//입력받은것을 data.name에 저장

			printf("휴대폰 번호를 입력하세요\n");				//휴대폰 번호도 입력하게 유도
			gets(data.number);									//번호를 입력받아 data.number에 저장

			strcpy(data.video1, A);								//비디오 대여 현황 1~3을 전부 배열 A, 즉 공백으로 만듬.
			strcpy(data.video2, A);
			strcpy(data.video3, A);
			

			fseek(User_file, 0L, SEEK_END);							//이진파일의 포인터를 파일의 맨 끝에 위치시키고
			fwrite(&data, sizeof(data), 1, User_file);				//그곳에 아까 입력받은 자료를 저장한 구조체 data를 써넣음. 즉 공백인 곳에 데이터 위에 입력받은 데이터를 덮어 씌움

			printf("이름 : %s 전화번호 : %s 대여현황 %s %s %s \n\n", data.name, data.number, data.video1, data.video2, data.video3);
			
		}
		break;
	}
		strcpy(data8.name,data.name);								//전역변수로 선언되어있는 사용자 함수 data8 에 data의 내용을 전부 복사함.
		strcpy(data8.number,data.number);
		strcpy(data8.video1,data.video1);
		strcpy(data8.video2,data.video2);
		strcpy(data8.video3,data.video3);

}

void Video_Add(FILE *User_file, FILE *Video_file) {					//비디오를 추가하는 함수 

	VIDEO data2,data3;
	int count = 0;

	fseek(Video_file, 0, SEEK_SET);							//파일 포인터의 위치를 파일 시작지점으로 옮기고
	fflush(stdin);											//표준 입출력장치의 버퍼를 비운 후

	getchar();

	while (!feof(Video_file)) {								//파일의 끝에 도달 할 때 까지 반복하여 
		fread(&data3, sizeof(data3), 1, Video_file);		//현재 포인터의 위치에서 읽어서 구조체 data에 저장.
		count++;											//한번 읽어올때마다 count의 값 1씩 증가
		if (strcmp(data3.name, "  ") == 0) {
			//만약 읽어 온 값(data3.name)이 공백 두칸과 동일하다면 (삭제처리가 되었다면) (한칸이 아닌 두칸인 이유는 띄워쓰기와 비교하는것을 방지)

			printf("\n======신규 입력 선택(공백)======\n\n");			//사용자에게 본인이 선택한것이 무엇인지 보여줌

			printf("이름을 입력하세요.\n");						//사용자가 이름을 입력하게 유도
			gets(data2.name);									//입력받은것을 data2.name에 저장

			printf("등록 번호를 입력하세요\n");					//등록번호도 입력하게 유도
			gets(data2.number);									//번호를 입력받아 data2.number에 저장

			strcpy(data2.have, B);								//비디오 보유 현황을 담당하는 data2.have에 배열 B (=보유)를 붙어넣음

			fseek(Video_file, 0L, SEEK_END);							//이진파일의 포인터를 파일의 맨 끝에 위치시키고
			fseek(Video_file, ((count - 1) * sizeof(data2)), SEEK_SET);	//(카운터의 값 -1) * 구조체의 크기 만큼 포인터를 앞으로 이동시킨다.
			fwrite(&data2, sizeof(data2), 1, Video_file);				//그곳에 아까 입력받은 자료를 저장한 구조체 data를 써넣음. 즉 공백인 곳에 데이터 위에 입력받은 데이터를 덮어 씌움

			printf("이름 : %s 등록번호 : %s 보유현황 %s \n\n", data2.name, data2.number, data2.have);

		}

		else {													//공백이 두 칸 연속인 곳을 찾지 못한다면 (삭제되어 공백처리 된 데이터가 없다면)

			printf("이름을 입력하세요.\n");						//사용자가 이름을 입력하게 유도
			gets(data2.name);									//입력받은것을 data2.name에 저장

			printf("등록 번호를 입력하세요\n");					//등록 번호도 입력하게 유도
			gets(data2.number);									//번호를 입력받아 data2.number에 저장

			strcpy(data2.have, B);								//비디오 보유 현황을 담당하는 data2.have에 배열 B (=보유)를 붙어넣음

			fseek(Video_file, 0, SEEK_END);								//이진파일의 포인터를 파일의 맨 끝에 위치시키고
			fwrite(&data2, sizeof(data2), 1, Video_file);				//그곳에 아까 입력받은 자료를 저장한 구조체 data2를 써넣음

			printf("이름 : %s 등록번호 : %s 보유현황 %s \n\n", data2.name, data2.number, data2.have);

			break;
		}
		break;
	}
}

void Search_User(FILE *User_file) {							//사용자 검색에 사용하는 함수

	
	USER data2;
	char search[20];

	int count = 0;											//출력횟수를 측정하는 변수 count를 선언하고 0으로 초기화
	COUNT = 0;												//파일 포인터의 위치를 조정할 변수 COUNT를 선언하고 0으로 초기화

	fseek(User_file, 0, SEEK_SET);							//포인터의 위치를 파일의 처음으로
	fflush(stdin);											//표준입출력 장치의 버퍼를 비움
	getchar();												//한텀의 쉬는시간(바로 안넘어가게)으로 사용

	printf("검색할 사람의 이름을 입력하세요\n\n");			//사용자가 삭제할 사람의 이름을 입력하게 유도
	gets(search);											//그 입력한 이름을 search에 저장

	while (!feof(User_file)) {								//파일의 끝이 아니면 반복
		fread(&data2, sizeof(data2), 1, User_file);			//현재 포인터의 위치에서 자료를 읽어서 구조체 data2에 저장.
		COUNT++;											//한번 읽어올때마다 COUNT의 값 1씩 증가
		if (strcmp(data2.name, search) == 0) {			    //data2.name에 search와 같은 내용이있으면 실행
			count++;
			printf("이름 : %s 전화번호 : %s 대여현황 %s %s %s \n\n", data2.name, data2.number, data2.video1, data2.video2, data2.video3);
			
			strcpy(data8.name,data2.name);
			strcpy(data8.number,data2.number);				//전역변수로 선언되어있는 사용자 함수 data8 에 data2의 내용을 전부 복사함.
			strcpy(data8.video1,data2.video1);
			strcpy(data8.video2,data2.video2);
			strcpy(data8.video3,data2.video3);

			break;
		}
	}
	if (count == 0) printf("검색결과 없음\n\n");			//count (=출력한 횟수)가 0이면 검색결과없음 출력.

}

void Search_Video(FILE *Video_file) {						//비디오 검색에 이용하는 변수

	Count = 0;												//파일 포인터의 위치를 조정할 변수 Count를 선언하고 0으로 초기화

	VIDEO data2;
	char search[20];
	int k;
	int count = 0;

	fseek(Video_file, 0, SEEK_SET);							//포인터의 위치를 파일의 처음으로
	fflush(stdin);											//표준입출력 장치의 버퍼를 비움
	getchar();												//한텀의 쉬는시간(바로 안넘어가게)으로 사용

	printf("1. 이름으로검색 \t 2. 등록번호로 검색\n\n");
	scanf_s("%d", &k);

	switch (k) {


	case 1:
	{

		printf("검색할 비디오의 이름을 입력하세요\n\n");			//사용자가 검색할 사람의 이름을 입력하게 유도
		getchar();
		gets(search);												//그 입력한 이름을 search에 저장

		while (!feof(Video_file)) {									//파일의 끝이 아니면 반복
			fread(&data2, sizeof(data2), 1, Video_file);			//현재 포인터의 위치에서 자료를 읽어서 구조체 data2에 저장.											
			Count++;												//한번 읽어올때마다 Count의 값 1씩 증가
			if (strcmp(data2.name, search) == 0) {				    //data2.name에 search와 같은 내용이있으면 실행
				count++;
				printf("\n이름 : %s 등록번호 : %s 보유현황 %s \n\n", data2.name, data2.number, data2.have);
				break;
			}
		}
		if (count == 0) printf("검색결과 없음\n\n");				//끝까지 반복했으나 count가 0이면 (=한번도 찾지 못하였으면) 결과없음 출력
		break;
	}

	case 2:
	{

		fflush(stdin);
		getchar();

		printf("검색할 비디오의 등록번호를 입력하세요\n\n");			//사용자가 삭제할 사람의 등록번호를 입력하게 유도
		gets(search);													//그 입력한 등록번호를 search에 저장

		while (!feof(Video_file)) {										//파일의 끝이 아니면 반복
			fread(&data2, sizeof(data2), 1, Video_file);				//현재 포인터의 위치에서 자료를 읽어서 구조체 data2에 저장.	
			Count++;													//한번 읽어올때마다 Count의 값 1씩 증가
			if (strcmp(data2.number, search) == 0) {				    //data2.name에 search와 같은 내용이있으면 실행
				count++;	
				printf("이름 : %s 등록번호 : %s 보유현황 %s \n\n", data2.name, data2.number, data2.have);
				break;
			}
		}
		if (count == 0) printf("검색결과 없음\n\n");
		break;
	}

	default:
		break;
	}

	strcpy(data9.name,data2.name);
	strcpy(data9.number,data2.number);
	strcpy(data9.have,data2.have);
}

void Print_User(FILE *User_file) {						//저장되어있는 사용자 정보들을 출력한다.

	printf("사용자 정보 전체출력\n\n");

	USER data3;											//출력하는데 파일에서 구조체를 읽어와서 그 구조체를 저장할 data3 선언

	int count = 0;										//몇번 출력이 이루어 졌는지 검사할 변수 count 출력

	fseek(User_file, 0, SEEK_SET);									//포인터의 위치를 파일의시작지점으로 옮김

	while (fread(&data3, sizeof(data3), 1, User_file)) {			//파일내에서 읽어오는 동안 계속 반복
		if (!strcmp(data3.name, "  ") == 0) {				//data3.name과 "  " (공백두칸)(=삭제된 데이터)을 비교하여 같지 않다면 실행 
			printf("이름 : %s 전화번호 : %s 대여현황 %s %s %s \n\n", data3.name, data3.number, data3.video1, data3.video2, data3.video3);							//읽어온 구조체 data3를 출력
			count++;										//출력한번당 count값을 1씩 증가
		}
		if (SEEK_END == 1) break;							//만약 포인터의 위치가 파일의 끝이면 반복 종료
	}
	if (count == 0) printf("출력할 파일이 없습니다.\n\n");
	//만약 count의 값이 1도 증가하지않았다면, 즉 전부 공백이거나 저장된 데이터가없다면 출력할 것이 없다는 메세지 출력


}

void Print_Video(FILE *Video_file) {						//저장된 비디오의 정보를 출력하는 

	printf("비디오 정보 전체출력 \n\n");

	VIDEO data3;											//출력하는데 파일에서 구조체를 읽어와서 그 구조체를 저장할 data3 선언

	int count = 0;											//몇번 출력이 이루어 졌는지 검사할 변수 count 출력

	fseek(Video_file, 0, SEEK_SET);									//포인터의 위치를 파일의시작지점으로 옮김

	while (fread(&data3, sizeof(data3), 1, Video_file)) {			//파일내에서 읽어오는 동안 계속 반복
		if (!strcmp(data3.name, "  ") == 0) {						//data3.name과 "  " (공백두칸)(=삭제된 데이터)을 비교하여 같지 않다면 실행 
			printf("이름 : %s 등록번호 : %s 보유현황 %s \n\n", data3.name, data3.number, data3.have);						//읽어온 구조체 data3를 출력
			count++;										//출력한번당 count값을 1씩 증가
		}
		if (SEEK_END == 1) break;							//만약 포인터의 위치가 파일의 끝이면 반복 종료
	}
	if (count == 0) printf("출력할 파일이 없습니다.\n\n");
	//만약 count의 값이 1도 증가하지않았다면, 즉 전부 공백이거나 저장된 데이터가없다면 출력할 것이 없다는 메세지 출력

}

void Not_Have_Video(FILE *Video_file) {
	
	VIDEO data2;
	int count = 0;

	fseek(Video_file, 0, SEEK_SET);	

	while (fread(&data2, sizeof(data2), 1, Video_file)) {			//현재 포인터의 위치에서 자료를 읽어서 구조체 data2에 저장.		
			if ((strcmp(data2.have,C) == 0)&& (!strcmp(data2.name, "  ") == 0)){			//공백(삭제 처리)이 아니고 동시에 보유현황이 미보유인 경우에 실행
				printf("이름 : %s 등록번호 : %s 보유현황 %s \n\n", data2.name, data2.number, data2.have);
				count++;											//한번 출력할때마다 count의 값 1씩 증가
			}
	}
	if(count==0) printf("대여중인 비디오가 없습니다.\n\n");			//한번도 출력 된 적이없으면 대여중인 비디오가 없다고 출력
}

void Have_Video(FILE *Video_file) {									//보유중인 비디오 출력

	VIDEO data2;
	int count = 0;

	fseek(Video_file, 0, SEEK_SET);

	while (fread(&data2, sizeof(data2), 1, Video_file)) {									//현재 포인터의 위치에서 자료를 읽어서 구조체 data2에 저장.
		if ((strcmp(data2.have, C) != 0) && (!strcmp(data2.name, "  ") == 0)){				//공백(삭제 처리)이 아니고 동시에 보유현황이 미보유가 아닌 경우에 실행
			printf("이름 : %s 등록번호 : %s 보유현황 %s \n\n", data2.name, data2.number, data2.have);			
			count++;																		//한번 출력할때마다 count의 값 1씩 증가
		}
	}
	if (count == 0) printf("대여가능한 비디오가 없습니다.\n\n");							//한번도 출력하지 않은 경우 대여가능한 비디오가 없다는 메세지 출력
}
	
void Rent_Video(FILE *User_file, FILE *Video_file){											//대여를 담당하는 함수
				
	COUNT = 0;
	Count = 0;

	int z;

	int count=0 ;

	printf("신규 사용자 입니까?\n");
	printf("1. 예 \t\t2. 아니오\n\n");
	scanf_s("%d",&z);

	fflush(stdin);

	switch (z) {
	case 1: {
		printf("사용자 추가부터 진행해주세요\n\n");
	
		break;
	}
	case 2: {

		printf("기존 사용자 검색\n");
		Search_User(User_file);					//사용자 검색 함수 호출
		if ((!strcmp(data8.video1, A) == 0) && (!strcmp(data8.video3, A) == 0) && (!strcmp(data8.video2, A) == 0)) {		
			/* 대여 현황에 공백이 없으면 count의 값을 증가시킴.*/
			++count;													//한번 읽어올때마다 count의 값 1씩 증가
			break;
		}
		if (count != 0) {		//count의 값이 0 이아니라면 즉 1인 갯수제한인 3개를 전부 빌렸다면 반납부터 진행하도록 메세지 출력하고 프로그램종료
			printf("기존 비디오의 반납부터 진행해주세요.\n");
			exit(1);
		}

		printf("대여할 비디오를 검색합니다\n");
		Search_Video(Video_file);


		if ((strcmp(data9.have, B) == 0)) {
			strcpy(data9.have, C);


			printf("이름 : %s 등록번호 : %s 보유현황 %s \n\n", data9.name, data9.number, data9.have);
			printf("\n\n대여완료\n\n");

			Write(User_file, Video_file,Count,COUNT);

			break;
		}
		else {
			printf("보유중인 비디오가 아닙니다.\n\n");
			exit(1);
		}
		break;
	}
	
	default :
		printf("잘못된 입력입니다. 다시 입력하세요.\n");
		exit(1);
	}
}

void Return_Video(FILE *User_file, FILE *Video_file) {		//비디오 반납에 관한 함수

	Count = 0;

	int count = 0;
	int u=0;

	printf("반납할 사용자의 정보 검색 \n");
	Search_User(User_file);
	if ((strcmp(data8.video1, A) == 0) && (strcmp(data8.video3, A) == 0) && (strcmp(data8.video2, A) == 0)) {
		++count;													//사용자의 비디오 대여 현황이 전부 공백일때 count 값 1 증가
	}
	if (count != 0) {												//count의 값이 0이 아닐경우 메세지를 출력하고 프로그램 종료
		printf("대여한 비디오가 없습니다.");
		exit(1);
	}

	printf("반납할 비디오를 선택하세요\n");							//사용자의 비디오 대여현황을 출력하고 그중에 반납할 비디오를 선택하도록 유도
	printf("1.%s 2.%s 3.%s\n\n", data8.video1, data8.video2, data8.video3);
	scanf_s("%d", &u);												//사용자가 선택한것을 u에 저장


	switch (u) {													//u에 저장한걸로 switch문 호출
	case 1:
		while (!feof(Video_file)) {									//파일의 끝이 아니면 반복
			fread(&data9, sizeof(data9), 1, Video_file);
			Count++;
			if (strcmp(data8.video1, data9.name)==0) {				//1번을 선택한경우 비디오 1과 비교
				printf("%s\t %s", data9.name, data9.have);
				break;
			}
		}
		break;
	case 2:
		while (!feof(Video_file)) {									//파일의 끝이 아니면 반복
			fread(&data9, sizeof(data9), 1, Video_file);
			Count++;
			if (strcmp(data8.video2, data9.name)==0) {				//2번을 선택한경우 비디오 현황 2와 비교
				printf("%s\t %s", data9.name, data9.have);
				break;
			}
		}
		break;
	case 3:
		while (!feof(Video_file)) {									//파일의 끝이 아니면 반복
			fread(&data9, sizeof(data9), 1, Video_file);
			Count++;
			if (strcmp(data8.video3, data9.name) == 0) {			//3번을 선택한경우 비디오 현황 3와 비교
				printf("%s\t %s", data9.name, data9.have);
				break;
			}
		}
		break;

	default: {
		printf("error\n\n");
		exit(1);
	}
	}

	if (strcmp(data9.have, C) == 0) {				//반납하려는 비디오가 미보유, 즉 대여중(=C) 일때만 실행

		strcpy(data9.have, B);						//비디오 보유 현황을 B(=보유)로 바꿈


		printf("이름 : %s 등록번호 : %s 보유현황 %s \n\n", data9.name, data9.number, data9.have);
		printf("\n\n반납완료\n\n");

		Write2(User_file, Video_file,Count,COUNT);	//파일에 구조체를 쓰는 함수 호출
	}
	else {											//대여중이 아니라면 메세지를 출력후 종료
		printf("대출중인 비디오가 아닙니다.\n\n");
		exit(1);
	}
}

void Write(FILE *User_file, FILE *Video_file,int Count,int COUNT) {


	fseek(Video_file, 0L, SEEK_END);								//파일 포인터의 위치를 파일 맨 끝으로 이동시키고
	fseek(Video_file, ((Count - 1) * sizeof(data9)), SEEK_SET);		//파일의 시작지점으로부터 증가한 count값 -1 만큼 구조체(data2)의 크기에 곱한 후 그 만큼 포인터를 앞으로 이동시킨다
	fwrite(&data9, sizeof(data9), 1, Video_file);

	printf("이름 : %s 전화번호 : %s 대여현황 %s %s %s \n\n", data8.name, data8.number, data8.video1, data8.video2, data8.video3);

	if (strcmp(data8.video1, A) == 0) {								//사용자의 비디오 대여 현황이 공백인곳을 찾아서 그곳에 덮어씌워 저장
		strcpy(data8.video1, data9.name);
		fseek(User_file, 0L, SEEK_END);						
		fseek(User_file, ((COUNT - 1) * sizeof(data8)), SEEK_SET);	
		fwrite(&data8, sizeof(data8), 1, User_file);
	}
	else if (strcmp(data8.video2, A) == 0) {
		strcpy(data8.video2, data9.name);
		fseek(User_file, 0L, SEEK_END);						
		fseek(User_file, ((COUNT - 1) * sizeof(data8)), SEEK_SET);		
		fwrite(&data8, sizeof(data8), 1, User_file);
	}
	else if (strcmp(data8.video3, A) == 0) {
		strcpy(data8.video3, data9.name);
		fseek(User_file, 0L, SEEK_END);						
		fseek(User_file, ((COUNT - 1) * sizeof(data8)), SEEK_SET);		
		fwrite(&data8, sizeof(data8), 1, User_file);
	}
	else printf("error\n\n");

}

void Write2(FILE *User_file, FILE *Video_file,int Count, int COUNT) {

	fseek(Video_file, 0L, SEEK_END);						
	fseek(Video_file, ((Count - 1) * sizeof(data9)), SEEK_SET);		
	fwrite(&data9, sizeof(data9), 1, Video_file);

	printf("이름 : %s 전화번호 : %s 대여현황 %s %s %s \n\n", data8.name, data8.number, data8.video1, data8.video2, data8.video3);

	if (strcmp(data8.video1, data9.name) == 0) {							//사용자의 비디오 대여 현황에 반납할 비디오와 같은 이름을 가진곳을 찾아서 그곳에 덮어씌워 저장
		strcpy(data8.video1, A);
		fseek(User_file, 0L, SEEK_END);						
		fseek(User_file, ((COUNT-1) * sizeof(data8)), SEEK_SET);		
		fwrite(&data8, sizeof(data8), 1, User_file);
	}
	else if (strcmp(data8.video2, data9.name) == 0) {
		strcpy(data8.video2, A);
		fseek(User_file, 0L, SEEK_END);						
		fseek(User_file, ((COUNT-1) * sizeof(data8)), SEEK_SET);		
		fwrite(&data8, sizeof(data8), 1, User_file);
	}
	else if (strcmp(data8.video3, data9.name) == 0) {
		strcpy(data8.video3, A);
		fseek(User_file, 0L, SEEK_END);						
		fseek(User_file, ((COUNT-1) * sizeof(data8)), SEEK_SET);		
		fwrite(&data8, sizeof(data8), 1, User_file);
	}
	else printf("error\n\n");

}

void User_Delete(FILE *User_file) {						//사용자를 삭제하는 함수

	USER data2;											//파일을 읽어와서 비교 후 공백으로 덧씌울 구조체 data2 선언 
	char A[20] = "  ";									//공백으로 만들 (삭제처리) 문자열 배열 A 선언
	char search[20];
	
	int count = 0;												//포인터의 위치를 조정할 변수 count를 선언하고 0으로 초기화

	fseek(User_file, 0, SEEK_SET);								//포인터의 위치를 파일의 처음으로
	fflush(stdin);												//표준입출력 장치의 버퍼를 비움
	getchar();													//한텀의 쉬는시간(바로 안넘어가게)으로 사용

	printf("삭제할 사람의 이름을 입력하세요\n\n");				//사용자가 삭제할 사람의 이름을 입력하게 유도
	gets(search);												//그 입력한 이름을 search에 저장

	while (!feof(User_file)) {									//파일의 끝이 아니면 반복
		fread(&data2, sizeof(data2), 1, User_file);				//현재 포인터의 위치에서 자료를 읽어서 구조체 data2에 저장.
		count++;												//한번 읽어올때마다 count의 값 1씩 증가
		if (strcmp(data2.name, search) == 0) {					//data2.name에 search와 같은 내용이있으면 실행
			
			strcpy(data2.name, A);								//그 구조체.name에 A(공백)를 붙여넣어 이름을 삭제처리를 해준다
			strcpy(data2.number, A);							//동일하게 그 구조체.number에 A(공백)을 붙여넣어 전화번호도 삭제처리한다.
			strcpy(data2.video1,A);								//그 읽어온 구조체 .video에 A(공백)을 붙여넣어 비디오 대여 현황을 삭제처리한다.
			strcpy(data2.video2, A);
			strcpy(data2.video3, A);

			fseek(User_file, 0L, SEEK_END);						
			fseek(User_file, ((count - 1) * sizeof(data2)), SEEK_SET);			
			fwrite(&data2, sizeof(data2), 1, User_file);					

			break;											
		}
	}
}

void Video_Delete(FILE *Video_file) {						//비디오의 정보를 제거하는 함수

	VIDEO data2;											//파일을 읽어와서 비교 후 공백으로 덧씌울 구조체 data2 선언 
	char A[20] = "  ";										//공백으로 만들 (삭제처리) 문자열 배열 A 선언
	char B[10] = "  ";										//공백으로 만들 (삭제처리) 문자열 배열 B 선언
	char search[20];

	int count = 0;											//포인터의 위치를 조정할 변수 count를 선언하고 0으로 초기화

	fseek(Video_file, 0, SEEK_SET);							//포인터의 위치를 파일의 처음으로
	fflush(stdin);											//표준입출력 장치의 버퍼를 비움
	getchar();												//한텀의 쉬는시간(바로 안넘어가게)으로 사용

	printf("삭제할 비디오의 이름을 입력하세요\n\n");		//사용자가 삭제할 사람의 이름을 입력하게 유도
	gets(search);											//그 입력한 이름을 search에 저장

	while (!feof(Video_file)) {								//파일의 끝이 아니면 반복
		fread(&data2, sizeof(data2), 1, Video_file);		//현재 포인터의 위치에서 자료를 읽어서 구조체 data2에 저장.
		count++;											//한번 읽어올때마다 count의 값 1씩 증가
		if (strcmp(data2.name, search) == 0) {			    //data2.name에 search와 같은 내용이있으면 실행

			strcpy(data2.name, A);							//그 구조체.name에 A(공백)를 붙여넣어 이름을 삭제처리를 해준다
			strcpy(data2.number, A);						//동일하게 그 구조체.number에 A(공백)을 붙여넣어 전화번호도 삭제처리한다.
			strcpy(data2.have, B);							//그 읽어온 구조체.have에 B(공백)을 붙여넣어 보유현황도 삭제처리한다.
	
			fseek(Video_file, 0L, SEEK_END);						
			fseek(Video_file, ((count - 1) * sizeof(data2)), SEEK_SET);			
			fwrite(&data2, sizeof(data2), 1, Video_file);				

			break;										
		}
	}
}