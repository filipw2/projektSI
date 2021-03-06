// lab4.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <ctime>

using namespace std;

#define WIELKOSCP 512   //wielkosc populacji osobnikow
#define ITERACJE 400	//ilosc iteracji programu
#define PMUTACJI 0.2	//prawdopodobienstwo mutacji jednego chromosomu
#define DWA_22 4194304	//2^22
#define PI 3.14159265359
class Osobnik{
public:
	int chromosom[22];
	double przystosowanie;
};

vector<Osobnik> STL(WIELKOSCP);
vector<Osobnik> STL2(WIELKOSCP);

//inicjalizacja populacji osobnikow wypelniajac losowymi chromosomami

void inicjalizacja(){	
	for (int i = 0; i < WIELKOSCP; i++){
		for (int j = 0; j < 22; j++) { 
			STL[i].chromosom[j]= rand() % (2);
		}
	}
}

//zamiana liczby binarnej na dziesietna

int btod(Osobnik &a){
	int temp=1;
	int dziesietna=0;
	for(int i = 0; i < 22; i++){
		if(a.chromosom[i]==1) dziesietna+=temp;
		temp*=2;
	}
	return dziesietna;
}

//obliczanie odpowiedniej liczby rzeczywistej

double rzeczywista(Osobnik &a)
{
	return -1.5+(4.0*btod(a))/(DWA_22-1.5);
}

//obliczanie przystosowania ktore jest wartoscia funkcji f(x)
//szukamy minimum wiec im wartosc przystosowanie jest mniejsza tym lepiej

void przystosowanie(Osobnik &a){
	double x=rzeczywista(a);
	double co=cos(4*x);
	double wynik=x*x+co*co*co;
	a.przystosowanie=wynik;
}

//zmiana pojedynczego chromosomu

void mutuj(Osobnik &a){
	int i=rand() %22;
	a.chromosom[i]=rand() % (2);
}

//porownywanie przystosowania osobnikow
//potrzebne do sortowania

bool porownaj(Osobnik &a, Osobnik &b){
	if (a.przystosowanie < b.przystosowanie) return true;
	else return false;
}

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));
	int i1,i2,pktp1,pktp2,tmp;
	Osobnik o1, o2;
	inicjalizacja();
	
	for (int k = 0; k < ITERACJE; k++){
		for (int i = 0; i < WIELKOSCP; i++){
			przystosowanie(STL[i]);			//obliczenie przystosowania
		}
		sort(STL.begin(), STL.end(), porownaj);		//posortowanie osobnikow wzgledem przystosowania
		
		//losowanie punktow podzialu a nastepnie krzyzowanie polegajace na wymianie fragmentow
		
		i1 = (rand() % WIELKOSCP);
		i2 = (rand() % WIELKOSCP);			
		pktp1 = (rand() % 20 + 2);
		pktp2 = (rand() % 20 + 2);
		if (pktp1 >= pktp2) {
			tmp = pktp1;
			pktp1 = pktp2;
			pktp2 = tmp;
		}
		for (int j = 0; j<pktp1; j++){
			o1.chromosom[j] = STL[i1].chromosom[j];
			o2.chromosom[j] = STL[i2].chromosom[j];
		}
		for (int j = pktp1; j<pktp2; j++){
			o1.chromosom[j] = STL[i2].chromosom[j];
			o2.chromosom[j] = STL[i1].chromosom[j];
		}
		for (int j = pktp2; j < 22; j++){
			o1.chromosom[j] = STL[i1].chromosom[j];
			o2.chromosom[j] = STL[i2].chromosom[j];
		}
		if (rand() % 10 < PMUTACJI) mutuj(o1);
		if (rand() % 10 < PMUTACJI) mutuj(o2);
		for (int i = 0; i < WIELKOSCP - 2; i++) STL2[i] = STL[i];
		STL2[WIELKOSCP - 2] = o1;
		STL2[WIELKOSCP - 1] = o2;
		swap(STL, STL2);
	}
	
	cout << rzeczywista(STL[0])<<endl;
	cout << "przystosowanie: " << STL[0].przystosowanie << endl;
	system("pause");
	return 0;
}

