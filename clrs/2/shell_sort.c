#include <stdio.h>

void
shell_sort(int nums[], int n)
{
    int i, j, gap, temp, key;

    for (gap = n / 2; gap > 0; gap /= 2) {
        for (i = gap; i < n; i++) {
            key = nums[i];
            for (j = i - gap; j >= 0 && nums[j] > key; j -= gap) {
                nums[j+gap] = nums[j];
            }
            nums[j+gap] = key;
        }
    }
}
