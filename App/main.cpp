#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <chrono>
#include <algorithm>

#include "Duration.h"

std::chrono::nanoseconds nanotime()
{
	std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
	auto duration = now.time_since_epoch();
	return std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
}

void printArray(const std::vector<int> arr) {
	for (const auto &n : arr) {
		std::cout << n << " ";
	}
	std::cout << std::endl << std::endl;
}

std::vector<int> getRandomArray(const int size, const int min, const int max)
{
	srand(static_cast<unsigned int>(time(NULL)));

	std::vector<int> arr;

	for (int i = 0; i < size; ++i) {
		arr.push_back(min + rand() % (max - min + 1));
	}

	return arr;
}


void writeTextToFile(const std::vector<int> arr, const std::string &fileName)
{
	std::ofstream fout;

	fout.open(fileName);
	if (fout) {
		for (int i = 0; i < arr.size(); ++i) {
			fout << arr[i] << "\n";
		}
	}
	fout.close();
}


std::vector<int> readTextFromFile(const std::string path)
{
	std::vector<int> arr;
	std::ifstream fin;

	fin.open(path);

	if (fin) {
		int n;
		while (fin >> n) {
			arr.push_back(n);
		}
	}

	fin.close();

	return arr;
}

std::vector<int> bubbleSort(std::vector<int> arr)
{
	for (int i = 0; i < arr.size(); ++i) {
		for (int j = 0; j < arr.size() - 1; ++j) {

			if (arr[j + 1] < arr[j]) {
				int buff = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = buff;
			}
		}
	}

	return arr;
}

// int linearSearch(const std::vector<int> arr, const size_t num)
// {
// 	for (int i = 0; i < arr.size(); ++i) {
// 		if (arr[i] == num) {
// 			return i;
// 		}
// 	}

// 	return -1;
// }

int binaryRecursiveSearch(const std::vector<int> arr, const int num, int beg, int end)
{
	int mid = beg + (end - beg) / 2;

	if (num == arr[mid]) {
		return mid;
	}

	if (num < arr[mid]) {
		return binaryRecursiveSearch(arr, num, beg, mid - 1);
	}
	else {
		return binaryRecursiveSearch(arr, num, mid + 1, end);
	}
	return -1;
}

size_t binarySearch(const std::vector<int> arr, const int num, size_t beg, size_t end)
{
	while (beg <= end) {
		int mid = beg + (end - beg) / 2;

		if (arr[mid] == num) {
			return mid;
		}
		else if (arr[mid] < num) {
			beg = mid + 1;
		}
		else {
			end = mid - 1;
		}
	}
	return -1;
}

int linearSearch(const std::vector<int> &arr, const size_t num)
{
	for (int i = 0; i < 10; ++i) {
		// std::cout << arr[i] << std::endl;
		if (arr[i] == num) {
			return i;
		}
	}

	return -1;
}

int main()
{
	const int size = 100;
	const int min = 0;
	const int max = 100;

	const auto fileName = "RandomArray.txt";

	writeTextToFile(getRandomArray(size, min, max), fileName);

	std::vector<int> arr = readTextFromFile(fileName);
	// printArray(arr);
	const int wantFind = 8;

	std::vector<int> arr1;
	// arr1.push_back(wantFind);
	for (const auto &e : arr) {
		arr1.push_back(e);
	}

	// int *arr1 = new int[10];

	// for (int i = 0; i < 10; ++i) {
	// 	arr1[i] = i;
	// }

	//linear search
	{
		// const Duration d("Linear search time (nano): ");
		const auto res = linearSearch(arr1, wantFind);
		if (res < 0) {
			std::cout << res << "\n";
			return -1;
		}
		const auto lNum = arr1[res];
		std::cout << "Linear search found number: " << lNum << "\n";
	}

	//bubble sort
	std::vector<int> sortArr;
	{
		const Duration d("bubble sort time (nano): ");
		sortArr = bubbleSort(arr);
		// printArray(sortArr);
	}

	//linear search
	{
		const Duration d("Linear search time after sort (nano): ");
		const auto res = linearSearch(sortArr, wantFind);
		if (res == -1) {
			std::cout << "Can't fined: " << wantFind << "\n";
			return -1;
		}
		const auto lNum = sortArr[res];
		std::cout << "Linear search found number: " << lNum << "\n";
	}

	//binary Recursive search
	{
		const Duration d("Binary Recursive search time after sort (nano): ");
		const auto res = binaryRecursiveSearch(sortArr, wantFind, 0, sortArr.size());
		if (res == -1) {
			std::cout << "Can't fined: " << wantFind << "\n";
			return -1;
		}
		const auto bNum = sortArr[res];
		std::cout << "Binary Recursive search found number: " << bNum << "\n";
	}

	//binary search
	{
		const Duration d("Binary search time after sort (nano): ");
		const auto res = binarySearch(sortArr, wantFind, 0, sortArr.size());
		if (res == -1) {
			std::cout << "Can't fined: " << wantFind << "\n";
			return -1;
		}
		const auto bNum = sortArr[res];
		std::cout << "Binary search found number: " << bNum << "\n";
	}

	// //C++ find
	// {
	// 	const Duration d("Algorithm fined not sorted array (nano): ");
	// 	const auto it = std::ranges::find(arr, wantFind);
	// 	if (it == arr.end()) {
	// 		std::cout << "Can't fined: " << wantFind << "\n";
	// 		return -1;
	// 	}
	// 	std::cout << "Algorithm fined not sorted array: " << *it << "\n";
	// }

	// //C++ find
	// {
	// 	const Duration d("Algorithm fined sorted array (nano): ");
	// 	const auto it = std::ranges::find(sortArr, wantFind);
	// 	if (it == sortArr.end()) {
	// 		std::cout << "Can't fined: " << wantFind << "\n";
	// 		return -1;
	// 	}
	// 	std::cout << "Algorithm fined sorted array: " << *it << "\n";
	// }

	return 0;
}
