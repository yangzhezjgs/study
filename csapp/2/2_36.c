
int tmult_ok(int x, int y)
{
    long long mul = (long long) x * y;
    return mul == (int) mul;
}
