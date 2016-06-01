// lab4.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <vector>
#include<algorithm>
#include <string>
#include <ctime>

using namespace std;

#define WIELKOSCP 512
#define ITERACJE 400 //200
#define WELITARYZMU 0.05
#define PMUTACJI 0.2
#define PODZBIOR WIELKOSCP/4
#define DWA_22 4194304
#define PI 3.14159265359
class Osobnik{
public:
	int chromosom[22];
	double przystosowanie;
	
	
};
vector<Osobnik> STL(WIELKOSCP);
vector<Osobnik> STL2(WIELKOSCP);
Osobnik a;
void inicjalizacja(){
	
	for (int i = 0; i < WIELKOSCP; i++){
	
		for (int j = 0; j < 22; j++) { 
			STL[i].chromosom[j]= rand() % (2);}
		
	}


}
int btod(Osobnik &a){
	int temp=1;
	int dziesietna=0;
	for(int i = 0; i < 22; i++){
		if(a.chromosom[i]==1)
			dziesietna+=temp;
		temp*=2;
	}
	return dziesietna;
}

double rzeczywista(Osobnik &a)
{
	return -1.5+(4.0*btod(a))/(DWA_22-1.5);
}

void przystosowanie(Osobnik &a){
	double x=rzeczywista(a);
	double co=cos(4*x);
	double wynik=x*x+co*co*co;
	//cout<<wynik<<endl;
	a.przystosowanie=wynik;
	//

}

void mutuj(Osobnik &a){
	int i=rand() %22;
	a.chromosom[i]=rand() % (2);
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
	int pktp1;
	int pktp2;
	int tmp;
	inicjalizacja();
	
	for (int k = 0; k < ITERACJE; k++){
		for (int i = 0; i < WIELKOSCP; i++){
			przystosowanie(STL[i]);
		}
		sort(STL.begin(), STL.end(), porownaj);
		//for (int i = 0; i < 20; i++)
		//cout << STL[i].przystosowanie<<endl;
		//cout << "przystosowanie: " << STL[0].przystosowanie << endl;
		

		for (int i = 0; i < esize; i++)
		{
			for (int j = 0; j < 22; j++)
				STL2[i].chromosom[j] = STL[i].chromosom[j];
			STL2[i].przystosowanie = STL[i].przystosowanie;
		}

		for (int i = esize; i < WIELKOSCP-1; )
		{
			i1 = (rand() % PODZBIOR);
			i2 = (rand() % PODZBIOR);
			pktp1 = (rand() % 20 + 2);
			pktp2 = (rand() % 20 + 2);
			if (pktp1 >= pktp2) {
				tmp = pktp1;
				pktp1 = pktp2;
				pktp2 = tmp;
			}
			for(int j=0;j<pktp1;j++){
			STL2[i].chromosom[j] = STL[i1].chromosom[j];// + STL[i2].chromosom.substr(pktp, TEKST.length()-1);
			STL2[i + 1].chromosom[j] = STL[i2].chromosom[j];//.substr(0, pktp) + STL[i1].chromosom.substr(pktp, TEKST.length());
			}
			for (int j = pktp1; j<pktp2; j++){
				STL2[i].chromosom[j] = STL[i2].chromosom[j];
				STL2[i + 1].chromosom[j] = STL[i1].chromosom[j];
			}
			for (int j = pktp2; j < 22; j++){
				STL2[i].chromosom[j] = STL[i1].chromosom[j];
				STL2[i + 1].chromosom[j] = STL[i2].chromosom[j];
			}
			if (rand() % 10 < PMUTACJI) mutuj(STL2[i]);
			if (rand() % 10 < PMUTACJI) mutuj(STL2[i+1]);
			i += 2;

		}

		swap(STL, STL2);
	}
	cout << rzeczywista(STL[0])<<endl;
	cout << "przystosowanie: " << STL[0].przystosowanie << endl;
	//for(int i=0;i<22;i++)cout<<STL[0].chromosom[i];
	system("pause");
	return 0;
}

