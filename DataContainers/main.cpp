#include <iostream>
using namespace std;
#define tab "\t"
#define delimiter "\n---------------------------------------------------------------------\n"

//class ForwardList;

class Element
{
	int Data;			//значение элемента
	Element* pNext;		//Pointer to Next - указатель на следующий элемент
	static int count;
public:
	static int get_count() { return count; }

	Element(int Data = 0, Element* pNext = nullptr) : Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};
int Element::count = 0;

class ForwardList
{
	Element* Head; //Голова списка, указывает на начальный элемент списка
	unsigned int size;
public:
	int get_size()const { return size; }
	void set_size(unsigned int size) { this->size = size; }

	ForwardList() //конструктор по умолчанию, который создает пустой список
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
	ForwardList(initializer_list<int> values)
	{
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const ForwardList& other)
	{
		*this = other;
		cout << "CopyConstructor:\t" << this << endl;
	}
	ForwardList(ForwardList&& other)
	{
		*this = std::move(other); //Функция std::move() принудительно вызывает MoveAssignment для класса.
		cout << "MoveConstructor:\t" << this << endl;
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
		other.Head = nullptr;
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
		//1) Создаем новый элемент
		Element* New = new Element(Data);

		//2) Пристыковываем новый элемент к началу списка
		New->pNext = Head;

		//3) Голову перенаправляем на новый элемент
		Head = New;
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);

		Element* New = new Element(Data);
		Element* last = Head;
		while (last->pNext)
			last = last->pNext;
		last->pNext = New;
		size++;
	}
	void insert(int Data, int index)
	{
		if (index > size)cout << "Error: Out of range\n"; return;
		if (index == 0)return push_front(Data);
		Element* New = new Element(Data);
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)
		{
			//if (Temp->pNext)break;
			Temp = Temp->pNext;
		}
		New->pNext = Temp->pNext;
		Temp->pNext = New;
		size++;
	}

	//				Removing elements:

	void pop_front()
	{
		if (Head == nullptr)return;
		//1) Запоминаем вдрес удаляемого элемента:
		Element* purgatory = Head;
		//2) Исключаем удаляемый элемент из списка:
		Head = Head->pNext;
		//3)  Удаляем эоемент из памяти:
		delete purgatory;
		size--;
		//delete[] purgatory;
		/*
		-----------
		new   - создает объект в динамической памяти
		new[] - создает массив объектов в динамической памяти

		delete   - удаляет 1 объект из динамической памяти
		delete[] - удаляет массив объектов из динамической памяти

		delete new ....;
		delete[] new ...[...];
		-----------
		delete new ...[...];	//behaviour is undefined (поведение неопределено)
		delete[] new ...;		//behaviour is undefined (поведение неопределено)
		-----------
		*/
	}
	void pop_back()
	{
		if (Head == nullptr)return;
		if (Head->pNext == nullptr)return pop_front();
		//1) Доходим до предпоследнего элемента списка:
		Element* last = Head;
		while (last->pNext->pNext != nullptr)last = last->pNext;
		//2) Удаляем послений элемент из памяти:
		delete last->pNext;
		//3) Обнуляем указатель на последний элемент:
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
		Element* Temp = Head; //Temp - это итератор
							  //Итератор - указатель, при помощи которого можно получить доступ к элементам структуры данных
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
	}

};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList Temp;
	for (int i = 0; i < left.get_size(); i++)
		Temp.push_back(left[i]);
	for (int i = 0; i < right.get_size(); i++)
		Temp.push_back(right[i]);
	return Temp;
}

//#define BASE_CHECK
//#define COUNT_CHECK
//#define SIZE_CONSTRUCTOR_CHECK
//#define COPY_METHODS_CHECK

int main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Введите количество элементов списка: "; cin >> n;
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
	//cout << "Введите индекс добавляемого элемента: "; cin >> index;
	//cout << "Введите значение добавляемого элемента: "; cin >> value;
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

	ForwardList list = { 1, 2, 3, 4 }; //initializer_list<int>
}