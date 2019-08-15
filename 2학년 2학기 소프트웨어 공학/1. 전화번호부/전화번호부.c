#include <stdio.h>
#include <string.h>
#include <stdlib.h>				

int j,i = 0;					//전역변수 i,j선언
FILE *N_file = NULL;			//파일을 가리키는 포인터
char search[20];				//검색/수정할때 사용할 문자열을 저장할 배열 선언
char RE_name[20];				//수정할때 임시로 문자열을 저장해놓을 배열 선언					
 
typedef struct numberbook {		//구조체 선언
	char name[20];				//이름을 저장
	char number[20];			//전화번호 저장
	char cut_number[300];		//단축번호 저장
}NUMBERBOOK;					//구조체를 새로운 타입 NUMBERBOOK으로 묶음

void Main_Print(int i);				//첫 화면(메뉴모음)을 출력할 함수
void modify_number();				//뭘로 검색하여 수정할지 창을 띄우는 함수
void New_number(FILE *N_file);		//신규번호를 저장하는 함수
void delete_number();				//저장되어있는 번호를 삭제하는 함수
void see_number();					//지금까지 저장되어 있는 번호들을 출력하는 함수
void Name_Modify_Number(FILE *N_file);		//수정할 정보를 이름으로 검색하여 수정하는 함수
void Cut_Modify_Number(FILE *N_file);		//수정할 정보를 단축번호로 검색하여 수정하는 함수
void print_record(NUMBERBOOK);				//이름, 전화번호, 단축번호를 출력하는 함수
void Cut_Delet_Number(FILE *N_file);				//삭제할 정보를 단축번호로 검색하여 삭제하는 함수
void Name_Delete_Number(FILE *N_file);				//삭제할 정보를 이름으로 검색하여 삭제하는 함수

void main() {

	Main_Print(1);								//메인함수에서 메뉴선택을 담당하는 함수를 호출한다.

}

void Main_Print(int i) {
	printf("원하는 메뉴를 선택하세요\n\n");		
	printf("1. 신규 정보 저장\t2. 정보수정\t3. 정보 삭제\t4. 전화번호부 보기\t5. 프로그램종료\n\n");
	scanf_s("%d", &i);							//사용자가 원하는 메뉴를 선택함
	switch (i)									//입력받은 i의 값에 따라 실행
	{
	case 1: 
		New_number(N_file);						//신규정보 저장을 담당하는 함수 호출
		break;									//swithc문 탈출(계속해서 2,3,4번 이후로 진행하지 않게)
	case 2: 
		{
		modify_number();						//수정을 담당하는 함수 호출
		break;}
	case 3: 
		{delete_number();						//삭제를 담당하는 함수 호출
		break;}
	case 4: 
		{
		see_number();							//전체 출력을 담당하는 함수 호출
		break;
		}
	case 5: exit(1);							//프로그램 종료
	default:									//만약 1~5가 아닌 다른 값이 입력될 경우 다시 입력할것을 요구
		printf("========올바른 번호를 다시 선택하세요========\n");		//에러 메세지 출력
		Main_Print(1);							//다시 첫 선택화면을 담당하는 함수 호출
	}
}

