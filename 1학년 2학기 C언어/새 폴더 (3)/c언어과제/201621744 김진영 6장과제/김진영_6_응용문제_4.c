#include <stdio.h>

int main(void)
{
	float A,B,C,D,E; //�߰�,�⸻,�⼮,����Ʈ,�ջ� ����

	printf("�߰���� ����, �⸻��� ����, �⼮ ����, ����Ʈ ������ ������� �Է��Ͻÿ�.\n");
	scanf("%f %f %f %f", &A, &B, &C, &D);

	E=A+B+C+D;

	if (A>30||B>30||C>10||D>20)
	{
		printf("�߸��� ���Դϴ�.");
	}
	else
	{
		if (E>=95)
			printf("������ A+�Դϴ�.\n");
		else if (E>=90)
			printf("������ A�Դϴ�.\n");
		else if(E>=85)
			printf("������ B+�Դϴ�.\n");
		else if(E>=80)
			printf("������ B�Դϴ�.\n");
		else if(E>=75)
			printf("������ C+�Դϴ�.\n");
		else if(E>=70)
			printf("������ C�Դϴ�.\n");
		else if(E>=65)
			printf("������ D+�Դϴ�.\n");
		else if(E>=60)
			printf("������ C�Դϴ�.\n");
		else
			printf("������ F�Դϴ�.\n");

		printf("�Էµ� ������\n �߰����: %f��\n �⸻���: %f��\n �⼮:%f��\n ������:%f��\n ����:%f �Դϴ�.",A,B,C,D,E);
	}
	return 0;
}