#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ap 10 //进程页面数
#define pp 3  //内存分配的页面数
struct Page
{
    int id;
    int In;            // 1-in 0-out
    int pagecontorlID; //-1
};
struct Page page[ap];
struct Pagecontorl
{
    int id;
    int pageID;
    int empty; // 0-empty 1-occupy
    struct Pagecontorl *next;
};
struct Pagecontorl *first;
int diseffect; 
void init_page()
{
    int i;
    for (i = 0; i < ap; i++)
    {
        page[i].id = i;
        page[i].In = 0;
        page[i].pagecontorlID = -1;
    }
}
void init_pagecontorl()//初始化内存分配页面
{
    first = (struct Pagecontorl *)malloc(sizeof(struct Pagecontorl));
    struct Pagecontorl *p = first;
    int i = 0;
    for (i = 0; i < pp; i++)
    {
        struct Pagecontorl *q = (struct Pagecontorl *)malloc(sizeof(struct Pagecontorl));
        q->id = i;
        q->pageID = -1;
        q->empty = 0;
        p->next = q;
        q->next = NULL;
        p = q;
    }
}
int isFull()//判断页面是否分配完了
{
    struct Pagecontorl *p = first->next;
    while (1)
    {
        if (p->empty == 0)
            return 0;
        if (p->next == NULL)
            break;
        else
            p = p->next;
    }
    return 1;
}
int InQueue(int PageId)//入队
{
    struct Pagecontorl *p = first->next;
    while (p->next != NULL)
    {
        if (p->empty == 0)
            break;
        p = p->next;
    }
    if (p->empty == 0)
    {
        p->pageID = PageId;
        p->empty = 1;
        return p->id;
    }
    else
    {
        struct Pagecontorl *q = (struct Pagecontorl *)malloc(sizeof(struct Pagecontorl));
        q->pageID = PageId;
        q->empty = 1;
        q->next = NULL;
        p->next = q;
        q->id = p->id + 1;
        return q->id;
    }
}
void OutQueue()//出队
{
    int i = 0;
    struct Pagecontorl *p = first->next;
    struct Pagecontorl *q = p->next;
    while (1)
    {
        q->id = i;
        page[q->pageID].pagecontorlID = q->id;
        i++;
        if (q->next == NULL)
            break;
        q = q->next;
    }
    page[p->pageID].In = 0;
    page[p->pageID].pagecontorlID = -1;
    first->next = p->next;
    free(p);
}
void show()
{
    struct Pagecontorl *p = first->next;
    while (1)
    {
        printf("id = %d ", p->id);
        if(p->pageID == -1)
        printf("----------|");
        else printf("pageid = %d|", p->pageID);
        if (p->next == NULL)
            break;
        p = p->next;
    }
    printf("\n");
}
void FIFO()
{
    int mian[ap];
    diseffect = 0;
    srand((unsigned)time(0));
    int i;
    for (i = 0; i < ap; i++)
        mian[i] = rand() % ap;
    printf("mian : ");
    for (i = 0; i < ap; i++)
        printf("%d ", mian[i]);
    printf("\n");
    for (i = 0; i < ap; i++)
    {
        if (page[mian[i]].In)
        {
            show();
            continue;
        }
        diseffect++;
        page[mian[i]].In = 1;
        if (isFull())
            OutQueue();
        page[mian[i]].pagecontorlID = InQueue(page[mian[i]].id);
        show();
    }
}
void show_page(){
    for(int i = 0;i < ap; i++){
        printf("padeid = %d ", page[i].pagecontorlID);
    }
    printf("\n");
}
int main()
{
    init_page();
    init_pagecontorl();
    FIFO();
    show_page();
    printf("right = %lf%\n", (double)(1 - diseffect* 1.0 / ap ) * 100);
    return 0;
}