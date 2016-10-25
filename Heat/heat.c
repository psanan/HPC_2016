#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#ifdef _OPENMP
#  include <omp.h>
#endif

#define min(A,B) ((A) < (B) ? (A) : (B))
#define max(A,B) ((A) > (B) ? (A) : (B))

#ifndef imax
#  define imax  10
#endif 
#ifndef kmax
#  define kmax  10
#endif 
#ifndef itmax 
#  define itmax  15000
#endif 

#ifndef prtrows
#  define prtrows 10
#endif 
#ifndef prtcols
#  define prtcols 10
#endif 
 

void heatpr(double phi[imax+1][kmax+1]);

int main()
{
  double eps = 1.0e-08;
  double phi[imax+1][kmax+1], phin[imax][kmax];
  double dx,dy,dx2,dy2,dx2i,dy2i,dt,dphi,dphimax;
  int i,k,it;

  clock_t t1,t2;
  struct timeval tv1,tv2; struct timezone tz;
# ifdef _OPENMP
    double wt1,wt2;
# endif
 
# ifdef _OPENMP
#   pragma omp parallel
    { 
#     pragma omp single 
      printf("OpenMP-parallel with %1d threads\n", omp_get_num_threads());
    } /* end omp parallel */
# endif

  dx=1.0/(kmax-1);
  dy=1.0/(imax-1);
  dx2=dx*dx;
  dy2=dy*dy;
  dx2i=1.0/dx2;
  dy2i=1.0/dy2;
  dt=min(dx2,dy2)/4.0;
/* start values 0.d0 */
  for (k=0;k<kmax;k++)
  {
    for (i=0;i<imax;i++)
    {
      phi[i][k]=0.0;
    }
  }
/* start values 1.d0 */
  for (i=0;i<=imax;i++)
  {
    phi[i][kmax]=1.0;
  }
/* start values dx */
  phi[0][0]=0.0;
  phi[imax][0]=0.0;
  for (k=1;k<kmax;k++)
  {
    phi[0][k]=phi[0][k-1]+dx;
    phi[imax][k]=phi[imax][k-1]+dx;
  }

  printf("\nHeat Conduction 2d\n");
  printf("\ndx = %12.4g, dy = %12.4g, dt = %12.4g, eps = %12.4g\n",
         dx,dy,dt,eps);
  printf("\nstart values\n");
  heatpr(phi);

  gettimeofday(&tv1, &tz);
# ifdef _OPENMP
    wt1=omp_get_wtime();
# endif
  t1=clock();

/* iteration */
  for (it=1;it<=itmax;it++)
  {
    dphimax=0.;
    for (k=1;k<kmax;k++)
    {
      for (i=1;i<imax;i++)
      {
        dphi= ......  // please fill-in the missing C-Code
        dphimax=max(dphimax,dphi);
        phin[i][k]=phi[i][k]+dphi;
      }
    }
/* save values */
    for (k=1;k<kmax;k++)
    {
      for (i=1;i<imax;i++)
      {
	phi[i][k]=  ....; // please fill-in the missing C-Code
      }
    }
    if(dphimax<eps) break;
  }

  t2=clock();
# ifdef _OPENMP
    wt2=omp_get_wtime();
# endif
  gettimeofday(&tv2, &tz);

  printf("\nphi after %d iterations\n",it);
  heatpr(phi);
  printf( "CPU time (clock)                = %12.4g sec\n", (t2-t1)/1000000.0 );
# ifdef _OPENMP
    printf( "wall clock time (omp_get_wtime) = %12.4g sec\n", wt2-wt1 );
# endif
  printf( "wall clock time (gettimeofday)  = %12.4g sec\n", (tv2.tv_sec-tv1.tv_sec) + (tv2.tv_usec-tv1.tv_usec)*1e-6 );

}

void heatpr(double phi[imax+1][kmax+1])
{
  int i,k, prt_i,prt_k, prt_i_max, prt_k_max;

  prt_i_max = min(prtrows, imax+1); 
  prt_k_max = min(prtcols, kmax+1); 
  printf("i  \\  k="); 
  for (prt_k=0; prt_k<prt_k_max; prt_k++)
  { k=1.0*prt_k/(prt_k_max-1)*kmax + 0.5/*rounding*/;
    printf("  %6i",k); 
  } 
  printf("\n"); 
  printf("-------+"); 
  for (prt_k=0; prt_k<prt_k_max; prt_k++)
  { k=1.0*prt_k/(prt_k_max-1)*kmax + 0.5/*rounding*/;
    printf("--------"); 
  } 
  printf("\n"); 
  for (prt_i=0; prt_i<prt_i_max; prt_i++)
  { i=1.0*prt_i/(prt_i_max-1)*imax + 0.5/*rounding*/;
    printf("%6i |",i); 
    for (prt_k=0; prt_k<prt_k_max; prt_k++)
    { k=1.0*prt_k/(prt_k_max-1)*kmax + 0.5/*rounding*/;
      printf("  %6.4g",phi[i][k]);
    }
    printf("\n");
  }

return;
}
