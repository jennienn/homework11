/*
 * sorting-hashing.c
 *
 *  Sorting & Hashing
 *  School of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필여에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a); /* 선택 정렬 함수 */
int insertionSort(int *a); /* 삽입 정렬 함수 */
int bubbleSort(int *a); /* 버블 정렬 함수 */
int shellSort(int *a); /* 셸 정렬 함수 */

/* 퀵 정렬 함수 (재귀 함수로 구현) */
int quickSort(int *a, int n);

/* 해시 코드 생성기, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* 배열 a에 대한 해시 테이블을 만든다 */
int hashing(int *a, int **ht);

/* 해시 테이블에서 key를 검색하여 해당하는 인덱스를 반환하는 함수 */
int search(int *ht, int key);

int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

    printf("[----- [김예진]  [2022041035] -----]\n");

	srand(time(NULL));

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* 배열이 NULL인 경우 메모리 할당 */
    if(*a == NULL) {
        temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
        *a = temp;  /* 할당된 메모리의 주소를 복사 -->  main 함수에서 control할 수 있음 */
    } else
        temp = *a;

    /* 임의의 숫자를 배열에 저장 */
    for(int i = 0; i < MAX_ARRAY_SIZE; i++)
        temp[i] = rand() % MAX_ARRAY_SIZE;

    return 0;

}

int freeArray(int *a)
{
	if(a != NULL)
		free(a);
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a)
{
    int min;           // 최소값을 저장할 변수
    int minindex;      // 최소값의 인덱스를 저장할 변수
    int i, j;

    printf("Selection Sort: \n");
    printf("----------------------------------------------------------------\n");

    printArray(a);     // 정렬 이전의 배열 출력

    for (i = 0; i < MAX_ARRAY_SIZE; i++)   // 배열의 모든 요소를 순회
    {
        minindex = i;   // 현재 인덱스를 최소값 인덱스로 설정
        min = a[i];     // 현재 인덱스의 값을 최소값으로 설정

        // 현재 인덱스보다 큰 인덱스를 찾아 최소값을 업데이트
        for (j = i + 1; j < MAX_ARRAY_SIZE; j++)
        {
            if (min > a[j])
            {
                min = a[j];
                minindex = j;
            }
        }

        // 최소값과 현재 인덱스의 값을 교환
        a[minindex] = a[i];
        a[i] = min;
    }

    printf("----------------------------------------------------------------\n");
    printArray(a);     // 정렬 이후의 배열 출력
    return 0;
}


int insertionSort(int *a)
{
    int i, j, t;

    printf("삽입 정렬: \n");
    printf("----------------------------------------------------------------\n");

    printArray(a); // 배열의 초기 상태를 출력

    for(i = 1; i < MAX_ARRAY_SIZE; i++)
    {
        t = a[i]; // 현재 위치의 값을 임시 변수 t에 저장
        j = i;
        while (a[j-1] > t && j > 0)
        {
            a[j] = a[j-1]; // 현재 위치의 값보다 큰 값을 오른쪽으로 한 칸씩 이동
            j--;
        }
        a[j] = t; // 올바른 위치에 현재 값을 삽입
    }

    printf("----------------------------------------------------------------\n");
    printArray(a); // 정렬된 배열을 출력

    return 0;
}


int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");  // 버블 정렬을 수행한다는 메시지 출력
	printf("----------------------------------------------------------------\n");

	printArray(a);  // 정렬되기 전 배열 출력

	for(i = 0; i < MAX_ARRAY_SIZE; i++)  // 배열의 모든 요소에 대해 반복
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)  // 배열의 모든 요소에 대해 반복
		{
			if (a[j-1] > a[j])  // 현재 요소와 그 이전 요소를 비교하여 정렬이 필요한 경우
			{
				t = a[j-1];  // 현재 요소를 임시 변수에 저장
				a[j-1] = a[j];  // 현재 요소를 이전 요소로 이동
				a[j] = t;  // 임시 변수 값을 현재 요소로 이동
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);  // 정렬된 배열 출력

	return 0;
}


