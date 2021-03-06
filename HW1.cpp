// HW1.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。

#include "pch.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "gurobi_c++.h"	//將Gurobi載入

using namespace std;
//set
#define N 9 //node數
#define R 3 //piecewise linear segment數
#define m 4 //commodities數

string itos(int i) //命名會用到
{
	stringstream s;
	s << i;
	return s.str();
}
/*程式主體*/
int main(int argc, char *argv[])
{
	string s;//未來建模時命名用
	/*讀取資料檔*/
	cout << "Open the file of Cij-data" << endl; 
	fstream fin1, fin2, fin3, fin4, fin5, fin6, fin7, fin8, fin9, fin10, fin11, fin12, fin13, fin14, fin15; 
	fin1.open("Mrijr1.txt", ios::in);
	fin2.open("Mrijr2.txt", ios::in);
	fin3.open("Mrijr3.txt", ios::in);
	fin4.open("tij.txt", ios::in);
	fin5.open("Qij.txt", ios::in);
	fin6.open("li.txt", ios::in);
	fin7.open("ui.txt", ios::in);
	fin8.open("Di.txt", ios::in);
	fin9.open("Si.txt", ios::in);
	fin10.open("Frijr1.txt", ios::in);
	fin11.open("Frijr2.txt", ios::in);
	fin12.open("Frijr3.txt", ios::in);
	fin13.open("Crijr1.txt", ios::in);
	fin14.open("Crijr2.txt", ios::in);
	fin15.open("Crijr3.txt", ios::in);
	if (!fin1 || !fin2 || !fin3 || !fin4 || !fin5 || !fin6 || !fin7 || !fin8 || !fin9 || !fin10 || !fin11 || !fin12 || !fin13 || !fin14 || !fin15)//檢查檔案是否成功開啟，如果!file為真，表示無法開啟檔案
	{
		cerr << "Can't open file!\n"; //檔案開啟失敗
		system("pause");
		exit(1);
	}
	else
	cout << "File open successfully!\n"; //成功開啟
	//宣告參數
	//參數 Mrij
	int G[R + 1][N][N] = { 0 };
	for (int r = 1; r <= R; r++)
	{
		if (r == 1)
		{
			cout << endl;
			cout << "Mrij1" << endl;
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					fin1 >> G[r][i][j];
					cout << G[r][i][j] << "\t";
				}
				cout << endl;
			}cout << endl;
		}
		else if (r == 2)
		{
			cout << endl;
			cout << "Mrij2" << endl;
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					fin2 >> G[r][i][j];
					cout << G[r][i][j] << "\t";
				}
				cout << endl;
			}cout << endl;
		}
		else if (r == 3)
		{
			cout << endl;
			cout << "Mrij3" << endl;
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					fin3 >> G[r][i][j];
					cout << G[r][i][j] << "\t";
				}
				cout << endl;
			}cout << endl;
		}
	}
	//參數 tij  從i到j的旅行時間
	int t[N][N] = { 0 }; //從0開始 
	cout << endl;
	cout << "tij" << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			fin4 >> t[i][j];
			cout << t[i][j] << "\t";
		}
		cout << endl;
	}cout << endl;

	//參數 Qij
	int Q[N][N] = { 0 }; 
	cout << endl;
	cout << "Qij" << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			fin5 >> Q[i][j];
			cout << Q[i][j] << "\t";
		}
		cout << endl;
	}cout << endl;

	//參數 li lower bond
	int l[N] = { 0 };
	cout << endl;
	cout << "li" << endl;
	for (int i = 0; i < N; i++)
	{
		fin6 >> l[i];
		cout << l[i] << "\t";
	}
	cout << endl;

	//參數 ui upper bond
	int u[N] = { 0 };
	cout << endl;
	cout << "ui" << endl;
	for (int i = 0; i < N; i++)
	{
		fin7 >> u[i];
		cout << u[i] << "\t";
	}
	cout << endl;

	//參數 Di departure time
	int D[N] = { 0 };
	cout << endl;
	cout << "Di" << endl;
	for (int i = 0; i < N; i++)
	{
		fin8 >> D[i];
		cout << D[i] << "\t";
	}
	cout << endl;

	//參數 Si service time
	int S[m][N] = { 0 };
	cout << endl;
	cout << "Smi" << endl;
	for (int V = 0; V < m; V++)
	{
		for (int i = 0; i < N; i++)
		{
			fin9 >> S[V][i];
			cout << S[V][i] << "\t";
		}
		cout << endl;
	}
	cout << endl;

	//參數 Fij 
	int F[R + 1][N][N] = { 0 };
	for (int r = 1; r <= R; r++)
	{
		if (r == 1)
		{
			cout << endl;
			cout << "Frij1" << endl;
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					fin10 >> F[r][i][j];
					cout << F[r][i][j] << "\t";
				}
				cout << endl;
			}cout << endl;
		}
		else if (r == 2)
		{
			cout << endl;
			cout << "Frij2" << endl;
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					fin11 >> F[r][i][j];
					cout << F[r][i][j] << "\t";
				}
				cout << endl;
			}cout << endl;
		}
		else if (r == 3)
		{
			cout << endl;
			cout << "Frij3" << endl;
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					fin12 >> F[r][i][j];
					cout << F[r][i][j] << "\t";
				}
				cout << endl;
			}cout << endl;
		}
	}

	//參數 Cij 
	int C[R + 1][N][N] = { 0 };
	for (int r = 1; r <= R; r++)
	{
		if (r == 1)
		{
			cout << endl;
			cout << "Crij1" << endl;
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					fin13 >> C[r][i][j];
					cout << C[r][i][j] << "\t";
				}
				cout << endl;
			}cout << endl;
		}
		else if (r == 2)
		{
			cout << endl;
			cout << "Crij2" << endl;
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					fin14 >> C[r][i][j];
					cout << C[r][i][j] << "\t";
				}
				cout << endl;
			}cout << endl;
		}
		else if (r == 3)
		{
			cout << endl;
			cout << "Crij3" << endl;
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					fin15 >> C[r][i][j];
					cout << C[r][i][j] << "\t";
				}
				cout << endl;
			}cout << endl;
		}
	}

	//參數dm 每個commodity需求
	int d[m] = { 1,5,6,2 };
	for (int i = 0; i < m; i++)
	{
		cout << d[i] << "\t";
	}
	cout << endl;

	/*開始進入Gurobi編寫*/
	try {
		GRBEnv env = GRBEnv();			
		GRBModel model = GRBModel(env);	
		/* Create Variables 建立決策變數 */
		//宣告Gurobi變數 Yij
		GRBVar Y[R + 1][N][N];
		for (int r = 1; r <= R; r++)
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					Y[r][i][j] = model.addVar(0, 9999, 0.0, GRB_BINARY, "Yij"); 
				}
			}
		}
		//宣告Gurobi變數 Xij
		GRBVar X[m][R + 1][N][N];
		for (int V = 0; V < m; V++)
		{
			for (int r = 1; r <= R; r++)
			{
				for (int i = 0; i < N; i++)
				{
					for (int j = 0; j < N; j++)
					{
						X[V][r][i][j] = model.addVar(0, 9999, 0.0, GRB_INTEGER, "Xij"); 
					}
				}
			}
		}

		//宣告Gurobi變數 Wij
		GRBVar W[m][N][N];
		for (int V = 0; V < m; V++)
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					W[V][i][j] = model.addVar(0, 9999, 0.0, GRB_INTEGER, "W"); 
				}
			}
		}

		//宣告Gurobi變數 Ai
		GRBVar A[m][N];
		for (int V = 0; V < m; V++)
		{
			for (int i = 0; i < N; i++)
			{
				A[V][i] = model.addVar(0, 9999, 0.0, GRB_CONTINUOUS, "A"); 
			}
		}
		//宣告Gurobi變數 Uij
		GRBVar U[R + 1][N][N];
		for (int r = 1; r <= R; r++)
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					U[r][i][j] = model.addVar(0, 9999, 0.0, GRB_CONTINUOUS, "Uij");
				}
			}
		}

		//宣告Gurobi變數 Lij
		GRBVar L[R + 1][N][N];
		for (int r = 1; r <= R; r++)
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					L[r][i][j] = model.addVar(0, 9999, 0.0, GRB_CONTINUOUS, "Lij");
				}
			}
		}
		//宣告Gurobi變數 DELTA
		GRBVar DELTA[m][N][N];
		for (int V = 0; V < m; V++)
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
		
					DELTA[V][i][j] = model.addVar(-9999, 9999, 0.0, GRB_SEMICONT, "DELTA");
				}
			}
		}
		//宣告Gurobi變數 Bij
		GRBVar B[m][N][N];
		for (int V = 0; V < m; V++)
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					B[V][i][j] = model.addVar(0, 9999, 0.0, GRB_CONTINUOUS, "Bij"); 
				}
			}
		}

		//宣告變數a
		GRBVar a;
		a = model.addVar(0, 9999, 0.0, GRB_CONTINUOUS, "a: "); 
	
		//宣告Gurobi變數 fi
		GRBVar f[m][N];
		for (int V = 0; V < m; V++)
		{
			for (int i = 0; i < N; i++)
			{
				f[V][i] = model.addVar(0, 9999, 0.0, GRB_CONTINUOUS, "fi"); 
			}
			
		}
		model.update();
		/* 設定目標式與限制式 */
		//Set objective(1)
		GRBLinExpr sum = 0;
		GRBLinExpr sum1 = 0;
		for (int r = 1; r <= R; r++)
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					sum1 += F[r][i][j] * Y[r][i][j];
				}
			}
		}
		GRBLinExpr sum2 = 0;
		for (int r = 1; r <= R; r++)
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					sum2 += U[r][i][j] + L[r][i][j];
				}
			}
		}
		GRBLinExpr sum3 = 0;
		for (int V = 0; V < m; V++)
		{
			for (int i = 0; i < N; i++)
			{
				sum3 += f[V][i];
			}
		}
		GRBLinExpr sum4 = 0;
		for (int V = 0; V < m; V++)
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					sum4 += B[V][i][j];
				}
			}
		}
		GRBLinExpr sum5 = 0;
		for (int V = 0; V < m; V++)
		{
			for (int r = 1; r <= R; r++)
			{
				for (int i = 0; i < N; i++)
				{
					for (int j = 0; j < N; j++)
					{
						sum5 += C[r][i][j] * X[V][r][i][j];
					}
				}
			}
		}
		sum = (sum1 + sum2 + sum3 + sum4 + sum5);
		model.setObjective(sum, GRB_MINIMIZE); //目標為minimize

		// Add constraint (2)
		GRBLinExpr suma = 0, sumz = 0;
		for (int V = 0; V < m; V++)
		{
			if (V == 0)
			{
				for (int i = 0; i < N; i++)
				{
					if (i == 0)
					{
						suma = 0;
						sumz = 0;
						for (int j = 0; j < N; j++)
						{
							sumz += W[V][i][j];
							suma += W[V][j][i];
						}
						model.addConstr(sumz - suma == d[V],"c2");
					}
					else if (i == 7)
					{
						suma = 0;
						sumz = 0;
						for (int j = 0; j < N; j++)
						{
							sumz += W[V][i][j];
							suma += W[V][j][i];
						}
						model.addConstr(sumz - suma == -1 * d[V], "c2");
					}
					else
					{
						suma = 0;
						sumz = 0;
						for (int j = 0; j < N; j++)
						{
							sumz += W[V][i][j];
							suma += W[V][j][i];
						}
						model.addConstr(sumz - suma == 0, "c2");
					}
				}
			}
			else if (V == 1)
			{
				for (int i = 0; i < N; i++)
				{
					if (i == 0)
					{
						suma = 0;
						sumz = 0;
						for (int j = 0; j < N; j++)
						{
							sumz += W[V][i][j];
							suma += W[V][j][i];
						}
						model.addConstr(sumz - suma == d[V], "c2");
					}
					else if (i == 8)
					{
						suma = 0;
						sumz = 0;
						for (int j = 0; j < N; j++)
						{
							sumz += W[V][i][j];
							suma += W[V][j][i];
						}
						model.addConstr(sumz - suma == -1 * d[V], "c2");
					}
					else
					{
						suma = 0;
						sumz = 0;
						for (int j = 0; j < N; j++)
						{
							sumz += W[V][i][j];
							suma += W[V][j][i];
						}
						model.addConstr(sumz - suma == 0, "c2");
					}
				}
			}
			else if (V == 2)
			{
				for (int i = 0; i < N; i++)
				{
					if (i == 1)
					{
						suma = 0;
						sumz = 0;
						for (int j = 0; j < N; j++)
						{
							sumz += W[V][i][j];
							suma += W[V][j][i];
						}
						model.addConstr(sumz - suma == d[V], "c2");
					}
					else if (i == 7)
					{
						suma = 0;
						sumz = 0;
						for (int j = 0; j < N; j++)
						{
							sumz += W[V][i][j];
							suma += W[V][j][i];
						}
						model.addConstr(sumz - suma == -1 * d[V], "c2");
					}
					else
					{
						suma = 0;
						sumz = 0;
						for (int j = 0; j < N; j++)
						{
							sumz += W[V][i][j];
							suma += W[V][j][i];
						}
						model.addConstr(sumz - suma == 0, "c2");
					}
				}
			}
			else
			{
				for (int i = 0; i < N; i++)
				{
					if (i == 1)
					{
						suma = 0;
						sumz = 0;
						for (int j = 0; j < N; j++)
						{
							sumz += W[V][i][j];
							suma += W[V][j][i];
						}
						model.addConstr(sumz - suma == d[V], "c2");
					}
					else if (i == 8)
					{
						suma = 0;
						sumz = 0;
						for (int j = 0; j < N; j++)
						{
							sumz += W[V][i][j];
							suma += W[V][j][i];
						}
						model.addConstr(sumz - suma == -1 * d[V], "c2");
					}
					else
					{
						suma = 0;
						sumz = 0;
						for (int j = 0; j < N; j++)
						{
							sumz += W[V][i][j];
							suma += W[V][j][i];
						}
						model.addConstr(sumz - suma == 0, "c2");
					}
				}
			}
		}
		// Add constraint (3)
		GRBLinExpr sumb = 0;
		for (int V = 0; V < m; V++)
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					sumb = W[V][i][j];
					for (int r = 1; r <= R; r++)
					{
						sumb -= X[V][r][i][j];
					}
					model.addConstr(sumb <= 0, "c3");
				}
			}
		}

		// Add constraint (4)
		for (int V = 0; V < m; V++)
		{
			for (int r = 1; r <= R; r++)
			{
				for (int i = 0; i < N; i++)
				{
					for (int j = 0; j < N; j++)
					{
						model.addConstr(X[V][r][i][j] <= d[V] * Y[r][i][j], "c3");
					}
				}
			}
		}
		// Add constraint (5)
		GRBLinExpr sumc = 0;
		for (int r = 1; r <= R; r++)
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					sumc = 0;
					for (int V = 0; V < m; V++)
					{
						sumc += X[V][r][i][j];
					}
					model.addConstr(L[r][i][j] <= sumc, "c5");
					model.addConstr(sumc <= U[r][i][j], "c5");
				}
			}
		}
		// Add constraint (6)
		for (int r = 1; r <= R; r++)
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					model.addConstr(U[r][i][j] >= G[r][i][j] * Y[r][i][j] - Q[i][j], "c6");
				}
			}
		}

		// Add constraint (7)
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				model.addConstr(L[1][i][j] >= G[0][i][j] * Y[1][i][j] - Q[i][j], "c7");
				model.addConstr(L[2][i][j] >= G[1][i][j] * Y[2][i][j] - Q[i][j], "c7");
				model.addConstr(L[3][i][j] >= G[2][i][j] * Y[3][i][j] - Q[i][j], "c7");
			}
		}

		// Add constraint (8)
		for (int r = 1; r <= R; r++)
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					model.addConstr(U[r][i][j] >= 0, "c8");
				}
			}
		}

		// Add constraint (9)
		for (int r = 1; r <= R; r++)
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					model.addConstr(L[r][i][j] >= 0, "c9");
				}
			}
		}

		// Add constraint (10)
		GRBLinExpr sumd;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				sumd = 0;
				for (int r = 1; r <= R; r++)
				{
					sumd += Y[r][i][j];
				}
				model.addConstr(sumd <= 1, "c10");
			}
		}

		// Add constraint (11)
		for (int V = 0; V < m; V++)
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					model.addConstr(-1 * B[V][i][j] <= f[V][i] + t[i][j] - A[V][i]);
					model.addConstr(f[V][i] + t[i][j] - A[V][i] <= B[V][i][j]);
				}
			}
		}

		// Add constraint (12)
		for (int V = 0; V < m; V++)
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					model.addConstr(B[V][i][j] >= -9999 * W[V][i][j] + 9999);
				}
			}
		}

		// Add constraint (13)
		for (int V = 0; V < m; V++)
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					model.addConstr(B[V][i][j] >= 0);
				}
			}
		}

		// Add constraint (14)
		for (int V = 0; V < m; V++)
		{
			for (int i = 0; i < N; i++)
			{
				model.addConstr(f[V][i] >= D[i]);
			}
		}

		// Add constraint (15)
		for (int V = 0; V < m; V++)
		{
			for (int i = 0; i < N; i++)
			{
				model.addConstr(f[V][i] >= A[V][i] + S[V][i]);
			}
		}

		// Add constraint (16)
		for (int V = 0; V < m; V++)
		{
			for (int i = 0; i < N; i++)
			{
				model.addConstr(l[i] <= A[V][i]);
				model.addConstr(A[V][i] <= u[i]);
			}
		}

		sum1 = 0;
		for (int r = 1; r <= R; r++)
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					sum1 += (F[r][i][j] * Y[r][i][j]);
				}
			}
		}
		model.addConstr(sum1 == a);

		// Optimize model
		model.update();		//更新model
		//model.write("debug.lp");
		model.optimize();	//開始求解
		cout << "Obj: " << model.get(GRB_DoubleAttr_ObjVal) << endl;//列印最佳解的值
		for (int V = 0; V < m; V++)
		{
			cout << "Commodity" << V + 1 << ":" << endl;
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					if (W[V][i][j].get(GRB_DoubleAttr_X) > 0)
					{
						cout << i + 1 << "->" << j + 1 << ":" << W[V][i][j].get(GRB_DoubleAttr_X) << endl;
					}
				}
			}
		}
		cout << "固定成本: " << a.get(GRB_DoubleAttr_X) << endl;
		cout << "變動成本: " << endl;
		sum5 = 0;
		for (int V = 0; V < m; V++)
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					for (int r = 1; r <= R; r++)
					{
						sum5 = sum5 + C[r][i][j] * X[V][r][i][j].get(GRB_DoubleAttr_X);
					}
				}
			}
			cout << "Commodity " << V + 1 << ": " << sum5 << endl;
			sum5 = 0;
		}
	}// try的
	catch (GRBException e)
	{
		cout << "Error code = " << e.getErrorCode() << endl;
		cout << e.getMessage() << endl;
	}
	catch (...) {
		cout << "Exception during optimization" << endl;
	}
	system("pause");
	return 0;
}//main的
