#include <iostream>
using namespace std;
#define tab "\t"
#define delimiter "\n---------------------------------------------------------------------\n"

//class ForwardList;

class Element
{
	int Data;			//�������� ��������
	Element* pNext;		//Pointer to Next - ��������� �� ��������� �������
	static int count;
public:
	static int get_count() { return count; }
	const int get_data()const { return Data; }

	Element(int Data = 0, Element* pNext = nullptr) : Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	Element(const Element& other)
	{
		this->Data = other.Data;
		this->pNext = nullptr;
		//this->pNext = other.pNext;
		count++;
		cout << "ECopyConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class Iterator;
	friend class ForwardList;

};
int Element::count = 0;

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr):Temp(Temp)
	{
		cout << "IConstructor:\t" << this << endl;
	}
	~Iterator()
	{
		cout << "IDestructor:\t" << this << endl;
	}
	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	Iterator& operator++(int)
	{
		Iterator old = *this;
		Temp = Temp->pNext;
		return old;
	}
	//operator=(const Iterator& other)
	/*{
		
	}*/
	bool operator==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}
	int operator*()const
	{
		return Temp->Data;
	}
	int& operator*()
	{
		return Temp->Data;
	}
};

class ForwardList
{
	Element* Head; //������ ������, ��������� �� ��������� ������� ������
	unsigned int size;
public:
	int get_size()const { return size; }
	void set_size(unsigned int size) { this->size = size; }

	ForwardList() //����������� �� ���������, ������� ������� ������ ������
	{
		Head = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	explicit ForwardList(unsigned int size) : ForwardList()
	{
		while(size--)push_back(0);
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const ForwardList& other)
	{
		*this = other;
		cout << "CopyConstructor:\t" << this << endl;
	}
	ForwardList(ForwardList&& other)
	{
		*this = std::move(other); //������� std::move() ������������� �������� MoveAssignment ��� ������.
		cout << "MoveConstructor:\t" << this << endl;
	}
	ForwardList(const initializer_list<int>& il) : ForwardList()
	{
		for (const int* it = il.begin(); it != il.end(); it++) 
		{
			//it - iterator
			push_back(*it);
		}
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		while (Head != nullptr)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	//				Operators:

	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		this->~ForwardList();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	ForwardList& operator=(ForwardList&& other)
	{
		if (this == &other)return *this;
		this->~ForwardList();
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr; //��������, ����� ���������� �� �������� ��� ������
		other.size = 0;
		other.~ForwardList();
		cout << "MoveAssignment:\t" << this << endl;
	}
	int& operator[](int index)const
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)
			Temp = Temp->pNext;
		return Temp->Data;
	}
	int& operator[](int index)
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)
			Temp = Temp->pNext;
		return Temp->Data;
	}

	//				Adding elements:

	void push_front(int Data)
	{
		Head = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);

		Element* Temp = Head;
		while (Temp->pNext)Temp = Temp->pNext;
		Temp->pNext = new Element(Data);
		size++;
	}
	void insert(int Data, int index)
	{
		if (index > size)cout << "Error: Out of range\n"; return;
		if (index == 0)return push_front(Data);
		
		Element * Temp = Head;
		for (int i = 0; i <= index - 1; i++)Temp = Temp->pNext; //if (Temp->pNext)break;
		Temp->pNext = new Element(Data, Temp->pNext);
		size++; 
	}

	//				Removing elements:

	void pop_front()
	{
		if (Head == nullptr)return;
		//1) ���������� ����� ���������� ��������:
		Element* purgatory = Head;
		//2) ��������� ��������� ������� �� ������:
		Head = Head->pNext;
		//3)  ������� ������� �� ������:
		delete purgatory;
		size--;
		//delete[] purgatory;
		/*
		-----------
		new   - ������� ������ � ������������ ������
		new[] - ������� ������ �������� � ������������ ������

		delete   - ������� 1 ������ �� ������������ ������
		delete[] - ������� ������ �������� �� ������������ ������

		delete new ....;
		delete[] new ...[...];
		-----------
		delete new ...[...];	//behaviour is undefined (��������� ������������)
		delete[] new ...;		//behaviour is undefined (��������� ������������)
		-----------
		*/
	}
	void pop_back()
	{
		if (Head == nullptr)return;
		if (Head->pNext == nullptr)return pop_front();
		//1) ������� �� �������������� �������� ������:
		Element* last = Head;
		while (last->pNext->pNext != nullptr)last = last->pNext;
		//2) ������� �������� ������� �� ������:
		delete last->pNext;
		//3) �������� ��������� �� ��������� �������:
		last->pNext = nullptr;
		size--;
	}
	void erase(int index)
	{
		if (index > size)cout << "Error: Out of range\n"; return;
		if (index == 0)return pop_front();
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)
		{
			Temp = Temp->pNext;
		}
		Element* purgatory = Temp->pNext;
		Temp->pNext = purgatory->pNext;
		delete purgatory;
		size--;
	}
	
	//				methods:

	void fillrand()
	{
		//for (int i = 0; i < size; i++)
		//	*this[i] = rand() % 100;
		Element* Temp = Head;
		for (int i = 0; Temp; i++)
		{
			Temp->Data = rand() % 100;
			Temp = Temp->pNext;
		}
	}
	void print()const
	{
		//Element* Temp = Head; //Temp - ��� ��������
							  //�������� - ���������, ��� ������ �������� ����� �������� ������ � ��������� ��������� ������
		//while (Temp)
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	}
	Iterator begin()const
	{
		return Head;
	}
	Iterator end()const
	{
		return nullptr;
	}
};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList buffer = left;
	for (int i = 0; i < right.get_size(); i++)buffer.push_back(right[i]);
	return buffer;
}
ostream& operator<<(ostream& os, const Element& other)
{
	return os << other.get_data() << tab;
}

