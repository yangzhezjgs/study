#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef struct {
    int min;
    int max;
} extremum;

extremum
find_extremum(int buf[], int n)
{
    extremum res;
    int i, min, max;

    res.min = res.max = buf[0];
    for (i = 1; i < n - 1; i += 2)
        if (buf[i] < buf[i + 1]) {
            res.min = MIN(res.min, buf[i]);
            res.max = MAX(res.max, buf[i + 1]);
        } else {
            res.min = MIN(res.min, buf[i + 1]);
            res.max = MAX(res.max, buf[i]);
        }

    if (i != n) {
        res.min = MIN(res.min, buf[n - 1]);
        res.max = MAX(res.max, buf[n - 1]);
    }

    return res;
}



