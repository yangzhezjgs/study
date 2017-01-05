#include <stdio.h>

int binary_search(int a[], int start, int end, int val)
{
    int mid;
    if (start <= end) {
        mid = (start + end) / 2;
        if (val > a[mid]) {
            return binary_search(a, mid+1, end, val);   //需要return
        } else if (val < a[mid]) {
            return binary_search(a, start, mid-1, val);
        } else {
            return mid;
        }
    }
    return -1;
}

int main()
{
    int a[] = {1, 2, 3, 4, 5, 8, 9, 10};
    printf("a[%d]: %d\n", binary_search(a, 0, 7, 10), 10);
    printf("a[%d]: %d\n", binary_search(a, 0, 7, 11), 11);

    return 0;
}

        
        