void New_number(FILE *N_file) {					//신규 정보를 저장하는 함수

	NUMBERBOOK data;			//입력받아서 저장할 구조체 data선언 
	NUMBERBOOK data2;			//이름이 공백으로 처리 되어있는경우(삭제된경우) 그 위에 덮어쓰는 용도로 사용할 구조체 data2 선언

	int count = 0;				//파일 포인터의 위치를 조정할 변수 count 선언

	fopen_s(&N_file, "N_file.bin", "a+");				//이진파일 오픈. 만약 파일이 없을경우 신규 생성
	if (N_file == NULL) {								//파일 생성 혹은 열기에 실패한 경우 
		puts("입력을 위한 파일을 열 수 없습니다.\n");		//에러메세지 출력
		exit(1);											//프로그램 종료
	}
	else {												//파일 생성 or 열기에 성공한 경우
		puts("전화번호부 구동에 필요한 파일을 생성 or 오픈 했습니다.\n");		//성공 메세지 출력
	}

	fflush(stdin);										//stdin(표준 입출력 장치)버퍼를 비움
	getchar();											
	//안쓰면 이름을 입력할 새도 없이 바로 이름입력하세요 번호입력하세요 동시에 뜨길래 한박자 쉬어가게 넣었습니다

	fseek(N_file, 0, SEEK_SET);							//파일 포인터의 위치를 파일 시작지점으로 옮기고
	fflush(stdin);										//표준 입출력장치의 버퍼를 비운 후
	while (!feof(N_file)) {								//파일의 끝에 도달 할 때 까지 반복하여 
		fread(&data2, sizeof(data2), 1, N_file);		//현재 포인터의 위치에서 읽어서 구조체 data에 저장.
		count++;										//한번 읽어올때마다 count의 값 1씩 증가
		if (strcmp(data2.cut_number, "  ") == 0) {		
			//만약 읽어 온 값(data.name)이 공백 두칸과 동일하다면 (삭제처리가 되었다면) (한칸이 아닌 두칸인 이유는 띄워쓰기와 비교하는것을 방지)

			fclose(N_file);								//추가모드로 연 파일을 닫고

			fopen_s(&N_file, "N_file.bin", "rb+");				//파일을 rb+ (읽고 쓰기 모드)로 오픈
			if (N_file == NULL) {									//파일을 여는데 실패한 경우
				puts("파일 열기 오류");							//에러 메세지 출력 후
				exit(1);										//프로그램 종료
			}

			printf("\n======신규 입력 선택(공백)======\n\n");			//사용자에게 본인이 선택한것이 무엇인지 보여줌

			printf("이름을 입력하세요.\n");						//사용자가 이름을 입력하게 유도
			gets(data.name);									//입력받은것을 data.name에 저장

			printf("휴대폰 번호를 입력하세요\n");				//휴대폰 번호도 입력하게 유도
			gets(data.number);									//번호를 입력받아 data.number에 저장

			printf("설정할 단축번호를 입력하세요.\n");			//단축번호를 입력하게 유도
			gets(data.cut_number);								//입력받은 단축번호를 data.cut_number에 저장


			fseek(N_file, 0L, SEEK_END);							//이진파일의 포인터를 파일의 맨 끝에 위치시키고
			fseek(N_file, ((count - 1) * sizeof(data)), SEEK_SET);	//(카운터의 값 -1) * 구조체의 크기 만큼 포인터를 앞으로 이동시킨다.
			fwrite(&data, sizeof(data), 1, N_file);				//그곳에 아까 입력받은 자료를 저장한 구조체 data를 써넣음. 즉 공백인 곳에 데이터 위에 입력받은 데이터를 덮어 씌움

			fclose(N_file);										//파일 닫기

			Main_Print(1);										//다시 첫화면으로 돌아간다.
		}

		else {													//공백이 두 칸 연속인 곳을 찾지 못한다면 (삭제되어 공백처리 된 데이터가 없다면)
			fclose(N_file);										

			fopen_s(&N_file, "N_file.bin", "rb+");				//파일을 rb+ (읽고 쓰기 추가모드)로 오픈
			if (N_file == NULL) {									//파일을 여는데 실패한 경우
				puts("파일 열기 오류");							//에러 메세지 출력 후
				exit(1);										//프로그램 종료
			}

			printf("\n======신규 입력 선택(파일 맨 뒤 추가)======\n\n");
			//사용자에게 본인이 선택한것이 무엇인지 보여줌

			printf("이름을 입력하세요.\n");						//사용자가 이름을 입력하게 유도
			gets(data.name);									//입력받은것을 data.name에 저장

			printf("휴대폰 번호를 입력하세요\n");				//휴대폰 번호도 입력하게 유도
			gets(data.number);									//번호를 입력받아 data.number에 저장

			printf("설정할 단축번호를 입력하세요.\n");			//단축번호를 입력하게 유도
			gets(data.cut_number);								//입력받은 단축번호를 data.cut_number에 저장


			fseek(N_file, 0, SEEK_END);							//이진파일의 포인터를 파일의 맨 끝에 위치시키고
			fwrite(&data, sizeof(data), 1, N_file);				//그곳에 아까 입력받은 자료를 저장한 구조체 data를 써넣음

			fclose(N_file);										//파일 닫기

			Main_Print(1);										//다시 첫화면으로 돌아간다.
		}
	}
}


