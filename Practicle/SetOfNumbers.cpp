/*
* ������������� ����������������� ���������
*/
#include "SetOfNumbers.h"
#include "SetsOfNumbers.h"
#include <iostream>


using namespace std;

void main() {
	system("chcp 1251");

	int sizeSet = 0;
	int size = 0;
	cout << "������� ����� ��������: ";
	cin >> size;
	cout << "\n\n";

	SetsOfNumbers sets(size);
	
	//������ ��������� � ��������� ������ ��������
	for (int i = 0; i < size; i++) {
		cout << "������ ��������� " << i + 1 << ": ";
		cin >> sizeSet;
		SetOfNumbers set(sizeSet);
		set.inputKeyboard();
		cout << "set" << i + 1 << ": ";
		set.outputMonitor();
		cout << "\n";
		sets.addSetOfNumbers(set);
	}

	cout << "\n���������";
	sets.outputMonitor();

	sets.sortByNumberElements(0, size - 1);
	cout << "����� ����������: ";
	sets.outputMonitor();

	if (sets.numberEqualArrays() == 1) 
		cout << "\n����� ���������� ��������: 0" << endl;
	else 	cout << "\n����� ���������� ��������: " << sets.numberEqualArrays() << endl;

	sets.unionSets();
	cout << "\n�����������: ";
	sets.outputMonitor();
	system("pause");
}