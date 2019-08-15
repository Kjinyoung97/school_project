#include <string.h> 
#include <stdio.h> 
#include <stdlib.h> 

#define KEY_SIZE    10    
#define TABLE_SIZE    13     
#define equal(e1,e2) (!strcmp(e1.key,e2.key))  
#define empty(e) (strlen(e.key) == 0)


typedef struct
{
	char key[KEY_SIZE];
	char name[20];
	char st_number[20];
	char code[20];
}element;

element hash_table[TABLE_SIZE];

int Trans(char *key)		
{
	int number = 0;
	while (*key)
		number += *key++;
	return number;
}
 
int Hash(char *key)
{
	return Trans(key) % TABLE_SIZE;	
}

void Hash_add(element item, element ht[])
{
	int i, hash_value;

	hash_value = i = Hash(item.key);

	while (!empty(ht[i])) {
		if (equal(item, ht[i])) {
			printf("탐색키 중복\n");
			return;
		}
		i = (i + 1) % TABLE_SIZE;
		if (i == hash_value) {
			printf("테이블 꽉참\n");
			return;
		}
	}
	ht[i] = item;	
}

void Print(element ht[]) {
	int i;
	for (i = 0; i < TABLE_SIZE; i++) {
		printf("[%d]\t",i);
		printf("해시 키 값 : %s\t학과 코드 : %s\t이름 : %s\t학번 : %s\n", ht[i].key, ht[i].code, ht[i].name, ht[i].st_number);

	}
}

void Search(element item, element ht[]) {
	int i, hash_value;
	
	hash_value = i = Hash(item.key);

	while (!empty(ht[i])) {
		if (equal(item, ht[i])) {
			printf("탐색성공. 위치 = %d\n", i);
			printf("해시 키 값 : %s\t학과 코드 : %s\t이름 : %s\t학번 : %s\n", ht[i].key, ht[i].code, ht[i].name, ht[i].st_number);
			return;
		}
		i = (i + 1) % TABLE_SIZE;
		if (i == hash_value) {
			printf("찾는 값이 테이블에 없음.\n");
			return;
		}
	}
	printf("찾는 값이 테이블에 없음.\n");
}

void Delete(element item, element ht[]) {
	int i, hash_value;

	hash_value = i = Hash(item.key);
	while (!empty(ht[i])) {
		if (equal(item, ht[i])) {
			printf("삭제할 값 탐색성공. 위치 = %d\n", i);
			*ht[i].key = NULL;
			*ht[i].code = NULL;
			*ht[i].st_number = NULL;
			*ht[i].name = NULL;
			printf("삭제 완료.\n");
			return;
		}
		i = (i + 1) % TABLE_SIZE;
		if (i == hash_value) {
			printf("찾는 값이 테이블에 없음.\n");
			return;
		}
	}
	printf("찾는 값이 테이블에 없음.\n");
}

int main()
{
	element tmp;
	int Q;
	while (1) {
		printf("\n원하는 연산을 입력하시오(0=입력, 1=삭제, 2=탐색, 3=현재 배열상태 출력, 4=종료) : ");
		scanf("%d", &Q);

		printf("\n\n");
		if (Q == 4) break;
		
		if (Q == 0) {
			printf("해시키값을 입력하십시오. (알파벳 혹은 숫자) \n");
			scanf("%s", tmp.key);
			printf("학번 입력\n");
			scanf("%s", tmp.st_number);
			printf("이름 입력\n");
			scanf("%s", tmp.name);
			printf("학과코드 입력\n");
			scanf("%s", tmp.code);
			Hash_add(tmp, hash_table);
			Print(hash_table);
		}
		else if (Q == 1)
		{ 
			printf("해시키값을 입력하십시오 (알파벳 혹은 숫자) \n");
			scanf("%s", tmp.key);
			Delete(tmp, hash_table);
			Print(hash_table);
		}
		else if (Q == 2)
		{
			printf("해시키값을 입력하십시오\n");
			scanf("%s", tmp.key);
			Search(tmp, hash_table);
		}
		else if (Q == 3)
		{
			Print(hash_table);
		}
		else
			printf("잘못된 입력입니다. 다시 시도하세요.\n");
	}
	return 0;
}