void modify_number() {									//수정을 담당하는 함수
	printf("\n======정보 수정 선택======\n\n");			//사용자가 무엇을 선택하였는지 사용자에게 보여줌

	fopen_s(&N_file, "N_file.bin", "rb+");				//파일을 rb+ (읽고 쓰기 추가모드)로 오픈
	if(N_file==NULL) {									//파일을 여는데 실패한 경우
		puts("파일 열기 오류");							//에러 메세지 출력 후
		exit(1);										//프로그램 종료
	}

	printf("1. 이름으로 찾기\n2.단축번호로 찾기\n3. 메인화면으로\n\n");		//사용자가 무엇으로 검색하여 수정할지 선택권을 부여
	scanf_s("%d", &j);														//사용자가 선택한 값을 저장하여 

	switch (j)											//switch문으로 선택한 값에 따라 적당 함수를 호출한다
	{
	case 1:												//1을 선택한 경우
		Name_Modify_Number(N_file);						//이름으로 찾아 수정하는 함수를 호출한다
		Main_Print(1);									//이름으로 수정하는 함수가 끝날경우 첫 화면으로 다시 돌아간다.
	case 2 :											//2를 선택한 경우
		Cut_Modify_Number(N_file);						//단축번호로 찾아 수정하는 함수를 호출한다.
		Main_Print(1);									//단축번호로 수정하는 함수가 끝난 경우 다시 척 화면으로 동라간다.
	case 3: Main_Print(1);								//3을 선택한 경우 다시 메인화면으로 돌아간다(잘못 선택한 경우)
	default:											//1~3 이외의 값을 입력 한경우
		printf("번호 입력 오류 다시 입력하세요\n\n");		//에러 메세지를 출력한다.
		fclose(N_file);										//열려있는 파일을 닫고
		modify_number();									//자기 자신을 다시 호출하여 재입력하게 한다.
		}
}

void delete_number() {										//삭제를 담당하는 함수를 호출한다.
	printf("\n======정보 삭제 선택======\n\n");				//사용자에게 사용자가 무엇을 선택했는지 보여준다.

	fopen_s(&N_file, "N_file.bin", "rb+");					//파일을 rb+(읽고 쓰기 추가모드)로 연다.
	if (N_file == NULL) {									//파일이 제대로 열리지 않은 경우
		puts("파일 열기 오류");								//에러메세지를 출력하고 
		exit(1);											//프로그램을 종료한다.
	}

	printf("1. 이름으로 찾기\n2.단축번호로 찾기\n3. 메인화면으로\n\n");		//사용자에게 무엇으로 찾아서 삭제할지 선택권 부여
	scanf_s("%d", &j);														//사용자가 선택한걸 변수 j에 저장
	
	switch (j)											//입력받은 j 값으로 switch문 작동
	{	
	case 1:												//j값이 1일 경우
		Name_Delete_Number(N_file);						//이름으로 검색하여 삭제하는 함수 호출
		Main_Print(1);									//이름으로 삭제하는 함수가 끝나면 첫화면으로 돌려보냄
	case 2:												//j값이 2인 경우
		Cut_Delet_Number(N_file);						//단축번호로 검색하여 삭제하는 함수 호출
		Main_Print(1);									//단축번호로 삭제하는 함수가 끝나면 첫화면으로 돌려보냄
	case 3: Main_Print(1);								//j값이 3일 경우 첫화면으로 돌려보냄
	default:												//1~3외의 다른 값이 입력된다면
		printf("번호 입력 오류 다시 입력하세요");			//에러메세지를 출력한 후
		fclose(N_file);										//열려있는 파일을 닫고
		delete_number();									//자기 자신의 함수를 다시 호출하여 다시 선택하게 한다.
	}
}

