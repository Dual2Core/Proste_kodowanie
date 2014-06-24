#include <iostream>
#include <string>

#define WERSJA 1

#define SZYFRUJ_DOMYSLNIE szyfrowanie_rekurencyjne(tekst, metoda) 
#define NIEZASZYFROWANY tekst_przed_zaszyfrowaniem
#define ZASZYFROWANY tekst
using namespace std;

void szyfrowanie_rekurencyjne(string &tekst_szyfrowany, int metoda_szyfrowania=1)
{
	static int a;
	tekst_szyfrowany.at(a)+=metoda_szyfrowania;

#if (WERSJA == 1)
	cout<<"Pole a wynosi: \t"<<a<<endl;
	cout<<"Metoda szyfrowania wynosi: \t"<<metoda_szyfrowania<<endl;
#endif

	a++;

	if( a < (tekst_szyfrowany.size() / 2) )
	{
		metoda_szyfrowania++;
		szyfrowanie_rekurencyjne(tekst_szyfrowany, metoda_szyfrowania);
	}
tekst_szyfrowany.at(a)+=metoda_szyfrowania;

#if (WERSJA == 1)
	cout<<"Pole a wynosi: \t"<<a<<endl;
	cout<<"Metoda szyfrowania wynosi: \t"<<metoda_szyfrowania<<endl;
#endif

	a++;
	
	return;
}

int main()
{
	int metoda;
	string tekst, tekst_przed_zaszyfrowaniem;
	cout<<"Wpisz tekst do zakodowania: ";
	getline(cin, tekst);
	if(cin.good())cout<<"Tekst zaladowany pomyslnie!"<<endl;
	else 
	{
		cout<<"Wystapil blad podczas ladowania tekstu!";
	}
	cout<<"Wpisz metode szyfrowania (przesuniecie ASCII): ";
	cin>>metoda;
	
	NIEZASZYFROWANY=tekst;
	
	cout<<"Rozpoczynam szyfrowanie..."<<endl;
	
	SZYFRUJ_DOMYSLNIE;
	
	cout<<"Niezaszyfrowany wyraz:\t"<<NIEZASZYFROWANY<<endl;
	cout<<"Zaszyfrowany wyraz:\t"<<ZASZYFROWANY<<endl;
	
	
	
}
