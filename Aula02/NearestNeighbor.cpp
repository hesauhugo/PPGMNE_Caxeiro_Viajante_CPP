#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

int main()
{
	double Latitudes[20];
	double Longitudes[20];
	double MatrizDistancias[20][20];
	int Rota[20];
	int ForaDaRota[20];
	int QtdRota;
	int QtdForaDaRota;
	double LatMin;
	double LatMax;
	double LngMin;
	double LngMax;
	int NumeroPontos=5;
	//Cria matriz distância
	Latitudes[0] = 10;
	Latitudes[1] = 20;
	Latitudes[2] = 50;
	Latitudes[3] = 70;
	Latitudes[4] = 90;

	Longitudes[0] = 30;
	Longitudes[1] = 50;
	Longitudes[2] = 90;
	Longitudes[3] = 30;
	Longitudes[4] = 50;
	//Calcula distância Euclidiana
	for (int i = 0; i < NumeroPontos; i++)
	{
		for (int j = 0; j < NumeroPontos; j++)
		{
			
			double x = Latitudes[i] - Latitudes[j]; 
			double y = Longitudes[i] - Longitudes[j];
				
			MatrizDistancias[i][j] = sqrt(x * x + y * y);
			cout << MatrizDistancias[i][j] << "\t";
		}
		cout << endl;
	}

	//Rota caminho mais proximo
	QtdRota = 0;
	QtdForaDaRota = NumeroPontos;
	for (int i = 0; i < NumeroPontos; i++)
	{
		ForaDaRota[i] = i;
	}
	Rota[QtdRota] = 0;
	QtdRota++;
	ForaDaRota[0] = ForaDaRota[QtdForaDaRota - 1];
	QtdForaDaRota--;
	while (QtdForaDaRota > 0)
	{
		double MenorDistancia = 999999;
		int PosicaoPontoMaisProximo;
		int PontoMaisProximo;
		int UltimoDaRota = Rota[QtdRota - 1];
		for (int j = 0; j < QtdForaDaRota; j++)
		{
			if (MatrizDistancias[UltimoDaRota][ForaDaRota[j]] < MenorDistancia)
			{
				MenorDistancia = MatrizDistancias[UltimoDaRota][ForaDaRota[j]];
				PosicaoPontoMaisProximo = j;
				
			}
		}
		PontoMaisProximo = ForaDaRota[PosicaoPontoMaisProximo];
		Rota[QtdRota] = PontoMaisProximo;
		QtdRota++;
		ForaDaRota[PosicaoPontoMaisProximo] = ForaDaRota[QtdForaDaRota - 1];
		QtdForaDaRota--;
	}

	//Imprime a rota obtida
	cout << "A rota obtida foi: ";
	double Distancia = 0;
	for (int i = 0; i < NumeroPontos; i++)
	{
		cout << Rota[i] << "-";
	}
	//Imprime a soma da rota
	cout << Rota[0];
	for (int i = 0; i < NumeroPontos - 1; i++)
	{
		Distancia += MatrizDistancias[Rota[i]][Rota[i + 1]];
	}
	Distancia += MatrizDistancias[Rota[NumeroPontos - 1]][Rota[0]];
	cout << endl << "A distancia total foi de: " << Distancia << " km";
	
}