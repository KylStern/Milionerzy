#include <iostream>
#include <ctime>
#include <random>
#include <windows.h>
#include <string>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include<iomanip>

using namespace std;


mt19937 generator(time(nullptr));
uniform_int_distribution<int> odp(0, 3);//losowanie odpowiedzi 
uniform_int_distribution<int> pyt(0, 9);//losowanie pytan

fstream  Historia;//plik do zapisu u�ytkownik�w i ich wynikow
uniform_int_distribution<int> fifty(0, 1);//losowanie kolejno�ci odp prawid�owej i fa�szywej w kole 50/50
int zwyciestwa = 0;int porazki = 0;//liczniki, zwyci�stwa oznaczaj� zdobyte punkty, inna warto�� pora�ek ni� 0 oznacza przegran� i zako�czenie gry
int kolaRatunkowe = 3;//liczba k� ratunkowych
char decyzja;//u�yta w Menu, okre�la co chce zrobi� u�ytkownik
string uzytkownik;//nazwa u�ytkownika
int checGry = 1;//czy u�ytkownik chce gra�, domy�lnie ustawione na 1, inna warto�� przerywa p�tl� 
string czychcegrac{};//odpowied� u�ytkownika na pytanie czy chce dalej gra�
bool CzyChceGrac = true;// je�li true to gra zaczyna si� od nowa, je�li false, to wy�wietla si� menu

int powtorzonePytanie;// warto�� zmienia si� w funkcjach odpowiedzialnych za wy�wietlanie pyta�, upewnienie �e to samo pytanie nie 
//wy�wietli si� po u�yciu ko�a "zmiana pytania"

//komentarze w funkcji pyt1 odnosz� si� te� do funkcji pyt2, pyt3, ... ,pyt12.

