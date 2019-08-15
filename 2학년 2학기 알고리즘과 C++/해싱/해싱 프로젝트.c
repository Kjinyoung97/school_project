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
			printf("Ž��Ű �ߺ�\n");
			return;
		}
		i = (i + 1) % TABLE_SIZE;
		if (i == hash_value) {
			printf("���̺� ����\n");
			return;
		}
	}
	ht[i] = item;	
}

void Print(element ht[]) {
	int i;
	for (i = 0; i < TABLE_SIZE; i++) {
		printf("[%d]\t",i);
		printf("�ؽ� Ű �� : %s\t�а� �ڵ� : %s\t�̸� : %s\t�й� : %s\n", ht[i].key, ht[i].code, ht[i].name, ht[i].st_number);

	}
}

void Search(element item, element ht[]) {
	int i, hash_value;
	
	hash_value = i = Hash(item.key);

	while (!empty(ht[i])) {
		if (equal(item, ht[i])) {
			printf("Ž������. ��ġ = %d\n", i);
			printf("�ؽ� Ű �� : %s\t�а� �ڵ� : %s\t�̸� : %s\t�й� : %s\n", ht[i].key, ht[i].code, ht[i].name, ht[i].st_number);
			return;
		}
		i = (i + 1) % TABLE_SIZE;
		if (i == hash_value) {
			printf("ã�� ���� ���̺� ����.\n");
			return;
		}
	}
	printf("ã�� ���� ���̺� ����.\n");
}

void Delete(element item, element ht[]) {
	int i, hash_value;

	hash_value = i = Hash(item.key);
	while (!empty(ht[i])) {
		if (equal(item, ht[i])) {
			printf("������ �� Ž������. ��ġ = %d\n", i);
			*ht[i].key = NULL;
			*ht[i].code = NULL;
			*ht[i].st_number = NULL;
			*ht[i].name = NULL;
			printf("���� �Ϸ�.\n");
			return;
		}
		i = (i + 1) % TABLE_SIZE;
		if (i == hash_value) {
			printf("ã�� ���� ���̺� ����.\n");
			return;
		}
	}
	printf("ã�� ���� ���̺� ����.\n");
}

int main()
{
	element tmp;
	int Q;
	while (1) {
		printf("\n���ϴ� ������ �Է��Ͻÿ�(0=�Է�, 1=����, 2=Ž��, 3=���� �迭���� ���, 4=����) : ");
		scanf("%d", &Q);

		printf("\n\n");
		if (Q == 4) break;
		
		if (Q == 0) {
			printf("�ؽ�Ű���� �Է��Ͻʽÿ�. (���ĺ� Ȥ�� ����) \n");
			scanf("%s", tmp.key);
			printf("�й� �Է�\n");
			scanf("%s", tmp.st_number);
			printf("�̸� �Է�\n");
			scanf("%s", tmp.name);
			printf("�а��ڵ� �Է�\n");
			scanf("%s", tmp.code);
			Hash_add(tmp, hash_table);
			Print(hash_table);
		}
		else if (Q == 1)
		{ 
			printf("�ؽ�Ű���� �Է��Ͻʽÿ� (���ĺ� Ȥ�� ����) \n");
			scanf("%s", tmp.key);
			Delete(tmp, hash_table);
			Print(hash_table);
		}
		else if (Q == 2)
		{
			printf("�ؽ�Ű���� �Է��Ͻʽÿ�\n");
			scanf("%s", tmp.key);
			Search(tmp, hash_table);
		}
		else if (Q == 3)
		{
			Print(hash_table);
		}
		else
			printf("�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���.\n");
	}
	return 0;
}