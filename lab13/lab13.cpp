
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

        for (int j = r; j < M; j++) {
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
    }


}




int main()
{
    





}