void Cut_Delet_Number(FILE *N_file) {				//단축번호로 검색하여 삭제하는 함수
		
	NUMBERBOOK data2;								//파일을 읽어와서 비교 후 공백으로 덧씌울 구조체 data2 선언 

	char A[20] = "  ";								//이름과 전화번호를 공백으로 만들(삭제처리) 문자열 배열 A 선언
	char B[300] = "  ";								//단축번호를 공백으로 만들(삭제처리) 문자열 배열 B 선언

	int count = 0;									//포인터의 위치를 조정할 변수 count를 선언하고 0으로 초기화

	fseek(N_file, 0, SEEK_SET);						//포인터의 위치를 파일의 처음으로
	fflush(stdin);									//표준입출력 장치의 버퍼를 비움
	getchar();										//한텀의 쉬는시간(바로 안넘어가게)으로 사용

	printf("삭제할 사람의 단축번호를 입력하세요\n\n");		//삭제할 사람의 단축번호를 입력받음
	gets(search);											//입력받은것을 search변수에 저장


	while (!feof(N_file)) {									//파일의 끝이 아니면 반복
		fread(&data2, sizeof(data2), 1, N_file);			//현재 포인터의 위치에서 자료를 읽어서 구조체 data2에 저장.
		count++;											//한번 읽어올때마다 count의 값 1씩 증가
		if (strcmp(data2.cut_number, search) == 0) {		//data2.cut_nunber에 search와 같은 내용이있으면 실행
			print_record(data2);							//search와 같은 내용이 있는 그 구조체를 출력하고

			strcpy(data2.name,A);							//그 구조체.name에 A(공백)를 붙여넣어 이름을 삭제처리를 해준다
			strcpy(data2.number,A);							//동일하게 그 구조체.number에 A(공백)을 붙여넣어 전화번호도 삭제처리한다.
			strcpy(data2.cut_number,B);						//그 읽어온 구조체.cut_number에 B(공백)을 붙여넣어 단축번호도 삭제처리한다.

			fseek(N_file,0L,SEEK_END);						//파일 포인터의 위치를 파일 맨 끝으로 이동시키고
			fseek(N_file,((count-1) * sizeof(data2)),SEEK_SET);		//증가한 count값의 -1 만큼 구조체(data2)의 크기에 곱한 후 그 만큼 포인터를 앞으로 이동시킨다
			fwrite(&data2, sizeof(data2), 1, N_file);		//전부 공백처리로 삭제처리된 data2를 그 위치에 써넣는다. 그 위치는 삭제할 데이터가 있던 위치이다.

			break;											//반복을 종료한다.
		}
	}
		fclose(N_file);										//파일을 닫는다.
}

void Name_Delete_Number(FILE *N_file) {						//이름으로 검색하여 삭제하는 함수

	NUMBERBOOK data2;										//파일을 읽어와서 비교 후 공백으로 덧씌울 구조체 data2 선언 
	char A[20] = "  ";										//이름과 전화번호를 공백으로 만들 (삭제처리) 문자열 배열 A 선언
	char B[300] = "  ";										//단축번호를 공백으로 만들(삭제처리) 문자열 배열 B 선언

	int count = 0;											//포인터의 위치를 조정할 변수 count를 선언하고 0으로 초기화

	fseek(N_file, 0, SEEK_SET);								//포인터의 위치를 파일의 처음으로
	fflush(stdin);											//표준입출력 장치의 버퍼를 비움
	getchar();												//한텀의 쉬는시간(바로 안넘어가게)으로 사용
		
	printf("삭제할 사람의 이름을 입력하세요\n\n");			//사용자가 삭제할 사람의 이름을 입력하게 유도
	gets(search);											//그 입력한 이름을 search에 저장
		
	while (!feof(N_file)) {									//파일의 끝이 아니면 반복
		fread(&data2, sizeof(data2), 1, N_file);			//현재 포인터의 위치에서 자료를 읽어서 구조체 data2에 저장.
		count++;											//한번 읽어올때마다 count의 값 1씩 증가
		if (strcmp(data2.name, search) == 0) {			    //data2.name에 search와 같은 내용이있으면 실행
			print_record(data2);							//그 동일한 내용이 있는 부분의 읽어온 구조체를 출력

			strcpy(data2.name,A);							//그 구조체.name에 A(공백)를 붙여넣어 이름을 삭제처리를 해준다
			strcpy(data2.number,A);							//동일하게 그 구조체.number에 A(공백)을 붙여넣어 전화번호도 삭제처리한다.
			strcpy(data2.cut_number,B);						//그 읽어온 구조체.cut_number에 B(공백)을 붙여넣어 단축번호도 삭제처리한다.

			fseek(N_file,0L,SEEK_END);						//파일 포인터의 위치를 파일 맨 끝으로 이동시키고
			fseek(N_file,((count-1) * sizeof(data2)),SEEK_SET);			//증가한 count값의 -1 만큼 구조체(data2)의 크기에 곱한 후 그 만큼 포인터를 앞으로 이동시킨다
			fwrite(&data2, sizeof(data2), 1, N_file);					//전부 공백처리로 삭제처리된 data2를 그 위치에 써넣는다.  그 위치는 삭제할 데이터가 있던 위치이다.
						
			break;											//반복을 종료한다.
		}
	}
		fclose(N_file);										//파일을 닫는다
}

