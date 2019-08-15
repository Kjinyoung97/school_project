#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LSN {		//���� ���̺��� ������ ����ü ����
	int data;
	struct LSN *link;
}LSN;
	
typedef struct MEMORY{		//���ڿ��� ������ ����ü ����
	char data[20];			//���ڿ��� �ִ� 20����Ʈ���� ���尡��
}MEMORY;

typedef struct BLOCK{		//�������� ���� ����ü ����
	struct MEMORY MEmory[32];		// ������ �޸� ����ü�� 32�� ���ԵǾ�����.
}BLOCK;

int Secter,block;		//���� ���� ��� ���� ���� ���� ����

LSN *lsn;				//lsn�� ��Ÿ�� ����ü ����
MEMORY *memory;			//�޸� ����ü
LSN *psn;				//psn�� ��Ÿ�� ����ü ����
BLOCK *blo;				//���� ��Ÿ���� ����ü ����	
	
char A[20] = "  ";			//����ó���� ����� ���� ���ڿ� ����
int Write = 0, Erase = 0;	//�б� ���� Ƚ���� �����ϴ� ��������

void init();				//���Ϳ� ����� �����ϰ� �ʱ�ȭ�ϴ� �Լ�
void Flash_read();			//����� �����Ϳ� ���� ���̺��� ����ϴ� �Լ�
void Flash_write();			//�����͸� �����ϴ� �Լ�
void Flash_erase();			//����Ǿ��ִ� �����͸� ����� �Լ�

void init(){

	int size;		//�޸��� ũ�⸦ ���ϴ� ���� ����
	int i,w,j;		

		printf("�޸𸮴� ��MB �Դϱ�? (2MB����)\n");
		scanf("%d", &size);		

		Secter = (size * 1024) / 512;		//MB�� ����Ʈ�� ��ȯ �� ����� ���� �� ����
		block = (Secter / 32 ) +1;			//���͸� 32���� ����� ��� �� ���ϱ�. ���� ��� �ϳ� �߰� ����.

		printf("%d MBũ���� �÷��� �޸� ����\n\n", size);
		printf("������ ���� %d\n", Secter);
		printf("������ ���� ���� %d (���� ��� �ϳ� ����) \n", block);
	
		lsn = (LSN *)malloc(sizeof(LSN)*Secter);		
		psn = (LSN *)malloc(sizeof(LSN)*Secter);
		memory = (MEMORY *)malloc(sizeof(MEMORY));
		blo = (BLOCK *)malloc(sizeof(BLOCK)*block);				//������ �ʿ��� �޸� �����Ҵ�

		for (i = 0; i < Secter; i++) {
			lsn[i].data = 0 + i;					//lsn���̺� �� ����
			psn[i].data = (Secter - 1) - i;			//psn���̺� �� ����

			if (i >=32 ){
				w = i/31;							//������� �������	
				j = i%31;							//w����� ���° ��������
				strcpy(blo[w].MEmory[j].data,A);	//�� �ʱ�ȭ
			}
			else {									//i�� 32�̸��̸� ������ 0��° ����̹Ƿ�
				j = i%31;							//���� ���� �� 
				strcpy(blo[0].MEmory[j].data,A);	//�� �ʱ�ȭ
			}

			lsn[i].link = psn[i].data;				//lsn�� link�� psn�� data�� ����Ű���� ����.


		}
}

void Flash_read() {

	int q, i, j, w,count=0;
	
	for (i = 0; i < Secter; i++) {
		printf("lsn�� �� %d\t psn�� ��%d\t\n", lsn[i].data, psn[i].data);
	}
	for (q = 0; q < Secter; q++) {
		if (q >= 32) {
			w = q / 31;												//������� �������
			j = q % 31;												//w����� ���° ��������
			if (strcmp(blo[w].MEmory[j].data, A) != 0) {			//����� ���Ͽ� ������ �ƴҶ��� ����.
				count++;											//��� Ƚ���� �����ϴ� count ���� 1����
				printf("����� ���ڿ� : %s\n", blo[w].MEmory[j].data);		//��� ����
				printf("lsn %d���� ����� psn %d ��, %d �� �� %d ��° ���Ϳ� ����Ǿ��ֽ��ϴ�.\n", lsn[q].link, q, w, j);
			}
		}
		else {
			j = q % 31;
			if (strcmp(blo[0].MEmory[j].data, A) != 0) {
				count++;
				printf("����� ���ڿ� : %s\n", blo[0].MEmory[j].data);
				printf("lsn %d���� ����� psn %d ��, 0 �� �� %d ��° ���Ϳ� ����Ǿ��ֽ��ϴ�.\n", lsn[q].link, q, j);
			}
		}
	}
	if (count == 0)									//count ������ 0�̸� ��, �ѹ��� ��µ��� �ʾ�����
		printf("\n����� �����Ͱ� �����ϴ�.\n");		
}

