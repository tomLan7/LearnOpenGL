#include<stdio.h>
#include<stdlib.h>
struct Node//定¨义?链ⅰ?表括?的?结á点?类え?型í
{
    int data;
    struct Node* next;
};
typedef  struct Node   LNode;
typedef  struct Node* LinkList;
LinkList CreateTailList(int n);    //用?尾2插?法ぁ?创洹?建¨带?n个?结á点?的?单蹋?链ⅰ?表括?
void OutputList(LinkList L);       //输?出?单蹋?链ⅰ?表括?
LinkList DestroyList(LinkList  L);     //销ú毁ù单蹋?链ⅰ?表括?
int MaxList(LinkList  L);          //求ó单蹋?链ⅰ?表括?最?大洙?值μ

int main()
{
    LinkList  head;          //定¨义?一?个?LinkList 型í的?变?量?head
    int n;

    scanf("%d", &n);              //输?入?结á点?的?个?数簓 
    head = CreateTailList(n);     //用?尾2插?法ぁ?输?入?数簓据Y创洹?建¨单蹋?链ⅰ?表括?
    OutputList(head);            //输?出?单蹋?链ⅰ?表括?输?出?格?式? "%d "
    printf("max=%d\n", MaxList(head));
    head = DestroyList(head);        //销ú毁ù以?head为a头?的?链ⅰ?表括?各÷结á点?
    if (head == NULL)
        printf("链ⅰ?表括?已?销ú毁ù");
}
LinkList CreateTailList(int n)
{
    /********** Begin **********/
    LNode* head, * newNode, * preNode;                      //
    head = (LinkList)malloc(sizeof(LNode));     //
    head->next = NULL;                          //
    preNode = head;//准备开始循环，preNode就是head节点
    for (int i = 0; i < n; i++)                 //
    {
        newNode = (LinkList)malloc(sizeof(LNode));    //
        scanf("%d", &newNode->data);                  //
        newNode->next = NULL;                         //
        preNode->next = newNode;                            //
        preNode = newNode;//让下一次循环时，pre存储的也是新节点的前一个节点
    }
    /********** End **********/
    return head;
}

void OutputList(LinkList  head)
{
    LNode* p = head->next;
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
}

LinkList DestroyList(LinkList  head)
{
    LNode* p;
    p = head->next;
    while (p != NULL) {
        LNode* backup = p->next;
        free(p);
        p = backup;
    }
    return head;
}

int MaxList(LinkList  head)
{
    LNode* p = head->next, * pmax=NULL;
    while (p != NULL) {
        if (pmax == NULL) {
            pmax = p;
        }
        else {
            if (p->data > pmax->data)
            {
                pmax = p;
            }
        }
        p = p->next;
    }
    return pmax->data;
}
