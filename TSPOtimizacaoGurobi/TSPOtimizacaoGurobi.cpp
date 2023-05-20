#include <iostream>
#include "gurobi_c++.h"
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <sstream>

using namespace std;

int main(int argc,
	char* argv[])
{
	try {
		//Cria matriz distância
		double Latitudes[20];
		double Longitudes[20];

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
		double Distancias[5][5];
		//Calcula distância Euclidiana
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				double x = Latitudes[i] - Latitudes[j];
				double y = Longitudes[i] - Longitudes[j];

				Distancias[i][j] = sqrt(x * x + y * y);

				cout << Distancias[i][j] << "\t";
			}
			cout << endl;
		}

		//Cria o ambiente
		GRBEnv Ambiente = GRBEnv(true);
		Ambiente.set("LogFile", "tsp.log");
		Ambiente.start();
		//Cria o modelo
		GRBModel Modelo = GRBModel(Ambiente);
		//Variáveis
		GRBVar U[5];
		GRBVar X[5][5];
		//Restrição binaria e interia
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (j != i)
				{
					X[i][j] = Modelo.addVar(0, 1, Distancias[i][j], GRB_BINARY, "x_" + to_string(i) + "_" + to_string(j));
				}
			}
		}
		//Restrição binaria e interia
		for (int i = 0; i < 5; i++)
		{

			U[i] = Modelo.addVar(0, 100000000000, 0, GRB_CONTINUOUS, "u_" + to_string(i));

		}

		GRBLinExpr expr = 0;
		//Restrição soma i para todo j = 1
		for (int i = 0; i < 5; i++)
		{
			expr = 0;
			for (int j = 0; j < 5; j++)
			{
				if (i != j)
					expr += X[i][j];
			}
			Modelo.addConstr(expr == 1, "R3_" + to_string(i));
		}
		//Restrição soma j para todo i = 1
		for (int j = 0; j < 5; j++)
		{
			expr = 0;
			for (int i = 0; i < 5; i++)
			{
				if (j != i)
					expr += X[i][j];
			}
			Modelo.addConstr(expr == 1, "R4_" + to_string(j));
		}
		
		Modelo.addConstr(U[0] == 0, "Ryyyyy");
		//Restrição MTZ
		for (int j = 1; j < 5; j++)
		{
			for (int i = 1; i < 5; i++)
			{

					if (j != i) {
						Modelo.addConstr(((U[i] - U[j]) + (4 * X[i][j])) <= 3, "RMTZx_" + to_string(i) + "_" + to_string(j));
					}
				
			}

		}

		//Otimização
		Modelo.optimize();
		Modelo.write("ModeloTSP.lp");
		Modelo.write("ModeloTSP.sol");

		cout << "Obj: " << Modelo.get(GRB_DoubleAttr_ObjVal) << endl;

	}
	catch (GRBException e) {
		cout << "Error code = " << e.getErrorCode() << endl;
		cout << e.getMessage() << endl;
	}
	catch (...) {
		cout << "Exception during optimization" << endl;
	}
	return 0;
}


