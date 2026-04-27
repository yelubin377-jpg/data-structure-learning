#ifndef _SEQLIST_H_
#define _SEQLIST_H_
#include <stdio.h>
#include <stdlib.h>


#pragma once
//#define N 100
typedef int LbDataType;
// typedef struct SeqList{    //静态顺序表
//     LbDataType a[N];
//     int size;//数组存储数据
//     int capacity;//数组实际能存储的空间容量大小
// }Lb;

typedef struct SeqList{    //动态顺序表
    LbDataType * a;
    int size;    //数组要存储多少个数据
    int capacity;//数组实际能存储多少个数据
}Lb;

//接口函数，命名风格与STL相近
void SeqList_Init(Lb *ps);//初始化
//静态：满了就不让插入
void SeqList_Pushback(Lb *ps, LbDataType x);//尾插法
void SeqList_PopBack(Lb *ps);  //尾删法
void SeqList_PushFront(Lb *ps, LbDataType x);// 头插法
void SeqList_PopFront(Lb *ps); //头删法
int SeqList_Find(Lb *ps,LbDataType x);//寻找
void SeqList_Insert(Lb *ps,int pos,LbDataType x);
void SeqList_Erase(Lb *ps,int pos);
#endif