#include<stdio.h>
#include<stdlib.h>

typedef struct BinarySearchTree {
  int num;
  struct BinarySearchTree *left;
  struct BinarySearchTree *right;
} node;

int main() {
  void printTree(node *t);
  char c;
  int n;
  node *top = NULL;
  while (scanf(" %c", &c) == 1) {

    if (c == 'i') {
      scanf("%d", &n);
      if (top == NULL) {
        top = malloc(sizeof(node));
        top->num = n;
        top->left = NULL;
        top->right = NULL;
        printf("inserted\n");
      } else {
        node *ptr = top;
        node *prev;
        while (ptr != NULL) {
          if (ptr->num == n) {
            printf("duplicate\n");
            break;
          } else if (ptr->num > n) {
            if (ptr->left == NULL) {
              prev = ptr;
            }
            ptr = ptr->left;
          } else {
            if (ptr->right == NULL) {
              prev = ptr;
            }
            ptr = ptr->right;
          }
        }
        if (ptr == NULL) {
          ptr = malloc(sizeof(node));
          ptr->num = n;
          ptr->left = NULL;
          ptr->right = NULL;
          if (prev->num > n) {
            prev->left = ptr;
          } else {
            prev->right = ptr;
          }
          printf("inserted\n");
        }
      }

    } else if (c == 's') {
      scanf("%d", &n);

      node *ptr = top;
      while (ptr != NULL) {
        if (ptr->num == n) {
          printf("present\n");
          break;
        } else if (ptr->num > n) {
          ptr = ptr->left;
        } else {
          ptr = ptr->right;
        }
      }

      if (ptr == NULL) {
        printf("absent\n");
      }

    } else if (c == 'd') {
      scanf("%d", &n);

      node *ptr = top;
      node *prev;
      if (top == NULL) {

        printf("absent\n");

      } else if (top->num == n) {
        if (top->left == NULL && top->right == NULL) {
          top = NULL;
        } else if (top->left == NULL && top->right != NULL) {
          top = top->right;
        } else if (top->left != NULL && top->right == NULL) {
          top = top->left;
        } else {
          ptr = ptr->left;
          if (ptr->right == NULL) {
            ptr->right = top->right;
            top = ptr;
          } else {
            prev = ptr;
            ptr = ptr->right;
            while (ptr->right != NULL) {
              prev = ptr;
              ptr = ptr->right;
            }
            prev->right = ptr->left;
            ptr->left = top->left;
            ptr->right = top->right;
            top = ptr;
          }
        }
        printf("deleted\n");
      } else {
        if (top->num < n) {
          prev = ptr;
          ptr = ptr->right;
        } else {
          prev = ptr;
          ptr = ptr->left;
        }

        while (ptr != NULL) {
          if (ptr->num == n) {

            if (ptr->left == NULL && ptr->right == NULL) {
              ptr = NULL;
              if (prev->num > n) {
                prev->left = NULL;
              } else {
                prev->right = NULL;
              }
              printf("deleted\n");
            } else if (ptr->left == NULL && ptr->right != NULL) {
              ptr = ptr->right;

              if (prev->num > n) {
                prev->left = ptr;
              } else {
                prev->right = ptr;
              }

              printf("deleted\n");
              break;
            } else if (ptr->left != NULL && ptr->right == NULL) {
              ptr = ptr->left;

              if (prev->num > n) {
                prev->left = ptr;
              } else {
                prev->right = ptr;
              }

              printf("deleted\n");
              break;
            } else {

              node *ptr2;
              node *prev2;
              ptr2 = ptr->left;
              if (ptr2->right == NULL) {
                ptr2->right = ptr->right;
                ptr = ptr2;
              } else {
                prev2 = ptr2;
                ptr2 = ptr2->right;

                while (ptr2->right != NULL) {
                  prev2 = ptr2;
                  ptr2 = ptr2->right;
                }

                prev2->right = ptr2->left;
                ptr2->left = ptr->left;
                ptr2->right = ptr->right;
                ptr = ptr2;

                if (prev->num > n) {
                  prev->left = ptr;
                } else {
                  prev->right = ptr;
                }

                printf("deleted\n");
                break;

              }
            }
          } else if (ptr->num > n) {
            prev = ptr;
            ptr = ptr->left;

            if (ptr == NULL) {
              printf("absent\n");
            }
          } else {
            prev = ptr;
            ptr = ptr->right;

            if (ptr == NULL) {
              printf("absent\n");
            }
          }
        }
      }
    } else if (c == 'p') {
      printTree(top);
      printf("\n");
    } else {
      break;
    }
  }
  free(top);
  return 0;
}

void printTree(node *t) {
  if (t == NULL) return;
  printf("(");
  printTree(t->left);
  printf("%d", t->num);
  printTree(t->right);
  printf(")");
}
