#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[]) {
  if (argc != 7) {
    printf("%d", argc);
    printf("incorrect Number of Arguments, Try Again\n");
    return 0;
  }

  int hits = 0;
  int misses = 0;
  int reads = 0;
  int writes = 0;

  int cacheSize = atoi(argv[1]);
  int blockSize = atoi(argv[5]);
  int i = 1;
  int j;

  while (i != cacheSize) {
    i = i * 2;
    if (i > cacheSize) {
      printf("Invalid Cache Size, Try Again\n");
      return 0;
    }
  }

  i = 1;
  int blockOffset = 0;
  while (i != blockSize) {
    blockOffset++;
    i = i * 2;
    if (i > blockSize) {
      printf("Invalid Block Size, Try Again\n");
      return 0;
    }
  }

  int numLines = cacheSize / blockSize;
  int linesPerSet;

  if (strcmp("direct", argv[2]) == 0) {
    linesPerSet = 1;
  } else if (strcmp("assoc", argv[2]) == 0) {
    linesPerSet = numLines;
  } else {
    int n = strlen(argv[2]) - 6;
    char num[n + 1];
    num[n] = '\0';
    for (i = 0; i < n; i++) {
      num[i] = argv[2][6 + i];
    }
    linesPerSet = atoi(num);
  }

  int numSets = numLines / linesPerSet;

  i = 1;
  int setOffset = 0;
  while (i != numSets) {
    setOffset++;
    i = i * 2;
  }

  typedef struct setOfLines {
    unsigned long int lines[linesPerSet];
    unsigned long int lineToBeReplaced;
  } set;

  set cache[numSets];

  for (i = 0; i < numSets; i++) {
    for (j = 0; j < linesPerSet; j++) {
      cache[i].lines[j] = 0;
    }
    cache[i].lineToBeReplaced = 0;
  }

  FILE *fp;
  fp = fopen(argv[6], "r");
  char counter[20];
  fscanf(fp, "%s", counter);

  while (!feof(fp)) {
    char action[2];
    unsigned long int address;
    fscanf(fp, "%s", action);
    fscanf(fp, "%lx", &address);

    unsigned long int setAndTag = address >> blockOffset;
    unsigned long int setIndex = setAndTag & ((1 << setOffset) - 1);
    unsigned long int tag = setAndTag >> setOffset;
    int inserted = 0;

    for (i = 0; i < linesPerSet; i++) {
      if (cache[setIndex].lines[i] == tag) {
        hits++;
        if (action[0] == 'W') writes++;
        inserted = 1;
        break;
      } else if (cache[setIndex].lines[i] == 0) {
        misses++;
        reads++;
        if (action[0] == 'W') writes++;
        inserted = 1;
        cache[setIndex].lines[i] = tag;

        if (strcmp(argv[3], "p1") == 0) {
          unsigned long int address1 = address + blockSize;
          unsigned long int setAndTag1 = address1 >> blockOffset;
          unsigned long int setIndex1 = setAndTag1 & ((1 << setOffset) - 1);
          unsigned long int tag1 = setAndTag1 >> setOffset;
          int inserted1 = 0;

          for (j = 0; j < linesPerSet; j++) {
            if (cache[setIndex1].lines[j] == tag1) {
              inserted1 = 1;
              break;
            } else if (cache[setIndex1].lines[j] == 0) {
              reads++;
              inserted1 = 1;
              cache[setIndex1].lines[j] = tag1;
              break;
            }
          }
          if (inserted1 == 0) {
            reads++;
            cache[setIndex1].lines[cache[setIndex1].lineToBeReplaced] = tag1;
            cache[setIndex1].lineToBeReplaced++;
            if (cache[setIndex1].lineToBeReplaced == linesPerSet) {
              cache[setIndex1].lineToBeReplaced = 0;
            }
          }

        }
        break;
      }
    }

    if (inserted == 0) {
      misses++;
      reads++;
      if (action[0] == 'W') writes++;
      cache[setIndex].lines[cache[setIndex].lineToBeReplaced] = tag;
      cache[setIndex].lineToBeReplaced++;
      if (cache[setIndex].lineToBeReplaced == linesPerSet) {
        cache[setIndex].lineToBeReplaced = 0;
      }

      if (strcmp(argv[3], "p1") == 0) {
        unsigned long int address1 = address + blockSize;
        unsigned long int setAndTag1 = address1 >> blockOffset;
        unsigned long int setIndex1 = setAndTag1 & ((1 << setOffset) - 1);
        unsigned long int tag1 = setAndTag1 >> setOffset;
        int inserted1 = 0;



        for (j = 0; j < linesPerSet; j++) {
          if (cache[setIndex1].lines[j] == tag1) {
            inserted1 = 1;
            break;
          } else if (cache[setIndex1].lines[j] == 0) {
            reads++;
            inserted1 = 1;
            cache[setIndex1].lines[j] = tag1;
            break;
          }
        }

        if (inserted1 == 0) {
          reads++;
          cache[setIndex1].lines[cache[setIndex1].lineToBeReplaced] = tag1;
          cache[setIndex1].lineToBeReplaced++;
          if (cache[setIndex1].lineToBeReplaced == linesPerSet) {
            cache[setIndex1].lineToBeReplaced = 0;
          }
        }

      }
    }

    fscanf(fp, "%s", counter);
    if (strcmp(counter, "#eof") == 0) {
      break;
    }
  }

  printf("Memory reads: %d\n", reads);
  printf("Memory writes: %d\n", writes);
  printf("Cache hits: %d\n", hits);
  printf("Cache misses: %d\n", misses);

  return 0;
}
