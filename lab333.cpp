//#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include "windows.h"

using namespace std;

struct Patty
{
	string taste;
	float length, weight, kkal;
	void Out();
};

struct Product {
	int volume;
	double price;
	void Out();
};

struct MyStack
{
	struct Node
	{
		Patty data;
		Node* prev;
	};
	Node* Top = NULL;
	int Count;
	bool Push(Patty);
	bool Pop(Patty&);
	void Info();
};

struct MyQueue {
	struct Node {
		Product data;
		Node* next;
	};
	int remain;
	double profit = 0;
	Node* First = NULL;
	int Count = 0;
	bool Push(Product);
	bool Pop(Product&);
	void Info();
	int Sell(int, double, bool);
};

bool MyStack::Pop(Patty& data)
{
	if (!Top) return false;
	Node* temp = Top->prev;
	data = Top->data; delete Top;
	Top = temp; Count--;
	return true;
}

bool MyQueue::Pop(Product& data) {
	if (!First) return false;
	Node* temp = First->next;
	data = First->data;
	remain -= First->data.volume;
	delete First;
	First = temp;
	Count--;
	return true;
}

bool MyStack::Push(Patty data)
{
	if (!Top)
	{
		Top = new Node;
		Top->prev = NULL;
		Count = 1;
	}
	else
	{
		Node* temp;
		temp = new Node;
		temp->prev = Top;
		Top = temp;
		Count++;
	}
	Top->data = data;//!!!Узкое место
	return true;
}

bool MyQueue::Push(Product data) {
	if (!First) {
		First = new Node;
		First->next = NULL;
		First->data = data;
		Count = 1;
		remain = First->data.volume;
	}
	else {
		Node* temp;
		temp = First;
		while (temp->next != NULL) temp = temp->next;
		temp->next = new Node;
		temp->next->data = data;
		remain += temp->next->data.volume;
		temp->next->next = NULL;
		Count++;
	}
	return true;
}

void MyStack::Info()
{
	if (!Top)
		cout << "---> Cтек пуст.\n" << endl;
	else
	{
		cout << endl << "Информация о стеке:" << endl;
		cout << "\tРазмер стека = " << Count << "\n\n";
		Top->data.Out();
		cout << endl;
		
	}
}

void MyQueue::Info() {
	if (!First) {
		cout << "--->Очередь пуста" << endl;
		cout << "\nОстаток = " << remain << "\nДоход = " << profit;
	}
	else {
		cout << endl << "Информация: " << endl;
		cout << "\tРазмер очереди = " << Count << endl;
		First->data.Out();

		cout << "\nОстаток = " << remain << "\nДоход = " << profit;
	}
}

void Patty::Out()
{
	cout << "Вкус: " << taste <<"| Длина: "<< length <<" | Вес: " << weight << "| Ккал: "<< kkal << endl;
};

void Product::Out() {
	cout << "\nКоличество = " << volume << ' ' << "Цена = " << price << endl;
}

int MyQueue::Sell(int volume, double price, bool fsell) {
	Product temp;

	if (volume == 0) return true;


	if (price < First->data.price && fsell == true) {
		cout << "\nСлишком низкая цена\n";
		return false;
	}
	else {
		if (volume > remain) {
			cout << "\nНедостаточно товаров\n";
			return -1;
		}
		if (First->data.volume > volume) {
			First->data.volume -= volume;
			profit += (price - First->data.price) * volume;
			remain -= volume;
			return 0;
		}
		else {
			profit += (price - First->data.price) * First->data.volume;
			volume -= First->data.volume;
			Pop(temp);
			return volume;
		}
	}
}

