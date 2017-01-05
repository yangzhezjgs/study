int cread_alt(int *xp)
{
    int z = 0;
    int *val_ptr;

    val_ptr = xp? xp: &z;
    return *val_ptr;
}
