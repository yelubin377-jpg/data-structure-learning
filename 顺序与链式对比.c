
#include <stdio.h>
#include <stdlib.h>




typedef struct
{
    int *Yuan;     // 存元素的数组
    int Ge;        // 当前几个
    int Rong;      // 总共能放几个
} ShunXu;
  
void SX_JianLi(ShunXu *S, int Rong)
{
    S->Yuan = (int *)malloc(Rong * sizeof(int));
    S->Ge = 0;
    S->Rong = Rong;
}

// 插入的时候顺便数一下移动了几次
void SX_ChaRu(ShunXu *S, int Wei, int Zhi)
{
    if (S->Ge >= S->Rong || Wei < 0 || Wei > S->Ge)
        return;
    int YiDongCi = 0;
    // 从后往前挪 给新元素腾位置
    for (int i = S->Ge; i > Wei; i--)
    {
        S->Yuan[i] = S->Yuan[i - 1];
        YiDongCi++;
    }
    S->Yuan[Wei] = Zhi;
    S->Ge++;
    printf("  [ShunXu] ChaRu Wei=%d, Zhi=%d, YiDong %d Ci\n", Wei, Zhi, YiDongCi);
}

void SX_ShanChu(ShunXu *S, int Wei)
{
    if (Wei < 0 || Wei >= S->Ge)
        return;
    printf("  [ShunXu] ShanChu Wei=%d, BeiShanDe=%d", Wei, S->Yuan[Wei]);
    int YiDongCi = 0;
    // 从前往后覆盖 把后面的往前搬
    for (int i = Wei; i < S->Ge - 1; i++)
    {
        S->Yuan[i] = S->Yuan[i + 1];
        YiDongCi++;
    }
    S->Ge--;
    printf(", YiDong %d Ci\n", YiDongCi);
}

// 这个就是顺序表的优势了 直接下标就能访问
int SX_FangWen(ShunXu *S, int Wei)
{
    return S->Yuan[Wei];
}

void SX_DaYin(ShunXu *S)
{
    printf("  ShunXu[%d/%d]: ", S->Ge, S->Rong);
    for (int i = 0; i < S->Ge; i++)
        printf("%d ", S->Yuan[i]);
    printf("\n");
}

void SX_ShiFang(ShunXu *S)
{
    free(S->Yuan);
    S->Yuan = NULL;
    S->Ge = S->Rong = 0;
}


// 链表部分 带头节点的  上次不带头节点被坑惨了

typedef struct LJD
{
    int Zhi;
    struct LJD *Xia;   // 下一个
} LianJie;

LianJie *LB_JianLi()
{
    LianJie *Tou = (LianJie *)malloc(sizeof(LianJie));
    // malloc失败就不管了 学习用的
    Tou->Xia = NULL;
    return Tou;
}

void LB_ChaRu(LianJie *Tou, int Wei, int Zhi)
{
    LianJie *P = Tou;
    int BuShu = 0;
    for (int i = 0; i < Wei && P; i++)
    {
        P = P->Xia;
        BuShu++;
    }
    if (!P)
        return;
    LianJie *Xin = (LianJie *)malloc(sizeof(LianJie));
    Xin->Zhi = Zhi;
    // 先接后面再接前面！！ 顺序反了就断链了
    Xin->Xia = P->Xia;
    P->Xia = Xin;
    printf("  [LianBiao] ChaRu Wei=%d, Zhi=%d, BianLi %d Bu, GaiZhiZhen 2Ci\n",
           Wei, Zhi, BuShu);
}

// 删除也是 要找前驱节点 不然没法操作
void LB_ShanChu(LianJie *Tou, int Wei)
{
    LianJie *P = Tou;
    int BuShu = 0;
    for (int i = 0; i < Wei && P->Xia; i++)
    {
        P = P->Xia;
        BuShu++;
    }
    if (!P->Xia)
        return;
    LianJie *Shan = P->Xia;
    printf("  [LianBiao] ShanChu Wei=%d, BeiShanDe=%d, BianLi %d Bu\n",
           Wei, Shan->Zhi, BuShu);
    P->Xia = Shan->Xia;
    free(Shan);  // 别忘了free！
}

int LB_FangWen(LianJie *Tou, int Wei)
{
    LianJie *P = Tou->Xia;
    int BuShu = 0;
    for (int i = 0; i < Wei && P; i++)
    {
        P = P->Xia;
        BuShu++;
    }
    printf("  [LianBiao] FangWen Wei=%d, BianLi %d Bu cai ZhaoDaoLe\n", Wei, BuShu);
    return P ? P->Zhi : -1;
}

void LB_DaYin(LianJie *Tou)
{
    printf("  LianBiao: Tou");
    LianJie *P = Tou->Xia;
    while (P)
    {
        printf("->%d", P->Zhi);
        P = P->Xia;
    }
    printf("->NULL\n");
}

void LB_ShiFang(LianJie *Tou)
{
    LianJie *P = Tou;
    while (P)
    {
        LianJie *LinShi = P;
        P = P->Xia;
        free(LinShi);
        // 一定要先存再移再释放 顺序不能乱 上次踩过坑
    }
}


int main(void)
{
    ShunXu S;
    LianJie *L = LB_JianLi();
    SX_JianLi(&S, 10);

    // 先都往尾部插几个数据
    printf("WeiBu ChaRu 10 20 30 40:\n");
    int ShuJu[] = {10, 20, 30, 40};
    for (int i = 0; i < 4; i++)
    {
        SX_ChaRu(&S, S.Ge, ShuJu[i]);
        LB_ChaRu(L, i, ShuJu[i]);
    }
    SX_DaYin(&S);
    LB_DaYin(L);
    // 尾部插入顺序表不用移动 链表要遍历到尾巴 各有各的代价

    // 试试头部插入 这个差距应该很明显
    printf("\nTouBu ChaRu 99:\n");
    SX_ChaRu(&S, 0, 99);
    LB_ChaRu(L, 0, 99);
    SX_DaYin(&S);
    LB_DaYin(L);
    // 果然 顺序表头插要挪4个元素 链表改两个指针就完事了

    // 中间插入
    printf("\nZhongJian ChaRu(Wei=2, Zhi=55):\n");
    SX_ChaRu(&S, 2, 55);
    LB_ChaRu(L, 2, 55);
    SX_DaYin(&S);
    LB_DaYin(L);

    // 测测随机访问 这个顺序表碾压
    printf("\nFangWen Di3Ge YuanSu:\n");
    printf("  [ShunXu] ZhiJie XiaBiao FangWen O(1), Zhi=%d\n", SX_FangWen(&S, 3));
    int LBZhi = LB_FangWen(L, 3);
    printf("  DeDaoZhi: %d\n", LBZhi);
    // 顺序表直接S.Yuan[3]就完了 链表得从头遍历3步

    // 删除头部
    printf("\nShanChu TouBu:\n");
    SX_ShanChu(&S, 0);
    LB_ShanChu(L, 0);
    SX_DaYin(&S);
    LB_DaYin(L);

    printf("\n--- ZongJie ---\n");
    printf("  ShunXu: NeiCun LianXu, FangWen O(1), ChaRu/ShanChu O(n)\n");
    printf("  LianShi: NeiCun LiSan, FangWen O(n), ChaRu/ShanChu O(1)\n");

    SX_ShiFang(&S);
    LB_ShiFang(L);
    return 0;
}
