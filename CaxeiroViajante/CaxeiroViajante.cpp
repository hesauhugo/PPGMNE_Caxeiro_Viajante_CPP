#include <iostream>
#include <cstdlib>
#include <time.h>
#include <chrono>

using namespace std;

/* Método para imprimir vetores */
void ImprimirVetor(long vet[], long tam)
{
	int i;
	for (i = 0; i < tam; i++)
		cout << vet[i] << "\n";
	cout << endl;
}


int main()
{
	cout << "Intervalo: 0 - " << RAND_MAX << endl;
	long* vetor;
	int inicio, fim;
	long n, semente;
	long Trocas, Comparacoes, Associacoes;
	Comparacoes = 0;
	Trocas = 0;
	Associacoes = 0;
	cout << "Digite o tamanho do vetor: ";
	cin >> n;
	cout << "Digite a semente: ";
	cin >> semente;
	vetor = new long[n];
	srand(semente);

	//Criando vetor
	for (long p = 0; p < n; p++)
	{
		vetor[p] = rand();
	}

	// Imprimir vetor desordenado
	cout << "Vetor Desordenado: \n";
	ImprimirVetor(vetor, n);

	//Ordenando vetor
	long i, j, PosicaoMenor;
	inicio = clock();
	auto start = std::chrono::high_resolution_clock::now();
	for (i = 0; i < n - 1; i++)
	{
		Associacoes++;
		PosicaoMenor = i;
		for (j = i + 1; j < n; j++)
		{
			Comparacoes++;
			if (vetor[j] < vetor[PosicaoMenor])
			{
				Associacoes++;
				PosicaoMenor = j;
			}
		}
		Trocas++;
		Associacoes += 3;
		long aux = vetor[i];
		vetor[i] = vetor[PosicaoMenor];
		vetor[PosicaoMenor] = aux;
	}

	fim = clock();
	auto finish = std::chrono::high_resolution_clock::now();

	// Imprimir vetor ordenado
	cout << "Vetor Ordenado: \n";
	ImprimirVetor(vetor, n);

	// Imprimir tempo
	cout << "Tempo: " << inicio << "--" << fim << " -> " << fim - inicio << "\n";
	std::chrono::duration<double> elapsed = finish - start;
	cout << "Tempo:" << elapsed.count() << "\n";
	double Intervalo = elapsed.count() / (double)CLOCKS_PER_SEC * 1000;
	cout << "Tempo:" << Intervalo << "\n";
	cout << "A quantidade total de comparações foi de: " << Comparacoes << "\n";
	cout << "A quantidade total de trocas foi de: " << Trocas << "\n";
	cout << "A quantidade total de associacoes foi de: " << Associacoes << "\n";
	int b;
	cin >> b;
	return 0;
}

