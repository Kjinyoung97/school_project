#include <stdio.h>
#include <string.h>
#include <stdlib.h>				

int j,i = 0;					//전역변수 i,j선언
FILE *N_file = NULL;			//파일을 가리키는 포인터
char search[20];				//검색할때 사용할 문자열을 저장할 배열 선언
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

	/* 원래 이름이 공백처리(삭제된 경우)되어 있을 경우 그곳에 데이터를 덮어 씌우는 방식으로 하려했으나 
	이진파일을 w(덮어쓰기) 방식으로 열게 될 경우 공백처리된 부분 뿐만 아니라 그 이후의 저장되어있는 데이터까지 전부
	삭제처리되어 a+로 열어 무조건 아래에 추가하는 방식으로 진행되었습니다. 공백을 검사하여 그 부분에 데이터를
	넣는것까지 성공했으나 그 뒷두부분까지 전부 파일 하나로 취급되어 덮어씌워지기에 그 기능을 삭제했습니다.*/

	NUMBERBOOK data;			//입력받아서 저장할 구조체 data선언 
	NUMBERBOOK data2;

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

	printf("\n======신규 입력 선택======\n\n");			//사용자에게 본인이 선택한것이 무엇인지 보여줌

	printf("이름을 입력하세요.\n");						//사용자가 이름을 입력하게 유도
	gets(data.name);									//입력받은것을 data.name에 저장

	printf("휴대폰 번호를 입력하세요\n");				//휴대폰 번호도 입력하게 유도
	gets(data.number);									//번호를 입력받아 data.number에 저장

	printf("설정할 단축번호를 입력하세요.");			//단축번호를 입력하게 유도
	gets(data.cut_number);								//입력받은 단축번호를 data.cut_number에 저장


	fseek(N_file, 0, SEEK_END);							//이진파일의 포인터를 파일의 맨 끝에 위치시키고
	fwrite(&data, sizeof(data), 1, N_file);				//그곳에 아까 입력받은 자료를 저장한 구조체 data를 써넣음

	fclose(N_file);										//파일 닫기

	Main_Print(1);										//다시 첫화면으로 돌아간다.
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
		
	NUMBERBOOK data2;								//파일을 읽어와서 비교 후 덧씌울 

	char A[20] = "  ";
	char B[300] = "  ";

	int count = 0;

	fseek(N_file, 0, SEEK_SET);
	fflush(stdin);
	getchar();

	printf("삭제할 사람의 단축번호를 입력하세요\n\n");
	gets(search);

	fseek(N_file, 0, SEEK_SET);
	fflush(stdin);
	while (!feof(N_file)) {
		fread(&data2, sizeof(data2), 1, N_file);		//현재 위치에서 읽어서 구조체 data에 저장.
		count++;
		if (strcmp(data2.cut_number, search) == 0) {			//data.name에 search와 같은 내용이있으면 실행
			print_record(data2);

			strcpy(data2.name,A);
			strcpy(data2.number,A);
			strcpy(data2.cut_number,B);

			fseek(N_file,0L,SEEK_END);
			fseek(N_file,((count-1) * sizeof(data2)),SEEK_SET);
			fwrite(&data2, sizeof(data2), 1, N_file);

			break;
		}
	}
		fclose(N_file);
}

void Name_Delete_Number(FILE *N_file) {

	NUMBERBOOK data2;
	char A[20] = "  ";
	char B[300] = "  ";

	int count = 0;

	fseek(N_file, 0, SEEK_SET);
	fflush(stdin);
	getchar();

	printf("삭제할 사람의 이름을 입력하세요\n\n");
	gets(search);

	fseek(N_file, 0, SEEK_SET);
	fflush(stdin);
	while (!feof(N_file)) {
		fread(&data2, sizeof(data2), 1, N_file);		//현재 위치에서 읽어서 구조체 data에 저장.
		count++;
		if (strcmp(data2.name, search) == 0) {			//data.name에 search와 같은 내용이있으면 실행
			print_record(data2);

			strcpy(data2.name,A);
			strcpy(data2.number,A);
			strcpy(data2.cut_number,B);

			fseek(N_file,0L,SEEK_END);
			fseek(N_file,((count-1) * sizeof(data2)),SEEK_SET);
			fwrite(&data2, sizeof(data2), 1, N_file);

			break;
		}
	}
		fclose(N_file);
}

