#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct val
 {
   int left;
   int right;
   int sum;
 }rvals;

rvals* max_crossing_subarray(int* pa, int low, int mid, int high);
rvals* max_subarray(int *pa, int low, int high);

int main()
{

  int tc ;
  scanf("%d", &tc);

  int* pa = (int*)malloc(tc*sizeof(int));

  for(int i=0; i<tc; i++)
    scanf("%d", pa+i);

  rvals* res=max_subarray(pa, 0, tc-1);

  int start = res->left;
  int stop = res->right;
  int tot = res->sum;

  printf("%d %d %d\n", start, stop, tot);

  return 0;
}


rvals* max_crossing_subarray(int* pa, int low, int mid, int high)
{

  int max_left=0;
  int max_right=0;
  int left_sum = -9999;
  int sum =0;
  for (int i=mid; i>=low; i--) 
  {
    sum = sum + *(pa+i);
    if (sum>left_sum)
    {
      left_sum=sum;
      max_left = i;
    }
  }

  int right_sum = -9999;
  sum =0;
  for (int j=mid+1; j<=high; j++) 
  {
    sum += *(pa+j);  
    if (sum>right_sum)
    {
      right_sum=sum;
      max_right = j;
    }
  }

  rvals* r1 = (rvals*)malloc(sizeof(rvals));
  r1->left = max_left;
  r1->right = max_right;
  r1->sum = left_sum + right_sum;

  return r1;
}


rvals* max_subarray(int* pa, int low, int high)
{

  //printf(" max_subarray: %d %d\n", low, high);
  rvals* rvms = (rvals*)malloc(sizeof(rvals));

  if (high==low)
  {
    //printf("marker\n");
    rvms->left = low;
    rvms->right = high;
    rvms->sum = pa[low]; 

    return rvms;
  }
  else
  {
    int mid;
    mid = (low+high)/2;

    int left_low;
    int left_high;
    int left_sum=-999;
    int right_low;
    int right_high;
    int right_sum=-999;
    int cross_low;
    int cross_high;
    int cross_sum =-999;

    rvals* rs1 = max_subarray (pa, low, mid);
    left_low = rs1->left;
    left_high = rs1->right;
    left_sum = rs1->sum;
    //printf("%d %d %d\n", left_low, left_high, left_sum);
    rvals* rs2 = max_subarray(pa, mid+1, high);
    right_low = rs2->left;
    right_high = rs2->right;
    right_sum = rs2->sum;
    //printf("%d %d %d\n", right_low, right_high, right_sum);
    rvals* rc1 =  max_crossing_subarray(pa, low, mid, high);
    cross_low = rc1->left;
    cross_high = rc1->right;
    cross_sum = rc1->sum;
    //printf("%d %d %d\n", cross_low, cross_high, cross_sum);

    if((left_sum>=right_sum)&&(left_sum>=cross_sum))
    {
      //printf("Left : %d %d %d\n", left_low, left_high, left_sum);
      rvms->left = left_low;
      rvms->right = left_high;
      rvms->sum = left_sum;
      return rvms;
    }

    else if((right_sum>=left_sum)&&(right_sum>=cross_sum))
    {
      rvms->left =right_low;
      rvms->right = right_high;
      rvms->sum = right_sum;
      //printf("Right: %d %d %d\n", right_low, right_high, right_sum);
      return rvms;
    }

    else
    {
      //printf("Cross: %d %d %d\n", cross_low, cross_high, cross_sum);
      rvms->left = cross_low;
      rvms->right = cross_high;
      rvms->sum = cross_sum;
      return rvms;
    }
  }
}
