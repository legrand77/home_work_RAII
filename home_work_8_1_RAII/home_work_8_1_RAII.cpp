/*#include <iostream>
#include <vector>


class Int
{ public:
	Int(int value = 0) : _value{ value } { std::cout << "Int" << std::endl; }

	~Int() { std::cout << "~Int" << std::endl; }

	int _value{};

};

int main(int argc, char* argv[])
{
	const int arr_count = 3;
	Int* arr = new Int[arr_count];

	for (int i = 0; i < arr_count; i++)
	{
		if (i > 1) { delete[] arr; return -1; }
		arr[i]._value = i;
		std::cout << arr[i]._value << std::endl;

	}
	delete[] arr;
	return EXIT_SUCCESS;

}*/


#include <iostream>
#include <vector>
#include <string>

class str_error : public std::exception // обработка исключений
{
public:
	str_error(const std::string& message) : message{ message }
	{}
	const char* what() const noexcept override
	{
		return message.c_str();     // получаем из std::string строку const char*
	}
private:
	std::string message;    // сообщение об ошибке
};

class Int
{
public:
	//Int(int value = 0) : _value{ value } { std::cout << "Int" << std::endl; }
  // ~Int() { std::cout << "~Int" << std::endl; }
	int _value;
	int status{};	
};

class smart_array
{
public:
	smart_array(int count)
	{
		arr = new Int[count];
		x = count;
	}

	~smart_array()
	{
		if (nullptr != arr)
		{
			delete[] arr;
		}
	}
public:
	int x;
	int count{};
    Int* arr{nullptr};
	void add_element(int value)
	{
		count++;
		if (count > x) throw str_error("Количество элементов больше количества элементов, на которую выделена память");
		for (int i=0; i < x; i++)
		{
			if (arr[i].status != 1)
			{
				arr[i]._value = value;
				arr[i].status = 1;
				break;
			}
		}
	}
	int get_element(int value)
	{	if ((value < 0) || (value >= x)) throw str_error("Некорректность индекса получения элемента");
		return arr[value]._value;
	}
};

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	system("chcp 1251");
	try {
		smart_array arr(5);
		arr.add_element(1);
		arr.add_element(4);
		arr.add_element(155);
		arr.add_element(14);
		arr.add_element(15);
		//arr.add_element(18); // 6 элемент
		std::cout << arr.get_element(1) << std::endl;
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}


	//const int arr_count = 3;
	/*smart_array arr(arr_count);
	for (int i = 0; i < arr_count; i++)
	{
		if (i > 1) return -1;
		arr.arr[i]._value = i;
		std::cout << arr.arr[i]._value << std::endl;

	}*/
	return EXIT_SUCCESS;

}