#include <stdio.h>
#include <stdlib.h>

typedef struct node{
  struct node* next;
  int value;
} node_t;

typedef struct queue{
  struct node* tail;
  int size;
} queue_t  ;

/*
* Add @val value at the head of the @q queue
*
* @val     : the value to enqueue
* @q     : the queue
*
* @return 0 if no error, -1 otherwise
*
* pre : The queue q will always be valid, you don't need to handle the NULL case.
*/
int enqueue(queue_t* q, int val){
    struct node * node_ptr = (struct node *)malloc(sizeof(struct node));
    if (node_ptr == NULL) return -1;
    node_ptr->value = val;
    q->size++;
    struct node * head = q->tail != NULL && q->tail->next != NULL ? q->tail->next : NULL;
    if ( q->tail == NULL) q->tail = node_ptr;
    else q->tail->next = node_ptr;
    if ( head != NULL ) node_ptr->next = head;
    else node_ptr->next = node_ptr;
    return 0;
}


/*
* Remove the node at the tail of the @q queue and return the value of this node
* @q         : the queue
* @return     : the value at the tail
*
* pre         : The given queue will always be valid, you do not need to handle the NULL case.
*/
int dequeue(queue_t* q){
    if ( q->size == 0) return -1;
    int value = q->tail->value;
    struct node * prev = NULL;
    struct node * head = q->tail != NULL && q->tail->next != NULL ? q->tail->next : NULL;
    if ( q->tail != NULL && q->tail->next != NULL) {
        for ( struct node * current = q->tail->next; current != q->tail; current = current->next) {
            prev = current;
        }
    }
    free(q->tail);
    q->tail = prev;
    q->size--;
    if ( prev != NULL) prev->next = head;
    return value;
}

void showqueue(queue_t* q) {
    printf("Display elements in the Queue\n");
    printf("-----------------------------\n");
    if ( q == NULL || q->size == 0) return;
    struct node * head = q->tail != NULL && q->tail->next != NULL ? q->tail->next : NULL;
    for (struct node * current = head; current != q->tail; current = current->next) {
        printf("Element remaining in queue %d\n", current->value);
    }
    if (q->tail != NULL ) printf("Element remaining in queue %d\n", q->tail->value);
}

int main()
{
    printf("Exercice Advanced Queue\n");
    printf("***********************\n\n");
    struct queue myqueue = {NULL, 0};
    printf("Add 10 elements in queue\n");
    printf("------------------------\n");
    for ( int i=9; i >= 0; i--) {
        int rc = enqueue(&myqueue, i);
        if (rc == 0) printf("Element added %d\n", i);
        else printf("ERROR when adding element %d\n", i);
    }
    showqueue(&myqueue);
    printf("Display first element in queue\n");
    printf("------------------------------\n");
    printf("First element %d\n", myqueue.tail->next->value);
    printf("Display last element in queue\n");
    printf("---------------------------------\n");
    printf("Last element %d\n", myqueue.tail->value);

    int i09 = dequeue(&myqueue);
    printf("Remove 1 element at tail\n");
    printf("------------------------\n");
    printf("Element removed %d\n", i09);

    printf("Display first element in queue\n");
    printf("------------------------------\n");
    printf("First element %d\n", myqueue.tail->next->value);
    printf("Display last element in queue\n");
    printf("-----------------------------\n");
    printf("Last element %d\n", myqueue.tail->value);

    showqueue(&myqueue);
    printf("Remove all remaining elements in queue\n");
    printf("--------------------------------------\n");
    int nbrelemtoremove = myqueue.size;
    for ( int i=0; i < nbrelemtoremove; i++) {
        int value = dequeue(&myqueue);
        printf("Element removed %d\n", value);
    }
    showqueue(&myqueue);
    int i00 = enqueue(&myqueue, 0);
    printf("Add 1 element\n");
    printf("-------------\n");
    printf("Element added %d\n", i00);
    showqueue(&myqueue);
    return 0;
}
