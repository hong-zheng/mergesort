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

// 三数取中
// 三数取中--> 找到三个数中的中间数
// 其最重要的目的就是防止序排序数组的有序情况，其时间复杂度为O(n^2)
// 在三个数中去中值极大的避免了这种已有序情况
int getMid(int* arr, int begin, int end){
	int mid = begin + (end - begin) / 2;
	// 先与中间值mid比较
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
	时间复杂度：
		满二叉树均衡划分 划分层次 logn
		时间复杂度 O(nlogn)
		最坏：数据有序的情况可能会崩掉，内存栈溢出，由于递归层数过多
			数据有序：划分：每次只能产生一个待划分的区间
					此时快速排序退化为冒泡排序：递归算法的递归深度太大，容易导致栈溢出
						调用栈太多，只有压栈，没有出栈，栈压满
			O(n^2)
			因此快排需要优化
				三数取中法
		平均情况 O(nlogn)
	空间复杂度：
		空间就是变量的个数
			栈的空间  函数调用栈 O(logn) ， 极端情况下就是O(n)
	稳定性：
		不稳定
		2 2 2 1：此时如果以第一个2作为基准值，则会发生变化，由于基准值需要发生变化，所以不稳定
	数据敏感与否：
			数据敏感

	·解决划分不均衡问题 
		  几个数中去取中间值作为基准值
		  begin mid end : 三数取中解决不均衡问题
		  三数取中法：可以把最坏的情况-->均衡划分


	·小区间优化 ，当划分在一定数据量时
		做正常的排序
		减少底层递归的调用次数，提高性能



	···快排注意事项
	三种划分： hora , 挖坑 ，前后指针
	优化：基准值的选取（三数取中），小区间优化（不再递归，减少底层调用）
	非递归：栈，队列 保存区间值
	最坏情况：数据有序，时间复杂度：优化之前：O(n^2)
									优化之后：O(nlogn) --> 基准值选择方法
			  如果是递归：优化之前栈溢出
*/
int getmid(int* arr, int begin, int end){
	int mid = begin + (end - begin) / 2;
	// begin , mid , end 选择中间值的位置
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

// 栈的实现

// 单链表: pushFront popFront
// 顺序表: pushBack popBack  优先选择 栈的实现基本上都是顺序表实现
//#pragma once
// 顺序表实现栈
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
	// 检查容量
	if (st->_size == st->_capacity){
		st->_capacity *= 2;
		st->_array = (Type*)realloc(st->_array, sizeof(Type)*st->_capacity);
	}
	st->_array[st->_size++] = data;
}
void stackPop(Stack* st){
	// 尾删
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
// 快排非递归算法
// 划分区间，先大区间后小区间
// 用栈实现非递归
// 先划分左边子区间，再划分右边子区间
		// 因此入栈时先右后左
// 区间入栈，每次获取栈顶区间，进行划分
// 划分之后的小区间继续入栈
// 直到栈为空结束
void quickAortNoR(int* arr, int n){
	Stack st;
	stackInit(&st,10);
	// 起始区间入栈
	if (n > 1){
	// 先入右再入左
		stackPush(&st, n - 1);
		stackPush(&st, 0);
	}
	// 遍历栈，划分栈中的每一个区间
	while (stackEmpty(&st) != 1){
		// 获取栈顶区间
		int begin = stackTop(&st);
		stackPop(&st);
		int end = stackTop(&st);
		stackPop(&st);

		// 划分
		int keyPos = partion(arr, begin, end);
		// 子区间入栈，为了保持入栈顺序一致，先入右区间，再入左区间
		//右边的子区间 keyPos+1 ， end
		if (keyPos + 1 < end){  // 至少有两个值
			stackPush(&st, end);
			stackPush(&st, keyPos + 1);
		}
		// 左，begin , keyPos-1
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

	// 创建一个结点，将该结点赋予data值，同时下一个元素指向NULL
	QNode* node = (QNode*)malloc(sizeof(QNode));
	node->_data = data;
	node->_next = NULL;
	return node;
}
void queueInit(Queue* q){
	// 初始化空队列
	// 空队列中并无元素，因此前后都指向空
	q->_front = q->_rear = NULL;
	q->_size = 0;
}
// 队尾入队，考虑空队列
void queuePush(Queue* q, QDataType data){
	// 尾插操作
	QNode* node = createNode(data);
	if (q->_front == NULL){
		// 考虑当前队列为空队列的情况，使首位都等于node
		q->_front = q->_rear = node;
	}
	else{
		q->_rear->_next = node;
		q->_rear = node;
	}
	q->_size++;
}
// 队头出队，出队需要释放，需要考虑只有一个结点的情况
void queuePop(Queue* q){
	/*	if (q->_front == NULL){
	return NULL;
	}else*/
	if (q->_front){
		// 记录下头的下一个结点
		QNode* next = q->_front->_next;
		// 释放头结点
		free(q->_front);
		//q->_front = NULL;
		q->_front = next;

		// 队列中只有一个元素，删除之后更新尾指针
		if (q->_front == NULL)
			q->_rear = NULL;
		q->_size--;
	}
}
// 获取队头元素
QDataType queueFront(Queue* q){
	return q->_front->_data;
}
// 获取队尾元素
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
	// 增加一个变量之后
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
// 用队列实现快速排序
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

// 队列实现非递归
void QuickSortQueue2(int* arr, int n){
	Queue q;
	queueInit(&q);
	if (n > 1){
	// 先左后右
		queuePush(&q, 0);
		queuePush(&q, n - 1);
	}
	// 判断队列是否为空
	while (queueEmpty(&q) != 1){
		// 获取队头区间
		int begin = queueFront(&q);
		queuePop(&q);
		int end = queueFront(&q);
		queuePop(&q);
		// 划分
		int keyPos = partion(arr, begin, end);
		// 划分完之后子区间入队
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

// 归并排序
// 合并：需要直到两个有序子列的区间[begin , mid] [mid+1 end]
void merge(int* arr, int begin, int mid, int end,int* tmp){
	int begin1 = begin, end1 = mid, begin2 = mid + 1, end2 = end;
	// indx 需要从当前位置开始，而不是每一次都从数组首元素开始，逻辑划分的区间头开始
	int indx = begin;	
	// 合并
	while (begin1 <= end1 && begin2 <= end2){
		if (arr[begin1] < arr[begin2]){
			tmp[indx++] = arr[begin1++];
		}
		else{
			tmp[indx++] = arr[begin2++];
		}
	}
	// 查看是否有剩余元素
	// 将剩余元素补上
	if (begin1 <= end1){
		memcpy(tmp + indx, arr + begin1, sizeof(int)*(end1 - begin1 + 1));
	}
	if (begin2 <= end2){
		memcpy(tmp + indx, arr + begin2, sizeof(int)*(end2 - begin2 + 1));
	}
	// 拷贝到原始空间
	memcpy(arr + begin, tmp + begin, sizeof(int)*(end - begin + 1));
}
// 要当前序列排序，则首先需要子区间有序
void MERGESORT(int* arr, int begin , int end,int* tmp){
	if (begin >= end) return;
	int mid = begin + (end - begin) / 2;

	// 首先保证子区间有序，首先子区间的有序
	MERGESORT(arr, begin, mid, tmp);
	MERGESORT(arr, mid + 1, end, tmp);
	merge(arr, begin, mid,end, tmp);
}
/*
	时间复杂度：O(nlogn)
	空间复杂度：O(n)
	稳定性：稳定
	数据敏感：不敏感
*/
void meresort(int* arr, int n){
	int* tmp = (int*)malloc(sizeof(int)*n);
	MERGESORT(arr, 0, n-1, tmp);
	free(tmp);
}


// 归并排序
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
	int k = 1; // 待合并区间的元素个数
	while (k < n){
		for (int i = 0; i < n; i += 2 * k)
		{
			int begin = i;
			// 判断mid是否越界
			int mid = i + k - 1;
			if (mid >= n - 1) // 此时只有一个子区间，直接跳过
				continue;
			// 判断end是否越界
			int end = i + 2 * k - 1;
			if (end >= n)// 虽然有需要合并的区间，但是有超过区间长度的，因此需要重置
				end = n - 1;
			merge(arr, begin, mid, end, tmp);
		}
		k *= 2;
	}
}
// 归并排序的非递归
// 归并排序的思想特别适合于外排序，逐段进行排序
void mergenor(int* arr, int len){
	int k = 1; // 定义每一次合并的区间元素个数
	int*  tmp = (int*)malloc(sizeof(int)*len);
	while (k < len){
		for (int i = 0; i < len; i += 2*k){ // 每一次合并都是两个区间的长度，因为合并的时候是两个区间进行合并
			int begin = i;
			int mid = i + k - 1;
			// 判断mid是否越界
			if (mid >= len - 1)
				continue;// 当mid为最后一个位置时，则只需要进行下一组
			int end = i + 2 * k - 1;
			if (end >= len)
				end = len - 1;
			merge(arr, begin, mid, end, tmp);
		}
		k *= 2;
	}
}
/*
	时间复杂度：O(max(len,范围))
	空间复杂度：O(range)
	稳定性：没有涉及到比较，暂不讨论稳定性：教材说的是稳定！
	数据敏感：不敏感
	基数排序：只符合小范围数据，如果范围比较大，空间复杂度较高
	因此适合对字符排序
*/
// 基数排序：非比较排序
void countsort(int* arr, int len){
	// 统计范围
	int min = arr[0], max = arr[0];
	for (int i = 1 ; i < len; i++){
		if (arr[i] > max)
			max = arr[i];
		if (arr[i] < min)
			min = arr[i];
	}
	int range = max - min + 1;
	// 开辅助空间，进行计数
	int* countArr = (int*)malloc(sizeof(int)*range);
	// 初始化为0
	memset(countArr, 0, sizeof(int)*range);
	// 统计次数
	for (int i = 0; i < len; i++){
		countArr[arr[i] - min]++;
	}
	// 恢复数据，遍历计数数组
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
//// 三数取中
//int getMid(int* array, int begin, int end){
//	int mid = begin + (end - begin) / 2;
//	// begin , mid , end 选取中间值的位置
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
//	// 交换 mid -- begin
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
//// 栈实现非递归 ：保存待划分区间
//void quikSortNoR(int* array, int n){
//
//}
//// 合并 ， 需要知道 两个有序子序列的区间
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
//	// 查看是否有剩余元素
//	if (begin1 < end1){
//		memcpy(tmp + indx, arr + begin1, sizeof(int)*(end1 - begin1 + 1));
//	}
//	if (begin2 < end2){
//		memcpy(tmp + indx, arr + begin2, sizeof(int)*(end2 - begin2 + 1));
//	}
//	// 拷贝到原始空间
//	memcpy(arr + begin, tmp + begin, sizeof(end - begin + 1));
//}
//void mergesortR(int* arr, int begin , int end,int* tmp){
//	if (begin == end) return;
//	int mid = begin + (end - begin) / 2;
//	// 首先保证子区间有序，首先子区间的排序
//	mergesortR(arr, begin, mid, tmp);
//	mergesortR(arr, mid + 1, end, tmp);
//
//	// 合并子区间
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
////	// 定义数据量
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
////	printf("最终排序为:>");
////	display(arr, num);
////	printf("堆排序所费时间为:>%d\n", end - begin);
////}
////
////int main(){
////	testPartion();
////
////	system("pause");
////	return 0;
////}
////
////// 快速排序
////// 前后指针法
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
////	// 定义数据量
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
////	printf("最终排序为:>");
////	display(arr, num);
////	printf("堆排序所费时间为:>%d\n", end - begin);
////}
////int mawin(void){
////
////	testPartion();
////	system("pause");
////	return 0;
////}
//////// 快排 分治的思想，不断的进行切分
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
//////// hora划分
//////int partion(int arr[], int begin, int end){
//////	// 选择基准值
//////	int start = begin;
//////	int key = arr[begin];
//////	// 划分
//////	while (begin < end){
//////		while (begin < end&&arr[begin] <= key){
//////			begin++;
//////		}
//////		// 从后向前找到第一个小于key的位置
//////		// 相等的时候也要移动，否则就大于key
//////		while (begin < end && arr[end] >= key)
//////			--end;
//////		// 从前向后找第一个大于key的位置
//////		// 相等时也要移动，否则会小于key
//////
//////		swap(arr, begin, end);
//////	}
//////	// key 和相遇位置的数据交换
//////	swap(arr, start, begin);
//////	return begin;
//////}
//////
////////挖坑法
//////int partion2(int arr[], int begin, int end){
//////	int key = arr[begin];
//////	while (begin < end){
//////		// 从后至前
//////		while (begin < end && arr[begin] >= key){
//////			--end;
//////		}
//////		arr[begin] = arr[end];
//////		// 从前至后
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
//////	// 划分当前区间
//////	// 划分之后的当前位置
//////	int keyPos = partion(arr, begin, end);
//////	// 划分子区间
//////	qsort(arr, begin, keyPos - 1);
//////	qsort(arr, keyPos+1,end );
//////}
//////void testsort(){
//////	srand(time(NULL));
//////	// 定义数据量
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
//////	printf("最终排序为:>");
//////	display(arr, num);
//////	printf("堆排序所费时间为:>%d\n", end - begin);
//////}
//////int main(){
//////	testsort();
//////	system("pause");
//////	return 0;
//////}
/////////*
////////	时间复杂度：O(nlog(n))
////////	空间复杂度：O(1)
////////	稳定性：不稳定
////////	数据敏感度：不敏感
////////*/
////////void shiftDown(int arr[], int len, int parent){
////////	if (parent < 0)
////////		return;
////////	int child = 2 * parent + 1;
////////	while (child < len){
////////		// 找到小的孩子
////////		if (child + 1 < len && arr[child + 1] < arr[child])
////////			child++;
////////		// 比较小孩子与父亲的关系
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
////////	// 建堆
////////	for (int parent = (len - 2) / 2; parent >= 0; parent--){
////////		shiftDown(arr, len, parent);
////////	}
////////
////////	// 排序
////////	for (int i = len-1; i >=0; i--){
////////		swap(arr, i, 0);
////////		shiftDown(arr, i, 0);
////////	}
////////}
////////void testsort(){
////////	srand(time(NULL));
////////	// 定义数据量
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
////////	printf("最终排序为:>");
////////	display(arr, num);
////////	printf("堆排序所费时间为:>%d\n", end - begin);
////////}
////////int maien(){
////////	testsort();
////////	system("pause");
////////	return 0;
////////}
/////////*
////////	时间复杂度：最坏O(n^2) 平均O(n^2) 最好O(n)
////////	空间复杂度：O(1)
////////	稳定性：稳定
////////	数据敏感度：敏感
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
////////	// 从后向前比较，把小的放在前面
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
////////		// 一轮冒泡排序
////////		for (int i = 0; i<end; i++){
////////			// 相邻元素进行比较
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
////////	// 定义数据量
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
////////	printf("最终排序为:>");
////////	display(arr, num);
////////	printf("堆排序所费时间为:>%d\n", end - begin);
////////}
////////int main(){
////////	int n = testsort();
////////	//printf("%d", n);
////////	system("pause");
////////	return 0;
////////}
////////// 快速排序
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
//////// hore 划分
////////int partion(int arr[], int begin, int end){
////////	// 选择基准值
////////	int key = arr[begin];
////////	int start = begin;
////////	// 划分
////////	while (begin < end){
////////		// 从后向前找第一个小于key的位置
////////		while (begin < end && arr[end] >= key){
////////			--end;
////////		}
////////		// 从前向后找第一个大于key的位置
////////		while (begin < end && arr[begin] <= key){
////////			++begin;
////////		}
////////		//  交换end , begin数据
////////		swap(arr, begin, end);
////////	}
////////
////////	// key和相遇位置数据交换
////////	swap(arr, start, begin);
////////	return begin;
////////}
////////void quitSort(int arr[], int begin, int end){
////////	if (begin >= end){
////////		return;
////////	}
////////	// 划分当前区间
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
////////		// 从后先前找
////////		while (l < h && arr[h] > key){
////////			h--;
////////		}
////////		arr[l] = arr[h];
////////		// 从前向后找大于key的值
////////		while (l < h && arr[l] < key){
////////			l++;
////////		}
////////		arr[h] = arr[l];
////////	}
////////	// 最后一个坑，相遇的位置-->填充基准值
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
////////// 前后指针法
////////int partion3(int* arr, int begin, int end){
////////	// prev ： 最后一个小于基准值的位置
////////	int prev = begin;
////////	// cur：新发现的下一个小于基准值的位置
////////	int cur = prev + 1;
////////	int key = arr[begin];
////////	while (cur <= end){
////////		// 新发现的小数据和尾指针指向的位置不连续，则中间含有大于基准值的数据
////////		// 大数据向后移动，小数据向前移动
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
////////	// 定义数据量
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
////////	printf("堆排序所费时间为:>%d\n", end - begin);
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
////////	// 定义数据量
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
////////	printf("堆排序所费时间为:>%d\n", end - begin);
////////	//begin = clock();
////////	//heapSort(arr, num);
////////	//end = clock();
////////	////display(arr, num);
////////	//printf("排好序之后的希尔排序所费时间为:>%d\n", end - begin);
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
////////	时间复杂度：最坏O(n^2) 平均(n^2) 最好O(n)
////////	空间复杂度：O(1)
////////	稳定性：稳定
////////	数据敏感度：敏感
////////*/
////////void bubbleSort(int arr[], int len){
////////	while( len ){
////////		int end = len;
////////		// 一轮冒泡排序
////////		for (int i = 0; i<end - 1; i++){
////////			// 相邻元素进行比较
////////			if (arr[i] > arr[i + 1]){
////////				swap(arr, i, i + 1);
////////			}
////////		}
////////		len--;
////////	}
////////}
////////
////////// 优化
////////// 满足关系不需要再交换
////////void bubbleSort1(int arr[], int len){
////////	while (len){
////////		// 对于已经有序的序列，通过标签提前结束排序过程
////////		int flag = 1; // 表示是否发生交换，1 表示一轮过程中没有发生交换
////////		int end = len;
////////		// 一轮冒泡排序
////////		for (int i = 0; i<end - 1; i++){
////////			// 相邻元素进行比较
////////			if (arr[i] > arr[i + 1]){
////////				swap(arr, i, i + 1);
////////				flag = 0;
////////			}
////////		}
////////		// flag 标志任意一轮中没有发生交换便可以直接退出
////////		// 没有发生交换
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
////////	// 定义数据量
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
////////	printf("冒泡排序所费时间为:>%d\n", end - begin);
////////	begin = clock();
////////	bubble(arr, num);
////////	end = clock();
////////	//display(arr, num);
////////	printf("排好序之后的希尔排序所费时间为:>%d\n", end - begin);
////////}
////////int maisn(){
////////	testBubble();
////////	system("pause");
////////	return 0;
////////}
////////
/////////*
////////	时间复杂度：最坏时间复杂度,当数据逆序时O(n^2)；平均 O(n^2)；最好O(n^2)
////////	空间复杂度：O(1)
////////	稳定性：稳定
////////	数据敏感度：不敏感
////////*/
////////void selectSort(int arr[], int len){
////////	for (int i = 0; i < len; i++){
////////		int start = i;
////////		int min = i;
////////		// 从剩余的元素中找最小值
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
////////// 该种时间排序减小了时间复杂度 O(n*log(n))
////////void selectSort1(int arr[], int len){
////////	int begin = 0;
////////	int end = len - 1;
////////	while (begin < end){
////////		// 每一次选择最大值和最小值
////////		int min = begin, max = begin;
////////		for (int i = begin + 1; i <= end;i++){
////////			if (arr[i] > arr[max])
////////				max = i;
////////			if (arr[i] < arr[min]) // 不稳定的排序
////////				min = i;
////////		}
////////		// 最小值放在begin
////////		swap(arr, begin, min);
////////		// 如果最大值放在begin处，此时的begin已被交换至min处，此时需要将max的位置改为min处
////////		if (max == begin) 
////////			max = min;
////////		// 最大值放在end
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
////////	printf("选择排序所费时间为:>%d\n", end - begin);
////////	begin = clock();
////////	selectSort1(arr, num);
////////	end = clock();
////////	display(arr, num);
////////	printf("排好序之后的再排所费时间为:>%d\n", end - begin);
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
////////时间复杂度：最坏时间复杂度,当数据逆序时O(n^2)；平均 O(n^1.3)；最好O(n)
////////空间复杂度：只有几个临时变量O(1)
////////稳定性：不稳定 -->分组时，相同数据不一定分到同一组，元素发生跳跃性的移动，并非顺序性的移动
////////数据敏感度：敏感
////////*/
////////void  shellSort(int array[], int len){
////////	int gap = len; // 步长
////////	// 多轮的插入排序
////////	while (gap > 1){
////////		gap = gap / 3 + 1; // 需要保证最后是一个普通的插入排序
////////		// 一轮插入排序
////////		for (int i = 0; i < len - gap; ++i){
////////			// 通过步长gap进行逻辑分组
////////			// 组内进行插入排序
////////			// 不同的元素交替进行排序
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
////////	// 确定步长，初始化步长，最后一定要为一个普通插入排序
////////	int step = len / 2;
////////	while (step >= 1){// 当步长为1时就是一个普通的插入排序
////////		// 从当前步长开始进行排序
////////		for (int i = step; i < len; i++){
////////			// 当前组内的前一个元素
////////			int j = i - step;
////////			// 当前元素
////////			int cur = arr[i];
////////			// 对当前位置的元素与组内前面已经排好序的元素比较，后移，直至不满足条件为止
////////			while (j >= 0 && cur<arr[j]){
////////				arr[j + step] = arr[j];
////////				j -= step;
////////			}
////////			// 插入当前元素
////////			arr[j + step] = cur;
////////		}
////////		step /= 2;
////////	}
////////}
////////
////////void testShell(){
////////	void shl(int arr[], int len);
////////	srand(time(NULL));
////////	// 定义数据量
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
////////	printf("希尔排序所费时间为:>%d\n", end - begin);
////////	begin = clock();
////////	shl(arr, num);
////////	end = clock();
////////	//display(arr, num);
////////	printf("排好序之后的希尔排序所费时间为:>%d\n", end - begin);
////////}
////////
/////////*
////////	时间复杂度：最坏时间复杂度,当数据逆序时O(n^2)；平均 O(n^2)；最好O(n)
////////	空间复杂度：只有几个临时变量O(1)
////////	稳定性：稳定
////////	数据敏感度：敏感
////////*/
////////void insertSort(int arr[], int len){
////////	// i ： 表示有序数据的最后一个位置
////////	for (int i = 0; i < len - 1; i++){
////////		// end 表示有序序列的最后一个位置
////////		int end = i;
////////		// 待插入数据，有序数据的最后位置的后一个位置
////////		int key = arr[end + 1];
////////		// 找到第一个 小于等于key 的位置
////////		while (end >= 0 && arr[end] > key){
////////			// 当前数据向后移动一个位置
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
////////	时间复杂度：最坏时间复杂度,当数据逆序时O(n^2)；平均 O(n^1.3)；最好O(n)
////////	空间复杂度：只有几个临时变量O(1)
////////	稳定性：不稳定 -->分组时，相同数据不一定分到同一组，元素发生跳跃性的移动，并非顺序性的移动
////////	数据敏感度：敏感
////////*/
////////void  shellSort(int array[] , int len){
////////	int gap = len; // 步长
////////	// 多轮的插入排序
////////	while (gap > 1){
////////		gap = gap / 3 + 1; // 需要保证最后是一个普通的插入排序
////////		// 一轮插入排序
////////		for (int i = 0; i < len - gap; ++i){
////////			// 通过步长gap进行逻辑分组
////////			// 组内进行插入排序
////////			// 不同的元素交替进行排序
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
////////	// 确定步长，初始化步长，最后一定要为一个普通插入排序
////////	int step = len / 2;
////////	while (step >= 1){// 当步长为1时就是一个普通的插入排序
////////		// 从当前步长开始进行排序
////////		for (int i = step; i < len;i++){
////////			// 当前组内的前一个元素
////////			int j = i - step;
////////			// 当前元素
////////			int cur = arr[i];
////////			// 对当前位置的元素与组内前面已经排好序的元素比较，后移，直至不满足条件为止
////////			while (j>=0 && cur<arr[j]){
////////				arr[j + step] = arr[j];
////////				j -= step;
////////			}
////////			// 插入当前元素
////////			arr[j + step] = cur;
////////		}
////////		step /= 2;
////////	}
////////}
////////
////////void testShell(){
////////		void shl(int arr[], int len);
////////		srand(time(NULL));
////////		// 定义数据量
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
////////		printf("希尔排序所费时间为:>%d\n", end - begin);
////////		begin = clock();
////////		shl(arr, num);
////////		end = clock();
////////		//display(arr, num);
////////		printf("排好序之后的希尔排序所费时间为:>%d\n", end - begin);
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
////////	时间复杂度：最坏O(n^2) 平均O(n^2) 最好O(n)
////////	空间复杂度：O(1)
////////	稳定性：稳定
////////	数据敏感：敏感
////////*/
////////void insertSort(int arr[], int len){
////////	for (int i = 0; i < len - 1;i++){
////////		// 新数据的插入
////////		// end ： 有序序列的最后一个位置
////////		int end = i;
////////		// key ： 待插入数据
////////		int key = arr[end + 1];
////////		// 找到第一个小于等于key的位置
////////		while (end >= 0 && arr[end] > key){
////////			// 当前数据向后移动
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
////////	时间复杂度：最坏O(n^2)
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
////////	时间复杂度：最坏O(n^2) 平均O(n^2) 最好O(n^2)
////////	空间复杂度：O(1)
////////	稳定性：稳定
////////	数据敏感：不敏感
////////*/
////////void selectSort(int arr[], int len){
////////	for (int i = 0; i < len;i++){
////////		int start = i;
////////		int min = start; // 表示的是最小值的位置
////////		// 从未排序的数据中找最小值
////////		for (int j = start + 1; j < len; j++){
////////			if ( arr[j] < arr[min]){
////////				min = j;
////////			}
////////		}
////////		if (start != min) // 判断min是否改变，如果改变就交换，否则不交换
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
////////	// 定义数据量
////////	int num = 0;
////////	scanf("%d",&num);
////////	int* arr = (int*)malloc(sizeof(int)*num);
////////	for (int i = 0; i < num;i++){
////////		arr[i] = rand();
////////	}
////////	int begin = clock();
////////	insertSort(arr, num);
////////	int end = clock();
////////	printf("插入排序所费时间为:>%d\n", end - begin);
////////	display(arr, num);
////////	arr = (int*)malloc(sizeof(int)*num);
////////	for (int i = 0; i < num; i++){
////////		arr[i] = rand();
////////	}
////////	begin = clock();
////////	shellSort(arr, num);
////////	end = clock();
////////	printf("希尔排序所费时间为:>%d\n", end - begin);
////////	display(arr, num);
////////
////////	for (int i = 0; i < num; i++){
////////		arr[i] = rand();
////////	}
////////	begin = clock();
////////	selectSort(arr, num);
////////	end = clock();
////////	printf("选择排序所费时间为:>%d\n", end - begin);
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
////////#include "queue.h" //参考之前的代码
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