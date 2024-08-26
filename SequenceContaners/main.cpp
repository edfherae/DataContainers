#include <iostream>
#include<array>
#include<vector>
#include <list>
#include <forward_list>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n----------------------------------------------------\n"

//#define STL_ARRAY
//#define STL_VECTOR
//#define STL_LIST

template<typename T>void vector_properties(const std::vector<T>& vec);

void main()
{
	setlocale(LC_ALL, "");

#ifdef STL_ARRAY
	//array - это контейнер, который хранит данные в виде статического массива.
	const int SIZE = 5;
	std::array<int, SIZE> arr = { 3, 5, 8 };
	for (int i = 0; i < SIZE; i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;

	//arr.
#endif // STL_ARRAY

#ifdef STL_VECTOR
	//vector - это контейнер, который хранит данные в виде динамического массива.
	std::vector<int> vec = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };
	try
	{
		for (int i = 0; i < vec.size() * 2; i++)
		{
			cout << vec.at(i) << tab;
			//cout << vec[i] << tab;
		}
		cout << endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}

	vector_properties(vec);

	vec.push_back(144);
	vector_properties(vec);

	//vec.resize(15);	//задает фактический размер Вектора.
	//vec.shrink_to_fit();//урезает вместительность до фактического размера.
	vec.reserve(120);	//позволяет зарезервировать нужный объем памяти.
	//Этот метод выполняется только в том случае, если ему передать значение
	//больше текущего capacity();
	for (int i : vec)cout << i << tab; cout << endl;
	vector_properties(vec);
	cout << vec.front() << endl;
	cout << vec.back() << endl;
	cout << vec.data() << endl;
	for (int i = 0; i < vec.size(); i++)
	{
		cout << *(vec.data() + i) << tab;
		//cout << vec.data()[i] << tab;
	}
	cout << endl;
	cout << "Iterators:" << endl;
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl << delimiter;

	int value;
	int index;
	cout << "Введите значение типа int\n";
	while (true)
	{
		try
		{
			cin >> value; 
			break;
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << endl;
		}
	}
	cout << "Введите индекс вставки значения\n"; cin >> index;

	vec.insert(vec.begin() + index, value);
	for (std::vector<int>::const_iterator it = vec.begin(); it != vec.end(); ++it)
	{
		cout << *it << tab;
	}

	cout << "Введите индекс удаления значения\n"; cin >> index;
	vec.erase(vec.begin() + index);
	for (std::vector<int>::const_iterator it = vec.begin(); it != vec.end(); ++it)
	{
		cout << *it << tab;
	}

#endif // STL_VECTOR

#ifdef STL_LIST
	
	std::list<int> list = { 3,5,8 };
	for (std::list<int>::const_iterator it = list.begin(); it != list.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;

	int value;
	int index;
	cout << "Введите значение типа int: "; cin >> value;
	cout << "Введите индекс вставки значения: "; cin >> index;
	
	std::list<int>::const_iterator it = list.begin();
	for (int i = 0; i < index; i++)++it;
	list.insert(it, value);

	for (std::list<int>::const_iterator it = list.begin(); it != list.end(); ++it)cout << *it << tab;
	cout << endl;

	cout << "Введите индекс удаления значения: "; cin >> index;
	it = list.begin();
	for (int i = 0; i < index; i++)++it;
	list.erase(it);

	for (std::list<int>::const_iterator it = list.begin(); it != list.end(); ++it)cout << *it << tab;
	cout << endl;

#endif // STL_LIST



}
template<typename T>void vector_properties(const std::vector<T>& vec)
{
	cout << "Size:\t " << vec.size() << endl;
	cout << "Capacity:" << vec.capacity() << endl;
	cout << "MaxSize: " << vec.max_size() << endl;
	cout << delimiter << endl;
}