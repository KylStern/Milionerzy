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

fstream  Historia;//plik do zapisu u¿ytkowników i ich wynikow
uniform_int_distribution<int> fifty(0, 1);//losowanie kolejnoœci odp prawid³owej i fa³szywej w kole 50/50
int zwyciestwa = 0;int porazki = 0;//liczniki, zwyciêstwa oznaczaj¹ zdobyte punkty, inna wartoœæ pora¿ek ni¿ 0 oznacza przegran¹ i zakoñczenie gry
int kolaRatunkowe = 3;//liczba kó³ ratunkowych
char decyzja;//u¿yta w Menu, okreœla co chce zrobiæ u¿ytkownik
string uzytkownik;//nazwa u¿ytkownika
int checGry = 1;//czy u¿ytkownik chce graæ, domyœlnie ustawione na 1, inna wartoœæ przerywa pêtlê 
string czychcegrac{};//odpowiedŸ u¿ytkownika na pytanie czy chce dalej graæ
bool CzyChceGrac = true;// jeœli true to gra zaczyna siê od nowa, jeœli false, to wyœwietla siê menu

int powtorzonePytanie;// wartoœæ zmienia siê w funkcjach odpowiedzialnych za wyœwietlanie pytañ, upewnienie ¿e to samo pytanie nie 
//wyœwietli siê po u¿yciu ko³a "zmiana pytania"

//komentarze w funkcji pyt1 odnosz¹ siê te¿ do funkcji pyt2, pyt3, ... ,pyt12.