void Flash_write (){

	int k,Q,w,j;
	char save[20];

	printf("������ ��ġ(lsn ��ġ)�� �Է��Ͻÿ�.");
	scanf("%d",&k);

	if ((k < 0) || (k >= Secter)) {								//������ ��� ���� �Է��Ͽ��ų� ������ �ƴ� ��� ���� �޼��� ��°� �Բ� ����
		printf("\n\n��ȿ�� ��ġ�� �ƴմϴ�. ���α׷� ����.");
		exit(1);
	}

	printf("������ ���ڿ��� �Է��Ͻÿ�.");
	scanf("%s",&save);

	Q=lsn[k].link;					// = psn[k].data  ���Ḯ��Ʈ�� ���� Q�� ����.

	if (Q >=32 ){
				w = Q/31;		//������� �������
				j = Q%31;		//w����� ���° ��������
				if (strcmp(blo[w].MEmory[j].data, A) != 0) {				//����� ���Ͽ� ������ �ƴϸ� �̹� ����Ǿ� �ִ� �����Ͱ� �ִٴ°��̹Ƿ�
					printf("�̹� ����Ǿ��ִ� �����Ͱ� �ֽ��ϴ�. ������� ����.\n");		//�����޼��� ���.
				}
				else {
					strcpy(blo[w].MEmory[j].data, save);				//�����϶��� ������.
					printf("lsn %d���� ����� psn %d ��, %d �� �� %d ��° ���Ϳ� ����Ǿ����ϴ�.\n", k, Q, w, j);
				}
			}
			else {
				j = Q%31;
				if (strcmp(blo[0].MEmory[j].data, A) != 0) {
					printf("�̹� ����Ǿ��ִ� �����Ͱ� �ֽ��ϴ�. ������� ����.\n");
				}
				else {
					strcpy(blo[0].MEmory[j].data, save);
					printf("lsn %d���� ����� psn %d ��, 0�� �� %d ��° ���Ϳ� ����Ǿ����ϴ�.\n", k, Q, j);
				}
			}
}

void Flash_erase() {

	int k,Q,w,j,u,z;

	printf("\n������ ��ġ(lsn ��ġ)�� �Է��Ͻʽÿ�.");
	scanf("%d", &k);

	if ((k < 0) || (k >= Secter)) {
		printf("\n\n��ȿ�� ��ġ�� �ƴմϴ�. ���α׷� ����.");
		exit(1);
	}
	
	Q = lsn[k].link;

	if (Q >= 32) {
		w = Q / 31;						//������� �������
		j = Q % 31;						//w����� ���° ��������

		if (strcmp(blo[w].MEmory[j].data, A) == 0) {			//�����ϱ��� �̹� �������� �˻�
			printf("\n\n�̹� �����Ͱ� ����ִ� ��ġ�Դϴ�. ���α׷��� �����մϴ�.\n");		//�̹� �����̸� �����޼��� ���. ���α׷� ����
			exit(1);
		}

		printf("\n�ش� ��ġ�� ������ �Ҽ� ���� ����մϴ�.\n");

		printf("\n������ ��ġ�� ������ ������ ���� ��Ͽ� ����\n\n");
		for (u = 0; u < 32; u++) {
			strcpy(blo[block].MEmory[j].data,blo[w].MEmory[j].data);
			printf("%d �� �� %d ��° ���͸� %d�� �� %d ��° ���Ϳ� ���� \n",w, j,block,u);
		}
		
		strcpy(blo[block].MEmory[j].data, A);
		printf("\n������ ��ġ�� �����ϰ� ���� ��Ͽ� �ִ� �����͵��� ������ �� ��ġ�� ����\n\n");
		for (z = 0; z < 32; z++) {
			strcpy(blo[w].MEmory[z].data, blo[block].MEmory[z].data);
			printf("%d �� %d ��° ���͸� %d�� �� %d ��° ���Ϳ� ���� \n", block, z, w, z);

			if (z == 0) printf("\n ���� ����� �����ϰ� ���� ������ ����\n");

			printf("%d�� ��� %d ��° ���� ���� ��\n\n", block, z);
			strcpy(blo[block].MEmory[z].data, A);

			if (z == 31) printf("\n\n�����Ϸ� \n\n");
		}
		printf("\nlsn %d���� ����� psn %d ��, %d �� �� %d ��° ���Ͱ� ����ó���Ǿ����ϴ�.\n", k, Q, w, j);
	}
	else {
		j = Q % 31;

		if (strcmp(blo[0].MEmory[j].data, A) == 0) {
			printf("\n\n�̹� �����Ͱ� ����ִ� ��ġ�Դϴ�. ���α׷��� �����մϴ�.\n");
			exit(1);
		}

		printf("\n������ ��ġ�� ������ ������ ���� ��Ͽ� ����\n\n");


		printf("\n�ش� ��ġ�� ������ �Ҽ� ���� ����մϴ�.\n");

		for (u = 0; u < 32; u++) {
			strcpy(blo[block].MEmory[j].data, blo[0].MEmory[j].data);
			printf("0 �� �� %d ��° ���͸� %d�� �� %d ��° ���Ϳ� ���� \n",  j, block, u);
		}
		strcpy(blo[block].MEmory[j].data, A);
		printf("\n������ ��ġ�� �����ϰ� ���� ��Ͽ� �ִ� �����͵��� ������ �� ��ġ�� ����\n\n");
		for (z = 0; z < 32; z++) {
			strcpy(blo[0].MEmory[z].data, blo[block].MEmory[z].data);
			printf("%d �� %d ��° ���͸� 0�� �� %d ��° ���Ϳ� ���� \n", block, u, z);

			if (z == 0) printf("\n ���� ����� �����ϰ� ���� ������ ����\n");

			printf("%d�� ��� %d ��° ���� ���� ��\n", block, z);
			strcpy(blo[block].MEmory[z].data, A);

			if (z == 31) printf("\n\n�����Ϸ� \n\n");
		}
		printf("lsn %d���� ����� psn %d ��, 0�� �� %d ��° ���Ͱ� ����ó���Ǿ����ϴ�.\n", k, Q, j);

	}

}


void main() {
	int u;

	init();

	while (1) {
		printf("������ ����� �����ϼ���.\t1.���\t2.������ ����\t3.������ ����\t4.���α׷�����\n");
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
			printf("�߸��� ���� �ԷµǾ����ϴ�. �ٽ� �Է��Ͻʽÿ�.");
			break;
		}
	}

}