
#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

const double eps = 0.000001;



int gaus(int M, int N, double** A, double* X) {
// Элементарные преобразования
// 1) Перестановка строк(уравн) и столбцов(переменных)
// 2)  Вычитание из i строки k строки, умноженной на с
// 3) Деление i строки на a[i][i]
    int i, j, k, v, u, r;
    float c, z;

    int* L = new int[N];
    for (int i = 0; i < N; i++) L[i] = i;

    r = 0;

    // прямой ход
    for (int i = 0; i < N && r < M; i++) {
        v = r; u = i; 

        for (j = r; j < M; j++) {
            for (int k = i; k < N; k++) {
                if (fabs(A[j][k]) > fabs(A[v][u])) {
                    v = j;
                    u = k;
                }

            }
        }
        if (fabs(A[v][u]) < eps) {
            //не найден
            continue;
        }

        // перестановка строк
        if (v != r) {
            for (j = i; j <= N; j++) {
                z = A[r][j];
                A[r][j] = A[v][j];
                A[v][j] = z;
            }
        }

        // перестановка столбцов
        if (u != i) {
            for (int k = 0; k < M; k++) {
                z = A[k][i];
                A[k][i] = A[k][u];
                A[k][u] = z;
            }
            // меняем индексы переменных
            int p = L[i];
            L[i] = L[u];
            L[u] = p;
        }
        
        // деление строк 
        c = A[r][i];
        for (j = i; j <= N; j++) {
            A[r][j] /= c;
        }

        // Вычитание стлбцов
        for (int k = 0; k < M; k++) {
            if (k != r) {
                c = A[k][i];
                for (j = i; j <= N; j++) {
                    A[k][j] -= c * A[r][j];
                }
            }

        }
        r++;
    }

    i = r;
    while (i < M && fabs(A[i][N]) < eps) i++;

    if (i < M) {
        // нет решений
        delete[] L;
        return 0;
    }

    if (r == N ) {
        // 1р 
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < r; k++) {
                if (fabs(A[k][j] - 1.0) < eps) {
                    X[L[j]] = A[k][N];
                    break;
                }
            }
        }
        delete[] L;
        return 1;
    }

    // бесконечно много решений
    for (j = r; j < N; j++) X[L[j]] = 0; // свободным переменным == 0 

    for (int j = 0; j < r; j++) {
        // вычисление зависимых переменных
        for (int k = 0; k < r; k++) {
            int col = -1;
            for (int t = 0; t < N; t++) {
                if (fabs(A[k][t] - 1.0) < eps) { // нахождение 1 в матрице
                    col = t;
                    break;
                }
            }
            if (col == L[j]) { // сопоставляем найденный столбец зависимой пер
                X[L[j]] = A[k][N]; // св.член
                for (int t = r; t < N; t++) {
                    X[L[j]] -= A[k][t] * X[L[t]];
                }
                break;
        }
        }
    }
    delete[] L;
    return 2;
}




int main()
{
    int testnum;
    cout << "Введите номер теста: ";
    cin >> testnum;

    string inpfile = "test" + to_string(testnum) + ".txt";
    string outfile = "result" + to_string(testnum) + ".txt";

    ifstream fin(inpfile);
    ofstream fout(outfile);

    int m, n;
    fin >> m >> n;

    // Выделение памяти
    double** A = new double* [m];
    for (int i = 0; i < m; i++) {
        A[i] = new double[n + 1];
        for (int j = 0; j <= n; j++) {
            fin >> A[i][j];
        }
    }

    double* X = new double[n];

    // Решение
    int res = gaus(m, n, A, X);

    // Вывод результата
    fout << fixed << setprecision(6);

    if (res == 0) {
        fout << "Система не имеет решений" << endl;
    }
    else if (res == 1) {
        for (int i = 0; i < n; i++) {
            fout << "x" << i + 1 << " = " << X[i];
            if (i < n - 1) fout << "; ";
        }
        fout << endl;
    }
    else {
        fout << "Система имеет бесконечно много решений" << endl;
        for (int i = 0; i < n; i++) {
            fout << "x" << i + 1 << " = " << X[i];
            if (i < n - 1) fout << "; ";
        }


    }
    for (int i = 0; i < m; i++) {
        delete[] A[i];
    }
    delete[] A;
    delete[] X;

    fin.close();
    fout.close();

    return 0;

}

