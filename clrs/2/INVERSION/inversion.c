#include <stdio.h>

int count_inversions(int a[], int start, int end)
{
    int inversions = 0;
    int mid;

    if (start < end) {
        mid = (start + end) / 2;
        inversions += count_inversions(a, start, mid);
        inversions += count_inversions(a, mid+1, end);
        inversions += merge_inversions(a, start, mid, end);
    }
    return inversions;
}

int merge_inversions(int a[], int start, int mid, int end)
{
    int i, j, k, inversions = 0;

    int n1 = mid - start + 1;
    int n2 = end - mid;

    int L[n1];
    int R[n2];

    for (i = 0; i < n1; i++)
        L[i] = a[start + i];
    for (j = 0; j < n2; j++)
        R[j] = a[mid + 1 + j];

    for (i = 0, j = 0, k = start; k <= end; k++) {
        if (i == n1) {
            a[k] = R[j++];
        } else if (j == n2) {
            a[k] = L[i++];
        } else if (L[i] <= R[j]) {
            a[k] = L[i++];
        } else {
            a[k] = R[j++];
            inversions += n1 - i;
        }
    }
    return inversions;
}

int main()
{
    int a[] = {2, 3, 8, 6, 1};

    printf("%d\n", count_inversions(a, 0, 4));

    return 0;
}
    


        
    
