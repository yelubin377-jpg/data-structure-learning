
#include <stdio.h>
#include <stdlib.h>

#define RONG_LIANG 20

typedef struct
{
    int Yuan[RONG_LIANG];
    int Ge;      // 当前元素个数
} ShunXuBiao;

void ChuShiHua(ShunXuBiao *B)
{
    B->Ge = 0;
}

// 插入 返回这次移动了几个元素
int ChaRu(ShunXuBiao *B, int Wei, int Zhi)
{
    if (B->Ge >= RONG_LIANG || Wei < 0 || Wei > B->Ge)
        return -1;
    int YiDong = 0;
    for (int i = B->Ge; i > Wei; i--)
    {
        B->Yuan[i] = B->Yuan[i - 1];
        YiDong++;
    }
    B->Yuan[Wei] = Zhi;
    B->Ge++;
    return YiDong;
}

// 删除也返回移动次数
int ShanChu(ShunXuBiao *B, int Wei)
{
    if (Wei < 0 || Wei >= B->Ge)
        return -1;
    int YiDong = 0;
    for (int i = Wei; i < B->Ge - 1; i++)
    {
        B->Yuan[i] = B->Yuan[i + 1];
        YiDong++;
    }
    B->Ge--;
    return YiDong;
}

// 重置表内容 方便反复测试
void TianChong(ShunXuBiao *B, int GeShu)
{
    B->Ge = 0;
    for (int i = 0; i < GeShu && i < RONG_LIANG; i++)
    {
        B->Yuan[i] = (i + 1) * 10;
        B->Ge++;
    }
}

void DaYin(ShunXuBiao *B)
{
    printf("  [");
    for (int i = 0; i < B->Ge; i++)
        printf("%s%d", i ? "," : "", B->Yuan[i]);
    printf("] (Ge=%d)\n", B->Ge);
}

int main(void)
{
    ShunXuBiao B;
    int CiShu;

    // 先看看在不同位置插入分别要移动多少次
    printf("ChaRu CeShi (n=8)\n\n");

    // 头部插入
    TianChong(&B, 8);
    CiShu = ChaRu(&B, 0, 999);
    printf("TouBu ChaRu: YiDong %d Ci\n", CiShu);
    DaYin(&B);


    // 中间插入
    TianChong(&B, 8);
    CiShu = ChaRu(&B, 4, 999);
    printf("ZhongJian ChaRu(Wei=4): YiDong %d Ci\n", CiShu);
    DaYin(&B);

    // 尾部插入
    TianChong(&B, 8);
    CiShu = ChaRu(&B, 8, 999);
    printf("WeiBu ChaRu: YiDong %d Ci\n", CiShu);
    DaYin(&B);
    // 0次！ 尾部插不用挪任何东西

    // 再看删除
    printf("\nShanChu CeShi (n=8)\n\n");

    TianChong(&B, 8);
    CiShu = ShanChu(&B, 0);
    printf("ShanChu TouBu: YiDong %d Ci\n", CiShu);
    DaYin(&B);

    TianChong(&B, 8);
    CiShu = ShanChu(&B, 3);
    printf("ShanChu ZhongJian(Wei=3): YiDong %d Ci\n", CiShu);
    DaYin(&B);

    TianChong(&B, 8);
    CiShu = ShanChu(&B, 7);
    printf("ShanChu WeiBu: YiDong %d Ci\n", CiShu);
    DaYin(&B);
    // 也是0次

    // 想看看n变大的时候 头插的移动次数是不是线性增长
    printf("\nn ZengDa, TouCha YiDongCiShu\n\n");
    int GuiMo[] = {2, 4, 6, 8, 10, 12};
    for (int t = 0; t < 6; t++)
    {
        TianChong(&B, GuiMo[t]);
        CiShu = ChaRu(&B, 0, 999);
        printf("n=%2d -> YiDong %2d Ci\n", GuiMo[t], CiShu);
    }
    // 确实是线性的 n=2移2次 n=12移12次

    // 最后算一下平均移动次数 看看是不是真的等于 n/2
    printf("\nPingJun YiDongCiShu (n=10)\n\n");
    int ZongCha = 0, ZongShan = 0;
    int N = 10;

    // 插入: 在每个位置(0到n)都插一次 加起来
    for (int i = 0; i <= N; i++)
    {
        TianChong(&B, N);
        ZongCha += ChaRu(&B, i, 0);
    }
    for (int i = 0; i < N; i++)
    {
        TianChong(&B, N);
        ZongShan += ShanChu(&B, i);
    }

    printf("ChaRu: Zong %d Ci / %d Ge WeiZhi = PingJun %.1f\n",
           ZongCha, N + 1, (float)ZongCha / (N + 1));
    printf("ShanChu: Zong %d Ci / %d Ge WeiZhi = PingJun %.1f\n",
           ZongShan, N, (float)ZongShan / N);
    printf("LiLun: ChaRu PingJun n/2=%.1f, ShanChu PingJun (n-1)/2=%.1f\n",
           N / 2.0, (N - 1) / 2.0);


    return 0;
}

