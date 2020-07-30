#include <iostream>
#include <clocale>
#include <string>
#include <cmath>
#include <cstdlib>
#include <fstream> 

using namespace std;

string user;
int balance = 0;
int stocklist[2][4];
string stockname[4] = {"Стиральные машины","Электрические чайники","Холодильники","Духовые шкафы"};

int alarm() {
	int count = 0;
	if (stocklist[0][0] < 10 || stocklist[0][1] < 10 || stocklist[0][2] < 10 || stocklist[0][3] < 10) {
			cout << "\nВнимание! На складе менее 10 единиц товара(ов): ";
			int i = 0;
			while(i < 4) {
				if (stocklist[0][i] < 10) {
				count++;
				if (count > 1) cout << ", " << stockname[i];
					else cout << stockname[i];
				}
				i++;
			}
			cout << "\n";
	}
	return(0);
}

int loaddata() {
	int element;
	ifstream file("data.txt");
	int i = 0;
	while (i < 9) {
		while (file >> element) {
			if (i <= 3) stocklist[0][i] = element;
			else if (i < 8) stocklist[1][i-4] = element;
			if (i == 8) balance = element;
			i++;
		}
	}
	file.close();	
	return (0);
}

int savedata() {
	remove ("data.txt");
	ofstream file ("data.txt");
	int i = 0;
	while (i < 9) {
		if (i <= 3) file << stocklist[0][i] << " ";
		else if (i < 8) file << stocklist[1][i-4] << " ";
		if (i == 8) file << balance;
		i++;
	}
	file.close();
	return(0);
}

int changeprice() {
	system ("cls");
	int numprice,change;
	cout << "Какую цену вы хотите изменить? \n 1. Стиральные машины \n 2. Электрические чайники \n 3. Холодильники \n 4. Духовые шкафы \n";
	cin >> numprice;
	if (numprice <= 4 && numprice >= 1) {
	cout << "Какой будет новая цена? \n";
	cin >> change;	
	stocklist[1][numprice-1] = change;
	}
	savedata();
	return(0);
}

int fillstock() {
	system("cls");
	int type, quantity;
	cout << "Какой вид продукции прибыл на склад? \n 1. Стиральные машины \n 2. Электрические чайники \n 3. Холодильники \n 4. Духовые шкафы \n";
	cin >> type;
	if (type >= 1 && type <= 4) {
	cout << "Сколько единиц продукции прибыло? \n";
	cin >> quantity;
	stocklist[0][type-1] = stocklist[0][type-1] + quantity;
	}
	savedata();
	return(0);
}

int printdata() {
	int i4,balmil;
	balmil = 0;
	system("cls");
	for (i4=0;i4<4;i4++)
		cout << (stockname[i4]) << " в количестве " << (stocklist[0][i4]) << " по цене " << (stocklist[1][i4]) << " P\n";
	if (balance/1000000 != 0) balmil = balance/1000000;
	cout << "\nДоход компании: ";
	if (balmil != 0) cout << balmil; 
	cout << " " << balance/1000-balmil*1000 << " " << balance%1000 << " P\n";
	system("pause");
	return(0);
}

int purchase(){
	int nbuy, qbuy;
	string yn;
	system("cls");
	cout << "Что вы желаете приобрести? \n 1. Стиральную машину - 5999 P \n 2. Электрический чайник - 999 P \n 3. Холодильник - 7999 P\n 4. Духовой шкаф - 6999 P\n \n 5. Выйти из меню покупок\n";
	cin >> nbuy;
	if (nbuy <= 5 && nbuy >= 1)
	{
	if (nbuy == 5) return(1);
	cout << "Сколько единиц товара вы желаете приобрести? ";
	cin >> qbuy;
	if (stocklist[0][nbuy-1]>=qbuy) {
		cout << qbuy << " единиц товара " << (stockname[nbuy-1]) << " будут стоить вам " << (qbuy*stocklist[1][nbuy-1]) << ". Подтвердить покупку? (Да - 1/Нет - 2) ";  
		cin >> yn;
		if (yn == "1")	{
			stocklist[0][nbuy-1] = stocklist[0][nbuy-1] - qbuy;
			balance = balance + qbuy*stocklist[1][nbuy-1];
			cout << "Спасибо за покупку! \n";
			system("pause");
			savedata();
			return(0);
		}
			else {
				cout << "Сожалеем, возвращайтесь к нам ещё! \n";
				system("pause");
				return(0);	
			}
	}
		else {
			cout << "К сожалению, сейчас на складе товара " << (stockname[nbuy-1]) << " только " << (stocklist[0][nbuy-1]) << " штук \n";
			system("pause");
			return(0);
		}
	}
	savedata();
	return(0);
}

