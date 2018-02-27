/*
* ����� ��� ������������� ������� �������� �� n ����� ���������
* �������� �������:
* ���������� ��������� � ������
* ������ ������� �� �����
* ���������� ������� �� ���������� ��������� � ����������
* ���������� ����� ����������(������) ��������
*/
#pragma once
#include "SetOfNumbers.h"

class SetsOfNumbers {

private:
	//������ ���������� ��������� ��������
	int numSet = 0;
	//������ ��������
	SetOfNumbers *arrayS;

public:
	void addSetOfNumbers(SetOfNumbers&); //���������� ��������� � ������
	void outputMonitor(); //����� �� �����
						  //������� ���������� �� ���������� ��������� � ����������
	void sortByNumberElements(int left, int righ);
	int numberEqualArrays(); // ����� ������ ��������
	void unionSets(); //����� ���� ��������� �������

					  //������������ � ����������
	SetsOfNumbers();
	SetsOfNumbers(int);
	~SetsOfNumbers();
};


//====������������ � ����������====
/*
* �� ���������
* ����� ������ ������
*/
SetsOfNumbers::SetsOfNumbers() {
	arrayS = new SetOfNumbers[0];
}

/*
* ������ ������ � �������� ������ ���������
* �������� number - ����� ���������
*/
SetsOfNumbers::SetsOfNumbers(int number) {
	arrayS = new SetOfNumbers[number];
}

SetsOfNumbers::~SetsOfNumbers() {
	delete[] arrayS;
}




//====�������====
/*
* ������� ��������� ����������� � ������
* ��������: ��������� ������ SetOfNumbers
*/
void SetsOfNumbers::addSetOfNumbers(SetOfNumbers &setOfNum) {
	setOfNum.getSetOfNumbers();
	arrayS[numSet].setSetOfNumbers(setOfNum);
	arrayS[numSet].setNumberElements(setOfNum.getNumberElements());
	//����������� ���������� ��������� � �������
	numSet++;
}

/*
* ������� ������� �� ����� ���� ������
*/
void SetsOfNumbers::outputMonitor() {
	cout << "\n";
	for (int i = 0; i < numSet; i++) {
		if (arrayS[i].getNumberElements() != 0) 
			arrayS[i].outputMonitor();
	}
	cout << endl;
}

/*
* ������� ��������� ������ �� ���������� ��������� � ����������
* ������� ������� ���������� �� �����������
* ���������: left - ����� ������� �������, rigth - ������
*/
void SetsOfNumbers::sortByNumberElements(int left, int right) {

	int i = left, j = right;
	//��������
	int x = arrayS[(left + right) / 2].getNumberElements();

	while (i <= j) {
		while (arrayS[i].getNumberElements() < x) i++;
		while (arrayS[j].getNumberElements() > x) j--;

		if (i <= j) {
			//������ ������ ���������, ������� ����� ������
			int size = arrayS[i].getNumberElements();
			int *tmp = new int[size];
			//������ ���������
			tmp = arrayS[i].getSetOfNumbers();
			arrayS[i].setSetOfNumbers(arrayS[j].getSetOfNumbers(), arrayS[j].getNumberElements());
			arrayS[j].setSetOfNumbers(tmp, size);
			//��������, ����������� ����� � �������� size
			delete[] tmp;
			size = 0;
			i++;
			j--;
		}
	}
	//��������
	if (i < right) sortByNumberElements(i, right);
	if (left < j) sortByNumberElements(left, j);
}

/*
* ������� ��������� ���������� ������ ��������
* ���������� ��������� ��������
*/
int SetsOfNumbers::numberEqualArrays() {
	// ����� ���������� = 1, ������ ���
	int numberEqual = 1;

	// ���� ��������� �������� ������������� � ����� ���������
	// � ��� ���������, �� ��� �����
	for (int i = 0; i < numSet - 1; i++) {
		for (int j = numSet; j > i; j--) {
			if (arrayS[i].chekSubset(arrayS[j]) &&
				arrayS[i].getNumberElements() == arrayS[j].getNumberElements()) {
				numberEqual++;
			}
		}
	}
	return numberEqual;
}

/*
* ������� ������� ����� ��������� �������
* ���������� ����������� ��������
*/
void SetsOfNumbers::unionSets() {
	int sum = 0;
	for (int i = 0; i < numSet - 1; i++) {
		arrayS[i + 1].unionMas(arrayS[i]);
		arrayS[i].setSetOfNumbers(NULL, NULL);
	}
	arrayS[0].setSetOfNumbers(arrayS[numSet - 1].getSetOfNumbers(), arrayS[numSet - 1].getNumberElements());
	arrayS[numSet - 1].setSetOfNumbers(NULL, NULL);
}