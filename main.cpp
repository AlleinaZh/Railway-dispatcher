#include <unordered_map>
#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <iterator>
#include <vector>
#include <cstdio>
#include <ctime>
#include <cmath>

using namespace std;

struct Train
{
	int number;
	char departure_city;
	char arrival_city;
	int departure_day;
	float departure_time;
	int arrival_day;
	float arrival_time;
	int condition;
	bool accidient;
	Train()
	{
		int possibility_of_an_accidient;
		condition = rand() % 6;
		if (condition == 0)
		{
			possibility_of_an_accidient = rand() % 2;
		}
		else if (condition > 0 && condition <= 2)
		{
			possibility_of_an_accidient = rand() % 6;
		}
		else if (condition > 3 && condition <= 5)
		{
			possibility_of_an_accidient = rand() % 12;
		}
		else
		{
			possibility_of_an_accidient = rand() % 9;
		}

		if (possibility_of_an_accidient > 0) accidient = false;
		else accidient = true;
	}
};

void enter_number(int &trainnum, int &i)
{
	int num = NULL;
	do
	{
		if (num != NULL) cout << " Введені дані не відповідають вимогам, введіть скореговані дані: ";
		cin >> num;
		trainnum = num;
		for (i = 0; num > 0; i++) num /= 10;
	} while (trainnum <= 0);
}

void enter_city(char &city)
{
    city = NULL;
	do
	{
		if (city != NULL) cout << " Введені дані не відповідають вимогам, введіть скореговані дані: ";
		cin >> city;
		getchar();

		if (city > 96 && city < 123)
		{
			int a = city;
			city = a - 32;
		}
	} while (city < 65 || city>90);
}

void enter_day(int &day)
{
	day = NULL;
	do
	{
		if (day != NULL) cout << " Введені дані не відповідають вимогам, введіть скореговані дані: ";
		cin >> day;

	} while (1 > day || 30 < day);
}


void enter_time_from(Train& train)
{
    train.departure_time = NULL;
	do
	{
		if (train.departure_time != NULL) cout << " Введені дані не відповідають вимогам, введіть скореговані дані: ";
		cin >> train.departure_time;
	} while (train.departure_time > 23.59 || train.departure_time < 00.00);
}

void enter_time_to(Train& train)
{
	train.arrival_time = NULL;
	do
	{
		if (train.arrival_time != NULL) cout << " Введені дані не відповідають вимогам, введіть скореговані дані: ";
		if (train.departure_day == train.arrival_day)
		{
			do
			{
				cin >> train.arrival_time;
			} while (train.arrival_time <= train.departure_time);
		}
		else cin >> train.arrival_time;
	} while (train.arrival_time > 23.59 || train.arrival_time < 00.00);
}

void print_one_train(Train& train)
{
   cout << "  __________________________________________" << endl
		<< " | Потяг номер " << train.number << endl
		<< " |-Відправка- " << endl
		<< " | •Місто " << train.departure_city << endl
		<< " | •День " << train.departure_day << endl
		<< " | •Час " << train.departure_time << endl
		<< " |-Прибуття-" << endl
		<< " | •Місто " << train.arrival_city << endl
		<< " | •День " << train.arrival_day << endl
		<< " | •Час " << train.arrival_time << endl
		<< " |Стан потягу (0-5) " << train.condition << endl
		<< " |__________________________________________" << endl;
}

void key_creator(int &trainnum, char &cityfrom, char &cityto, int &i,long long &key)
{
	key = (cityfrom * 100 * pow(10, i)) + (trainnum * 100) + cityto;
}

void create_train(unordered_map<long long, Train>& Dispatcher, vector <Train>& Broken)
{

	Train train;
	cout << " !!Створення потягу!!" << endl << " По черзі введіть дані, які будуть запитуватись." << endl;
	cout << " •Номер потягу (будь яка кількість цифр, число має починатись із 1-9): ";
	int trainnum;
	int i;
	enter_number(trainnum, i);
	train.number = trainnum;

	cout << " •Перша літера міста з якого відправиться потяг (англійською): ";
	char cityfrom;
	enter_city(cityfrom);
	train.departure_city = cityfrom;
	
	cout << " •Перша літера міста в яке прибуває потяг (англійською): ";
	char cityto;
	enter_city(cityto);
	train.arrival_city = cityto;

	cout << " •День у який потяг відправиться (з 1-30): ";
	int day_from;
	enter_day(day_from);
	train.departure_day = day_from;

	cout << " •День у який потяг прибуде (з 1-30): ";
	int day_to;
	enter_day(day_to);
	train.arrival_day = day_to;

	cout << " •Час у який потяг відправиться (записується через крапку): ";
	enter_time_from(train);

	cout << " •Час у який потяг прибуде (записується через крапку): ";
	enter_time_to(train);

	long long key;
	key_creator(trainnum, cityfrom, cityto, i, key);

	print_one_train(train);
	

	if (train.accidient)
	{
		int choice;
		cout << " !!!!У рейсі сталася аварія!!!!\n" << " Щоб зберегти потяг натисніть 1 . Або будь яку цифру, щоб продовжити:";
		cin >> choice;
		if (choice == 1)
		{
			cout << " Потяг збережено." << endl;
			Broken.push_back(train);
		}
	}
	else Dispatcher.insert({ key, train });

	system("pause");
	system("cls");
}

