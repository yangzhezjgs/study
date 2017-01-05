unsigned int snooze(unsigned int secs)
{
    int rs = sleep(secs);
    printf("Slept for %u of %u secs.\n", secs - rs, secs);
    return rs;
}
