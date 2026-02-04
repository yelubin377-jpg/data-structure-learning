// 顺序表实现 - 支持动态扩容

#include <stdio.h>
#include <stdlib.h>

#define CHU_SHI_RONG_LIANG 4  // 初始容量

typedef struct
{
    int *ShuZu;       // 数组
    int ChangDu;      // 长度
    int RongLiang;    // 容量
} ShunXuBiao;         // 顺序表

// 初始化
int ChuShiHua(ShunXuBiao *B)  // B=表
{
    if (!B)
        return -1;
    B->ShuZu = (int *)malloc(CHU_SHI_RONG_LIANG * sizeof(int));
    if (!B->ShuZu)
        return -1;
    B->ChangDu = 0;
    B->RongLiang = CHU_SHI_RONG_LIANG;
    return 0;
}

// 扩容
static int KuoRong(ShunXuBiao *B)
{
    int XinRongLiang = B->RongLiang * 2;  // 新容量
    int *LinShi = (int *)realloc(B->ShuZu, XinRongLiang * sizeof(int));  // 临时
    if (!LinShi)
        return -1;
    B->ShuZu = LinShi;
    B->RongLiang = XinRongLiang;
    printf("KuoRong: %d -> %d\n", B->RongLiang / 2, XinRongLiang);
    return 0;
}

// 插入
int ChaRu(ShunXuBiao *B, int WeiZhi, int Zhi)  // 位置, 值
{
    if (!B || WeiZhi < 0 || WeiZhi > B->ChangDu)
        return -1;
    if (B->ChangDu >= B->RongLiang && KuoRong(B) != 0)
        return -1;
    
    for (int i = B->ChangDu; i > WeiZhi; i--)
        B->ShuZu[i] = B->ShuZu[i - 1];
    B->ShuZu[WeiZhi] = Zhi;
    B->ChangDu++;
    return 0;
}

//  追加
int ZhuiJia(ShunXuBiao *B, int Zhi)  // 值
{
    return ChaRu(B, B->ChangDu, Zhi);
}

//  删除
int ShanChu(ShunXuBiao *B, int WeiZhi, int *ShuChu)  // 位置, 输出
{
    if (!B || B->ChangDu == 0 || WeiZhi < 0 || WeiZhi >= B->ChangDu)
        return -1;
    if (ShuChu)
        *ShuChu = B->ShuZu[WeiZhi];
    for (int i = WeiZhi; i < B->ChangDu - 1; i++)
        B->ShuZu[i] = B->ShuZu[i + 1];
    B->ChangDu--;
    return 0;
}

// 打印
void DaYin(ShunXuBiao *B)
{
    if (!B)
        return;
    printf("[%d/%d]: ", B->ChangDu, B->RongLiang);
    for (int i = 0; i < B->ChangDu; i++)
        printf("%d ", B->ShuZu[i]);
    printf("\n");
}

//  销毁
void XiaoHui(ShunXuBiao *B)
{
    if (B && B->ShuZu)
    {
        free(B->ShuZu);
        B->ShuZu = NULL;
        B->ChangDu = B->RongLiang = 0;
    }
}

int main(void)
{
    ShunXuBiao LieBiao;  // 列表
    int Zhi;             // 值
    
    ChuShiHua(&LieBiao);
    
    //  添加数据
    for (int i = 1; i <= 6; i++)
        ZhuiJia(&LieBiao, i * 10);
    DaYin(&LieBiao);
    
    // 中间插入
    ChaRu(&LieBiao, 2, 999);
    DaYin(&LieBiao);
    
    //  删除
    ShanChu(&LieBiao, 3, &Zhi);
    printf("ShanChu Le: %d\n", Zhi);  // 删除了
    DaYin(&LieBiao);
    
    XiaoHui(&LieBiao);
    return 0;
}