void delete_train(unordered_map<long long, Train>& Dispatcher)
{
	int trainnum, i;
	char cityfrom, cityto;
	cout << "  Для того щоб видалити потяг треба ввести його номер та міста звідки - куди він прямує" << endl;
	cout << " •Номер потягу: ";
	enter_number(trainnum, i);

	cout << " •Перша літера міста з якого відправиться потяг: ";
	enter_city(cityfrom);

	cout << " •Перша літера міста в яке прибуває потяг: ";
	enter_city(cityto);

	long long key;
	key_creator(trainnum, cityfrom, cityto, i, key);

	if (Dispatcher.find(key) == Dispatcher.end())
	{
		cout << " !Такий потяг відстуній у списку працюючих потягів!" << endl;;
		system("pause");
		return;
	}

	Dispatcher.erase(key);
	cout << " Потяг видалено " << endl;;
	system("pause");
	system("cls");
}

void change_time(unordered_map<long long, Train>& Dispatcher)
{
	int trainnum, i;
	char cityfrom, cityto;
	cout << "  Для того щоб видалити потяг треба ввести його номер та міста звідки - куди він прямує" << endl;
	cout << " •Номер потягу: ";
	enter_number(trainnum, i);

	cout << " •Перша літера міста з якого відправиться потяг: ";
	enter_city(cityfrom);

	cout << " •Перша літера міста в яке прибуває потяг: ";
	enter_city(cityto);

	long long key;
	key_creator(trainnum, cityfrom, cityto, i, key);


	if (Dispatcher.find(key) == Dispatcher.end())
	{
		cout << " Такого потяга не існує " << endl;;
		system("pause");
		return;
	}

	unordered_map<long long, Train>::iterator itr;
	itr = Dispatcher.find(key);
	Train train = itr->second;
	print_one_train(train);

	Dispatcher.erase(key);

	cout << " •Новий час у який потяг відправиться (записується через крапку): ";
	enter_time_from(train);

	cout << " •Новий час у який потяг прибуде (записується через крапку): ";
	enter_time_to(train);


	print_one_train(train);

	Dispatcher.insert({ key, train });

	system("pause");
	system("cls");
}

void print_all(unordered_map<long long, Train>& Dispatcher)
{
	unordered_map<long long, Train>::iterator itr;
	cout << "  _______________________________________" << endl;
	for (itr = Dispatcher.begin(); itr != Dispatcher.end(); itr++)
	{
		Train train = itr->second;
		cout << " | Потяг номер " << train.number << endl
			<< " |-Відправка- " << endl
			<< " | •Місто " << train.departure_city << endl
			<< " | •День " << train.departure_day << endl
			<< " | •Час " << train.departure_time << endl
			<< " |-Прибуття-" << endl
			<< " | •Місто " << train.arrival_city << endl
			<< " | •День " << train.arrival_day << endl
			<< " | •Час " << train.arrival_time << endl
			<< " |Стан потягу (0-5) " << train.condition << endl
			<< " |__________________________________________" << endl;
	}
	system("pause");
	system("cls");
}

void print_all_Broken(vector <Train>& Broken)
{
	vector <Train> ::iterator itr;
	cout << "  _________________________________________" << endl;
	for (itr = Broken.begin(); itr != Broken.end(); ++itr)
	{
		cout << " | Потяг номер " << itr->number << endl
			<< " |-Відправка- " << endl
			<< " | •Місто " << itr->departure_city << endl
			<< " | •День " << itr->departure_day << endl
			<< " | •Час " << itr->departure_time << endl
			<< " |-Прибуття-" << endl
			<< " | •Місто " << itr->arrival_city << endl
			<< " | •День " << itr->arrival_day << endl
			<< " | •Час " << itr->arrival_time << endl
			<< " |Стан потягу (0-5) " << itr->condition << endl
			<< " |__________________________________________" << endl;
	}

	system("pause");
	system("cls");
}

void by_number_and_city(unordered_map<long long, Train>& Dispatcher)
{
	int trainnum, i;
	char cityfrom, cityto;
	cout << "  Для того щоб знайти день та час відправки-прибуття потяга треба ввести його номер та міста звідки - куди він прямує" << endl;
	cout << " •Номер потягу: ";
	enter_number(trainnum, i);

	cout << " •Перша літера міста з якого відправиться потяг: ";
	enter_city(cityfrom);

	cout << " •Перша літера міста в яке прибуває потяг: ";
	enter_city(cityto);

	long long key;
	key_creator(trainnum, cityfrom, cityto, i, key);


	if (Dispatcher.find(key) == Dispatcher.end())
	{
		cout << " !Такого потяга не існує!";
		system("pause");
		return;
	}
	unordered_map<long long, Train>::iterator itr;
	itr = Dispatcher.find(key);
	Train train = itr->second;

	print_one_train(train);

	system("pause");
	system("cls");
}

