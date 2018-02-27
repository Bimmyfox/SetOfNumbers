/*
* ����� ��� ������������� ��������� �� n ����� ���������
* �������� �������:
* ���������� ��������� � ���������� � ���������� �������
* ����� ��������� �� �����
* ����������� ��������
* �������� �������������� ����� ���������
* ��������: �������� �� ��������� ���(���)���������� �������
*/
#pragma once
#include <iostream>
#include <ctime>
#include <malloc.h>

using namespace std;

class SetOfNumbers {

private:
	//����� ��������� � ���������
	int numberElements;
	//���������
	int *setOfNumbers;

public:
	//====�������====
	void inputRandom(); //���������� "����������" �������
	void inputKeyboard(); //���� � ����������
	void outputMonitor(); //����� ��������� �� �����
	void unionMas(SetOfNumbers&); //����������� ��������
	bool chekBelonging(int); //�������� �������������� ����� ���������
	bool chekSubset(SetOfNumbers&); //��������: �������� �� ��������� ���(���)���������� �������


	//=====������� � �������====
	//��� ��������� ���������
	int getNumberElements();
	void setNumberElements(int);

	//��� ��������� ���������
	int* getSetOfNumbers();
	void setSetOfNumbers(SetOfNumbers&);
	void setSetOfNumbers(int*, int);


	//====������������ � ����������====
	SetOfNumbers(); //�� ���������
	SetOfNumbers(int); //� �������� ������ ��������� 
	~SetOfNumbers();
};




//=======================������������ � ����������===============
/*
* ����������� �� ���������
* ����� ����� ���������� = 0
* ������ ������ ���������
*/
SetOfNumbers::SetOfNumbers() {
	numberElements = 0;
	setOfNumbers = (int*)malloc(0);
}

/*
* ����������� � �������� ������ ���������:
* ����� ����� ���������� = number
* ������ ��������� c ����������� ��������� number
*/
SetOfNumbers::SetOfNumbers(int number) {
	numberElements = number;
	setOfNumbers = (int*)malloc(numberElements * sizeof(int));
}


SetOfNumbers::~SetOfNumbers() {
	free(setOfNumbers);
}




//==========================������� � �������====================
int SetOfNumbers::getNumberElements() {
	return numberElements;
}

void SetOfNumbers::setNumberElements(int number) {
	numberElements = number;
}

int* SetOfNumbers::getSetOfNumbers() {
	return setOfNumbers;
}

/*
* �������� - ��������� ������ SetOfNumbers
*/
void SetOfNumbers::setSetOfNumbers(SetOfNumbers& setOfNum) {
	numberElements = setOfNum.numberElements;
	setOfNumbers = (int*)malloc(numberElements * sizeof(int));
	//��������� ��������� ����������
	for (int i = 0; i < numberElements; i++)
		setOfNumbers[i] = setOfNum.setOfNumbers[i];
}

/*
* ���������:
* *setOfNum - ������������ ������ � �������
* numElements - ���������� ��������� � �������
*/
void SetOfNumbers::setSetOfNumbers(int *setOfNum, int numElements) {
	numberElements = numElements;
	setOfNumbers = (int*)malloc(numberElements * sizeof(int));
	for (int i = 0; i < numberElements; i++) {
		setOfNumbers[i] = setOfNum[i];
	}
}




//==================�������======================
/*
* ������� ��������� ��������� ���������� �������
*/
void SetOfNumbers::inputRandom() {
	srand(time_t(NULL));
	for (int i = 0; i < numberElements; i++) {
		setOfNumbers[i] = rand() % 100;
	}
}

/*
* ������� ��������� ��������� �������, ��������� � ����������
*/
void SetOfNumbers::inputKeyboard() {
	cout << "������� �������� ���������: ";

	for (int i = 0; i < numberElements; i++) {
		cin >> setOfNumbers[i];
	}
	cout << endl;
}

/*
* ������� ������� �� ����� ��� �������� ���������
*/
void SetOfNumbers::outputMonitor() {
	for (int i = 0; i < numberElements; i++) {
		cout << setOfNumbers[i] << " ";
	}
	cout << "\n";
}

