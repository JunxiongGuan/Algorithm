/*
 * Author: guanjx09
 * Date: 20190914
 * Brief: Stack interface and implementation in C
 */

#define TRUE 1
#define FALSE 0

typedef int DataType;

typedef struct Node {
    DataType data;
    struct Node *next;
} LinkedList;

/* This is a object-orientated stack */
typedef struct {
   /* data */
   LinkedList *head; 

   /* interfae */
   void (*push)(Stack *self, DataType data);
   DataType (*pop)(Stack *self);
   int (*isEmpty)(Stack *self);
} Stack;

static LinkedList *CreateNode(DataType *data)
{
    LinkedList *node = malloc(sizeof(*node));
    if (node == NULL) {
        printf("Malloc failed.");
        return NULL;
    }
    node->next = NULL;
    node->data = *data;

    return node;
}

static LinkedList *DestroyNode(LinkedList *node)
{
    if (node != NULL) {
        free(node);
    }
}

void Push(Stack *self, DataType data)
{
    LinkedList *node = CreateNode(&data);
    if (node == NULL) {
        printf("Push error\n");
        return;
    }

    node->next = self->head;
    self->head = node;
}

DataType (*Pop)(Stack *self)
{
    DataType data;
    LinkedList *currNode = NULL;

    currNode =  self->head;
    data = currNode->data;
    self->head = currNode->next;

    /* destroy the node */
    DestroyNode(currNode);

    return data;
}

int (*IsEmpty)(Stack *self)
{
    return self->head == NULL ? TRUE : FALSE;
}

static void InitStack(Stack *stack)
{
    stack->head = NULL;
    stack->push = Push;
    stack->pop = Pop;
    stack->isEmpty = IsEmpty;
}

int TestCase1(void)
{
    Stack stack = { NULL };
    char ch;

    InitStack(&stack);

    while(scanf("%c", &ch) != EOF) {
        if (ch == '-') {
            if (IsEmpty(&stack)) {
                printf("Pop empty stack\n");
                continue;
            }
            printf("%c ", stack.pop(&stack));
        } else {
            stack.push(&stack, ch);
        }
    }

    printf("\n print unpoped data:\n");
    while(IsEmpty(&stack)) {
        printf("%c ", stack.pop(&stack));
    }
    printf("\n");
}

int main(void)
{
    printf("------Hello world start-----\n");

    TestCase1();

    printf("------Hello world end-------\n");

    return 0;
}

