#include <stdio.h>
#include <stdlib.h>

// 二叉树递归遍历


// 二叉树节点
// 和链表差不多 就是多了一个指针
typedef struct ShuJieDian
{
    int ShuJu;
    struct ShuJieDian *Zuo;   
    struct ShuJieDian *You;   
} ShuJieDian;

// 创建节点
ShuJieDian *ChuangJianJieDian(int Zhi)
{
    ShuJieDian *JieDian = (ShuJieDian *)malloc(sizeof(ShuJieDian));
    // 防背刺：这里没判空，实际项目要加上 但是我懒得加
    JieDian->ShuJu = Zhi;
    JieDian->Zuo = NULL;   // 初始化为空
    JieDian->You = NULL;
    return JieDian;
}

// 前序遍历：根-左-右
// 口诀：先访问根，再递归左子树，最后递归右子树

void QianXuBianLi(ShuJieDian *Gen)
{
    if (Gen == NULL) return;  // 递归出口！！别忘了 这个忘了就死循环了
    printf("%d ", Gen->ShuJu);    // 先根
    QianXuBianLi(Gen->Zuo);       // 再左
    QianXuBianLi(Gen->You);       // 后右
}

// 中序遍历：左-根-右
// 对于二叉搜索树，中序遍历结果是有序的

void ZhongXuBianLi(ShuJieDian *Gen)
{
    if (Gen == NULL) return;
    ZhongXuBianLi(Gen->Zuo);      // 先左
    printf("%d ", Gen->ShuJu);    // 再根
    ZhongXuBianLi(Gen->You);      // 后右
}

// 后序遍历：左-右-根
// 释放树的时候要用这个顺序！！先释放孩子再释放自己

void HouXuBianLi(ShuJieDian *Gen)
{
    if (Gen == NULL) return;
    HouXuBianLi(Gen->Zuo);        // 先左
    HouXuBianLi(Gen->You);        // 再右
    printf("%d ", Gen->ShuJu);    // 最后根
}

// 释放树（后序方式释放，先释放子节点再释放根）
// 防背刺：顺序很重要！如果先释放根节点，左右孩子就找不到了

void XiaoHuiShu(ShuJieDian *Gen)
{
    if (Gen == NULL) return;
    XiaoHuiShu(Gen->Zuo);   // 先释放左子树
    XiaoHuiShu(Gen->You);   // 再释放右子树
    // printf("释放节点: %d\n", Gen->ShuJu);  // 调试用，看释放顺序
    free(Gen);              // 最后释放自己
}

int main()
{
    // 手动构建二叉树
    // 画个图帮助理解：
    //       1
    //      / \
    //     2   3
    //    / \
    //   4   5
    //
    // 前序：1 2 4 5 3  (根左右)
    // 中序：4 2 5 1 3  (左根右)
    // 后序：4 5 2 3 1  (左右根)
    ShuJieDian *Gen = ChuangJianJieDian(1);
    Gen->Zuo = ChuangJianJieDian(2);
    Gen->You = ChuangJianJieDian(3);
    Gen->Zuo->Zuo = ChuangJianJieDian(4);
    Gen->Zuo->You = ChuangJianJieDian(5);
    // 这样写有点丑 但是简单直接
    
    printf("前序遍历: ");
    QianXuBianLi(Gen);
    printf("\n");
    
    printf("中序遍历: ");
    ZhongXuBianLi(Gen);
    printf("\n");
    
    printf("后序遍历: ");
    HouXuBianLi(Gen);
    printf("\n");
    
    // 释放树
    // printf("\n销毁树的顺序:\n");
    XiaoHuiShu(Gen);
    // printf("释放完成\n");  // 调试用
    
    return 0;
}

// 踩坑记录：
// 1. 递归一定要有出口！if(Gen==NULL)return; 这句忘了就死循环
// 2. 释放树必须后序遍历，先释放孩子再释放父亲
// 3. 树太深会栈溢出，可以用非递归版本（用栈模拟）

