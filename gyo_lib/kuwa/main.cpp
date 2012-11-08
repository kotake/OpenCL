/*
 * main.cpp
 *
 *  Created on: 2012/11/08
 *      Author: y-kuwa
 */
#include"main.h"

using namespace std;
int main(){
  int fvar=4096, fwid=4096, lvar=4096, lwid=4096;
  double *mtrx1,*mtrx2,*Out;
  FILE *fp;
  if ((fp = fopen("inputD.txt","r")) == NULL)
  {
    printf("file open error!!\n");
    exit(EXIT_FAILURE);
  }
  int size;
  fscanf(fp, "%d", &size);
  //cout<< size <<endl;

  mtrx1 = (double*) malloc(size * size * sizeof(double));
  if(mtrx1==NULL) return 1;
  mtrx2 = (double*) malloc(size * size * sizeof(double));
  Out = (double*) malloc(size * size * sizeof(double));

  int i, j;
  for(i=0;i<size;i++)
  {
    for(j=0;j<size;j++)
    {
      Out[i*size+j] = 0;
      fscanf(fp, "%lf", &mtrx1[i * size + j]);
      //cout <<mtrx1[i*size+j]<<endl;
    }
  }

  for(i=0;i<size;i++)
  {
    for(j=0;j<size;j++)
    {
      fscanf(fp,"%lf", &mtrx2[i * size + j]);
    }
  }

  cout<< "apistart"<<endl;

  fclose(fp);

  /*for(int i = 0 ;i < 30;i ++)
    {
    cout<<mtrx1[i]<<" "<<mtrx2[i]<<endl;
    }
    */

  string filename="test.cl";
  clapi cl(filename);
  cl.hikisu(2, size*size, mtrx1, size*size, mtrx2);
  cl.doOpenCL();
  cout<<cl.getOut()<<endl;
  Out = cl.getOut();
  //*Out = cl_api(fvar,fwid,mtrx1,lvar,lwid,mtrx2,size,Out);

  //結果表示
  cout<<"加算結果"<<endl;
  for(int i = 0 ; i < fvar ; i++){
    for(int j = 0 ; j < fwid ; j++){
      cout<< Out[i*fwid+j] << " " ;
    }
    cout << endl;
  }

  free(mtrx1);
  free(mtrx2);
  free(Out);
}

