#!/usr/bin/env python
# encoding: utf-8

def naive_strstr(haystack, needle):

    n = len(haystack)
    m = len(needle)
    if not m:
        return 0
    if n < m:
        return -1
    for i in range(n - m + 1):
        if haystack[i:i+m] == needle:
            return i

def rb_strstr(haystack, needle):

    if needle is None:
        return 0
    length1 = len(haystack)
    length2 = len(needle)
    if length1 < length2:
        return -1
    h = 1
    A = ord('A')
    d = ord('z') - ord('A') + 1
    q = 131
    for _ in range(length2-1):
        h = h * d % q
    print 'h:', h
    p = t = 0
    for i in range(length2):
        p = (p * d + ord(needle[i]) - A) % q
        t = (t * d + ord(haystack[i]) - A) % q
    print 'p:', p

    for i in range(length1 - length2 + 1):
        if t == p:
            if haystack[i:i+length2] == needle:
                return i
        if i < length1-length2:
            t = (d * (t - (ord(haystack[i]) - A) * h) + ord(haystack[i+length2]) - A) % q
    return -1


# 预处理θ(n^3|Σ|)
def auto_matcher_strstr(haystack, needle):
    import string

    if needle is None:
        return 0
    m = len(haystack)
    n = len(needle)
    if m < n:
        return -1
    transfer = {}
    for q in range(n + 1):
        for c in string.letters:
            k = min(n, q + 1)
            i = 0
            while needle[:k] != needle[i:q] + c and k > 0:
                k -= 1
                i += 1
            transfer[(q, c)] = k
    q = 0
    for i in range(m):
        q = transfer[(q, haystack[i])]
        if q == n:
            return i - n + 1
    return -1

# 预处理θ(n|Σ|)
def auto_matcher_strstr2(haystack, needle):
    import string

    n = len(haystack)
    m = len(needle)
    if not m:
        return 0
    if n < m:
        return -1

    prefix = [0, 0]
    k = 0
    for i in range(1, m):
        while k > 0 and needle[k] != needle[i]:
            k = prefix[k]
        if needle[k] == needle[i]:
            k += 1
        prefix.append(k)

    transfer = {}
    for i in range(m + 1):
        for c in string.ascii_letters:
            if i == 0:
                transfer[(i, c)] = 1 if c == needle[0] else 0
            else:
                transfer[(i, c)] = i + 1 if i != m and c == needle[i] else transfer[(prefix[i], c)]

    k = 0
    for i in range(n):
        k = transfer[(k, haystack[i])]
        if k == m:
            return i - m + 1
    return -1

def kmp_strstr(haystack, needle):

    n = len(haystack)
    m = len(needle)
    if not m:
        return 0
    if n < m:
        return -1

    prefix = [0, 0]
    k = 0
    for q in range(1, m):
        while k > 0 and needle[k] != needle[q]:
            k = prefix[k]
        if needle[k] == needle[q]:
            k += 1
        prefix.append(k)

    k = 0
    for q in range(n):
        while k > 0 and needle[k] != haystack[q]:
            k = prefix[k]
        if needle[k] == haystack[q]:
            k += 1
        if k == m:
            return q - m + 1
    return -1
