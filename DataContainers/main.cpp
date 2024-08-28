#include <iostream>
using namespace std;
#define tab "\t"
#define delimiter "\n---------------------------------------------------------------------\n"

template<typename T>class ForwardList;
template<typename T>class Iterator;
template<typename T>class Stack;

template<typename T>class Element
{
	T Data;			//значение элемента
	Element* pNext;		//Pointer to Next - указатель на следующий элемент
	static int count;
public:
	static int get_count() { return count; }
	const int get_data()const { return Data; }

	Element(T Data = 0, Element* pNext = nullptr) : Data(Data), pNext(pNext)
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
	//можно просто дописать перед friend <typename T>
	friend class Iterator<T>;
	friend class ForwardList<T>;
	friend class Stack<T>;
};
template<typename T>int Element<T>::count = 0;

template<typename T>
class Iterator
{
	Element<T>* Temp;
public:
	Iterator(Element<T>* Temp = nullptr):Temp(Temp)
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

template<typename T>class ForwardList
{
protected:
	Element<T>* Head; //Голова списка, указывает на начальный элемент списка
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
	ForwardList(const initializer_list<T>& il) : ForwardList()
	{
		for (const T* it = il.begin(); it != il.end(); it++) 
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
		other.Head = nullptr; //зануляем, чтобы деструктор не почистил наш список
		other.size = 0;
		other.~ForwardList();
		cout << "MoveAssignment:\t" << this << endl;
	}
	T& operator[](int index)const
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)
			Temp = Temp->pNext;
		return Temp->Data;
	}
	T& operator[](int index)
	{
		Element<T>* Temp = Head;
		for (int i = 0; i < index; i++)
			Temp = Temp->pNext;
		return Temp->Data;
	}

	//				Adding elements:

	void push_front(T Data)
	{
		Head = new Element<T>(Data, Head);
		size++;
	}
	void push_back(T Data)
	{
		if (Head == nullptr)return push_front(Data);

		Element<T>* Temp = Head;
		while (Temp->pNext)Temp = Temp->pNext;
		Temp->pNext = new Element<T>(Data);
		size++;
	}
	void insert(T Data, int index)
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
		//1) Запоминаем вдрес удаляемого элемента:
		Element<T>* purgatory = Head;
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
		//Element* Temp = Head; //Temp - это итератор
							  //Итератор - указатель, при помощи которого можно получить доступ к элементам структуры данных
		//while (Temp)
		for (Element<T>* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	}
	Iterator<T> begin()const { return Head; }
	Iterator<T> end()const { return nullptr; }
};

template<typename T>ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right)
{
	ForwardList<T> buffer = left;
	for (int i = 0; i < right.get_size(); i++)buffer.push_back(right[i]);
	return buffer;
}
template<typename T>ostream& operator<<(ostream& os, const Element<T>& other)
{
	return os << other.get_data() << tab;
}

template<typename T>class Stack : ForwardList<T>
{
public:
	void push(T data)
	{
		ForwardList<T>::push_front(data);
	}
	T pop()
	{
		T data = ForwardList<T>::Head->Data;
		ForwardList<T>::pop_front();
		return data;
	}
	unsigned int depth()
	{
		return ForwardList<T>::size;
	}
};

//#define BASE_CHECK
//#define COUNT_CHECK
//#define SIZE_CONSTRUCTOR_CHECK
//#define COPY_METHODS_CHECK
//#define INITIALIZER_LIST_CONSTRUCTOR
//#define RANGE_BASED_FOR_ARRAY
//#define RANGE_BASED_FOR_LIST
//#define TEMPLATE_TYPES

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

#ifdef INITIALIZER_LIST_CONSTRUCTOR
	ForwardList list = { 1, 2, 3, 4 }; //initializer_list<int>
	list.print();

	//как мы изменяем const int*  
#endif // INITIALIZER_LIST_CONSTRUCTOR

#ifdef RANGE_BASED_FOR_ARRAY
	int arr[] = { 3,5,8,13,21 }; //массив статический, размер не указывается
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;

	//Range-based for
	for (int i : arr) //вычисляет размер точно так же: sizeof(arr) / sizeof(type)
	{
		cout << i << tab;
	}
	//Range - диапазон. Под данным термином в этом контексте понимают контейнер
	//То есть, контейнеры иногда называют 'range'
	//Следовательно, range-based for - это цикл for для контейнеров
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

#ifdef TEMPLATE_TYPES
	ForwardList<int> i_list = { 1,2,3,4,5 };
	i_list.print();
	ForwardList<double> d_list = { 1.1,2.2,3.3,4.4,5.5 };
	d_list.print();
	ForwardList<string> s_list = { "to","the","moon" };
	s_list.print();
	//ForwardList<Element<int>> e_list = { Element<int>(1), Element<int>(2), Element<int>(2)};
	//e_list.print();  
#endif // TEMPLATE_TYPES

	Stack<int> stack;
	stack.push(1);
	stack.push(2);
	stack.push(5);
	stack.push(8);
	stack.push(13);

	while (stack.depth())
	{
		cout << stack.pop() << tab;
	}
}