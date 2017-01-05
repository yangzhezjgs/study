#include "cachelab.h"
#include <getopt.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

/* definition of cache line */
typedef struct {
    int valid_bit;
    int tag;
    int LRU_counter;
} cache_line;

/* status for cahce simulator */
enum { MISS, HIT, MISS_EVICTION, MISS_HIT, HIT_HIT, MISS_EVICTION_HIT, INSTRUCTION };

/* global variables */
int s, E, b;
unsigned set_index_mask;
char *trace_file;
int hits = 0;
int misses = 0;
int evictions = 0;
cache_line **cache;

/*
 * initCache - initialize a cache, 2^s sets and E lines per set;
 */
void initCache()
{
    int i;
    int S = 1 << s;
    /* allocation and initialization */
    cache = (cache_line **) calloc(S, sizeof(cache_line *));
    if (!cache) {
        fprintf(stderr, "Memory error!\n");
        exit(1);
    }
    for (i = 0; i < S; i++) {
        cache[i] = (cache_line *) calloc(E, sizeof(cache_line));
        if (!cache[i]) {
            fprintf(stderr, "Memory error!\n");
            exit(1);
        }
    }
    /* s bits 1 */
    set_index_mask = (1 << (b + s)) - (1 << b); 
}

void freeCache()
{
    int i;
    int S = 1 << s;
    for (i = 0; i < S; i++) {
        free(cache[i]);
    }
    free(cache);
}

int accessData(char opt, unsigned addr, int size)
{
    if (opt == 'I')
        return INSTRUCTION;
    static int counter = 1;
    int i, smallest;
    unsigned tag_bits, set_bits;
    tag_bits = addr >> (s + b);
    set_bits = (addr & set_index_mask) >> b;
    counter++;

    cache_line *cache_set;
    cache_set = cache[set_bits];
    /* hit */
    for (i = 0; i < E; i++) {
        if (cache_set[i].valid_bit == 1 && cache_set[i].tag == tag_bits) {
            cache_set[i].LRU_counter = counter;
            if (opt == 'M') {
                hits += 2;
                return HIT_HIT;
            } else {
                hits++;
                return HIT;
            }
        }
    }
    /* miss with empty line */
    for (i = 0; i < E; i++) {
        if (cache_set[i].valid_bit == 0) {
            cache_set[i].valid_bit = 1;
            cache_set[i].tag = tag_bits;
            cache_set[i].LRU_counter = counter;
            if (opt == 'M') {
                misses++;
                hits++;
                return MISS_HIT;
            } else {
                misses++;
                return MISS;
            }
        }
    }

    /* find smallest LRU_counter and eivct it */
    smallest = 0;
    for (i = 0; i < E; i++) {
        if (cache_set[i].LRU_counter < cache_set[smallest].LRU_counter) {
            smallest = i;
        }
    }
    cache_set[smallest].tag = tag_bits;
    cache_set[smallest].LRU_counter = counter;
    if (opt == 'M') {
        misses++;
        evictions++;
        hits++;
        return MISS_EVICTION_HIT;
    } else {
        misses++;
        evictions++;
        return MISS_EVICTION;
    }
    return INSTRUCTION;
}

void replayTrace()
{
    FILE *pFile;
    /* open trace file */
    pFile = fopen(trace_file, "r");

    if (!pFile) {
        fprintf(stderr, "can't open file - %s, %s\n", trace_file, strerror(errno));
        exit(1);
    }

    char operation;
    unsigned long address;
    int size;
    /* state of access data */
    int status;
    /* read a series of lines in pFile */
    while(fscanf(pFile, " %c %lx,%d", &operation, &address, &size) > 0) {
        status = accessData(operation, address, size);
        switch(status) {
        case HIT:
            printf(" %c %lx,%d hit\n", operation, address, size);
            break;
        case MISS:
            printf(" %c %lx,%d miss\n", operation, address, size);
            break;
        case MISS_HIT:
            printf(" %c %lx,%d miss hit\n", operation, address, size);
            break;
        case HIT_HIT:
            printf(" %c %lx,%d hit hit\n", operation, address, size);
            break;
        case MISS_EVICTION:
            printf(" %c %lx,%d miss eviction\n", operation, address, size);
            break;
        case MISS_EVICTION_HIT:
            printf(" %c %lx,%d miss eviction hit\n", operation, address, size);
            break;
        default:
            break;
        }
    }
    fclose(pFile);
}

void printUsage()
{
    printf("./csim: Missing required command line arguemnt\n\
Usage ./csim [-hv] -s <num> -E <num> -b <num> -t <file>\n\
Options:\n\
  -h\t    Print this help messsage.\n\
  -v\t    Optional verbose flag.\n\
  -s <num>  Number of set index bits.\n\
  -E <num>  Number of lines per set.\n\
  -b <num>  Number of block offset bits.\n\
  -t <file> Trace file.\n");
    exit(-1);
}

int main(int argc, char **argv)
{
    /* get arguments */
    int opt;
    int opt_count = 0;
    while ((opt = getopt(argc, argv, "h:s:E:b:t:")) != -1) {
        switch(opt) {
        case 'h':
            printUsage();
        case 's':
            s = atoi(optarg);
            opt_count++;
            break;
        case 'E':
            E = atoi(optarg);
            opt_count++;
            break;
        case 'b':
            b = atoi(optarg);
            opt_count++;
            break;
        case 't':
            trace_file = optarg;
            opt_count++;
            break;
        default:
            printUsage();
        }
    }
    if (opt_count != 4) {
        printUsage();
    }
    

    /* kernels */
    initCache();
    replayTrace();
    freeCache();

    printSummary(hits, misses, evictions);
    return 0;
}
