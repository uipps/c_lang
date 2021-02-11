#include <stdio.h>
#include <conio.h>
#include "BinTree.c"

void oper(ChainBinTree *p) //操作二叉树结点数据
{
    printf("%c ", p->data); //输出数据
    return;
}
ChainBinTree *InitRoot() //初始化二叉树的根
{
    ChainBinTree *node;
    if (node = (ChainBinTree *)malloc(sizeof(ChainBinTree))) //分配内存
    {
        printf("\n输入根结点数据：");
        scanf("%s", &node->data);
        node->left = NULL;
        node->right = NULL;
        return BinTreeInit(node);
    }
    return NULL;
}
void AddNode(ChainBinTree *bt)
{
    ChainBinTree *node, *parent;
    DATA data;
    char select;
    if (node = (ChainBinTree *)malloc(sizeof(ChainBinTree))) //分配内存
    {
        printf("\n输入二叉树结点数据:");
        fflush(stdin); //清空输入缓冲区
        scanf("%s", &node->data);
        node->left = NULL; //设置左右数为空
        node->right = NULL;

        printf("输入父结点数据：");
        fflush(stdin); //清空输入缓冲区
        scanf("%s", &data);
        parent = BinTreeFind(bt, data); //查找制定数据的结点
        if (!parent)                    //若未找到制定数据的结点
        {
            printf("未找到父结点!\n");
            free(node); //释放创建的结点内存
            return;
        }
        printf("1.添加到左子树\n2.添加到右子树\n");
        do
        {
            select = getch();
            select -= '0';
            if (select == 1 || select == 2)
                BinTreeAddNode(parent, node, select); //添加结点到二叉树
        } while (select != 1 && select != 2);
    }
    return;
}
int main()
{
    ChainBinTree *root = NULL; // root为指向二叉树根结点的指针
    char select;
    void (*oper1)(); //指向函数的指针
    oper1 = oper;    //指向具体操作的函数
    do
    {
        printf("\n1.设置二叉树根元素   2.添加二叉树结点\n");
        printf("3.先序遍历            4.中序遍历\n");
        printf("5.后序遍历            6.按层遍历\n");
        printf("7.二叉树深度          0.退出\n");
        select = getch();
        switch (select)
        {
        case '1': //设置根元素
            root = InitRoot();
            break;
        case '2': //添加结点
            AddNode(root);
            break;
        case '3': //先序遍历
            printf("\n先序遍历的结果：");
            BinTree_DLR(root, oper1);
            printf("\n");
            break;
        case '4': //中序遍历
            printf("\n中序遍历的结果：");
            BinTree_LDR(root, oper1);
            printf("\n");
            break;
        case '5': //后序遍历
            printf("\n后序遍历的结果：");
            BinTree_LRD(root, oper1);
            printf("\n");
            break;
        case '6':
            printf("\n按层遍历的结果:");
            BinTree_Level(root, oper1);
            printf("\n");
            break;
        case '7': //二叉树的深度
            printf("\n二叉树深度为%d\n", BinTreeDepth(root));
            break;
        case '0':
            break;
        }
    } while (select != '0');
    BinTreeClear(root); //清空二叉树
    root = NULL;
    getch();
    return 0;
}