void pyt1()
{
	int losPytanie;//kwestia bezpieczeñstwa, ustawienie na pocz¹tek du¿ej wartoœci równej powtorzonePytanie
	losPytanie = pyt(generator);//losowanie numeru pytania (w tym indeksu tablicy pytañ i odpowiedzi)
	start:
	string Pytanie[10]{ "Jaki jest symbol chemiczny potasu?","Jaki jest symbol chemiczny Z³ota?","Autorem 'Potopu', powieœci opowiadaj¹cej o potopie szwedzkim, jest: ","W mitologii greckiej opiekunk¹ ogniska domowego by³a bogini:","W mitologii greckiej z g³owy Zeusa wyskoczy³a: ","W mitologii greckiej bogiem wojny by³:","Najd³uzsza polska rzeka to: ","Ile w Polsce jest województw?","Mo¿na znaæ siê jak dwa ³yse:","Na drzewach nie rosn¹:" };
	int prawidlowa = odp(generator);//wylosowanie, która odpowiedŸ fa³szywa zostanie zast¹piona
	int licznik = 0;//indeks odpowiedzi
	int fifty_fifty;//dla ko³a 50/50
	int los;//losowanie kolejnoœci pytañ fa³szywych
	int zamiana;//podpiêcie odpowiedzi u¿ytkownika do inta
	double bylo[4]{ 5,5,5,5 };//tablica sprawdzaj¹ca, czy wartoœæ los siê powtarza
	char abcd[4]{ 'a','b','c','d' };	// litery od 'a' do 'b', do wyœwietlenia przy odpowiedziach
	string pr[10]{ "K",  "Au",  "H. Sienkiewicz",  "Hestia",  "Atena",  "Ares",  "Wis³a",  "16",  "Konie",  "Truskawki", };//odpowiedzi prawid³owe
	string f1[10]{ "Na","Zn","J. Kochanowski", "Hera", "Persefona", "Kratos", "Odra", "14", "Psy", "Jab³ka", };
	string f2[10]{ "Au","He","A. Mickiewicz", "Atena", "Hera", "Hermes", "Warta", "15", "Koty", "Œliwki", };
	string f3[10]{ "P","In","M. Rej", "Artemida", "Afrodyta", "Zeus", "San", "20", "Barany", "Banany", };
	string f4[10]{ "Pb","Ag","J. Tuwim", "Kora", "Hestia", "Hefajstos", "Bzura", "12", "Wielb³¹dy", "Gruszki", };// f1-f4 odpowiedzi fa³szywe
	string tab[4]{}; //ta tablica bêdzie wyœwietlana
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
	tab[prawidlowa] = pr[losPytanie]; // zast¹pienie jednej z fa³szywych odpowiedzi prawdziw¹
	do {
		pytanie:
		cout << endl<<"Ko³a ratunkowe: "<< kolaRatunkowe<< endl << endl << "Pytanie 1: " << Pytanie[losPytanie] << endl;
		for (int i = 0; i < 4; i++)// wypisanie odpowiedzi
		{
			cout << abcd[i] << ") ";
			cout << tab[i] << endl;
		}
		if (kolaRatunkowe != 0)
		{
			cout << endl << "Wybierz 'k', aby u¿yæ ko³a ratunkowego 50/50. Nie bêdziesz móg³ potem u¿yæ ko³a 'Zmiana pytania'." << endl;
			cout << "Wybierz 'l', aby u¿yæ ko³a ratunkowego 'Zmiana pytania'. Mo¿esz go u¿yæ wielokrotnie i u¿yæ ko³a 50/50" << endl;
		}
		cout << endl << "Podaj odpowiedŸ: ";
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
		else if (odpowiedz == 'k' || odpowiedz == 'K') //ko³o ratunkowe 50/50
		{
			if (kolaRatunkowe != 0) //sprawdzenie czy ko³a ratunkowe s¹ dostepne
			{
				int rng = prawidlowa;
				while (rng == prawidlowa||( rng!=bylo[0] && rng != bylo[1] && rng != bylo[2] && rng != bylo[3]))
					rng = odp(generator);//wylosowanie indeksu odpowiedzi fa³szywej innego ni¿ indeks odpowiedzi prawdziwej,
				//plus upewnienie siê, ¿eby wczeœniej niewyœwietlona odpowiedŸ siê nie wyœwietli³a
				
				
				fifty_fifty = fifty(generator);//losowanie miêdzy 0 a 1
				zamiana = 5; //dla pêtli poni¿ej
				while (zamiana==5) //zamiana ustawia siê na 5, jeœli nie istnieje odpowiedŸ pdana przez u¿ytkownika
				{
					Sleep(1000);
					system("cls");
					cout << "Pytanie 1: " << Pytanie[losPytanie] << endl;
					if (fifty_fifty == 0)//ustalanie koljenoœci odpowiedzi fa³szywej i prawdziewj
					{
						cout << "a) " << pr[losPytanie] << endl;
						cout << "b) " << tab[rng] << endl;
						prawidlowa = 0;
					}
					else if (fifty_fifty == 1)//tu te¿
					{
						cout << "a) " << tab[rng] << endl;
						cout << "b) " << pr[losPytanie] << endl;
						prawidlowa = 1;
					}
						cout << endl << "Podaj odpowiedŸ: ";
						cin >> odpowiedz;

					if (odpowiedz == 'a' || odpowiedz == 'A')//sprawdzenie odpowiedzi
						zamiana = 0;
					else if (odpowiedz == 'b' || odpowiedz == 'B')
						zamiana = 1;
					else if (odpowiedz == 'k' || odpowiedz == 'K')//zapobiegniêcie ponownemu u¿yciu 50/50
					{
						zamiana = 5;//powtórzenie pêtli
						cout << " Ju¿ u¿y³eœ ko³a ratunkowego, spróbuj ponownie!" << endl;
					}
					else//odpowiedŸ inna ni¿ oczekiwane
					{
						cout << " Nie ma takiej odpowiedzi, spróbuj ponownie!" << endl;
						zamiana = 5;//powtórzenie pêtli
					}
					kolaRatunkowe--;
				}
				
			}
			else //nie ma kó³ ratunkowych
			{
				cout << "Nie masz ju¿ kó³ ratunkowych!" << endl;
				Sleep(1000);
				system("cls");
				goto pytanie;
			}
		}
		else if (odpowiedz == 'l' || odpowiedz == 'L')//ko³o ratunkowe "Zmiana pytania"
		{
			if (kolaRatunkowe > 0)//czy u¿ytkownik ma ko³a ratunkowe
			{
				powtorzonePytanie = losPytanie;//zapamiêtanie pytania które ju¿ by³o
				kolaRatunkowe--;//zmniejszenie kó³ ratunkowych
				system("cls");
				while (losPytanie == powtorzonePytanie)//wylosowanie innego pytania 
					losPytanie = pyt(generator);
				goto start;//funkcja zaczyna siê od nowa, losuj¹c inne pytanie
			}
			else//u¿ytykownik nie ma kó³ ratunkowych
			{
				cout << "Nie masz ju¿ kó³ ratunkowych!";
				Sleep(2000);
				system("cls");
				goto pytanie;//powrót do pytania
			}
		}
		else
			zamiana = 5;// pêtla wykona siê od nowa

		if (zamiana == prawidlowa)//czy przekonwertowana odpowiedŸ zgadza siê z odp prawid³ow¹
		{
			cout << endl << "Dobra odpowiedŸ!" << endl << endl;
			zwyciestwa++;
		}
		else if (zamiana == 5)
			cout << "Nie ma takiej odpowiedzi! Spróbuj ponownie" << endl;
		else//powiadomienie o z³ej odpowiedzi i wyœwitlenie poprawnej
		{
			cout <<endl<< "Z³a odpowiedŸ!" << endl << endl;
			cout << "Poprawna odpowiedŸ: "<< pr[losPytanie] << endl;
			porazki++;
			Sleep(1000);
		}
		Sleep(2000);
		system("cls");
	} while (zamiana == 5);// warunek powtarzania pêtli
	powtorzonePytanie = 30;//ustawienie wartoœci z powrotem, by wszystkie 10 pytañ w nastêpnej funkcji mog³o byæ wylosowane 
}
void pyt2()
{
	int losPytanie;
	losPytanie = pyt(generator);
	start:
	string Pytanie[10]{ "W którym roku rozpoczê³a siê I wojna œwiatowa?","Pierwszym cz³owiekiem na Ksiê¿ycu by³:","Pi¹ta planeta od S³oñca to:","Nazwa naszej galaktyki to:","Drzewem liœciastym nie jest:","Kontynentów jest: ","Które pañstwo nie ma dostêpu do morza?","Napoleon pochodzi³ z:","Egipski bóg umar³ych Anubis mia³ g³owê:","Brylant to oszlifowany:" };
	int prawidlowa = odp(generator);
	int licznik = 0, fifty_fifty;
	int zamiana, bylo[4]{ 5,5,5,5 };
	char abcd[4]{ 'a','b','c','d' };
	string pr[10]{ "1914",  "Neil Armstrong",  "Jowisz",  "Droga Mleczna",  "Modrzew",  "7",  "Czechy",  "Francji",  "Szakala",  "Diament", };
	string f1[10]{ "1918","Buzz Aldrin","Ziemia", "Andromeda", "Klon", "5", "Polska", "W³och", "Kota", "Rubin", };
	string f2[10]{ "1939","Michael Collins","Mars", "S³oneczna", "Brzoza", "8", "Rosja", "Rosji", "Sepa", "Szmaragd", };
	string f3[10]{ "1908","John F. Kennedy","Pluton", "Czarna Dziura", "Jab³oñ", "6", "W³ochy", "Hiszpanii", "Krokodyla", "Topaz", };
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
		cout << "Zdobyta suma pieniêdzy: 500z³" << endl << endl;
		cout << endl << "Ko³a ratunkowe: " << kolaRatunkowe << endl << endl << "Pytanie 2: " << Pytanie[losPytanie] << endl;
		

		for (int i = 0; i < 4; i++)
		{
			cout << abcd[i] << ") ";
			cout << tab[i] << endl;
		}
		if (kolaRatunkowe != 0)
		{
			cout << endl << "Wybierz 'k', aby u¿yæ ko³a ratunkowego 50/50. Nie bêdziesz móg³ potem u¿yæ ko³a 'Zmiana pytania'." << endl;
			cout << "Wybierz 'l', aby u¿yæ ko³a ratunkowego 'Zmiana pytania'. Mo¿esz go u¿yæ wielokrotnie i u¿yæ ko³a 50/50" << endl;
		}
		cout << endl << "Podaj odpowiedŸ: ";
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
					cout << "Zdobyta suma pieniêdzy: 500z³" << endl << endl;
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
					cout << endl << "Podaj odpowiedŸ: ";
					cin >> odpowiedz;

					if (odpowiedz == 'a' || odpowiedz == 'A')
						zamiana = 0;
					else if (odpowiedz == 'b' || odpowiedz == 'B')
						zamiana = 1;
					else if (odpowiedz == 'k' || odpowiedz == 'K')
					{
						zamiana = 5;
						cout << " Ju¿ u¿y³eœ ko³a ratunkowego, spróbuj ponownie!" << endl;
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
				cout << "Nie masz ju¿ kó³ ratunkowych!" << endl;
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
				cout << "Nie masz ju¿ kó³ ratunkowych!";
				Sleep(2000);
				system("cls");
				goto pytanie;
			}
		}
		else
			zamiana = 5;

		if (zamiana == prawidlowa)
		{
			cout << endl << "Dobra odpowiedŸ!" << endl << endl;
			zwyciestwa++;
		}
		else if (zamiana == 5)
			cout << "Nie ma takiej odpowiedzi! Spróbuj ponownie" << endl;
		else
		{
			cout << endl << "Z³a odpowiedŸ!" << endl << endl;
			cout << "Poprawna odpowiedŸ: " << pr[losPytanie] << endl;
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
	string Pytanie[10]{ "Do ilu mórz ma dostêp Finlandia?","Jak nazywa siê chorobliwy lêk przed ogniem?","Jak nazywa siê urzêdnik stoj¹cy na czele powiatu?","Kiedy zaton¹³ Titanic?","Którego utworu nie napisa³ Szekspir?","W którym roku Krzysztof Kolumb odkry³ Ameryke?","Czyja wyprawa jako pierwsza op³ynê³a glob?","Wynalazc¹ druku jest: ","Ile stóp ma metr?","Jak ma na imiê g³ówny bohater serii ksi¹¿ek o wiedŸminie Andrzeja Sapkowskiego?" };
	int prawidlowa = odp(generator);
	int licznik = 0, fifty_fifty;
	int los, zamiana, bylo[4]{ 5,5,5,5 };
	char abcd[4]{ 'a','b','c','d' };
	string pr[10]{ "Jednego",  "Pirofobia",  "Starosta",  "W pierwszej po³owie XX wieku",  "Zemsta",  "1492",  "Ferdynanda Magellana",  "Jan Gutenberg",  "Oko³o 3",  "Geralt", };
	string f1[10]{ "Dwóch","Arachnofobia","So³tys", "W drugiej po³owie XVIII wieku", "Hamlet", "1410", "Krzysztofa Kolumba", "Marcin Luter", "Oko³o 4", "Gerard", };
	string f2[10]{ "Trzech","Aerofobia","Wójt", "W pierwszej po³owie XIX wieku", "Romeo i Julia", "1502", "Marco Polo", "Leonardo da Vinci", "Oko³o 2", "Gerart", };
	string f3[10]{ "Czterech","Duxofobia","Burmistrz", "W drugiej po³owie XIX wieku", "Makbet", "1452", "Vasco Da Gama", "Galileusz", "Oko³o 6", "Gelart", };
	string f4[10]{ "¯adnego","Agorafobia","Prezydent", "W drugiej po³owie XX wieku", "Sen nocy letniej", "1499", "James Cook", "Jan Kalwin", "Oko³o 5", "Gelard", };
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
		cout << "Zdobyta suma pieniêdzy: 1000z³. Kwota gwarantowana: 1000z³" << endl << endl;
		cout << endl << "Ko³a ratunkowe: " << kolaRatunkowe << endl << endl << "Pytanie 3: " << Pytanie[losPytanie] <<endl;
		

		for (int i = 0; i < 4; i++)
		{
			cout << abcd[i] << ") ";
			cout << tab[i] << endl;
		}
		if (kolaRatunkowe != 0)
		{
			cout << endl << "Wybierz 'k', aby u¿yæ ko³a ratunkowego 50/50. Nie bêdziesz móg³ potem u¿yæ ko³a 'Zmiana pytania'." << endl;
			cout << "Wybierz 'l', aby u¿yæ ko³a ratunkowego 'Zmiana pytania'. Mo¿esz go u¿yæ wielokrotnie i u¿yæ ko³a 50/50" << endl;
		}
		cout << endl << "Podaj odpowiedŸ: ";
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
					cout << "Zdobyta suma pieniêdzy: 1000z³. Kwota gwarantowana: 1000z³" << endl << endl;
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
					cout << endl << "Podaj odpowiedŸ: ";
					cin >> odpowiedz;

					if (odpowiedz == 'a' || odpowiedz == 'A')
						zamiana = 0;
					else if (odpowiedz == 'b' || odpowiedz == 'B')
						zamiana = 1;
					else if (odpowiedz == 'k' || odpowiedz == 'K')
					{
						zamiana = 5;
						cout << " Ju¿ u¿y³eœ ko³a ratunkowego, spróbuj ponownie!" << endl;
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
				cout << "Nie masz ju¿ kó³ ratunkowych!" << endl;
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
				cout << "Nie masz ju¿ kó³ ratunkowych!";
				Sleep(2000);
				system("cls");
				goto pytanie;
			}
		}
		else
			zamiana = 5;

		if (zamiana == prawidlowa)
		{
			cout << endl << "Dobra odpowiedŸ!" << endl << endl;
			zwyciestwa++;
		}
		else if (zamiana == 5)
			cout << "Nie ma takiej odpowiedzi! Spróbuj ponownie" << endl;
		else
		{
			cout << endl << "Z³a odpowiedŸ!" << endl << endl;
			cout << "Poprawna odpowiedŸ: " << pr[losPytanie] << endl;
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
	string Pytanie[10]{ "Symbolem Szkocji jest:","Jak Harry Potter nazwa³ swoj¹ sowê?","Gdzie znajduje sie Stonehenge","Kto jest tworc¹ postaci Pana Kleksa?","Ile kó³ ma rydwan","W którym województwie le¿y Ko³obrzeg?","Wellington jest stolic¹ którego pañstwa?","Drugim najwy¿szym szczytem na Ziemii jest: ","Jak nazywa siê najbardziej zasolone jezioro na Ziemii?","Ile w Biblii by³o plag egipskich? " };
	int prawidlowa = odp(generator);
	int licznik = 0, fifty_fifty;
	int los, zamiana, bylo[4]{ 5,5,5,5 };
	char abcd[4]{ 'a','b','c','d' };
	string pr[10]{ "Koniczyna",  "Hedwiga",  "W Wielkiej Brytanii",  "Jan Brzechwa",  "Dwa",  "W zachodniopomorskim",  "Nowej Zelandii",  "K2",  "Morze Martwe",  "10", };
	string f1[10]{ "Mlecz","Hagrida","W Irlandii", "Julian Tuwim ", "Cztery", "W mazowieckim", "Irlandii", "Mount Everest", "Jezioro Aralskie", "13", };
	string f2[10]{ "Ró¿a","Hermiona","We Francji", "Henryk Sienkiewicz", "Piêæ", "W malopolskim", "Islandii", "Mont Blanc", "Jezioro Bodeñskie", "7", };
	string f3[10]{ "Oset","Przepiórka","W Islandii", "Maria Konopnicka", "Szeœæ", "W lubelskim", "Albanii", "Góra Koœciuszki", "Morze Kaspijskie", "8", };
	string f4[10]{ "Pokrzywa","W³ochatka","W Australii", "Adam Mickiewicz", "Trzy", "W kujawsko-pomorskim", "Australii", "Kilimand¿aro", "Jezioro ¯ywieckie", "5", };
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
		cout << "Zdobyta suma pieniêdzy: 2000z³. Kwota gwarantowana: 1000z³" << endl << endl;
		cout << endl << "Ko³a ratunkowe: " << kolaRatunkowe << endl << endl << "Pytanie 4: " << Pytanie[losPytanie] << endl;
		
		for (int i = 0; i < 4; i++)
		{
			cout << abcd[i] << ") ";
			cout << tab[i] << endl;
		}
		if (kolaRatunkowe != 0)
		{
			cout << endl << "Wybierz 'k', aby u¿yæ ko³a ratunkowego 50/50. Nie bêdziesz móg³ potem u¿yæ ko³a 'Zmiana pytania'." << endl;
			cout << "Wybierz 'l', aby u¿yæ ko³a ratunkowego 'Zmiana pytania'. Mo¿esz go u¿yæ wielokrotnie i u¿yæ ko³a 50/50" << endl;
		}
		cout << endl << "Podaj odpowiedŸ: ";
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
					cout << "Zdobyta suma pieniêdzy: 2000z³. Kwota gwarantowana: 1000z³" << endl << endl;
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
					cout << endl << "Podaj odpowiedŸ: ";
					cin >> odpowiedz;

					if (odpowiedz == 'a' || odpowiedz == 'A')
						zamiana = 0;
					else if (odpowiedz == 'b' || odpowiedz == 'B')
						zamiana = 1;
					else if (odpowiedz == 'k' || odpowiedz == 'K')
					{
						zamiana = 5;
						cout << " Ju¿ u¿y³es ko³a ratunkowego, spróbuj ponownie!" << endl;
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
				cout << "Nie masz ju¿ kó³ ratunkowych!" << endl;
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
				cout << "Nie masz ju¿ kó³ ratunkowych!";
				Sleep(2000);
				system("cls");
				goto pytanie;
			}
		}
		else
			zamiana = 5;

		if (zamiana == prawidlowa)
		{
			cout << endl << "Dobra odpowiedŸ!" << endl << endl;
			zwyciestwa++;
		}
		else if (zamiana == 5)
			cout << "Nie ma takiej odpowiedzi! Spróbuj ponownie" << endl;
		else
		{
			cout << endl << "Z³a odpowiedŸ!" << endl << endl;
			cout << "Poprawna odpowiedŸ: " << pr[losPytanie] << endl;
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
	string Pytanie[10]{ "Stolic¹ Maroko jest:","Jaka waluta obowi¹zuje na Wêgrzech?","G³ówny bohater 'Ferdydurke' W. Gombrowicza nazywa³ siê:","Która z podanych chorób NIE jest chorob¹ wirusow¹?","Kraj Kwitn¹cej Wiœni to: ","Inkowie ¿yli w:","Stolic¹ Lotaryngii jest:","Wojna stuletna toczy³a siê miêdzy Francj¹, a:","Sma¿one kulki albo kotleciki z ciecierzycy lub bobu z sezamem to:","Noc Kryszta³owa mia³a miejsce w/we:" };
	int prawidlowa = odp(generator);
	int licznik = 0, fifty_fifty;
	int los, zamiana, bylo[4]{ 5,5,5,5 };
	char abcd[4]{ 'a','b','c','d' };
	string pr[10]{ "Rabat",  "Forint",  "Józio Kowalski",  "Angina",  "Japonia",  "Ameryce Po³udniowej",  "Metz",  "Angli¹",  "Falafel",  "Niemczech", };
	string f1[10]{ "Ankara","Korona Wêgierska","Jan Kowalski", "Ospa wietrzna", "Chiny", "Ameryce Pó³nocnej", "Cannes", "Hiszpani¹", "Kebab", "W³oszech", };
	string f2[10]{ "Burkina Faso","Marka Wêgierska","Staœ Tarkowski", "Grypa", "Singapur", "Afryce", "Reims", "Polsk¹", "Kuskus", "Francji", };
	string f3[10]{ "Kair","Euro","Olaf Pimka", "Œwinka", "Korea Po³udniowa", "Europie", "Nicea", "Niemcami", "Tabbouleh", "Czechach", };
	string f4[10]{ "Maroko","Kuna","Ryszard Miœ", "Ró¿yczka", "Nepal", "Australii", "Nancy", "Portugali¹", "Kotlet mielony", "Wielkiej Brytanii", };
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
		cout << "Zdobyta suma pieniêdzy: 5000z³. Kwota gwarantowana: 1000z³" << endl << endl;
		cout << endl << "Ko³a ratunkowe: " << kolaRatunkowe << endl << endl << "Pytanie 5: " << Pytanie[losPytanie] << endl;
		

		for (int i = 0; i < 4; i++)
		{
			cout << abcd[i] << ") ";
			cout << tab[i] << endl;
		}
		if (kolaRatunkowe != 0)
		{
			cout << endl << "Wybierz 'k', aby u¿yæ ko³a ratunkowego 50/50. Nie bêdziesz móg³ potem u¿yæ ko³a 'Zmiana pytania'." << endl;
			cout << "Wybierz 'l', aby u¿yæ ko³a ratunkowego 'Zmiana pytania'. Mo¿esz go u¿yæ wielokrotnie i u¿yæ ko³a 50/50" << endl;
		}
		cout << endl << "Podaj odpowiedŸ: ";
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
					cout << "Zdobyta suma pieniêdzy: 5000z³. Kwota gwarantowana: 1000z³" << endl << endl;
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
					cout << endl << "Podaj odpowiedŸ: ";
					cin >> odpowiedz;

					if (odpowiedz == 'a' || odpowiedz == 'A')
						zamiana = 0;
					else if (odpowiedz == 'b' || odpowiedz == 'B')
						zamiana = 1;
					else if (odpowiedz == 'k' || odpowiedz == 'K')
					{
						zamiana = 5;
						cout << " Ju¿ u¿y³eœ ko³a ratunkowego, spróbuj ponownie!" << endl;
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
				cout << "Nie masz ju¿ kó³ ratunkowych!" << endl;
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
				cout << "Nie masz ju¿ kó³ ratunkowych!";
				Sleep(2000);
				system("cls");
				goto pytanie;
			}
		}
		else
			zamiana = 5;

		if (zamiana == prawidlowa)
		{
			cout << endl << "Dobra odpowiedŸ!" << endl << endl;
			zwyciestwa++;
		}
		else if (zamiana == 5)
			cout << "Nie ma takiej odpowiedzi! Spróbuj ponownie" << endl;
		else
		{
			cout << endl << "Z³a odpowiedŸ!" << endl << endl;
			cout << "Poprawna odpowiedŸ: " << pr[losPytanie] << endl;
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
	string Pytanie[10]{ "Sk¹d pochodzi Connan Barbarzyñca?","Najwy¿sze polskie odznaczenie wojskowe, nadawane za wybitne zas³ugi bojowe, to:","Langusta to:","W którym województwie znajduje siê Ojcowski Park Narodowy?","Trafalgar Square to plac znajduj¹cy siê w:","Którego utworu symbolem jest czapka z pawim piórem?","Który polski prezydent zgin¹³ 5 dni po objêciu stanowiska?","Co znaczy ³aciñskie wyra¿enie 'Pecunia non olet'?","Które z poni¿szych miast znajduje siê na zachodnim wybrze¿u Stanów Zjednoczonych?","Wojna zimowa to nazwa konfliktu zbrojnego tocz¹cego siê od 30 listopada 1939 do 13 marca 1940 pomiêdzy ZSRR a:" };
	int prawidlowa = odp(generator);
	int licznik = 0, fifty_fifty;
	int los, zamiana, bylo[4]{ 5,5,5,5 };
	char abcd[4]{ 'a','b','c','d' };
	string pr[10]{ "Z Cimmerii",  "Order Virtuti Militari",  "Skorupiak morski",  "Ma³opolskim",  "Londynie",  "Wesele",  "Gabriel Narutowicz",  "Pieni¹dze nie smierdz¹",  "San Francisco",  "Finlandia", };
	string f1[10]{ "Z Rivii","Krzy¿ Poleg³ych","Ryba", "Œl¹skim", "Nowym Jorku", "Ogniem i Mieczem", "Ignacy Moœcicki", "Chwytaj dzieñ", "Miami", "Dania", };
	string f2[10]{ "Z Cuzco","Order Odrodzenia Polski","Krzew", "Swiêtokrzyskim", "Doblinie", "Pan Wo³odyjowski", "Ignacy Jan Paderewski", "Polityka nie œmierdzi", "Nowy Jork", "Norwegia", };
	string f3[10]{ "Z Niziny Wêgierskiej","Order Krzy¿a Wojskowego","Owad", "Podkarpackim", "Sydney", "Ferdydurke", "Maciej Rataj", "Pamiêtaj o œmierci", "Chicago", "Szwecj¹", };
	string f4[10]{ "Z Rzymu","Order Orla Bialego","P³az", "Mazowieckim", "Manchesterze", "Pan Tadeusz", "Boles³aw Bierut", "Nic nowego", "Waszyngton", "Kazachstanem", };
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
		cout << "Zdobyta suma pieniêdzy: 10 000z³. Kwota gwarantowana: 1000z³" << endl << endl;
		cout << endl << "Ko³a ratunkowe: " << kolaRatunkowe << endl << endl << "Pytanie 6: " << Pytanie[losPytanie] <<endl;
		

		for (int i = 0; i < 4; i++)
		{
			cout << abcd[i] << ") ";
			cout << tab[i] << endl;
		}
		if (kolaRatunkowe != 0)
		{
			cout << endl << "Wybierz 'k', aby u¿yæ ko³a ratunkowego 50/50. Nie bêdziesz móg³ potem u¿yæ ko³a 'Zmiana pytania'." << endl;
			cout << "Wybierz 'l', aby u¿yæ ko³a ratunkowego 'Zmiana pytania'. Mo¿esz go u¿yæ wielokrotnie i u¿yæ ko³a 50/50" << endl;
		}
		cout << endl << "Podaj odpowiedŸ: ";
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
					cout << "Zdobyta suma pieniêdzy: 10 000z³. Kwota gwarantowana: 1000z³" << endl << endl;
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
					cout << endl << "Podaj odpowiedŸ: ";
					cin >> odpowiedz;

					if (odpowiedz == 'a' || odpowiedz == 'A')
						zamiana = 0;
					else if (odpowiedz == 'b' || odpowiedz == 'B')
						zamiana = 1;
					else if (odpowiedz == 'k' || odpowiedz == 'K')
					{
						zamiana = 5;
						cout << " Ju¿ u¿y³eœ ko³a ratunkowego, spróbuj ponownie!" << endl;
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
				cout << "Nie masz ju¿ kó³ ratunkowych!" << endl;
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
				cout << "Nie masz ju¿ kó³ ratunkowych!";
				Sleep(2000);
				system("cls");
				goto pytanie;
			}
		}
		else
			zamiana = 5;

		if (zamiana == prawidlowa)
		{
			cout << endl << "Dobra odpowiedŸ!" << endl << endl;
			zwyciestwa++;
		}
		else if (zamiana == 5)
			cout << "Nie ma takiej odpowiedzi! Spróbuj ponownie" << endl;
		else
		{
			cout << endl << "Z³a odpowiedŸ!" << endl << endl;
			cout << "Poprawna odpowiedŸ: " << pr[losPytanie] << endl;
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
	string Pytanie[10]{ "Z ilu koœci sk³ada siê nadgarstek?","Nizina Mand¿urska, zajmuj¹ca obszar oko³o 350 tys. km, znajduje siê w:","Który z wymienionych malarzy by³ tworc¹ kubizmu?","Którego z wymienionych pierwiastków jest procentowo najwiêcej w bia³kach?","Prawid³owy tytu³ dramatu Tennessee Williamsa, to:","W którym pañstwie znajduje siê najd³u¿szy szklany most wisz¹cy?","Które z wymienionych pañstw le¿y na Pó³wyspie Iberyjskim?","Wed³ug Platona, 'Demokracja prowadzi do...':","Panczeny to","Dat¹ rozbicia dzielnicowego Polski jest rok:" };
	int prawidlowa = odp(generator);
	int licznik = 0, fifty_fifty;
	int los, zamiana, bylo[4]{ 5,5,5,5 };
	char abcd[4]{ 'a','b','c','d' };
	string pr[10]{ "8",  "Chinach",  "Pablo Picasso",  "Wêgla",  "Szklana Mena¿eria",  "W Chinach",  "Andora",  "Dyktatury",  "£y¿wy",  "1138", };
	string f1[10]{ "4","Indiach","Paul Gauguin", "Cynku", "Szklana góra", "W Japonii", "Francja", "Dobrobytu", "Bojlery", "1320", };
	string f2[10]{ "10","Mongolii","Leonardo Da Vinci", "Fosforu", "Szklana szkatu³ka", "W Korei Po³udniowej", "W³ochy", "Wojny", "Narty", "1025", };
	string f3[10]{ "5","Rosji","Claude Monet", "Siarki", "Szklana kula", "W Tajlandii", "Niemcy", "Demoralizacji", "Sanki", "1226", };
	string f4[10]{ "7","Kazachstanie","Salvador Dali", "O³owiu", "Szklana bransoleta", "W Korei Pó³ónocnej", "Mauretania", "Tragedii", "Rakiety do œniegu", "1410", };
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
		cout << "Zdobyta suma pieniêdzy: 20 000z³. Kwota gwarantowana: 1000z³" << endl << endl;
		cout << endl << "Ko³a ratunkowe: " << kolaRatunkowe << endl << endl << "Pytanie 7: " << Pytanie[losPytanie] <<endl;
		

		for (int i = 0; i < 4; i++)
		{
			cout << abcd[i] << ") ";
			cout << tab[i] << endl;
		}
		if (kolaRatunkowe != 0)
		{
			cout << endl << "Wybierz 'k', aby u¿yæ ko³a ratunkowego 50/50. Nie bêdziesz móg³ potem u¿yæ ko³a 'Zmiana pytania'." << endl;
			cout << "Wybierz 'l', aby u¿yæ ko³a ratunkowego 'Zmiana pytania'. Mo¿esz go u¿yæ wielokrotnie i u¿yæ ko³a 50/50" << endl;
		}
		cout << endl << "Podaj odpowiedŸ: ";
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
					cout << "Zdobyta suma pieniêdzy: 20 000z³. Kwota gwarantowana: 1000z³" << endl << endl;
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
					cout << endl << "Podaj odpowiedŸ: ";
					cin >> odpowiedz;

					if (odpowiedz == 'a' || odpowiedz == 'A')
						zamiana = 0;
					else if (odpowiedz == 'b' || odpowiedz == 'B')
						zamiana = 1;
					else if (odpowiedz == 'k' || odpowiedz == 'K')
					{
						zamiana = 5;
						cout << " Ju¿ u¿y³eœ ko³a ratunkowego, spróbuj ponownie!" << endl;
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
				cout << "Nie masz ju¿ kó³ ratunkowych!" << endl;
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
				cout << "Nie masz ju¿ kó³ ratunkowych!";
				Sleep(2000);
				system("cls");
				goto pytanie;
			}
		}
		else
			zamiana = 5;

		if (zamiana == prawidlowa)
		{
			cout << endl << "Dobra odpowiedŸ!" << endl << endl;
			zwyciestwa++;
		}
		else if (zamiana == 5)
			cout << "Nie ma takiej odpowiedzi! Spróbuj ponownie" << endl;
		else
		{
			cout << endl << "Z³a odpowiedŸ!" << endl << endl;
			cout << "Poprawna odpowiedŸ: " << pr[losPytanie] << endl;
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
	string Pytanie[10]{ "Do Unii Europejskiej nie nale¿y:","Na którym instrumencie gra³ Louis Armstrong?","Bona Sforza by³a ¿on¹:","Który z wymienionych stanów USA NIE graniczy z Meksykiem?","Patagonia to kraina geograficzna w:","Œmieræ którego z wymienionych w³adców by³a koñcem dynastii Jagiellonów?","Najostrzejsz¹ z tych papryk jest: ","'Capo di tutti capi' z w³oskiego oznacza:","Mówi¹c o Kitaju, Rosjanin ma na myœli:","Homonimem s³owa ranny (o poranku) jest s³owo:" };
	int prawidlowa = odp(generator);
	int licznik = 0, fifty_fifty;
	int los, zamiana, bylo[4]{ 5,5,5,5 };
	char abcd[4]{ 'a','b','c','d' };
	string pr[10]{ "Szwajcaria",  "Tr¹bka",  "Zygmunta I Starego",  "Waszyngton",  "Ameryce Po³udniowej",  "Zygmunta Augusta",  "Habanero",  "Szef wszystkich szefów",  "Chiñczyka",  "Ranny(zraniony)", };
	string f1[10]{ "Hiszpania","Saksofon","Zygmunta II Augusta", "Kalifornia", "Australii", "Zygmunta Starego", "Thai Chili", "Sprawy nasze s¹ nasze", "Japoñczyka", "Wieczorny", };
	string f2[10]{ "S³owacja","Skrzypce","Jana I Olbrachta", "Arizona", "Europie", "Aleksandra Jagielloñczyka", "Serrano", "Raz kapuœ, zawsze kapuœ", "Nowozelandczyka", "Poranny", };
	string f3[10]{ "Chorwacja","Puzon","Kazimierza IV Jagielloñczyka", "Teksas", "Azji", "Kazimierza Jagielloñczyka", "Jalapeno", "Historia œwiadkiem dziejów", "Tajlandczyka", "Rynna", };
	string f4[10]{ "Portugalia","Kornet","Zygmunta III Wazy", "Nowy Meksyk", "Ameryce Pó³nocnej", "W³adyslaw II Jagie³³o", "Poblano", "Prawda zostanie prawd¹", "Koreañczyka", "Œwitowy", };
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
		cout << "Zdobyta suma pieniêdzy: 40 000z³. Kwota gwarantowana: 40 000z³" << endl << endl;
		cout << endl << "Ko³a ratunkowe: " << kolaRatunkowe << endl << endl << "Pytanie 8: " << Pytanie[losPytanie] <<endl;
		

		for (int i = 0; i < 4; i++)
		{
			cout << abcd[i] << ") ";
			cout << tab[i] << endl;
		}
		if (kolaRatunkowe != 0)
		{
			cout << endl << "Wybierz 'k', aby u¿yæ ko³a ratunkowego 50/50. Nie bêdziesz móg³ potem u¿yæ ko³a 'Zmiana pytania'." << endl;
			cout << "Wybierz 'l', aby u¿yæ ko³a ratunkowego 'Zmiana pytania'. Mo¿esz go u¿yæ wielokrotnie i u¿yæ ko³a 50/50" << endl;
		}
		cout << endl << "Podaj odpowiedŸ: ";
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
					cout << "Zdobyta suma pieniêdzy: 40 000z³. Kwota gwarantowana: 40 000z³" << endl << endl;
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
					cout << endl << "Podaj odpowiedŸ: ";
					cin >> odpowiedz;

					if (odpowiedz == 'a' || odpowiedz == 'A')
						zamiana = 0;
					else if (odpowiedz == 'b' || odpowiedz == 'B')
						zamiana = 1;
					else if (odpowiedz == 'k' || odpowiedz == 'K')
					{
						zamiana = 5;
						cout << " Ju¿ u¿y³eœ ko³a ratunkowego, spróbuj ponownie!" << endl;
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
				cout << "Nie masz ju¿ kó³ ratunkowych!" << endl;
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
				cout << "Nie masz ju¿ kó³ ratunkowych!";
				Sleep(2000);
				system("cls");
				goto pytanie;
			}
		}
		else
			zamiana = 5;

		if (zamiana == prawidlowa)
		{
			cout << endl << "Dobra odpowiedŸ!" << endl << endl;
			zwyciestwa++;
		}
		else if (zamiana == 5)
			cout << "Nie ma takiej odpowiedzi! Spróbuj ponownie" << endl;
		else
		{
			cout << endl << "Z³a odpowiedŸ!" << endl << endl;
			cout << "Poprawna odpowiedŸ: " << pr[losPytanie] << endl;
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
	string Pytanie[10]{ "Ragdoll to rasa/gatunek:","Które Chorwackie miasto nie le¿y nad Morzem Adriatyckim?","Komuna Paryska to zryw rewolucyjny ludnoœci Pary¿a, przede wszystkim inteligencji i robotników w:","Od stê¿enia jakiego sk³adnika zale¿y kolor sk³ry cz³owieka?","Ile metrów ma mila?","W którym roku wybuch³ 'wielki po¿ar Londynu'?","W którym wieku powsta³y najwiêksze dzie³a Monteskiusza?","Które zdarzenie mia³o miejsce najwczeœniej?","Kiedy przypada swiêto narodowe w Argentynie?","Trasa W-Z w Warszawie zosta³a zbudowana w latach:" };
	int prawidlowa = odp(generator);
	int licznik = 0, fifty_fifty;
	int los, zamiana, bylo[4]{ 5,5,5,5 };
	char abcd[4]{ 'a','b','c','d' };
	string pr[10]{ "Kota",  "Zagrzeb",  "XIX w.",  "Melaniny",  "1609",  "1666",  "XVIII w.",  "Œmieræ Marilyn Monroe",  "25 maja",  "1947-1949", };
	string f1[10]{ "Psa","Dubrownik","XX w.", "Melatoniny", "1605", "1565", "XVII w.", "Zamach na prezydenta Kennedy'ego", "30 maja", "1945-1947", };
	string f2[10]{ "Królika","Zadar","XVII w.", "Keratyny", "1600", "1536", "I w. p. n. e.", "L¹dowanie na Ksiê¿ycu", "14 maja", "1950-1952", };
	string f3[10]{ "Papugi","Split","XVIII w.", "Prolaktyny", "1608", "1685", "II w. p. n. e.", "Pierwszy koncert The Beatles w Stanach Zjednoczonych", "28 kwietnia", "1955-1957", };
	string f4[10]{ "Chomika","Pula","XXVI w.", "Melanostatyna", "1606", "1657", "III w. p. n. e.", "Œmieræ Winstona Churchilla", "23 kwietnia", "1957-1959", };
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
		cout << "Zdobyta suma pieniêdzy: 75 000z³. Kwota gwarantowana: 40 000z³" << endl << endl;
		cout << endl << "Ko³a ratunkowe: " << kolaRatunkowe << endl << endl << "Pytanie 9: "<< Pytanie[losPytanie] << endl;
		

		for (int i = 0; i < 4; i++)
		{
			cout << abcd[i] << ") ";
			cout << tab[i] << endl;
		}
		if (kolaRatunkowe != 0)
		{
			cout << endl << "Wybierz 'k', aby u¿yæ ko³a ratunkowego 50/50. Nie bêdziesz móg³ potem u¿yæ ko³a 'Zmiana pytania'." << endl;
			cout << "Wybierz 'l', aby u¿yæ ko³a ratunkowego 'Zmiana pytania'. Mo¿esz go u¿yæ wielokrotnie i u¿yæ ko³a 50/50" << endl;
		}
		cout << endl << "Podaj odpowiedŸ: ";
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
					cout << "Zdobyta suma pieniêdzy: 75 000z³. Kwota gwarantowana: 40 000z³" << endl << endl;
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
					cout << endl << "Podaj odpowiedŸ: ";
					cin >> odpowiedz;

					if (odpowiedz == 'a' || odpowiedz == 'A')
						zamiana = 0;
					else if (odpowiedz == 'b' || odpowiedz == 'B')
						zamiana = 1;
					else if (odpowiedz == 'k' || odpowiedz == 'K')
					{
						zamiana = 5;
						cout << " Ju¿ u¿y³eœ ko³a ratunkowego, spróbuj ponownie!" << endl;
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
				cout << "Nie masz ju¿ kó³ ratunkowych!" << endl;
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
				cout << "Nie masz ju¿ kó³ ratunkowych!";
				Sleep(2000);
				system("cls");
				goto pytanie;
			}
		}
		else
			zamiana = 5;

		if (zamiana == prawidlowa)
		{
			cout << endl << "Dobra odpowiedŸ!" << endl << endl;
			zwyciestwa++;
		}
		else if (zamiana == 5)
			cout << "Nie ma takiej odpowiedzi! Spróbuj ponownie" << endl;
		else
		{
			cout << endl << "Z³a odpowiedŸ!" << endl << endl;
			cout << "Poprawna odpowiedŸ: " << pr[losPytanie] << endl;
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
	string Pytanie[10]{ "Monachomachia to poemat heroikomiczny o wojnie mnichów autorstwa:","Jaki stan amerykañski jako pierwszy zadeklarowa³ secesjê z Unii w 1860 roku?","Który z tych szczytów nie znajduje siê w Tatrach?","Co oznacza skrót RPP?","Która z tych wysp nie nale¿y do Wysp Kanaryjskich?","Jedna z g³ównych ulic warszawskiego Œrodmieœcia, przechodz¹ca bezpoœrednio w Krakowskie Przedmieœcie, to:","Poprawnym zapisem jest:","'Upiêr w operze' to dzie³o: ","Auguste Rodin to francuski:","Które Afrykaœskie pañstwo jest najludniejsze?" };
	int prawidlowa = odp(generator);
	int licznik = 0, fifty_fifty;
	int los, zamiana, bylo[4]{ 5,5,5,5 };
	char abcd[4]{ 'a','b','c','d' };
	string pr[10]{ "Ignacego Krasickiego",  "Karolina Po³udniowa",  "Œnie¿nik",  "Rada Polityki Pieniê¿nej",  "Lesbos",  "Nowy Œwiat",  "Znienacka",  "Andrew Lloyda Webbera",  "RzeŸbiarz",  "Nigeria", };
	string f1[10]{ "Aleksandra Fredry","Nowy Jork","Gerlach", "Rada Polityki Polskiej", "Lanzarote", "Marsza³kowska", "Z nienacka", "Wolfganga Amadeusza Mozarta", "Malarz", "Kenia", };
	string f2[10]{ "Jana Kochanowskiego","Waszyngton","Krywan", "Rada Polityki Pañstwowej", "Lobos", "Aleje Jerozolimskie", "Znienadzka", "Stanis³awa Moniuszki", "Pisarz", "RPA", };
	string f3[10]{ "Juliana Ursyna Niemcewicza","Dakota Pó³nocna","Koœcielec", "Rada Polskiej Przedsiêbiorczoœci", "Teneryfa", "Grojecka", "Z nienadzka", "Fryderyka Chopina", "Kompozytor", "Mozambik", };
	string f4[10]{ "Adama Mickiewicza","Georgia","£omnica", "Rada Pañstwa Polskiego", "La Palma", "Œródmiejska", "Z nie nacka", "Ignacego Paderewskiego", "Aktor", "Namibia", };
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
		cout << "Zdobyta suma pieniêdzy: 125 000z³. Kwota gwarantowana: 40 000z³" << endl << endl;
		cout << endl << "Ko³a ratunkowe: " << kolaRatunkowe << endl << endl << "Pytanie 10: " << Pytanie[losPytanie] <<endl;
		
		for (int i = 0; i < 4; i++)
		{
			cout << abcd[i] << ") ";
			cout << tab[i] << endl;
		}
		if (kolaRatunkowe != 0)
		{
			cout << endl << "Wybierz 'k', aby u¿yæ ko³a ratunkowego 50/50. Nie bêdziesz móg³ potem u¿yæ ko³a 'Zmiana pytania'." << endl;
			cout << "Wybierz 'l', aby u¿yæ ko³a ratunkowego 'Zmiana pytania'. Mo¿esz go u¿yæ wielokrotnie i u¿yæ ko³a 50/50" << endl;
		}
		cout << endl << "Podaj odpowiedŸ: ";
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
					cout << "Zdobyta suma pieniêdzy: 125 000z³. Kwota gwarantowana: 40 000z³" << endl << endl;
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
					cout << endl << "Podaj odpowiedŸ: ";
					cin >> odpowiedz;

					if (odpowiedz == 'a' || odpowiedz == 'A')
						zamiana = 0;
					else if (odpowiedz == 'b' || odpowiedz == 'B')
						zamiana = 1;
					else if (odpowiedz == 'k' || odpowiedz == 'K')
					{
						zamiana = 5;
						cout << " Ju¿ u¿y³es ko³a ratunkowego, spróbuj ponownie!" << endl;
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
				cout << "Nie masz ju¿ kó³ ratunkowych!" << endl;
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
				cout << "Nie masz ju¿ kó³ ratunkowych!";
				Sleep(2000);
				system("cls");
				goto pytanie;
			}
		}
		else
			zamiana = 5;

		if (zamiana == prawidlowa)
		{
			cout << endl << "Dobra odpowiedŸ!" << endl << endl;
			zwyciestwa++;
		}
		else if (zamiana == 5)
			cout << "Nie ma takiej odpowiedzi! Spróbuj ponownie" << endl;
		else
		{
			cout << endl << "Z³a odpowiedŸ!" << endl << endl;
			cout << "Poprawna odpowiedŸ: " << pr[losPytanie] << endl;
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
	string Pytanie[10]{ "W oryginalnej trylogii 'Gwiezdne wojny' 3-CPO ma srebrn¹: ","W której ksi¹¿ce pojawia sie postaæ Winstona Smitha?","Która z tych liczb jest wynikiem dzia³ania '5!'?","Ichtiologia to nauka o:","Grupa instrumentów muzycznych w których Ÿród³em dŸwiêku jest cia³o sta³e maj¹ce niezmienn¹, naturaln¹ sprê¿ystoœæ, to:","Dokoñcz przys³owie 'Deszcze listopadowe...'","Wêgierski taniec narodowy, to:","Kto stworzy³ fikcyjn¹ postaæ Josefa Szwejka w antywojennej powieœci „Przygody dobrego wojaka Szwejka”?","Autorem obrazu 'Mleczarka' jest:","Kumys powstaje w wyniku fermentacji mleka:" };
	int prawidlowa = odp(generator);
	int licznik = 0, fifty_fifty;
	int los, zamiana, bylo[4]{ 5,5,5,5 };
	char abcd[4]{ 'a','b','c','d' };
	string pr[10]{ "Praw¹ nogê",  "Rok 1984",  "120",  "Rybach",  "Idiofony",  "budz¹ wiatry zimowe",  "Czardasz",  "Jaroslav Hasek",  "Jan Vermeer",  "Koñskiego", };
	string f1[10]{ "Praw¹ rêkê","Proces","5", "Pszczo³ach", "Aerofony", "wró¿¹ upa³y marcowe", "Trepak", "Karel Capek", "Peter Paul Rubens", "Oœlego", };
	string f2[10]{ "G³owê","Fahrenheit 451","25", "Wulkanach", "Chordofony", "wró¿¹ k³opoty drogowe", "Kozak", "Stanis³aw Kostka Neumann", "Rembrandt van Rijn", "Krowiego", };
	string f3[10]{ "Szczêkê","Solaris","3125", "Lasach", "Membranofony", "œci¹gaj¹ chmury œniegowe", "Hajduk", "Julius Fucik", "Frans Hals", "KoŸlego", };
	string f4[10]{ "Klatkê piersiow¹","Moskva","125", "Morzach i oceanach", "Instrumenty perkusyjne", "wró¿¹ œwiêta bezœniegowe", "Syrba", "Lubomir Benes", "Nicolaes Maes", "Owczego", };
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
		cout << "Zdobyta suma pieniêdzy: 250 000z³. Kwota gwarantowana: 40 000z³" << endl << endl;
		cout << endl << "Ko³a ratunkowe: " << kolaRatunkowe << endl << endl << "Pytanie 11: " << Pytanie[losPytanie] <<endl;
		
		for (int i = 0; i < 4; i++)
		{
			cout << abcd[i] << ") ";
			cout << tab[i] << endl;
		}
		if (kolaRatunkowe != 0)
		{
			cout << endl << "Wybierz 'k', aby u¿yæ ko³a ratunkowego 50/50. Nie bêdziesz móg³ potem u¿yæ ko³a 'Zmiana pytania'." << endl;
			cout << "Wybierz 'l', aby u¿yæ ko³a ratunkowego 'Zmiana pytania'. Mo¿esz go u¿yæ wielokrotnie i u¿yæ ko³a 50/50" << endl;
		}
		cout << endl << "Podaj odpowiedŸ: ";
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
					cout << "Zdobyta suma pieniêdzy: 250 000z³. Kwota gwarantowana: 40 000z³" << endl << endl;
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
					cout << endl << "Podaj odpowiedŸ: ";
					cin >> odpowiedz;

					if (odpowiedz == 'a' || odpowiedz == 'A')
						zamiana = 0;
					else if (odpowiedz == 'b' || odpowiedz == 'B')
						zamiana = 1;
					else if (odpowiedz == 'k' || odpowiedz == 'K')
					{
						zamiana = 5;
						cout << " Ju¿ u¿y³eœ ko³a ratunkowego, spróbuj ponownie!" << endl;
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
				cout << "Nie masz ju¿ kó³ ratunkowych!" << endl;
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
				cout << "Nie masz ju¿ kó³ ratunkowych!";
				Sleep(2000);
				system("cls");
				goto pytanie;
			}
		}
		else
			zamiana = 5;

		if (zamiana == prawidlowa)
		{
			cout << endl << "Dobra odpowiedŸ!" << endl << endl;
			zwyciestwa++;
		}
		else if (zamiana == 5)
			cout << "Nie ma takiej odpowiedzi! Spróbuj ponownie" << endl;
		else
		{
			cout << endl << "Z³a odpowiedŸ!" << endl << endl;
			cout << "Poprawna odpowiedŸ: " << pr[losPytanie] << endl;
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
	string Pytanie[10]{ "Co na Ksiê¿ycu zrobi³ Alan Shepard?","Ile edycji Miêdzynarodowego Konkursu Pianistycznego im. Fryderyka Chopina odby³o sie do 2016 r.?","Ile wynosi rekord dni bez snu?","Œrednia d³ugoœæ jelita cienkiego wynosi:","Jak nazwano najstarsz¹, znan¹ pramatkê cz³owieka?","KMnO4 to wzór","Kto jest autorem obrazu 'Adele Bloch - Bauer I'?","Grupa funkcyjna -COOH jest charakterystyczna dla:","Ile razy Franklin Roosevelt pe³ni³ kadencjê prezydenck¹?","Hrabina Natasza Rostowa jest g³ówn¹ bohaterk¹ powieœci:" };
	int prawidlowa = odp(generator);
	int licznik = 0, fifty_fifty;
	int los, zamiana, bylo[4]{ 5,5,5,5 };
	char abcd[4]{ 'a','b','c','d' };
	string pr[10]{ "Zagra³ w golfa",  "17",  "11",  "5-6 m",  "Lucy",  "Nadmanganianu potasu",  "Gustav Klimt",  "Kwasów karboksylowych",  "4",  "Wojna i pokój", };
	string f1[10]{ "Zaœpiewa³","40","20", "2-3 m", "Bella", "Chlorku potasu", "Edward Munch", "Alkoholi", "1", "Zbrodnia i kara", };
	string f2[10]{ "Zrobi³ kilka pajacyków","25","4", "10-11 m", "Fiona", "P³ynu Lugola", "Claude Monet", "Estrów", "2", "Anna Karenina", };
	string f3[10]{ "Zatañczyl","10","9", "7-8 m", "Amy", "Sody oczyszczonej", "Henri Matisse", "Soli", "3", "Eugeniusz Oniegin", };
	string f4[10]{ "Rzuci³ frisbee","20","10", "17-18 m", "Holy", "Cieczy nienutonowskiej", "Salvador Dali", "Zasad", "5", "Granica", };
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
		cout << "Zdobyta suma pieniêdzy: 500 000z³. Kwota gwarantowana: 40 000z³" << endl << endl;
		cout << endl << "Ko³a ratunkowe: " << kolaRatunkowe << endl << endl << "Pytanie 12: " << Pytanie[losPytanie] <<endl;
		
		for (int i = 0; i < 4; i++)
		{
			cout << abcd[i] << ") ";
			cout << tab[i] << endl;
		}
		if (kolaRatunkowe != 0)
		{
			cout << endl << "Wybierz 'k', aby u¿yæ ko³a ratunkowego 50/50. Nie bêdziesz móg³ potem u¿yæ ko³a 'Zmiana pytania'." << endl;
			cout << "Wybierz 'l', aby u¿yæ ko³a ratunkowego 'Zmiana pytania'. Mo¿esz go u¿yæ wielokrotnie i u¿yæ ko³a 50/50" << endl;
		}
		cout << endl << "Podaj odpowiedŸ: ";
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
					cout << "Zdobyta suma pieniêdzy: 500 000z³. Kwota gwarantowana: 40 000z³" << endl << endl;
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
					cout << endl << "Podaj odpowiedŸ: ";
					cin >> odpowiedz;

					if (odpowiedz == 'a' || odpowiedz == 'A')
						zamiana = 0;
					else if (odpowiedz == 'b' || odpowiedz == 'B')
						zamiana = 1;
					else if (odpowiedz == 'k' || odpowiedz == 'K')
					{
						zamiana = 5;
						cout << " Ju¿ u¿y³eœ ko³a ratunkowego, spróbuj ponownie!" << endl;
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
				cout << "Nie masz ju¿ kó³ ratunkowych!" << endl;
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
				cout << "Nie masz ju¿ kó³ ratunkowych!";
				Sleep(2000);
				system("cls");
				goto pytanie;
			}
		}
		else
			zamiana = 5;

		if (zamiana == prawidlowa)
		{
			cout << endl << "Dobra odpowiedŸ!" << endl << endl;
			zwyciestwa++;
		}
		else if (zamiana == 5)
			cout << "Nie ma takiej odpowiedzi! Spróbuj ponownie" << endl;
		else
		{
			cout << endl << "Z³a odpowiedŸ!" << endl << endl;
			cout << "Poprawna odpowiedŸ: " << pr[losPytanie] << endl;
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
			cout << "Historia jest pusta, zagraj, ¿eby dodaæ wynik!\n";
		}
		 
		else {Historia.seekg(0, ios::beg);
			while (!Historia.eof())
			{
				getline(Historia, pobranie);
				dlugosc = pobranie.size();// d³ugoœæ nazwy u¿ytkownika
				if (pobranie[dlugosc - 2] == ' ')//wynik 1-cyfrowy
				{
					zwyciestwo = pobranie.substr(dlugosc - 1);// oddzielenie wyniku i zapisanie do stringa
					wynik[indeks] = stoi(zwyciestwo);//zmienienie stringa na inta i wpisanie do tablicy wyników
					uzytkownik[indeks] = pobranie.substr(0, dlugosc - 1);// oddzielenie nazwy u¿ytkownika i zapisaniedo tablicy
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
		cout << "Nie mo¿na otworzyæ pliku" << endl;
	Historia.close();
	int numeracja=1;
	int NajdluzszyUzytkownik = 0;// najdlu¿sza nazwa u¿ytkownika 
	for (int i = 0; i < indeks; i++)
	{
		if (NajdluzszyUzytkownik < uzytkownik[i].size())
			NajdluzszyUzytkownik = uzytkownik[i].size();

	}
	for (int i = indeks-1; i >=0; i--)// wypisanie w takie sposób, ¿eby wyniki by³y równo
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
		while (CzyChceGrac)// pêtla wykonuje siê dpóki u¿ytkownik chce kontynuowac grê
		{
			

			uzytkownik = "";
			while (uzytkownik.size() == 0)
			{
				system("cls");
				cout << "Podaj nazwê u¿ytkownika (bez polskich znaków): ";
				getline(cin, uzytkownik);//pobranie nazwy u¿ytkownika
				
			}
			
			
			Sleep(1000);
			system("cls");

			Historia.seekg(0, ios::end);
			if (Historia.tellg() == 0) 
			{
			Historia << uzytkownik;//zapisanie u¿ytkownika do pliku
				
			}
			else
			{
				Historia << endl << uzytkownik;//zapisanie u¿ytkownika do pliku
			}
			pyt1();
			while (porazki < 2)// pêtla siê wykonuje a¿ pora¿ki nie wynios¹ 1 wtedy wyœwietla siê komunikat o koñcu gry
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
						cout << "Nic nie wygra³eœ!" << endl;
					else if (zwyciestwa < 7)
					{
						cout << "Wygra³eœ 1000 z³!" << endl;
					}
					else if (zwyciestwa >= 7)
					{
						cout << "Wygra³eœ 40 000 z³!" << endl;
					}
					porazki = 2;
				}
				else if (zwyciestwa == 12)
				{
					cout << "Gratulacje! Wygra³eœ milion!" << endl;
					porazki = 2;
				}
			}

			getline(cin, czychcegrac);// pozbycie siê \n w buforze

			while (checGry == 1)// pêtla wykonuje siê tak d³ugo, a¿ u¿ytkownik poda jedn¹ z oczekiwanych odpowiedzi
			{
				cout << endl << "Czy chcesz zagraæ jeszcze raz?" << endl << "Wpisz 'tak' lub 'nie': " << endl;
				getline(cin, czychcegrac);// czy u¿ytkonik chce dalej graæ
				if (czychcegrac == "tak" || czychcegrac == "Tak" || czychcegrac == "tAk" || czychcegrac == "taK" || czychcegrac == "TAk" || czychcegrac == "tAK" || czychcegrac == "TAK" || czychcegrac == "TaK")
				{
					checGry++;//CzyChceGrac pozostaje true
				}
				else if (czychcegrac == "nie" || czychcegrac == "Nie" || czychcegrac == "nIe" || czychcegrac == "niE" || czychcegrac == "NIe" || czychcegrac == "nIE" || czychcegrac == "NIE" || czychcegrac == "NiE")
				{
					CzyChceGrac = false;//pêtla gry siê przerywa
					checGry++;

				}
				else
				{
					cout << "Nie rozumiem, spróbuj ponownie: " << endl;
					Sleep(2000);
					system("cls");
				}
			}


			Historia << ":  " << zwyciestwa;//dopisanie wyniku do nazwy u¿ytkownika
			checGry = 1;
			porazki = 0;
			zwyciestwa = 0;
			kolaRatunkowe = 3;// ustawienie wszytskiego na wartoœæ domyœln¹
		}
		Historia.close();
		system("cls");
		cout << endl << "Dziêkujê za grê!" << endl;
		Sleep(2000);
		system("cls");
	}
