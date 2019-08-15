#include <iostream>
using namespace std;
#include <time.h>
#include <stdlib.h>
#include "sort.h"

void SelectionSort(int a[], int N);
void ImpBubbleSort(int a[], int N);
void InsertionSort(int a[], int N);
void ShellSort(int a[], int N);
void QuickSort(int a[], int l, int r); 
void CheckSort2(int a[], int n);
void MergeSort(int a[], int l, int r);
void heapify(int a[], int h, int m);
void HeapSort(int a[], int n);
void CountingSort(int a[], int n, int m);
int digit(int d, int k);
class Queue;
void RadixSort(int a[], int n, int m, Queue q[]);

const int N = 10;
const int M = 1;
int b[N + 1];

void main() {
	int i, a[N+1],select;
	Queue *Q[10];

	cout << "\n\n\t\t=======  10���� ���� ����  ======= \n" << endl;
	for (i = 1; i <= N; i++) {
		a[i] = rand() % 100;

		cout << a[i] << "\t";
	}
	cout << "\n\n";

	cout << "\t\t=======  � ������ ����ұ��  =======\n" << endl;
	cout << "\t\t1. ��������\t2. ��������\t3. ��������\n\t\t4. ������\t5. ������\t6. �պ�����\n\t\t7. ��������\t8. �������\t9. �������\n" << endl;

	scanf_s("%d", &select);

	switch (select)
	{
	default:
		cout << "�ٽ� �Է��Ͻÿ�\n"<<endl;
		main();

	case 1:
		cout << "�������� �Լ� ȣ��\n" <<endl;
		SelectionSort(a,N);
		break;

	case 2 :
		cout << "�������� �Լ� ȣ��\n" << endl;
		ImpBubbleSort(a, N);
		break;

	case 3:
		cout << "�������� �Լ� ȣ��\n" << endl;
		InsertionSort(a, N);
		break;

	case 4:
		cout << "�� ���� �Լ� ȣ��\n" << endl;
		ShellSort(a, N);
		break;

	case 5:
		cout << "�� ���� �Լ� ȣ��\n" << endl;
		QuickSort(a, 1, N);
		CheckSort2(a, N);
		break;

	case 6:
		cout << "�պ����� �Լ� ȣ��\n" << endl;
		MergeSort(a, 1, N);
		CheckSort2(a, N);
		break;

	case 7:
		cout << "�������� �Լ� ȣ��\n" << endl;
		HeapSort(a, N);
		CheckSort2(a, N);
		break;

	case 8 :
		cout << "������� �Լ� ȣ��\n" << endl;
		CountingSort(a, N, M);
		CheckSort2(a, N);
		break;

	case 9:
		cout << "������� �Լ� ȣ��\n" << endl;
		RadixSort(a, N, M, *Q);
		CheckSort2(a, N);
		break;
	}
	system("pause");
}

void SelectionSort(int a[], int N) {
	int i, j, min;
	for (i = 1; i <= N; i++) {
		min = i;
		for (j = i + 1; j <= N; j++) {
			if (a[j] < a[min]) min = j;
			cout << "���� �迭�˻��߿��� ���� ���� ��"<< a[min] << "\n";
		}
		swap(a, min, i);
		cout << "�������� ���� �Ϸ� �� ��" << a[i] << endl;
	}
	cout << "\n\n\t\t\t========���ĿϷ�=======" << endl;
	for (i = 1; i <= N; i++) {
		cout << a[i] << "\t";
	}
	cout << "\n\n";

}

