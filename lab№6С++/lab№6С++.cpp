#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <windows.h>

#include <algorithm>



using namespace std;

FILE* fout, *fin; //объекты для записи данных в файл и чтение их из файла

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
		cin.ignore(); // для ввода нескольких слов в одной строке
		cout << "Фамилия: ";
		getline(cin, workers[i].surname); //ввод данных в элемент структуры
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

	fout = fopen("Workers.bin", "wb"); //открываем файл
	fwrite(workers, sizeof(Workers), number, fout); //запись в файл
	fclose(fout);
	delete[] workers; //освобождаем память
	workers = nullptr;
	Workers* restored = new Workers[number];
	fin = fopen("Workers.bin", "rb");
	fread(restored, sizeof(Workers), number, fin);
	fclose(fin);
	cout << endl << "Информация о всех работниках женского пола без высшего образования, которым в этом году необходимо оформлять пенсию:" << endl << endl;
	for (int i = 0; i < number; i++)
	{
		std :: transform(restored[i].education.begin(), restored[i].education.end(), restored[i].education.begin(), tolower);
		if (restored[i].age >= 60 && restored[i].gender._Equal( "женский") && !restored[i].education._Equal("высшее"))
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
	const int n = 5, m = 5;
	int matrix[n][m];
	cout << "Введите элементы матрицы:" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			/*cin >> matrix[i][j];*/
			matrix[i][j] = rand() % 100;
		}
	}
	fout = fopen("matrix.bin", "wb");
	fwrite(matrix, sizeof(int), n*m, fout);
	fclose(fout);
	int restored[n][m];
	fin = fopen("matrix.bin", "rb");
	fread(restored, sizeof(int), n*m, fin);
	fclose(fin);
	cout << endl << "Матрица которую вы ввели: " << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << restored[i][j] << "\t";
		}
		cout << endl << endl;
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			restored[i][j] *= 2;
		}
	}
	fout = fopen("matrix.bin", "wb");
	fwrite(restored, sizeof(int), n*m, fout);
	fclose(fout);
	cout << endl << endl << "Матрица, елементы которой увеличены в 2 раза:" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
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
			InternetNetwork[i].cost_per_month = (InternetNetwork[i].cost_per_month - InternetNetwork[i].cost_per_month*0.07);
		}
	}
	fout = fopen("Internet.bin", "wb");
	fwrite(InternetNetwork, sizeof(Internet_Network), number, fout);
	fclose(fout);
	fin = fopen("Internet.bin", "rb");
	fread(InternetNetwork, sizeof(Internet_Network), number, fin);
	fclose(fin);
	cout << endl << "Информация о клиентах со снижением тарифа на 7%, если он оплатил на 3 месяца вперед:" << endl << endl;
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

