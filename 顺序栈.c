//
// 顺序栈实现

#include <stdio.h>
#include <stdlib.h>

#define ZUI_DA_RONG_LIANG 10  // 最大容量

typedef struct
{
    int ShuJu[ZUI_DA_RONG_LIANG];  // 数据
    int DingBu;                    // 顶部 (ZhanDing XiaBiao, -1 BiaoShi Kong 栈顶下标,-1表示空)
} Zhan;                            // 栈

//  初始化
void ChuShiHua(Zhan *Z)  // Z=栈
{
    Z->DingBu = -1;
}

// 是否为空
int ShiFouWeiKong(Zhan *Z)
{
    return Z->DingBu == -1;
}

// 是否已满
int ShiFouYiMan(Zhan *Z)
{
    return Z->DingBu == ZUI_DA_RONG_LIANG - 1;
}

//  入栈
int RuZhan(Zhan *Z, int Zhi)  // 值
{
    if (ShiFouYiMan(Z))
        return -1;
    Z->ShuJu[++Z->DingBu] = Zhi;
    return 0;
}

// 出栈
int ChuZhan(Zhan *Z, int *Zhi)  // 值
{
    if (ShiFouWeiKong(Z))
        return -1;
    *Zhi = Z->ShuJu[Z->DingBu--];
    return 0;
}

//  查看顶
int ChaKanDing(Zhan *Z)
{
    if (ShiFouWeiKong(Z))
        return -1;
    return Z->ShuJu[Z->DingBu];
}

//  打印栈
void DaYinZhan(Zhan *Z)
{
    printf("Zhan: ");  // 栈
    for (int i = 0; i <= Z->DingBu; i++)
        printf("%d ", Z->ShuJu[i]);
    printf("\n");
}

//  检查括号
//  括号匹配检测
int JianChaKuoHao(const char *ZiFuChuan)  // 字符串
{
    Zhan Z;           // 栈
    ChuShiHua(&Z);
    int LinShi;       // 临时
    
    for (int i = 0; ZiFuChuan[i]; i++)
    {
        char C = ZiFuChuan[i];  // 字符
        if (C == '(' || C == '[' || C == '{')
        {
            RuZhan(&Z, C);
        }
        else if (C == ')' || C == ']' || C == '}')
        {
            if (ShiFouWeiKong(&Z))
                return 0;
            ChuZhan(&Z, &LinShi);
            if ((C == ')' && LinShi != '(') ||
                (C == ']' && LinShi != '[') ||
                (C == '}' && LinShi != '{'))
                return 0;
        }
    }
    return ShiFouWeiKong(&Z);
}

int main(void)
{
    Zhan MoGeZhan;  // 某个栈
    int Zhi;        // 值
    
    ChuShiHua(&MoGeZhan);
    
    //  入栈测试
    RuZhan(&MoGeZhan, 10);
    RuZhan(&MoGeZhan, 20);
    RuZhan(&MoGeZhan, 30);
    DaYinZhan(&MoGeZhan);
    
    // 出栈
    ChuZhan(&MoGeZhan, &Zhi);
    printf("TanChu: %d\n", Zhi);  // 弹出
    DaYinZhan(&MoGeZhan);
    
    //  括号匹配
    printf("\nKuoHao PiPei CeShi:\n");  // 括号匹配测试
    printf("((a+b)): %s\n", JianChaKuoHao("((a+b))") ? "PiPei" : "BuPiPei");  // 匹配/不匹配
    printf("([)]: %s\n", JianChaKuoHao("([)]") ? "PiPei" : "BuPiPei");
    
    return 0;
}