void ImpBubbleSort(int a[], int N) {
	int u = 1, exchpos, lastpos;
	exchpos = N;
	do { 
		lastpos = exchpos;
		for (int j = N ; j > 0; j--)				//j�� N���� �����Ͽ� 1�� ���ҽ�Ű�� �ݺ��Ѵ�.
			if (a[j -1] > a[j]) {					//a[j]���� a[j-1]�� Ŭ ��� �� ���� �ٲ۴�.
				cout << "�ڸ��� ����� �� ��\t" << a[j -1] << "\t" << a[j] << endl;
				swap(a[j], a[j - 1]);
				exchpos = j-1 ;
				cout << "exchpos = " << exchpos << endl;
				cout << "lastpos = " << lastpos << endl;
			}
		cout << "exchpos = " << exchpos << endl;
		cout << "lastpos = " << lastpos << endl;
		cout << "\n ���� �迭��"<<u<<"��° �ڸ��� �ִ� ��" << endl;
		cout << a[u] << "\n";
		u++;
	} while ((u <= N)&&((exchpos==lastpos)==0));

	cout << "\n\n\t\t\t========���ĿϷ�=======" << endl;
	for (int i = 1; i <= N; i++) {
		cout << a[i] << "\t";
	}
	cout << "\n\n";

}


void InsertionSort(int a[], int N) {
	int i, j;
	for (i = 2; i <= N; i++) {
		a[0] = a[i];			//�Ⱦ��� a[0]�� a[i]�� ����
		j = i;					//j�� i�� ����
		while (a[j - 1]>a[0]) {					//a[j-1]�� ����� a[0]���� ũ�� 
			a[j] = a[j - 1];					//a[j]�� a[j-1]�� �����ϰ�
			j--;								//j���� �ϳ� ���δ�.
		}
		a[j] = a[0];			//a[0]�� ����Ǿ��ִ� ���� a[j]�� ����
		cout << "�̹� �ݺ����� ���� �Ϸ� �� ��\t" <<"[ "<< a[j] <<" ]\n"<< endl;
		cout << "���� \t" << i <<"��° ĭ���� ���ĿϷ� "<< endl;
		for (int k = 1; k <= N; k++) {
			cout << a[k] << "\t";
		}
		cout << "\n\n";
	}
	cout << "\n\n\t\t\t========���ĿϷ�=======" << endl;
	for (int i = 1; i <= N; i++) {
		cout << a[i] << "\t";
	}
	cout << "\n\n";

}

void ShellSort(int a[], int N) {
	int i, j, h,k=1,count = 1;
	for (h = 1; h <= N; h = 3 * h + 1) ;
		for (; h > 0; h /= 3){
						if(h>N) continue;
			cout << "���� �������� ����(h)�� " << h << "�� ��\n" << endl;
			for (i = h + 1; i <= N; i++) {
				a[0] = a[i];
				j = i;
				while (j > h&&a[j - h] > a[0]) {
					a[j] = a[j - h];
					j -= h;
				}
				a[j] = a[0];
				cout<<"���� ���� �� ��\t"<< a[i] << endl;
			}
			cout <<"\n\n h�� ���� " << h << "�϶� ���ݱ��� ���ĵȰ� " << endl;
				for (int z = 1; z <= N; z++) {
		cout << a[z] << "\t";
	}
				cout << "\n"<<endl;
		}
	cout << "\n\n\t\t\t========���ĿϷ�=======" << endl;
	for (int z = 1; z <= N; z++) {
	cout << a[z] << "\t";
	}
	cout << "\n\n";
}

void QuickSort(int a[], int l, int r) {
	int i, j, v;
	if (r > l) {
		v = a[r];
		i = l - 1;
		j = r;
		for (; ;) {
			while (a[++i] < v);
			while (a[--j] > v);
			if (i >= j) break;
			swap(a, i, j);
			cout << "��ȯ�� �� �� \t" << a[i] << "\t" << a[j] << endl;
		}
		cout << i << "��° �迭 ���ĿϷ� \n" << i << "��° �迭�� ����" << a[i] << "\n"<< endl;
		swap(a, i, r);
		QuickSort(a, l, i - 1);
		QuickSort(a, i + 1, r);
	}
}

void CheckSort2(int a[], int n) {
	int i, Sorted;
	Sorted = TRUE;
	for (i = 1; i < n; i++) {
		if (a[i] > a[i + 1]) Sorted = FALSE;
	}
	if (Sorted){
	cout << "\n\n\t\t\t========���ĿϷ�=======" << endl;
	for (int z = 1; z <= N; z++) {
		cout << a[z] << "\t";
	}
	}
}

