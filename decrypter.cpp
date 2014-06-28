#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

#define WERSJA 1  // 1 dla wersji testowych, 2 dla wersji oficjalnej
#define DECRYPT_DEFAULT szyfrowanie_rekurencyjne(cryptedstring, method)


#define POZA_ZAKRESEM znak<48 || znak>57 && znak<65 || znak>90 && znak<97 || znak>122
using namespace std;

void szyfrowanie_rekurencyjne(string &tekst_szyfrowany, const int metoda_szyfrowania, int miejsce_szyfrowane=0, int przesuniecie=0)
{
    if(miejsce_szyfrowane==0)przesuniecie=metoda_szyfrowania;
	
	int dlugosc_szyfrowanego_tekstu = tekst_szyfrowany.size();
	
	if(miejsce_szyfrowane>=dlugosc_szyfrowanego_tekstu)
        return;
        
    

    /*--------------------------------Modul szyfrujacy----------------------------------*/
#if (WERSJA == 1)
	int znak_A=tekst_szyfrowany[miejsce_szyfrowane];
	cout<<"Kod ASCII zaszyfrowanego znaku:\t"<<znak_A<<"\t>>\t"<<tekst_szyfrowany[miejsce_szyfrowane]<<endl;
#endif
    
	int znak = tekst_szyfrowany[miejsce_szyfrowane] - przesuniecie;
    
	for(int tendencja=2;POZA_ZAKRESEM;tendencja++)
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
	int znak_B=tekst_szyfrowany[miejsce_szyfrowane];
	cout<<"Kod ASCII odszyfrowanego znaku:\t"<<znak_B<<"\t>>\t"<<tekst_szyfrowany[miejsce_szyfrowane]<<endl;
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
	fstream plik("crypted.txt", ios::in);
	if(plik.is_open())cout<<"Plik zaladowany pomyslnie!"<<endl;
	string cryptedstring;
	getline(plik, cryptedstring);
	int method;
	cout<<"Podaj wartosc bedaca podstawa algorytmu deszyfrujacego: ";
	cin>>method;
	cout<<endl;
	string zaszyfrowany=cryptedstring;
	
	DECRYPT_DEFAULT;
	
	cout<<"Zaszyfrowany ciag znakow:\t"<<zaszyfrowany<<endl;
	cout<<"Odszyfrowany ciag znakow:\t"<<cryptedstring<<endl<<endl;
	
	cout<<"Uzyta metoda deszyfracji: "<<method<<endl<<endl;
	
	system("pause");
	cout<<endl;
	
	goto onemoretime;
}
