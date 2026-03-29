
#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

const float eps = 0.000001;



int gaus(int M, int N, float** A, float* X) {
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
                if (fabs(A[k][j]) - 1.0 < eps) {
                    X[L[j]] = A[k][N];
                    break;
                }
            }
        }
        delete[] L;
        return 1;
    }



}




int main()
{
    





}

