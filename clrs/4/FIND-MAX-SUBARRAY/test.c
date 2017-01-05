#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <stdlib.h>

typedef struct {
    int low;
    int high;
    int sum;
} subarr;

subarr find_max_subarray_brute(int a[], int low, int high)
{
    subarr max_subarr = {-1, -1, INT_MIN};
    int i, j;

    for (i = low; i <= high; i++) {
        int current_sum = 0;
        for (j = i; j <= high; j++) {
            current_sum += a[j];
            if (current_sum > max_subarr.sum) {
                max_subarr.sum = current_sum;
                max_subarr.low = i;
                max_subarr.high = j;
            }
        }
    }
    return max_subarr;
}

subarr find_max_subarray(int a[], int low, int high)
{
    subarr find_max_crossing_subarray(int *, int ,int ,int);

    subarr max_subarr, left_max_subarr, right_max_subarr, cross_max_subarr;
    int mid;

    if (low == high) {
        max_subarr.low = low;
        max_subarr.high = high;
        max_subarr.sum = a[low];
        return max_subarr;
    } else {
        mid = (high + low) / 2;
        left_max_subarr = find_max_subarray(a, low, mid);
        right_max_subarr = find_max_subarray(a, mid + 1, high);
        cross_max_subarr = find_max_crossing_subarray(a, low, mid, high);
        if (left_max_subarr.sum >= right_max_subarr.sum && left_max_subarr.sum >= cross_max_subarr.sum)
            return left_max_subarr;
        else if (right_max_subarr.sum >= left_max_subarr.sum && right_max_subarr.sum >= cross_max_subarr.sum)
            return right_max_subarr;
        else
            return cross_max_subarr;
    }
}

subarr find_max_crossing_subarray(int a[], int low, int mid, int high)
{
    subarr max_subarr;
    int sum, left_sum, right_sum, max_left, max_right, i;

    sum = 0;
    left_sum = a[mid];
    max_left = mid;
    for (i = mid; i >= low; i--) {
        sum += a[i];
        if (sum > left_sum) {
            left_sum = sum;
            max_left = i;
        }
    }

    sum = 0;
    right_sum = a[mid + 1];
    max_right = mid + 1;
    for (i = mid + 1; i <= high; i++) {
        sum += a[i];
        if (sum > right_sum) {
            right_sum = sum;
            max_right = i;
        }
    }

    max_subarr.low = max_left;
    max_subarr.high = max_right;
    max_subarr.sum = left_sum + right_sum;
    return max_subarr;
}

subarr *find_max_subarray_fast(int a[], int low, int high)
{
    subarr *result = (subarr *)malloc(3*sizeof(int));
    result->low = result->high = low;
    result->sum = a[low];
    subarr current = {low, low, a[low]};
    int i;

    for (i = low + 1; i <= high; i++) {
        if (current.sum > 0) {
            current.sum += a[i];
            current.high = i;
            if (current.sum > result->sum)
                result = &current;
        } else {
            current.low = current.high = i; //不能直接赋值
            current.sum = a[i];
            if (current.sum > result->sum)
                result = &current;
        }
    }
    return result;
}



int main()
{
    int arr[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
    subarr *max_subarr;

    clock_t start = clock();
    max_subarr = find_max_subarray_fast(arr, 0, 15);
    clock_t end = clock();
    double duration = (double) (end - start) / CLOCKS_PER_SEC;
    printf("%f seconds\n", duration);

    
    printf("%d %d %d\n", max_subarr->low, max_subarr->high, max_subarr->sum);
    return 0;
}



        
        

