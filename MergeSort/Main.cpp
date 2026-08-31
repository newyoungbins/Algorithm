#include <iostream>
#include <cstdlib>
#include <ctime>

// 비교 로직 전달을 위한 함수 포인터.
typedef bool (*Comparer)(int, int);

// LessEqual 함수.
bool LessEqual(int a, int b) { return a <= b; }

// GreaterEEqual 함수.
bool GreaterEqual(int a, int b) { return a >= b; }

// 분할된 배열을 병합하면서 정렬하는 함수.
void Merge(
	int* array,
	int* leftArray, int leftArrayLength,
	int* rightArray, int rightArrayLength)
{
	// 병합처리를 위한 인덱스.
	int leftIndex = 0;
	int rightIndex = 0;
	int mergedIndex = 0;

	// 오름차순 정렬로 구현.
	// 두 배열 각각의 현재 인덱스의 값을 비교해 작은 값을 array에 저장.
	while (leftIndex < leftArrayLength && rightIndex < rightArrayLength)
	{
		// 왼쪽 인덱스 기준으로 처리.
		if (leftArray[leftIndex] <= rightArray[rightIndex])
		{
			array[mergedIndex] = leftArray[leftIndex];
			++leftIndex;
		}
		// 오른쪽 배열의 값이 더 작은 경우.
		else
		{
			array[mergedIndex] = rightArray[rightIndex];
			++rightIndex;
		}

		// 병합된 배열의 인덱스 증가 처리.
		++mergedIndex;
	}

	// 왼쪽 배열에서 남은 원소를 복사.
	while (leftIndex < leftArrayLength)
	{
		array[mergedIndex] = leftArray[leftIndex];
		++leftIndex;
		++mergedIndex;
	}

	// 오른쪽 배열에서 남은 원소를 복사.
	while (rightIndex < rightArrayLength)
	{
		array[mergedIndex] = rightArray[rightIndex];
		++rightIndex;
		++mergedIndex;
	}
}

// 병합 정렬 함수 (재귀).
void MergeSort(int* array, int length)
{
	// 종료 조건 (더이상 분할할 수 없으면 종료).
	if(length <= 1)
	{
		return;
	}

	// 반으로 나누면서 분할 진행.
	// 중간 인덱스.
	int middle = length / 2;

	// 왼쪽으로 나눌 배열의 크기.
	int leftArrayLength = middle;

	// 오른쪽으로 나눌 배열의 크기(전체 크기에서 왼쪽 배열 크기를 뺌).
	int rightArrayLength = length - middle;

	// 분할된 배열 선언.
	int* leftArray = new int[leftArrayLength] {};
	int* rightArray = new int[rightArrayLength] {};

	// 분할된 배열에 값 복사.
	memcpy(leftArray, array, sizeof(int) * leftArrayLength);

	// 분할된 오른쪽 배열에 값 복사.
	memcpy(rightArray, array, sizeof(int) * rightArrayLength);

	// 분할을 이어서 진행 (재귀).
	MergeSort(leftArray, leftArrayLength);
	MergeSort(rightArray, rightArrayLength);

	// 분할이 재귀적으로 모두 끝나면 병합을 진행.
	Merge(array, leftArray, leftArrayLength, rightArray, rightArrayLength);

	// 사용한 배열 해제.
	delete[] leftArray;
	leftArray = nullptr;

	delete[] rightArray;
	rightArray = nullptr;
}

// 랜덤에 시드 값 적용하는 함수.
void SRand()
{
	srand(static_cast<uint32_t>(time(nullptr)));
}

// min에서 max 사이의 정수를 반환하는 랜덤 함수.
int RandomRange(int min, int max)
{
	// 범위 구하기.
	int diff = (max - min) + 1;
	return ((diff * rand()) / (RAND_MAX + 1)) + min;
}

int main()
{
	// 배열
	const int length = 100;

	// 정렬한 배열 선언.
	int* original = new int [length] {};

	// 랜덤을 활용해서 배열에 값 저장.
	for (int ix = 0; ix < length; ++ix)
	{
		original[ix] = RandomRange(1, length);
	}

	// 정렬에 사용할 배열.
	int* array = new int[length] {};

	// 메모리 통복사.
	memcpy(array, original, sizeof(int) * length);

	// 출력.
	auto printArray =[](int* array, int length)
		{
			for (int ix = 0; ix < length; ++ix)
			{
				std::cout << array[ix];

				if (ix < length - 1)
				{
					std::cout << ", ";
				}
			}

			std::cout << "\n\n";
		};

	// 배열 원소 출력.
	std::cout << "정렬 전 : ";
	printArray(array, length);

	// 정렬.
	MergeSort(array, length);

	std::cout << "정렬 후 : ";
	printArray(array, length);

	delete[] original;
	original = nullptr;

	delete[] array;
	array = nullptr;
}