//#define BASE_CHECK
//#define COUNT_CHECK
//#define SIZE_CONSTRUCTOR_CHECK
//#define COPY_METHODS_CHECK
//#define INITIALIZER_LIST_CONSTRUCTOR
//#define RANGE_BASED_FOR_ARRAY
//#define RANGE_BASED_FOR_LIST

int main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "������� ���������� ��������� ������: "; cin >> n;
	ForwardList list(n);
	list.fillrand();
	list.print();
	cout << "push_back" << endl;
	list.push_back(rand() % 10);
	list.print();
	cout << "pop_front" << endl;
	list.pop_front();
	list.print();
	cout << "pop_back" << endl;
	list.pop_back();
	list.print();
	cout << "insert" << endl;
	int index = 2;
	int value = 1000;
	//cout << "������� ������ ������������ ��������: "; cin >> index;
	//cout << "������� �������� ������������ ��������: "; cin >> value;
	list.insert(value, index);
	list.print();
	cout << delimiter << endl;
	cout << "erase" << endl;
	list.erase(index);
	list.print();
#endif // BASE_CHECK

#ifdef COUNT_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1.print();

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();
	cout << list1.get_size() << "\t" << list2.get_size() << endl;
	cout << Element::get_count() << endl;
#endif // COUNT_CHECK

#ifdef SIZE_CONSTRUCTOR_CHECK
	ForwardList list(5);
	for (int i = 0; i < list.get_size(); i++)
	{
		list[i] = rand() % 100;
	}
	for (int i = 0; i < list.get_size(); i++)
	{
		cout << list[i] << tab;
	}
	cout << endl;
#endif // SIZE_CONSTRUCTOR_CHECK

	//ForwardList* list1 = new ForwardList[5]{ 3,5,8,13,21 };
	//ForwardList list1[5] = {3,5,8,13,21};

#ifdef COPY_METHODS_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1.print();

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();

	cout << delimiter << endl;
	ForwardList list3 = list1 + list2;	//CopyConstructor
	cout << delimiter << endl;
	ForwardList list4;
	cout << delimiter << endl;
	list4 = list1 + list2;	//CopyAssignment
	cout << delimiter << endl;
	list4.print();
#endif // COPY_CHECK

#ifdef INITIALIZER_LIST_CONSTRUCTOR
	ForwardList list = { 1, 2, 3, 4 }; //initializer_list<int>
	list.print();

	//��� �� �������� const int*  
#endif // INITIALIZER_LIST_CONSTRUCTOR

#ifdef RANGE_BASED_FOR_ARRAY
	int arr[] = { 3,5,8,13,21 }; //������ �����������, ������ �� �����������
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;

	//Range-based for
	for (int i : arr) //��������� ������ ����� ��� ��: sizeof(arr) / sizeof(type)
	{
		cout << i << tab;
	}
	//Range - ��������. ��� ������ �������� � ���� ��������� �������� ���������
	//�� ����, ���������� ������ �������� 'range'
	//�������������, range-based for - ��� ���� for ��� �����������
	cout << endl;
#endif // RANGE_BASED_FOR_ARRAY

#ifdef RANGE_BASED_FOR_LIST
	//initializer_list<int> il = { 1,2,3 };
	//il.begin();
	ForwardList list = { 3,5,8,13,21 };
	list.print();
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;

	for (Iterator it = list.begin(); it != list.end(); ++it)
	{
		cout << *it << tab;
	}
#endif // RANGE_BASED_FOR_LIST

}