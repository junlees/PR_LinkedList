#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

//노드 타입 정의
typedef struct node {
    int data;
    struct node* link;
} node; 


void makeList(node** hptr); // 복수개의 입력되는 데이터를 단순연결리스트로 만드는 기능
void viewList(node* hptr); // 만들어진 단순연결리스트의 데이터를 순서대로 출력하는 기능
node* findLast(node* hptr); //리스트의 맨 마지막 노드를 찾는 기능으로 그 포인터를 리턴함
int findPosition(node* hptr, int data, node** pptr, node** preptr); /*이 기능은 전달인자로 입력되는 데이터를 리스트에서 찾아 만약 리스트에
                                                                    존재하면 1 을 리턴하고 만약 데이터가 리스트에 존재하지 않으면 0 을 리턴한다. 또한
                                                                    리스트의 헤더 포인터외 찾는 데이터를 가르키는 포인터와 그 노드의 이전노드를 가르키는
                                                                    포인터를 전달인자로 전달하여 만약 존재 한다며 그 포인터 값을 저장하여야 함*/

void insertList(node** hptr, node* pptr, int data); /*새로운 데이터를 리스트에 삽입하는 기능으로 전달인자로 리스트 헤더 포인터,
                                                    어디 다음에 삽입해야 하는지 알려주는 포인터, 그리고 삽입할 데이터를 전달인자로 전달
                                                    받으며 이 기능에서 새로운 노드를 생성하여 삽입하여야 함. 또한, 리스트 생성, 즉
                                                    makeList 에서 이 기능을 호출하여 리스트를 생성하여야 함.*/

void deleteList(node** hptr, node* pptr, node* preptr); //리스트에 원하는 데이터를 삭제하는 기능으로 전달인자로, 리스트 헤더 포인터, 그리고 삭제를 원하는 노드의 포인터 및 이전 포인터가 사용됨.

//============================================================================================//

int main() {
    node* head = NULL;
    node* pptr = NULL;
    node* preptr = NULL;
    int data, location;
    int num;

    //노드 생성
    makeList(&head);

    //생성된 리스트 출력
    viewList(head);

    while (1) {
        printf("(1)Delete  (2)Insert  (3)Quit\n");
        printf("Select Menu\n");
        scanf("%d", &num);
        switch (num) {
        //리스트 삭제
        case 1:
            printf("Data : ");
            scanf("%d", &data);
            if (findPosition(head, data, &pptr, &preptr)) {
                deleteList(&head, pptr, preptr);
                printf("Delete Complite\n");
            }
            else 
                printf("Delete Fail\n");
            viewList(head);
            break;

        //리스트 삽입
        case 2:
            printf("Insert Data : ");
            scanf("%d", &data);
            printf("Location : ");
            scanf("%d", &location);
            if (findPosition(head, location, &pptr, &preptr)) {
                insertList(&head, preptr, data);
                printf("Insert Complite.\n");
            }
            else 
                printf("Insert Fail.\n");
            viewList(head);
            break;

        //종료
        case 3:
            return 0;

        default:
            break;
        }
    }
    return 0;
}

//============================================================================================//

node* findLast(node* hptr) {
    while (hptr->link != NULL) {
        hptr = hptr->link;
    }
    return hptr;
}

int findPosition(node* hptr, int data, node** pptr, node** preptr) {
    node* pre = NULL;
    node* ptr = hptr;
    while (ptr != NULL) {
        if (ptr->data == data) {
            *pptr = ptr;
            *preptr = pre;
            return 1;
        }
        pre = ptr;
        ptr = ptr->link;
    }
    return 0;
}

void insertList(node** hptr, node* pptr, int data) {
    node* new;
    new = (node*)malloc(sizeof(node));

    new->data = data;
    if (*hptr == NULL) {
        *hptr = new;
        new->link = NULL;
    }
    else if (pptr == NULL) {
        new->link = *hptr;
        *hptr = new;
    }
    else {
        new->link = pptr->link;
        pptr->link = new;
    }
    return;
}

void deleteList(node** hptr, node* pptr, node* preptr) {
    if (preptr == NULL) {
        *hptr = pptr->link;
    }
    else {
        preptr->link = pptr->link;
    }
    free(pptr);
    return;
}

void makeList(node** hptr) {
    node* pre = NULL;
    node* new = NULL;
    int data;

    printf("입력할 데이터는 < enter -1 to end>\n");
    scanf("%d", &data);
    while (data != -1) {
        insertList(hptr, pre, data);
        pre = findLast(*hptr);
        printf("Enter data again\n");
        scanf("%d", &data);
    }
    return;
}

void viewList(node* hptr) {
    node* ptr = hptr;

    printf("List : ");
    while (ptr != NULL) {
        printf("%d ", ptr->data);
        ptr = ptr->link;
    }
    printf("\n");
    return;
}

