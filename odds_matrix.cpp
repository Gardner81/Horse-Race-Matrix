
#include <iostream>
#include <stdlib.h>
#include <ctime>

using namespace std;

//The const positive integer z0 is the number of horses in the race
const int z0=8;
//Notice for team sports instead of horse races, set z0=3 for (home, draw, away)

//db is a small constant and klean(...) is useful for converting "almost"
//zero values to perfect zeros
const double db=0.00000001;
double klean(double x) {if(x<db && x>-db) x=0; return x;}

//fizz() returns a random real number betweew 0.75 and 1.25
double fizz() {int k=rand()%5001; return 0.75+0.0001*(double)k;}


//Rvecs are z0-dimensional vectors over the real numbers
class Rvec{
public:
 double v[z0];
 //sum() is the sum of all values in the vector
 double sum() {double t=0; for(int i=0; i<z0; i++) t+=v[i]; return klean(t);}
 //show() displays the vector
 void show() {cout << "("; for(int i=0; i<z0-1; i++) cout << v[i] << ", "; cout << v[z0-1] << ")";}
 //money() is like show but adds $ signs to indicate money values
 void money() {cout << "($"; for(int i=0; i<z0-1; i++) cout << v[i] << ", $"; cout << v[z0-1] << ")";}
 //percent() is like show but displays the values as percentages
 void percent() {cout << "("; for(int i=0; i<z0-1; i++) cout << 100*v[i] << "%, "; cout << 100*v[z0-1] << "%)";}
 //flip takes 1/x for each vector component x
 void flip() {double t; for(int i=0; i<z0; i++) {t=1; t/=v[i]; v[i]=t;}}
 //set(double s) sets all values in the vector to s
 void set(double s) {for(int i=0; i<z0; i++) v[i]=s;}
 //null() sets each vector components to zero
 void null() {set(0);}
 //clean() converts "almost zero" values to zero
 void clean() {for(int i=0; i<z0; i++) v[i]=klean(v[i]);}
 //vmscale is scalar multiplication
 void vmscale(double s) {for(int i=0; i<z0; i++) v[i]*=s;}
 //vdscale is scalar divison
 void vdscale(double s) {for(int i=0; i<z0; i++) v[i]/=s;}
 //wobble() introduces some random noise in the vector components
 void wobble() {for(int i=0; i<z0; i++) v[i]*=fizz();}
 //portion() scales the vector so that the sum of the components is 1
 void portion() {double t=sum(); vdscale(t);}
 //start() randomly generates a vector whose components sum to 1
 void start()
  {int i,k,m=0;
   for(i=0; i<z0; i++) {k=rand()%1000+200; m+=k; v[i]=(double)k;}
   for(i=0; i<z0; i++) v[i]/=(double)m;
  }
 //the operator * is the dot product on vectors
 double operator * (const Rvec&);
 //vector addition
 Rvec operator + (const Rvec&);
 //vector subtraction
 Rvec operator - (const Rvec&);
};

double Rvec::operator * (const Rvec& X) {double t=0; for(int i=0; i<z0; i++) t+=v[i]*X.v[i]; return klean(t);}

Rvec Rvec::operator + (const Rvec& X) {Rvec Y; for(int i=0; i<z0; i++) Y.v[i]=v[i]+X.v[i]; Y.clean(); return Y;}

Rvec Rvec::operator - (const Rvec& X) {Rvec Y; for(int i=0; i<z0; i++) Y.v[i]=v[i]-X.v[i]; Y.clean(); return Y;}


//Matrix denotes the class of z0 by z0 matrices over the real numbers
class Matrix{
public:
 double a[z0][z0];
//set(double s) sets each matrix component to the value s
 void set(double s)
  {int i,j;
   for(i=0; i<z0; i++)
   for(j=0; j<z0; j++)
    a[i][j]=s;
  }
//null() creates the zero matrix
 void null() {set(0);}
//unit() sets all matrix components to 1
 void unit() {set(1);}
//id() set the matrix to the identity matrix
 void id() {null(); for(int i=0; i<z0; i++) a[i][i]=1;}
//see README.md for the purpose of the odds(Rvec X) function
 void odds(Rvec X) {unit(); for(int i=0; i<z0; i++) a[i][i]-=X.v[i];}
//converts "almost zero" values to zero for improved readability
 void clean()
  {int i,j;
   for(i=0; i<z0; i++)
   for(j=0; j<z0; j++)
    a[i][j]=klean(a[i][j]);
  }
//scalar multiplication
 void mmscale(double s)
  {int i,j;
   for(i=0; i<z0; i++)
   for(j=0; j<z0; j++)
    a[i][j]*=s;
  }
//scalar division
 void mdscale(double s)
  {int i,j;
   for(i=0; i<z0; i++)
   for(j=0; j<z0; j++)
    a[i][j]/=s;
  }
//show() displays the matrix to the user
 void show()
  {int i,j;
   for(i=0; i<z0; i++)
    {for(j=0; j<z0; j++) cout << a[i][j] << "\t";
     cout << "\n";
    }
  }
//takes the transpose of the matrix
 void transpose()
  {int i,j; double b[z0][z0];
   for(i=0; i<z0; i++)
   for(j=0; j<z0; j++)
    b[i][j]=a[j][i];
   for(i=0; i<z0; i++)
   for(j=0; j<z0; j++)
    a[i][j]=b[i][j];
  }
//the next three functions are for elementary row operations for taking the inverse
//chrow(m,n) switches the mth row with the nth row
 void chrow(int m, int n)
  {m%=z0; n%=z0; int i; double b[z0];
   for(i=0; i<z0; i++) b[i]=a[m][i];
   for(i=0; i<z0; i++) a[m][i]=a[n][i];
   for(i=0; i<z0; i++) a[n][i]=b[i];
  }
//rdscale(s,m) divides the mth row by scalar s
 void rdscale(double s, int m) {m%=z0; for(int i=0; i<z0; i++) a[m][i]/=s;}
//subrow(s,m,n) subtracts the scalar s times the mth row from the nth row
 void subrow(double s, int m, int n) {m%=z0; n%=z0; for(int i=0; i<z0; i++) a[n][i]-=s*a[m][i];}
//& is matrix-vector multiplication
 Rvec operator & (const Rvec&);
//matrix addition
 Matrix operator + (const Matrix&);
//matrix subtraction
 Matrix operator - (const Matrix&);
//matrix multiplication
 Matrix operator * (const Matrix&);
};

