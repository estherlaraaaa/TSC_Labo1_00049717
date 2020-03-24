#include <vector>
#include "math.h"
#include "stdlib.h"

using namespace std;

typedef vector<float> Vector;
typedef vector<Vector> Matrix;


void zeroes(Vector &v,int n){
    for(int i=0;i<n;i++){
        v.push_back(0.0);
    }
}

void zeroes(Matrix &M,int n){
    for(int i=0;i<n;i++){
        vector<float> row(n,0.0);
        M.push_back(row);
    }
}

void zeroes(Matrix &M,int n, int m){
    for(int i=0;i<n;i++){
        vector<float> row(m,0.0);
        M.push_back(row);
    }
}

void copyVector(Vector v, Vector &copy){
    zeroes(copy,v.size());
    for(int i=0;i<v.size();i++)
        copy.at(i) = v.at(i);
}

void copyMatrix(Matrix A, Matrix &copy){
    zeroes(copy,A.size());
    for(int i=0;i<A.size();i++)
        for(int j=0;j<A.at(0).size();j++)
            copy.at(i).at(j) = A.at(i).at(j);
}

void productMatrixVector(Matrix A, Vector v, Vector &R){
    for(int f=0;f<A.size();f++){
        float cell = 0.0;
        for(int c=0;c<v.size();c++){
            cell += A.at(f).at(c)*v.at(c);
        }
        R.at(f) += cell;
    }
}

//modificada tambien para guardar en un valor la operacion y hacer mas facil el proceso (para mi)
void productRealMatrix(float real,Matrix M,Matrix &R){
    zeroes(R,M.size());
    for(int i=0;i<M.size();i++){
        for(int j=0;j<M.at(0).size();j++){
            float val = roundf(real*M.at(i).at(j) * 100) / 100;
            R.at(i).at(j) = val;
        }
    }
}

float calculateMember(int i,int j,int r,Matrix A,Matrix B){
    float member = 0;
    for(int k=0;k<r;k++)
        member += A.at(i).at(k)*B.at(k).at(j);
    return member;
}

Matrix productMatrixMatrix(Matrix A,Matrix B,int n,int r,int m){
    Matrix R;

    zeroes(R,n,m);
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            R.at(i).at(j) = calculateMember(i,j,r,A,B);

    return R;
}

void getMinor(Matrix &M,int i, int j){
    M.erase(M.begin()+i); 
    for(int i=0;i<M.size();i++)
        M.at(i).erase(M.at(i).begin()+j);
}

float determinant(Matrix M){
    if(M.size() == 1) return M.at(0).at(0);
    else{
        float det=0.0;
        for(int i=0;i<M.at(0).size();i++){
            Matrix minor;
            copyMatrix(M,minor);
            getMinor(minor,0,i);
            det += pow(-1,i)*M.at(0).at(i)*determinant(minor);
        }
        return det;
    }
}

Vector sumVector(Vector A,Vector B,int n){
    Vector R;

    zeroes(R,n);
    for(int i=0;i<n;i++)
        R.at(i) = A.at(i)+B.at(i);

    return R;
}

Matrix sumMatrix(Matrix A,Matrix B,int n,int m){
    Matrix R;

    zeroes(R,n,m);
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            R.at(i).at(j) = A.at(i).at(j)+B.at(i).at(j);

    return R;
}

//COFACTORES
void cofactors(Matrix M, Matrix &Cof){
    zeroes(Cof,M.size());
    for(int i=0;i<M.size();i++){
        for(int j=0;j<M.at(0).size();j++){
            Matrix minor;
            copyMatrix(M,minor);
            getMinor(minor,i,j);
            Cof.at(i).at(j) = pow(-1,i+j)*determinant(minor);
        }
    }
}

//TRANSPUESTA
void transpose(Matrix M, Matrix &T){
    zeroes(T,M.size());
    for(int i=0;i<M.size();i++)
        for(int j=0;j<M.at(0).size();j++)
            T.at(j).at(i) = M.at(i).at(j);
}


//EJERCICIO DE LABO BASANDOME EN EL CODIGO PROPORCIONADO

//La Inversa de una Matriz solo es posible de calcular cuando el determinante es distinto de cero.
//Si el determinante es igual a cero, deberá terminar su programa utilizando la macro EXIT_FAILURE de la librería “stdlib.h”
//Su función deberá recibir dos parámetros, el primero la Matriz a Invertir y el segundo, la Inversa de la Matriz.

//INVERSA
void inverseM(Matrix M, Matrix &Minv){
    if (determinant(M) == 0){
        exit(EXIT_FAILURE);
    }

    Matrix cofM, cofMTrans;
    cofactors(M, cofM);
    transpose(cofM, cofMTrans);
    productRealMatrix(1.0/determinant(M), cofMTrans, Minv);
}