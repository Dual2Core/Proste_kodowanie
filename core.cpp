#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

#define WERSJA 1  // 1 dla wersji testowych, 2 dla wersji oficjalnej

#define SZYFRUJ_DOMYSLNIE szyfrowanie_rekurencyjne(tekst, metoda) 
#define NIEZASZYFROWANY tekst_przed_zaszyfrowaniem
#define ZASZYFROWANY tekst
#define POZA_ZAKRESEM znak<48 || znak>57 && znak<65 || znak>90 && znak<97 || znak>122
using namespace std;

void szyfrowanie_rekurencyjne(string &tekst_szyfrowany, const int metoda_szyfrowania, int miejsce_szyfrowane=0, int przesuniecie=0)
{
    if(miejsce_szyfrowane==0)przesuniecie=metoda_szyfrowania;
	
	int dlugosc_szyfrowanego_tekstu = tekst_szyfrowany.size();
	
	if(miejsce_szyfrowane>=dlugosc_szyfrowanego_tekstu)
        return;

    /*--------------------------------Modul szyfrujacy----------------------------------*/
	
	    
    int znak = tekst_szyfrowany[miejsce_szyfrowane] + przesuniecie;
    
	if(POZA_ZAKRESEM)
	for(int tendencja=1;POZA_ZAKRESEM;tendencja++)
	{
		int odbicie;
		if(znak>122)
		{
			odbicie=znak-122; //znak wychodzi poza gorna granice zakresu, wartosc ekstra jest "obcinana" jako odbicie
			znak=122-odbicie; //wartosc jest odbijana wzgledem ostatniej gornej osi x wykresu
		}
		else
		if(znak<48)
		{
			odbicie=48-znak; //znak wychodzi poza dolna granice zakresu, wartosc ekstra jest "obcinana" jako odbicie
			znak=48+odbicie; //wartosc jest odbijana wzgledem ostatniej dolnej osi x wykresu
		}
		else
		{
			if(tendencja%2==0) // jesli tendencja jest parzysta, czyli funkcja jest rosnaca i jest poza zakresem (ale w szerokim zakresie jest)
			while(POZA_ZAKRESEM)znak--; // wartosc znaku rosnie az do osi¹gniêcia zakresu w jednym z w¹skich zakresów
			else
			if(tendencja%2!=0) // jesli tendencja jest nieparzysta, czyli funkcja jest malejaca i jest poza zakresem (ale w szerokim zakresie jest)
			while(POZA_ZAKRESEM)znak++; // wartosc znaku maleje az do osi¹gniêcia zakresu w jednym z w¹skich zakresów
		}
	}
	
	
	tekst_szyfrowany[miejsce_szyfrowane]=znak;

#if (WERSJA == 1)
	if(POZA_ZAKRESEM)
		cout<<"POZA ZAKRESEM"<<endl;
		cout<<"Kod ASCII znaku: "<<znak<<endl;
#endif
	
	
	/*----------------------------------------------------------------------------------*/

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
	onemoretime:
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
	cin.sync();
	
	fstream plik("crypted.txt",ios::out);
	if(plik.is_open())cout<<"Utworzono pomyslnie plik z zaszyfrowanym ciagiem znakow!";
	else 
	cout<<"Wystapil blad podczas tworzenia/zapisu do pliku!";
	plik<<ZASZYFROWANY;
	cout<<"Zaszyfrowany ciag pomyslnie zapisany do pliku!";
	
	goto onemoretime;
	
}
