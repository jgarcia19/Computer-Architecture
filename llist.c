#include<stdio.h>
#include<malloc.h>

typedef struct LinkedList {
  int num;
  struct LinkedList *next;
} node;

int main() {
  void printList(node *head, int s);
  int size = 0;
  char c;
  int n;
  node *head = NULL;
  while (scanf(" %c", &c) == 1) {
    scanf("%d", &n);
    if (c == 'i') {
      if (size == 0) {
        head = malloc(sizeof(node));
        head->num = n;
        head->next = NULL;
        size++;
      } else if (size == 1) {
        node *newNode = malloc(sizeof(node));
        newNode->num = n;
        if (head->num == n) {
          free(newNode);
        } else if (head->num < n) {
          head->next = newNode;
          newNode->next = NULL;
          size++;
        } else {
          newNode->next = head;
          head->next = NULL;
          head = newNode;
          size++;
        }
      } else if (head->num == n) {

      } else if (head->num > n) {
        node *newNode = malloc(sizeof(node));
        newNode->num = n;
        newNode->next = head;
        head = newNode;
        size++;
      } else {
        node *newNode = malloc(sizeof(node));
        newNode->num = n;
        node *ptr = head->next;
        node *prev = head;
        while (ptr != NULL) {
          if (ptr->num == n) {
            free(newNode);
            break;
          } else if (ptr->num > n) {
            prev->next = newNode;
            newNode->next = ptr;
            size++;
            break;
          }
          prev = ptr;
          ptr = ptr->next;
        }
        if (ptr == NULL) {
          prev->next = newNode;
          newNode->next = NULL;
          size++;
        }
      }
      printList(head, size);
    } else if (c == 'd') {
      if (size == 0) {

      } else if (size == 1) {
        if (head->num == n) {
          free(head);
          size--;
        }

      } else if (head->num == n) {
        node *ptr = head;
        head = head->next;
        free(ptr);
        size--;
      } else {
        node *ptr = head->next;
        node *prev = head;
        while (ptr != NULL) {
          if (ptr->num == n) {
            prev->next = ptr->next;
            free(ptr);
            size--;
            break;
          } else if (ptr->num < n) {
            prev = ptr;
            ptr = ptr->next;
          } else {
            break;
          }
        }
      }
      printList(head, size);
    } else if (c != 'i' || c != 'd') {
      break;
    }
  }
}

void printList(node *head, int s) {
  node *ptr;
  ptr = head;
  printf("%d :", s);
  while (ptr != NULL) {
    printf(" %d", ptr->num);
    ptr = ptr->next;
  }
  printf("\n");
  ptr = head;
}