void MergeSort(int a[], int l, int r) {
	int i, j, k, m;
	if (r > l) {
		m = (r + l) / 2;
		MergeSort(a, l, m);
		MergeSort(a, m + 1, r);
		for (i = m + 1; i > l; i--) b[i - 1] = a[i - 1];
		for (j = m; j < r; j++) b[r + m - j] = a[j + 1];
		for (k = l; k <= r; k++) {
			a[k] = (b[i] < b[j]) ? b[i++] : b[j--];
			cout << "���� " << k << "��° ����� �迭" << a[k] << endl;
		}
		cout << "���� ��ȯ ���� �� ���� ����� �迭" << endl;
		cout << "\n\n" << endl;
	}
}

void heapify(int a[], int h, int m) {
	int j, v;
	v = a[h];
	for (j = 2 * h; j <= m; j *= 2) {
		if (j < m && a[j] < a[j + 1]) j++;
		if (v >= a[j]) break;
		else a[j / 2] = a[j];
	}
	a[j / 2] = v;
}

void HeapSort(int a[], int n) {
	int i;
	for (i = n / 2; i >= 1; i--)
		heapify(a, i, n);
	cout << "�ְ� �� �����Ϸ� " << a[1] << endl;
	for (i = n - 1; i >= 1; i--) {
		swap(a, 1, i + 1);
		cout << "�ְ��� ���� ������ ���� ����" << i + 1 << " ��° �迭�� �� " << endl;
		heapify(a, 1, i);
		cout << "������ �� �ִ밪" << a[1] << " ��/�� �迭 ù��° ĭ, �� �ֻ��� ���� ����\t" << endl;
		cout << "\t\t========���� �迭 ���� ����========= " << endl;
		for (int z = 1; z <= N; z++) {
			cout << a[z] << "\t";
		}
		cout << "\n\n" << endl;
	}
}

void CountingSort(int a[], int n, int m) {
	int i, j, count[M + 1];
	for (j = 1; j <= m; j++)count[j] = 0;
	for (i = 1; i <= n; i++) count[a[i]]++;
	for (j = 2; j <= m; j++) count[j] += count[j - 1];
	for (i = n; i >= 1; i--) b[count[a[i]]--] = a[i];
	for (i = 1; i <= n; i++) a[i] = b[i];
}

class Queue {
public:
	Queue();
	~Queue();
	void enqueue(int v);
	int depueue();
	int empty();
private:
	struct node {
		int data;
		struct node *link;
	};
	struct node *front, *rear;
};

Queue::Queue() {
	front = new node;
	rear = new node;
	front = NULL;
	rear = NULL;
}

Queue::~Queue() {
	struct node *t = front;
	while (t != NULL) {
		front = t;
		t->link = t;
		delete front;
	}
}

void Queue::enqueue(int v) {
	struct node *t = new node;
	t->data = v;
	t->link = NULL;
	if (front == NULL) {
		front = t;
		rear = t;
	}
	else {
		rear->link = t;
		rear = t;
	}
}

int Queue::depueue() {
	int x;
	struct node *t = front;
	if (front == NULL) {
		cout << "ť�� ������." << endl;
		exit(1);
	}
	else {
		x = t->data;
		front = t->link;
		if (front == NULL) rear = NULL;
		delete t;
		return x;
	}
}

int Queue::empty() {
	return front == NULL;
}

int digit(int d, int k) {
	int i, temp = 1;
	for (i = 1; i < k; i++) temp *= 10;
	d /= temp;
	d %= 10;
	return d;
}

void RadixSort(int a[], int n, int m, Queue q[]) {
	int k, i, p, kd;
	for (k = 1; k <= m; k++) {
		for (i = 1; i <= n; i++) {
			kd = digit(a[i], k);
			q[kd].enqueue(a[i]);
		}
		p = 0;
		for (i = 0; i <= 9; i++)
			while (!q[i].empty())
				a[++p] = q[i].depueue();
	}
}
