#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

#define WERSJA 1  // 1 dla wersji testowych, 2 dla wersji oficjalnej

#define SZYFRUJ_DOMYSLNIE szyfrowanie_rekurencyjne(tekst, metoda)
#define OBLICZ_KIERUNKI szyfrowanie_rekurencyjne(kierunki, metoda, 0, 0, 1) 
#define NIEZASZYFROWANY tekst_przed_zaszyfrowaniem
#define ZASZYFROWANY tekst
#define POZA_ZAKRESEM znak<48 || znak>57 && znak<65 || znak>90 && znak<97 || znak>122
using namespace std;

bool group_HIGH( char symbol )
{
	int zakres[6] = {'`','_','^',']','\\','['};
	for(int i=0;i<6;i++)
	{
		if(symbol==zakres[i])
			return true;
	}
	return false;
}

bool group_LOW( char symbol )
{
	int zakres[7] = {'@','?','>','=','<',';',':'};
	for(int i=0;i<7;i++)
	{
		if(symbol==zakres[i])
			return true;
	}
	return false;
}

void szyfrowanie_rekurencyjne(string &tekst_szyfrowany, const int metoda_szyfrowania, int miejsce_szyfrowane=0, int przesuniecie=0, int tryb=0)
{
    if(miejsce_szyfrowane==0)przesuniecie=metoda_szyfrowania;
	
	int dlugosc_szyfrowanego_tekstu = tekst_szyfrowany.size();
	
	if(miejsce_szyfrowane>=dlugosc_szyfrowanego_tekstu)
        return;
	
	
#if (WERSJA == 1)
		cout<<"Kod ASCII znaku NIEzaszyfrowanego: "<<static_cast <int> (tekst_szyfrowany[miejsce_szyfrowane])<<endl;
#endif

    /*--------------------------------Modul szyfrujacy----------------------------------*/
	
	    
    int znak = tekst_szyfrowany[miejsce_szyfrowane] + przesuniecie;
    if(tekst_szyfrowany[miejsce_szyfrowane]<58 && znak>64 && znak<91)znak+=7;
	else
    if(tekst_szyfrowany[miejsce_szyfrowane]<58 && znak>96)znak+=13;
    else
    if(tekst_szyfrowany[miejsce_szyfrowane]>64 && tekst_szyfrowany[miejsce_szyfrowane]<91 && znak>96)znak+=6;
	    
	int tendencja,kierunek=48;
    
	if(POZA_ZAKRESEM)
	for(tendencja=1;POZA_ZAKRESEM;tendencja++)
	{
		int odbicie;
		if(znak>122)
		{
			odbicie=znak-122; //znak wychodzi poza gorna granice zakresu, wartosc ekstra jest "obcinana" jako odbicie
			//cout<<"Odbicie od osi x w dol wynosi: "<<odbicie<<endl;
			znak=122-odbicie; //wartosc jest odbijana wzgledem ostatniej gornej osi x wykresu
			if(odbicie<=61)kierunek=49;
			//cout<<"znak wynosi: "<<znak<<endl;
			if(group_LOW(znak) || znak<58)znak-=13;
			else
			if(group_HIGH(znak) || znak<91)znak-=6;
			else
			if(znak<48)znak-=13;
			//cout<<"a teraz znak wynosi: "<<znak<<endl;
		}
		else
		if(znak<48)
		{
			odbicie=48-znak; //znak wychodzi poza dolna granice zakresu, wartosc ekstra jest "obcinana" jako odbicie
			//cout<<"Odbicie od osi x w gore wynosi: "<<odbicie<<endl;
			znak=48+odbicie; //wartosc jest odbijana wzgledem ostatniej dolnej osi x wykresu
			if(odbicie<=61)kierunek=48;
			if(group_HIGH(znak) || znak>96)znak+=13;
			else
			if(group_LOW(znak) || znak>64)znak+=7;
			else
			if(znak>122)znak+=13;
		}
		else
		{
			if(tendencja%2==0)
			{
				if(group_HIGH(znak))znak-=6;
				else
				if(group_LOW(znak))znak-=7;
			}
			else
			if(tendencja%2!=0)
			{
				if(group_HIGH(znak))znak+=6;
				else
				if(group_LOW(znak))znak+=7;
			}
		}
		
	}
	
	if(tryb==0)
	tekst_szyfrowany[miejsce_szyfrowane]=znak;
	else
	if(tryb==1)
	tekst_szyfrowany[miejsce_szyfrowane]=kierunek;
	
#if (WERSJA == 1)
		cout<<"Kod ASCII znaku zaszyfrowanego: "<<znak<<endl;
#endif
	
	
	/*----------------------------------------------------------------------------------*/

#if (WERSJA == 1)
	cout<<"Pole szyfrowane wynosi: \t"<<miejsce_szyfrowane<<endl;
	cout<<"Przesuniecie wynosi: \t"<<przesuniecie<<endl;
	cout<<"Tendencja wynosi: \t"<<tendencja<<endl<<endl;
#endif
	
	if( miejsce_szyfrowane < dlugosc_szyfrowanego_tekstu/2 )
    {
    	szyfrowanie_rekurencyjne(tekst_szyfrowany, metoda_szyfrowania, miejsce_szyfrowane+1, przesuniecie+metoda_szyfrowania, tryb);
	}
	else
	{
	   szyfrowanie_rekurencyjne(tekst_szyfrowany, metoda_szyfrowania, miejsce_szyfrowane+1, przesuniecie-metoda_szyfrowania, tryb);
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
	string kierunki=tekst;
	
	cout<<"Rozpoczynam szyfrowanie..."<<endl;
	
	SZYFRUJ_DOMYSLNIE;
	OBLICZ_KIERUNKI;
	
	
	cout<<"Niezaszyfrowany wyraz:\t"<<NIEZASZYFROWANY<<endl;
	cout<<"Zaszyfrowany wyraz:\t"<<ZASZYFROWANY<<endl;
	cout<<"Kierunki do zaszyfrowanego:\t"<<kierunki<<endl;
	
	cin.sync();
	
	fstream plik("crypted.txt",ios::out);
	if(plik.is_open())cout<<"Utworzono pomyslnie plik z zaszyfrowanym ciagiem znakow!"<<endl;
	else 
	cout<<"Wystapil blad podczas tworzenia/zapisu do pliku!"<<endl;
	plik<<ZASZYFROWANY<<endl;
	plik<<kierunki;
	cout<<"Zaszyfrowany ciag pomyslnie zapisany do pliku \"crypted.txt\""<<endl;
	system("pause");
	goto onemoretime;
	
}
