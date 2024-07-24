#include <iostream>
using namespace std;
#define tab "\t"
#define delimiter "\t---------------------------------------------------------------------\t"

class Element
{
	int Data;			//значение элемента
	Element* pNext;		//Pointer to Next - указатель на следующий элемент
public:
	Element(int Data, Element* pNext = nullptr) : Data(Data), pNext(pNext) 
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};
class ForwardList
{
	Element* Head; //Голова списка, указывает на начальный элемент списка
	//static int count;
public:
	ForwardList(Element* Head = nullptr) //конструктор по умолчанию, который создает пустой список
	{
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}

	//				Adding elements:

	void push_front(int Data)
	{
		//1) Создаем новый элемент
		Element* New = new Element(Data);

		//2) Пристыковываем новый элемент к началу списка
		New->pNext = Head;

		//3) Голову перенаправляем на новый элемент
		Head = New;
	}
	void push_back(int Data)
	{
		Element* New = new Element(Data);
		Element* last = Head;
		while (last->pNext != nullptr)
		{
			last = last->pNext;
		}
		last->pNext = New;
	}
	void pop_front()
	{
		Element* purgatory = Head;
		Head = Head->pNext;
		//delete[] purgatory;
		delete purgatory;
	}
	void pop_back()
	{
		Element* last = Head;
		while (last->pNext != nullptr)
		{
			last = last->pNext;
		}
		//delete last;
		last = nullptr;
	}
	void insert(int Data, int index)
	{
		Element* New = new Element(Data);
		Element* Temp = Head;
		for (int i = 0; i < --index; i++)
		{
			Temp = Temp->pNext;
		}
		New->pNext = Temp->pNext;
		Temp->pNext = New;
	}
	void erase(int index)
	{
		Element* temp = Head;
		for (int i = 0; i < --index; i++)
		{
			temp = temp->pNext;
		}
		Element* purgatory = temp->pNext;
		temp->pNext = purgatory->pNext;
		delete purgatory;
	}
	
	//				methods:

	void print()const
	{
		Element* Temp = Head; //Temp - это итератор
							  //Итератор - указатель, при помощи которого можно получить доступ к элементам структуры данных
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
	}
};

int main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите количество элементов списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
	cout << delimiter << endl;
	cout << "push_back" << endl;
	list.push_back(rand() % 10);
	list.print();
	//удаляет ли деструктор выделенную память
	cout << delimiter << endl;
	cout << "pop_front" << endl;
	list.pop_front();
	list.print();
	cout << delimiter << endl;
	cout << "pop_back" << endl;
	list.pop_back();
	list.print();
	cout << delimiter << endl;
	cout << "insert" << endl;
	list.insert(88, 2);
	list.print();
	cout << delimiter << endl;
	cout << "erase" << endl;
	list.erase(2);
	list.print();
}