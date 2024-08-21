#include <iostream>
using namespace std;
#define tab "\t"
#define delimiter "\n----------------------------------------\n"

//class List
//{
//	class Element;
//	Element& operator[](int index);
//};

class List
{
	class Element
	{
		int Data;
		Element* pPrev;
		Element* pNext;
		int get_data()const { return Data; }
		void set_data(int Data) { this->Data = Data; }
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			: Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		void operator=(int Data)
		{
			set_data(Data);
		}
		friend class List;
	} *Head, *Tail; //объекты класса можно объявлять непосредственно после его описания
	//Element* Head;
	//Element* Tail;
	size_t size; //size_t _ это typedef на unsigned int
	//Директива typedef создает псевдоним для существующего типа данных
	//typedef имеет следующий синтаксис:
	//				typedef существующий_тип_данных псевдоним
public:
	int get_size()const { return size; }

	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	~List()
	{
		//while (Head)pop_front();
		while (Head)pop_back();
		print();
		cout << "LDestructor:\t" << this << endl;
	}

	//				Adding Elements:

	void push_front(int Data) //push_front не умеет работать с пустым списком
	{
		/*Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;
		New->pNext->pPrev = New;*/
		if (Head == nullptr && Tail == nullptr)Head = Tail = new Element(Data);
		else
		{
			Head->pPrev = new Element(Data, Head);
			Head = Head->pPrev;
		}
		size++;	
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)Head = Tail = new Element(Data);
		else
		{
			Tail->pNext = new Element(Data, nullptr, Tail);
			Tail = Tail->pNext;
		}
		size++;
	}
	/*Element& operator[](int index)
	{
		if (index == 0)return *Head;
		if (index == size - 1)return *Tail;

		Element* Temp = nullptr;
		if (index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < index; i++)
			{
				Temp = Temp->pNext;
			}
		}
		else 
		{
			Temp = Tail;
			for (int i = 0; i < index; i++)
			{
				Temp = Temp->pPrev;
			}
		}
		return *Temp;
	}*/
	int& operator[](int index)
	{
		if (index == 0)return Head->Data;
		if (index == size - 1)return Tail->Data;

		/*Element* Temp = nullptr;
		Temp = Head;
		for (int i = 0; i < index; i++)
		{
			Temp = Temp->pNext;
		}*/

		Element* Temp = nullptr;
		if (index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < index; i++)
			{
				Temp = Temp->pNext;
			}
		}
		else
		{
			Temp = Tail;
			for (int i = size - 1; i > index; i--)
			{
				Temp = Temp->pPrev;
			}
		}
		return Temp->Data;
	}
	void insert(int Data, int index)
	{
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;
		Temp->pNext->pPrev = new Element(Data, Temp->pNext, Temp);
		size++;
		//this[index] = new Element(Data);
	}

	//ForwardList& operator=(const ForwardList& other)
	//{
	//	if (this == &other)return *this;
	//	this->~ForwardList();
	//	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
	//		push_back(Temp->Data);
	//	cout << "CopyAssignment:\t" << this << endl;
	//	return *this;
	//}
	//ForwardList& operator=(ForwardList&& other)
	//{
	//	if (this == &other)return *this;
	//	this->~ForwardList();
	//	this->Head = other.Head;
	//	this->size = other.size;
	//	other.Head = nullptr; //зануляем, чтобы деструктор не почистил наш список
	//	other.size = 0;
	//	other.~ForwardList();
	//	cout << "MoveAssignment:\t" << this << endl;
	//}
	//int& operator[](int index)const
	//{
	//	Element* Temp = Head;
	//	for (int i = 0; i < index; i++)
	//		Temp = Temp->pNext;
	//	return Temp->Data;
	//}
	//int& operator[](int index)
	//{
	//	Element* Temp = Head;
	//	for (int i = 0; i < index; i++)
	//		Temp = Temp->pNext;
	//	return Temp->Data;
	//}

	//				Removing Elements:

	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
		}
		else
		{
			Head = Head->pNext;
			delete Head->pNext;
			Head->pPrev = nullptr;
		}
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Tail;
			Head = Tail = nullptr;
		}
		else
		{
			Tail = Tail->pPrev;
			delete Tail->pNext;
			Tail->pNext = nullptr;
		}
		size--;
	}
	void erase(int index)
	{
		Element* purgatory;
	}

	//				Operators:

	//void operator=(int Data) {this->}

	//				Methods:

	void print()const
	{
		for (Element* Temp = Head; Temp; Temp=Temp->pNext)
			cout << Temp->pPrev << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов в списке: " << size << endl;
	}
	void reverse_print()const
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов в списке: " << size << endl;
	}
};

int main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (size_t i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();

	cout << delimiter << endl;

	list.insert(100, 2);
	for (int i = 0; i < list.get_size(); i++)
	{
		cout << list[i] << tab;
	}
	cout << endl;
	list.reverse_print();

	cout << delimiter << endl;

	//list.erase(2);
	//list.print();

	//for (size_t i = 0; i < n; i++)
	//{
	//	//list.pop_front();
	//	list.pop_back();
	//}
}