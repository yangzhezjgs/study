#include <stdio.h>

typedef struct subarray {
    int low;
    int high;
    int sum;
} subarray;

/* 暴力解法 θ(n^2) */
subarray 
violent_find_maximum_subarray(int buf[], int n)
{
    subarray res;
    int i, j, sum;

    res.low = res.high = 0;
    res.sum = buf[0];

    if (n > 1) 
        for (i = 0; i < n; i++) {
            sum = 0;
            for (j = i; j < n; j++) {
                sum += buf[j];
                if (sum > res.sum) {
                    res.low = i;
                    res.high = j;
                    res.sum = sum;
                }
            }
        }

    return res;
}

/* θ(n) */
subarray
find_max_crossing_subarray(int buf[], int low, int mid, int high)
{
    int i, left, right, left_sum, right_sum, sum;
    subarray res;

    left = mid;
    left_sum = sum =  buf[left];
    for (i = mid - 1; i >= low; i--) {
        sum += buf[i];
        if (sum > left_sum) {
            left = i;
            left_sum = sum;
        }
    }

    right = mid + 1;
    right_sum = sum = buf[right];
    for (i = mid + 2; i <= high; i++) {
        sum += buf[i];
        if (sum > right_sum) {
            right = i;
            right_sum = sum;
        }
    }

    res.low = left;
    res.high = right;
    res.sum = left_sum + right_sum;
    return res;
}

/* θ(nlgn) */
subarray 
recursive_find_maximum_subarray(int buf[], int low, int high)
{
    subarray left, right, cross;
    int mid;

    if (low == high) {
        left.low = left.high = low;
        left.sum = buf[low];
        return left;
    } else {
        mid = (low + high) / 2;

        left = recursive_find_maximum_subarray(buf, low, mid);
        right = recursive_find_maximum_subarray(buf, mid + 1, high);
        cross = find_max_crossing_subarray(buf, low, mid, high);

        if (left.sum >= right.sum && left.sum >= cross.sum)
            return left;
        else if (right.sum >= left.sum && right.sum >= cross.sum)
            return right;
        else
            return cross;
    }
}

/* 最大子数组要么是之前的最大子数组，要么有最新的元素，但如果子数组和小于0，肯定不会是最大子数组的一部分。
   θ(n) 
*/
subarray
linear_find_maximum_subarray(int buf[], int n)
{
    subarray res;
    int i, left,  sum;
    
    res.low = res.high = 0;
    res.sum = buf[0];

    if (n > 1) {
        sum = 0;
        for (i = left = 0; i < n; i++) {
            if (sum <= 0) {
                sum = 0;
                left = i;
            }

            sum += buf[i];

            if (sum > res.sum) {
                res.low = left;
                res.high = i;
                res.sum = sum;
            }
        }
    }

    return res;
}


int
main(void)
{
    int buf[] = { 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
    subarray res;

    res = linear_find_maximum_subarray(buf, 16);
    printf("low: %d\nhigh: %d\nsum: %d\n", res.low, res.high, res.sum);
}
