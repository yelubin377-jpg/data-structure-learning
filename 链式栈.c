#include <stdio.h>
#include <stdlib.h>

// 链式栈实现
// 用头插法实现，入栈出栈都是O(1)



// 栈节点
// 跟链表节点差不多
typedef struct JieDian
{
    int ShuJu;                // 存数据
    struct JieDian *XiaYiGe;  // 指下一个
} JieDian;

// 栈结构（头插法实现，入栈出栈都是O(1)）
// 为什么不直接用链表？ 因为我想增加一个记录大小的变量
typedef struct
{
    JieDian *DingBu;  // 栈顶指针
    int DaXiao;       // 记录元素个数，免得每次遍历
} Zhan;

// 初始化栈
Zhan *ChuangJianZhan()
{
    Zhan *z = (Zhan *)malloc(sizeof(Zhan));

    if(z == NULL)
    {
        printf("分配失败 算了\n");
        return NULL;
    }
    z->DingBu = NULL;
    z->DaXiao = 0;
    return z;
}

// 判空
// 这个简单
int PanKong(Zhan *z)
{
    return z->DingBu == NULL;  // 返回1表示空
    // 也可以用 z->DaXiao == 0，但指针判断更直接
}

// 入栈（头插法 O(1)）
// 防背刺：新节点插在最前面，这样出栈就是O(1)
// 尾插法的话出栈要遍历找到倒数第二个 超级慢
void RuZhan(Zhan *z, int Zhi)
{
    JieDian *XinJieDian = (JieDian *)malloc(sizeof(JieDian));
    XinJieDian->ShuJu = Zhi;
    XinJieDian->XiaYiGe = z->DingBu;  // 新节点指向原栈顶
    z->DingBu = XinJieDian;           // 更新栈顶
    z->DaXiao++;
    // printf("入栈: %d\n", Zhi);  // 调试用
}

// 出栈
// 返回栈顶元素并删除，栈空返回-1
// 其实应该用指针传出错误码的 但是这样写简单点
int ChuZhan(Zhan *z)
{
    if (PanKong(z))
    {
        printf("栈空了兄弟!\n");  // 其实不应该这样 但是方便调试
        return -1;
    }
    JieDian *ShanChu = z->DingBu;
    int Zhi = ShanChu->ShuJu;
    z->DingBu = ShanChu->XiaYiGe;  // 栈顶下移
    free(ShanChu);  // 释放！！
    z->DaXiao--;
    return Zhi;
}

// 获取栈顶（不删除）
// 只看一眼，不拿走 类似于peek
int HuoQuDing(Zhan *z)
{
    if (PanKong(z))
    {
        return -1;  // 空栈返回-1
    }
    return z->DingBu->ShuJu;
}

// 释放栈
// 一个一个pop掉，最后释放栈结构本身
void XiaoHuiZhan(Zhan *z)
{
    // 先把所有节点pop掉
    while (!PanKong(z))
    {
        ChuZhan(z);  // 复用出栈函数，懒得再写一遍
    }
    free(z);  // 别忘了栈本身也要释放！！
    // 第一次写的时候忘了这个 结果valgrind报错
}

int main()
{
    Zhan *z = ChuangJianZhan();
    
    // 入栈测试 
    // 入栈顺序10 20 30，栈顶是30
    RuZhan(z, 10);
    RuZhan(z, 20);
    RuZhan(z, 30);
    
    printf("栈顶: %d\n", HuoQuDing(z));  // 应该是30
    printf("出栈: %d\n", ChuZhan(z));    // 30
    printf("出栈: %d\n", ChuZhan(z));    // 20
    printf("栈顶: %d\n", HuoQuDing(z));  // 10
    
    // ChuZhan(z);  // 再出一次就剩空栈了
    // ChuZhan(z);  // 这次会打印“栈空了兄弟”
    
    XiaoHuiZhan(z);
    return 0;
}

// 复杂度分析（考试常考！）：
// 头插法：入栈O(1)，出栈O(1) OK 推荐
// 尾插法：入栈O(n)，出栈O(n) 垃圾 别用
//
// 为啥尾插法慢？因为单链表没法O(1)找到尾节点的前驱
// 除非用双向链表，但那就复杂了