void pyt1()
{
	int losPytanie;//kwestia bezpiecze�stwa, ustawienie na pocz�tek du�ej warto�ci r�wnej powtorzonePytanie
	losPytanie = pyt(generator);//losowanie numeru pytania (w tym indeksu tablicy pyta� i odpowiedzi)
	start:
	string Pytanie[10]{ "Jaki jest symbol chemiczny potasu?","Jaki jest symbol chemiczny Z�ota?","Autorem 'Potopu', powie�ci opowiadaj�cej o potopie szwedzkim, jest: ","W mitologii greckiej opiekunk� ogniska domowego by�a bogini:","W mitologii greckiej z g�owy Zeusa wyskoczy�a: ","W mitologii greckiej bogiem wojny by�:","Najd�uzsza polska rzeka to: ","Ile w Polsce jest wojew�dztw?","Mo�na zna� si� jak dwa �yse:","Na drzewach nie rosn�:" };
	int prawidlowa = odp(generator);//wylosowanie, kt�ra odpowied� fa�szywa zostanie zast�piona
	int licznik = 0;//indeks odpowiedzi
	int fifty_fifty;//dla ko�a 50/50
	int los;//losowanie kolejno�ci pyta� fa�szywych
	int zamiana;//podpi�cie odpowiedzi u�ytkownika do inta
	double bylo[4]{ 5,5,5,5 };//tablica sprawdzaj�ca, czy warto�� los si� powtarza
	char abcd[4]{ 'a','b','c','d' };	// litery od 'a' do 'b', do wy�wietlenia przy odpowiedziach
	string pr[10]{ "K",  "Au",  "H. Sienkiewicz",  "Hestia",  "Atena",  "Ares",  "Wis�a",  "16",  "Konie",  "Truskawki", };//odpowiedzi prawid�owe
	string f1[10]{ "Na","Zn","J. Kochanowski", "Hera", "Persefona", "Kratos", "Odra", "14", "Psy", "Jab�ka", };
	string f2[10]{ "Au","He","A. Mickiewicz", "Atena", "Hera", "Hermes", "Warta", "15", "Koty", "�liwki", };
	string f3[10]{ "P","In","M. Rej", "Artemida", "Afrodyta", "Zeus", "San", "20", "Barany", "Banany", };
	string f4[10]{ "Pb","Ag","J. Tuwim", "Kora", "Hestia", "Hefajstos", "Bzura", "12", "Wielb��dy", "Gruszki", };// f1-f4 odpowiedzi fa�szywe
	string tab[4]{}; //ta tablica b�dzie wy�wietlana
	while (licznik < 4)
	{
		los = odp(generator);
		if (los == 0 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f1[losPytanie];
			bylo[licznik] = 0;
			licznik++;
		}
		else if (los == 1 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f2[losPytanie];
			bylo[licznik] = 1;
			licznik++;
		}
		else if (los == 2 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f3[losPytanie];
			bylo[licznik] = 2;
			licznik++;
		}
		else if (los == 3 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f4[losPytanie];
			bylo[licznik] = 3;
			licznik++;
		}
	}
	tab[prawidlowa] = pr[losPytanie]; // zast�pienie jednej z fa�szywych odpowiedzi prawdziw�
	do {
		pytanie:
		cout << endl<<"Ko�a ratunkowe: "<< kolaRatunkowe<< endl << endl << "Pytanie 1: " << Pytanie[losPytanie] << endl;
		for (int i = 0; i < 4; i++)// wypisanie odpowiedzi
		{
			cout << abcd[i] << ") ";
			cout << tab[i] << endl;
		}
		if (kolaRatunkowe != 0)
		{
			cout << endl << "Wybierz 'k', aby u�y� ko�a ratunkowego 50/50. Nie b�dziesz m�g� potem u�y� ko�a 'Zmiana pytania'." << endl;
			cout << "Wybierz 'l', aby u�y� ko�a ratunkowego 'Zmiana pytania'. Mo�esz go u�y� wielokrotnie i u�y� ko�a 50/50" << endl;
		}
		cout << endl << "Podaj odpowied�: ";
		char odpowiedz;
		cin >> odpowiedz;
		

		if (odpowiedz == 'a' || odpowiedz == 'A') //sprawdzenie odpowiedzi
			zamiana = 0;
		else if (odpowiedz == 'b' || odpowiedz == 'B')
			zamiana = 1;
		else if (odpowiedz == 'c' || odpowiedz == 'C')
			zamiana = 2;
		else if (odpowiedz == 'd' || odpowiedz == 'D')
			zamiana = 3;
		else if (odpowiedz == 'k' || odpowiedz == 'K') //ko�o ratunkowe 50/50
		{
			if (kolaRatunkowe != 0) //sprawdzenie czy ko�a ratunkowe s� dostepne
			{
				int rng = prawidlowa;
				while (rng == prawidlowa||( rng!=bylo[0] && rng != bylo[1] && rng != bylo[2] && rng != bylo[3]))
					rng = odp(generator);//wylosowanie indeksu odpowiedzi fa�szywej innego ni� indeks odpowiedzi prawdziwej,
				//plus upewnienie si�, �eby wcze�niej niewy�wietlona odpowied� si� nie wy�wietli�a
				
				
				fifty_fifty = fifty(generator);//losowanie mi�dzy 0 a 1
				zamiana = 5; //dla p�tli poni�ej
				while (zamiana==5) //zamiana ustawia si� na 5, je�li nie istnieje odpowied� pdana przez u�ytkownika
				{
					Sleep(1000);
					system("cls");
					cout << "Pytanie 1: " << Pytanie[losPytanie] << endl;
					if (fifty_fifty == 0)//ustalanie koljeno�ci odpowiedzi fa�szywej i prawdziewj
					{
						cout << "a) " << pr[losPytanie] << endl;
						cout << "b) " << tab[rng] << endl;
						prawidlowa = 0;
					}
					else if (fifty_fifty == 1)//tu te�
					{
						cout << "a) " << tab[rng] << endl;
						cout << "b) " << pr[losPytanie] << endl;
						prawidlowa = 1;
					}
						cout << endl << "Podaj odpowied�: ";
						cin >> odpowiedz;

					if (odpowiedz == 'a' || odpowiedz == 'A')//sprawdzenie odpowiedzi
						zamiana = 0;
					else if (odpowiedz == 'b' || odpowiedz == 'B')
						zamiana = 1;
					else if (odpowiedz == 'k' || odpowiedz == 'K')//zapobiegni�cie ponownemu u�yciu 50/50
					{
						zamiana = 5;//powt�rzenie p�tli
						cout << " Ju� u�y�e� ko�a ratunkowego, spr�buj ponownie!" << endl;
					}
					else//odpowied� inna ni� oczekiwane
					{
						cout << " Nie ma takiej odpowiedzi, spr�buj ponownie!" << endl;
						zamiana = 5;//powt�rzenie p�tli
					}
					kolaRatunkowe--;
				}
				
			}
			else //nie ma k� ratunkowych
			{
				cout << "Nie masz ju� k� ratunkowych!" << endl;
				Sleep(1000);
				system("cls");
				goto pytanie;
			}
		}
		else if (odpowiedz == 'l' || odpowiedz == 'L')//ko�o ratunkowe "Zmiana pytania"
		{
			if (kolaRatunkowe > 0)//czy u�ytkownik ma ko�a ratunkowe
			{
				powtorzonePytanie = losPytanie;//zapami�tanie pytania kt�re ju� by�o
				kolaRatunkowe--;//zmniejszenie k� ratunkowych
				system("cls");
				while (losPytanie == powtorzonePytanie)//wylosowanie innego pytania 
					losPytanie = pyt(generator);
				goto start;//funkcja zaczyna si� od nowa, losuj�c inne pytanie
			}
			else//u�ytykownik nie ma k� ratunkowych
			{
				cout << "Nie masz ju� k� ratunkowych!";
				Sleep(2000);
				system("cls");
				goto pytanie;//powr�t do pytania
			}
		}
		else
			zamiana = 5;// p�tla wykona si� od nowa

		if (zamiana == prawidlowa)//czy przekonwertowana odpowied� zgadza si� z odp prawid�ow�
		{
			cout << endl << "Dobra odpowied�!" << endl << endl;
			zwyciestwa++;
		}
		else if (zamiana == 5)
			cout << "Nie ma takiej odpowiedzi! Spr�buj ponownie" << endl;
		else//powiadomienie o z�ej odpowiedzi i wy�witlenie poprawnej
		{
			cout <<endl<< "Z�a odpowied�!" << endl << endl;
			cout << "Poprawna odpowied�: "<< pr[losPytanie] << endl;
			porazki++;
			Sleep(1000);
		}
		Sleep(2000);
		system("cls");
	} while (zamiana == 5);// warunek powtarzania p�tli
	powtorzonePytanie = 30;//ustawienie warto�ci z powrotem, by wszystkie 10 pyta� w nast�pnej funkcji mog�o by� wylosowane 
}
void pyt2()
{
	int losPytanie;
	losPytanie = pyt(generator);
	start:
	string Pytanie[10]{ "W kt�rym roku rozpocz�a si� I wojna �wiatowa?","Pierwszym cz�owiekiem na Ksi�ycu by�:","Pi�ta planeta od S�o�ca to:","Nazwa naszej galaktyki to:","Drzewem li�ciastym nie jest:","Kontynent�w jest: ","Kt�re pa�stwo nie ma dost�pu do morza?","Napoleon pochodzi� z:","Egipski b�g umar�ych Anubis mia� g�ow�:","Brylant to oszlifowany:" };
	int prawidlowa = odp(generator);
	int licznik = 0, fifty_fifty;
	int zamiana, bylo[4]{ 5,5,5,5 };
	char abcd[4]{ 'a','b','c','d' };
	string pr[10]{ "1914",  "Neil Armstrong",  "Jowisz",  "Droga Mleczna",  "Modrzew",  "7",  "Czechy",  "Francji",  "Szakala",  "Diament", };
	string f1[10]{ "1918","Buzz Aldrin","Ziemia", "Andromeda", "Klon", "5", "Polska", "W�och", "Kota", "Rubin", };
	string f2[10]{ "1939","Michael Collins","Mars", "S�oneczna", "Brzoza", "8", "Rosja", "Rosji", "Sepa", "Szmaragd", };
	string f3[10]{ "1908","John F. Kennedy","Pluton", "Czarna Dziura", "Jab�o�", "6", "W�ochy", "Hiszpanii", "Krokodyla", "Topaz", };
	string f4[10]{ "1932","George Gallup","Neptun", "Droga Kakaowa", "Orzech", "9", "Hiszpania", "Wielkiej Brytanii", "Sowy", "Szafir", };
	string tab[4]{};
	while (licznik < 4)
	{
		int los = odp(generator);
		if (los == 0 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f1[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}
		else if (los == 1 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f2[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}
		else if (los == 2 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f3[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}
		else if (los == 3 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f4[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}

	}
	tab[prawidlowa] = pr[losPytanie];
	do {
		pytanie:
		cout << "Zdobyta suma pieni�dzy: 500z�" << endl << endl;
		cout << endl << "Ko�a ratunkowe: " << kolaRatunkowe << endl << endl << "Pytanie 2: " << Pytanie[losPytanie] << endl;
		

		for (int i = 0; i < 4; i++)
		{
			cout << abcd[i] << ") ";
			cout << tab[i] << endl;
		}
		if (kolaRatunkowe != 0)
		{
			cout << endl << "Wybierz 'k', aby u�y� ko�a ratunkowego 50/50. Nie b�dziesz m�g� potem u�y� ko�a 'Zmiana pytania'." << endl;
			cout << "Wybierz 'l', aby u�y� ko�a ratunkowego 'Zmiana pytania'. Mo�esz go u�y� wielokrotnie i u�y� ko�a 50/50" << endl;
		}
		cout << endl << "Podaj odpowied�: ";
		char odpowiedz;
		cin >> odpowiedz;

		if (odpowiedz == 'a' || odpowiedz == 'A')
			zamiana = 0;
		else if (odpowiedz == 'b' || odpowiedz == 'B')
			zamiana = 1;
		else if (odpowiedz == 'c' || odpowiedz == 'C')
			zamiana = 2;
		else if (odpowiedz == 'd' || odpowiedz == 'D')
			zamiana = 3;
		else if (odpowiedz == 'k' || odpowiedz == 'K')
		{
			if (kolaRatunkowe != 0)
			{
				int rng = prawidlowa;
				while (rng == prawidlowa||( rng!=bylo[0] && rng != bylo[1] && rng != bylo[2] && rng != bylo[3]))
					rng = odp(generator);


				fifty_fifty = fifty(generator);
				zamiana = 5;
				while (zamiana == 5)
				{
					Sleep(1000);
					system("cls");
					cout << "Zdobyta suma pieni�dzy: 500z�" << endl << endl;
					cout << "Pytanie 2: " << Pytanie[losPytanie] << endl;
					if (fifty_fifty == 0)
					{
						cout << "a) " << pr[losPytanie] << endl;
						cout << "b) " << tab[rng] << endl;
						prawidlowa = 0;
					}
					else if (fifty_fifty == 1)
					{
						cout << "a) " << tab[rng] << endl;
						cout << "b) " << pr[losPytanie] << endl;
						prawidlowa = 1;
					}
					cout << endl << "Podaj odpowied�: ";
					cin >> odpowiedz;

					if (odpowiedz == 'a' || odpowiedz == 'A')
						zamiana = 0;
					else if (odpowiedz == 'b' || odpowiedz == 'B')
						zamiana = 1;
					else if (odpowiedz == 'k' || odpowiedz == 'K')
					{
						zamiana = 5;
						cout << " Ju� u�y�e� ko�a ratunkowego, spr�buj ponownie!" << endl;
					}
					else
					{
						cout << " Nie ma takiej odpowiedzi, spr�buj ponownie!" << endl;
						zamiana = 5;
					}
					kolaRatunkowe--;
				}

			}
			else
			{
				cout << "Nie masz ju� k� ratunkowych!" << endl;
				Sleep(1000);
				system("cls");
				goto pytanie;
			}
		}
		else if (odpowiedz == 'l' || odpowiedz == 'L')
		{
			if (kolaRatunkowe > 0)
			{
				powtorzonePytanie = losPytanie;
				while (losPytanie == powtorzonePytanie)
					losPytanie = pyt(generator);
				kolaRatunkowe--;
				system("cls");
				goto start;
			}
			else
			{
				cout << "Nie masz ju� k� ratunkowych!";
				Sleep(2000);
				system("cls");
				goto pytanie;
			}
		}
		else
			zamiana = 5;

		if (zamiana == prawidlowa)
		{
			cout << endl << "Dobra odpowied�!" << endl << endl;
			zwyciestwa++;
		}
		else if (zamiana == 5)
			cout << "Nie ma takiej odpowiedzi! Spr�buj ponownie" << endl;
		else
		{
			cout << endl << "Z�a odpowied�!" << endl << endl;
			cout << "Poprawna odpowied�: " << pr[losPytanie] << endl;
			porazki++;
			Sleep(1000);
		}
		Sleep(2000);
		system("cls");
	} while (zamiana == 5);
	powtorzonePytanie = 30;
}
void pyt3()
{
	int losPytanie;
	losPytanie = pyt(generator);
	start:
	string Pytanie[10]{ "Do ilu m�rz ma dost�p Finlandia?","Jak nazywa si� chorobliwy l�k przed ogniem?","Jak nazywa si� urz�dnik stoj�cy na czele powiatu?","Kiedy zaton�� Titanic?","Kt�rego utworu nie napisa� Szekspir?","W kt�rym roku Krzysztof Kolumb odkry� Ameryke?","Czyja wyprawa jako pierwsza op�yn�a glob?","Wynalazc� druku jest: ","Ile st�p ma metr?","Jak ma na imi� g��wny bohater serii ksi��ek o wied�minie Andrzeja Sapkowskiego?" };
	int prawidlowa = odp(generator);
	int licznik = 0, fifty_fifty;
	int los, zamiana, bylo[4]{ 5,5,5,5 };
	char abcd[4]{ 'a','b','c','d' };
	string pr[10]{ "Jednego",  "Pirofobia",  "Starosta",  "W pierwszej po�owie XX wieku",  "Zemsta",  "1492",  "Ferdynanda Magellana",  "Jan Gutenberg",  "Oko�o 3",  "Geralt", };
	string f1[10]{ "Dw�ch","Arachnofobia","So�tys", "W drugiej po�owie XVIII wieku", "Hamlet", "1410", "Krzysztofa Kolumba", "Marcin Luter", "Oko�o 4", "Gerard", };
	string f2[10]{ "Trzech","Aerofobia","W�jt", "W pierwszej po�owie XIX wieku", "Romeo i Julia", "1502", "Marco Polo", "Leonardo da Vinci", "Oko�o 2", "Gerart", };
	string f3[10]{ "Czterech","Duxofobia","Burmistrz", "W drugiej po�owie XIX wieku", "Makbet", "1452", "Vasco Da Gama", "Galileusz", "Oko�o 6", "Gelart", };
	string f4[10]{ "�adnego","Agorafobia","Prezydent", "W drugiej po�owie XX wieku", "Sen nocy letniej", "1499", "James Cook", "Jan Kalwin", "Oko�o 5", "Gelard", };
	string tab[4]{};
	while (licznik < 4)
	{
		los = odp(generator);
		if (los == 0 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f1[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}
		else if (los == 1 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f2[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}
		else if (los == 2 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f3[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}
		else if (los == 3 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f4[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}

	}
	tab[prawidlowa] = pr[losPytanie];
	do {
		pytanie:
		cout << "Zdobyta suma pieni�dzy: 1000z�. Kwota gwarantowana: 1000z�" << endl << endl;
		cout << endl << "Ko�a ratunkowe: " << kolaRatunkowe << endl << endl << "Pytanie 3: " << Pytanie[losPytanie] <<endl;
		

		for (int i = 0; i < 4; i++)
		{
			cout << abcd[i] << ") ";
			cout << tab[i] << endl;
		}
		if (kolaRatunkowe != 0)
		{
			cout << endl << "Wybierz 'k', aby u�y� ko�a ratunkowego 50/50. Nie b�dziesz m�g� potem u�y� ko�a 'Zmiana pytania'." << endl;
			cout << "Wybierz 'l', aby u�y� ko�a ratunkowego 'Zmiana pytania'. Mo�esz go u�y� wielokrotnie i u�y� ko�a 50/50" << endl;
		}
		cout << endl << "Podaj odpowied�: ";
		char odpowiedz;
		cin >> odpowiedz;

		if (odpowiedz == 'a' || odpowiedz == 'A')
			zamiana = 0;
		else if (odpowiedz == 'b' || odpowiedz == 'B')
			zamiana = 1;
		else if (odpowiedz == 'c' || odpowiedz == 'C')
			zamiana = 2;
		else if (odpowiedz == 'd' || odpowiedz == 'D')
			zamiana = 3;
		else if (odpowiedz == 'k' || odpowiedz == 'K')
		{
			if (kolaRatunkowe != 0)
			{
				int rng = prawidlowa;
				while (rng == prawidlowa||( rng!=bylo[0] && rng != bylo[1] && rng != bylo[2] && rng != bylo[3]))
					rng = odp(generator);


				fifty_fifty = fifty(generator);
				zamiana = 5;
				while (zamiana == 5)
				{
					Sleep(1000);
					system("cls");
					cout << "Zdobyta suma pieni�dzy: 1000z�. Kwota gwarantowana: 1000z�" << endl << endl;
					cout << "Pytanie 3: " << Pytanie[losPytanie] << endl;
					if (fifty_fifty == 0)
					{
						cout << "a) " << pr[losPytanie] << endl;
						cout << "b) " << tab[rng] << endl;
						prawidlowa = 0;
					}
					else if (fifty_fifty == 1)
					{
						cout << "a) " << tab[rng] << endl;
						cout << "b) " << pr[losPytanie] << endl;
						prawidlowa = 1;
					}
					cout << endl << "Podaj odpowied�: ";
					cin >> odpowiedz;

					if (odpowiedz == 'a' || odpowiedz == 'A')
						zamiana = 0;
					else if (odpowiedz == 'b' || odpowiedz == 'B')
						zamiana = 1;
					else if (odpowiedz == 'k' || odpowiedz == 'K')
					{
						zamiana = 5;
						cout << " Ju� u�y�e� ko�a ratunkowego, spr�buj ponownie!" << endl;
					}
					else
					{
						cout << " Nie ma takiej odpowiedzi, spr�buj ponownie!" << endl;
						zamiana = 5;
					}
					kolaRatunkowe--;
				}

			}
			else
			{
				cout << "Nie masz ju� k� ratunkowych!" << endl;
				Sleep(1000);
				system("cls");
				goto pytanie;
			}
		}
		else if (odpowiedz == 'l' || odpowiedz == 'L')
		{
			if (kolaRatunkowe > 0)
			{
				powtorzonePytanie = losPytanie;
				while (losPytanie == powtorzonePytanie)
					losPytanie = pyt(generator);
				kolaRatunkowe--;
				system("cls");
				goto start;
			}
			else
			{
				cout << "Nie masz ju� k� ratunkowych!";
				Sleep(2000);
				system("cls");
				goto pytanie;
			}
		}
		else
			zamiana = 5;

		if (zamiana == prawidlowa)
		{
			cout << endl << "Dobra odpowied�!" << endl << endl;
			zwyciestwa++;
		}
		else if (zamiana == 5)
			cout << "Nie ma takiej odpowiedzi! Spr�buj ponownie" << endl;
		else
		{
			cout << endl << "Z�a odpowied�!" << endl << endl;
			cout << "Poprawna odpowied�: " << pr[losPytanie] << endl;
			porazki++;
			Sleep(1000);
		}
		Sleep(2000);
		system("cls");
	} while (zamiana == 5);
	powtorzonePytanie = 30;
}
void pyt4()
{
	int losPytanie;
	losPytanie = pyt(generator);
start:
	string Pytanie[10]{ "Symbolem Szkocji jest:","Jak Harry Potter nazwa� swoj� sow�?","Gdzie znajduje sie Stonehenge","Kto jest tworc� postaci Pana Kleksa?","Ile k� ma rydwan","W kt�rym wojew�dztwie le�y Ko�obrzeg?","Wellington jest stolic� kt�rego pa�stwa?","Drugim najwy�szym szczytem na Ziemii jest: ","Jak nazywa si� najbardziej zasolone jezioro na Ziemii?","Ile w Biblii by�o plag egipskich? " };
	int prawidlowa = odp(generator);
	int licznik = 0, fifty_fifty;
	int los, zamiana, bylo[4]{ 5,5,5,5 };
	char abcd[4]{ 'a','b','c','d' };
	string pr[10]{ "Koniczyna",  "Hedwiga",  "W Wielkiej Brytanii",  "Jan Brzechwa",  "Dwa",  "W zachodniopomorskim",  "Nowej Zelandii",  "K2",  "Morze Martwe",  "10", };
	string f1[10]{ "Mlecz","Hagrida","W Irlandii", "Julian Tuwim ", "Cztery", "W mazowieckim", "Irlandii", "Mount Everest", "Jezioro Aralskie", "13", };
	string f2[10]{ "R�a","Hermiona","We Francji", "Henryk Sienkiewicz", "Pi��", "W malopolskim", "Islandii", "Mont Blanc", "Jezioro Bode�skie", "7", };
	string f3[10]{ "Oset","Przepi�rka","W Islandii", "Maria Konopnicka", "Sze��", "W lubelskim", "Albanii", "G�ra Ko�ciuszki", "Morze Kaspijskie", "8", };
	string f4[10]{ "Pokrzywa","W�ochatka","W Australii", "Adam Mickiewicz", "Trzy", "W kujawsko-pomorskim", "Australii", "Kilimand�aro", "Jezioro �ywieckie", "5", };
	string tab[4]{};
	while (licznik < 4)
	{
		los = odp(generator);
		if (los == 0 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f1[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}
		else if (los == 1 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f2[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}
		else if (los == 2 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f3[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}
		else if (los == 3 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f4[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}

	}
	tab[prawidlowa] = pr[losPytanie];
	do {
		pytanie:
		cout << "Zdobyta suma pieni�dzy: 2000z�. Kwota gwarantowana: 1000z�" << endl << endl;
		cout << endl << "Ko�a ratunkowe: " << kolaRatunkowe << endl << endl << "Pytanie 4: " << Pytanie[losPytanie] << endl;
		
		for (int i = 0; i < 4; i++)
		{
			cout << abcd[i] << ") ";
			cout << tab[i] << endl;
		}
		if (kolaRatunkowe != 0)
		{
			cout << endl << "Wybierz 'k', aby u�y� ko�a ratunkowego 50/50. Nie b�dziesz m�g� potem u�y� ko�a 'Zmiana pytania'." << endl;
			cout << "Wybierz 'l', aby u�y� ko�a ratunkowego 'Zmiana pytania'. Mo�esz go u�y� wielokrotnie i u�y� ko�a 50/50" << endl;
		}
		cout << endl << "Podaj odpowied�: ";
		char odpowiedz;
		cin >> odpowiedz;

		if (odpowiedz == 'a' || odpowiedz == 'A')
			zamiana = 0;
		else if (odpowiedz == 'b' || odpowiedz == 'B')
			zamiana = 1;
		else if (odpowiedz == 'c' || odpowiedz == 'C')
			zamiana = 2;
		else if (odpowiedz == 'd' || odpowiedz == 'D')
			zamiana = 3;
		else if (odpowiedz == 'k' || odpowiedz == 'K')
		{
			if (kolaRatunkowe != 0)
			{
				int rng = prawidlowa;
				while (rng == prawidlowa||( rng!=bylo[0] && rng != bylo[1] && rng != bylo[2] && rng != bylo[3]))
					rng = odp(generator);


				fifty_fifty = fifty(generator);
				zamiana = 5;
				while (zamiana == 5)
				{
					Sleep(1000);
					system("cls");
					cout << "Zdobyta suma pieni�dzy: 2000z�. Kwota gwarantowana: 1000z�" << endl << endl;
					cout << "Pytanie 4: " << Pytanie[losPytanie]  << endl;
					if (fifty_fifty == 0)
					{
						cout << "a) " << pr[losPytanie] << endl;
						cout << "b) " << tab[rng] << endl;
						prawidlowa = 0;
					}
					else if (fifty_fifty == 1)
					{
						cout << "a) " << tab[rng] << endl;
						cout << "b) " << pr[losPytanie] << endl;
						prawidlowa = 1;
					}
					cout << endl << "Podaj odpowied�: ";
					cin >> odpowiedz;

					if (odpowiedz == 'a' || odpowiedz == 'A')
						zamiana = 0;
					else if (odpowiedz == 'b' || odpowiedz == 'B')
						zamiana = 1;
					else if (odpowiedz == 'k' || odpowiedz == 'K')
					{
						zamiana = 5;
						cout << " Ju� u�y�es ko�a ratunkowego, spr�buj ponownie!" << endl;
					}
					else
					{
						cout << " Nie ma takiej odpowiedzi, spr�buj ponownie!" << endl;
						zamiana = 5;
					}
					kolaRatunkowe--;
				}

			}
			else
			{
				cout << "Nie masz ju� k� ratunkowych!" << endl;
				Sleep(1000);
				system("cls");
				goto pytanie;
			}
		}
		else if (odpowiedz == 'l' || odpowiedz == 'L')
		{
			if (kolaRatunkowe > 0)
			{
				powtorzonePytanie = losPytanie;
				while (losPytanie == powtorzonePytanie)
					losPytanie = pyt(generator);
				kolaRatunkowe--;
				system("cls");
				goto start;
			}
			else
			{
				cout << "Nie masz ju� k� ratunkowych!";
				Sleep(2000);
				system("cls");
				goto pytanie;
			}
		}
		else
			zamiana = 5;

		if (zamiana == prawidlowa)
		{
			cout << endl << "Dobra odpowied�!" << endl << endl;
			zwyciestwa++;
		}
		else if (zamiana == 5)
			cout << "Nie ma takiej odpowiedzi! Spr�buj ponownie" << endl;
		else
		{
			cout << endl << "Z�a odpowied�!" << endl << endl;
			cout << "Poprawna odpowied�: " << pr[losPytanie] << endl;
			porazki++;
			Sleep(1000);
		}
		Sleep(2000);
		system("cls");
	} while (zamiana == 5);
	powtorzonePytanie = 30;
	
}
void pyt5()
{
	int losPytanie;
	losPytanie = pyt(generator);
start:
	string Pytanie[10]{ "Stolic� Maroko jest:","Jaka waluta obowi�zuje na W�grzech?","G��wny bohater 'Ferdydurke' W. Gombrowicza nazywa� si�:","Kt�ra z podanych chor�b NIE jest chorob� wirusow�?","Kraj Kwitn�cej Wi�ni to: ","Inkowie �yli w:","Stolic� Lotaryngii jest:","Wojna stuletna toczy�a si� mi�dzy Francj�, a:","Sma�one kulki albo kotleciki z ciecierzycy lub bobu z sezamem to:","Noc Kryszta�owa mia�a miejsce w/we:" };
	int prawidlowa = odp(generator);
	int licznik = 0, fifty_fifty;
	int los, zamiana, bylo[4]{ 5,5,5,5 };
	char abcd[4]{ 'a','b','c','d' };
	string pr[10]{ "Rabat",  "Forint",  "J�zio Kowalski",  "Angina",  "Japonia",  "Ameryce Po�udniowej",  "Metz",  "Angli�",  "Falafel",  "Niemczech", };
	string f1[10]{ "Ankara","Korona W�gierska","Jan Kowalski", "Ospa wietrzna", "Chiny", "Ameryce P�nocnej", "Cannes", "Hiszpani�", "Kebab", "W�oszech", };
	string f2[10]{ "Burkina Faso","Marka W�gierska","Sta� Tarkowski", "Grypa", "Singapur", "Afryce", "Reims", "Polsk�", "Kuskus", "Francji", };
	string f3[10]{ "Kair","Euro","Olaf Pimka", "�winka", "Korea Po�udniowa", "Europie", "Nicea", "Niemcami", "Tabbouleh", "Czechach", };
	string f4[10]{ "Maroko","Kuna","Ryszard Mi�", "R�yczka", "Nepal", "Australii", "Nancy", "Portugali�", "Kotlet mielony", "Wielkiej Brytanii", };
	string tab[4]{};
	while (licznik < 4)
	{
		los = odp(generator);
		if (los == 0 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f1[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}
		else if (los == 1 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f2[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}
		else if (los == 2 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f3[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}
		else if (los == 3 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f4[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}

	}
	tab[prawidlowa] = pr[losPytanie];
	do {
		pytanie:
		cout << "Zdobyta suma pieni�dzy: 5000z�. Kwota gwarantowana: 1000z�" << endl << endl;
		cout << endl << "Ko�a ratunkowe: " << kolaRatunkowe << endl << endl << "Pytanie 5: " << Pytanie[losPytanie] << endl;
		

		for (int i = 0; i < 4; i++)
		{
			cout << abcd[i] << ") ";
			cout << tab[i] << endl;
		}
		if (kolaRatunkowe != 0)
		{
			cout << endl << "Wybierz 'k', aby u�y� ko�a ratunkowego 50/50. Nie b�dziesz m�g� potem u�y� ko�a 'Zmiana pytania'." << endl;
			cout << "Wybierz 'l', aby u�y� ko�a ratunkowego 'Zmiana pytania'. Mo�esz go u�y� wielokrotnie i u�y� ko�a 50/50" << endl;
		}
		cout << endl << "Podaj odpowied�: ";
		char odpowiedz;
		cin >> odpowiedz;

		if (odpowiedz == 'a' || odpowiedz == 'A')
			zamiana = 0;
		else if (odpowiedz == 'b' || odpowiedz == 'B')
			zamiana = 1;
		else if (odpowiedz == 'c' || odpowiedz == 'C')
			zamiana = 2;
		else if (odpowiedz == 'd' || odpowiedz == 'D')
			zamiana = 3;
		else if (odpowiedz == 'k' || odpowiedz == 'K')
		{
			if (kolaRatunkowe != 0)
			{
				int rng = prawidlowa;
				while (rng == prawidlowa||( rng!=bylo[0] && rng != bylo[1] && rng != bylo[2] && rng != bylo[3]))
					rng = odp(generator);


				fifty_fifty = fifty(generator);
				zamiana = 5;
				while (zamiana == 5)
				{
					Sleep(1000);
					system("cls");
					cout << "Zdobyta suma pieni�dzy: 5000z�. Kwota gwarantowana: 1000z�" << endl << endl;
					cout << "Pytanie 5: " << Pytanie[losPytanie] <<  endl;
					if (fifty_fifty == 0)
					{
						cout << "a) " << pr[losPytanie] << endl;
						cout << "b) " << tab[rng] << endl;
						prawidlowa = 0;
					}
					else if (fifty_fifty == 1)
					{
						cout << "a) " << tab[rng] << endl;
						cout << "b) " << pr[losPytanie] << endl;
						prawidlowa = 1;
					}
					cout << endl << "Podaj odpowied�: ";
					cin >> odpowiedz;

					if (odpowiedz == 'a' || odpowiedz == 'A')
						zamiana = 0;
					else if (odpowiedz == 'b' || odpowiedz == 'B')
						zamiana = 1;
					else if (odpowiedz == 'k' || odpowiedz == 'K')
					{
						zamiana = 5;
						cout << " Ju� u�y�e� ko�a ratunkowego, spr�buj ponownie!" << endl;
					}
					else
					{
						cout << " Nie ma takiej odpowiedzi, spr�buj ponownie!" << endl;
						zamiana = 5;
					}
					kolaRatunkowe--;
				}

			}
			else
			{
				cout << "Nie masz ju� k� ratunkowych!" << endl;
				Sleep(1000);
				system("cls");
				goto pytanie;
			}
		}
		else if (odpowiedz == 'l' || odpowiedz == 'L')
		{
			if (kolaRatunkowe > 0)
			{
				powtorzonePytanie = losPytanie;
				while (losPytanie == powtorzonePytanie)
					losPytanie = pyt(generator);
				kolaRatunkowe--;
				system("cls");
				goto start;
			}
			else
			{
				cout << "Nie masz ju� k� ratunkowych!";
				Sleep(2000);
				system("cls");
				goto pytanie;
			}
		}
		else
			zamiana = 5;

		if (zamiana == prawidlowa)
		{
			cout << endl << "Dobra odpowied�!" << endl << endl;
			zwyciestwa++;
		}
		else if (zamiana == 5)
			cout << "Nie ma takiej odpowiedzi! Spr�buj ponownie" << endl;
		else
		{
			cout << endl << "Z�a odpowied�!" << endl << endl;
			cout << "Poprawna odpowied�: " << pr[losPytanie] << endl;
			porazki++;
			Sleep(1000);
		}
		Sleep(2000);
		system("cls");

	} while (zamiana == 5);
	powtorzonePytanie = 30;
}
void pyt6()
{
	int losPytanie;
	losPytanie = pyt(generator);
start:
	string Pytanie[10]{ "Sk�d pochodzi Connan Barbarzy�ca?","Najwy�sze polskie odznaczenie wojskowe, nadawane za wybitne zas�ugi bojowe, to:","Langusta to:","W kt�rym wojew�dztwie znajduje si� Ojcowski Park Narodowy?","Trafalgar Square to plac znajduj�cy si� w:","Kt�rego utworu symbolem jest czapka z pawim pi�rem?","Kt�ry polski prezydent zgin�� 5 dni po obj�ciu stanowiska?","Co znaczy �aci�skie wyra�enie 'Pecunia non olet'?","Kt�re z poni�szych miast znajduje si� na zachodnim wybrze�u Stan�w Zjednoczonych?","Wojna zimowa to nazwa konfliktu zbrojnego tocz�cego si� od 30 listopada 1939 do 13 marca 1940 pomi�dzy ZSRR a:" };
	int prawidlowa = odp(generator);
	int licznik = 0, fifty_fifty;
	int los, zamiana, bylo[4]{ 5,5,5,5 };
	char abcd[4]{ 'a','b','c','d' };
	string pr[10]{ "Z Cimmerii",  "Order Virtuti Militari",  "Skorupiak morski",  "Ma�opolskim",  "Londynie",  "Wesele",  "Gabriel Narutowicz",  "Pieni�dze nie smierdz�",  "San Francisco",  "Finlandia", };
	string f1[10]{ "Z Rivii","Krzy� Poleg�ych","Ryba", "�l�skim", "Nowym Jorku", "Ogniem i Mieczem", "Ignacy Mo�cicki", "Chwytaj dzie�", "Miami", "Dania", };
	string f2[10]{ "Z Cuzco","Order Odrodzenia Polski","Krzew", "Swi�tokrzyskim", "Doblinie", "Pan Wo�odyjowski", "Ignacy Jan Paderewski", "Polityka nie �mierdzi", "Nowy Jork", "Norwegia", };
	string f3[10]{ "Z Niziny W�gierskiej","Order Krzy�a Wojskowego","Owad", "Podkarpackim", "Sydney", "Ferdydurke", "Maciej Rataj", "Pami�taj o �mierci", "Chicago", "Szwecj�", };
	string f4[10]{ "Z Rzymu","Order Orla Bialego","P�az", "Mazowieckim", "Manchesterze", "Pan Tadeusz", "Boles�aw Bierut", "Nic nowego", "Waszyngton", "Kazachstanem", };
	string tab[4]{};
	while (licznik < 4)
	{
		los = odp(generator);
		if (los == 0 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f1[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}
		else if (los == 1 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f2[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}
		else if (los == 2 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f3[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}
		else if (los == 3 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f4[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}

	}
	tab[prawidlowa] = pr[losPytanie];
	do {
		pytanie:
		cout << "Zdobyta suma pieni�dzy: 10 000z�. Kwota gwarantowana: 1000z�" << endl << endl;
		cout << endl << "Ko�a ratunkowe: " << kolaRatunkowe << endl << endl << "Pytanie 6: " << Pytanie[losPytanie] <<endl;
		

		for (int i = 0; i < 4; i++)
		{
			cout << abcd[i] << ") ";
			cout << tab[i] << endl;
		}
		if (kolaRatunkowe != 0)
		{
			cout << endl << "Wybierz 'k', aby u�y� ko�a ratunkowego 50/50. Nie b�dziesz m�g� potem u�y� ko�a 'Zmiana pytania'." << endl;
			cout << "Wybierz 'l', aby u�y� ko�a ratunkowego 'Zmiana pytania'. Mo�esz go u�y� wielokrotnie i u�y� ko�a 50/50" << endl;
		}
		cout << endl << "Podaj odpowied�: ";
		char odpowiedz;
		cin >> odpowiedz;

		if (odpowiedz == 'a' || odpowiedz == 'A')
			zamiana = 0;
		else if (odpowiedz == 'b' || odpowiedz == 'B')
			zamiana = 1;
		else if (odpowiedz == 'c' || odpowiedz == 'C')
			zamiana = 2;
		else if (odpowiedz == 'd' || odpowiedz == 'D')
			zamiana = 3;
		else if (odpowiedz == 'k' || odpowiedz == 'K')
		{
			if (kolaRatunkowe != 0)
			{
				int rng = prawidlowa;
				while (rng == prawidlowa||( rng!=bylo[0] && rng != bylo[1] && rng != bylo[2] && rng != bylo[3]))
					rng = odp(generator);


				fifty_fifty = fifty(generator);
				zamiana = 5;
				while (zamiana == 5)
				{
					Sleep(1000);
					system("cls");
					cout << "Zdobyta suma pieni�dzy: 10 000z�. Kwota gwarantowana: 1000z�" << endl << endl;
					cout << "Pytanie 6: " << Pytanie[losPytanie] <<endl;
					if (fifty_fifty == 0)
					{
						cout << "a) " << pr[losPytanie] << endl;
						cout << "b) " << tab[rng] << endl;
						prawidlowa = 0;
					}
					else if (fifty_fifty == 1)
					{
						cout << "a) " << tab[rng] << endl;
						cout << "b) " << pr[losPytanie] << endl;
						prawidlowa = 1;
					}
					cout << endl << "Podaj odpowied�: ";
					cin >> odpowiedz;

					if (odpowiedz == 'a' || odpowiedz == 'A')
						zamiana = 0;
					else if (odpowiedz == 'b' || odpowiedz == 'B')
						zamiana = 1;
					else if (odpowiedz == 'k' || odpowiedz == 'K')
					{
						zamiana = 5;
						cout << " Ju� u�y�e� ko�a ratunkowego, spr�buj ponownie!" << endl;
					}
					else
					{
						cout << " Nie ma takiej odpowiedzi, sprobuj ponownie!" << endl;
						zamiana = 5;
					}
					kolaRatunkowe--;
				}

			}
			else
			{
				cout << "Nie masz ju� k� ratunkowych!" << endl;
				Sleep(1000);
				system("cls");
				goto pytanie;
			}
		}
		else if (odpowiedz == 'l' || odpowiedz == 'L')
		{
			if (kolaRatunkowe > 0)
			{
				powtorzonePytanie = losPytanie;
				while (losPytanie == powtorzonePytanie)
					losPytanie = pyt(generator);
				kolaRatunkowe--;
				system("cls");
				goto start;
			}
			else
			{
				cout << "Nie masz ju� k� ratunkowych!";
				Sleep(2000);
				system("cls");
				goto pytanie;
			}
		}
		else
			zamiana = 5;

		if (zamiana == prawidlowa)
		{
			cout << endl << "Dobra odpowied�!" << endl << endl;
			zwyciestwa++;
		}
		else if (zamiana == 5)
			cout << "Nie ma takiej odpowiedzi! Spr�buj ponownie" << endl;
		else
		{
			cout << endl << "Z�a odpowied�!" << endl << endl;
			cout << "Poprawna odpowied�: " << pr[losPytanie] << endl;
			porazki++;
			Sleep(1000);
		}
		Sleep(2000);
		system("cls");
	} while (zamiana == 5);
	powtorzonePytanie = 30;
}
void pyt7()
{
	int losPytanie;
	losPytanie = pyt(generator);
start:
	string Pytanie[10]{ "Z ilu ko�ci sk�ada si� nadgarstek?","Nizina Mand�urska, zajmuj�ca obszar oko�o 350 tys. km, znajduje si� w:","Kt�ry z wymienionych malarzy by� tworc� kubizmu?","Kt�rego z wymienionych pierwiastk�w jest procentowo najwi�cej w bia�kach?","Prawid�owy tytu� dramatu Tennessee Williamsa, to:","W kt�rym pa�stwie znajduje si� najd�u�szy szklany most wisz�cy?","Kt�re z wymienionych pa�stw le�y na P�wyspie Iberyjskim?","Wed�ug Platona, 'Demokracja prowadzi do...':","Panczeny to","Dat� rozbicia dzielnicowego Polski jest rok:" };
	int prawidlowa = odp(generator);
	int licznik = 0, fifty_fifty;
	int los, zamiana, bylo[4]{ 5,5,5,5 };
	char abcd[4]{ 'a','b','c','d' };
	string pr[10]{ "8",  "Chinach",  "Pablo Picasso",  "W�gla",  "Szklana Mena�eria",  "W Chinach",  "Andora",  "Dyktatury",  "�y�wy",  "1138", };
	string f1[10]{ "4","Indiach","Paul Gauguin", "Cynku", "Szklana g�ra", "W Japonii", "Francja", "Dobrobytu", "Bojlery", "1320", };
	string f2[10]{ "10","Mongolii","Leonardo Da Vinci", "Fosforu", "Szklana szkatu�ka", "W Korei Po�udniowej", "W�ochy", "Wojny", "Narty", "1025", };
	string f3[10]{ "5","Rosji","Claude Monet", "Siarki", "Szklana kula", "W Tajlandii", "Niemcy", "Demoralizacji", "Sanki", "1226", };
	string f4[10]{ "7","Kazachstanie","Salvador Dali", "O�owiu", "Szklana bransoleta", "W Korei P��nocnej", "Mauretania", "Tragedii", "Rakiety do �niegu", "1410", };
	string tab[4]{};
	while (licznik < 4)
	{
		los = odp(generator);
		if (los == 0 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f1[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}
		else if (los == 1 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f2[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}
		else if (los == 2 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f3[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}
		else if (los == 3 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f4[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}

	}
	tab[prawidlowa] = pr[losPytanie];
	do {
		pytanie:
		cout << "Zdobyta suma pieni�dzy: 20 000z�. Kwota gwarantowana: 1000z�" << endl << endl;
		cout << endl << "Ko�a ratunkowe: " << kolaRatunkowe << endl << endl << "Pytanie 7: " << Pytanie[losPytanie] <<endl;
		

		for (int i = 0; i < 4; i++)
		{
			cout << abcd[i] << ") ";
			cout << tab[i] << endl;
		}
		if (kolaRatunkowe != 0)
		{
			cout << endl << "Wybierz 'k', aby u�y� ko�a ratunkowego 50/50. Nie b�dziesz m�g� potem u�y� ko�a 'Zmiana pytania'." << endl;
			cout << "Wybierz 'l', aby u�y� ko�a ratunkowego 'Zmiana pytania'. Mo�esz go u�y� wielokrotnie i u�y� ko�a 50/50" << endl;
		}
		cout << endl << "Podaj odpowied�: ";
		char odpowiedz;
		cin >> odpowiedz;

		if (odpowiedz == 'a' || odpowiedz == 'A')
			zamiana = 0;
		else if (odpowiedz == 'b' || odpowiedz == 'B')
			zamiana = 1;
		else if (odpowiedz == 'c' || odpowiedz == 'C')
			zamiana = 2;
		else if (odpowiedz == 'd' || odpowiedz == 'D')
			zamiana = 3;
		else if (odpowiedz == 'k' || odpowiedz == 'K')
		{
			if (kolaRatunkowe != 0)
			{
				int rng = prawidlowa;
				while (rng == prawidlowa||( rng!=bylo[0] && rng != bylo[1] && rng != bylo[2] && rng != bylo[3]))
					rng = odp(generator);


				fifty_fifty = fifty(generator);
				zamiana = 5;
				while (zamiana == 5)
				{
					Sleep(1000);
					system("cls");
					cout << "Zdobyta suma pieni�dzy: 20 000z�. Kwota gwarantowana: 1000z�" << endl << endl;
					cout << "Pytanie 7: " << Pytanie[losPytanie] <<endl;
					if (fifty_fifty == 0)
					{
						cout << "a) " << pr[losPytanie] << endl;
						cout << "b) " << tab[rng] << endl;
						prawidlowa = 0;
					}
					else if (fifty_fifty == 1)
					{
						cout << "a) " << tab[rng] << endl;
						cout << "b) " << pr[losPytanie] << endl;
						prawidlowa = 1;
					}
					cout << endl << "Podaj odpowied�: ";
					cin >> odpowiedz;

					if (odpowiedz == 'a' || odpowiedz == 'A')
						zamiana = 0;
					else if (odpowiedz == 'b' || odpowiedz == 'B')
						zamiana = 1;
					else if (odpowiedz == 'k' || odpowiedz == 'K')
					{
						zamiana = 5;
						cout << " Ju� u�y�e� ko�a ratunkowego, spr�buj ponownie!" << endl;
					}
					else
					{
						cout << " Nie ma takiej odpowiedzi, spr�buj ponownie!" << endl;
						zamiana = 5;
					}
					kolaRatunkowe--;
				}

			}
			else
			{
				cout << "Nie masz ju� k� ratunkowych!" << endl;
				Sleep(1000);
				system("cls");
				goto pytanie;
			}
		}
		else if (odpowiedz == 'l' || odpowiedz == 'L')
		{
			if (kolaRatunkowe > 0)
			{
				powtorzonePytanie = losPytanie;
				while (losPytanie == powtorzonePytanie)
					losPytanie = pyt(generator);
				kolaRatunkowe--;
				system("cls");
				goto start;
			}
			else
			{
				cout << "Nie masz ju� k� ratunkowych!";
				Sleep(2000);
				system("cls");
				goto pytanie;
			}
		}
		else
			zamiana = 5;

		if (zamiana == prawidlowa)
		{
			cout << endl << "Dobra odpowied�!" << endl << endl;
			zwyciestwa++;
		}
		else if (zamiana == 5)
			cout << "Nie ma takiej odpowiedzi! Spr�buj ponownie" << endl;
		else
		{
			cout << endl << "Z�a odpowied�!" << endl << endl;
			cout << "Poprawna odpowied�: " << pr[losPytanie] << endl;
			porazki++;
			Sleep(1000);
		}
		Sleep(2000);
		system("cls");
	} while (zamiana == 5);
	powtorzonePytanie = 30;
}
void pyt8()
{
	int losPytanie;
	losPytanie = pyt(generator);
start:
	string Pytanie[10]{ "Do Unii Europejskiej nie nale�y:","Na kt�rym instrumencie gra� Louis Armstrong?","Bona Sforza by�a �on�:","Kt�ry z wymienionych stan�w USA NIE graniczy z Meksykiem?","Patagonia to kraina geograficzna w:","�mier� kt�rego z wymienionych w�adc�w by�a ko�cem dynastii Jagiellon�w?","Najostrzejsz� z tych papryk jest: ","'Capo di tutti capi' z w�oskiego oznacza:","M�wi�c o Kitaju, Rosjanin ma na my�li:","Homonimem s�owa ranny (o poranku) jest s�owo:" };
	int prawidlowa = odp(generator);
	int licznik = 0, fifty_fifty;
	int los, zamiana, bylo[4]{ 5,5,5,5 };
	char abcd[4]{ 'a','b','c','d' };
	string pr[10]{ "Szwajcaria",  "Tr�bka",  "Zygmunta I Starego",  "Waszyngton",  "Ameryce Po�udniowej",  "Zygmunta Augusta",  "Habanero",  "Szef wszystkich szef�w",  "Chi�czyka",  "Ranny(zraniony)", };
	string f1[10]{ "Hiszpania","Saksofon","Zygmunta II Augusta", "Kalifornia", "Australii", "Zygmunta Starego", "Thai Chili", "Sprawy nasze s� nasze", "Japo�czyka", "Wieczorny", };
	string f2[10]{ "S�owacja","Skrzypce","Jana I Olbrachta", "Arizona", "Europie", "Aleksandra Jagiello�czyka", "Serrano", "Raz kapu�, zawsze kapu�", "Nowozelandczyka", "Poranny", };
	string f3[10]{ "Chorwacja","Puzon","Kazimierza IV Jagiello�czyka", "Teksas", "Azji", "Kazimierza Jagiello�czyka", "Jalapeno", "Historia �wiadkiem dziej�w", "Tajlandczyka", "Rynna", };
	string f4[10]{ "Portugalia","Kornet","Zygmunta III Wazy", "Nowy Meksyk", "Ameryce P�nocnej", "W�adyslaw II Jagie��o", "Poblano", "Prawda zostanie prawd�", "Korea�czyka", "�witowy", };
	string tab[4]{};
	while (licznik < 4)
	{
		los = odp(generator);
		if (los == 0 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f1[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}
		else if (los == 1 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f2[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}
		else if (los == 2 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f3[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}
		else if (los == 3 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f4[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}

	}
	tab[prawidlowa] = pr[losPytanie];
	do {
		pytanie:
		cout << "Zdobyta suma pieni�dzy: 40 000z�. Kwota gwarantowana: 40 000z�" << endl << endl;
		cout << endl << "Ko�a ratunkowe: " << kolaRatunkowe << endl << endl << "Pytanie 8: " << Pytanie[losPytanie] <<endl;
		

		for (int i = 0; i < 4; i++)
		{
			cout << abcd[i] << ") ";
			cout << tab[i] << endl;
		}
		if (kolaRatunkowe != 0)
		{
			cout << endl << "Wybierz 'k', aby u�y� ko�a ratunkowego 50/50. Nie b�dziesz m�g� potem u�y� ko�a 'Zmiana pytania'." << endl;
			cout << "Wybierz 'l', aby u�y� ko�a ratunkowego 'Zmiana pytania'. Mo�esz go u�y� wielokrotnie i u�y� ko�a 50/50" << endl;
		}
		cout << endl << "Podaj odpowied�: ";
		char odpowiedz;
		cin >> odpowiedz;

		if (odpowiedz == 'a' || odpowiedz == 'A')
			zamiana = 0;
		else if (odpowiedz == 'b' || odpowiedz == 'B')
			zamiana = 1;
		else if (odpowiedz == 'c' || odpowiedz == 'C')
			zamiana = 2;
		else if (odpowiedz == 'd' || odpowiedz == 'D')
			zamiana = 3;
		else if (odpowiedz == 'k' || odpowiedz == 'K')
		{
			if (kolaRatunkowe != 0)
			{
				int rng = prawidlowa;
				while (rng == prawidlowa||( rng!=bylo[0] && rng != bylo[1] && rng != bylo[2] && rng != bylo[3]))
					rng = odp(generator);


				fifty_fifty = fifty(generator);
				zamiana = 5;
				while (zamiana == 5)
				{
					Sleep(1000);
					system("cls");
					cout << "Zdobyta suma pieni�dzy: 40 000z�. Kwota gwarantowana: 40 000z�" << endl << endl;
					cout << "Pytanie 8: " << Pytanie[losPytanie]<< endl;
					if (fifty_fifty == 0)
					{
						cout << "a) " << pr[losPytanie] << endl;
						cout << "b) " << tab[rng] << endl;
						prawidlowa = 0;
					}
					else if (fifty_fifty == 1)
					{
						cout << "a) " << tab[rng] << endl;
						cout << "b) " << pr[losPytanie] << endl;
						prawidlowa = 1;
					}
					cout << endl << "Podaj odpowied�: ";
					cin >> odpowiedz;

					if (odpowiedz == 'a' || odpowiedz == 'A')
						zamiana = 0;
					else if (odpowiedz == 'b' || odpowiedz == 'B')
						zamiana = 1;
					else if (odpowiedz == 'k' || odpowiedz == 'K')
					{
						zamiana = 5;
						cout << " Ju� u�y�e� ko�a ratunkowego, spr�buj ponownie!" << endl;
					}
					else
					{
						cout << " Nie ma takiej odpowiedzi, spr�buj ponownie!" << endl;
						zamiana = 5;
					}
					kolaRatunkowe--;
				}

			}
			else
			{
				cout << "Nie masz ju� k� ratunkowych!" << endl;
				Sleep(1000);
				system("cls");
				goto pytanie;
			}
		}
		else if (odpowiedz == 'l' || odpowiedz == 'L')
		{
			if (kolaRatunkowe > 0)
			{
				powtorzonePytanie = losPytanie;
				while (losPytanie == powtorzonePytanie)
					losPytanie = pyt(generator);
				kolaRatunkowe--;
				system("cls");
				goto start;
			}
			else
			{
				cout << "Nie masz ju� k� ratunkowych!";
				Sleep(2000);
				system("cls");
				goto pytanie;
			}
		}
		else
			zamiana = 5;

		if (zamiana == prawidlowa)
		{
			cout << endl << "Dobra odpowied�!" << endl << endl;
			zwyciestwa++;
		}
		else if (zamiana == 5)
			cout << "Nie ma takiej odpowiedzi! Spr�buj ponownie" << endl;
		else
		{
			cout << endl << "Z�a odpowied�!" << endl << endl;
			cout << "Poprawna odpowied�: " << pr[losPytanie] << endl;
			porazki++;
			Sleep(1000);
		}
		Sleep(2000);
		system("cls");
	} while (zamiana == 5);
	powtorzonePytanie = 30;
}
void pyt9()
{
	int losPytanie;
	losPytanie = pyt(generator);
start:
	string Pytanie[10]{ "Ragdoll to rasa/gatunek:","Kt�re Chorwackie miasto nie le�y nad Morzem Adriatyckim?","Komuna Paryska to zryw rewolucyjny ludno�ci Pary�a, przede wszystkim inteligencji i robotnik�w w:","Od st�enia jakiego sk�adnika zale�y kolor sk�ry cz�owieka?","Ile metr�w ma mila?","W kt�rym roku wybuch� 'wielki po�ar Londynu'?","W kt�rym wieku powsta�y najwi�ksze dzie�a Monteskiusza?","Kt�re zdarzenie mia�o miejsce najwcze�niej?","Kiedy przypada swi�to narodowe w Argentynie?","Trasa W-Z w Warszawie zosta�a zbudowana w latach:" };
	int prawidlowa = odp(generator);
	int licznik = 0, fifty_fifty;
	int los, zamiana, bylo[4]{ 5,5,5,5 };
	char abcd[4]{ 'a','b','c','d' };
	string pr[10]{ "Kota",  "Zagrzeb",  "XIX w.",  "Melaniny",  "1609",  "1666",  "XVIII w.",  "�mier� Marilyn Monroe",  "25 maja",  "1947-1949", };
	string f1[10]{ "Psa","Dubrownik","XX w.", "Melatoniny", "1605", "1565", "XVII w.", "Zamach na prezydenta Kennedy'ego", "30 maja", "1945-1947", };
	string f2[10]{ "Kr�lika","Zadar","XVII w.", "Keratyny", "1600", "1536", "I w. p. n. e.", "L�dowanie na Ksi�ycu", "14 maja", "1950-1952", };
	string f3[10]{ "Papugi","Split","XVIII w.", "Prolaktyny", "1608", "1685", "II w. p. n. e.", "Pierwszy koncert The Beatles w Stanach Zjednoczonych", "28 kwietnia", "1955-1957", };
	string f4[10]{ "Chomika","Pula","XXVI w.", "Melanostatyna", "1606", "1657", "III w. p. n. e.", "�mier� Winstona Churchilla", "23 kwietnia", "1957-1959", };
	string tab[4]{};
	while (licznik < 4)
	{
		los = odp(generator);
		if (los == 0 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f1[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}
		else if (los == 1 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f2[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}
		else if (los == 2 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f3[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}
		else if (los == 3 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f4[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}

	}
	tab[prawidlowa] = pr[losPytanie];
	do {
		pytanie:
		cout << "Zdobyta suma pieni�dzy: 75 000z�. Kwota gwarantowana: 40 000z�" << endl << endl;
		cout << endl << "Ko�a ratunkowe: " << kolaRatunkowe << endl << endl << "Pytanie 9: "<< Pytanie[losPytanie] << endl;
		

		for (int i = 0; i < 4; i++)
		{
			cout << abcd[i] << ") ";
			cout << tab[i] << endl;
		}
		if (kolaRatunkowe != 0)
		{
			cout << endl << "Wybierz 'k', aby u�y� ko�a ratunkowego 50/50. Nie b�dziesz m�g� potem u�y� ko�a 'Zmiana pytania'." << endl;
			cout << "Wybierz 'l', aby u�y� ko�a ratunkowego 'Zmiana pytania'. Mo�esz go u�y� wielokrotnie i u�y� ko�a 50/50" << endl;
		}
		cout << endl << "Podaj odpowied�: ";
		char odpowiedz;
		cin >> odpowiedz;

		if (odpowiedz == 'a' || odpowiedz == 'A')
			zamiana = 0;
		else if (odpowiedz == 'b' || odpowiedz == 'B')
			zamiana = 1;
		else if (odpowiedz == 'c' || odpowiedz == 'C')
			zamiana = 2;
		else if (odpowiedz == 'd' || odpowiedz == 'D')
			zamiana = 3;
		else if (odpowiedz == 'k' || odpowiedz == 'K')
		{
			if (kolaRatunkowe != 0)
			{
				int rng = prawidlowa;
				while (rng == prawidlowa||( rng!=bylo[0] && rng != bylo[1] && rng != bylo[2] && rng != bylo[3]))
					rng = odp(generator);


				fifty_fifty = fifty(generator);
				zamiana = 5;
				while (zamiana == 5)
				{
					Sleep(1000);
					system("cls");
					cout << "Zdobyta suma pieni�dzy: 75 000z�. Kwota gwarantowana: 40 000z�" << endl << endl;
					cout << "Pytanie 9: " << Pytanie[losPytanie] <<endl;
					if (fifty_fifty == 0)
					{
						cout << "a) " << pr[losPytanie] << endl;
						cout << "b) " << tab[rng] << endl;
						prawidlowa = 0;
					}
					else if (fifty_fifty == 1)
					{
						cout << "a) " << tab[rng] << endl;
						cout << "b) " << pr[losPytanie] << endl;
						prawidlowa = 1;
					}
					cout << endl << "Podaj odpowied�: ";
					cin >> odpowiedz;

					if (odpowiedz == 'a' || odpowiedz == 'A')
						zamiana = 0;
					else if (odpowiedz == 'b' || odpowiedz == 'B')
						zamiana = 1;
					else if (odpowiedz == 'k' || odpowiedz == 'K')
					{
						zamiana = 5;
						cout << " Ju� u�y�e� ko�a ratunkowego, spr�buj ponownie!" << endl;
					}
					else
					{
						cout << " Nie ma takiej odpowiedzi, spr�buj ponownie!" << endl;
						zamiana = 5;
					}
					kolaRatunkowe--;
				}

			}
			else
			{
				cout << "Nie masz ju� k� ratunkowych!" << endl;
				Sleep(1000);
				system("cls");
				goto pytanie;
			}
		}
		else if (odpowiedz == 'l' || odpowiedz == 'L')
		{
			if (kolaRatunkowe > 0)
			{
				powtorzonePytanie = losPytanie;
				while (losPytanie == powtorzonePytanie)
					losPytanie = pyt(generator);
				kolaRatunkowe--;
				system("cls");
				goto start;
			}
			else
			{
				cout << "Nie masz ju� k� ratunkowych!";
				Sleep(2000);
				system("cls");
				goto pytanie;
			}
		}
		else
			zamiana = 5;

		if (zamiana == prawidlowa)
		{
			cout << endl << "Dobra odpowied�!" << endl << endl;
			zwyciestwa++;
		}
		else if (zamiana == 5)
			cout << "Nie ma takiej odpowiedzi! Spr�buj ponownie" << endl;
		else
		{
			cout << endl << "Z�a odpowied�!" << endl << endl;
			cout << "Poprawna odpowied�: " << pr[losPytanie] << endl;
			porazki++;
			Sleep(1000);
		}
		Sleep(2000);
		system("cls");
	} while (zamiana == 5);
	powtorzonePytanie = 30;
}
void pyt10()
{
	int losPytanie;
	losPytanie = pyt(generator);
start:
	string Pytanie[10]{ "Monachomachia to poemat heroikomiczny o wojnie mnich�w autorstwa:","Jaki stan ameryka�ski jako pierwszy zadeklarowa� secesj� z Unii w 1860 roku?","Kt�ry z tych szczyt�w nie znajduje si� w Tatrach?","Co oznacza skr�t RPP?","Kt�ra z tych wysp nie nale�y do Wysp Kanaryjskich?","Jedna z g��wnych ulic warszawskiego �rodmie�cia, przechodz�ca bezpo�rednio w Krakowskie Przedmie�cie, to:","Poprawnym zapisem jest:","'Upi�r w operze' to dzie�o: ","Auguste Rodin to francuski:","Kt�re Afryka�skie pa�stwo jest najludniejsze?" };
	int prawidlowa = odp(generator);
	int licznik = 0, fifty_fifty;
	int los, zamiana, bylo[4]{ 5,5,5,5 };
	char abcd[4]{ 'a','b','c','d' };
	string pr[10]{ "Ignacego Krasickiego",  "Karolina Po�udniowa",  "�nie�nik",  "Rada Polityki Pieni�nej",  "Lesbos",  "Nowy �wiat",  "Znienacka",  "Andrew Lloyda Webbera",  "Rze�biarz",  "Nigeria", };
	string f1[10]{ "Aleksandra Fredry","Nowy Jork","Gerlach", "Rada Polityki Polskiej", "Lanzarote", "Marsza�kowska", "Z nienacka", "Wolfganga Amadeusza Mozarta", "Malarz", "Kenia", };
	string f2[10]{ "Jana Kochanowskiego","Waszyngton","Krywan", "Rada Polityki Pa�stwowej", "Lobos", "Aleje Jerozolimskie", "Znienadzka", "Stanis�awa Moniuszki", "Pisarz", "RPA", };
	string f3[10]{ "Juliana Ursyna Niemcewicza","Dakota P�nocna","Ko�cielec", "Rada Polskiej Przedsi�biorczo�ci", "Teneryfa", "Grojecka", "Z nienadzka", "Fryderyka Chopina", "Kompozytor", "Mozambik", };
	string f4[10]{ "Adama Mickiewicza","Georgia","�omnica", "Rada Pa�stwa Polskiego", "La Palma", "�r�dmiejska", "Z nie nacka", "Ignacego Paderewskiego", "Aktor", "Namibia", };
	string tab[4]{};
	while (licznik < 4)
	{
		los = odp(generator);
		if (los == 0 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f1[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}
		else if (los == 1 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f2[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}
		else if (los == 2 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f3[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}
		else if (los == 3 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f4[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}

	}
	tab[prawidlowa] = pr[losPytanie];
	do {
		pytanie:
		cout << "Zdobyta suma pieni�dzy: 125 000z�. Kwota gwarantowana: 40 000z�" << endl << endl;
		cout << endl << "Ko�a ratunkowe: " << kolaRatunkowe << endl << endl << "Pytanie 10: " << Pytanie[losPytanie] <<endl;
		
		for (int i = 0; i < 4; i++)
		{
			cout << abcd[i] << ") ";
			cout << tab[i] << endl;
		}
		if (kolaRatunkowe != 0)
		{
			cout << endl << "Wybierz 'k', aby u�y� ko�a ratunkowego 50/50. Nie b�dziesz m�g� potem u�y� ko�a 'Zmiana pytania'." << endl;
			cout << "Wybierz 'l', aby u�y� ko�a ratunkowego 'Zmiana pytania'. Mo�esz go u�y� wielokrotnie i u�y� ko�a 50/50" << endl;
		}
		cout << endl << "Podaj odpowied�: ";
		char odpowiedz;
		cin >> odpowiedz;

		if (odpowiedz == 'a' || odpowiedz == 'A')
			zamiana = 0;
		else if (odpowiedz == 'b' || odpowiedz == 'B')
			zamiana = 1;
		else if (odpowiedz == 'c' || odpowiedz == 'C')
			zamiana = 2;
		else if (odpowiedz == 'd' || odpowiedz == 'D')
			zamiana = 3;
		else if (odpowiedz == 'k' || odpowiedz == 'K')
		{
			if (kolaRatunkowe != 0)
			{
				int rng = prawidlowa;
				while (rng == prawidlowa||( rng!=bylo[0] && rng != bylo[1] && rng != bylo[2] && rng != bylo[3]))
					rng = odp(generator);


				fifty_fifty = fifty(generator);
				zamiana = 5;
				while (zamiana == 5)
				{
					Sleep(1000);
					system("cls");
					cout << "Zdobyta suma pieni�dzy: 125 000z�. Kwota gwarantowana: 40 000z�" << endl << endl;
					cout << "Pytanie 10: " << Pytanie[losPytanie] << endl;
					if (fifty_fifty == 0)
					{
						cout << "a) " << pr[losPytanie] << endl;
						cout << "b) " << tab[rng] << endl;
						prawidlowa = 0;
					}
					else if (fifty_fifty == 1)
					{
						cout << "a) " << tab[rng] << endl;
						cout << "b) " << pr[losPytanie] << endl;
						prawidlowa = 1;
					}
					cout << endl << "Podaj odpowied�: ";
					cin >> odpowiedz;

					if (odpowiedz == 'a' || odpowiedz == 'A')
						zamiana = 0;
					else if (odpowiedz == 'b' || odpowiedz == 'B')
						zamiana = 1;
					else if (odpowiedz == 'k' || odpowiedz == 'K')
					{
						zamiana = 5;
						cout << " Ju� u�y�es ko�a ratunkowego, spr�buj ponownie!" << endl;
					}
					else
					{
						cout << " Nie ma takiej odpowiedzi, spr�buj ponownie!" << endl;
						zamiana = 5;
					}
					kolaRatunkowe--;
				}

			}
			else
			{
				cout << "Nie masz ju� k� ratunkowych!" << endl;
				Sleep(1000);
				system("cls");
				goto pytanie;
			}
		}
		else if (odpowiedz == 'l' || odpowiedz == 'L')
		{
			if (kolaRatunkowe > 0)
			{
				powtorzonePytanie = losPytanie;
				while (losPytanie == powtorzonePytanie)
					losPytanie = pyt(generator);
				kolaRatunkowe--;
				system("cls");
				goto start;
			}
			else
			{
				cout << "Nie masz ju� k� ratunkowych!";
				Sleep(2000);
				system("cls");
				goto pytanie;
			}
		}
		else
			zamiana = 5;

		if (zamiana == prawidlowa)
		{
			cout << endl << "Dobra odpowied�!" << endl << endl;
			zwyciestwa++;
		}
		else if (zamiana == 5)
			cout << "Nie ma takiej odpowiedzi! Spr�buj ponownie" << endl;
		else
		{
			cout << endl << "Z�a odpowied�!" << endl << endl;
			cout << "Poprawna odpowied�: " << pr[losPytanie] << endl;
			porazki++;
			Sleep(1000);
		}
		Sleep(2000);
		system("cls");
	} while (zamiana == 5);
	powtorzonePytanie = 30;
}
void pyt11()
{
	int losPytanie;
	losPytanie = pyt(generator);
start:
	string Pytanie[10]{ "W oryginalnej trylogii 'Gwiezdne wojny' 3-CPO ma srebrn�: ","W kt�rej ksi��ce pojawia sie posta� Winstona Smitha?","Kt�ra z tych liczb jest wynikiem dzia�ania '5!'?","Ichtiologia to nauka o:","Grupa instrument�w muzycznych w kt�rych �r�d�em d�wi�ku jest cia�o sta�e maj�ce niezmienn�, naturaln� spr�ysto��, to:","Doko�cz przys�owie 'Deszcze listopadowe...'","W�gierski taniec narodowy, to:","Kto stworzy� fikcyjn� posta� Josefa Szwejka w antywojennej powie�ci �Przygody dobrego wojaka Szwejka�?","Autorem obrazu 'Mleczarka' jest:","Kumys powstaje w wyniku fermentacji mleka:" };
	int prawidlowa = odp(generator);
	int licznik = 0, fifty_fifty;
	int los, zamiana, bylo[4]{ 5,5,5,5 };
	char abcd[4]{ 'a','b','c','d' };
	string pr[10]{ "Praw� nog�",  "Rok 1984",  "120",  "Rybach",  "Idiofony",  "budz� wiatry zimowe",  "Czardasz",  "Jaroslav Hasek",  "Jan Vermeer",  "Ko�skiego", };
	string f1[10]{ "Praw� r�k�","Proces","5", "Pszczo�ach", "Aerofony", "wr� upa�y marcowe", "Trepak", "Karel Capek", "Peter Paul Rubens", "O�lego", };
	string f2[10]{ "G�ow�","Fahrenheit 451","25", "Wulkanach", "Chordofony", "wr� k�opoty drogowe", "Kozak", "Stanis�aw Kostka Neumann", "Rembrandt van Rijn", "Krowiego", };
	string f3[10]{ "Szcz�k�","Solaris","3125", "Lasach", "Membranofony", "�ci�gaj� chmury �niegowe", "Hajduk", "Julius Fucik", "Frans Hals", "Ko�lego", };
	string f4[10]{ "Klatk� piersiow�","Moskva","125", "Morzach i oceanach", "Instrumenty perkusyjne", "wr� �wi�ta bez�niegowe", "Syrba", "Lubomir Benes", "Nicolaes Maes", "Owczego", };
	string tab[4]{};
	while (licznik < 4)
	{
		los = odp(generator);
		if (los == 0 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f1[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}
		else if (los == 1 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f2[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}
		else if (los == 2 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f3[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}
		else if (los == 3 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f4[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}

	}
	tab[prawidlowa] = pr[losPytanie];
	do {
		pytanie:
		cout << "Zdobyta suma pieni�dzy: 250 000z�. Kwota gwarantowana: 40 000z�" << endl << endl;
		cout << endl << "Ko�a ratunkowe: " << kolaRatunkowe << endl << endl << "Pytanie 11: " << Pytanie[losPytanie] <<endl;
		
		for (int i = 0; i < 4; i++)
		{
			cout << abcd[i] << ") ";
			cout << tab[i] << endl;
		}
		if (kolaRatunkowe != 0)
		{
			cout << endl << "Wybierz 'k', aby u�y� ko�a ratunkowego 50/50. Nie b�dziesz m�g� potem u�y� ko�a 'Zmiana pytania'." << endl;
			cout << "Wybierz 'l', aby u�y� ko�a ratunkowego 'Zmiana pytania'. Mo�esz go u�y� wielokrotnie i u�y� ko�a 50/50" << endl;
		}
		cout << endl << "Podaj odpowied�: ";
		char odpowiedz;
		cin >> odpowiedz;

		if (odpowiedz == 'a' || odpowiedz == 'A')
			zamiana = 0;
		else if (odpowiedz == 'b' || odpowiedz == 'B')
			zamiana = 1;
		else if (odpowiedz == 'c' || odpowiedz == 'C')
			zamiana = 2;
		else if (odpowiedz == 'd' || odpowiedz == 'D')
			zamiana = 3;
		else if (odpowiedz == 'k' || odpowiedz == 'K')
		{
			if (kolaRatunkowe != 0)
			{
				int rng = prawidlowa;
				while (rng == prawidlowa||( rng!=bylo[0] && rng != bylo[1] && rng != bylo[2] && rng != bylo[3]))
					rng = odp(generator);


				fifty_fifty = fifty(generator);
				zamiana = 5;
				while (zamiana == 5)
				{
					Sleep(1000);
					system("cls");
					cout << "Zdobyta suma pieni�dzy: 250 000z�. Kwota gwarantowana: 40 000z�" << endl << endl;
					cout << "Pytanie 11: " << Pytanie[losPytanie]<< endl;
					if (fifty_fifty == 0)
					{
						cout << "a) " << pr[losPytanie] << endl;
						cout << "b) " << tab[rng] << endl;
						prawidlowa = 0;
					}
					else if (fifty_fifty == 1)
					{
						cout << "a) " << tab[rng] << endl;
						cout << "b) " << pr[losPytanie] << endl;
						prawidlowa = 1;
					}
					cout << endl << "Podaj odpowied�: ";
					cin >> odpowiedz;

					if (odpowiedz == 'a' || odpowiedz == 'A')
						zamiana = 0;
					else if (odpowiedz == 'b' || odpowiedz == 'B')
						zamiana = 1;
					else if (odpowiedz == 'k' || odpowiedz == 'K')
					{
						zamiana = 5;
						cout << " Ju� u�y�e� ko�a ratunkowego, spr�buj ponownie!" << endl;
					}
					else
					{
						cout << " Nie ma takiej odpowiedzi, spr�buj ponownie!" << endl;
						zamiana = 5;
					}
					kolaRatunkowe--;
				}

			}
			else
			{
				cout << "Nie masz ju� k� ratunkowych!" << endl;
				Sleep(1000);
				system("cls");
				goto pytanie;
			}
		}
		else if (odpowiedz == 'l' || odpowiedz == 'L')
		{
			if (kolaRatunkowe > 0)
			{
				powtorzonePytanie = losPytanie;
				while (losPytanie == powtorzonePytanie)
					losPytanie = pyt(generator);
				kolaRatunkowe--;
				system("cls");
				goto start;
			}
			else
			{
				cout << "Nie masz ju� k� ratunkowych!";
				Sleep(2000);
				system("cls");
				goto pytanie;
			}
		}
		else
			zamiana = 5;

		if (zamiana == prawidlowa)
		{
			cout << endl << "Dobra odpowied�!" << endl << endl;
			zwyciestwa++;
		}
		else if (zamiana == 5)
			cout << "Nie ma takiej odpowiedzi! Spr�buj ponownie" << endl;
		else
		{
			cout << endl << "Z�a odpowied�!" << endl << endl;
			cout << "Poprawna odpowied�: " << pr[losPytanie] << endl;
			porazki++;
			Sleep(1000);
		}
		Sleep(2000);
		system("cls");
	} while (zamiana == 5);
	powtorzonePytanie = 30;
}
void pyt12()
{
	int losPytanie;
	losPytanie = pyt(generator);
start:
	string Pytanie[10]{ "Co na Ksi�ycu zrobi� Alan Shepard?","Ile edycji Mi�dzynarodowego Konkursu Pianistycznego im. Fryderyka Chopina odby�o sie do 2016 r.?","Ile wynosi rekord dni bez snu?","�rednia d�ugo�� jelita cienkiego wynosi:","Jak nazwano najstarsz�, znan� pramatk� cz�owieka?","KMnO4 to wz�r","Kto jest autorem obrazu 'Adele Bloch - Bauer I'?","Grupa funkcyjna -COOH jest charakterystyczna dla:","Ile razy Franklin Roosevelt pe�ni� kadencj� prezydenck�?","Hrabina Natasza Rostowa jest g��wn� bohaterk� powie�ci:" };
	int prawidlowa = odp(generator);
	int licznik = 0, fifty_fifty;
	int los, zamiana, bylo[4]{ 5,5,5,5 };
	char abcd[4]{ 'a','b','c','d' };
	string pr[10]{ "Zagra� w golfa",  "17",  "11",  "5-6 m",  "Lucy",  "Nadmanganianu potasu",  "Gustav Klimt",  "Kwas�w karboksylowych",  "4",  "Wojna i pok�j", };
	string f1[10]{ "Za�piewa�","40","20", "2-3 m", "Bella", "Chlorku potasu", "Edward Munch", "Alkoholi", "1", "Zbrodnia i kara", };
	string f2[10]{ "Zrobi� kilka pajacyk�w","25","4", "10-11 m", "Fiona", "P�ynu Lugola", "Claude Monet", "Estr�w", "2", "Anna Karenina", };
	string f3[10]{ "Zata�czyl","10","9", "7-8 m", "Amy", "Sody oczyszczonej", "Henri Matisse", "Soli", "3", "Eugeniusz Oniegin", };
	string f4[10]{ "Rzuci� frisbee","20","10", "17-18 m", "Holy", "Cieczy nienutonowskiej", "Salvador Dali", "Zasad", "5", "Granica", };
	string tab[4]{};
	while (licznik < 4)
	{
		los = odp(generator);
		if (los == 0 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f1[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}
		else if (los == 1 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f2[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}
		else if (los == 2 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f3[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}
		else if (los == 3 && bylo[0] != los && bylo[1] != los && bylo[2] != los && bylo[3] != los)
		{
			tab[licznik] = f4[losPytanie];
			bylo[licznik] = los;
			licznik++;
		}

	}
	tab[prawidlowa] = pr[losPytanie];
	do {
		pytanie:
		cout << "Zdobyta suma pieni�dzy: 500 000z�. Kwota gwarantowana: 40 000z�" << endl << endl;
		cout << endl << "Ko�a ratunkowe: " << kolaRatunkowe << endl << endl << "Pytanie 12: " << Pytanie[losPytanie] <<endl;
		
		for (int i = 0; i < 4; i++)
		{
			cout << abcd[i] << ") ";
			cout << tab[i] << endl;
		}
		if (kolaRatunkowe != 0)
		{
			cout << endl << "Wybierz 'k', aby u�y� ko�a ratunkowego 50/50. Nie b�dziesz m�g� potem u�y� ko�a 'Zmiana pytania'." << endl;
			cout << "Wybierz 'l', aby u�y� ko�a ratunkowego 'Zmiana pytania'. Mo�esz go u�y� wielokrotnie i u�y� ko�a 50/50" << endl;
		}
		cout << endl << "Podaj odpowied�: ";
		char odpowiedz;
		cin >> odpowiedz;

		if (odpowiedz == 'a' || odpowiedz == 'A')
			zamiana = 0;
		else if (odpowiedz == 'b' || odpowiedz == 'B')
			zamiana = 1;
		else if (odpowiedz == 'c' || odpowiedz == 'C')
			zamiana = 2;
		else if (odpowiedz == 'd' || odpowiedz == 'D')
			zamiana = 3;
		else if (odpowiedz == 'k' || odpowiedz == 'K')
		{
			if (kolaRatunkowe != 0)
			{
				int rng = prawidlowa;
				while (rng == prawidlowa||( rng!=bylo[0] && rng != bylo[1] && rng != bylo[2] && rng != bylo[3]))
					rng = odp(generator);


				fifty_fifty = fifty(generator);
				zamiana = 5;
				while (zamiana == 5)
				{
					Sleep(1000);
					system("cls");
					cout << "Zdobyta suma pieni�dzy: 500 000z�. Kwota gwarantowana: 40 000z�" << endl << endl;
					cout << "Pytanie 12: " << Pytanie[losPytanie]<< endl;
					if (fifty_fifty == 0)
					{
						cout << "a) " << pr[losPytanie] << endl;
						cout << "b) " << tab[rng] << endl;
						prawidlowa = 0;
					}
					else if (fifty_fifty == 1)
					{
						cout << "a) " << tab[rng] << endl;
						cout << "b) " << pr[losPytanie] << endl;
						prawidlowa = 1;
					}
					cout << endl << "Podaj odpowied�: ";
					cin >> odpowiedz;

					if (odpowiedz == 'a' || odpowiedz == 'A')
						zamiana = 0;
					else if (odpowiedz == 'b' || odpowiedz == 'B')
						zamiana = 1;
					else if (odpowiedz == 'k' || odpowiedz == 'K')
					{
						zamiana = 5;
						cout << " Ju� u�y�e� ko�a ratunkowego, spr�buj ponownie!" << endl;
					}
					else
					{
						cout << " Nie ma takiej odpowiedzi, spr�buj ponownie!" << endl;
						zamiana = 5;
					}
					kolaRatunkowe--;
				}

			}
			else
			{
				cout << "Nie masz ju� k� ratunkowych!" << endl;
				Sleep(1000);
				system("cls");
				goto pytanie;
			}
		}
		else if (odpowiedz == 'l' || odpowiedz == 'L')
		{
			if (kolaRatunkowe > 0)
			{
				powtorzonePytanie = losPytanie;
				while (losPytanie == powtorzonePytanie)
					losPytanie = pyt(generator);
				kolaRatunkowe--;
				system("cls");
				goto start;
			}
			else
			{
				cout << "Nie masz ju� k� ratunkowych!";
				Sleep(2000);
				system("cls");
				goto pytanie;
			}
		}
		else
			zamiana = 5;

		if (zamiana == prawidlowa)
		{
			cout << endl << "Dobra odpowied�!" << endl << endl;
			zwyciestwa++;
		}
		else if (zamiana == 5)
			cout << "Nie ma takiej odpowiedzi! Spr�buj ponownie" << endl;
		else
		{
			cout << endl << "Z�a odpowied�!" << endl << endl;
			cout << "Poprawna odpowied�: " << pr[losPytanie] << endl;
			porazki++;
			Sleep(1000);
		}
		Sleep(2000);
		system("cls");
	} while (zamiana == 5);
	powtorzonePytanie = 30;
}
void historia()
{
	Historia.open("Historia.txt", ios::in);
	string pobranie, uzytkownik[1024], zwyciestwo;
	int dlugosc, indeks = 0; int wynik[1024]{};
	if (Historia.is_open())
	{
		Historia.seekg(0, ios::end);
		if (Historia.tellg() == 0) {
			cout << "Historia jest pusta, zagraj, �eby doda� wynik!\n";
		}
		 
		else {Historia.seekg(0, ios::beg);
			while (!Historia.eof())
			{
				getline(Historia, pobranie);
				dlugosc = pobranie.size();// d�ugo�� nazwy u�ytkownika
				if (pobranie[dlugosc - 2] == ' ')//wynik 1-cyfrowy
				{
					zwyciestwo = pobranie.substr(dlugosc - 1);// oddzielenie wyniku i zapisanie do stringa
					wynik[indeks] = stoi(zwyciestwo);//zmienienie stringa na inta i wpisanie do tablicy wynik�w
					uzytkownik[indeks] = pobranie.substr(0, dlugosc - 1);// oddzielenie nazwy u�ytkownika i zapisaniedo tablicy
				}
				else if (pobranie[dlugosc - 3] == ' ')//wynik 2-cyfrowy
				{
					zwyciestwo = pobranie.substr(dlugosc - 2);// to co w poprzednim if, tylko na wyniku 2-cyfrowym
					wynik[indeks] = stoi(zwyciestwo);
					uzytkownik[indeks] = pobranie.substr(0, dlugosc - 2);
				}
				indeks++;
			}}
			


		
		
			
		
	}
	else
		cout << "Nie mo�na otworzy� pliku" << endl;
	Historia.close();
	int numeracja=1;
	int NajdluzszyUzytkownik = 0;// najdlu�sza nazwa u�ytkownika 
	for (int i = 0; i < indeks; i++)
	{
		if (NajdluzszyUzytkownik < uzytkownik[i].size())
			NajdluzszyUzytkownik = uzytkownik[i].size();

	}
	for (int i = indeks-1; i >=0; i--)// wypisanie w takie spos�b, �eby wyniki by�y r�wno
	{
		
		
	if (i > 3)
				cout<< numeracja << ") " << uzytkownik[i] << setw(NajdluzszyUzytkownik + 4 - uzytkownik[i].size()) << wynik[i] << endl;
	else
				cout << numeracja<< ") " << uzytkownik[i] << setw(NajdluzszyUzytkownik+ 3- uzytkownik[i].size()) << wynik[i] << endl;
	numeracja++;
	}
}
void Gra() 
	{
		Historia.open("Historia.txt", ios::out | ios::app);
		system("cls");
		CzyChceGrac = true;
		while (CzyChceGrac)// p�tla wykonuje si� dp�ki u�ytkownik chce kontynuowac gr�
		{
			

			uzytkownik = "";
			while (uzytkownik.size() == 0)
			{
				system("cls");
				cout << "Podaj nazw� u�ytkownika (bez polskich znak�w): ";
				getline(cin, uzytkownik);//pobranie nazwy u�ytkownika
				
			}
			
			
			Sleep(1000);
			system("cls");

			Historia.seekg(0, ios::end);
			if (Historia.tellg() == 0) 
			{
			Historia << uzytkownik;//zapisanie u�ytkownika do pliku
				
			}
			else
			{
				Historia << endl << uzytkownik;//zapisanie u�ytkownika do pliku
			}
			pyt1();
			while (porazki < 2)// p�tla si� wykonuje a� pora�ki nie wynios� 1 wtedy wy�wietla si� komunikat o ko�cu gry
			{
				if (porazki == 0 && zwyciestwa == 1)
					pyt2();
				else if (porazki == 0 && zwyciestwa == 2)
					pyt3();
				else if (porazki == 0 && zwyciestwa == 3)
					pyt4();
				else if (porazki == 0 && zwyciestwa == 4)
					pyt5();
				else if (porazki == 0 && zwyciestwa == 5)
					pyt6();
				else if (porazki == 0 && zwyciestwa == 6)
					pyt7();
				else if (porazki == 0 && zwyciestwa == 7)
					pyt8();
				else if (porazki == 0 && zwyciestwa == 8)
					pyt9();
				else if (porazki == 0 && zwyciestwa == 9)
					pyt10();
				else if (porazki == 0 && zwyciestwa == 10)
					pyt11();
				else if (porazki == 0 && zwyciestwa == 11)
					pyt12();
				else if (porazki == 1)
				{
					cout << "Koniec gry!" << endl;
					if (zwyciestwa == 0 || zwyciestwa == 1)
						cout << "Nic nie wygra�e�!" << endl;
					else if (zwyciestwa < 7)
					{
						cout << "Wygra�e� 1000 z�!" << endl;
					}
					else if (zwyciestwa >= 7)
					{
						cout << "Wygra�e� 40 000 z�!" << endl;
					}
					porazki = 2;
				}
				else if (zwyciestwa == 12)
				{
					cout << "Gratulacje! Wygra�e� milion!" << endl;
					porazki = 2;
				}
			}

			getline(cin, czychcegrac);// pozbycie si� \n w buforze

			while (checGry == 1)// p�tla wykonuje si� tak d�ugo, a� u�ytkownik poda jedn� z oczekiwanych odpowiedzi
			{
				cout << endl << "Czy chcesz zagra� jeszcze raz?" << endl << "Wpisz 'tak' lub 'nie': " << endl;
				getline(cin, czychcegrac);// czy u�ytkonik chce dalej gra�
				if (czychcegrac == "tak" || czychcegrac == "Tak" || czychcegrac == "tAk" || czychcegrac == "taK" || czychcegrac == "TAk" || czychcegrac == "tAK" || czychcegrac == "TAK" || czychcegrac == "TaK")
				{
					checGry++;//CzyChceGrac pozostaje true
				}
				else if (czychcegrac == "nie" || czychcegrac == "Nie" || czychcegrac == "nIe" || czychcegrac == "niE" || czychcegrac == "NIe" || czychcegrac == "nIE" || czychcegrac == "NIE" || czychcegrac == "NiE")
				{
					CzyChceGrac = false;//p�tla gry si� przerywa
					checGry++;

				}
				else
				{
					cout << "Nie rozumiem, spr�buj ponownie: " << endl;
					Sleep(2000);
					system("cls");
				}
			}


			Historia << ":  " << zwyciestwa;//dopisanie wyniku do nazwy u�ytkownika
			checGry = 1;
			porazki = 0;
			zwyciestwa = 0;
			kolaRatunkowe = 3;// ustawienie wszytskiego na warto�� domy�ln�
		}
		Historia.close();
		system("cls");
		cout << endl << "Dzi�kuj� za gr�!" << endl;
		Sleep(2000);
		system("cls");
	}
char Menu()// pobranie decyzji u�ytkownika
{
	
	char decyzja;
	//cout << "Co chcesz zrobi�? \n\nWpisz 1, aby zagra�.\nWpisz 2, aby wy�wietli� histori� gier.\nWpisz 3, aby wy�wietli� zasady.\nWpisz 4, aby wy�wietli� top 10 graczy.\nWpisz 5, aby zako�czy�." << endl;
	decyzja = _getch();
	return decyzja;
	
}
void Zasady()//wy�wietlenie zasad gry
{
	cout << "Zasady s� bardzo proste:" << endl << "1. Jest 12 losowych pyta�, ka�de kolejne jest trudniejsze od poprzedniego" << endl;
	cout << "2. Za ka�d� poprawn� odpowied� otrzymuje si� coraz wi�ksz� kwot�. Jest te� kwota gwarantowana, kt�r� otrzymuje si� po przegranej." << endl;
	cout << "3. Do dyspozycji s� dwa ko�a ratunkowe: 50/50 oraz 'Zamiana pytania'. Pierwsze wy�wietla jedn� odpowied� poprawn� i jedn� fa�szyw�. Drugie losuje inne pytanie" << endl;
	cout << "4. ��cznie k� ratunkowych mo�na u�y� 3 razy, jednak u�ycie 50/50 uniemo�liwia u�ycie go ponownie w tym samym pytaniu lub wylosowanie innego." << endl;
	cout << "5. Zamiany pytania mo�na u�y� wielokrotnie, dop�ki dost�pne s� ko�a ratunkowe" << endl;
}
void top10()
{
	Historia.open("Historia.txt", ios::in);
	string pobranie, uzytkownik[1024], zwyciestwo;
	int dlugosc, indeks = 0; int wynik[1024]{};
	if (Historia.is_open())
	{
		Historia.seekg(0, ios::end);
		if (Historia.tellg() == 0) {
			cout << "Historia jest pusta, zagraj, �eby doda� wynik!\n";
		}

		else
		{
		while (!Historia.eof())
		{
			getline(Historia, pobranie);
			dlugosc = pobranie.size();// d�ugo�� nazwy u�ytkownika
			if(pobranie[dlugosc -2]== ' ')//wynik 1-cyfrowy
			{
				zwyciestwo = pobranie.substr(dlugosc - 1);// oddzielenie wyniku i zapisanie do stringa
				wynik[indeks] = stoi(zwyciestwo);//zmienienie stringa na inta i wpisanie do tablicy wynik�w
				uzytkownik[indeks] = pobranie.substr(0, dlugosc - 1);// oddzielenie nazwy u�ytkownika i zapisaniedo tablicy
			}
			else if (pobranie[dlugosc - 3] == ' ')//wynik 2-cyfrowy
			{
				zwyciestwo = pobranie.substr(dlugosc - 2);// to co w poprzednim if, tylko na wyniku 2-cyfrowym
				wynik[indeks] = stoi(zwyciestwo);
				uzytkownik[indeks] = pobranie.substr(0, dlugosc - 2);
			}
			indeks++;
		}
		}
	}
	else
		cout << "Nie mo�na otworzy� pliku" << endl;
	Historia.close();

	int zamiana;
	string zam;
	bool czyPokolei = false;
	while (czyPokolei == false)//sortowanie u�ytkownik�w i ich wynik�w
	{
		czyPokolei = true;
		for (int i = 0; i <= indeks; i++)
		{
			if (wynik[i] < wynik[i + 1])
			{
				zamiana = wynik[i];
				zam = uzytkownik[i];
				uzytkownik[i] = uzytkownik[i + 1];
				uzytkownik[i + 1] = zam;
				wynik[i] = wynik[i + 1];
				wynik[i + 1] = zamiana;
				czyPokolei = false;
			}
		}
	}
	int NajdluzszyUzytkownik = 0;// najdlu�sza nazwa u�ytkownika 
	for (int i = 0; i < indeks; i++)
	{
		if (NajdluzszyUzytkownik < uzytkownik[i].size())
			NajdluzszyUzytkownik = uzytkownik[i].size();

	}
	for (int i = 0; i < indeks; i++)// wypisanie w takie spos�b, �eby wyniki by�y r�wno
	{
		if (i < 10)// wypisanie tylko 10
		{
			if (i != 9)
				cout << i + 1 << ") " << uzytkownik[i] << setw(NajdluzszyUzytkownik + 2 - uzytkownik[i].size()) << wynik[i] << endl;
			else
				cout << i + 1 << ") " << uzytkownik[i] << setw(NajdluzszyUzytkownik + 1 - uzytkownik[i].size()) << wynik[i] << endl;
		}
	}
}


int main()
{
	cout << endl;
	cout << "��ۻ�����ۻ�ۻ�ۻ������ۻ�����ۻ���ۻ���ۻ������ۻ�����ۻ�������ۻ�ۻ����ۻ�ۻ" << endl;//wielki napis Milionerzy
	cout << "���ۻ����ۺ�ۺ�ۺ������ۺ������ۻ���ۻ��ۺ������ͼ������ۻ������ۺ��ۻ���ɼ�ۺ" << endl;
	cout << "���������ۺ�ۺ�ۺ������ۺ�ۺ���ۺ����ۻ�ۺ����ۻ��������ɼ������ͼ������ɼ��ۺ" << endl;
	cout << "�ۺ���ɼ�ۺ�ۺ�ۺ������ۺ�ۺ���ۺ�ۺ����ۺ����ͼ��������ۻ����ͼ�������ɼ���ͼ" << endl;
	cout << "�ۺ��ͼ��ۺ�ۺ������ۻ�ۺ������ɼ�ۺ����ۺ������ۻ�ۺ���ۺ������ۻ����ۺ����ۻ" << endl;
	cout << "�ͼ������ͼ�ͼ������ͼ�ͼ�����ͼ��ͼ����ͼ������ͼ�ͼ���ͼ������ͼ����ͼ����ͼ" << endl;
	
	setlocale(LC_CTYPE, "Polish");//ustawienie polskiego j�zyka (polskie znaki)

	cout << endl << endl << "Naci�nij dowolny przycisk aby rozpocz��!" << endl;
	char h;
	h=_getch();
	
	system("cls");
	
	bool dziala = true;
	while (dziala) //niesko�czona p�tla, ko�czy j� switch -> case 5
	{
		powr�t:
		cout << "Co chcesz zrobi�? \n\nWpisz 1, aby zagra�.\nWpisz 2, aby wy�wietli� zasady.\nWpisz 3, aby wy�wietli� histori� gier.\nWpisz 4, aby wy�wietli� top 10 graczy.\nWpisz 5, aby zako�czy�." << endl;

	menu:
			decyzja = Menu();//decyzja u�ytkownika
			
			if (decyzja >= 49 && decyzja <= 53)
			{
				switch (decyzja)
				{
				case '1':
					
					Gra();//rozpocz�cie gry
					break;
				case '3':
					
					system("cls");//wypisanie historii gier
					historia();
					cout << "\nNaci�nij ENTER aby wyj��\n";
					while (1)
					{
						if (_getch() == 13)
						{
							system("cls");
							
							goto powr�t;
						}
					}
				case '2':
					
					system("cls");//wy�wietlenie zasad
					Zasady();
					cout << "\nNaci�nij ENTER aby wyj��\n";
					while (1)
					{
						if (_getch() == 13)
						{
							system("cls");
							
							goto powr�t;
						}
					}
				case '4':
					
					system("cls");//wy�wietlenie 10 najlepszych wynik�w
					top10();
					cout << "\nNaci�nij ENTER aby wyj��\n";
					while (1)
					{
						if (_getch() == 13)
						{
							system("cls");
							
							goto powr�t;
						}
					}
				case '5'://zamkni�cie programu
					decyzja = 0;
					exit(0);
				}
			}
			else
				goto menu;
				
			
		
	}

	system("pause");
}
