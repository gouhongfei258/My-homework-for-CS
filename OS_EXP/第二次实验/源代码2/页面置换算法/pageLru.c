#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ap 10 //进程页面数
#define pp 3  //内存分配的页面数
struct Page
{
    int id;
    int In;            // 1-in 0-out
    int pagecontorlID; //-1 not
};
struct Page page[ap];
struct Pagecontorl
{
    int id;
    int pageID;
    int empty; // 0-empty 1-occupy
    int usetime;//LRU_time
};
struct Pagecontorl pagecontorl[pp];
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
void init_pagecontorl()
{
    int i;
    for (i = 0; i < pp; i++)
    {
        pagecontorl[i].id = i;
        pagecontorl[i].empty = 0;
        pagecontorl[i].pageID = -1;
        pagecontorl[i].usetime = 0;
    }
}
int isFull()
{
    int i = 0;
    for(i = 0; i < pp; i++){
        if(pagecontorl[i].empty == 0) return pagecontorl[i].id;
    }
    return -1;
}
int InQueue(int id, int PageId, int time)
{
    page[PageId].pagecontorlID = id;
    pagecontorl[id].pageID = PageId;
    pagecontorl[id].usetime = time;
    pagecontorl[id].empty = 1;
}
int OutQueue(int id){
    page[id].In = 0;
    page[id].pagecontorlID = -1;
}
void show()
{
    int i;
    for(i = 0;i < pp; i++)
    {
        printf("id = %d time = %d ", pagecontorl[i].id, pagecontorl[i].usetime);
        if(pagecontorl[i].pageID == -1)
        printf("----------|");
        else printf("pageid = %d|", pagecontorl[i].pageID);
    }
    printf("\n");
}
int FindId(){
    int min = pagecontorl[0].usetime;
    int min_id = 0;
    int i;
    for(i = 1;i < pp; i++){
        if(pagecontorl[i].usetime < min){
            min = pagecontorl[i].usetime;
            min_id = pagecontorl[i].id;
        }
    }
    return min_id;
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
            pagecontorl[page[mian[i]].pagecontorlID].usetime = i;
            show();
            continue;
        }
        diseffect++;
        int id = isFull();
        if(id == -1){
            id = FindId();
            OutQueue(pagecontorl[id].pageID);
            InQueue(id, page[mian[i]].id, i);
        }
        else{
            InQueue(id, page[mian[i]].id, i);
        }
        page[mian[i]].In = 1;
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
    //show_page();
    printf("right = %lf%\n", (double)(1 - diseffect* 1.0 / ap ) * 100);
    return 0;
}