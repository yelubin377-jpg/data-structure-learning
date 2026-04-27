#include "SeqList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <inttypes.h>
#include <stdint.h>
#include <assert.h>
#include <stdio.h>
//接口函数，命名风格与STL相近
void SeqList_Init(Lb *ps)//初始化
{
    ps->a = (LbDataType*)malloc(sizeof(LbDataType)*4);        
    if(ps->a == NULL)
    {
        perror("fail to malloc");
        exit(-1);
    }
    ps->a[0] = 1;
    ps->a[1] = 2;
    ps->a[2] = 3;
    ps->a[3] = 40;
    ps->size = 4;        //数组要存储的数据个数
    ps->capacity = 4;    //数组实际能够存储的数据个数
}
//静态：满了就不让插入
void SeqList_Pushback(Lb *ps, LbDataType x)//尾插法
{
    //没有空间，开空间
    //空间不够，继续开空间
    if(ps->size == ps->capacity)
    {
        ps->a = (LbDataType*)realloc(ps->a,sizeof(LbDataType) * ps->capacity * 2);
        if(ps->a == NULL)
        {
            perror("fail to realloc");
            exit(-1);
        }
        ps->a[ps->size] = x;
        ps->size++;
        ps->capacity *= 2;
    }
    //空间足够，直接插入数据就行
    else
    {
        ps->a[ps->size] = x;
        ps->size++;
    }
}
void SeqList_PopBack(Lb *ps) //尾删法
{
    if(ps->size == 0)
    {
        return;
    }
    //assert(ps->size > 0);  //必须是这种情况，否则直接退出程序并报错
    ps->size--;
}
void SeqList_PushFront(Lb *ps, LbDataType x)// 头插法
{
    if(ps->size == ps->capacity)
    {
        ps->a = (LbDataType*)realloc(ps->a,sizeof(LbDataType)*ps->capacity*2);
        if(NULL == ps->a)
        {
            perror("fail to realloc -- from PushFront");
            exit(-1);
        }
        ps->capacity *= 2;
    }
    if(ps->size-1 >= 0)
    {
        for(int i = ps->size - 1;i>=0;i--)//从最后一个元素开始，前面元素全部向后退一个位置，覆盖调后面的
        {
            ps->a[i+1] = ps->a[i]; 
        }
    }
    ps->a[0] = x;
    ps->size++;

}
void SeqList_PopFront(Lb *ps) //头删法
{
    if(ps->size-1 >= 0)
    {
        for(int i = 1;i<=ps->size-1;i++)
        {
            ps->a[i-1] = ps->a[i];   
        }
        ps->size--;
    }
}
int SeqList_Find(Lb *ps,LbDataType x)
{
    for(int i = 0;i<ps->size;i++)
    {
        if(ps->a[i] == x)
        {
            printf("We could Find it!\n");
            printf("%d\n",i);
        }
    }
    for(int i = 0;i<ps->size;i++)
    {
        if(ps->a[i] == x)
        {
            return 0;
        }
    }
    printf("We couldn't Find it!\n");

}


void SeqList_Insert(Lb *ps,int pos,LbDataType x)//pos指下标位置
{
    if(pos<0||pos>ps->size-1)
    {
        return;
    }
    for(int i = ps->size-1;i>=pos;i--)
    {
        if(ps->size == ps->capacity)
        {
            ps->a = (LbDataType*)realloc(ps->a,sizeof(LbDataType)*ps->capacity*2);
            if(ps->a == NULL)
            {
                perror("fail to realloc -- from SeqList_Insert");
                exit(-1);
            }
        }
        ps->a[i+1] = ps->a[i];
    }
    ps->a[pos] = x;
    ps->size++;
}

void SeqList_Erase(Lb *ps,int pos)
{
    for(int i = pos+1;i <= ps->size-1;i++)
    {
        ps->a[i-1] = ps->a[i];
    }
    ps->size--;
}