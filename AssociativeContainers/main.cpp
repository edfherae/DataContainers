#include <iostream>
#include<string>
#include<map>
#include<vector>
#include<list>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n----------------------------------------\n"

//#define STL_MAP
//#define STL_MAP_2

void main()
{
	setlocale(LC_ALL, "");

#ifdef STL_MAP
	/*map - это контейнер, каждый элемент которого хранит пару<ключ, значение>
			pair<key, value>
	*/

#ifdef STL_MAP
	std::map<int, std::string> week =
	{
		{4, "Thursday"},
		std::pair<int, std::string>(0, "Sunday"),
		std::pair<int, std::string>(0, "Sunday"),
		std::pair<int, std::string>(0, "Sunday"),
		std::pair<int, std::string>(0, "Sunday"),
		std::pair<int, std::string>(1, "Monday"),
		std::pair<int, std::string>(2, "Tuesday"),
		std::pair<int, std::string>(3, "Wednesday"),
		std::pair<int, std::string>(3, "Среда"),
		std::pair<int, std::string>(3, "Wednesday"),
		std::pair<int, std::string>(3, "Wednesday"),
		std::pair<int, std::string>(3, "Wednesday"),
		std::pair<int, std::string>(3, "Wednesday"),
		{5, "Friday"},
		{5, "Friday"},
		{5, "Пятница"},
		{5, "Friday"},
		{5, "Friday"},
		{5, "Friday"},
		{5, "Friday"},
		{6, "Saturday"},
		{6, "Saturday"},
		{6, "Saturday"},
		{6, "Saturday"},
		{6, "Saturday"},
		{6, "Saturday"},
		{7, "Sunday"},
	};

	for (std::map<int, std::string>::iterator it = week.begin(); it != week.end(); ++it)
	{
		cout << it->first << tab << it->second << endl;
	}
	cout << endl;
#endif // STL_MAP


#endif // STL_MAP
#ifdef STL_MAP_2
	std::map<std::string, std::vector<std::string>> dictionary =
	{
		std::pair<std::string, std::vector<std::string>>("map", {"карта", "план", "таблица"}),
		std::pair<std::string, std::vector<std::string>>("window", {"окно", "витрина"}),
		{"statement", {"утверждение", "заявление", "высказывание"}},
		{"journey", {"путешествие", "поездка", "рейс", "прогулка"}}
	};
	for (std::map<std::string, std::vector<std::string>>::iterator it = dictionary.begin(); it != dictionary.end(); ++it)
	{
		cout.width(16);
		cout << std::left;
		cout << (*it).first + ":";
		for (std::vector<std::string>::iterator jt = it->second.begin(); jt != it->second.end(); ++jt)
		{
			cout << *jt;
			cout << (*jt != it->second.back() ? ", " : ";");
		}
		cout << endl;
	}

	cout << delimiter << endl;

	for (std::pair<std::string, std::vector<std::string>> i : dictionary)
	{
		cout << i.first << tab;
		for (std::vector<std::string>::iterator it = i.second.begin(); it != i.second.end(); ++it)
		{
			cout << *it << tab;
		}
		cout << endl;
	}
#endif // STL_MAP_2

	std::map<std::string, std::vector<std::string>> GAI =
	{
		std::pair<std::string, std::vector<std::string>>("1tst11", {"test", "test"}),
		{"1abc23", {"нет", "нет"}}
	};

	std::string number;
	cout << "Введите номер автомобиля "; cin >> number;
	std::string offense;
	std::vector<std::string> offense_list;
	cout << "Введите правонарушения. Введите 0 для продолжения "; 
	while (true)
	{
		cin >> offense;
		if (offense[0] == 48)break;
		offense_list.push_back(offense);
	}

	std::map<std::string, std::vector<std::string>>::iterator element = GAI.find(number);
	if (element != GAI.end())
	{
		element->second.insert(element->second.end(), offense_list.begin(), offense_list.end());
	}
	else
	{
		GAI.emplace(std::pair<std::string, std::vector<std::string>>(number, offense_list));
	}

	for (std::pair<std::string, std::vector<std::string>> i : GAI)
	{
		cout << i.first << ":\t";
		for (std::vector<std::string>::iterator it = i.second.begin(); it != i.second.end(); ++it)
		{
			cout << *it << ", ";
		}
		cout << "\b\b." << endl;
	}
}