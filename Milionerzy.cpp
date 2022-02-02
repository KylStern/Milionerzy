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

fstream  Historia;//plik do zapisu użytkowników i ich wynikow
uniform_int_distribution<int> fifty(0, 1);//losowanie kolejności odp prawidłowej i fałszywej w kole 50/50
int zwyciestwa = 0;int porazki = 0;//liczniki, zwycięstwa oznaczają zdobyte punkty, inna wartość porażek niż 0 oznacza przegraną i zakończenie gry
int kolaRatunkowe = 3;//liczba kół ratunkowych
char decyzja;//użyta w Menu, określa co chce zrobić użytkownik
string uzytkownik;//nazwa użytkownika
int checGry = 1;//czy użytkownik chce grać, domyślnie ustawione na 1, inna wartość przerywa pętlę 
string czychcegrac{};//odpowiedź użytkownika na pytanie czy chce dalej grać
bool CzyChceGrac = true;// jeśli true to gra zaczyna się od nowa, jeśli false, to wyświetla się menu

int powtorzonePytanie;// wartość zmienia się w funkcjach odpowiedzialnych za wyświetlanie pytań, upewnienie że to samo pytanie nie 
//wyświetli się po użyciu koła "zmiana pytania"

//komentarze w funkcji pyt1 odnoszą się też do funkcji pyt2, pyt3, ... ,pyt12.

