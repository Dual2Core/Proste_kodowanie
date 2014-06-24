#include <iostream>
#include <string>
#include <cstdlib>

#define WERSJA 1  // 1 dla wersji testowych, 2 dla wersji oficjalnej

#define SZYFRUJ_DOMYSLNIE szyfrowanie_rekurencyjne(tekst, metoda) 
#define NIEZASZYFROWANY tekst_przed_zaszyfrowaniem
#define ZASZYFROWANY tekst
using namespace std;

void szyfrowanie_rekurencyjne(string &tekst_szyfrowany, const int metoda_szyfrowania, int miejsce_szyfrowane=0, int przesuniecie=0)
{
    if(miejsce_szyfrowane==0)przesuniecie=metoda_szyfrowania;
	
	int dlugosc_szyfrowanego_tekstu = tekst_szyfrowany.size();
	
	if(miejsce_szyfrowane>=dlugosc_szyfrowanego_tekstu)
        return;

    /*------------------Modul szyfrujacy-----------------*/    
    int znak = tekst_szyfrowany[miejsce_szyfrowane] + przesuniecie;
    tekst_szyfrowany[miejsce_szyfrowane]=znak;
#if (WERSJA == 1)
	if(znak<48 || znak>57 && znak<65 || znak>90 && znak<97 || znak>122)
		cout<<"POZA ZAKRESEM"<<endl;
#endif
	/*---------------------------------------------------*/

#if (WERSJA == 1)
	cout<<"Pole szyfrowane wynosi: \t"<<miejsce_szyfrowane<<endl;
	cout<<"Przesuniecie wynosi: \t"<<przesuniecie<<endl<<endl;
#endif
	
	if( miejsce_szyfrowane < dlugosc_szyfrowanego_tekstu/2 )
    {
    	szyfrowanie_rekurencyjne(tekst_szyfrowany, metoda_szyfrowania, miejsce_szyfrowane+1, przesuniecie+metoda_szyfrowania);
	}
	else
	{
	   szyfrowanie_rekurencyjne(tekst_szyfrowany, metoda_szyfrowania, miejsce_szyfrowane+1, przesuniecie-metoda_szyfrowania);
	}
}

int main()
{
	int metoda;
	string tekst, tekst_przed_zaszyfrowaniem;
	cout<<"Wpisz tekst do zakodowania: ";
	getline(cin, tekst);
	if(cin.good())
		cout<<"Tekst zaladowany pomyslnie!"<<endl;
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
	
	system("pause");
	
}