void from_A_to_B(unordered_map<long long, Train>& Dispatcher)
{
	char cityfrom, cityto;

	cout << " -Введіть перші літери міст для пошуку- " << endl;
	cout << " •Перша літера міста з якого відправиться потяг: ";
	enter_city(cityfrom);

	cout << " •Перша літера міста в яке прибуває потяг: ";
	enter_city(cityto);

	unordered_map<long long, Train>::iterator itr;
	int i = 0;
	cout << "  _______________________________________" << endl;
	for (itr = Dispatcher.begin(); itr != Dispatcher.end(); itr++)
	{
		Train train = itr->second;
		if (cityfrom == train.departure_city && cityto == train.arrival_city)
		{
			i++;
			cout<< " | Потяг номер " << train.number << endl
				<< " |-Відправка- " << endl
				<< " | •Місто " << train.departure_city << endl
				<< " | •День " << train.departure_day << endl
				<< " | •Час " << train.departure_time << endl
				<< " |-Прибуття-" << endl
				<< " | •Місто " << train.arrival_city << endl
				<< " | •День " << train.arrival_day << endl
				<< " | •Час " << train.arrival_time << endl
				<< " |Стан потягу (0-5) " << train.condition << endl
				<< " |__________________________________________" << endl;
		}
	}
	if (i == 0) cout << "Потягів з міста " << cityfrom << " в місто " << cityto << " немає." << endl;

	system("pause");
	system("cls");
}

void control_menu(unordered_map<long long, Train>& Dispatcher, vector <Train>& Broken)
{

	cout << ".........КОНТРОЛЬНЕ МЕНЮ..........\n";
	int ch;
	do
	{
		cout << " _____________________________________________________________________\n"
			<< "| 1.Створити потяг                                                    |\n"
			<< "| 2.Видалити потяг                                                    |\n"
			<< "| 3.Змінити час існуючого потягу                                      |\n"
			<< "| 4.Вивести графік потягів                                            |\n"
			<< "| 5.Вивести список зламаних потягів                                   |\n"
			<< "| 6.Повернутись до головного меню                                     |\n"
			<< "|_____________________________________________________________________|\n"
			<< " Введіть Ваш вибір: ";
		cin >> ch;
		switch (ch)
		{
		case 1:
			system("cls");
			create_train(Dispatcher, Broken);
			break;
		case 2:
			system("cls");
			delete_train(Dispatcher);
			break;
		case 3:
			system("cls");
			change_time(Dispatcher);
			break;
		case 4:
			system("cls");
			print_all(Dispatcher);
			break;
		case 5:
			print_all_Broken(Broken);
			break;
		}
	} while (ch <= 4);
	getchar();
	system("cls");

}

void user_menu(unordered_map<long long, Train>& Dispatcher)
{

	cout << ".........МЕНЮ КОРИСТУВАЧА...........\n";
	int ch;
	do
	{
		cout << "  ___________________________________________ \n"
			<< " |1.Отримати інформацію про окремий потяг    |\n"
			<< " |2.Список усіх потягів із міста А в місто Б |\n"
			<< " |3.Список всіх потягів                      |\n"
			<< " |4.Повернутись до головного меню            |\n"
			<< " |___________________________________________|\n"
			<< " Ваш вибір:";
		cin >> ch;
		cout << endl;
		switch (ch)
		{
		case 1:
			system("cls");
			by_number_and_city(Dispatcher);
			break;
		case 2:
			system("cls");
			from_A_to_B(Dispatcher);
			break;
		case 3:
			system("cls");
			print_all(Dispatcher);
			break;
		}
	} while (ch <= 3);
	getchar();
	system("cls");
}

int main()
{
	SetConsoleOutputCP(1251);
	unordered_map <long long, Train> Dispatcher;
	vector <Train> Broken;
	srand(time(0));
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
		<< "......ПОЧАТОК РОБОТИ ПРОГРАМИ-ДИСПЕТЧЕРА.......\n"
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
		<< " програма працює із записами лише на один місяць" << endl << endl;

	int choice;
	char exit;
	do
	{
		do
		{
			cout << " ______________________________________________________\n"
				<< "|   щоб працювати із потягами натисніть 1;             |\n"
				<< "| щоб подивитись інформацію про потяги натисніть 2;    |\n"
				<< "|______________________________________________________|\n"
				<< " Ваш вибір: ";
			cin >> choice;
			system("cls");
			if (choice == 1) control_menu(Dispatcher, Broken);
			else if (choice == 2) user_menu(Dispatcher);

		} while (choice > 2 || choice < 1);
		cout << " Натисніть англійське e для того щоб вийти або будь-що, щоб повторити\n"
			<< " Ваш вибір: ";
		cin >> exit;
	} while (exit != 'e');
	getchar();
	system("cls");

	cout << "***********************************************\n"
		<< "  ............ЗАКІНЧЕННЯ РОБОТИ..............\n"
		<< "***********************************************\n";

	return 0;
}
