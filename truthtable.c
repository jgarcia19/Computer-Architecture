#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*
  This program generates a truth table based upon an input given in a text FILE
  This text file contains certain types of logic gates.
  This program does NOT error check, as it was not required at the time:
  Here are some sample inputs:
  --------------------
  INPUT A B C D
  OUTPUT Z
  AND A B : E
  MULTIPLEXER E F : 0 1 1 0 : Z
  OR C D : F
  -----------------------
  INPUT IN1 IN2 IN3
  OUTPUT OUT1 OUT2
  AND IN1 IN2 : temp1
  PASS temp1 : OUT1
  OR IN3 temp1 : OUT2
  ------------------------
  I will also include the pdf file for the project.
*/
typedef struct LinkedList {
  struct LinkedList *next;
  char name[17];
} node;

typedef struct LinkedListOp {
  struct LinkedListOp *next;
  node *varInputs;
  node *varOutputs;
  char operator[12];
} nodeOp;

int main(int argc, char *argv[]) {
  int search(char name[], node *list);
  void printMainList(nodeOp *list);
  void printList(node *list);
  int not(int num);

  FILE *fp;
  fp = fopen(argv[1], "r");

  if (fp == NULL) {
    printf("PUT AN ARGUMENT DOWN JASON!!!\n");
    return 0;
  }

  node *inputs = malloc(sizeof(node));
  node *outputs = malloc(sizeof(node));
  node *temp = malloc(sizeof(node));

  inputs->next = NULL;
  outputs->next = NULL;
  temp->next = NULL;

  int numInputs = 0;
  int numOutputs = 0;
  int numTemps = 0;

  fscanf(fp, "%s", inputs->name);
  node *ptr = inputs;

  char varName[17];
  fscanf(fp, "%s", varName);

  while (strcmp(varName, "OUTPUT") != 0) {
    ptr->next = malloc(sizeof(node));
    ptr = ptr->next;
    ptr->next = NULL;
    strcpy(ptr->name, varName);
    fscanf(fp, "%s", varName);
    numInputs++;
  }

  ptr = outputs;
  strcpy(ptr->name, varName);
  fscanf(fp, "%s", varName);

  while ((strcmp(varName, "PASS") != 0) && (strcmp(varName, "NOT") != 0) &&
         (strcmp(varName, "AND") != 0) && (strcmp(varName, "OR") != 0) && (strcmp(varName, "NAND") != 0) &&
         (strcmp(varName, "NOR") != 0) && (strcmp(varName, "XOR") != 0) && (strcmp(varName, "DECODER") != 0) &&
         (strcmp(varName, "MULTIPLEXER") != 0)) {
    ptr->next = malloc(sizeof(node));
    ptr = ptr->next;
    ptr->next = NULL;
    strcpy(ptr->name, varName);
    fscanf(fp, "%s", varName);
    numOutputs++;
  }

  nodeOp *operators = malloc(sizeof(nodeOp));
  nodeOp *ptrOp = operators;
  node *ptr2 = temp;

  while (!feof(fp)) {
    ptrOp->next = malloc(sizeof(nodeOp));
    ptrOp = ptrOp->next;
    ptrOp->next = NULL;

    ptrOp->varInputs = malloc(sizeof(node));
    ptrOp->varOutputs = malloc(sizeof(node));
    strcpy(ptrOp->operator, varName);

    ptr = ptrOp->varInputs;
    fscanf(fp, "%s", varName);

    int m = 1;
    while (strcmp(varName, ":") != 0) {
      if ((search(varName, inputs) == -1) && (search(varName, temp) == -1) && (strcmp(varName, "0") != 0) && (strcmp(varName, "1") != 0)) {
        ptr2->next = malloc(sizeof(node));
        ptr2 = ptr2->next;
        ptr2->next = NULL;
        strcpy(ptr2->name, varName);
        numTemps++;
      }
      ptr->next = malloc(sizeof(node));
      ptr = ptr->next;
      ptr->next = NULL;
      strcpy(ptr->name, varName);

      fscanf(fp, "%s", varName);

      if ((strcmp(varName, ":") == 0) && (strcmp(ptrOp->operator, "MULTIPLEXER") == 0) && (m == 1)) {
        ptr->next = malloc(sizeof(node));
        ptr = ptr->next;
        ptr->next = NULL;
        strcpy(ptr->name, varName);

        fscanf(fp, "%s", varName);
        m = 0;
      }
    }

    ptrOp->varInputs = ptrOp->varInputs->next;
    ptr = ptrOp->varOutputs;

    fscanf(fp, "%s", varName);

    while ((strcmp(varName, "PASS") != 0) && (strcmp(varName, "NOT") != 0) &&
           (strcmp(varName, "AND") != 0) && (strcmp(varName, "OR") != 0) && (strcmp(varName, "NAND") != 0) &&
           (strcmp(varName, "NOR") != 0) && (strcmp(varName, "XOR") != 0) && (strcmp(varName, "DECODER") != 0) &&
           (strcmp(varName, "MULTIPLEXER") != 0) && !feof(fp)) {
      if ((search(varName, outputs) == -1) && (search(varName, temp) == -1) && (strcmp(varName, "_") != 0)) {
        ptr2->next = malloc(sizeof(node));
        ptr2 = ptr2->next;
        ptr2->next = NULL;
        strcpy(ptr2->name, varName);
        numTemps++;
      }
      ptr->next = malloc(sizeof(node));
      ptr = ptr->next;
      ptr->next = NULL;
      strcpy(ptr->name, varName);
      fscanf(fp, "%s", varName);
    }
    ptrOp->varOutputs = ptrOp->varOutputs->next;
  }

  operators = operators->next;

  temp = temp->next;
  inputs = inputs->next;
  outputs = outputs->next;

  fclose(fp);

  ptr = temp;
  while (ptr != NULL) {
    nodeOp *ptrOp1;
    nodeOp *prev;
    nodeOp *prev1;
    int i = 0;
    int o = 0;

    strcpy(varName, ptr->name);
    ptrOp = operators;
    while (ptrOp != NULL) {
      ptr2 = ptrOp->varInputs;
      int t = 0;

      while (ptr2 != NULL) {
        if (strcmp(ptr2->name, varName) == 0) {
          t = 1;
          break;
        } else {
          ptr2 = ptr2->next;
        }
      }

      if (t == 1) {
        break;
      }
      i++;
      ptrOp = ptrOp->next;
    }
    ptrOp1 = operators;

    while (ptrOp1 != NULL) {
      ptr2 = ptrOp1->varOutputs;
      int t = 0;

      while (ptr2 != NULL) {
        if (strcmp(ptr2->name, varName) == 0) {
          t = 1;
          break;
        } else {
          ptr2 = ptr2->next;
        }
      }

      if (t == 1) {
        break;
      }
      o++;
      ptrOp1 = ptrOp1->next;
    }

    if (i < o) {
      prev1 = operators;
      while (prev1->next != NULL) {
        ptr2 = prev1->next->varOutputs;
        int t = 0;
        while (ptr2 != NULL) {
          if (strcmp(ptr2->name, varName) == 0) {
            t = 1;
            break;
          } else {
            ptr2 = ptr2->next;
          }
        }
        if (t == 1) {
          break;
        }
        prev1 = prev1->next;
      }

      if (i == 0) {
        nodeOp *front = ptrOp1->next;
        if (o == 1) {
          ptrOp->next = front;
          ptrOp1->next = ptrOp;
        } else {
          ptrOp1->next = ptrOp->next;
          ptrOp->next = front;
          prev1->next = ptrOp;
        }
        operators = ptrOp1;
        ptr = temp;
      } else {
        prev = operators;
        while (prev->next != NULL) {
          ptr2 = prev->next->varInputs;
          int t = 0;
          while (ptr2 != NULL) {
            if (strcmp(ptr2->name, varName) == 0) {
              t = 1;
              break;
            } else {
              ptr2 = ptr2->next;
            }
          }
          if (t == 1) {
            break;
          }
          prev = prev->next;
        }
        nodeOp *front = ptrOp1->next;
        if (i + 1 == o) {
          prev->next = ptrOp1;
          ptrOp1->next = ptrOp;
          ptrOp->next = front;
        } else {
          ptrOp1->next = ptrOp->next;
          ptrOp->next = front;
          prev->next = ptrOp1;
          prev1->next = ptrOp;
        }
        ptr = temp;
      }
    } else {
      ptr = ptr->next;
    }
  }

  int in[numInputs];
  int tmp[numTemps];
  int out[numOutputs];
  int i;
  int j;
  int numCombs = 1;

  for (i = 0; i < numInputs; i++) {
    numCombs = numCombs * 2;
    in[i] = 0;
  }

  for (i = 0; i < numCombs; i++) {
    ptrOp = operators;

    while (ptrOp != NULL) {
      int index;

      if (strcmp(ptrOp->operator, "PASS") == 0) {
        if (search(ptrOp->varInputs->name, inputs) == -1) {

          if (search(ptrOp->varOutputs->name, outputs) == -1) {
            tmp[search(ptrOp->varOutputs->name, temp)] = tmp[search(ptrOp->varInputs->name, temp)];
          } else {
            out[search(ptrOp->varOutputs->name, outputs)] = tmp[search(ptrOp->varInputs->name, temp)];
          }

        } else {

          if (search(ptrOp->varOutputs->name, outputs) == -1) {
            tmp[search(ptrOp->varOutputs->name, temp)] = in[search(ptrOp->varInputs->name, inputs)];
          } else {
            out[search(ptrOp->varOutputs->name, outputs)] = in[search(ptrOp->varInputs->name, inputs)];
          }

        }

      } else if (strcmp(ptrOp->operator, "NOT") == 0) {
        if (search(ptrOp->varInputs->name, inputs) == -1) {

          if (search(ptrOp->varOutputs->name, outputs) == -1) {
            tmp[search(ptrOp->varOutputs->name, temp)] = not(tmp[search(ptrOp->varInputs->name, temp)]);
          } else {
            out[search(ptrOp->varOutputs->name, outputs)] = not(tmp[search(ptrOp->varInputs->name, temp)]);
          }

        } else {

          if (search(ptrOp->varOutputs->name, outputs) == -1) {
            tmp[search(ptrOp->varOutputs->name, temp)] = not(in[search(ptrOp->varInputs->name, inputs)]);
          } else {
            out[search(ptrOp->varOutputs->name, outputs)] = not(in[search(ptrOp->varInputs->name, inputs)]);
          }

        }

      } else if (strcmp(ptrOp->operator, "AND") == 0) {
        ptr = ptrOp->varInputs;
        int final = -1;
        while (ptr != NULL) {
          index = search(ptr->name, inputs);
          if (index == -1) {
            index = search(ptr->name, temp);
            if (tmp[index] == 0) {
              final = 0;
              break;
            }
          } else {
            if (in[index] == 0) {
              final = 0;
              break;
            }
          }
          ptr = ptr->next;
        }

        if (final == -1) {
          final = 1;
        }
        index = search(ptrOp->varOutputs->name, outputs);
        if (index == -1) {
          index = search(ptrOp->varOutputs->name, temp);
          tmp[index] = final;
        } else {
          out[index] = final;
        }

      } else if (strcmp(ptrOp->operator, "OR") == 0) {
        ptr = ptrOp->varInputs;
        int final = -1;
        while (ptr != NULL) {
          index = search(ptr->name, inputs);
          if (index == -1) {
            index = search(ptr->name, temp);
            if (tmp[index] == 1) {
              final = 1;
              break;
            }
          } else {
            if (in[index] == 1) {
              final = 1;
              break;
            }
          }
          ptr = ptr->next;
        }

        if (final == -1) {
          final = 0;
        }
        index = search(ptrOp->varOutputs->name, outputs);
        if (index == -1) {
          index = search(ptrOp->varOutputs->name, temp);
          tmp[index] = final;
        } else {
          out[index] = final;
        }

      } else if (strcmp(ptrOp->operator, "NAND") == 0) {
        ptr = ptrOp->varInputs;
        int final = -1;
        while (ptr != NULL) {
          index = search(ptr->name, inputs);
          if (index == -1) {
            index = search(ptr->name, temp);
            if (tmp[index] == 0) {
              final = 0;
              break;
            }
          } else {
            if (in[index] == 0) {
              final = 0;
              break;
            }
          }
          ptr = ptr->next;
        }

        if (final == -1) {
          final = 1;
        }
        index = search(ptrOp->varOutputs->name, outputs);
        if (index == -1) {
          index = search(ptrOp->varOutputs->name, temp);
          tmp[index] = not(final);
        } else {
          out[index] = not(final);
        }

      } else if (strcmp(ptrOp->operator, "NOR") == 0) {
        ptr = ptrOp->varInputs;
        int final = -1;
        while (ptr != NULL) {
          index = search(ptr->name, inputs);
          if (index == -1) {
            index = search(ptr->name, temp);
            if (tmp[index] == 1) {
              final = 1;
              break;
            }
          } else {
            if (in[index] == 1) {
              final = 1;
              break;
            }
          }
          ptr = ptr->next;
        }

        if (final == -1) {
          final = 0;
        }
        index = search(ptrOp->varOutputs->name, outputs);
        if (index == -1) {
          index = search(ptrOp->varOutputs->name, temp);
          tmp[index] = not(final);
        } else {
          out[index] = not(final);
        }

      } else if (strcmp(ptrOp->operator, "XOR") == 0) {
        int index2;
        int final;

        ptr = ptrOp->varInputs;
        index = search(ptr->name, inputs);
        if (index == -1) {
          index = search(ptr->name, temp);

          ptr = ptr->next;
          index2 = search(ptr->name, inputs);
          if (index2 == -1) {
            index2 = search(ptr->name, temp);

            if (tmp[index] == tmp[index2]) {
              final = 0;
            } else {
              final = 1;
            }

          } else {

            if (tmp[index] == in[index2]) {
              final = 0;
            } else {
              final = 1;
            }

          }

        } else {

          ptr = ptr->next;
          index2 = search(ptr->name, inputs);
          if (index2 == -1) {
            index2 = search(ptr->name, temp);

            if (in[index] == tmp[index2]) {
              final = 0;
            } else {
              final = 1;
            }

          } else {

            if (in[index] == in[index2]) {
              final = 0;
            } else {
              final = 1;
            }
          }
        }

        index = search(ptrOp->varOutputs->name, outputs);
        if (index == -1) {
          index = search(ptrOp->varOutputs->name, temp);
          tmp[index] = final;
        } else {
          out[index] = final;
        }

      } else if (strcmp(ptrOp->operator, "DECODER") == 0) {
        ptr = ptrOp->varInputs;
        int size = 0;
        while (ptr != NULL) {
          size++;
          ptr = ptr->next;
        }
        int a[size];
        int aIndex = 0;
        ptr = ptrOp->varInputs;
        while (ptr != NULL) {
          index = search(ptr->name, inputs);
          if (index == -1) {
            index = search(ptr->name, temp);
            a[aIndex] = tmp[index];
          } else {
            a[aIndex] = in[index];
          }
          aIndex++;
          ptr = ptr->next;
        }
        int b = 1;
        int sum = 0;

        for (j = size - 1; j >= 0; j--) {
          if (a[j] == 1) {
            sum = sum + b;
          }
          b = b * 2;
        }
        ptr = ptrOp->varOutputs;
        b = 0;

        while (ptr != NULL) {
          if (strcmp(ptr->name, "_") == 0) {
            b++;
            ptr = ptr->next;
            continue;
          } else {
            index = search(ptr->name, outputs);
            if (index == -1) {
              index = search(ptr->name, temp);
              if (sum == b) {
                tmp[index] = 1;
              } else {
                tmp[index] = 0;
              }
            } else if (sum == b) {
              out[index] = 1;
            } else {
              out[index] = 0;
            }
          }
          b++;
          ptr = ptr->next;
        }

      } else if (strcmp(ptrOp->operator, "MULTIPLEXER") == 0) {
        ptr = ptrOp->varInputs;
        int size = 0;
        while (strcmp(ptr->name, ":") != 0) {
          size++;
          ptr = ptr->next;
        }

        int a[size];
        int aIndex = 0;
        ptr = ptrOp->varInputs;
        while (strcmp(ptr->name, ":") != 0) {
          index = search(ptr->name, inputs);
          if (index == -1) {
            index = search(ptr->name, temp);
            a[aIndex] = tmp[index];
          } else {
            a[aIndex] = in[index];
          }
          aIndex++;
          ptr = ptr->next;
        }
        int b = 1;
        int sum = 0;

        for (j = size - 1; j >= 0; j--) {
          if (a[j] == 1) {
            sum = sum + b;
          }
          b = b * 2;
        }
        ptr = ptr->next;
        b = 0;

        while (ptr != NULL) {
          if (sum == b) break;
          b++;
          ptr = ptr->next;
        }

        index = search(ptrOp->varOutputs->name, outputs);
        if (strcmp(ptr->name, "0") == 0) {
          if (index == -1) {
            index = search(ptrOp->varOutputs->name, temp);
            tmp[index] = 0;
          } else {
            out[index] = 0;
          }
        } else if (strcmp(ptr->name, "1") == 0) {
          if (index == -1) {
            index = search(ptrOp->varOutputs->name, temp);
            tmp[index] = 1;
          } else {
            out[index] = 1;
          }
        } else {

          int index2 = search(ptrOp->varOutputs->name, outputs);
          index = search(ptr->name, inputs);

          if (index == -1) {

            index = search(ptr->name, temp);
            if (index2 == -1) {
              index2 = search(ptrOp->varOutputs->name, temp);
              tmp[index2] = tmp[index];
            } else {
              out[index2] = tmp[index];
            }

          } else {

            if (index2 == -1) {
              index2 = search(ptrOp->varOutputs->name, temp);
              tmp[index2] = in[index];
            } else {
              out[index2] = in[index];
            }

          }
        }
      }
      ptrOp = ptrOp->next;
    }

    for (j = 0; j < numInputs; j++) {
      printf("%d ", in[j]);
    }
    printf("|");
    for (j = 0; j < numOutputs; j++) {
      printf(" %d", out[j]);
    }
    printf("\n");

    for (j = numInputs - 1; j >= 0; j--) {
      if (in[j] == 0) {
        in[j] = 1;
        break;
      } else {
        in[j] = 0;
      }
    }

  }

  return 0;
}

void printList(node *list) {
  node *ptr = list;
  while (ptr != NULL) {
    printf("%s ", ptr->name);
    ptr = ptr->next;
  }
  return;
}

void printMainList(nodeOp *list) {
  void printList(node *list);
  nodeOp *ptr = list;
  while (ptr != NULL) {
    printf("%s ", ptr->operator);
    printList(ptr->varInputs);
    printf(": ");
    printList(ptr->varOutputs);
    printf("\n");
    ptr = ptr->next;
  }
  return;
}

int search(char name[], node *list) {
  node *ptr = list;
  int index = 0;
  while (ptr != NULL) {
    if (strcmp(ptr->name, name) == 0) {
      return index;
    }
    index++;
    ptr = ptr->next;
  }
  return -1;
}

int not(int num) {

  if (num != 0 && num != 1) return -1;

  if (num == 0) {
    return 1;
  } else {
    return 0;
  }
}