void see_number() {											//지금까지 저장되어 있는 자료를 출력하는 함수
	NUMBERBOOK data3;										//출력하는데 파일에서 구조체를 읽어와서 그 구조체를 저장할 data3 선언

	int count = 0;											//몇번 출력이 이루어 졌는지 검사할 변수 count 출력

	fopen_s(&N_file, "N_file.bin", "rb");					//파일을 읽기모드로 오픈
	if(N_file==NULL) {										//파일을 여는데 실패했다면
	puts("파일 열기 오류");									//에러 메세지 출력
	exit(1);												//프로그램 종료
	}

	printf("\n=====전화번호부 보기 선택======\n\n");		//사용자가 무엇을 선택하였는지 보여줌
	
	fseek(N_file, 0, SEEK_SET);								//포인터의 위치를 파일의시작지점으로 옮김
		
	while(fread(&data3, sizeof(data3), 1, N_file)){			//파일내에서 읽어오는 동안 계속 반복
		if (!strcmp(data3.name, "  ") == 0) {				//data3.name과 "  " (공백두칸)(=삭제된 데이터)을 비교하여 같지 않다면 실행 
			print_record(data3);							//읽어온 구조체 data3를 출력
			count++;										//출력한번당 count값을 1씩 증가
		}
		if (SEEK_END == 1) break;							//만약 포인터의 위치가 파일의 끝이면 반복 종료
	}
	if (count == 0) printf("출력할 파일이 없습니다.\n\n");		
	//만약 count의 값이 1도 증가하지않았다면, 즉 전부 공백이거나 저장된 데이터가없다면 출력할 것이 없다는 메세지 출력
	
	fclose(N_file);		//파일 닫기

	Main_Print(1);		//처음화면으로 돌아감.

}

void print_record(NUMBERBOOK data) {			//구조체 data의 출력을 담당하는 함수
	printf("이름 %s\t전화번호 %s\t단축번호 %s\n\n", data.name, data.number, data.cut_number);
	//data에 저장된 각각의 정보들을 출력함.
}

void Name_Modify_Number(FILE *N_file) {				//이름으로 검색하여 수정하는 함수
		
	NUMBERBOOK data2;								//파일을 읽어와서 자료를 저장하고 , 이후 수정할 때 사용할 구조체 data2 선언

	int count=0;									//파일 포인터의 위치를 조정할 때 사용할 변수 count 선언

	fseek(N_file, 0, SEEK_SET);						//파일 포인터의 위치를 파일의 시작지점으로 이동시킴
	fflush(stdin);									//표준입출력장치의 버퍼를 비움
	getchar();										//한텀 쉬어가는 용도로 사용

	printf("수정할 사람의 이름을 입력하세요\n\n");		//사용자에게 수정할 사람의 이름을 입력받음
	gets(search);										//입력받은 값을 search에 저장

	while (!feof(N_file)) {								//파일의 끝이 아니면 반복
		fread(&data2, sizeof(data2), 1, N_file);		//현재 포인터의 위치에서 자료를 읽어서 구조체 data2에 저장.
		count++;										//한번 읽어서 저장할 때마다 count의 값 1씩 증가
		if (strcmp(data2.name, search) == 0) {			//data2.name에 search와 같은 내용이있으면 실행
		print_record(data2);							//data2에 저장된 자료들을 한번 출력

		printf("바꿀 이름을 입력하세요\n\n");			//사용자에게 바꿀 이름을 입력받음
		gets(RE_name);									//그 입력받은 자료를 RE_name에 저장한 후
			
		strcpy(data2.name,RE_name);						//RE_name의 값을 data2.name에 복사함.

		fflush(stdin);									//표준 입출력 장치의 버퍼를 비우고
		printf("바꿀 번호를 입력하세요 \n\n");			//바꿀 번호또한 입력받음
		gets(RE_name);									//그 입력받은 번호를 RE_name에 저장하고

		strcpy(data2.number,RE_name);					//RE_name의 값을 data2.number로 복사함

		fflush(stdin);									//다시 표준 입출력 장치의 버퍼를 비우고
		printf("바꿀 단축번호를 입력하세요 \n\n");		//이번엔 변경할 단축번호를 입력받음
		gets(RE_name);									//입력받은 값을 RE_name에 저장하고
			
		strcpy(data2.cut_number,RE_name);				//RE_name의 값을 data2.cut_number에 복사한다.

			
		fseek(N_file,0L,SEEK_END);						//포인터의 위치를 파일의 끝으로 보낸 후
		fseek(N_file,((count-1) * sizeof(data2)),SEEK_SET);		//증가한 count -1 값에 구조체 data2 크기만큼 곱하여 그 값만큼 포인터를 앞으로 이동시킨다
		fwrite(&data2, sizeof(data2), 1, N_file);		//그 위치에 data2의 값을 덮어씌운다. 그 위치는 수정할 데이터가 있던 위치이다.
		
		break;		//반복문 이탈
		}
	}
	fclose(N_file);		//파일 닫기
}

