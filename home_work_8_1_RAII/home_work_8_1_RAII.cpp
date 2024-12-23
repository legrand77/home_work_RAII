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
private:
	int _value;
	int status{};

public:
	void set_value(int x) { _value = x; }
	void set_status(int x) { status = x; }
	int get_value() { return _value; }
	int get_status() { return status; }

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
private:
	int x;
	int count{};
    Int* arr{nullptr};


public:
	void add_element(int value)
	{
		count++;
		if (count > x) throw str_error("Количество элементов больше количества элементов, на которую выделена память");
		for (int i=0; i < x; i++)
		{
			if (arr[i].get_status() != 1)
			{
				arr[i].set_value(value);
				arr[i].set_status(1);
				break;
			}
		}
	}
	int get_element(int value)
	{	if ((value < 0) || (value >= x)) throw str_error("Некорректность индекса получения элемента");
		return arr[value].get_value();
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
		std::cout << arr.get_element(1) << std::endl;
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}

	return EXIT_SUCCESS;
}