/*
* ������� ���������� ��������� � ���������� � �������� ����������
* ��� ����������� ������������� �������� �� ������������
*/
void SetOfNumbers::unionMas(SetOfNumbers &setOfNum) {
	int *setOfNumbers2;
	int a;
	int b;
	int c = 0;

	//�������� �������� � setOfNumbers2
	int numberElements2 = setOfNum.numberElements;
	setOfNumbers2 = (int*)malloc(numberElements2 * sizeof(int));
	for (int i = 0; i < numberElements2; i++) {
		setOfNumbers2[i] = setOfNum.setOfNumbers[i];
	}

	//����� ��������� � ����� ��������� � ��� ��������
	int size = numberElements + numberElements2;
	int *arrayTmp;
	arrayTmp = (int*)malloc(size * sizeof(int));

	if (numberElements2 > numberElements) {
		a = numberElements2;
		b = numberElements;
	}
	else {
		c = 1;
		a = numberElements;
		b = numberElements2;
	}
	//���������� ����������
	int numberCoincidence = 0;
	//������: ���� �������� �����, �� ������(������), ����� ����(������)
	bool flag = false;

	//�������� �� ������� ��������� � ����� ������ c ��������� �������������
	for (int i = 0; i < a; i++) {
		for (int j = b; j > i; j--) {
			if (setOfNumbers[j] == setOfNumbers[i]) {
				numberCoincidence++;
				flag = true;
			}
		}
		if (!flag) arrayTmp[i - numberCoincidence] = setOfNumbers[i];
		flag = false;
	}

	//�������� �� ������� ��������� �� ��������� ������ � ��������� �������������
	for (int i = 0; i < numberElements2; i++) {
		if (chekBelonging(setOfNumbers2[i]))
			numberCoincidence++;
		else {
			if (c == 0) arrayTmp[i + b - numberCoincidence] = setOfNumbers2[i];
			else arrayTmp[i + a - numberCoincidence] = setOfNumbers2[i];
		}
	}

	//����� ������ �������
	numberElements = size - numberCoincidence;

	//����������������� ������
	setOfNumbers = (int*)realloc(setOfNumbers, numberElements * sizeof(int));


	//���������� ������ ��������� �������
	for (int i = 0; i < numberElements; i++) {
		setOfNumbers[i] = arrayTmp[i];
	}

	free(arrayTmp);
	free(setOfNumbers2);
}


/*
* ������� ���������� �������������� ����� ���������
* ���������: num - �����
* ���� ����� ����������� ���������, �� ������� ����� ������
* � ��������� ������ ���������� ����
*/
bool SetOfNumbers::chekBelonging(int num) {
	//���� ����� ���������� - ���� ����������
	bool flag = false;
	for (int i = 0; i < numberElements; i++) {
		if (setOfNumbers[i] == num) {
			flag = true;
		}
	}
	if (flag) return true;
	else return false;
}

/*
* ������� ���������: �������� �� ��������� ���(���)���������� �������
* ���������: ���������
* ���� �� - ���������� ������
* ����� - ����
*/
bool SetOfNumbers::chekSubset(SetOfNumbers &setOfNum) {
	//����� ����������
	int numberCoincidence = 0;
	//����� ��������� � ���������
	int numberElements2 = setOfNum.numberElements;

	//�������� ���������� ��������� � ������ setOfNumbers2,
	//����� ��������� � numberElements2
	int *setOfNumbers2 = (int*)malloc(numberElements2 * sizeof(int));
	for (int i = 0; i < numberElements2; i++)
		setOfNumbers2[i] = setOfNum.setOfNumbers[i];


	//������� ����� ��������� ��������� � ����������
	for (int i = 0; i < numberElements2; i++) {
		for (int j = 0; j < numberElements; j++) {
			if (setOfNumbers[j] == setOfNumbers2[i]) {
				numberCoincidence++;
			}
		}
	}
	//���� ���� ���������� = ����� ��������� ������ �� ��������, �� ��� �������� ��� ���(���)����������
	if ((numberCoincidence == numberElements) || (numberCoincidence == numberElements2))
		return true;
	else return false;
}