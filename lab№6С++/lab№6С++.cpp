#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

FILE* fout, *fin;

void Task1()
{
	struct Workers {
		string surname;
		int age;
		string education;
		string position;
		string gender;
	};
	int number;
	do
	{
		cout << "Введите колличество работников: ";
		cin >> number;
	} while (number <= 0);
	Workers *workers = new Workers[number];
	for (int i = 0; i < number; i++)
	{
		cin.ignore();
		cout << "Фамилия: ";
		getline(cin, workers[i].surname);
		do
		{
			cout << "Возраст: ";
			cin >> workers[i].age;
			if (workers[i].age <= 0 || workers[i].age > 100)
				cout << "Возраст введен некорректно." << endl;
		} while (workers[i].age <= 0 || workers[i].age > 100);

	    cin.ignore();
		cout << "Образование: ";
		getline(cin, workers[i].education);
					 
		cout << "Должность: ";
		getline(cin, workers[i].position);
		
		cout <<" Пол: ";			
		getline(cin, workers[i].gender);
	}

	fout = fopen("Workers.bin", "wb");
	fwrite(workers, sizeof(Workers), number, fout);
	fclose(fout);
	delete[] workers;
	workers = nullptr;
	Workers* restored = new Workers[number];
	fin = fopen("Workers.bin", "rb");
	fread(restored, sizeof(Workers), number, fin);
	fclose(fin);
	cout << endl << "Информация о всех работниках женского пола без высшего образования, которым в этом году необходимо оформлять пенсию:" << endl << endl;
	for (int i = 0; i < number; i++)
	{
		if (restored[i].age >= 60 && restored[i].gender == "женский" && restored[i].education != "высшее")
		{
			cout << "Работник №" << i + 1 << endl;
			cout << "Фамилия: " << restored[i].surname << " " << endl;
			cout << "Возраст: " << restored[i].age << endl;
			cout << "Образование: " << restored[i].education << endl;
			cout << "Должность: " << restored[i].position << endl;
			cout << "Пол: " << restored[i].gender << endl;
			cout << "--------------------------" << endl;
		}
	}						
}
///////////////////////////////////////
void Task2()
{
	int matrix[5][5];
	cout << "Введите элементы матрицы:" << endl;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			/*cin >> matrix[i][j];*/
			matrix[i][j] = rand() % 10;
		}
	}
	fout = fopen("matrix.bin", "wb");
	fwrite(matrix, sizeof(int), 25, fout);
	fclose(fout);
	int restored[5][5];
	fin = fopen("matrix.bin", "rb");
	fread(restored, sizeof(int), 25, fin);
	fclose(fin);
	cout << endl << "Матрица которую вы ввели: " << endl;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << restored[i][j] << "\t";
		}
		cout << endl << endl;
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			restored[i][j] *= 2;
		}
	}
	fout = fopen("matrix.bin", "wb");
	fwrite(restored, sizeof(int), 25, fout);
	fclose(fout);
	cout << endl << endl << "Матрица, елементы которой увеличены в 2 раза:" << endl;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << restored[i][j] << "\t";
		}
		cout << endl << endl;
	}

}
/////////////////////////////////
void Task3()
{
	struct Name {
		string surname;
		string name;
		string patronymic;
	};
	struct Internet_Network {
		Name name;
		float cost_per_month;
		int number_of_months;
		int number_of_months_forward;
	};	
	int number;
	do
	{
		cout << "Введите количество клиентов интернет сети: ";
		cin >> number;
	} while (number <= 0);

	Internet_Network* InternetNetwork = new Internet_Network[number];
	
	for (int i = 0; i < number; i++)
	{
		cout << "Введите фамилию, имя и отчество " << i + 1 << " клиента: ";
		cin >> InternetNetwork[i].name.surname >> InternetNetwork[i].name.name >> InternetNetwork[i].name.patronymic;
		do
		{
			cout << "Стоимость тарифного плана за месяц: ";
			cin >> InternetNetwork[i].cost_per_month;
		} while (InternetNetwork[i].cost_per_month <= 0);
		do
		{
			cout << "Количество месяцев оплаты интернет сети: ";
			cin >> InternetNetwork[i].number_of_months;
		} while (InternetNetwork[i].number_of_months <= 0);
		InternetNetwork[i].number_of_months_forward = InternetNetwork[i].number_of_months - 1;
		cout << endl << endl;
	}
	fout = fopen("Internet.bin", "wb");
	fwrite(InternetNetwork, sizeof(Internet_Network), number, fout);
	fclose(fout);
	fin = fopen("Internet.bin", "rb");
	fread(InternetNetwork, sizeof(Internet_Network), number, fin);
	fclose(fin);

	for (int i = 0; i < number; i++)
	{
		if (InternetNetwork[i].number_of_months_forward >= 3)
		{
			InternetNetwork[i].cost_per_month = InternetNetwork[i].cost_per_month - InternetNetwork[i].cost_per_month*0.07;
		}
	}
	fout = fopen("Internet.bin", "wb");
	fwrite(InternetNetwork, sizeof(Internet_Network), number, fout);
	fclose(fout);
	fin = fopen("Internet.bin", "rb");
	fread(InternetNetwork, sizeof(Internet_Network), number, fin);
	fclose(fin);
	cout << endl << "Инфопмация о клиентах со снижением тарифа на 7%, если он оплатил на 3 месяца вперед:" << endl << endl;
	for (int i = 0; i < number; i++)
	{
		cout << "Клиент №" << i + 1 << ": " << endl;
		cout << "Имя: " << InternetNetwork[i].name.surname << " " << InternetNetwork[i].name.name << " " << InternetNetwork[i].name.patronymic << endl;
		cout << "Стоимость тарифного плана за месяц: " << InternetNetwork[i].cost_per_month << endl;
		cout << "Количество месяцев оплаты интернет сети : " << InternetNetwork[i].number_of_months << endl;
		cout << "Количество месяцев, оплаченых наперед: " << InternetNetwork[i].number_of_months_forward << endl;
		cout << "-------------------------------------" << endl;
	}
}

int main()
{
	int numTask;
	cout << "Enter num of task: ";
	cin >> numTask;
	setlocale(LC_ALL, "Rus");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	switch (numTask)
	{
	case 1:
		Task1();
		break;
	case 2:
		Task2();
		break;
	case 3:
		Task3();
		break;	
	}
}