void Push(MyStack&);
bool GetFile(MyStack&);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Rus");

	int №;

	do
	{
		cout << "\nВыберите задание(1-2): ";
		cin >> №; cout << endl;

		if (№ == 1)
		{
			cout << "\nРабота со стеком.\n\n";
			Patty k, f;
			int task, i = 0, n, n1;

			MyStack S, I;

			cout << "Действие над стеком:\n1 - Добавить товар в корзину.\n2 - Достать товар из корзины.\n3 - Очистить корзину.\n4 - Взять элементы из файла.\n5 - Показать содержимое корзины.\n\n";
			do {
				cout << "Выберите действие: ";
				cin >> task;
				cout << "\n";

				if (task == 1)
				{
					Push(S);
				}

				else if (task == 2)
				{

						cout << "Вкус: ";
						cin >> f.taste;
						cout << "Длина: ";
						cin >> f.length;
						cout << "Вес: ";
						cin >> f.weight;
						cout << "Ккал: ";
						cin >> f.kkal;
						cout << endl;
						while (S.Pop(k))
						{
							I.Push(k);
							if (k.taste == f.taste && k.weight == f.weight && f.kkal==k.kkal && f.length ==k.length)
							{
								I.Pop(k);
								
							}
							else { cout << "Вы ввели неверную характеристику."<<endl; }
						}
						while (I.Pop(k))
						{
							S.Push(k);
						}
						
					

				}

				else if (task == 3)
				{

					while (S.Pop(k));
					S.Info();
				}

				else if (task == 4 && i == 0)
				{
					i = 1;
					GetFile(S);
					S.Info();
				}

				else if (task == 4 && i == 1)
				{
					cout << "Данные из файла уже были взяты.\n\n";
				}

				else if (task == 5)
				{
					cout << "___________________________\n\n";
					while (S.Pop(k))
					{
						I.Push(k);
						k.Out();
					}
					while (I.Pop(k))
					{
						S.Push(k);
					}
					//cout << " " << k;
					cout << endl;
					cout << "___________________________\n";
					cout << endl;
				}
				else cout << "Такого действия нет. Повторите попытку.\n\n";
			} while (task != 0);
			while (S.Pop(k));
		}

		else if (№ == 2)
		{

			int n = 10, i = 1, number, n1;
			float cost;
			Product k;
			MyQueue Q;
			do {
				do {
					cout << "Задайте количество товара для закупки на склад.\nКоличество: ";
					cin >> number; cout << "\n\n";
					if (number < 0) cout << "Вы ввели неверное кол-во товара. Повторите попытку.\n\n";
					else i = 0;
				} while (i != 0);
				
					do {
						cout << "По какой стоимости закупать.\nЦена: ";
						cin >> cost; cout << "\n\n";
						if (cost < 0) cout << "Вы ввели неверную стоимость товара. Повторите попытку.\n\n";
						else i = 0;
					} while (i = 0);
				
				Product k1 = { number, cost };
				Q.Push(k1);
				cout << "Добавить ещё товар?\n0 - нет\n1 - да.\n\n";
				cin >> n1; cout << "\n\n";
			} while (n1 != 0);


			Q.Info();
			int sellc, sellp, selld;
			do {
				cout << "\n__________________\n";
				cout << "\nВведите количество товара на продажу (0 для выхода): ";
				cin >> sellc;
				if (sellc > 0) {
					cout << "\nВведите стоимость продажи: ";
					cin >> sellp;
					if (sellp < 0) sellp = 0;
					selld = Q.Sell(sellc, sellp, true);
					while (selld > 0) {
						selld = Q.Sell(selld, sellp, false);
					}
					Q.Info();
				}
			} while (sellc > 0);
			cout << "\n__________________\n";
			while (Q.Pop(k)) k.Out();
			cout << endl;
			Q.Info();


		}
		else if (№ == 0)
			cout << "\nДо свидания.\n" << endl;

		else cout << "\nВы выбрали несуществующий номер, повторите попытку.\n" << endl;

	} while (№ != 0);

	return 0;
}

bool GetFile(MyStack& Stack) {
	ifstream F("pie.txt");
	if (!F) {
		cout << "Файл не найден." << endl;
		return false;
	}
	else
	{
		Patty k;

		while (F >> k.taste >> k.weight >> k.length >> k.kkal) {//Пока можем извлечь
			Stack.Push(k);
		}

		F.close();
		return true;
	}
}

void Push(MyStack& Stack)
{
	Patty k;
	cout << "Вкус: ";
	cin >> k.taste;
	cout << "Длина: ";
	cin >> k.length;
	cout << "Вес: ";
	cin >> k.weight;
	cout << "Ккал: ";
	cin >> k.kkal;
	Stack.Push(k);
	cout << endl;
}