char Menu()// pobranie decyzji u¿ytkownika
{
	
	char decyzja;
	//cout << "Co chcesz zrobiæ? \n\nWpisz 1, aby zagraæ.\nWpisz 2, aby wyœwietliæ historiê gier.\nWpisz 3, aby wyœwietliæ zasady.\nWpisz 4, aby wyœwietliæ top 10 graczy.\nWpisz 5, aby zakoñczyæ." << endl;
	decyzja = _getch();
	return decyzja;
	
}
void Zasady()//wyœwietlenie zasad gry
{
	cout << "Zasady s¹ bardzo proste:" << endl << "1. Jest 12 losowych pytañ, ka¿de kolejne jest trudniejsze od poprzedniego" << endl;
	cout << "2. Za ka¿d¹ poprawn¹ odpowiedŸ otrzymuje siê coraz wiêksz¹ kwotê. Jest te¿ kwota gwarantowana, któr¹ otrzymuje siê po przegranej." << endl;
	cout << "3. Do dyspozycji s¹ dwa ko³a ratunkowe: 50/50 oraz 'Zamiana pytania'. Pierwsze wyœwietla jedn¹ odpowiedŸ poprawn¹ i jedn¹ fa³szyw¹. Drugie losuje inne pytanie" << endl;
	cout << "4. £¹cznie kó³ ratunkowych mo¿na u¿yæ 3 razy, jednak u¿ycie 50/50 uniemo¿liwia u¿ycie go ponownie w tym samym pytaniu lub wylosowanie innego." << endl;
	cout << "5. Zamiany pytania mo¿na u¿yæ wielokrotnie, dopóki dostêpne s¹ ko³a ratunkowe" << endl;
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
			cout << "Historia jest pusta, zagraj, ¿eby dodaæ wynik!\n";
		}

		else
		{
		while (!Historia.eof())
		{
			getline(Historia, pobranie);
			dlugosc = pobranie.size();// d³ugoœæ nazwy u¿ytkownika
			if(pobranie[dlugosc -2]== ' ')//wynik 1-cyfrowy
			{
				zwyciestwo = pobranie.substr(dlugosc - 1);// oddzielenie wyniku i zapisanie do stringa
				wynik[indeks] = stoi(zwyciestwo);//zmienienie stringa na inta i wpisanie do tablicy wyników
				uzytkownik[indeks] = pobranie.substr(0, dlugosc - 1);// oddzielenie nazwy u¿ytkownika i zapisaniedo tablicy
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
		cout << "Nie mo¿na otworzyæ pliku" << endl;
	Historia.close();

	int zamiana;
	string zam;
	bool czyPokolei = false;
	while (czyPokolei == false)//sortowanie u¿ytkowników i ich wyników
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
	int NajdluzszyUzytkownik = 0;// najdlu¿sza nazwa u¿ytkownika 
	for (int i = 0; i < indeks; i++)
	{
		if (NajdluzszyUzytkownik < uzytkownik[i].size())
			NajdluzszyUzytkownik = uzytkownik[i].size();

	}
	for (int i = 0; i < indeks; i++)// wypisanie w takie sposób, ¿eby wyniki by³y równo
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
	cout << "ÛÛÛ»°°°ÛÛÛ»ÛÛ»ÛÛ»°°°°°ÛÛ»°ÛÛÛÛÛ»°ÛÛÛ»°°ÛÛ»ÛÛÛÛÛÛÛ»ÛÛÛÛÛÛ»°ÛÛÛÛÛÛÛ»ÛÛ»°°°ÛÛ»ÛÛ»" << endl;//wielki napis Milionerzy
	cout << "ÛÛÛÛ»°ÛÛÛÛºÛÛºÛÛº°°°°°ÛÛºÛÛÉÍÍÛÛ»ÛÛÛÛ»°ÛÛºÛÛÉÍÍÍÍ¼ÛÛÉÍÍÛÛ»ÈÍÍÍÍÛÛºÈÛÛ»°ÛÛÉ¼ÛÛº" << endl;
	cout << "ÛÛÉÛÛÛÛÉÛÛºÛÛºÛÛº°°°°°ÛÛºÛÛº°°ÛÛºÛÛÉÛÛ»ÛÛºÛÛÛÛÛ»°°ÛÛÛÛÛÛÉ¼°°ÛÛÛÉÍ¼°ÈÛÛÛÛÉ¼°ÛÛº" << endl;
	cout << "ÛÛºÈÛÛÉ¼ÛÛºÛÛºÛÛº°°°°°ÛÛºÛÛº°°ÛÛºÛÛºÈÛÛÛÛºÛÛÉÍÍ¼°°ÛÛÉÍÍÛÛ»ÛÛÉÍÍ¼°°°°ÈÛÛÉ¼°°ÈÍ¼" << endl;
	cout << "ÛÛº°ÈÍ¼°ÛÛºÛÛºÛÛÛÛÛÛÛ»ÛÛºÈÛÛÛÛÛÉ¼ÛÛº°ÈÛÛÛºÛÛÛÛÛÛÛ»ÛÛº°°ÛÛºÛÛÛÛÛÛÛ»°°°ÛÛº°°°ÛÛ»" << endl;
	cout << "ÈÍ¼°°°°°ÈÍ¼ÈÍ¼ÈÍÍÍÍÍÍ¼ÈÍ¼°ÈÍÍÍÍ¼°ÈÍ¼°°ÈÍÍ¼ÈÍÍÍÍÍÍ¼ÈÍ¼°°ÈÍ¼ÈÍÍÍÍÍÍ¼°°°ÈÍ¼°°°ÈÍ¼" << endl;
	
	setlocale(LC_CTYPE, "Polish");//ustawienie polskiego jêzyka (polskie znaki)

	cout << endl << endl << "Naciœnij dowolny przycisk aby rozpocz¹æ!" << endl;
	char h;
	h=_getch();
	
	system("cls");
	
	bool dziala = true;
	while (dziala) //nieskoñczona pêtla, koñczy j¹ switch -> case 5
	{
		powrót:
		cout << "Co chcesz zrobiæ? \n\nWpisz 1, aby zagraæ.\nWpisz 2, aby wyœwietliæ zasady.\nWpisz 3, aby wyœwietliæ historiê gier.\nWpisz 4, aby wyœwietliæ top 10 graczy.\nWpisz 5, aby zakoñczyæ." << endl;

	menu:
			decyzja = Menu();//decyzja u¿ytkownika
			
			if (decyzja >= 49 && decyzja <= 53)
			{
				switch (decyzja)
				{
				case '1':
					
					Gra();//rozpoczêcie gry
					break;
				case '3':
					
					system("cls");//wypisanie historii gier
					historia();
					cout << "\nNaciœnij ENTER aby wyjœæ\n";
					while (1)
					{
						if (_getch() == 13)
						{
							system("cls");
							
							goto powrót;
						}
					}
				case '2':
					
					system("cls");//wyœwietlenie zasad
					Zasady();
					cout << "\nNaciœnij ENTER aby wyjœæ\n";
					while (1)
					{
						if (_getch() == 13)
						{
							system("cls");
							
							goto powrót;
						}
					}
				case '4':
					
					system("cls");//wyœwietlenie 10 najlepszych wyników
					top10();
					cout << "\nNaciœnij ENTER aby wyjœæ\n";
					while (1)
					{
						if (_getch() == 13)
						{
							system("cls");
							
							goto powrót;
						}
					}
				case '5'://zamkniêcie programu
					decyzja = 0;
					exit(0);
				}
			}
			else
				goto menu;
				
			
		
	}

	system("pause");
}