void Cut_Modify_Number(FILE *N_file){			//단축번호로 검색하여 정보를 수정하는 함수

	NUMBERBOOK data2;							//파일을 읽어와서 자료를 저장하고 , 이후 수정할 때 사용할 구조체 data2 선언

	int count = 0;								//파일 포인터의 위치를 조정할 때 사용할 변수 count 선언
		
	fflush(stdin);								//표준입출력장치의 버퍼를 비움
	getchar();									//한텀 쉬어가는 용도로 사용

	printf("수정할 사람의 단축번호을 입력하세요\n\n");			//사용자에게 수정할 사람의 단축번호를 입력받음
	gets(search);												//입력받은 값을 search에 저장

	fseek(N_file, 0, SEEK_SET);					//포인터의 위치를 파일의 시작지점으로 이동시킴
	while (!feof(N_file)) {						//파일의 끝이 아니라면 반복
		fread(&data2, sizeof(data2), 1, N_file);			//현재 포인터의 위치에서 자료를 읽어서 구조체 data2에 저장.
		count++;											//자료를 한번씩 읽어 올때마다 count의 값을 1씩 증가 
		if (strcmp(data2.cut_number, search) == 0) {		//data2.cut_number에 search와 같은 내용이있으면 실행
		print_record(data2);								//그 동일한 내용이 있는 부분의 구조체 data2를 출력

		printf("바꿀 이름을 입력하세요\n\n");			//사용자에게 바꿀 이름을 입력받음
		gets(RE_name);									//그 입력받은 자료를 RE_name에 저장한 후

		strcpy(data2.name, RE_name);					//RE_name의 값을 data2.name에 복사함.

		fflush(stdin);									//표준 입출력 장치의 버퍼를 비우고
		printf("바꿀 번호를 입력하세요 \n\n");			//바꿀 번호또한 입력받음
		gets(RE_name);									//그 입력받은 번호를 RE_name에 저장하고

		strcpy(data2.number, RE_name);					//RE_name의 값을 data2.number로 복사함

		fflush(stdin);									//다시 표준 입출력 장치의 버퍼를 비우고
		printf("바꿀 단축번호를 입력하세요 \n\n");		//이번엔 변경할 단축번호를 입력받음
		gets(RE_name);									//입력받은 값을 RE_name에 저장하고

		strcpy(data2.cut_number, RE_name);				//RE_name의 값을 data2.cut_number에 복사한다.

			
		fseek(N_file, 0L, SEEK_END);						//포인터의 위치를 파일의 끝으로 보낸 후
		fseek(N_file, ((count - 1) * sizeof(data2)), SEEK_SET);		//증가한 count -1 값에 구조체 data2 크기만큼 곱하여 그 값만큼 포인터를 앞으로 이동시킨다
		fwrite(&data2, sizeof(data2), 1, N_file);		//그 위치에 data2의 값을 덮어씌운다. 그 위치는 수정할 데이터가 있던 위치이다.

		break;		//반복문 이탈
		}
	}
	fclose(N_file);		//파일 닫기
}