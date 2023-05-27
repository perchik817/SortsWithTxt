#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <cctype>
#include <numeric>
#include <iomanip> 
#include <locale>
#include <regex>
#include <sstream>
#include <iterator>
#include <cstdlib>
#include <ctime>

using namespace std;

string bubbleSort_filename = "BubbleSort.txt", batcherSort_filename = "BatcherSort.txt",
lowDensitySort_filename = "LowDensitySort.txt", outputFilename;

int num, bign, count_of_lines = 0, count_of_nums = 0, num_digits = 0;

vector<int> numbers;

ifstream arrayfile("array.txt");

void clearFile(string& outputFilename) {
	ofstream outputFile(outputFilename, ios::trunc);
	if (!outputFile.is_open()) {
		cout << "Unable to clear file";
	}
	outputFile.close();
}

void file(string& outputFilename) {
	ofstream outputFile(outputFilename, ios::app);
	if (outputFile.is_open()) {
		for (int i = 0; i < numbers.size(); i++) {
			outputFile << numbers[i] << " ";
			count_of_nums++;
			num_digits += log10(numbers[i]) + 1;
			if (numbers[i] > numbers[i] + 1) {
				bign = numbers[i];
			}
			else {
				bign = numbers[i] + 1;
			}
		}
		outputFile << endl;
		count_of_lines = count_of_nums / numbers.size();

		outputFile.close();
	}
	else {
		cout << "Unable to open file";
	}
}

void file2(string& outputFilename, int& count_of_nums, int& num_digits, int& count_of_lines, int& bign) {
	ofstream outputFile(outputFilename, ios::app);
	if (outputFile.is_open()) {
		outputFile << endl << "Количество строк: " << count_of_lines << endl;
		outputFile << "Количество чисел: " << count_of_nums << endl;
		outputFile << "Количество цифр: " << num_digits << endl;
		outputFile << "Самое большое число: " << bign - 1;

		outputFile.close();
	}
	else {
		cout << "Unable to open file";
	}
}

void bubbleSort(vector<int>& numbers) {
	cout << "bubbleSort" << endl;
	int n = numbers.size();
	int count = 0;
	clearFile(bubbleSort_filename);
	for (int i = 0; i < n - 1; i++) {
		file(bubbleSort_filename);
		for (int j = 0; j < n - i - 1; j++) {

			if (numbers[j] > numbers[j + 1]) {
				int temp = numbers[j];
				numbers[j] = numbers[j + 1];
				numbers[j + 1] = temp;
				count++;
			}
		}
		cout << "Sorted array: ";
		for (int i = 0; i < numbers.size(); i++) {
			cout << numbers[i] << " ";
		}
		cout << endl;
	}
	file2(bubbleSort_filename, count_of_nums, num_digits, count_of_lines, bign);
}

void lowDensitySort(vector<int>& numbers) {
	cout << "lowDensitySort" << endl;
	int n = numbers.size();
	int count = 0;
	int gap = n / 2;
	clearFile(lowDensitySort_filename);
	while (gap > 0) {
		file(lowDensitySort_filename);
		for (int i = gap; i < n; i++) {
			int temp = numbers[i];
			int j = i;
			while (j >= gap && numbers[j - gap] > temp) {
				numbers[j] = numbers[j - gap];
				j -= gap;
			}
			numbers[j] = temp;
		}
		cout << "Updated array: ";
		for (int i = 0; i < n; i++) {
			cout << numbers[i] << " ";
		}
		cout << endl;

		gap /= 2;
		count++;
	}
	file2(lowDensitySort_filename, count_of_nums, num_digits, count_of_lines, bign);
}

void merge(vector<int>& numbers, int l, int m, int r) {
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;
	vector<int> L(n1), R(n2);
	for (i = 0; i < n1; i++) {
		L[i] = numbers[l + i];
	}
	for (j = 0; j < n2; j++) {
		R[j] = numbers[m + 1 + j];
	}
	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			numbers[k] = L[i];
			i++;
		}
		else {
			numbers[k] = R[j];
			j++;
		}
		k++;
	}
	while (i < n1) {
		numbers[k] = L[i];
		i++;
		k++;
	}
	while (j < n2) {
		numbers[k] = R[j];
		j++;
		k++;
	}
}

void batcherSort(vector<int>& numbers, int l, int r) {
	int count = 0;
	clearFile(batcherSort_filename);
	if (l >= r) {
		return;
	}
	int mid = (l + r) / 2;

	batcherSort(numbers, l, mid);
	batcherSort(numbers, mid + 1, r);

	for (int i = l; i <= mid; i++) {
		file(batcherSort_filename);
		for (int j = mid + 1; j <= r; j++) {
			if (numbers[i] > numbers[j]) {
				int temp = numbers[i];
				numbers[i] = numbers[j];
				numbers[j] = temp;
				count++;
			}
		}
	}
	for (int k = mid; k > l; k--) {
		for (int i = l, j = k; j < r; i++, j++) {
			if (numbers[i] > numbers[j + 1]) {
				int temp = numbers[i];
				numbers[i] = numbers[j + 1];
				numbers[j + 1] = temp;
				count++;
			}
		}
	}
	cout << "Updated array: ";
	for (int x = 0; x < numbers.size(); x++) {
		cout << numbers[x] << " ";
	}
	cout << endl;

}


int main() {
	setlocale(LC_ALL, "Russian");
	if (arrayfile.is_open()) {
		while (arrayfile >> num) {
			numbers.push_back(num);
		}
	}
	arrayfile.close();

	//bubbleSort(numbers);

	lowDensitySort(numbers);

	//cout << endl << "batcherSort" << endl;
	//batcherSort(numbers, 0, numbers.size() - 1);
	//file2(batcherSort_filename, count_of_nums, num_digits, count_of_lines, bign);
	return 0;
}