void see_number() {
	NUMBERBOOK data3;

	int count = 0;

	fopen_s(&N_file, "N_file.bin", "r");
	if(N_file==NULL) {
	puts("파일 열기 오류");
	exit(1);
	}

	printf("\n=====전화번호부 보기 선택======\n\n");
	
	fseek(N_file, 0, SEEK_SET);

	while(fread(&data3, sizeof(data3), 1, N_file)){
		if (!strcmp(data3.name, "  ") == 0) {
			print_record(data3);
			count++;
		}
		if (SEEK_END == 1) break;
	}
	if (count == 0) printf("출력할 파일이 없습니다.\n\n");
	
	fclose(N_file);

	Main_Print(1);

}

void print_record(NUMBERBOOK data) {
	printf("이름 %s\t전화번호 %s\t단축번호 %s\n\n", data.name, data.number, data.cut_number);
}

void Name_Modify_Number(FILE *N_file) {

	NUMBERBOOK data2;

	int count=0;

	fseek(N_file, 0, SEEK_SET);
	fflush(stdin);
	getchar();

	printf("수정할 사람의 이름을 입력하세요\n\n");
	gets(search);

	fseek(N_file, 0, SEEK_SET);
	fflush(stdin);
	while (!feof(N_file)) {
		fread(&data2, sizeof(data2), 1, N_file);		//현재 위치에서 읽어서 구조체 data에 저장.
		count++;
		if (strcmp(data2.name, search) == 0) {		   //data.name에 search와 같은 내용이있으면 실행
		print_record(data2);

		printf("바꿀 이름을 입력하세요\n\n");
		gets(RE_name);

		strcpy(data2.name,RE_name);

		fflush(stdin);
		printf("바꿀 번호를 입력하세요 \n\n");
		gets(RE_name);

		strcpy(data2.number,RE_name);

		fflush(stdin);
		printf("바꿀 단축번호를 입력하세요 \n\n");
		gets(RE_name);

		strcpy(data2.cut_number,RE_name);

			
		fseek(N_file,0L,SEEK_END);
		fseek(N_file,((count-1) * sizeof(data2)),SEEK_SET);
		fwrite(&data2, sizeof(data2), 1, N_file);
		
		break;		//반복문 이탈
		}
	}
	fclose(N_file);
}

void Cut_Modify_Number(FILE *N_file){

	NUMBERBOOK data2;

	int count = 0;

	fflush(stdin);
	getchar();

	printf("수정할 사람의 단축번호을 입력하세요\n\n");
	gets(search);

	fseek(N_file, 0, SEEK_SET);
	fflush(stdin);
	while (!feof(N_file)) {
		fread(&data2, sizeof(data2), 1, N_file);			//읽어서 구조체 data에 저장.
		count++;
		if (strcmp(data2.cut_number, search) == 0) {		//data.cut_number에 search와 같은 내용이있으면 실행
		print_record(data2);

		printf("바꿀 이름을 입력하세요\n\n");
		gets(RE_name);

		strcpy(data2.name,RE_name);

		fflush(stdin);
		printf("바꿀 번호를 입력하세요 \n\n");
		gets(RE_name);

		strcpy(data2.number,RE_name);

		fflush(stdin);
		printf("바꿀 단축번호를 입력하세요 \n\n");
		gets(RE_name);

		strcpy(data2.cut_number,RE_name);

			
		fseek(N_file,0L,SEEK_END);
		fseek(N_file,((count-1) * sizeof(data2)),SEEK_SET);
		fwrite(&data2, sizeof(data2), 1, N_file);
		
		break;		//반복문 이탈
		}
	}
	fclose(N_file);
}