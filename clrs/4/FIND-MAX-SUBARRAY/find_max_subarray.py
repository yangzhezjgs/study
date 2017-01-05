#!/usr/bin/env python

def find_maximum_subarray(arr):
    length = len(arr)
    if length == 1:
        return (0, 0, arr[0])
    else:
        mid = length // 2
        (left_low, left_high, left_sum) = find_maximum_subarray(arr[:mid])
        (right_low, right_high, right_sum) = find_maximum_subarray(arr[mid:])
        (cross_low, cross_high, cross_sum) = find_max_crossing_subarray(arr, mid)
        if left_sum >= right_sum and left_sum >= cross_sum:
            return (left_low, left_high, left_sum)
        elif right_sum >= left_sum and right_sum >= cross_sum:
            return (right_low, right_high, right_sum)
        else:
            return (cross_low, cross_high, cross_sum)

def find_max_crossing_subarray(arr, mid):
    max_left = mid - 1
    left_sum = arr[mid - 1]
    sum = 0
    for i in range(mid - 1, -1, -1):
        sum += arr[i]
        if sum > left_sum:
            left_sum = sum
            max_left = i
    max_right = mid
    right_sum = arr[mid]
    sum = 0
    for i in range(mid, len(arr)):
        sum += arr[i]
        if sum > right_sum:
            right_sum = sum
            max_right = i
    return (max_left, max_right, left_sum + right_sum)

def find_maximum_subarray_fast(arr):
    max_sum = arr[0]
    current_sum = arr[0]
    current_low = max_low = max_high = 0
    for i in range(1, len(arr)):
        if current_sum > 0:
            current_sum += arr[i]
            if current_sum > max_sum:
                max_sum = current_sum
                max_low = current_low
                max_high = i
        else:
            current_low = i
            current_sum = arr[i]
            if current_sum > max_sum:
                max_sum = current_sum
                max_low = current_low
                max_high = i
    return (max_low, max_high, max_sum)
                


if __name__ == '__main__':
    arr = [13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7]
    (low, high, sum) = find_maximum_subarray_fast(arr)
    print(low, high, sum)

