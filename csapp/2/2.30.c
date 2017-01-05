
int tadd_ok(int x, int y)
{
    int sum = x + y;
    int neg_overflow = x < 0 && y < 0 && sum >= 0;
    int pos_overflow = x > 0 && y > 0 && sum < 0;
    return !(neg_overflow || pos_overflow);
}
