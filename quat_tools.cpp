#include <stdio.h>              
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <signal.h>
#include <curses.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_eigen.h>

#include<vector>

using namespace std;


void get_quaternion_avg(vector<vector<double> > quat_datas, gsl_vector *quat_avg)
{

   //calc M = sum 1/n*(q*q')
   // qavg = eigen_vec (M) for max eigen val
   gsl_matrix *M = gsl_matrix_calloc(4,4); //start with M =0 matrix
   gsl_vector *q = gsl_vector_alloc(4);
 
   int num;
 
   num = quat_datas.size();
 
   for(int i=0;i<num;i++)
     {
 
       for(int j=0;j<4;j++)
         {
           gsl_vector_set(q,j,quat_datas[i][j]);
         }
       gsl_blas_dsyr(CblasLower,1,q,M);
     }
 
   gsl_matrix_scale(M,1.0/num);
   gsl_vector *eval = gsl_vector_alloc(4);
   gsl_matrix *evec = gsl_matrix_alloc(4,4);
 
 
   gsl_eigen_symmv_workspace *w = gsl_eigen_symmv_alloc(4);
        
   gsl_eigen_symmv(M,eval, evec, w);
   gsl_eigen_symmv_free(w);
   gsl_eigen_symmv_sort(eval,evec,GSL_EIGEN_SORT_ABS_DESC);
 
   gsl_vector_memcpy(quat_avg,&gsl_matrix_column(evec,0).vector);
   //  quat_avg = gsl_matrix_column(evec,0).vector;
 
   gsl_vector_free (eval);
   gsl_matrix_free (evec);
   gsl_matrix_free(M);
   gsl_vector_free(q);

}
