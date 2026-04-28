#include"SeqList.h"
#include <stdio.h> 


void TestSeqList1()
{
    Lb lb;
    SeqList_Init(&lb); 
    SeqList_Pushback(&lb, 100);
    SeqList_Pushback(&lb, 200);
    SeqList_Pushback(&lb, 300);
    SeqList_Pushback(&lb, 400);
    SeqList_PushFront(&lb,500);
    SeqList_Pushback(&lb,40);
    SeqList_PopFront(&lb);
    SeqList_Insert(&lb,2,4000);
    SeqList_Erase(&lb,3);
    for(int i = 0;i<=lb.size -1;i++)
    {
        printf("%d\n",lb.a[i]);
    }
    SeqList_Find(&lb,400);
    SeqList_Destroy(&lb);
    
}



int main()
{
    TestSeqList1();

    return 0;
}