void pyt1()
{
	int losPytanie;//kwestia bezpieczeństwa, ustawienie na początek dużej wartości równej powtorzonePytanie
	losPytanie = pyt(generator);//losowanie numeru pytania (w tym indeksu tablicy pytań i odpowiedzi)
	start:
	string Pytanie[10]{ "Jaki jest symbol chemiczny potasu?","Jaki jest symbol chemiczny Złota?","Autorem 'Potopu', powieści opowiadającej o potopie szwedzkim, jest: ","W mitologii greckiej opiekunką ogniska domowego była bogini:","W mitologii greckiej z głowy Zeusa wyskoczyła: ","W mitologii greckiej bogiem wojny był:","Najdłuzsza polska rzeka to: ","Ile w Polsce jest województw?","Można znać się jak dwa łyse:","Na drzewach nie rosną:" };
	int prawidlowa = odp(generator);//wylosowanie, która odpowiedź fałszywa zostanie zastąpiona
	int licznik = 0;//indeks odpowiedzi
	int fifty_fifty;//dla koła 50/50
	int los;//losowanie kolejności pytań fałszywych
	int zamiana;//podpięcie odpowiedzi użytkownika do inta
	double bylo[4]{ 5,5,5,5 };//tablica sprawdzająca, czy wartość los się powtarza
	char abcd[4]{ 'a','b','c','d' };	// litery od 'a' do 'b', do wyświetlenia przy odpowiedziach
	string pr[10]{ "K",  "Au",  "H. Sienkiewicz",  "Hestia",  "Atena",  "Ares",  "Wisła",  "16",  "Konie",  "Truskawki", };//odpowiedzi prawidłowe
	string f1[10]{ "Na","Zn","J. Kochanowski", "Hera", "Persefona", "Kratos", "Odra", "14", "Psy", "Jabłka", };
	string f2[10]{ "Au","He","A. Mickiewicz", "Atena", "Hera", "Hermes", "Warta", "15", "Koty", "Śliwki", };
	string f3[10]{ "P","In","M. Rej", "Artemida", "Afrodyta", "Zeus", "San", "20", "Barany", "Banany", };
	string f4[10]{ "Pb","Ag","J. Tuwim", "Kora", "Hestia", "Hefajstos", "Bzura", "12", "Wielbłądy", "Gruszki", };// f1-f4 odpowiedzi fałszywe
	string tab[4]{}; //ta tablica będzie wyświetlana
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
	tab[prawidlowa] = pr[losPytanie]; // zastąpienie jednej z fałszywych odpowiedzi prawdziwą
	do {
		pytanie:
		cout << endl<<"Koła ratunkowe: "<< kolaRatunkowe<< endl << endl << "Pytanie 1: " << Pytanie[losPytanie] << endl;
		for (int i = 0; i < 4; i++)// wypisanie odpowiedzi
		{
			cout << abcd[i] << ") ";
			cout << tab[i] << endl;
		}
		if (kolaRatunkowe != 0)
		{
			cout << endl << "Wybierz 'k', aby użyć koła ratunkowego 50/50. Nie będziesz mógł potem użyć koła 'Zmiana pytania'." << endl;
			cout << "Wybierz 'l', aby użyć koła ratunkowego 'Zmiana pytania'. Możesz go użyć wielokrotnie i użyć koła 50/50" << endl;
		}
		cout << endl << "Podaj odpowiedź: ";
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
		else if (odpowiedz == 'k' || odpowiedz == 'K') //koło ratunkowe 50/50
		{
			if (kolaRatunkowe != 0) //sprawdzenie czy koła ratunkowe są dostepne
			{
				int rng = prawidlowa;
				while (rng == prawidlowa||( rng!=bylo[0] && rng != bylo[1] && rng != bylo[2] && rng != bylo[3]))
					rng = odp(generator);//wylosowanie indeksu odpowiedzi fałszywej innego niż indeks odpowiedzi prawdziwej,
				//plus upewnienie się, żeby wcześniej niewyświetlona odpowiedź się nie wyświetliła
				
				
				fifty_fifty = fifty(generator);//losowanie między 0 a 1
				zamiana = 5; //dla pętli poniżej
				while (zamiana==5) //zamiana ustawia się na 5, jeśli nie istnieje odpowiedź pdana przez użytkownika
				{
					Sleep(1000);
					system("cls");
					cout << "Pytanie 1: " << Pytanie[losPytanie] << endl;
					if (fifty_fifty == 0)//ustalanie koljeności odpowiedzi fałszywej i prawdziewj
					{
						cout << "a) " << pr[losPytanie] << endl;
						cout << "b) " << tab[rng] << endl;
						prawidlowa = 0;
					}
					else if (fifty_fifty == 1)//tu też
					{
						cout << "a) " << tab[rng] << endl;
						cout << "b) " << pr[losPytanie] << endl;
						prawidlowa = 1;
					}
						cout << endl << "Podaj odpowiedź: ";
						cin >> odpowiedz;

					if (odpowiedz == 'a' || odpowiedz == 'A')//sprawdzenie odpowiedzi
						zamiana = 0;
					else if (odpowiedz == 'b' || odpowiedz == 'B')
						zamiana = 1;
					else if (odpowiedz == 'k' || odpowiedz == 'K')//zapobiegnięcie ponownemu użyciu 50/50
					{
						zamiana = 5;//powtórzenie pętli
						cout << " Już użyłeś koła ratunkowego, spróbuj ponownie!" << endl;
					}
					else//odpowiedź inna niż oczekiwane
					{
						cout << " Nie ma takiej odpowiedzi, spróbuj ponownie!" << endl;
						zamiana = 5;//powtórzenie pętli
					}
					kolaRatunkowe--;
				}
				
			}
			else //nie ma kół ratunkowych
			{
				cout << "Nie masz już kół ratunkowych!" << endl;
				Sleep(1000);
				system("cls");
				goto pytanie;
			}
		}
		else if (odpowiedz == 'l' || odpowiedz == 'L')//koło ratunkowe "Zmiana pytania"
		{
			if (kolaRatunkowe > 0)//czy użytkownik ma koła ratunkowe
			{
				powtorzonePytanie = losPytanie;//zapamiętanie pytania które już było
				kolaRatunkowe--;//zmniejszenie kół ratunkowych
				system("cls");
				while (losPytanie == powtorzonePytanie)//wylosowanie innego pytania 
					losPytanie = pyt(generator);
				goto start;//funkcja zaczyna się od nowa, losując inne pytanie
			}
			else//użytykownik nie ma kół ratunkowych
			{
				cout << "Nie masz już kół ratunkowych!";
				Sleep(2000);
				system("cls");
				goto pytanie;//powrót do pytania
			}
		}
		else
			zamiana = 5;// pętla wykona się od nowa

		if (zamiana == prawidlowa)//czy przekonwertowana odpowiedź zgadza się z odp prawidłową
		{
			cout << endl << "Dobra odpowiedź!" << endl << endl;
			zwyciestwa++;
		}
		else if (zamiana == 5)
			cout << "Nie ma takiej odpowiedzi! Spróbuj ponownie" << endl;
		else//powiadomienie o złej odpowiedzi i wyświtlenie poprawnej
		{
			cout <<endl<< "Zła odpowiedź!" << endl << endl;
			cout << "Poprawna odpowiedź: "<< pr[losPytanie] << endl;
			porazki++;
			Sleep(1000);
		}
		Sleep(2000);
		system("cls");
	} while (zamiana == 5);// warunek powtarzania pętli
	powtorzonePytanie = 30;//ustawienie wartości z powrotem, by wszystkie 10 pytań w następnej funkcji mogło być wylosowane 
}
void pyt2()
{
	int losPytanie;
	losPytanie = pyt(generator);
	start:
	string Pytanie[10]{ "W którym roku rozpoczęła się I wojna światowa?","Pierwszym człowiekiem na Księżycu był:","Piąta planeta od Słońca to:","Nazwa naszej galaktyki to:","Drzewem liściastym nie jest:","Kontynentów jest: ","Które państwo nie ma dostępu do morza?","Napoleon pochodził z:","Egipski bóg umarłych Anubis miał głowę:","Brylant to oszlifowany:" };
	int prawidlowa = odp(generator);
	int licznik = 0, fifty_fifty;
	int zamiana, bylo[4]{ 5,5,5,5 };
	char abcd[4]{ 'a','b','c','d' };
	string pr[10]{ "1914",  "Neil Armstrong",  "Jowisz",  "Droga Mleczna",  "Modrzew",  "7",  "Czechy",  "Francji",  "Szakala",  "Diament", };
	string f1[10]{ "1918","Buzz Aldrin","Ziemia", "Andromeda", "Klon", "5", "Polska", "Włoch", "Kota", "Rubin", };
	string f2[10]{ "1939","Michael Collins","Mars", "Słoneczna", "Brzoza", "8", "Rosja", "Rosji", "Sepa", "Szmaragd", };
	string f3[10]{ "1908","John F. Kennedy","Pluton", "Czarna Dziura", "Jabłoń", "6", "Włochy", "Hiszpanii", "Krokodyla", "Topaz", };
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
		cout << "Zdobyta suma pieniędzy: 500zł" << endl << endl;
		cout << endl << "Koła ratunkowe: " << kolaRatunkowe << endl << endl << "Pytanie 2: " << Pytanie[losPytanie] << endl;
		

		for (int i = 0; i < 4; i++)
		{
			cout << abcd[i] << ") ";
			cout << tab[i] << endl;
		}
		if (kolaRatunkowe != 0)
		{
			cout << endl << "Wybierz 'k', aby użyć koła ratunkowego 50/50. Nie będziesz mógł potem użyć koła 'Zmiana pytania'." << endl;
			cout << "Wybierz 'l', aby użyć koła ratunkowego 'Zmiana pytania'. Możesz go użyć wielokrotnie i użyć koła 50/50" << endl;
		}
		cout << endl << "Podaj odpowiedź: ";
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
					cout << "Zdobyta suma pieniędzy: 500zł" << endl << endl;
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
					cout << endl << "Podaj odpowiedź: ";
					cin >> odpowiedz;

					if (odpowiedz == 'a' || odpowiedz == 'A')
						zamiana = 0;
					else if (odpowiedz == 'b' || odpowiedz == 'B')
						zamiana = 1;
					else if (odpowiedz == 'k' || odpowiedz == 'K')
					{
						zamiana = 5;
						cout << " Już użyłeś koła ratunkowego, spróbuj ponownie!" << endl;
					}
					else
					{
						cout << " Nie ma takiej odpowiedzi, spróbuj ponownie!" << endl;
						zamiana = 5;
					}
					kolaRatunkowe--;
				}

			}
			else
			{
				cout << "Nie masz już kół ratunkowych!" << endl;
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
				cout << "Nie masz już kół ratunkowych!";
				Sleep(2000);
				system("cls");
				goto pytanie;
			}
		}
		else
			zamiana = 5;

		if (zamiana == prawidlowa)
		{
			cout << endl << "Dobra odpowiedź!" << endl << endl;
			zwyciestwa++;
		}
		else if (zamiana == 5)
			cout << "Nie ma takiej odpowiedzi! Spróbuj ponownie" << endl;
		else
		{
			cout << endl << "Zła odpowiedź!" << endl << endl;
			cout << "Poprawna odpowiedź: " << pr[losPytanie] << endl;
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
	string Pytanie[10]{ "Do ilu mórz ma dostęp Finlandia?","Jak nazywa się chorobliwy lęk przed ogniem?","Jak nazywa się urzędnik stojący na czele powiatu?","Kiedy zatonął Titanic?","Którego utworu nie napisał Szekspir?","W którym roku Krzysztof Kolumb odkrył Ameryke?","Czyja wyprawa jako pierwsza opłynęła glob?","Wynalazcą druku jest: ","Ile stóp ma metr?","Jak ma na imię główny bohater serii książek o wiedźminie Andrzeja Sapkowskiego?" };
	int prawidlowa = odp(generator);
	int licznik = 0, fifty_fifty;
	int los, zamiana, bylo[4]{ 5,5,5,5 };
	char abcd[4]{ 'a','b','c','d' };
	string pr[10]{ "Jednego",  "Pirofobia",  "Starosta",  "W pierwszej połowie XX wieku",  "Zemsta",  "1492",  "Ferdynanda Magellana",  "Jan Gutenberg",  "Około 3",  "Geralt", };
	string f1[10]{ "Dwóch","Arachnofobia","Sołtys", "W drugiej połowie XVIII wieku", "Hamlet", "1410", "Krzysztofa Kolumba", "Marcin Luter", "Około 4", "Gerard", };
	string f2[10]{ "Trzech","Aerofobia","Wójt", "W pierwszej połowie XIX wieku", "Romeo i Julia", "1502", "Marco Polo", "Leonardo da Vinci", "Około 2", "Gerart", };
	string f3[10]{ "Czterech","Duxofobia","Burmistrz", "W drugiej połowie XIX wieku", "Makbet", "1452", "Vasco Da Gama", "Galileusz", "Około 6", "Gelart", };
	string f4[10]{ "Żadnego","Agorafobia","Prezydent", "W drugiej połowie XX wieku", "Sen nocy letniej", "1499", "James Cook", "Jan Kalwin", "Około 5", "Gelard", };
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
		cout << "Zdobyta suma pieniędzy: 1000zł. Kwota gwarantowana: 1000zł" << endl << endl;
		cout << endl << "Koła ratunkowe: " << kolaRatunkowe << endl << endl << "Pytanie 3: " << Pytanie[losPytanie] <<endl;
		

		for (int i = 0; i < 4; i++)
		{
			cout << abcd[i] << ") ";
			cout << tab[i] << endl;
		}
		if (kolaRatunkowe != 0)
		{
			cout << endl << "Wybierz 'k', aby użyć koła ratunkowego 50/50. Nie będziesz mógł potem użyć koła 'Zmiana pytania'." << endl;
			cout << "Wybierz 'l', aby użyć koła ratunkowego 'Zmiana pytania'. Możesz go użyć wielokrotnie i użyć koła 50/50" << endl;
		}
		cout << endl << "Podaj odpowiedź: ";
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
					cout << "Zdobyta suma pieniędzy: 1000zł. Kwota gwarantowana: 1000zł" << endl << endl;
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
					cout << endl << "Podaj odpowiedź: ";
					cin >> odpowiedz;

					if (odpowiedz == 'a' || odpowiedz == 'A')
						zamiana = 0;
					else if (odpowiedz == 'b' || odpowiedz == 'B')
						zamiana = 1;
					else if (odpowiedz == 'k' || odpowiedz == 'K')
					{
						zamiana = 5;
						cout << " Już użyłeś koła ratunkowego, spróbuj ponownie!" << endl;
					}
					else
					{
						cout << " Nie ma takiej odpowiedzi, spróbuj ponownie!" << endl;
						zamiana = 5;
					}
					kolaRatunkowe--;
				}

			}
			else
			{
				cout << "Nie masz już kół ratunkowych!" << endl;
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
				cout << "Nie masz już kół ratunkowych!";
				Sleep(2000);
				system("cls");
				goto pytanie;
			}
		}
		else
			zamiana = 5;

		if (zamiana == prawidlowa)
		{
			cout << endl << "Dobra odpowiedź!" << endl << endl;
			zwyciestwa++;
		}
		else if (zamiana == 5)
			cout << "Nie ma takiej odpowiedzi! Spróbuj ponownie" << endl;
		else
		{
			cout << endl << "Zła odpowiedź!" << endl << endl;
			cout << "Poprawna odpowiedź: " << pr[losPytanie] << endl;
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
	string Pytanie[10]{ "Symbolem Szkocji jest:","Jak Harry Potter nazwał swoją sowę?","Gdzie znajduje sie Stonehenge","Kto jest tworcą postaci Pana Kleksa?","Ile kół ma rydwan","W którym województwie leży Kołobrzeg?","Wellington jest stolicą którego państwa?","Drugim najwyższym szczytem na Ziemii jest: ","Jak nazywa się najbardziej zasolone jezioro na Ziemii?","Ile w Biblii było plag egipskich? " };
	int prawidlowa = odp(generator);
	int licznik = 0, fifty_fifty;
	int los, zamiana, bylo[4]{ 5,5,5,5 };
	char abcd[4]{ 'a','b','c','d' };
	string pr[10]{ "Koniczyna",  "Hedwiga",  "W Wielkiej Brytanii",  "Jan Brzechwa",  "Dwa",  "W zachodniopomorskim",  "Nowej Zelandii",  "K2",  "Morze Martwe",  "10", };
	string f1[10]{ "Mlecz","Hagrida","W Irlandii", "Julian Tuwim ", "Cztery", "W mazowieckim", "Irlandii", "Mount Everest", "Jezioro Aralskie", "13", };
	string f2[10]{ "Róża","Hermiona","We Francji", "Henryk Sienkiewicz", "Pięć", "W malopolskim", "Islandii", "Mont Blanc", "Jezioro Bodeńskie", "7", };
	string f3[10]{ "Oset","Przepiórka","W Islandii", "Maria Konopnicka", "Sześć", "W lubelskim", "Albanii", "Góra Kościuszki", "Morze Kaspijskie", "8", };
	string f4[10]{ "Pokrzywa","Włochatka","W Australii", "Adam Mickiewicz", "Trzy", "W kujawsko-pomorskim", "Australii", "Kilimandżaro", "Jezioro Żywieckie", "5", };
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
		cout << "Zdobyta suma pieniędzy: 2000zł. Kwota gwarantowana: 1000zł" << endl << endl;
		cout << endl << "Koła ratunkowe: " << kolaRatunkowe << endl << endl << "Pytanie 4: " << Pytanie[losPytanie] << endl;
		
		for (int i = 0; i < 4; i++)
		{
			cout << abcd[i] << ") ";
			cout << tab[i] << endl;
		}
		if (kolaRatunkowe != 0)
		{
			cout << endl << "Wybierz 'k', aby użyć koła ratunkowego 50/50. Nie będziesz mógł potem użyć koła 'Zmiana pytania'." << endl;
			cout << "Wybierz 'l', aby użyć koła ratunkowego 'Zmiana pytania'. Możesz go użyć wielokrotnie i użyć koła 50/50" << endl;
		}
		cout << endl << "Podaj odpowiedź: ";
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
					cout << "Zdobyta suma pieniędzy: 2000zł. Kwota gwarantowana: 1000zł" << endl << endl;
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
					cout << endl << "Podaj odpowiedź: ";
					cin >> odpowiedz;

					if (odpowiedz == 'a' || odpowiedz == 'A')
						zamiana = 0;
					else if (odpowiedz == 'b' || odpowiedz == 'B')
						zamiana = 1;
					else if (odpowiedz == 'k' || odpowiedz == 'K')
					{
						zamiana = 5;
						cout << " Już użyłes koła ratunkowego, spróbuj ponownie!" << endl;
					}
					else
					{
						cout << " Nie ma takiej odpowiedzi, spróbuj ponownie!" << endl;
						zamiana = 5;
					}
					kolaRatunkowe--;
				}

			}
			else
			{
				cout << "Nie masz już kół ratunkowych!" << endl;
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
				cout << "Nie masz już kół ratunkowych!";
				Sleep(2000);
				system("cls");
				goto pytanie;
			}
		}
		else
			zamiana = 5;

		if (zamiana == prawidlowa)
		{
			cout << endl << "Dobra odpowiedź!" << endl << endl;
			zwyciestwa++;
		}
		else if (zamiana == 5)
			cout << "Nie ma takiej odpowiedzi! Spróbuj ponownie" << endl;
		else
		{
			cout << endl << "Zła odpowiedź!" << endl << endl;
			cout << "Poprawna odpowiedź: " << pr[losPytanie] << endl;
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
	string Pytanie[10]{ "Stolicą Maroko jest:","Jaka waluta obowiązuje na Węgrzech?","Główny bohater 'Ferdydurke' W. Gombrowicza nazywał się:","Która z podanych chorób NIE jest chorobą wirusową?","Kraj Kwitnącej Wiśni to: ","Inkowie żyli w:","Stolicą Lotaryngii jest:","Wojna stuletna toczyła się między Francją, a:","Smażone kulki albo kotleciki z ciecierzycy lub bobu z sezamem to:","Noc Kryształowa miała miejsce w/we:" };
	int prawidlowa = odp(generator);
	int licznik = 0, fifty_fifty;
	int los, zamiana, bylo[4]{ 5,5,5,5 };
	char abcd[4]{ 'a','b','c','d' };
	string pr[10]{ "Rabat",  "Forint",  "Józio Kowalski",  "Angina",  "Japonia",  "Ameryce Południowej",  "Metz",  "Anglią",  "Falafel",  "Niemczech", };
	string f1[10]{ "Ankara","Korona Węgierska","Jan Kowalski", "Ospa wietrzna", "Chiny", "Ameryce Północnej", "Cannes", "Hiszpanią", "Kebab", "Włoszech", };
	string f2[10]{ "Burkina Faso","Marka Węgierska","Staś Tarkowski", "Grypa", "Singapur", "Afryce", "Reims", "Polską", "Kuskus", "Francji", };
	string f3[10]{ "Kair","Euro","Olaf Pimka", "Świnka", "Korea Południowa", "Europie", "Nicea", "Niemcami", "Tabbouleh", "Czechach", };
	string f4[10]{ "Maroko","Kuna","Ryszard Miś", "Różyczka", "Nepal", "Australii", "Nancy", "Portugalią", "Kotlet mielony", "Wielkiej Brytanii", };
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
		cout << "Zdobyta suma pieniędzy: 5000zł. Kwota gwarantowana: 1000zł" << endl << endl;
		cout << endl << "Koła ratunkowe: " << kolaRatunkowe << endl << endl << "Pytanie 5: " << Pytanie[losPytanie] << endl;
		

		for (int i = 0; i < 4; i++)
		{
			cout << abcd[i] << ") ";
			cout << tab[i] << endl;
		}
		if (kolaRatunkowe != 0)
		{
			cout << endl << "Wybierz 'k', aby użyć koła ratunkowego 50/50. Nie będziesz mógł potem użyć koła 'Zmiana pytania'." << endl;
			cout << "Wybierz 'l', aby użyć koła ratunkowego 'Zmiana pytania'. Możesz go użyć wielokrotnie i użyć koła 50/50" << endl;
		}
		cout << endl << "Podaj odpowiedź: ";
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
					cout << "Zdobyta suma pieniędzy: 5000zł. Kwota gwarantowana: 1000zł" << endl << endl;
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
					cout << endl << "Podaj odpowiedź: ";
					cin >> odpowiedz;

					if (odpowiedz == 'a' || odpowiedz == 'A')
						zamiana = 0;
					else if (odpowiedz == 'b' || odpowiedz == 'B')
						zamiana = 1;
					else if (odpowiedz == 'k' || odpowiedz == 'K')
					{
						zamiana = 5;
						cout << " Już użyłeś koła ratunkowego, spróbuj ponownie!" << endl;
					}
					else
					{
						cout << " Nie ma takiej odpowiedzi, spróbuj ponownie!" << endl;
						zamiana = 5;
					}
					kolaRatunkowe--;
				}

			}
			else
			{
				cout << "Nie masz już kół ratunkowych!" << endl;
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
				cout << "Nie masz już kół ratunkowych!";
				Sleep(2000);
				system("cls");
				goto pytanie;
			}
		}
		else
			zamiana = 5;

		if (zamiana == prawidlowa)
		{
			cout << endl << "Dobra odpowiedź!" << endl << endl;
			zwyciestwa++;
		}
		else if (zamiana == 5)
			cout << "Nie ma takiej odpowiedzi! Spróbuj ponownie" << endl;
		else
		{
			cout << endl << "Zła odpowiedź!" << endl << endl;
			cout << "Poprawna odpowiedź: " << pr[losPytanie] << endl;
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
	string Pytanie[10]{ "Skąd pochodzi Connan Barbarzyńca?","Najwyższe polskie odznaczenie wojskowe, nadawane za wybitne zasługi bojowe, to:","Langusta to:","W którym województwie znajduje się Ojcowski Park Narodowy?","Trafalgar Square to plac znajdujący się w:","Którego utworu symbolem jest czapka z pawim piórem?","Który polski prezydent zginął 5 dni po objęciu stanowiska?","Co znaczy łacińskie wyrażenie 'Pecunia non olet'?","Które z poniższych miast znajduje się na zachodnim wybrzeżu Stanów Zjednoczonych?","Wojna zimowa to nazwa konfliktu zbrojnego toczącego się od 30 listopada 1939 do 13 marca 1940 pomiędzy ZSRR a:" };
	int prawidlowa = odp(generator);
	int licznik = 0, fifty_fifty;
	int los, zamiana, bylo[4]{ 5,5,5,5 };
	char abcd[4]{ 'a','b','c','d' };
	string pr[10]{ "Z Cimmerii",  "Order Virtuti Militari",  "Skorupiak morski",  "Małopolskim",  "Londynie",  "Wesele",  "Gabriel Narutowicz",  "Pieniądze nie smierdzą",  "San Francisco",  "Finlandia", };
	string f1[10]{ "Z Rivii","Krzyż Poległych","Ryba", "Śląskim", "Nowym Jorku", "Ogniem i Mieczem", "Ignacy Mościcki", "Chwytaj dzień", "Miami", "Dania", };
	string f2[10]{ "Z Cuzco","Order Odrodzenia Polski","Krzew", "Swiętokrzyskim", "Doblinie", "Pan Wołodyjowski", "Ignacy Jan Paderewski", "Polityka nie śmierdzi", "Nowy Jork", "Norwegia", };
	string f3[10]{ "Z Niziny Węgierskiej","Order Krzyża Wojskowego","Owad", "Podkarpackim", "Sydney", "Ferdydurke", "Maciej Rataj", "Pamiętaj o śmierci", "Chicago", "Szwecją", };
	string f4[10]{ "Z Rzymu","Order Orla Bialego","Płaz", "Mazowieckim", "Manchesterze", "Pan Tadeusz", "Bolesław Bierut", "Nic nowego", "Waszyngton", "Kazachstanem", };
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
		cout << "Zdobyta suma pieniędzy: 10 000zł. Kwota gwarantowana: 1000zł" << endl << endl;
		cout << endl << "Koła ratunkowe: " << kolaRatunkowe << endl << endl << "Pytanie 6: " << Pytanie[losPytanie] <<endl;
		

		for (int i = 0; i < 4; i++)
		{
			cout << abcd[i] << ") ";
			cout << tab[i] << endl;
		}
		if (kolaRatunkowe != 0)
		{
			cout << endl << "Wybierz 'k', aby użyć koła ratunkowego 50/50. Nie będziesz mógł potem użyć koła 'Zmiana pytania'." << endl;
			cout << "Wybierz 'l', aby użyć koła ratunkowego 'Zmiana pytania'. Możesz go użyć wielokrotnie i użyć koła 50/50" << endl;
		}
		cout << endl << "Podaj odpowiedź: ";
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
					cout << "Zdobyta suma pieniędzy: 10 000zł. Kwota gwarantowana: 1000zł" << endl << endl;
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
					cout << endl << "Podaj odpowiedź: ";
					cin >> odpowiedz;

					if (odpowiedz == 'a' || odpowiedz == 'A')
						zamiana = 0;
					else if (odpowiedz == 'b' || odpowiedz == 'B')
						zamiana = 1;
					else if (odpowiedz == 'k' || odpowiedz == 'K')
					{
						zamiana = 5;
						cout << " Już użyłeś koła ratunkowego, spróbuj ponownie!" << endl;
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
				cout << "Nie masz już kół ratunkowych!" << endl;
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
				cout << "Nie masz już kół ratunkowych!";
				Sleep(2000);
				system("cls");
				goto pytanie;
			}
		}
		else
			zamiana = 5;

		if (zamiana == prawidlowa)
		{
			cout << endl << "Dobra odpowiedź!" << endl << endl;
			zwyciestwa++;
		}
		else if (zamiana == 5)
			cout << "Nie ma takiej odpowiedzi! Spróbuj ponownie" << endl;
		else
		{
			cout << endl << "Zła odpowiedź!" << endl << endl;
			cout << "Poprawna odpowiedź: " << pr[losPytanie] << endl;
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
	string Pytanie[10]{ "Z ilu kości składa się nadgarstek?","Nizina Mandżurska, zajmująca obszar około 350 tys. km, znajduje się w:","Który z wymienionych malarzy był tworcą kubizmu?","Którego z wymienionych pierwiastków jest procentowo najwięcej w białkach?","Prawidłowy tytuł dramatu Tennessee Williamsa, to:","W którym państwie znajduje się najdłuższy szklany most wiszący?","Które z wymienionych państw leży na Półwyspie Iberyjskim?","Według Platona, 'Demokracja prowadzi do...':","Panczeny to","Datą rozbicia dzielnicowego Polski jest rok:" };
	int prawidlowa = odp(generator);
	int licznik = 0, fifty_fifty;
	int los, zamiana, bylo[4]{ 5,5,5,5 };
	char abcd[4]{ 'a','b','c','d' };
	string pr[10]{ "8",  "Chinach",  "Pablo Picasso",  "Węgla",  "Szklana Menażeria",  "W Chinach",  "Andora",  "Dyktatury",  "Łyżwy",  "1138", };
	string f1[10]{ "4","Indiach","Paul Gauguin", "Cynku", "Szklana góra", "W Japonii", "Francja", "Dobrobytu", "Bojlery", "1320", };
	string f2[10]{ "10","Mongolii","Leonardo Da Vinci", "Fosforu", "Szklana szkatułka", "W Korei Południowej", "Włochy", "Wojny", "Narty", "1025", };
	string f3[10]{ "5","Rosji","Claude Monet", "Siarki", "Szklana kula", "W Tajlandii", "Niemcy", "Demoralizacji", "Sanki", "1226", };
	string f4[10]{ "7","Kazachstanie","Salvador Dali", "Ołowiu", "Szklana bransoleta", "W Korei Półónocnej", "Mauretania", "Tragedii", "Rakiety do śniegu", "1410", };
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
		cout << "Zdobyta suma pieniędzy: 20 000zł. Kwota gwarantowana: 1000zł" << endl << endl;
		cout << endl << "Koła ratunkowe: " << kolaRatunkowe << endl << endl << "Pytanie 7: " << Pytanie[losPytanie] <<endl;
		

		for (int i = 0; i < 4; i++)
		{
			cout << abcd[i] << ") ";
			cout << tab[i] << endl;
		}
		if (kolaRatunkowe != 0)
		{
			cout << endl << "Wybierz 'k', aby użyć koła ratunkowego 50/50. Nie będziesz mógł potem użyć koła 'Zmiana pytania'." << endl;
			cout << "Wybierz 'l', aby użyć koła ratunkowego 'Zmiana pytania'. Możesz go użyć wielokrotnie i użyć koła 50/50" << endl;
		}
		cout << endl << "Podaj odpowiedź: ";
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
					cout << "Zdobyta suma pieniędzy: 20 000zł. Kwota gwarantowana: 1000zł" << endl << endl;
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
					cout << endl << "Podaj odpowiedź: ";
					cin >> odpowiedz;

					if (odpowiedz == 'a' || odpowiedz == 'A')
						zamiana = 0;
					else if (odpowiedz == 'b' || odpowiedz == 'B')
						zamiana = 1;
					else if (odpowiedz == 'k' || odpowiedz == 'K')
					{
						zamiana = 5;
						cout << " Już użyłeś koła ratunkowego, spróbuj ponownie!" << endl;
					}
					else
					{
						cout << " Nie ma takiej odpowiedzi, spróbuj ponownie!" << endl;
						zamiana = 5;
					}
					kolaRatunkowe--;
				}

			}
			else
			{
				cout << "Nie masz już kół ratunkowych!" << endl;
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
				cout << "Nie masz już kół ratunkowych!";
				Sleep(2000);
				system("cls");
				goto pytanie;
			}
		}
		else
			zamiana = 5;

		if (zamiana == prawidlowa)
		{
			cout << endl << "Dobra odpowiedź!" << endl << endl;
			zwyciestwa++;
		}
		else if (zamiana == 5)
			cout << "Nie ma takiej odpowiedzi! Spróbuj ponownie" << endl;
		else
		{
			cout << endl << "Zła odpowiedź!" << endl << endl;
			cout << "Poprawna odpowiedź: " << pr[losPytanie] << endl;
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
	string Pytanie[10]{ "Do Unii Europejskiej nie należy:","Na którym instrumencie grał Louis Armstrong?","Bona Sforza była żoną:","Który z wymienionych stanów USA NIE graniczy z Meksykiem?","Patagonia to kraina geograficzna w:","Śmierć którego z wymienionych władców była końcem dynastii Jagiellonów?","Najostrzejszą z tych papryk jest: ","'Capo di tutti capi' z włoskiego oznacza:","Mówiąc o Kitaju, Rosjanin ma na myśli:","Homonimem słowa ranny (o poranku) jest słowo:" };
	int prawidlowa = odp(generator);
	int licznik = 0, fifty_fifty;
	int los, zamiana, bylo[4]{ 5,5,5,5 };
	char abcd[4]{ 'a','b','c','d' };
	string pr[10]{ "Szwajcaria",  "Trąbka",  "Zygmunta I Starego",  "Waszyngton",  "Ameryce Południowej",  "Zygmunta Augusta",  "Habanero",  "Szef wszystkich szefów",  "Chińczyka",  "Ranny(zraniony)", };
	string f1[10]{ "Hiszpania","Saksofon","Zygmunta II Augusta", "Kalifornia", "Australii", "Zygmunta Starego", "Thai Chili", "Sprawy nasze są nasze", "Japończyka", "Wieczorny", };
	string f2[10]{ "Słowacja","Skrzypce","Jana I Olbrachta", "Arizona", "Europie", "Aleksandra Jagiellończyka", "Serrano", "Raz kapuś, zawsze kapuś", "Nowozelandczyka", "Poranny", };
	string f3[10]{ "Chorwacja","Puzon","Kazimierza IV Jagiellończyka", "Teksas", "Azji", "Kazimierza Jagiellończyka", "Jalapeno", "Historia świadkiem dziejów", "Tajlandczyka", "Rynna", };
	string f4[10]{ "Portugalia","Kornet","Zygmunta III Wazy", "Nowy Meksyk", "Ameryce Północnej", "Władyslaw II Jagiełło", "Poblano", "Prawda zostanie prawdą", "Koreańczyka", "Świtowy", };
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
		cout << "Zdobyta suma pieniędzy: 40 000zł. Kwota gwarantowana: 40 000zł" << endl << endl;
		cout << endl << "Koła ratunkowe: " << kolaRatunkowe << endl << endl << "Pytanie 8: " << Pytanie[losPytanie] <<endl;
		

		for (int i = 0; i < 4; i++)
		{
			cout << abcd[i] << ") ";
			cout << tab[i] << endl;
		}
		if (kolaRatunkowe != 0)
		{
			cout << endl << "Wybierz 'k', aby użyć koła ratunkowego 50/50. Nie będziesz mógł potem użyć koła 'Zmiana pytania'." << endl;
			cout << "Wybierz 'l', aby użyć koła ratunkowego 'Zmiana pytania'. Możesz go użyć wielokrotnie i użyć koła 50/50" << endl;
		}
		cout << endl << "Podaj odpowiedź: ";
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
					cout << "Zdobyta suma pieniędzy: 40 000zł. Kwota gwarantowana: 40 000zł" << endl << endl;
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
					cout << endl << "Podaj odpowiedź: ";
					cin >> odpowiedz;

					if (odpowiedz == 'a' || odpowiedz == 'A')
						zamiana = 0;
					else if (odpowiedz == 'b' || odpowiedz == 'B')
						zamiana = 1;
					else if (odpowiedz == 'k' || odpowiedz == 'K')
					{
						zamiana = 5;
						cout << " Już użyłeś koła ratunkowego, spróbuj ponownie!" << endl;
					}
					else
					{
						cout << " Nie ma takiej odpowiedzi, spróbuj ponownie!" << endl;
						zamiana = 5;
					}
					kolaRatunkowe--;
				}

			}
			else
			{
				cout << "Nie masz już kół ratunkowych!" << endl;
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
				cout << "Nie masz już kół ratunkowych!";
				Sleep(2000);
				system("cls");
				goto pytanie;
			}
		}
		else
			zamiana = 5;

		if (zamiana == prawidlowa)
		{
			cout << endl << "Dobra odpowiedź!" << endl << endl;
			zwyciestwa++;
		}
		else if (zamiana == 5)
			cout << "Nie ma takiej odpowiedzi! Spróbuj ponownie" << endl;
		else
		{
			cout << endl << "Zła odpowiedź!" << endl << endl;
			cout << "Poprawna odpowiedź: " << pr[losPytanie] << endl;
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
	string Pytanie[10]{ "Ragdoll to rasa/gatunek:","Które Chorwackie miasto nie leży nad Morzem Adriatyckim?","Komuna Paryska to zryw rewolucyjny ludności Paryża, przede wszystkim inteligencji i robotników w:","Od stężenia jakiego składnika zależy kolor skłry człowieka?","Ile metrów ma mila?","W którym roku wybuchł 'wielki pożar Londynu'?","W którym wieku powstały największe dzieła Monteskiusza?","Które zdarzenie miało miejsce najwcześniej?","Kiedy przypada swięto narodowe w Argentynie?","Trasa W-Z w Warszawie została zbudowana w latach:" };
	int prawidlowa = odp(generator);
	int licznik = 0, fifty_fifty;
	int los, zamiana, bylo[4]{ 5,5,5,5 };
	char abcd[4]{ 'a','b','c','d' };
	string pr[10]{ "Kota",  "Zagrzeb",  "XIX w.",  "Melaniny",  "1609",  "1666",  "XVIII w.",  "Śmierć Marilyn Monroe",  "25 maja",  "1947-1949", };
	string f1[10]{ "Psa","Dubrownik","XX w.", "Melatoniny", "1605", "1565", "XVII w.", "Zamach na prezydenta Kennedy'ego", "30 maja", "1945-1947", };
	string f2[10]{ "Królika","Zadar","XVII w.", "Keratyny", "1600", "1536", "I w. p. n. e.", "Lądowanie na Księżycu", "14 maja", "1950-1952", };
	string f3[10]{ "Papugi","Split","XVIII w.", "Prolaktyny", "1608", "1685", "II w. p. n. e.", "Pierwszy koncert The Beatles w Stanach Zjednoczonych", "28 kwietnia", "1955-1957", };
	string f4[10]{ "Chomika","Pula","XXVI w.", "Melanostatyna", "1606", "1657", "III w. p. n. e.", "Śmierć Winstona Churchilla", "23 kwietnia", "1957-1959", };
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
		cout << "Zdobyta suma pieniędzy: 75 000zł. Kwota gwarantowana: 40 000zł" << endl << endl;
		cout << endl << "Koła ratunkowe: " << kolaRatunkowe << endl << endl << "Pytanie 9: "<< Pytanie[losPytanie] << endl;
		

		for (int i = 0; i < 4; i++)
		{
			cout << abcd[i] << ") ";
			cout << tab[i] << endl;
		}
		if (kolaRatunkowe != 0)
		{
			cout << endl << "Wybierz 'k', aby użyć koła ratunkowego 50/50. Nie będziesz mógł potem użyć koła 'Zmiana pytania'." << endl;
			cout << "Wybierz 'l', aby użyć koła ratunkowego 'Zmiana pytania'. Możesz go użyć wielokrotnie i użyć koła 50/50" << endl;
		}
		cout << endl << "Podaj odpowiedź: ";
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
					cout << "Zdobyta suma pieniędzy: 75 000zł. Kwota gwarantowana: 40 000zł" << endl << endl;
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
					cout << endl << "Podaj odpowiedź: ";
					cin >> odpowiedz;

					if (odpowiedz == 'a' || odpowiedz == 'A')
						zamiana = 0;
					else if (odpowiedz == 'b' || odpowiedz == 'B')
						zamiana = 1;
					else if (odpowiedz == 'k' || odpowiedz == 'K')
					{
						zamiana = 5;
						cout << " Już użyłeś koła ratunkowego, spróbuj ponownie!" << endl;
					}
					else
					{
						cout << " Nie ma takiej odpowiedzi, spróbuj ponownie!" << endl;
						zamiana = 5;
					}
					kolaRatunkowe--;
				}

			}
			else
			{
				cout << "Nie masz już kół ratunkowych!" << endl;
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
				cout << "Nie masz już kół ratunkowych!";
				Sleep(2000);
				system("cls");
				goto pytanie;
			}
		}
		else
			zamiana = 5;

		if (zamiana == prawidlowa)
		{
			cout << endl << "Dobra odpowiedź!" << endl << endl;
			zwyciestwa++;
		}
		else if (zamiana == 5)
			cout << "Nie ma takiej odpowiedzi! Spróbuj ponownie" << endl;
		else
		{
			cout << endl << "Zła odpowiedź!" << endl << endl;
			cout << "Poprawna odpowiedź: " << pr[losPytanie] << endl;
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
	string Pytanie[10]{ "Monachomachia to poemat heroikomiczny o wojnie mnichów autorstwa:","Jaki stan amerykański jako pierwszy zadeklarował secesję z Unii w 1860 roku?","Który z tych szczytów nie znajduje się w Tatrach?","Co oznacza skrót RPP?","Która z tych wysp nie należy do Wysp Kanaryjskich?","Jedna z głównych ulic warszawskiego Środmieścia, przechodząca bezpośrednio w Krakowskie Przedmieście, to:","Poprawnym zapisem jest:","'Upięr w operze' to dzieło: ","Auguste Rodin to francuski:","Które Afrykaśskie państwo jest najludniejsze?" };
	int prawidlowa = odp(generator);
	int licznik = 0, fifty_fifty;
	int los, zamiana, bylo[4]{ 5,5,5,5 };
	char abcd[4]{ 'a','b','c','d' };
	string pr[10]{ "Ignacego Krasickiego",  "Karolina Południowa",  "Śnieżnik",  "Rada Polityki Pieniężnej",  "Lesbos",  "Nowy Świat",  "Znienacka",  "Andrew Lloyda Webbera",  "Rzeźbiarz",  "Nigeria", };
	string f1[10]{ "Aleksandra Fredry","Nowy Jork","Gerlach", "Rada Polityki Polskiej", "Lanzarote", "Marszałkowska", "Z nienacka", "Wolfganga Amadeusza Mozarta", "Malarz", "Kenia", };
	string f2[10]{ "Jana Kochanowskiego","Waszyngton","Krywan", "Rada Polityki Państwowej", "Lobos", "Aleje Jerozolimskie", "Znienadzka", "Stanisława Moniuszki", "Pisarz", "RPA", };
	string f3[10]{ "Juliana Ursyna Niemcewicza","Dakota Północna","Kościelec", "Rada Polskiej Przedsiębiorczości", "Teneryfa", "Grojecka", "Z nienadzka", "Fryderyka Chopina", "Kompozytor", "Mozambik", };
	string f4[10]{ "Adama Mickiewicza","Georgia","Łomnica", "Rada Państwa Polskiego", "La Palma", "Śródmiejska", "Z nie nacka", "Ignacego Paderewskiego", "Aktor", "Namibia", };
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
		cout << "Zdobyta suma pieniędzy: 125 000zł. Kwota gwarantowana: 40 000zł" << endl << endl;
		cout << endl << "Koła ratunkowe: " << kolaRatunkowe << endl << endl << "Pytanie 10: " << Pytanie[losPytanie] <<endl;
		
		for (int i = 0; i < 4; i++)
		{
			cout << abcd[i] << ") ";
			cout << tab[i] << endl;
		}
		if (kolaRatunkowe != 0)
		{
			cout << endl << "Wybierz 'k', aby użyć koła ratunkowego 50/50. Nie będziesz mógł potem użyć koła 'Zmiana pytania'." << endl;
			cout << "Wybierz 'l', aby użyć koła ratunkowego 'Zmiana pytania'. Możesz go użyć wielokrotnie i użyć koła 50/50" << endl;
		}
		cout << endl << "Podaj odpowiedź: ";
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
					cout << "Zdobyta suma pieniędzy: 125 000zł. Kwota gwarantowana: 40 000zł" << endl << endl;
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
					cout << endl << "Podaj odpowiedź: ";
					cin >> odpowiedz;

					if (odpowiedz == 'a' || odpowiedz == 'A')
						zamiana = 0;
					else if (odpowiedz == 'b' || odpowiedz == 'B')
						zamiana = 1;
					else if (odpowiedz == 'k' || odpowiedz == 'K')
					{
						zamiana = 5;
						cout << " Już użyłes koła ratunkowego, spróbuj ponownie!" << endl;
					}
					else
					{
						cout << " Nie ma takiej odpowiedzi, spróbuj ponownie!" << endl;
						zamiana = 5;
					}
					kolaRatunkowe--;
				}

			}
			else
			{
				cout << "Nie masz już kół ratunkowych!" << endl;
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
				cout << "Nie masz już kół ratunkowych!";
				Sleep(2000);
				system("cls");
				goto pytanie;
			}
		}
		else
			zamiana = 5;

		if (zamiana == prawidlowa)
		{
			cout << endl << "Dobra odpowiedź!" << endl << endl;
			zwyciestwa++;
		}
		else if (zamiana == 5)
			cout << "Nie ma takiej odpowiedzi! Spróbuj ponownie" << endl;
		else
		{
			cout << endl << "Zła odpowiedź!" << endl << endl;
			cout << "Poprawna odpowiedź: " << pr[losPytanie] << endl;
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
	string Pytanie[10]{ "W oryginalnej trylogii 'Gwiezdne wojny' 3-CPO ma srebrną: ","W której książce pojawia sie postać Winstona Smitha?","Która z tych liczb jest wynikiem działania '5!'?","Ichtiologia to nauka o:","Grupa instrumentów muzycznych w których źródłem dźwięku jest ciało stałe mające niezmienną, naturalną sprężystość, to:","Dokończ przysłowie 'Deszcze listopadowe...'","Węgierski taniec narodowy, to:","Kto stworzył fikcyjną postać Josefa Szwejka w antywojennej powieści „Przygody dobrego wojaka Szwejka”?","Autorem obrazu 'Mleczarka' jest:","Kumys powstaje w wyniku fermentacji mleka:" };
	int prawidlowa = odp(generator);
	int licznik = 0, fifty_fifty;
	int los, zamiana, bylo[4]{ 5,5,5,5 };
	char abcd[4]{ 'a','b','c','d' };
	string pr[10]{ "Prawą nogę",  "Rok 1984",  "120",  "Rybach",  "Idiofony",  "budzą wiatry zimowe",  "Czardasz",  "Jaroslav Hasek",  "Jan Vermeer",  "Końskiego", };
	string f1[10]{ "Prawą rękę","Proces","5", "Pszczołach", "Aerofony", "wróżą upały marcowe", "Trepak", "Karel Capek", "Peter Paul Rubens", "Oślego", };
	string f2[10]{ "Głowę","Fahrenheit 451","25", "Wulkanach", "Chordofony", "wróżą kłopoty drogowe", "Kozak", "Stanisław Kostka Neumann", "Rembrandt van Rijn", "Krowiego", };
	string f3[10]{ "Szczękę","Solaris","3125", "Lasach", "Membranofony", "ściągają chmury śniegowe", "Hajduk", "Julius Fucik", "Frans Hals", "Koźlego", };
	string f4[10]{ "Klatkę piersiową","Moskva","125", "Morzach i oceanach", "Instrumenty perkusyjne", "wróżą święta bezśniegowe", "Syrba", "Lubomir Benes", "Nicolaes Maes", "Owczego", };
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
		cout << "Zdobyta suma pieniędzy: 250 000zł. Kwota gwarantowana: 40 000zł" << endl << endl;
		cout << endl << "Koła ratunkowe: " << kolaRatunkowe << endl << endl << "Pytanie 11: " << Pytanie[losPytanie] <<endl;
		
		for (int i = 0; i < 4; i++)
		{
			cout << abcd[i] << ") ";
			cout << tab[i] << endl;
		}
		if (kolaRatunkowe != 0)
		{
			cout << endl << "Wybierz 'k', aby użyć koła ratunkowego 50/50. Nie będziesz mógł potem użyć koła 'Zmiana pytania'." << endl;
			cout << "Wybierz 'l', aby użyć koła ratunkowego 'Zmiana pytania'. Możesz go użyć wielokrotnie i użyć koła 50/50" << endl;
		}
		cout << endl << "Podaj odpowiedź: ";
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
					cout << "Zdobyta suma pieniędzy: 250 000zł. Kwota gwarantowana: 40 000zł" << endl << endl;
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
					cout << endl << "Podaj odpowiedź: ";
					cin >> odpowiedz;

					if (odpowiedz == 'a' || odpowiedz == 'A')
						zamiana = 0;
					else if (odpowiedz == 'b' || odpowiedz == 'B')
						zamiana = 1;
					else if (odpowiedz == 'k' || odpowiedz == 'K')
					{
						zamiana = 5;
						cout << " Już użyłeś koła ratunkowego, spróbuj ponownie!" << endl;
					}
					else
					{
						cout << " Nie ma takiej odpowiedzi, spróbuj ponownie!" << endl;
						zamiana = 5;
					}
					kolaRatunkowe--;
				}

			}
			else
			{
				cout << "Nie masz już kół ratunkowych!" << endl;
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
				cout << "Nie masz już kół ratunkowych!";
				Sleep(2000);
				system("cls");
				goto pytanie;
			}
		}
		else
			zamiana = 5;

		if (zamiana == prawidlowa)
		{
			cout << endl << "Dobra odpowiedź!" << endl << endl;
			zwyciestwa++;
		}
		else if (zamiana == 5)
			cout << "Nie ma takiej odpowiedzi! Spróbuj ponownie" << endl;
		else
		{
			cout << endl << "Zła odpowiedź!" << endl << endl;
			cout << "Poprawna odpowiedź: " << pr[losPytanie] << endl;
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
	string Pytanie[10]{ "Co na Księżycu zrobił Alan Shepard?","Ile edycji Międzynarodowego Konkursu Pianistycznego im. Fryderyka Chopina odbyło sie do 2016 r.?","Ile wynosi rekord dni bez snu?","Średnia długość jelita cienkiego wynosi:","Jak nazwano najstarszą, znaną pramatkę człowieka?","KMnO4 to wzór","Kto jest autorem obrazu 'Adele Bloch - Bauer I'?","Grupa funkcyjna -COOH jest charakterystyczna dla:","Ile razy Franklin Roosevelt pełnił kadencję prezydencką?","Hrabina Natasza Rostowa jest główną bohaterką powieści:" };
	int prawidlowa = odp(generator);
	int licznik = 0, fifty_fifty;
	int los, zamiana, bylo[4]{ 5,5,5,5 };
	char abcd[4]{ 'a','b','c','d' };
	string pr[10]{ "Zagrał w golfa",  "17",  "11",  "5-6 m",  "Lucy",  "Nadmanganianu potasu",  "Gustav Klimt",  "Kwasów karboksylowych",  "4",  "Wojna i pokój", };
	string f1[10]{ "Zaśpiewał","40","20", "2-3 m", "Bella", "Chlorku potasu", "Edward Munch", "Alkoholi", "1", "Zbrodnia i kara", };
	string f2[10]{ "Zrobił kilka pajacyków","25","4", "10-11 m", "Fiona", "Płynu Lugola", "Claude Monet", "Estrów", "2", "Anna Karenina", };
	string f3[10]{ "Zatańczyl","10","9", "7-8 m", "Amy", "Sody oczyszczonej", "Henri Matisse", "Soli", "3", "Eugeniusz Oniegin", };
	string f4[10]{ "Rzucił frisbee","20","10", "17-18 m", "Holy", "Cieczy nienutonowskiej", "Salvador Dali", "Zasad", "5", "Granica", };
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
		cout << "Zdobyta suma pieniędzy: 500 000zł. Kwota gwarantowana: 40 000zł" << endl << endl;
		cout << endl << "Koła ratunkowe: " << kolaRatunkowe << endl << endl << "Pytanie 12: " << Pytanie[losPytanie] <<endl;
		
		for (int i = 0; i < 4; i++)
		{
			cout << abcd[i] << ") ";
			cout << tab[i] << endl;
		}
		if (kolaRatunkowe != 0)
		{
			cout << endl << "Wybierz 'k', aby użyć koła ratunkowego 50/50. Nie będziesz mógł potem użyć koła 'Zmiana pytania'." << endl;
			cout << "Wybierz 'l', aby użyć koła ratunkowego 'Zmiana pytania'. Możesz go użyć wielokrotnie i użyć koła 50/50" << endl;
		}
		cout << endl << "Podaj odpowiedź: ";
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
					cout << "Zdobyta suma pieniędzy: 500 000zł. Kwota gwarantowana: 40 000zł" << endl << endl;
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
					cout << endl << "Podaj odpowiedź: ";
					cin >> odpowiedz;

					if (odpowiedz == 'a' || odpowiedz == 'A')
						zamiana = 0;
					else if (odpowiedz == 'b' || odpowiedz == 'B')
						zamiana = 1;
					else if (odpowiedz == 'k' || odpowiedz == 'K')
					{
						zamiana = 5;
						cout << " Już użyłeś koła ratunkowego, spróbuj ponownie!" << endl;
					}
					else
					{
						cout << " Nie ma takiej odpowiedzi, spróbuj ponownie!" << endl;
						zamiana = 5;
					}
					kolaRatunkowe--;
				}

			}
			else
			{
				cout << "Nie masz już kół ratunkowych!" << endl;
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
				cout << "Nie masz już kół ratunkowych!";
				Sleep(2000);
				system("cls");
				goto pytanie;
			}
		}
		else
			zamiana = 5;

		if (zamiana == prawidlowa)
		{
			cout << endl << "Dobra odpowiedź!" << endl << endl;
			zwyciestwa++;
		}
		else if (zamiana == 5)
			cout << "Nie ma takiej odpowiedzi! Spróbuj ponownie" << endl;
		else
		{
			cout << endl << "Zła odpowiedź!" << endl << endl;
			cout << "Poprawna odpowiedź: " << pr[losPytanie] << endl;
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
			cout << "Historia jest pusta, zagraj, żeby dodać wynik!\n";
		}
		 
		else {Historia.seekg(0, ios::beg);
			while (!Historia.eof())
			{
				getline(Historia, pobranie);
				dlugosc = pobranie.size();// długość nazwy użytkownika
				if (pobranie[dlugosc - 2] == ' ')//wynik 1-cyfrowy
				{
					zwyciestwo = pobranie.substr(dlugosc - 1);// oddzielenie wyniku i zapisanie do stringa
					wynik[indeks] = stoi(zwyciestwo);//zmienienie stringa na inta i wpisanie do tablicy wyników
					uzytkownik[indeks] = pobranie.substr(0, dlugosc - 1);// oddzielenie nazwy użytkownika i zapisaniedo tablicy
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
		cout << "Nie można otworzyć pliku" << endl;
	Historia.close();
	int numeracja=1;
	int NajdluzszyUzytkownik = 0;// najdluższa nazwa użytkownika 
	for (int i = 0; i < indeks; i++)
	{
		if (NajdluzszyUzytkownik < uzytkownik[i].size())
			NajdluzszyUzytkownik = uzytkownik[i].size();

	}
	for (int i = indeks-1; i >=0; i--)// wypisanie w takie sposób, żeby wyniki były równo
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
		while (CzyChceGrac)// pętla wykonuje się dpóki użytkownik chce kontynuowac grę
		{
			

			uzytkownik = "";
			while (uzytkownik.size() == 0)
			{
				system("cls");
				cout << "Podaj nazwę użytkownika (bez polskich znaków): ";
				getline(cin, uzytkownik);//pobranie nazwy użytkownika
				
			}
			
			
			Sleep(1000);
			system("cls");

			Historia.seekg(0, ios::end);
			if (Historia.tellg() == 0) 
			{
			Historia << uzytkownik;//zapisanie użytkownika do pliku
				
			}
			else
			{
				Historia << endl << uzytkownik;//zapisanie użytkownika do pliku
			}
			pyt1();
			while (porazki < 2)// pętla się wykonuje aż porażki nie wyniosą 1 wtedy wyświetla się komunikat o końcu gry
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
						cout << "Nic nie wygrałeś!" << endl;
					else if (zwyciestwa < 7)
					{
						cout << "Wygrałeś 1000 zł!" << endl;
					}
					else if (zwyciestwa >= 7)
					{
						cout << "Wygrałeś 40 000 zł!" << endl;
					}
					porazki = 2;
				}
				else if (zwyciestwa == 12)
				{
					cout << "Gratulacje! Wygrałeś milion!" << endl;
					porazki = 2;
				}
			}

			getline(cin, czychcegrac);// pozbycie się \n w buforze

			while (checGry == 1)// pętla wykonuje się tak długo, aż użytkownik poda jedną z oczekiwanych odpowiedzi
			{
				cout << endl << "Czy chcesz zagrać jeszcze raz?" << endl << "Wpisz 'tak' lub 'nie': " << endl;
				getline(cin, czychcegrac);// czy użytkonik chce dalej grać
				if (czychcegrac == "tak" || czychcegrac == "Tak" || czychcegrac == "tAk" || czychcegrac == "taK" || czychcegrac == "TAk" || czychcegrac == "tAK" || czychcegrac == "TAK" || czychcegrac == "TaK")
				{
					checGry++;//CzyChceGrac pozostaje true
				}
				else if (czychcegrac == "nie" || czychcegrac == "Nie" || czychcegrac == "nIe" || czychcegrac == "niE" || czychcegrac == "NIe" || czychcegrac == "nIE" || czychcegrac == "NIE" || czychcegrac == "NiE")
				{
					CzyChceGrac = false;//pętla gry się przerywa
					checGry++;

				}
				else
				{
					cout << "Nie rozumiem, spróbuj ponownie: " << endl;
					Sleep(2000);
					system("cls");
				}
			}


			Historia << ":  " << zwyciestwa;//dopisanie wyniku do nazwy użytkownika
			checGry = 1;
			porazki = 0;
			zwyciestwa = 0;
			kolaRatunkowe = 3;// ustawienie wszytskiego na wartość domyślną
		}
		Historia.close();
		system("cls");
		cout << endl << "Dziękuję za grę!" << endl;
		Sleep(2000);
		system("cls");
	}