string menu(string user) { 
	string log,pass;
	int a;
	if (user == "manager") goto manager;
	if (user == "client") goto client;
	admin:
		system("cls");
		cout << "Админ:\n";
		cout << "Меню: \n 1. Внести покупку \n 2. Пополнить склад \n 3. Вывести отчет по складу и прибыли \n 4. Изменить цены \n \n 5. Выйти из системы\n 6. Вернуть систему к исходным данным\n";
		alarm();
		cin >> a;
		while (true) {
		if (a == 1) goto adm1;
		if (a == 2) goto adm2;
		if (a == 3) goto adm3;
		if (a == 4) goto adm4;
		if (a == 5) return("");
		if (a == 6) {
			stocklist[0][0] = 100;
			stocklist[0][1] = 100;
			stocklist[0][2] = 100;
			stocklist[0][3] = 100;
			stocklist[1][0] = 5999;
			stocklist[1][1] = 999;
			stocklist[1][2] = 7999;
			stocklist[1][3] = 6999;
			balance = 0;
			savedata();
			goto admin;
		}
		else goto admin;				
		}
	adm1:
		purchase();
		goto admin;
	adm2:
		fillstock();
		goto admin;
	adm3:	
		printdata();
		goto admin;
	adm4:
		changeprice();
		goto admin;
		
	manager:
		system("cls");
		cout << "Менеджер:\n";
		cout << "Меню: \n 1. Внести покупку \n 2. Пополнить склад \n 3. Вывести отчет по складу и прибыли \n \n 4. Выйти из системы \n";
		alarm();
		cin >> a;
		for (int i3 = 0; i3 < 4; i3++) {
			if (a == 1) goto a1;
			if (a == 2) goto a2;
			if (a == 3) goto a3;
			if (a == 4) return("");
				else goto manager;				
		}
	a1:
		purchase();
		goto manager;
	a2:
		fillstock();
		goto manager;
	a3:	
		printdata();
		goto manager;
	client:   
	if (purchase() == 1) return("");
		else goto client;
	return("");
}

string logpass() { //процесс регистрации в сис
	system("cls");
	cout << "Пожалуйста, зарегестрируйтесь. (если вы клиент, log: client, pass: client) \n(Также доступны аккаунты: admin, manager)\n";
	
	string log,pass;
	int lognum;
	
	string loglist[3];
		loglist[0] = "admin";
		loglist[1] = "manager";
		loglist[2] = "client";
	string passlist[3];
		passlist[0] = "admin";
		passlist[1] = "manager";
		passlist[2] = "client";
	login:
	cout << "Введите свой логин: ";
	cin >> log;
	for (int i =0; i < 3; i++) 
		if (log == loglist[i]) {
			lognum = i;	
			goto endlog;
		}
	system("cls");
	cout << "В базе нет такого логина! \n";
	goto login;
	endlog:
	passin:
	cout << "Введите свой пароль: (введите 'back' чтобы вернуться у вводу логина) \n";
	cin >> pass;
	if (pass == passlist[lognum]) goto endlogpass;
		else if (pass == "back") goto login;
			else {
				cout << "Неверный пароль! \n";
				goto passin;
			}                         
	endlogpass:
	cout << "Вы зарегестрировались в системе! \n";
	user = loglist[lognum];
	cout << "Добро пожаловать, " << user << "! \n";
	system("pause");
	return(user);	
}

main() {
	system("Color 71");
	loaddata();
	setlocale(LC_ALL, "Russian");	
	while (true) {
		logpass();
		menu(user);
	}
	return(0);
}




