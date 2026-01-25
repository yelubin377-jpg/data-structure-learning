#include <stdio.h>
#include <stdlib.h>

// 单链表实现 - 带头节点版本
// 头节点really really重要！！
// 没有头节点的话插入删除都要特判，灰长麻烦


// 节点结构 

typedef struct JieDian    //创造一个节点结构体（包含数据和指向下一个节点的指针）
{
    int ShuJu;              // 存数据的
    struct JieDian *Next;   // 指向下一个
} JieDian;
//用typedef定义节点结构体，让代码更简洁，不用一直打那个struct



// 创建头节点
// WARNINGS：这里返回的是头节点，不存数据，别搞混了
// 我第一次写的时候就搞混了，把数据存头节点里了 结果遍历的时候多打印一个
JieDian *ChuangJianLianBiao()//创建链表
{
    JieDian *Head = (JieDian*)malloc(sizeof(JieDian));
    // 防背刺：malloc可能失败，实际项目要判空
    // if(Head == NULL) return NULL;  先不加了 反正不会失败
    Head->Next = NULL;
    return Head;
}//这个时候是一个空链表，妹有数据

// 判空 - 检查头节点的next是否为空
// 这个函数其实可以不要 但是写上感觉完整一点
int Judge(JieDian *Head) 
{
    return  Head->Next == NULL;   // 1表示空 0表示非空
}

// 获取长度
// 坑：从Head->Next开始数，不是从Head开始！！（因为头节点只是相当于一个入口，他没有存储数据）

int HuoQuChangDu(JieDian *Head) //获取链表长度
{
    int ChangDu = 0;//记录长度
    JieDian *p = Head->Next;  // 跳过头节点
    // JieDian *p = Head;  这样写是错的!!!会多算1
    while (p) 
    {
        ChangDu++;
        p = p->Next;//继续往下
    }
    return ChangDu;
}

// 头插法插入
// 这个比尾插法快，因为不用遍历找尾巴
void TouChaFa(JieDian *Head, int data) 
{
    JieDian *XinJieDian = (JieDian*)malloc(sizeof(JieDian));
    XinJieDian->ShuJu = data;
    // 下面这两行顺序不能反！！先连后面再连前面

    XinJieDian->Next = Head->Next;//先连接原来的下一个节点，也就是连接后面
    Head->Next = XinJieDian;//再连接前面
}

// 尾插法插入
// 这个慢一点 要遍历找尾节点 O(n)
void WeiChaFa(JieDian *Head, int data) 
{
    JieDian *p = Head;
    while (p->Next)    // 找到最后一个
    {
        p = p->Next;  
    }
    // 现在p指向最后一个节点
    JieDian *XinJieDian = (JieDian*)malloc(sizeof(JieDian));
    XinJieDian->ShuJu = data;
    XinJieDian->Next = NULL;  // 新节点是最后一个 所以Next是NULL
    p->Next = XinJieDian;     // 接上去
}

// 删除指定值的节点
// 防背刺：找的是待删除节点的前驱！不是节点本身
// 因为单链表不能往前走 所以要找前面那个
void ShanChuJieDian(JieDian *Head, int data) 
{
    JieDian *p = Head;
    // 找到值为data的节点的前一个
    while (p->Next && p->Next->ShuJu != data) 
    {
        p = p->Next;
    }
    // 找到了 或者到头了
    if (p->Next)   // 找到了
    {
        JieDian *ShanChu = p->Next;   // 先保存要删的节点
        p->Next = ShanChu->Next;      // 跳过被删节点
        free(ShanChu);  // 别忘了释放！！内存泄漏警告
        // printf("删除成功\n");  // 调试用
    }
    // else 没找到就算了，不报错
}

// 遍历打印
// 这个比较简单
void PrintLianBiao(JieDian *Head) 
{
    JieDian *p = Head->Next;  // 跳过头节点
    printf("HEAD -> ");       // 加个HEAD看着清楚一点
    while (p) 
    {
        printf("%d -> ", p->ShuJu);
        p = p->Next;
    }
    printf("NULL\n");
}

// 释放链表
// 重要！！用完一定要释放，不然内存泄漏

void XiaoHuiLianBiao(JieDian *Head) 
{
    JieDian *p = Head;
    while (p)
    {
        JieDian *LinShi = p;  // 先存起来
        p = p->Next;          // 再移动
        free(LinShi);         // 最后释放，顺序不能乱！
        // 如果先free了 那p就没法往下走了 踩过这个坑
    }
}

int main() 
{
    JieDian *LianBiao = ChuangJianLianBiao();//创建链表
    //struct JieDian *LianBiao = ChuangJianLianBiao()；
    
    // 测试插入
    WeiChaFa(LianBiao, 1);
    WeiChaFa(LianBiao, 2);
    WeiChaFa(LianBiao, 3);
    TouChaFa(LianBiao, 0);  // 头插会插到最前面
    // 所以最后结果应该是 0->1->2->3
    
    printf("链表内容: ");
    PrintLianBiao(LianBiao);
    printf("长度: %d\n", HuoQuChangDu(LianBiao));
    
    // 测试删除
    ShanChuJieDian(LianBiao, 2);
    printf("删除2后: ");
    PrintLianBiao(LianBiao);
    
    // ShanChuJieDian(LianBiao, 99);  // 删不存在的 也不会报错
    
    XiaoHuiLianBiao(LianBiao);
    // printf("释放完成 没崩\n");  // 调试用
    return 0;
}