int shellSort(int *a)
{
    int i, j, k, h, v;

    printf("셸 정렬: \n");  // 셸 정렬을 수행하는 함수
    printf("----------------------------------------------------------------\n");

    printArray(a);  // 주어진 배열을 출력

    for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)  // 간격 h를 초기화하고 h를 반으로 줄여가며 반복
    {
        for (i = 0; i < h; i++)  // h 간격으로 구분된 그룹을 생성하여 반복
        {
            for(j = i + h; j < MAX_ARRAY_SIZE; j += h)  // 그룹 내의 요소들을 h 간격으로 비교 및 정렬
            {
                v = a[j];  // 현재 위치의 값을 보관
                k = j;
                while (k > h-1 && a[k-h] > v)  // 그룹 내의 이전 위치에 있는 요소와 비교하여 정렬
                {
                    a[k] = a[k-h];  // 값을 뒤로 이동
                    k -= h;  // h 간격만큼 이전 위치로 이동
                }
                a[k] = v;  // 적절한 위치에 값을 삽입
            }
        }
    }
    printf("----------------------------------------------------------------\n");
    printArray(a);  // 정렬된 배열을 출력

    return 0;
}


int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1];  // 피벗(pivot)으로 배열의 마지막 요소를 선택
		i = -1;     // i는 피벗보다 작은 요소들의 인덱스를 나타냄
		j = n - 1;  // j는 피벗보다 큰 요소들의 인덱스를 나타냄

		while(1)
		{
			while(a[++i] < v);  // 피벗보다 작은 요소를 찾을 때까지 i를 증가
			while(a[--j] > v);  // 피벗보다 큰 요소를 찾을 때까지 j를 감소

			if (i >= j) break;  // i와 j가 교차하면 반복문을 종료

			t = a[i];     // a[i]와 a[j]를 교환
			a[i] = a[j];
			a[j] = t;
		}

		t = a[i];            // 피벗을 올바른 위치로 이동
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i);     // 피벗을 기준으로 왼쪽 부분 배열을 재귀적으로 정렬
		quickSort(a+i+1, n-i-1);  // 피벗을 기준으로 오른쪽 부분 배열을 재귀적으로 정렬
	}

	return 0;
}


int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE; // 주어진 키를 해시 테이블 크기로 나눈 나머지 값을 반환하는 해시 함
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* 해시 테이블이 NULL인 경우에만 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); /* 메모리를 동적으로 할당하여 해시 테이블을 생성 */
		*ht = hashtable;  			/* 할당한 메모리의 주소를 전달 --> main 함수에서 배열을 제어할 수 있도록 함 */
	} else {
		hashtable = *ht;  /* 해시 테이블이 NULL이 아닌 경우, 테이블을 재설정하고 모든 요소를 -1로 초기화 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;  // 해시 테이블의 모든 요소를 -1로 초기화

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];  // 주어진 배열의 요소를 키로 설정
		hashcode = hashCode(key);  // 키를 해시 함수에 적용하여 해시 코드를 계산

		if (hashtable[hashcode] == -1)
		{
			hashtable[hashcode] = key;  // 계산된 해시 코드의 인덱스에 해당하는 해시 테이블 요소가 비어있으면 해당 키를 저장
		} else 	{
			index = hashcode;

			while(hashtable[index] != -1)
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;  // 해시 테이블 요소가 비어있지 않으면 선형 탐색을 수행하여 다음 비어있는 인덱스를 찾음
			}
			hashtable[index] = key;  // 다음 비어있는 인덱스에 키를 저장
		}
	}

	return 0;  // 해싱이 완료되면 함수를 종료

}

int search(int *ht, int key)
{
    int index = hashCode(key); // key를 해시코드로 변환하여 인덱스에 할당

    if (ht[index] == key) // 인덱스 위치에 있는 값이 key와 동일한 경우
        return index; // 인덱스를 반환

    while (ht[++index] != key) // 인덱스 위치에 있는 값이 key와 다른 경우
    {
        index = index % MAX_HASH_TABLE_SIZE; // 인덱스를 해시 테이블 크기로 나눈 나머지를 새로운 인덱스로 설정
    }
    return index; // 인덱스를 반환
}


