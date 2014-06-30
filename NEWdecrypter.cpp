#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

#define WERSJA 1  // 1 dla wersji testowych, 2 dla wersji oficjalnej
#define DECRYPT_DEFAULT deszyfrowanie(cryptedstring, method)

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

int szyfrowanie_rekurencyjne(char tekst_szyfrowany, int metoda_szyfrowania)
{
    int przesuniecie=metoda_szyfrowania;

    /*--------------------------------Modul szyfrujacy----------------------------------*/
	
	    
    int znak = tekst_szyfrowany + przesuniecie;
    if(tekst_szyfrowany<58 && znak>64 && znak<91)znak+=7;
	else
    if(tekst_szyfrowany<58 && znak>96)znak+=13;
    else
    if(tekst_szyfrowany>64 && tekst_szyfrowany<91 && znak>96)znak+=6;
	    
    
	if(POZA_ZAKRESEM)
	for(int tendencja=1;POZA_ZAKRESEM;tendencja++)
	{
		int odbicie;
		if(znak>122)
		{
			odbicie=znak-122; //znak wychodzi poza gorna granice zakresu, wartosc ekstra jest "obcinana" jako odbicie
			znak=122-odbicie; //wartosc jest odbijana wzgledem ostatniej gornej osi x wykresu
			if(group_LOW(znak) || znak<58)znak-=13;
			else
			if(group_HIGH(znak) || znak<91)znak-=6;
			else
			if(znak<48)znak-=13;
		}
		else
		if(znak<48)
		{
			odbicie=48-znak; //znak wychodzi poza dolna granice zakresu, wartosc ekstra jest "obcinana" jako odbicie
			znak=48+odbicie; //wartosc jest odbijana wzgledem ostatniej dolnej osi x wykresu
			if(group_HIGH(znak) || znak>96)znak+=13;
			else
			if(group_LOW(znak) || znak>64)znak+=7;
			else
			if(znak>122)znak+=13;
		}
		else
		{
			if(group_HIGH(znak))znak+=6;
			else
			if(group_LOW(znak))znak+=7;
		}
		
	}

	/*----------------------------------------------------------------------------------*/

#if (WERSJA == 1)
	//cout<<"Przesuniecie wynosi: \t"<<przesuniecie<<endl<<endl;
#endif

	return znak;
	
}

void deszyfrowanie( string &encrypted, const int decrypt_method )
{
	int movement=decrypt_method;
	for(int i=0;i<encrypted.size();i++)
	{
		if( i	>	0	&&	i	<=	encrypted.size() / 2 ) movement+=decrypt_method;
		else
		if( i	>	encrypted.size() / 2 ) movement-=decrypt_method;
		
		
		
		if(szyfrowanie_rekurencyjne(32, movement)	==	encrypted[i]) // moze to spacja?
			encrypted[i]=szyfrowanie_rekurencyjne(32, movement);
		else
		/*for(int s=48; s<=57; s++) // moze to jakas liczba?
		{
			char check=szyfrowanie_rekurencyjne(s, movement);
			if(check == encrypted[i])
			{
			encrypted[i]=s;
			cout<<"ZNALEZIONA LICZBA TO: "<<static_cast <char> (s)<<endl;
			}
		}
		for(int s=65; s<=90; s++) // moze to jakas duza litera?
		{
			char check=szyfrowanie_rekurencyjne(s, movement);
			if(check == encrypted[i])
			{
			cout<<"ZNALEZIONA LITERA TO: "<<static_cast <char> (s)<<endl;
			encrypted[i]=s;
			}
		}*/
		for(int s=97; s<=122; s++) // moze to jakas mala litera?
		{
			char check=szyfrowanie_rekurencyjne(s, movement);
			cout<<"Dla przypuszczenia niezaszyfrowanego: "<<s<<" zaszyfrowanie wynioslo: "<<static_cast <int> (check)<<endl;
			if(check == encrypted[i])
			{
			encrypted[i]=s;
			cout<<"ZNALEZIONA LITERA TO: "<<static_cast <char> (s)<<endl;
			}
		}
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
