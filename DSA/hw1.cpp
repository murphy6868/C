#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
    double matrix[200][200];
    double omatri[200][200];
    double imatri[200][200];
    double multip[200][200];
    int n;
void reduce_row_by_z(int row, double z) {
    for(int j=0; j<n; j++){
        matrix[row][j] /= z;
        imatri[row][j] /= z;
    } return ;
}
void swap_col_a_b(int a, int b) {
    double temp;
    for(int j=0; j<n; j++) {
        temp = matrix[j][a]; matrix[j][a] = matrix[j][b]; matrix[j][b] = temp;
        temp = imatri[j][a]; imatri[j][a] = imatri[j][b]; imatri[j][b] = temp;
    }
    return ;
}
void minus_z_times_from_a2b(double z, int a, int b) {
    for(int j=0; j<n; j++) {
        matrix[b][j] -= matrix[a][j] * z;
        imatri[b][j] -= imatri[a][j] * z;
    } return ;
}
void non_zero(int r, int c) {
    int col_count = 0;
    while(matrix[r][col_count] == 0)
        col_count++;
    swap_col_a_b(c, col_count);
    return ;
}
int main()
{
    scanf("%d", &n);
    for(int j=0; j<n; j++)
        for(int k=0; k< n; k++){
            scanf("%lf", &matrix[j][k]);
            omatri[j][k] = matrix[j][k];
        }
    for(int j=0; j<n; j++)
        imatri[j][j] = 1;
    if(!matrix[0][0])
        non_zero(0, 0);
    reduce_row_by_z(0, matrix[0][0]);
    for(int j=1; j<n; j++)
        minus_z_times_from_a2b(matrix[j][0], 0, j);
    for(int j=1; j<n; j++) {
        if(!matrix[j][j])
            non_zero(j, j);
        reduce_row_by_z(j, matrix[j][j]);
        for(int k=j+1; k<n; k++)
            minus_z_times_from_a2b(matrix[k][j], j, k);
    }

    for(int j=n-1; j>0; j--)
        for(int k=j-1; k>=0; k--)
            minus_z_times_from_a2b(matrix[k][j], j, k);

    for(int j=0; j<n; j++) {
        for(int k=0; k<n; k++) {
            for(int i=0; i<n; i++) {
                multip[j][k] += omatri[j][i] * imatri[i][k];
            }
        }
    }
    double maxerro = 0;
    for(int j=0; j<n; j++) {
        for(int k=0; k<n; k++) {
            if(j == k){
                double dis = abs(multip[j][k] - 1);
                if(maxerro < dis)
                    maxerro = dis;
            }else{
                double dis = abs(multip[j][k]);
                if(maxerro < dis)
                    maxerro = dis;
            }
        }
    }
    printf("%.12f\n", maxerro);
    for(int j=0; j<n; j++) {
        for(int k=0; k<n; k++) {
            printf("%.12f ", imatri[j][k]);
        }printf("\n");
    }
    return 0;
}