char Menu()// pobranie decyzji użytkownika
{
	
	char decyzja;
	//cout << "Co chcesz zrobić? \n\nWpisz 1, aby zagrać.\nWpisz 2, aby wyświetlić historię gier.\nWpisz 3, aby wyświetlić zasady.\nWpisz 4, aby wyświetlić top 10 graczy.\nWpisz 5, aby zakończyć." << endl;
	decyzja = _getch();
	return decyzja;
	
}
void Zasady()//wyświetlenie zasad gry
{
	cout << "Zasady są bardzo proste:" << endl << "1. Jest 12 losowych pytań, każde kolejne jest trudniejsze od poprzedniego" << endl;
	cout << "2. Za każdą poprawną odpowiedź otrzymuje się coraz większą kwotę. Jest też kwota gwarantowana, którą otrzymuje się po przegranej." << endl;
	cout << "3. Do dyspozycji są dwa koła ratunkowe: 50/50 oraz 'Zamiana pytania'. Pierwsze wyświetla jedną odpowiedź poprawną i jedną fałszywą. Drugie losuje inne pytanie" << endl;
	cout << "4. Łącznie kół ratunkowych można użyć 3 razy, jednak użycie 50/50 uniemożliwia użycie go ponownie w tym samym pytaniu lub wylosowanie innego." << endl;
	cout << "5. Zamiany pytania można użyć wielokrotnie, dopóki dostępne są koła ratunkowe" << endl;
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
			cout << "Historia jest pusta, zagraj, żeby dodać wynik!\n";
		}

		else
		{
		Historia.seekg(0, ios::beg);
		while (!Historia.eof())
		{
			getline(Historia, pobranie);
			dlugosc = pobranie.size();// długość nazwy użytkownika
			if(pobranie[dlugosc -2]== ' ')//wynik 1-cyfrowy
			{
				zwyciestwo = pobranie.substr(dlugosc - 1);// oddzielenie wyniku i zapisanie do stringa
				wynik[indeks] = stoi(zwyciestwo);//zmienienie stringa na inta i wpisanie do tablicy wyników
				uzytkownik[indeks] = pobranie.substr(0, dlugosc - 1);// oddzielenie nazwy użytkownika i zapisaniedo tablicy
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
		cout << "Nie można otworzyć pliku" << endl;
	Historia.close();

	int zamiana;
	string zam;
	bool czyPokolei = false;
	while (czyPokolei == false)//sortowanie użytkowników i ich wyników
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
	int NajdluzszyUzytkownik = 0;// najdluższa nazwa użytkownika 
	for (int i = 0; i < indeks; i++)
	{
		if (NajdluzszyUzytkownik < uzytkownik[i].size())
			NajdluzszyUzytkownik = uzytkownik[i].size();

	}
	for (int i = 0; i < indeks; i++)// wypisanie w takie sposób, żeby wyniki były równo
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
	cout << "ŰŰŰ»°°°ŰŰŰ»ŰŰ»ŰŰ»°°°°°ŰŰ»°ŰŰŰŰŰ»°ŰŰŰ»°°ŰŰ»ŰŰŰŰŰŰŰ»ŰŰŰŰŰŰ»°ŰŰŰŰŰŰŰ»ŰŰ»°°°ŰŰ»ŰŰ»" << endl;//wielki napis Milionerzy
	cout << "ŰŰŰŰ»°ŰŰŰŰşŰŰşŰŰş°°°°°ŰŰşŰŰÉÍÍŰŰ»ŰŰŰŰ»°ŰŰşŰŰÉÍÍÍÍĽŰŰÉÍÍŰŰ»ČÍÍÍÍŰŰşČŰŰ»°ŰŰÉĽŰŰş" << endl;
	cout << "ŰŰÉŰŰŰŰÉŰŰşŰŰşŰŰş°°°°°ŰŰşŰŰş°°ŰŰşŰŰÉŰŰ»ŰŰşŰŰŰŰŰ»°°ŰŰŰŰŰŰÉĽ°°ŰŰŰÉÍĽ°ČŰŰŰŰÉĽ°ŰŰş" << endl;
	cout << "ŰŰşČŰŰÉĽŰŰşŰŰşŰŰş°°°°°ŰŰşŰŰş°°ŰŰşŰŰşČŰŰŰŰşŰŰÉÍÍĽ°°ŰŰÉÍÍŰŰ»ŰŰÉÍÍĽ°°°°ČŰŰÉĽ°°ČÍĽ" << endl;
	cout << "ŰŰş°ČÍĽ°ŰŰşŰŰşŰŰŰŰŰŰŰ»ŰŰşČŰŰŰŰŰÉĽŰŰş°ČŰŰŰşŰŰŰŰŰŰŰ»ŰŰş°°ŰŰşŰŰŰŰŰŰŰ»°°°ŰŰş°°°ŰŰ»" << endl;
	cout << "ČÍĽ°°°°°ČÍĽČÍĽČÍÍÍÍÍÍĽČÍĽ°ČÍÍÍÍĽ°ČÍĽ°°ČÍÍĽČÍÍÍÍÍÍĽČÍĽ°°ČÍĽČÍÍÍÍÍÍĽ°°°ČÍĽ°°°ČÍĽ" << endl;
	
	setlocale(LC_CTYPE, "Polish");//ustawienie polskiego języka (polskie znaki)

	cout << endl << endl << "Naciśnij dowolny przycisk aby rozpocząć!" << endl;
	char h;
	h=_getch();
	
	system("cls");
	
	bool dziala = true;
	while (dziala) //nieskończona pętla, kończy ją switch -> case 5
	{
		powrót:
		cout << "Co chcesz zrobić? \n\nWpisz 1, aby zagrać.\nWpisz 2, aby wyświetlić zasady.\nWpisz 3, aby wyświetlić historię gier.\nWpisz 4, aby wyświetlić top 10 graczy.\nWpisz 5, aby zakończyć." << endl;

	menu:
			decyzja = Menu();//decyzja użytkownika
			
			if (decyzja >= 49 && decyzja <= 53)
			{
				switch (decyzja)
				{
				case '1':
					
					Gra();//rozpoczęcie gry
					break;
				case '3':
					
					system("cls");//wypisanie historii gier
					historia();
					cout << "\nNaciśnij ENTER aby wyjść\n";
					while (1)
					{
						if (_getch() == 13)
						{
							system("cls");
							
							goto powrót;
						}
					}
				case '2':
					
					system("cls");//wyświetlenie zasad
					Zasady();
					cout << "\nNaciśnij ENTER aby wyjść\n";
					while (1)
					{
						if (_getch() == 13)
						{
							system("cls");
							
							goto powrót;
						}
					}
				case '4':
					
					system("cls");//wyświetlenie 10 najlepszych wyników
					top10();
					cout << "\nNaciśnij ENTER aby wyjść\n";
					while (1)
					{
						if (_getch() == 13)
						{
							system("cls");
							
							goto powrót;
						}
					}
				case '5'://zamknięcie programu
					decyzja = 0;
					exit(0);
				}
			}
			else
				goto menu;
				
			
		
	}

	system("pause");
}
