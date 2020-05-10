#include "SORT.h"
void display(int arr[], int len){
	for (int i = 0; i < len; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
}
void swap(int arr[], int start, int min){
	int tmp = arr[start];
	arr[start] = arr[min];
	arr[min] = tmp;
}

// ����ȡ��
// ����ȡ��--> �ҵ��������е��м���
// ������Ҫ��Ŀ�ľ��Ƿ�ֹ����������������������ʱ�临�Ӷ�ΪO(n^2)
// ����������ȥ��ֵ����ı������������������
int getMid(int* arr, int begin, int end){
	int mid = begin + (end - begin) / 2;
	// �����м�ֵmid�Ƚ�
	if (arr[begin] < arr[mid]){
		if (arr[mid] < arr[end]){
			return mid;
		}
		else{ // mid >= end && mid > begin
			if (arr[begin] > arr[end]){
				return begin;
			}
			else{
				return end;
			}
		}
	}
	else{ // begin <= mid
		if (arr[mid] < arr[end]){
			return mid;
		}
		else{ // mid >= end && begin<=mid
			if (arr[begin] > arr[end])
				return end;
			else
				return begin;
		}
	}
}

/*
	ʱ�临�Ӷȣ�
		�����������⻮�� ���ֲ�� logn
		ʱ�临�Ӷ� O(nlogn)
		������������������ܻ�������ڴ�ջ��������ڵݹ��������
			�������򣺻��֣�ÿ��ֻ�ܲ���һ�������ֵ�����
					��ʱ���������˻�Ϊð�����򣺵ݹ��㷨�ĵݹ����̫�����׵���ջ���
						����ջ̫�ֻ࣬��ѹջ��û�г�ջ��ջѹ��
			O(n^2)
			��˿�����Ҫ�Ż�
				����ȡ�з�
		ƽ����� O(nlogn)
	�ռ临�Ӷȣ�
		�ռ���Ǳ����ĸ���
			ջ�Ŀռ�  ��������ջ O(logn) �� ��������¾���O(n)
	�ȶ��ԣ�
		���ȶ�
		2 2 2 1����ʱ����Ե�һ��2��Ϊ��׼ֵ����ᷢ���仯�����ڻ�׼ֵ��Ҫ�����仯�����Բ��ȶ�
	�����������
			��������

	��������ֲ��������� 
		  ��������ȥȡ�м�ֵ��Ϊ��׼ֵ
		  begin mid end : ����ȡ�н������������
		  ����ȡ�з������԰�������-->���⻮��


	��С�����Ż� ����������һ��������ʱ
		������������
		���ٵײ�ݹ�ĵ��ô������������



	����������ע������
	���ֻ��֣� hora , �ڿ� ��ǰ��ָ��
	�Ż�����׼ֵ��ѡȡ������ȡ�У���С�����Ż������ٵݹ飬���ٵײ���ã�
	�ǵݹ飺ջ������ ��������ֵ
	��������������ʱ�临�Ӷȣ��Ż�֮ǰ��O(n^2)
									�Ż�֮��O(nlogn) --> ��׼ֵѡ�񷽷�
			  ����ǵݹ飺�Ż�֮ǰջ���
*/
int getmid(int* arr, int begin, int end){
	int mid = begin + (end - begin) / 2;
	// begin , mid , end ѡ���м�ֵ��λ��
	if (arr[begin] < arr[mid]){
		// begin < mid
		if (arr[mid] < arr[end]){
			return mid;
		}
		else{
			// begin < mid , end <= mid
			if (arr[begin] > arr[end]){
				return begin;
			}
			else{
				return end;
			}
		}
	}
	else{ // begin >= mid
		if (arr[mid] > arr[end]){
			return mid;
		}
		else{
			// begin >= mid , end >= mid
			if (arr[begin] <= arr[end]){
				return begin;
			}
			else{
				return end;
			}
		}
	}
}
int partion(int* arr, int l, int h){
	int mid = getmid(arr, l, h);
	swap(arr, l, mid);
	//int mid = l;
	int cur = arr[l];
	while (l < h){
		while (l < h && arr[h] > cur)
			h--;
		arr[l] = arr[h];
		while (l < h && arr[l] <= cur)
			l++;
		arr[h] = arr[l];
	}
	arr[l] = cur;
	return l;
}
void QSORT(int* arr, int l, int h){
	if (l < h){
		int m = partion(arr, l, h);
		QSORT(arr, l, m - 1);
		QSORT(arr, m + 1, h);
	}
}
void QUICKSORT(int* arr, int len){
	QSORT( arr, 0, len - 1);
}


void test(){
	srand((unsigned long)time(NULL));
	int num = 10;
	int* arr = (int*)malloc(sizeof(int) * num);
	for (int i = 0; i < num; i++){
		arr[i] = rand();
	}
	display(arr, num);
	QUICKSORT(arr, num);
	display(arr, num);
}

typedef int Type;
typedef struct Node{
	Type _data;
	struct Node* _next;
}Node;

// ջ��ʵ��

// ������: pushFront popFront
// ˳���: pushBack popBack  ����ѡ�� ջ��ʵ�ֻ����϶���˳���ʵ��
//#pragma once
// ˳���ʵ��ջ
typedef struct Stack{
	Type* _array;
	size_t _size;
	size_t _capacity;
}Stack;
void stackInit(Stack* st, size_t n){
	st->_capacity = n;
	st->_array = (Type*)malloc(sizeof(Type)*st->_capacity);
	st->_size = 0;
}

void stackPush(Stack* st, Type data){
	// �������
	if (st->_size == st->_capacity){
		st->_capacity *= 2;
		st->_array = (Type*)realloc(st->_array, sizeof(Type)*st->_capacity);
	}
	st->_array[st->_size++] = data;
}
void stackPop(Stack* st){
	// βɾ
	if (NULL == st){
		return;
	}
	if (st->_size){
		st->_size--;
	}
}

Type stackTop(Stack* st){
	return st->_array[st->_size - 1];
}
size_t stackSize(Stack* st){
	return st->_size;
}
int stackEmpty(Stack* st){
	if (st->_size == 0){
		return 1;
	}
	return 0;
}


void stackDestory(Stack* st){
	free(st->_array);
	st->_array = NULL;
	st->_size = st->_capacity = 0;
}
// ���ŷǵݹ��㷨
// �������䣬�ȴ������С����
// ��ջʵ�ַǵݹ�
// �Ȼ�����������䣬�ٻ����ұ�������
		// �����ջʱ���Һ���
// ������ջ��ÿ�λ�ȡջ�����䣬���л���
// ����֮���С���������ջ
// ֱ��ջΪ�ս���
void quickAortNoR(int* arr, int n){
	Stack st;
	stackInit(&st,10);
	// ��ʼ������ջ
	if (n > 1){
	// ������������
		stackPush(&st, n - 1);
		stackPush(&st, 0);
	}
	// ����ջ������ջ�е�ÿһ������
	while (stackEmpty(&st) != 1){
		// ��ȡջ������
		int begin = stackTop(&st);
		stackPop(&st);
		int end = stackTop(&st);
		stackPop(&st);

		// ����
		int keyPos = partion(arr, begin, end);
		// ��������ջ��Ϊ�˱�����ջ˳��һ�£����������䣬����������
		//�ұߵ������� keyPos+1 �� end
		if (keyPos + 1 < end){  // ����������ֵ
			stackPush(&st, end);
			stackPush(&st, keyPos + 1);
		}
		// ��begin , keyPos-1
		if (begin < keyPos - 1){
			stackPush(&st, keyPos - 1);
			stackPush(&st, begin);
		}
	}
}

void testNoR(){
	srand((unsigned long)time(NULL));
	int num = 10;
	int* arr = (int*)malloc(sizeof(int) * num);
	for (int i = 0; i < num; i++){
		arr[i] = rand();
	}
	display(arr, num);
	quickAortNoR(arr, num);
	display(arr, num);
}


typedef int	QDataType;
typedef struct QNode{
	struct QNode* _next;
	QDataType _data;
}QNode;
typedef struct Queue{
	QNode* _front;
	QNode* _rear;
	int _size;
}Queue;
QNode* createNode(QDataType data){

	// ����һ����㣬���ý�㸳��dataֵ��ͬʱ��һ��Ԫ��ָ��NULL
	QNode* node = (QNode*)malloc(sizeof(QNode));
	node->_data = data;
	node->_next = NULL;
	return node;
}
void queueInit(Queue* q){
	// ��ʼ���ն���
	// �ն����в���Ԫ�أ����ǰ��ָ���
	q->_front = q->_rear = NULL;
	q->_size = 0;
}
// ��β��ӣ����ǿն���
void queuePush(Queue* q, QDataType data){
	// β�����
	QNode* node = createNode(data);
	if (q->_front == NULL){
		// ���ǵ�ǰ����Ϊ�ն��е������ʹ��λ������node
		q->_front = q->_rear = node;
	}
	else{
		q->_rear->_next = node;
		q->_rear = node;
	}
	q->_size++;
}
// ��ͷ���ӣ�������Ҫ�ͷţ���Ҫ����ֻ��һ���������
void queuePop(Queue* q){
	/*	if (q->_front == NULL){
	return NULL;
	}else*/
	if (q->_front){
		// ��¼��ͷ����һ�����
		QNode* next = q->_front->_next;
		// �ͷ�ͷ���
		free(q->_front);
		//q->_front = NULL;
		q->_front = next;

		// ������ֻ��һ��Ԫ�أ�ɾ��֮�����βָ��
		if (q->_front == NULL)
			q->_rear = NULL;
		q->_size--;
	}
}
// ��ȡ��ͷԪ��
QDataType queueFront(Queue* q){
	return q->_front->_data;
}
// ��ȡ��βԪ��
QDataType queueBack(Queue* q){
	return  q->_rear->_data;
}
int queueSize(Queue* q){
	//int cnt = 0;
	//QNode* cur = q->_front;
	//while (cur){
	//	cnt++;
	//	cur = cur->_next;
	//}
	//return cnt;
	// ����һ������֮��
	return q->_size;
}
int queueEmpty(Queue* q){
	if (q->_front == NULL)
		return 1;
	return 0;
}
void queueDestory(Queue* q){
	//QNode* prev = q->_front;
	QNode* cur = q->_front;
	while (cur){
		QNode* next = cur->_next;
		free(cur);
		cur = next;
	}
	q->_front = q->_rear = NULL;
	q->_size = 0;
}
// �ö���ʵ�ֿ�������
void QuickSortQueue(int* arr, int len){
	Queue q;
	queueInit(&q);
	if (len > 1){
		queuePush(&q, 0);
		queuePush(&q, len - 1);
	}
	while (queueEmpty(&q) != 1){
		int begin = queueFront(&q);
		queuePop(&q);
		int end = queueFront(&q);
		queuePop(&q);
		int keyPos = partion(arr, begin, end);
		if (begin < keyPos - 1){
			queuePush(&q, begin);
			queuePush(&q, keyPos - 1);
		}
		if (keyPos + 1 < end){
			queuePush(&q, keyPos+1);
			queuePush(&q, end);
		}
	}
}
void testNoRQueue(){
	srand((unsigned long)time(NULL));
	int num = 10;
	int* arr = (int*)malloc(sizeof(int) * num);
	for (int i = 0; i < num; i++){
		arr[i] = rand();
	}
	display(arr, num);
	QuickSortQueue(arr, num);
	display(arr, num);
}

// ����ʵ�ַǵݹ�
void QuickSortQueue2(int* arr, int n){
	Queue q;
	queueInit(&q);
	if (n > 1){
	// �������
		queuePush(&q, 0);
		queuePush(&q, n - 1);
	}
	// �ж϶����Ƿ�Ϊ��
	while (queueEmpty(&q) != 1){
		// ��ȡ��ͷ����
		int begin = queueFront(&q);
		queuePop(&q);
		int end = queueFront(&q);
		queuePop(&q);
		// ����
		int keyPos = partion(arr, begin, end);
		// ������֮�����������
		if (begin < keyPos - 1){
			queuePush(&q,begin);
			queuePush(&q, keyPos - 1);
		}
		if (keyPos + 1 < end){
			queuePush(&q, keyPos + 1);
			queuePush(&q, end);
		}
	}

}

// �鲢����
// �ϲ�����Ҫֱ�������������е�����[begin , mid] [mid+1 end]
void merge(int* arr, int begin, int mid, int end,int* tmp){
	int begin1 = begin, end1 = mid, begin2 = mid + 1, end2 = end;
	// indx ��Ҫ�ӵ�ǰλ�ÿ�ʼ��������ÿһ�ζ���������Ԫ�ؿ�ʼ���߼����ֵ�����ͷ��ʼ
	int indx = begin;	
	// �ϲ�
	while (begin1 <= end1 && begin2 <= end2){
		if (arr[begin1] < arr[begin2]){
			tmp[indx++] = arr[begin1++];
		}
		else{
			tmp[indx++] = arr[begin2++];
		}
	}
	// �鿴�Ƿ���ʣ��Ԫ��
	// ��ʣ��Ԫ�ز���
	if (begin1 <= end1){
		memcpy(tmp + indx, arr + begin1, sizeof(int)*(end1 - begin1 + 1));
	}
	if (begin2 <= end2){
		memcpy(tmp + indx, arr + begin2, sizeof(int)*(end2 - begin2 + 1));
	}
	// ������ԭʼ�ռ�
	memcpy(arr + begin, tmp + begin, sizeof(int)*(end - begin + 1));
}
// Ҫ��ǰ����������������Ҫ����������
void MERGESORT(int* arr, int begin , int end,int* tmp){
	if (begin >= end) return;
	int mid = begin + (end - begin) / 2;

	// ���ȱ�֤�������������������������
	MERGESORT(arr, begin, mid, tmp);
	MERGESORT(arr, mid + 1, end, tmp);
	merge(arr, begin, mid,end, tmp);
}
/*
	ʱ�临�Ӷȣ�O(nlogn)
	�ռ临�Ӷȣ�O(n)
	�ȶ��ԣ��ȶ�
	�������У�������
*/
void meresort(int* arr, int n){
	int* tmp = (int*)malloc(sizeof(int)*n);
	MERGESORT(arr, 0, n-1, tmp);
	free(tmp);
}


// �鲢����
void MERGENEW(int* arr, int begin, int mid, int end){
	int len = end - begin + 1;
	int* newArr = (int*)malloc(sizeof(int)*len);
	int k = 0;
	int begin1 = begin, end1 = mid, begin2 = mid + 1, end2 = end;
	while (begin1 <= end1 && begin2 <= end2){
		if (arr[begin1] <= arr[begin2]){
			newArr[k++] = arr[begin1++];
		}
		else{
			newArr[k++] = arr[begin2++];
		}
	}
	if (begin1 <= end1){
		memcpy(arr + begin1, newArr + begin1, sizeof(int)*(len-begin1+1));
	}
	if (begin2 <= end2){
		memcpy(arr + begin2, newArr + begin2, sizeof(int)*(len-begin2+1));
	}
	memcpy(arr, newArr, sizeof(int)*len);
	free(newArr);
}


void mergeSortNoR(int* arr, int n){
	int* tmp = (int*)malloc(n*sizeof(int));
	// [begin , mid] [mid+1,end]
	int k = 1; // ���ϲ������Ԫ�ظ���
	while (k < n){
		for (int i = 0; i < n; i += 2 * k)
		{
			int begin = i;
			// �ж�mid�Ƿ�Խ��
			int mid = i + k - 1;
			if (mid >= n - 1) // ��ʱֻ��һ�������䣬ֱ������
				continue;
			// �ж�end�Ƿ�Խ��
			int end = i + 2 * k - 1;
			if (end >= n)// ��Ȼ����Ҫ�ϲ������䣬�����г������䳤�ȵģ������Ҫ����
				end = n - 1;
			merge(arr, begin, mid, end, tmp);
		}
		k *= 2;
	}
}
// �鲢����ķǵݹ�
// �鲢�����˼���ر��ʺ�����������ν�������
void mergenor(int* arr, int len){
	int k = 1; // ����ÿһ�κϲ�������Ԫ�ظ���
	int*  tmp = (int*)malloc(sizeof(int)*len);
	while (k < len){
		for (int i = 0; i < len; i += 2*k){ // ÿһ�κϲ�������������ĳ��ȣ���Ϊ�ϲ���ʱ��������������кϲ�
			int begin = i;
			int mid = i + k - 1;
			// �ж�mid�Ƿ�Խ��
			if (mid >= len - 1)
				continue;// ��midΪ���һ��λ��ʱ����ֻ��Ҫ������һ��
			int end = i + 2 * k - 1;
			if (end >= len)
				end = len - 1;
			merge(arr, begin, mid, end, tmp);
		}
		k *= 2;
	}
}
/*
	ʱ�临�Ӷȣ�O(max(len,��Χ))
	�ռ临�Ӷȣ�O(range)
	�ȶ��ԣ�û���漰���Ƚϣ��ݲ������ȶ��ԣ��̲�˵�����ȶ���
	�������У�������
	��������ֻ����С��Χ���ݣ������Χ�Ƚϴ󣬿ռ临�ӶȽϸ�
	����ʺ϶��ַ�����
*/
// �������򣺷ǱȽ�����
void countsort(int* arr, int len){
	// ͳ�Ʒ�Χ
	int min = arr[0], max = arr[0];
	for (int i = 1 ; i < len; i++){
		if (arr[i] > max)
			max = arr[i];
		if (arr[i] < min)
			min = arr[i];
	}
	int range = max - min + 1;
	// �������ռ䣬���м���
	int* countArr = (int*)malloc(sizeof(int)*range);
	// ��ʼ��Ϊ0
	memset(countArr, 0, sizeof(int)*range);
	// ͳ�ƴ���
	for (int i = 0; i < len; i++){
		countArr[arr[i] - min]++;
	}
	// �ָ����ݣ�������������
	int idx = 0;
	for (int i = 0; i < range; i++){
		while (countArr[i]--){
			arr[idx++] = i + min;
		}
	}
	display(arr, len);
}
void testMerge(){
	srand((unsigned long)time(NULL));
	int num = 10;
	int* arr = (int*)malloc(sizeof(int) * num);
	for (int i = 0; i < num; i++){
		arr[i] = rand();
	}
	display(arr, num);
	countsort(arr, num);
	//display(arr, num);
}
int main(void){
	testMerge();
	system("pause");
	return 0;
}
//// ����ȡ��
//int getMid(int* array, int begin, int end){
//	int mid = begin + (end - begin) / 2;
//	// begin , mid , end ѡȡ�м�ֵ��λ��
//	if (array[begin] < array[mid]){
//		if (array[mid] < array[end]){
//			return mid;
//		}
//		else{
//			if (array[begin] > array[end]){
//				return begin;
//			}
//			else{
//				return end;
//			}
//		}
//	}
//	else{
//		// begin >= mid 
//		if (array[mid] > array[end])
//			return mid;
//		else{
//			// begin >= mid , end >= mid
//			if (array[begin] < array[end])
//				return begin;
//			else
//				return end;
//		}
//	}
//}
//
//int partion(int* arr , int begin , int end){
//	int mid = getMid(arr, begin, end); 
//	// ���� mid -- begin
//	swap(arr, mid , begin);
//	int start = arr[begin];
//	int key = arr[begin];
//	while (begin < end){
//		while (begin < end && key <= arr[end])
//			end--;
//		while (begin < end && key >= arr[begin])
//			begin++;
//		swap(arr, begin, end);
//	}
//	swap(arr, start, begin);
//	return begin;
//}
////void qsort(int arr[], int begin, int end){
////	if (begin >= end) return;
////	int m = partion(arr, begin, end);
////	qsort(arr, begin, m - 1);
////	qsort(arr, m + 1, end);
////}
//
//// ջʵ�ַǵݹ� ���������������
//void quikSortNoR(int* array, int n){
//
//}
//// �ϲ� �� ��Ҫ֪�� �������������е�����
//void merge(int* arr, int begin, int mid, int end,int* tmp){
//	int begin1 = begin, end1 = mid, begin2 = mid + 1, end2 = end;
//	int indx = begin;
//	while (begin1 < end1 && begin2 < end2){
//		if (arr[begin1] < arr[begin2]){
//			tmp[indx++] = arr[begin1++];
//		}
//		else{
//			tmp[indx++] = arr[begin2++];
//		}
//	}
//	// �鿴�Ƿ���ʣ��Ԫ��
//	if (begin1 < end1){
//		memcpy(tmp + indx, arr + begin1, sizeof(int)*(end1 - begin1 + 1));
//	}
//	if (begin2 < end2){
//		memcpy(tmp + indx, arr + begin2, sizeof(int)*(end2 - begin2 + 1));
//	}
//	// ������ԭʼ�ռ�
//	memcpy(arr + begin, tmp + begin, sizeof(end - begin + 1));
//}
//void mergesortR(int* arr, int begin , int end,int* tmp){
//	if (begin == end) return;
//	int mid = begin + (end - begin) / 2;
//	// ���ȱ�֤�������������������������
//	mergesortR(arr, begin, mid, tmp);
//	mergesortR(arr, mid + 1, end, tmp);
//
//	// �ϲ�������
//	merge(arr, begin, mid, end, tmp);
//}
//int main(void){
//
//	system("pause");
//	return 0;
//} 
////int partion(int arr[], int begin, int end){
////	int key = arr[begin];
////	int prev = begin;
////	int cur = prev + 1;
////	while (cur <= end){
////		if (key >= arr[cur] && (++prev != cur)){
////			swap(arr, cur, prev);
////		}
////		cur++;
////	}
////	swap(arr, prev, begin);
////	return prev;
////}
////void QSORT(int arr[], int begin, int end){
////	if (begin >= end) return;
////	int m = partion(arr, begin, end);
////	QSORT(arr, begin, m - 1);
////	QSORT(arr, m + 1, end);
////}
////void testPartion(){
////	srand(time(NULL));
////	// ����������
////	int num = 0;
////	scanf("%d", &num);
////	int* arr = (int*)malloc(sizeof(int)*num);
////	for (int i = 0; i < num; i++){
////		arr[i] = rand();
////	}
////	display(arr, num);
////	int begin = clock();
////	QSORT(arr, 0, num - 1);
////	int end = clock();
////	printf("��������Ϊ:>");
////	display(arr, num);
////	printf("����������ʱ��Ϊ:>%d\n", end - begin);
////}
////
////int main(){
////	testPartion();
////
////	system("pause");
////	return 0;
////}
////
////// ��������
////// ǰ��ָ�뷨
//////int partion(int arr[], int begin, int end){
//////	int prev = begin;
//////	int cur = prev + 1;
//////	int key = arr[begin];
//////	while (cur <= end){
//////		if ((arr[cur] < key) && (++prev != cur)){
//////			swap(arr, prev, cur);
//////		}
//////		++cur;
//////	}
//////	swap(arr, begin, prev);
//////	return prev;
//////}
//////int partion(int arr[], int begin, int end){
//////	int prev = begin;
//////	int cur = prev + 1;
//////	int key = arr[begin];
//////	while (cur <= end){
//////		if (arr[cur] < key && (++prev != cur)){
//////			swap(arr, cur, prev);
//////		}
//////		cur++;
//////	}
//////	swap(arr, prev, begin);
//////	return prev;
//////}
////int partion(int arr[], int begin, int end){
////	int prev = begin;
////	int cur = prev + 1;
////	int key = arr[begin];
////	while (cur <= end){
////		if (arr[cur] <= key && (++prev != cur)){
////			swap(arr, cur, prev);
////		}
////		++cur;
////	}
////	swap(arr, begin, prev);
////	return prev;
////}
////void qsort(int arr[], int begin, int end){
////	if (begin >= end) return;
////	int m = partion(arr, begin, end);
////	qsort(arr, begin, m - 1);
////	qsort(arr, m + 1, end);
////}
////void testPartion(){
////	srand(time(NULL));
////	// ����������
////	int num = 0;
////	scanf("%d", &num);
////	int* arr = (int*)malloc(sizeof(int)*num);
////	for (int i = 0; i < num; i++){
////		arr[i] = rand();
////	}
////	display(arr, num);
////	int begin = clock();
////	qsort(arr, 0,num-1);
////	int end = clock();
////	printf("��������Ϊ:>");
////	display(arr, num);
////	printf("����������ʱ��Ϊ:>%d\n", end - begin);
////}
////int mawin(void){
////
////	testPartion();
////	system("pause");
////	return 0;
////}
//////// ���� ���ε�˼�룬���ϵĽ����з�
//////
//////int partiona(int* arr , int begin , int end){
//////	int start = begin;
//////	int key = arr[begin];
//////	while (begin < end){
//////		while (begin < end && key <= arr[end])
//////			end--;
//////		while (begin < end && key >= arr[begin])
//////			begin++;
//////		swap(arr, begin, end);
//////	}
//////	swap(arr, start, begin);
//////}
//////
//////// hora����
//////int partion(int arr[], int begin, int end){
//////	// ѡ���׼ֵ
//////	int start = begin;
//////	int key = arr[begin];
//////	// ����
//////	while (begin < end){
//////		while (begin < end&&arr[begin] <= key){
//////			begin++;
//////		}
//////		// �Ӻ���ǰ�ҵ���һ��С��key��λ��
//////		// ��ȵ�ʱ��ҲҪ�ƶ�������ʹ���key
//////		while (begin < end && arr[end] >= key)
//////			--end;
//////		// ��ǰ����ҵ�һ������key��λ��
//////		// ���ʱҲҪ�ƶ��������С��key
//////
//////		swap(arr, begin, end);
//////	}
//////	// key ������λ�õ����ݽ���
//////	swap(arr, start, begin);
//////	return begin;
//////}
//////
////////�ڿӷ�
//////int partion2(int arr[], int begin, int end){
//////	int key = arr[begin];
//////	while (begin < end){
//////		// �Ӻ���ǰ
//////		while (begin < end && arr[begin] >= key){
//////			--end;
//////		}
//////		arr[begin] = arr[end];
//////		// ��ǰ����
//////		while (begin < end && arr[begin] <= key){
//////			arr[end] = arr[begin];
//////		}
//////	}
//////	arr[begin] = key;
//////	return begin;
//////}
////
//////void qsort(int arr[], int begin , int end){
//////	if (begin >= end) return;
//////	// ���ֵ�ǰ����
//////	// ����֮��ĵ�ǰλ��
//////	int keyPos = partion(arr, begin, end);
//////	// ����������
//////	qsort(arr, begin, keyPos - 1);
//////	qsort(arr, keyPos+1,end );
//////}
//////void testsort(){
//////	srand(time(NULL));
//////	// ����������
//////	int num = 0;
//////	scanf("%d", &num);
//////	int* arr = (int*)malloc(sizeof(int)*num);
//////	for (int i = 0; i < num; i++){
//////		arr[i] = rand();
//////	}
//////	display(arr, num);
//////	int begin = clock();
//////	qsort(arr, 0,num-1);
//////	int end = clock();
//////	printf("��������Ϊ:>");
//////	display(arr, num);
//////	printf("����������ʱ��Ϊ:>%d\n", end - begin);
//////}
//////int main(){
//////	testsort();
//////	system("pause");
//////	return 0;
//////}
/////////*
////////	ʱ�临�Ӷȣ�O(nlog(n))
////////	�ռ临�Ӷȣ�O(1)
////////	�ȶ��ԣ����ȶ�
////////	�������жȣ�������
////////*/
////////void shiftDown(int arr[], int len, int parent){
////////	if (parent < 0)
////////		return;
////////	int child = 2 * parent + 1;
////////	while (child < len){
////////		// �ҵ�С�ĺ���
////////		if (child + 1 < len && arr[child + 1] < arr[child])
////////			child++;
////////		// �Ƚ�С�����븸�׵Ĺ�ϵ
////////		if (arr[parent] > arr[child]){
////////			swap(arr, child, parent);
////////			parent = child;
////////			child = 2*parent +1;
////////		}
////////		else{
////////			break;
////////		}
////////	}
////////}
////////void heapSort(int arr[], int len){
////////	// ����
////////	for (int parent = (len - 2) / 2; parent >= 0; parent--){
////////		shiftDown(arr, len, parent);
////////	}
////////
////////	// ����
////////	for (int i = len-1; i >=0; i--){
////////		swap(arr, i, 0);
////////		shiftDown(arr, i, 0);
////////	}
////////}
////////void testsort(){
////////	srand(time(NULL));
////////	// ����������
////////	int num = 0;
////////	scanf("%d", &num);
////////	int* arr = (int*)malloc(sizeof(int)*num);
////////	for (int i = 0; i < num; i++){
////////		arr[i] = rand();
////////	}
////////	display(arr, num);
////////	int begin = clock();
////////	heapSort(arr, num);
////////	int end = clock();
////////	printf("��������Ϊ:>");
////////	display(arr, num);
////////	printf("����������ʱ��Ϊ:>%d\n", end - begin);
////////}
////////int maien(){
////////	testsort();
////////	system("pause");
////////	return 0;
////////}
/////////*
////////	ʱ�临�Ӷȣ��O(n^2) ƽ��O(n^2) ���O(n)
////////	�ռ临�Ӷȣ�O(1)
////////	�ȶ��ԣ��ȶ�
////////	�������жȣ�����
////////*/
////////void bubbleSort(int arr[], int len){
////////	int end = 0;
////////	
////////	while (end < len - 1){
////////		int flag = 1;
////////		for (int j = 0; j<len-end-1; j++){
////////			if (arr[j + 1]>arr[j])
////////				swap(arr, j + 1, j);
////////			flag = 0;
////////		}
////////		++end;
////////		if (flag)
////////			break;
////////	}
////////}
////////void bubbleSortSlow(int arr[], int len){
////////	// �Ӻ���ǰ�Ƚϣ���С�ķ���ǰ��
////////	int end = 0;
////////	while (end < len-1){
////////		int j = len-2;
////////		int flag = 1;
////////		while (j >= end){
////////			if (arr[j + 1] < arr[j])
////////				swap(arr, j + 1, j);
////////			j--;
////////			flag = 0;
////////		}
////////		end++;
////////		printf("[%d] ", end);
////////		display(arr, len);
////////		if (flag)
////////			break;
////////	}
////////}
////////void bs(int* arr, int len){
////////	while (len){
////////		int flag = 1;
////////		int end = len-1;
////////		// һ��ð������
////////		for (int i = 0; i<end; i++){
////////			// ����Ԫ�ؽ��бȽ�
////////			if (arr[i] > arr[i + 1])
////////				swap(arr, i + 1, i);
////////			flag = 0;
////////		}
////////		if (flag)
////////			break;
////////		len--;
////////	}
////////}
////////testsort(){
////////	srand(time(NULL));
////////	// ����������
////////	int num = 0;
////////	scanf("%d", &num);
////////	int* arr = (int*)malloc(sizeof(int)*num);
////////	for (int i = 0; i < num; i++){
////////		arr[i] = rand();
////////	}
////////	display(arr, num);
////////	int begin = clock();
////////	bs(arr, num);
////////	int end = clock();
////////	printf("��������Ϊ:>");
////////	display(arr, num);
////////	printf("����������ʱ��Ϊ:>%d\n", end - begin);
////////}
////////int main(){
////////	int n = testsort();
////////	//printf("%d", n);
////////	system("pause");
////////	return 0;
////////}
////////// ��������
////////int pivsort(int arr[], int l, int h){
////////	int cur = arr[l];
////////	while (l < h){
////////
//////		//while (l < h && arr[h] > cur){
//////		//	h--;
//////		//}
//////		//arr[l] = arr[h];
//////
//////		//while (l < h && arr[l] <= cur){
//////		//	l++;
//////		//}
//////		//arr[h] = arr[l];
////////	}
////////	arr[l] = cur;
////////	return l;
////////}
////////void QSort(int arr[], int l , int h){
////////	if (l < h){
////////		int m = pivsort(arr, l, h);
////////		QSort(arr, l, m - 1);
////////		QSort(arr, m + 1, h);
////////	}
////////}
////////void QSORT(int arr[], int len){
////////	QSort(arr, 0, len - 1);
////////}
//////
//////// hore ����
////////int partion(int arr[], int begin, int end){
////////	// ѡ���׼ֵ
////////	int key = arr[begin];
////////	int start = begin;
////////	// ����
////////	while (begin < end){
////////		// �Ӻ���ǰ�ҵ�һ��С��key��λ��
////////		while (begin < end && arr[end] >= key){
////////			--end;
////////		}
////////		// ��ǰ����ҵ�һ������key��λ��
////////		while (begin < end && arr[begin] <= key){
////////			++begin;
////////		}
////////		//  ����end , begin����
////////		swap(arr, begin, end);
////////	}
////////
////////	// key������λ�����ݽ���
////////	swap(arr, start, begin);
////////	return begin;
////////}
////////void quitSort(int arr[], int begin, int end){
////////	if (begin >= end){
////////		return;
////////	}
////////	// ���ֵ�ǰ����
////////	int keypos = partion(arr, begin, end);
////////	quitSort(arr, begin, keypos-1);
////////	quitSort(arr, keypos+1,end);
////////}
////////void qsort(int* arr, int len){
////////	quitSort(arr, 0, len - 1);
////////}
////////
////////int partion2(int arr[], int l, int h){
////////	int key = arr[l];
////////	while (l < h){
////////		// �Ӻ���ǰ��
////////		while (l < h && arr[h] > key){
////////			h--;
////////		}
////////		arr[l] = arr[h];
////////		// ��ǰ����Ҵ���key��ֵ
////////		while (l < h && arr[l] < key){
////////			l++;
////////		}
////////		arr[h] = arr[l];
////////	}
////////	// ���һ���ӣ�������λ��-->����׼ֵ
////////	arr[l] = key;
////////	return l;
////////}
////////int partion12(int arr[], int begin, int end){
////////	int key = arr[begin];
////////	int start = begin;
////////	while (begin < end){
////////		while (begin < end && arr[end]>key){
////////			end--;
////////		}
////////		while (begin < end && arr[begin] <= key){
////////			begin++;
////////		}
////////		swap(arr, begin, end);
////////	}
////////	swap(arr, start, begin);
////////	return begin;
////////}
////////// ǰ��ָ�뷨
////////int partion3(int* arr, int begin, int end){
////////	// prev �� ���һ��С�ڻ�׼ֵ��λ��
////////	int prev = begin;
////////	// cur���·��ֵ���һ��С�ڻ�׼ֵ��λ��
////////	int cur = prev + 1;
////////	int key = arr[begin];
////////	while (cur <= end){
////////		// �·��ֵ�С���ݺ�βָ��ָ���λ�ò����������м京�д��ڻ�׼ֵ������
////////		// ����������ƶ���С������ǰ�ƶ�
////////		if (arr[cur] < key && (++prev != cur)){
////////			//++prev;
////////			swap(arr, prev, cur);
////////		}
////////		++cur;
////////	}
////////	swap(arr, begin, prev);
////////	return prev;
////////}
////////void testQSort(){
////////	srand(time(NULL));
////////	// ����������
////////	int num = 0;
////////	scanf("%d", &num);
////////	int* arr = (int*)malloc(sizeof(int)*num);
////////	for (int i = 0; i < num; i++){
////////		arr[i] = rand();
////////	}
////////	display(arr, num);
////////	int begin = clock();
////////	qsort(arr, num);
////////	int end = clock();
////////	display(arr, num);
////////	printf("����������ʱ��Ϊ:>%d\n", end - begin);
////////}
////////int mainx(void){
////////	testQSort();
////////	system("pause");
////////	return 0;
////////}
////////void heapify(int arr[], int len, int i){
////////	if (i >= len){
////////		return;
////////	}
////////	int c1 = 2 * i + 1;
////////	int c2 = 2 * i + 2;
////////	int max = i;
////////	if (c1 < len && arr[c1] > arr[max]){
////////		max = c1;
////////	}
////////	if (c2 < len && arr[c2] > arr[max]){
////////		max = c2;
////////	}
////////	if (i != max){
////////		swap(arr, i, max);
////////		heapify(arr, len, max);
////////	}
////////}
////////void buildHeap(int arr[], int len){
////////	for (int parent = (len - 2) / 2; parent >= 0; parent--){
////////		heapify(arr, len, parent);
////////	}
////////}
////////void heapSort(int arr[], int len){
////////	buildHeap(arr, len);
////////	for (int i = len - 1; i >= 0; i--){
////////		swap(arr, 0, i);
////////		heapify(arr, i, 0);
////////	}
////////}
////////void testHeap(){
////////	void shl(int arr[], int len);
////////	srand(time(NULL));
////////	// ����������
////////	int num = 0;
////////	scanf("%d", &num);
////////	int* arr = (int*)malloc(sizeof(int)*num);
////////	for (int i = 0; i < num; i++){
////////		arr[i] = rand();
////////	}
////////	display(arr, num);
////////	int begin = clock();
////////	heapSort(arr, num);
////////	int end = clock();
////////	display(arr, num);
////////	printf("����������ʱ��Ϊ:>%d\n", end - begin);
////////	//begin = clock();
////////	//heapSort(arr, num);
////////	//end = clock();
////////	////display(arr, num);
////////	//printf("�ź���֮���ϣ����������ʱ��Ϊ:>%d\n", end - begin);
////////}
////////int maein(void){
////////	testHeap();
////////
////////
////////	system("pause");
////////	return 0;
////////}
////////
/////////*
////////	ʱ�临�Ӷȣ��O(n^2) ƽ��(n^2) ���O(n)
////////	�ռ临�Ӷȣ�O(1)
////////	�ȶ��ԣ��ȶ�
////////	�������жȣ�����
////////*/
////////void bubbleSort(int arr[], int len){
////////	while( len ){
////////		int end = len;
////////		// һ��ð������
////////		for (int i = 0; i<end - 1; i++){
////////			// ����Ԫ�ؽ��бȽ�
////////			if (arr[i] > arr[i + 1]){
////////				swap(arr, i, i + 1);
////////			}
////////		}
////////		len--;
////////	}
////////}
////////
////////// �Ż�
////////// �����ϵ����Ҫ�ٽ���
////////void bubbleSort1(int arr[], int len){
////////	while (len){
////////		// �����Ѿ���������У�ͨ����ǩ��ǰ�����������
////////		int flag = 1; // ��ʾ�Ƿ���������1 ��ʾһ�ֹ�����û�з�������
////////		int end = len;
////////		// һ��ð������
////////		for (int i = 0; i<end - 1; i++){
////////			// ����Ԫ�ؽ��бȽ�
////////			if (arr[i] > arr[i + 1]){
////////				swap(arr, i, i + 1);
////////				flag = 0;
////////			}
////////		}
////////		// flag ��־����һ����û�з������������ֱ���˳�
////////		// û�з�������
////////		if (flag)
////////			break;
////////		len--;
////////	}
////////}
////////void bubble(int arr[], int len){
////////	for (int i = 0; i < len - 1; i++){
////////		for (int j = 0; j < len - i - 1; j++){
////////			if (arr[j + 1] < arr[j]){
////////				swap(arr, j + 1, j);
////////			}
////////		}
////////	}
////////}
////////void testBubble(){
////////	void shl(int arr[], int len);
////////	srand(time(NULL));
////////	// ����������
////////	int num = 0;
////////	scanf("%d", &num);
////////	int* arr = (int*)malloc(sizeof(int)*num);
////////	for (int i = 0; i < num; i++){
////////		arr[i] = rand();
////////	}
////////	display(arr, num);
////////	int begin = clock();
////////	bubbleSort1(arr, num);
////////	int end = clock();
////////	display(arr, num);
////////	printf("ð����������ʱ��Ϊ:>%d\n", end - begin);
////////	begin = clock();
////////	bubble(arr, num);
////////	end = clock();
////////	//display(arr, num);
////////	printf("�ź���֮���ϣ����������ʱ��Ϊ:>%d\n", end - begin);
////////}
////////int maisn(){
////////	testBubble();
////////	system("pause");
////////	return 0;
////////}
////////
/////////*
////////	ʱ�临�Ӷȣ��ʱ�临�Ӷ�,����������ʱO(n^2)��ƽ�� O(n^2)�����O(n^2)
////////	�ռ临�Ӷȣ�O(1)
////////	�ȶ��ԣ��ȶ�
////////	�������жȣ�������
////////*/
////////void selectSort(int arr[], int len){
////////	for (int i = 0; i < len; i++){
////////		int start = i;
////////		int min = i;
////////		// ��ʣ���Ԫ��������Сֵ
////////		for (int j = start + 1; j < len; j++){
////////			if (arr[j] < arr[min])
////////				min = j;
////////		}
////////		if (min != i)
////////			swap( arr , i ,min);
////////	}
////////}
////////void select(int arr[], int len){
////////	for (int i = 0; i < len; i++){
////////		int cur = arr[i];
////////		int flag = i;
////////		for (int j = i + 1; j < len; j++){
////////			if (cur > arr[j]){
////////				cur = arr[j];
////////				flag = j;
////////			}
////////		}
////////		if (i != flag)
////////			swap(arr,i,flag);
////////	}
////////}
////////// ����ʱ�������С��ʱ�临�Ӷ� O(n*log(n))
////////void selectSort1(int arr[], int len){
////////	int begin = 0;
////////	int end = len - 1;
////////	while (begin < end){
////////		// ÿһ��ѡ�����ֵ����Сֵ
////////		int min = begin, max = begin;
////////		for (int i = begin + 1; i <= end;i++){
////////			if (arr[i] > arr[max])
////////				max = i;
////////			if (arr[i] < arr[min]) // ���ȶ�������
////////				min = i;
////////		}
////////		// ��Сֵ����begin
////////		swap(arr, begin, min);
////////		// ������ֵ����begin������ʱ��begin�ѱ�������min������ʱ��Ҫ��max��λ�ø�Ϊmin��
////////		if (max == begin) 
////////			max = min;
////////		// ���ֵ����end
////////		swap(arr, end, max);
////////		++begin;
////////		--end;
////////	}
////////}
////////void testSelect(){
////////	srand((size_t)time(NULL));
////////	int num = 0;
////////	scanf("%d", &num);
////////	int* arr = (int*)malloc(sizeof(int)*num);
////////	for (int i = 0; i < num; i++){
////////		arr[i] = rand();
////////	}
////////	int begin = clock();
////////	selectSort1(arr, num);
////////	int end = clock();
////////	display(arr, num);
////////	printf("ѡ����������ʱ��Ϊ:>%d\n", end - begin);
////////	begin = clock();
////////	selectSort1(arr, num);
////////	end = clock();
////////	display(arr, num);
////////	printf("�ź���֮�����������ʱ��Ϊ:>%d\n", end - begin);
////////}
////////int majin(){
////////	testSelect();
////////	//testShell();
////////	//testTime();
////////	//test();
////////	system("pause");
////////	return 0;
////////}
/////////*
////////ʱ�临�Ӷȣ��ʱ�临�Ӷ�,����������ʱO(n^2)��ƽ�� O(n^1.3)�����O(n)
////////�ռ临�Ӷȣ�ֻ�м�����ʱ����O(1)
////////�ȶ��ԣ����ȶ� -->����ʱ����ͬ���ݲ�һ���ֵ�ͬһ�飬Ԫ�ط�����Ծ�Ե��ƶ�������˳���Ե��ƶ�
////////�������жȣ�����
////////*/
////////void  shellSort(int array[], int len){
////////	int gap = len; // ����
////////	// ���ֵĲ�������
////////	while (gap > 1){
////////		gap = gap / 3 + 1; // ��Ҫ��֤�����һ����ͨ�Ĳ�������
////////		// һ�ֲ�������
////////		for (int i = 0; i < len - gap; ++i){
////////			// ͨ������gap�����߼�����
////////			// ���ڽ��в�������
////////			// ��ͬ��Ԫ�ؽ����������
////////			int end = i;
////////			int key = array[end + gap];
////////			while (end >= 0 && array[end]>key){
////////				array[end + gap] = array[end];
////////				end -= gap;
////////			}
////////			array[end + gap] = key;
////////		}
////////	}
////////}
////////void shell(int arr[], int len){
////////	// ȷ����������ʼ�����������һ��ҪΪһ����ͨ��������
////////	int step = len / 2;
////////	while (step >= 1){// ������Ϊ1ʱ����һ����ͨ�Ĳ�������
////////		// �ӵ�ǰ������ʼ��������
////////		for (int i = step; i < len; i++){
////////			// ��ǰ���ڵ�ǰһ��Ԫ��
////////			int j = i - step;
////////			// ��ǰԪ��
////////			int cur = arr[i];
////////			// �Ե�ǰλ�õ�Ԫ��������ǰ���Ѿ��ź����Ԫ�رȽϣ����ƣ�ֱ������������Ϊֹ
////////			while (j >= 0 && cur<arr[j]){
////////				arr[j + step] = arr[j];
////////				j -= step;
////////			}
////////			// ���뵱ǰԪ��
////////			arr[j + step] = cur;
////////		}
////////		step /= 2;
////////	}
////////}
////////
////////void testShell(){
////////	void shl(int arr[], int len);
////////	srand(time(NULL));
////////	// ����������
////////	int num = 0;
////////	scanf("%d", &num);
////////	int* arr = (int*)malloc(sizeof(int)*num);
////////	for (int i = 0; i < num; i++){
////////		arr[i] = rand();
////////	}
////////	int begin = clock();
////////	shl(arr, num);
////////	int end = clock();
////////	//display(arr, num);
////////	printf("ϣ����������ʱ��Ϊ:>%d\n", end - begin);
////////	begin = clock();
////////	shl(arr, num);
////////	end = clock();
////////	//display(arr, num);
////////	printf("�ź���֮���ϣ����������ʱ��Ϊ:>%d\n", end - begin);
////////}
////////
/////////*
////////	ʱ�临�Ӷȣ��ʱ�临�Ӷ�,����������ʱO(n^2)��ƽ�� O(n^2)�����O(n)
////////	�ռ临�Ӷȣ�ֻ�м�����ʱ����O(1)
////////	�ȶ��ԣ��ȶ�
////////	�������жȣ�����
////////*/
////////void insertSort(int arr[], int len){
////////	// i �� ��ʾ�������ݵ����һ��λ��
////////	for (int i = 0; i < len - 1; i++){
////////		// end ��ʾ�������е����һ��λ��
////////		int end = i;
////////		// ���������ݣ��������ݵ����λ�õĺ�һ��λ��
////////		int key = arr[end + 1];
////////		// �ҵ���һ�� С�ڵ���key ��λ��
////////		while (end >= 0 && arr[end] > key){
////////			// ��ǰ��������ƶ�һ��λ��
////////			arr[end + 1] = arr[end];
////////			--end;
////////		}
////////		arr[end + 1] = key;
////////	}
////////}
////////void insert(int arr[], int len){
////////	for (int i = 1; i < len; i++){
////////		if (arr[i] < arr[i - 1]){
////////			int j = 0;
////////			int cur = arr[i];
////////			for (j = i - 1; j >= 0 && cur < arr[j]; j--){
////////				arr[j + 1] = arr[j];
////////			}
////////			arr[j + 1] = cur;
////////		}
////////	}
////////}
////////void test(){
////////		int arr[] = { 34,0,43,5,79,19,57,164,87,9,16 };
////////		int len = sizeof(arr) / sizeof(arr[0]);
////////		insert(arr, len);
////////		display(arr, len);
////////}
////////void testTime(){
////////	srand(time(NULL));
////////	int n;
////////	scanf("%d", &n);
////////	int* array = (int*)malloc(sizeof(int)*n);
////////	for (int i = 0; i < n; i++){
////////		array[i] = rand();
////////	}
////////	size_t begin = clock();
////////	insertSort(array, n);
////////	size_t end = clock();
////////	printf("insertSort:>%d\n", end - begin);
////////
////////	begin = clock();
////////	insertSort(array, n);
////////	end = clock();
////////	printf("after insertSort:>%d\n", end - begin);
////////}
//////
/////////*
////////	ʱ�临�Ӷȣ��ʱ�临�Ӷ�,����������ʱO(n^2)��ƽ�� O(n^1.3)�����O(n)
////////	�ռ临�Ӷȣ�ֻ�м�����ʱ����O(1)
////////	�ȶ��ԣ����ȶ� -->����ʱ����ͬ���ݲ�һ���ֵ�ͬһ�飬Ԫ�ط�����Ծ�Ե��ƶ�������˳���Ե��ƶ�
////////	�������жȣ�����
////////*/
////////void  shellSort(int array[] , int len){
////////	int gap = len; // ����
////////	// ���ֵĲ�������
////////	while (gap > 1){
////////		gap = gap / 3 + 1; // ��Ҫ��֤�����һ����ͨ�Ĳ�������
////////		// һ�ֲ�������
////////		for (int i = 0; i < len - gap; ++i){
////////			// ͨ������gap�����߼�����
////////			// ���ڽ��в�������
////////			// ��ͬ��Ԫ�ؽ����������
////////			int end = i;
////////			int key = array[end + gap];
////////			while (end >= 0 && array[end]>key){
////////				array[end + gap] = array[end];
////////				end -= gap;
////////			}
////////			array[end + gap] = key;
////////		}
////////	}
////////}
////////void shell(int arr[], int len){
////////	// ȷ����������ʼ�����������һ��ҪΪһ����ͨ��������
////////	int step = len / 2;
////////	while (step >= 1){// ������Ϊ1ʱ����һ����ͨ�Ĳ�������
////////		// �ӵ�ǰ������ʼ��������
////////		for (int i = step; i < len;i++){
////////			// ��ǰ���ڵ�ǰһ��Ԫ��
////////			int j = i - step;
////////			// ��ǰԪ��
////////			int cur = arr[i];
////////			// �Ե�ǰλ�õ�Ԫ��������ǰ���Ѿ��ź����Ԫ�رȽϣ����ƣ�ֱ������������Ϊֹ
////////			while (j>=0 && cur<arr[j]){
////////				arr[j + step] = arr[j];
////////				j -= step;
////////			}
////////			// ���뵱ǰԪ��
////////			arr[j + step] = cur;
////////		}
////////		step /= 2;
////////	}
////////}
////////
////////void testShell(){
////////		void shl(int arr[], int len);
////////		srand(time(NULL));
////////		// ����������
////////		int num = 0;
////////		scanf("%d",&num);
////////		int* arr = (int*)malloc(sizeof(int)*num);
////////		for (int i = 0; i < num;i++){
////////			arr[i] = rand();
////////		}
////////		int begin = clock();
////////		shl(arr, num);
////////		int end = clock();
////////		//display(arr, num);
////////		printf("ϣ����������ʱ��Ϊ:>%d\n", end - begin);
////////		begin = clock();
////////		shl(arr, num);
////////		end = clock();
////////		//display(arr, num);
////////		printf("�ź���֮���ϣ����������ʱ��Ϊ:>%d\n", end - begin);
////////}
////////int main(){
////////	testShell();
////////	//testTime();
////////	//test();
////////	system("pause");
////////	return 0;
////////}
//////void shl(int arr[], int len){
//////	int step = len / 2;
//////	while (step >= 1){
//////		for (int i = step; i < len;i++){
//////			int j = i - step;
//////			int cur = arr[i];
//////			while (j >= 0 && cur < arr[j]){
//////				arr[j + step] = arr[j];
//////				j -= step;
//////			}
//////			arr[j + step] = cur;
//////		}
//////		step /= 2;
//////	}
//////}
////////void shell(int array[], int len){
////////	int step = len / 2;
////////	while (step >= 1){
////////		for (int i = step; i < len; i++){
////////			int j = i - step;
////////			int cur = array[i];
////////			for (; j >= 0 && cur < array[j]; j -= step){
////////				array[j + step] = array[j];
////////			}
////////			array[j + step] = cur;
////////
////////		}
////////		step /= 2;
////////	}
////////}
////////void display(int arr[], int len){
////////	for (int i = 0; i < len; i++){
////////		printf("%d ", arr[i]);
////////	}
////////	printf("\n");
////////}
/////////*
////////	ʱ�临�Ӷȣ��O(n^2) ƽ��O(n^2) ���O(n)
////////	�ռ临�Ӷȣ�O(1)
////////	�ȶ��ԣ��ȶ�
////////	�������У�����
////////*/
////////void insertSort(int arr[], int len){
////////	for (int i = 0; i < len - 1;i++){
////////		// �����ݵĲ���
////////		// end �� �������е����һ��λ��
////////		int end = i;
////////		// key �� ����������
////////		int key = arr[end + 1];
////////		// �ҵ���һ��С�ڵ���key��λ��
////////		while (end >= 0 && arr[end] > key){
////////			// ��ǰ��������ƶ�
////////			arr[end + 1] = arr[end];
////////			--end;
////////		}
////////		arr[end + 1] = key;
////////	}
////////}
////////void insert(int arr[], int len){
////////	for (int i = 1; i < len;i++){
////////		if (arr[i] < arr[i-1]){
////////			int j = 0;
////////			int cur = arr[i];
////////			for (j = i - 1; j >= 0 && arr[j] > cur; j--){
////////				arr[j + 1] = arr[j];
////////			}
////////			arr[j + 1] = cur;
////////		}
////////	}
////////}
////////
/////////*
////////	ʱ�临�Ӷȣ��O(n^2)
////////
////////*/
////////void shellSort(int arr[], int len){
////////	int step = len / 2;
////////	while (step >= 1){
////////		for (int i = step; i < len;i++){
////////			for (int j = 1; j < len; j++){
////////				if (arr[j] < arr[j-1] ){
////////					int k = 0;
////////					int cur = arr[j];
////////					for (k = j - step; k >= 0 && cur < arr[k];k-=step){
////////						arr[k + step] = arr[k];
////////					}
////////					arr[k + step] = cur;
////////				}
////////			}
////////		}
////////		step /= 2;
////////	}
////////}
////////void swap(int arr[],int start,int min){
////////	int tmp = arr[start];
////////	arr[start] = arr[min];
////////	arr[min] = tmp;
////////}
/////////*
////////	ʱ�临�Ӷȣ��O(n^2) ƽ��O(n^2) ���O(n^2)
////////	�ռ临�Ӷȣ�O(1)
////////	�ȶ��ԣ��ȶ�
////////	�������У�������
////////*/
////////void selectSort(int arr[], int len){
////////	for (int i = 0; i < len;i++){
////////		int start = i;
////////		int min = start; // ��ʾ������Сֵ��λ��
////////		// ��δ���������������Сֵ
////////		for (int j = start + 1; j < len; j++){
////////			if ( arr[j] < arr[min]){
////////				min = j;
////////			}
////////		}
////////		if (start != min) // �ж�min�Ƿ�ı䣬����ı�ͽ��������򲻽���
////////			swap( arr , start , min);
////////	}
////////}
//////////void selectSort(int* arr, int len){
//////////	int begin = 0; 
//////////	int end = len - 1;
//////////	while (begin < end){
//////////		int min = begin, max = begin;
//////////		for (int i = begin+1; i <= end; i++){
//////////			if ()
//////////		}
//////////	}
//////////}
////////void test(){
////////	srand(time(NULL));
////////	// ����������
////////	int num = 0;
////////	scanf("%d",&num);
////////	int* arr = (int*)malloc(sizeof(int)*num);
////////	for (int i = 0; i < num;i++){
////////		arr[i] = rand();
////////	}
////////	int begin = clock();
////////	insertSort(arr, num);
////////	int end = clock();
////////	printf("������������ʱ��Ϊ:>%d\n", end - begin);
////////	display(arr, num);
////////	arr = (int*)malloc(sizeof(int)*num);
////////	for (int i = 0; i < num; i++){
////////		arr[i] = rand();
////////	}
////////	begin = clock();
////////	shellSort(arr, num);
////////	end = clock();
////////	printf("ϣ����������ʱ��Ϊ:>%d\n", end - begin);
////////	display(arr, num);
////////
////////	for (int i = 0; i < num; i++){
////////		arr[i] = rand();
////////	}
////////	begin = clock();
////////	selectSort(arr, num);
////////	end = clock();
////////	printf("ѡ����������ʱ��Ϊ:>%d\n", end - begin);
////////	display(arr, num);
////////}
////////int main(){
////////	test();
////////	//int arr[] = { 34,0,43,5,79,19,57,164,87,9,16 };
////////	//int len = sizeof(arr) / sizeof(arr[0]);
////////	//insert(arr, len);
////////	//display(arr, len);
////////	system("pause");
////////	return 0;
////////}
//////
////////
////////#include "BTree.h"
////////#include "queue.h" //�ο�֮ǰ�Ĵ���
////////#include "stack.h"
////////
////////BTNode *BinaryTreeCreate(BTDataType * src, int n, int* pi)
////////{
////////	if (src[*pi] == '#' || *pi >= n)
////////	{
////////		(*pi)++;
////////		return NULL;
////////	}
////////
////////	BTNode * cur = (BTNode *)malloc(sizeof(BTNode));
////////	cur->_data = src[s_n];
////////	(*pi)++;
////////
////////	cur->_left = BinaryTreeCreateExe(src);
////////	cur->_right = BinaryTreeCreateExe(src);
////////
////////	return cur;
////////}
////////
////////void BinaryTreePrevOrder(BTNode* root)
////////{
////////	if (root)
////////	{
////////		putchar(root->_data);
////////		BinaryTreePrevOrder(root->_left);
////////		BinaryTreePrevOrder(root->_right);
////////	}
////////}
////////
////////void BinaryTreeInOrder(BTNode* root)
////////{
////////	if (root)
////////	{
////////		BinaryTreeInOrder(root->_left);
////////		putchar(root->_data);
////////		BinaryTreeInOrder(root->_right);
////////	}
////////}
////////
////////void BinaryTreePostOrder(BTNode* root)
////////{
////////	if (root)
////////	{
////////		BinaryTreePostOrder(root->_left);
////////		BinaryTreePostOrder(root->_right);
////////		putchar(root->_data);
////////	}
////////}
////////
////////void BinaryTreeDestory(BTNode** root)
////////{
////////	if (*root)
////////	{
////////		BinaryTreeDestory((*root)->_left);
////////		BinaryTreeDestory((*root)->_right);
////////		free(*root);
////////		*root = NULL;
////////	}
////////}
////////
////////void BinaryTreeLevelOrder(BTNode* root)
////////{
////////	Queue qu;
////////	BTNode * cur;
////////
////////	QueueInit(&qu);
////////
////////	QueuePush(&qu, root);
////////
////////	while (!QueueIsEmpty(&qu))
////////	{
////////		cur = QueueTop(&qu);
////////
////////		putchar(cur->_data);
////////
////////		if (cur->_left)
////////		{
////////			QueuePush(&qu, cur->_left);
////////		}
////////
////////		if (cur->_right)
////////		{
////////			QueuePush(&qu, cur->_right);
////////		}
////////
////////		QueuePop(&qu);
////////	}
////////
////////	QueueDestory(&qu);
////////}
////////
////////int BinaryTreeComplete(BTNode* root)
////////{
////////	Queue qu;
////////	BTNode * cur;
////////	int tag = 0;
////////
////////	QueueInit(&qu);
////////
////////	QueuePush(&qu, root);
////////
////////	while (!QueueIsEmpty(&qu))
////////	{
////////		cur = QueueTop(&qu);
////////
////////		putchar(cur->_data);
////////
////////		if (cur->_right && !cur->_left)
////////		{
////////			return 0;
////////		}
////////
////////		if (tag && (cur->_right || cur->_left))
////////		{
////////			return 0;
////////		}
////////
////////		if (cur->_left)
////////		{
////////			QueuePush(&qu, cur->_left);
////////		}
////////
////////		if (cur->_right)
////////		{
////////			QueuePush(&qu, cur->_right);
////////		}
////////		else
////////		{
////////			tag = 1;
////////		}
////////
////////		QueuePop(&qu);
////////	}
////////
////////	QueueDestory(&qu);
////////	return 1;
////////}