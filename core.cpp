#include <iostream>
#include <string>

#define WERSJA 1

#define SZYFRUJ_DOMYSLNIE szyfrowanie_rekurencyjne(tekst, metoda) 
#define NIEZASZYFROWANY tekst_przed_zaszyfrowaniem
#define ZASZYFROWANY tekst
using namespace std;

void szyfrowanie_rekurencyjne(string &tekst_szyfrowany, int metoda_szyfrowania, int miejsce_szyfrowane=0)
{
    int dlugosc_szyfrowanego_tekstu = tekst_szyfrowany.size();
    if(miejsce_szyfrowane>=dlugosc_szyfrowanego_tekstu)
        return;
    /*------------------Modul szyfrujacy-----------------*/    
    tekst_szyfrowany[miejsce_szyfrowane] +=metoda_szyfrowania;

#if (WERSJA == 1)
	cout<<"Pole szyfrowane wynosi: \t"<<miejsce_szyfrowane<<endl;
	cout<<"Metoda szyfrowania wynosi: \t"<<metoda_szyfrowania<<endl;
#endif
	
	if( miejsce_szyfrowane < dlugosc_szyfrowanego_tekstu/2 )
       szyfrowanie_rekurencyjne(tekst_szyfrowany, metoda_szyfrowania+1, miejsce_szyfrowane+1);
    else
       szyfrowanie_rekurencyjne(tekst_szyfrowany, metoda_szyfrowania-1, miejsce_szyfrowane+1);
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