Rvec Matrix::operator & (const Rvec& X)
{Rvec Y; int i,j; Y.null();
 for(i=0; i<z0; i++)
 for(j=0; j<z0; j++)
  Y.v[i]+=a[i][j]*X.v[j];
 Y.clean(); return Y;
}

Matrix Matrix::operator + (const Matrix& M)
{Matrix A; int i,j;
 for(i=0; i<z0; i++)
 for(j=0; j<z0; j++)
  A.a[i][j]=a[i][j]+M.a[i][j];
 A.clean(); return A;
}

Matrix Matrix::operator - (const Matrix& M)
{Matrix A; int i,j;
 for(i=0; i<z0; i++)
 for(j=0; j<z0; j++)
  A.a[i][j]=a[i][j]+M.a[i][j];
 A.clean(); return A;
}

Matrix Matrix::operator * (const Matrix& M)
{Matrix A; int i,j,k; A.null();
 for(i=0; i<z0; i++)
 for(j=0; j<z0; j++)
 for(k=0; k<z0; k++)
  A.a[i][j]+=a[i][k]*M.a[k][j];
 A.clean(); return A;
}

//calculates the inverse of a matrix using elementary row operations
Matrix inverse(Matrix A)
{int i,j; double t; Matrix B; B.id();

 for(i=0; i<z0; i++)
  {j=i;

   while(0==A.a[j][i]) j++;

   A.chrow(i,j);
   B.chrow(i,j);

   t=A.a[i][i];

   A.rdscale(t,i);
   B.rdscale(t,i);

   for(j=0; j<z0; j++)
    if(i!=j && 0!=A.a[j][i])
     {t=A.a[j][i];
      A.subrow(t,i,j);
      B.subrow(t,i,j);
     }
  }

 B.clean(); return B;
}


int main(){
cout << "\n\n";
int i,j,k,m,n,k0,m0,n0; srand(time(0)); double t,u,v,w,x,y,z; Rvec P,Q,R,T,U,V,W,X,Y,Z;
Matrix A,B,C,D,E,F,G,H;

//"vigorish" is the percent commission charged by the book maker
cout << "Vigorish (%) "; cin >> u; u*=0.01; v=1+u;

//wagers are originally put in exact proportion of probabilities, but the user can choose to
//add some random noise to the wagers
cout << "\nWobble wagers (1=yes, 2=no) ? "; cin >> k0;

/*
The ith component of vector T is the probability that the ith horse will win the race
The ith component of the W vector is the total wagers on the ith horse
The ith component of the V vector is the odds offered by the bookmaker on the ith horse
A is the "odds matrix" for the race
B is the inverse of the "odds matrix"
 notice both A and B are symmetric matricies (A=transpose(A), B=transpose(B))
The ith component of the P vector is the profit to the bookmaker incase the ith horse wins
The Q vector should be identical with the wager vector W (a good error check to make sure the code works)
The dot product x=T*P is the expected profit for the bookmaker
w = W.sum() is the total gross wagers on all horses
*/
k0%=2; T.start(); U=W=T; U.vmscale(v); V=U; V.flip(); W.vmscale(1000000); if(k0==1) W.wobble(); A.odds(V);

B=inverse(A); P=A&W; Q=B&P; x=T*P; w=W.sum(); cout << "\n";

cout << "Probabilities \t "; T.percent();

cout << "\n\nOdds \t\t "; V.show();

cout << "\n\nWagers \t\t "; W.money();

cout << "\n\nProfits \t "; P.money();

cout << "\n\nTotal wagers \t $" << w;

cout << "\n\nExpected value \t $" << x;

cout << "\n\nOdds matrix\n\n"; A.show();

cout << "\n\nInverse of odds matrix\n\n"; B.show();

cout << "\n\n";
return 0;
}
