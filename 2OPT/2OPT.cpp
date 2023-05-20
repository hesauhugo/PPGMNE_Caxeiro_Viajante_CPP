#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

struct ProblemaRoteirizacao
{
	double Latitudes[20];
	double Longitudes[20];
	double MatrizDistancias[20][20];
	int Rota[20];
	int NumeroPontos=5;
	bool TeveMelhoria2opt;

	//Cria matriz distância
	void GerarCoordenadasAleatorias()
	{
		
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

	}
	//Calcula distância Euclidiana
	void CalcularDistancias()
	{
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
	}
	//Rota Inicial
	void FazerRotaInicial()
	{
		int ForaDaRota[20];
		int QtdRota;
		int QtdForaDaRota;
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
			Rota[QtdRota] = 0;
		}
	}
	//Custo do caminho
	double CustoCaminho(int posicaoInicio, int posicaoFim)
	{
		double Custo = 0;
		for (int i = posicaoInicio; i < posicaoFim; i++)
		{
			Custo += MatrizDistancias[Rota[i]][Rota[i + 1]];
		}
		return Custo;
	}
	//Custo caminho reverso
	double CustoCaminhoReverso(int posicaoInicio, int posicaoFim)
	{
		double Custo = 0;
		for (int i = posicaoFim; i > posicaoInicio; i--)
		{
			Custo += MatrizDistancias[Rota[i]][Rota[i - 1]];
		}
		return Custo;
	}
	//Economia 2OPT
	double Economia2opt(int posicaoA, int posicaoB)
	{
		double CustoAntigo = 0;
		double CustoNovo = 0;
		double Economia;
		CustoAntigo = CustoCaminho(posicaoA, posicaoB + 1);
		CustoNovo += MatrizDistancias[Rota[posicaoA]][Rota[posicaoB]];
		CustoNovo += CustoCaminhoReverso(posicaoA + 1, posicaoB);
		CustoNovo += MatrizDistancias[Rota[posicaoA + 1]][Rota[posicaoB + 1]];
		Economia = CustoAntigo - CustoNovo - 0.0001;
		cout << "A economia de 2-opt referente à abertura dos arcos " << posicaoA << " e " << posicaoB << "eh de " << Economia << endl;
		return Economia;
	}
	//Pontos com melhoria
	void Melhoria2opt(int PosicaoA, int PosicaoB)
	{
		cout << endl << "Posicao A: " <<  PosicaoA << " Posicao B: "<< PosicaoB;
	}
	//Calcula Economia entre as posições
	void Melhoria2optCiclo()
	{
		double MaiorEconomia = -1;
		int Posicaoi;
		int Posicaoj;
		for (int i = 0; i < NumeroPontos; i++)
		{
			for (int j = i + 1; j < NumeroPontos; j++)
			{
				double EconomiaAtual = Economia2opt(i, j);
				if (EconomiaAtual > MaiorEconomia)
				{
					MaiorEconomia = EconomiaAtual;
					Posicaoi = i;
					Posicaoj = j;
				}

				if (EconomiaAtual > 0)
				{
					Melhoria2opt(i, j);
				}
			}
			if (MaiorEconomia > 0)
			{
				Melhoria2opt(Posicaoi, Posicaoj);
				TeveMelhoria2opt = true;
			}
		}
	}
	//Fez a melhoria completa chamando o metodo do ciclo
	void Melhoria2optCompleta()
	{
		TeveMelhoria2opt = true;
		while (TeveMelhoria2opt)
		{
			TeveMelhoria2opt = false;
			Melhoria2optCiclo();
		}
	}
};

int main()
{
	//Chama classe e metodos
	ProblemaRoteirizacao MeuProblema;
	MeuProblema.GerarCoordenadasAleatorias();
	MeuProblema.CalcularDistancias();
	MeuProblema.FazerRotaInicial();
	//Imprime a rota obtida
	cout << "A rota obtida foi: ";
	double Distancia = 0;
	for (int i = 0; i < MeuProblema.NumeroPontos; i++)
	{
		cout << MeuProblema.Rota[i] << "-";
	}
	//Imprime a soma a distância total
	cout << MeuProblema.Rota[0];
	for (int i = 0; i < MeuProblema.NumeroPontos - 1; i++)
	{
		Distancia += MeuProblema.MatrizDistancias[MeuProblema.Rota[i]][MeuProblema.Rota[i + 1]];
	}
	Distancia += MeuProblema.MatrizDistancias[MeuProblema.Rota[MeuProblema.NumeroPontos - 1]][MeuProblema.Rota[0]];
	cout << endl << "A distancia total foi de: " << Distancia << " km\n";
	//Verifica a melhoria dos arcos. 
	for (int i = 0; i < MeuProblema.NumeroPontos; i++)
	{
		for (int j = i + 1; j < MeuProblema.NumeroPontos; j++)
		{
			double aaa = MeuProblema.Economia2opt(i, j);
		}
	}

}