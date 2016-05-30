// lab4.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <vector>
#include<algorithm>
#include <string>
#include <ctime>

using namespace std;

#define TEKST string("Lubie WdSI")
#define WIELKOSCP 2048
#define ITERACJE 200 //200
#define WELITARYZMU 0.05
#define PMUTACJI 0.2
#define PODZBIOR WIELKOSCP/4


class Osobnik{
public:
	string chromosom;
	unsigned int przystosowanie;
	
	
};
vector<Osobnik> STL(WIELKOSCP);
vector<Osobnik> STL2(WIELKOSCP);
Osobnik a;
void inicjalizacja(){
	string temp="1234567890";
	for (int i = 0; i < WIELKOSCP; i++){
	
		for (int j = 0; j < TEKST.length(); j++) { 
			temp[j]= char(rand() % (95) + 32);}
		STL[i].chromosom=temp;
		STL[i].przystosowanie = 0;
	}


}
void elitaryzm(){

}
void przystosowanie(Osobnik &a){
	a.przystosowanie=0;
	for (int i = 0; i < TEKST.length(); i++)a.przystosowanie += abs(int(a.chromosom[i]) - TEKST[i]);
}

void mutuj(Osobnik &a){
	int i=rand() %10;
	a.chromosom[i]=char(rand() % (95) + 32);
}

bool porownaj(Osobnik &a, Osobnik &b){
	if (a.przystosowanie < b.przystosowanie)return true;
	else return false;

}

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));
	int esize = WIELKOSCP*WELITARYZMU;
	int i1;
	int i2;
	int pktp;
	inicjalizacja();
	
	for (int k = 0; k < ITERACJE; k++){
		for (int i = 0; i < WIELKOSCP; i++){
			przystosowanie(STL[i]);
		}
		sort(STL.begin(), STL.end(), porownaj);
		//for (int i = 0; i < 20; i++)
		cout << STL[0].chromosom<<endl;
		cout << "przystosowanie: " << STL[0].przystosowanie << endl;
		if (STL[0].przystosowanie == 0)break;

		for (int i = 0; i < esize; i++)
		{
			//for (int j = 0; j < TEKST.length(); j++)
				STL2[i].chromosom = STL[i].chromosom;
			STL2[i].przystosowanie = STL[i].przystosowanie;
		}

		for (int i = esize; i < WIELKOSCP-1; )
		{
			i1 = (rand() % PODZBIOR);
			i2 = (rand() % PODZBIOR);
			pktp = (rand() % 7 + 2);
			
			STL2[i].chromosom = (string)STL[i1].chromosom.substr(0,pktp) + (string)STL[i2].chromosom.substr(pktp, TEKST.length()-1);
			STL2[i + 1].chromosom = STL[i2].chromosom.substr(0, pktp) + STL[i1].chromosom.substr(pktp, TEKST.length());
			
			if (rand() % 10 < PMUTACJI) mutuj(STL2[i]);
			if (rand() % 10 < PMUTACJI) mutuj(STL2[i+1]);
			i += 2;

		}

		swap(STL, STL2);
	}
	cout << STL[0].chromosom<<endl;
	cout << "przystosowanie: " << STL[0].przystosowanie << endl;
	system("pause");
	return 0;
}

