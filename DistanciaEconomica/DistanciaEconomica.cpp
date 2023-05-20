// DistanciaEconomica.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
using namespace std;
#include <string>


struct  Rota
{
	int TamanhoMaximo;
	int TamanhoAtual;
	int Sequencia[20];
	double MatrizCustos[20][20];
	int ForaDaSequencia[];

	void Parametros(int tamMaximo) {

		TamanhoMaximo = tamMaximo;
		MatrizCustos[tamMaximo][tamMaximo];
		Sequencia[tamMaximo + 1];
		ForaDaSequencia[tamMaximo];

		for (int i = 0; i < tamMaximo; i++) {
			ForaDaSequencia[i] = i;
		}
	}

	void CalculaCustosPorDistanciaEuclidiana(double* x, double* y) {

		for (int i = 0; i < TamanhoMaximo; i++) {

			for (int j = 0; j < TamanhoMaximo; j++) {

				MatrizCustos[i][j] = sqrt((x[j] - x[i]) * (x[j] - x[i]) + (y[j] - y[i]) * (y[j] - y[i]));

			}
		}
	}

	void IniciarSequencia() {

		string ArcoInicial = EncontraMenorArco();
		Sequencia[0] = stoi( ArcoInicial.substr(0, ArcoInicial.find("_")));
		Sequencia[1] = stoi(ArcoInicial.substr(1, ArcoInicial.find("_")));
		Sequencia[2] = stoi(ArcoInicial.substr(0, ArcoInicial.find("_")));
		TamanhoAtual = 2; 
		ForaDaSequencia;

	}

	string EncontraMenorArco() {
		double MenorDistancia = 9999999999;
		string ArcoMenorDistancia = "";

		for (int i = 0; i < TamanhoMaximo; i++) {

			for (int j = 0; j < TamanhoMaximo; j++){
				
				if (i != j) {

					if (MatrizCustos[i][j] < MenorDistancia) {

						MenorDistancia = MatrizCustos[i][j];
						ArcoMenorDistancia = i + "_" + j ;
					
					}

				}

			}
		}
		return ArcoMenorDistancia;
	}

};


int main()
{


}