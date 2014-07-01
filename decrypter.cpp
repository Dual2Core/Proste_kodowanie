#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <cmath>

#define WERSJA 1  // 1 dla wersji testowych, 2 dla wersji oficjalnej
#define DECRYPT_DEFAULT deszyfrowanie(cryptedstring, method, kierunki)

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

char simulation_tendency( char znak_zaszyfrowany, int przesuniecie, int kierunek ) // zwraca proponowany znak
{
	if(kierunek==49)
	{
		
		// przypadek pierwszy: najpierw do gory
		int znak = znak_zaszyfrowany + przesuniecie;
	    if(znak_zaszyfrowany<58 && znak>64 && znak<91)znak+=7;
	    else
	    if(znak_zaszyfrowany<58 && znak>96)znak+=13;
	    else
	    if(znak_zaszyfrowany>64 && znak_zaszyfrowany<91 && znak>96)znak+=6;
	    
	    int tendencja;
	    
		if(POZA_ZAKRESEM)
		for(tendencja=1;POZA_ZAKRESEM;tendencja++)
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
		return znak;
	
	}
	else
	// przypadek drugi: najpierw w dol
	if(kierunek==48)
	{
		//cout<<"TYLE WYNOSI ZNAK SZYFROWANY: "<<znak_szyfrowany<<endl;
		//cout<<"TYLE WYNOSI PRZESUNIECIE: "<<przesuniecie<<endl;
		int znak = znak_zaszyfrowany - przesuniecie;
		if(znak_zaszyfrowany>96 && znak<91 && znak>64)znak-=6;
		else
		if(znak_zaszyfrowany>96 && znak<58)znak-=13;
		else
		if(znak_zaszyfrowany>64 && znak_zaszyfrowany<91 && znak<58)znak-=7;
	    //cout<<"PRZEEED przed znak wynosi: "<<znak<<endl;
	    
	    int tendencja;
	    
		if(POZA_ZAKRESEM)
		for(tendencja=1;POZA_ZAKRESEM;tendencja++)
		{
			int odbicie;
			if(znak>122)
			{
				odbicie=znak-122; //znak wychodzi poza gorna granice zakresu, wartosc ekstra jest "obcinana" jako odbicie
				//cout<<"Odbicie od osi x w dol wynosi: "<<odbicie<<endl;
				znak=122-odbicie; //wartosc jest odbijana wzgledem ostatniej gornej osi x wykresu
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
				//cout<<"Odbicie wynioslo: "<<odbicie<<endl;
				znak=48+odbicie; //wartosc jest odbijana wzgledem ostatniej dolnej osi x wykresu
				if(group_HIGH(znak) || znak>96)znak+=13;
				else
				if(group_LOW(znak) || znak>64)znak+=7;
				else
				if(znak>122)znak+=13;
			}
			else
			{
				if(tendencja%2!=0)
				{
					if(group_HIGH(znak))znak-=6;
					else
					if(group_LOW(znak))znak-=7;
				}
				else
				if(tendencja%2==0)
				{
					if(group_HIGH(znak))znak+=6;
					else
					if(group_LOW(znak))znak+=7;
				}
			}
			
			
		}
		return znak;
	}
	
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
	    
	int tendencja;
    
	if(POZA_ZAKRESEM)
	for(tendencja=1;POZA_ZAKRESEM;tendencja++)
	{
		int odbicie;
		if(znak>122)
		{
			odbicie=znak-122; //znak wychodzi poza gorna granice zakresu, wartosc ekstra jest "obcinana" jako odbicie
			//cout<<"Odbicie od osi x w dol wynosi: "<<odbicie<<endl;
			znak=122-odbicie; //wartosc jest odbijana wzgledem ostatniej gornej osi x wykresu
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
	
	
	/*----------------------------------------------------------------------------------*/

	return znak;
	
}


void deszyfrowanie( string &encrypted, const int decrypt_method, string directions )
{
	int movement=decrypt_method;
	for(int i=0;i<encrypted.size();i++)
	{
		if( i	>	0	&&	i	<=	encrypted.size() / 2 ) movement+=decrypt_method;
		else
		if( i	>	encrypted.size() / 2 ) movement-=decrypt_method;
		
		int direction=static_cast <int> (directions[i]);
		int odszyfrowany=static_cast <int> (simulation_tendency(encrypted[i], movement, direction));
		cout<<endl<<"kierunek: "<<direction<<endl;
		cout<<"odszyfrowany: "<<odszyfrowany<<endl;
		
		/*
		int propozycja1,propozycja2,odszyfrowany;
		
		cout<<endl<<"Kod ASCII znaku zaszyfrowanego: "<<static_cast <int> (encrypted[i])<<endl;
		propozycja1=static_cast <int> (simulation_tendency(encrypted[i], movement, 1));
		propozycja2=static_cast <int> (simulation_tendency(encrypted[i], movement, 2));
		
		cout<<"PROPOZYCJA 1: kod ASCII znaku odszyfrowanego: "<<propozycja1<<endl;
		cout<<"PROPOZYCJA 2: kod ASCII znaku odszyfrowanego: "<<propozycja2<<endl;
		*/
		cout<<endl<<"Kod ASCII znaku zaszyfrowanego:\t"<<static_cast <int> (encrypted[i])<<endl;
		cout<<"Kod ASCII znaku odszyfrowanego:\t"<<odszyfrowany<<endl;
		
		encrypted[i]=odszyfrowany;
		
		/*
		if(nr==1)
		{
			cout<<"Znak znaleziony: "<<static_cast <char> (propozycja1)<<endl;
			encrypted[i]=propozycja1;
		}
		else
		if(nr==2)
		{
			cout<<"Znak znaleziony: "<<static_cast <char> (propozycja2)<<endl;
			encrypted[i]=propozycja2;
		}
		nr=0;*/
	}
}

int main()
{
	onemoretime:
	fstream plik("crypted.txt", ios::in);
	if(plik.is_open())cout<<"Plik zaladowany pomyslnie!"<<endl;
	string cryptedstring;
	string kierunki;
	getline(plik, cryptedstring);
	getline(plik, kierunki);
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
