#include<stdio.h>
#include<stdlib.h>

#define MaxSize 100

typedef char ElemType;
typedef struct node
{
    ElemType data;
    struct node *lchild;
    struct node *rchild;
}BTNode;

//创建二叉树
void CreateBTNode(BTNode *b,char *str)
{
    BTNode * St[MaxSize],*p;
    int top=-1,k,j=0;
    char ch;
    b=NULL;
    ch=str[j];
    while(ch!='\0')
    {
        switch(ch)
        {
            case '(':top++;St[top]=p;k=1;break;
            case ')':top--;break;
            case ',':k=2;break;
            default:p=(BTNode *)malloc(sizeof(BTNode));
                    p->data=ch;p->lchild=p->rchild=NULL;
                    if(b==NULL)
                    {
                        b=p;
                    }
                    else
                    {
                        switch(k)
                        {
                            case 1:St[top]->lchild=p;break;
                            case 2:St[top]->rchild=p;break;
                        }
                    }
        }
        j++;
        ch=str[j];
    } 
} 

//查找节点 
BTNode *FindNode(BTNode *b,ElemType x)
{
    BTNode *p;
    if(b==NULL)
    {
        return NULL;
    }
    else if(b->data==x)
    {
        return b;
    }
    else
    {
        p=FindNode(b->lchild,x);
        if(p!=NULL)
        {
            return p;
        }
        else
        {
            return FindNode(b->rchild,x);
        }
    }
}

//找孩子节点
BTNode *LchildNode(BTNode *p)
{
    return p->lchild;
}
BTNode *RchildNode(BTNode *p)
{
    return p->rchild;
}

//求高度
int BTNodeHeight(BTNode *b)
{
    int lchildh,rchildh;
    if(b==NULL)
    {
        return 0;
    }
    else
    {
        lchildh=BTNodeHeight(b->lchild);
        rchildh=BTNodeHeight(b->rchild);
        return(lchildh>rchildh)?(lchildh+1):(rchildh+1);
    }
}

//输出二叉树 
void DispBTNode(BTNode *b)
{
    if(b!=NULL)
    {
        printf("%c",b->data);
        if(b->lchild!=NULL||b->rchild!=NULL)
        {
            printf("(");
            DispBTNode(b->lchild);
            if(b->rchild!=NULL)
            {
                printf(",");                
            }
            DispBTNode(b->rchild);
            printf(")");
        }
    }
}

//先序遍历的递归算法 
void PreOrder( BTNode *b)     
{
    if(b!=NULL)
    {
        printf("%c",b->data);  //访问根节点 
        PreOrder(b->lchild);   //先序遍历左子树 
        PreOrder(b->rchild);   //先序遍历右子树 
    }
}

//先序非递归遍历算法 
void PreOrder1(BTNode *b)           
{
    BTNode *St[MaxSize],*p;
    int top = -1;
    if(b!=NULL)
    {
        top++;                     //根节点进栈 
        St[top]=b;
        while(top>=-1)             //栈不空时循环 
        {
            p=St[top];             //退栈并访问该节点 
            top--;
            printf("%c",p->data);
            if(p->rchild!=NULL)    //右孩子节点进栈 
            {
                top++;
                St[top]=p->rchild; 
            }
            if(p->lchild!=NULL)    //左孩子节点进栈 
            {
                top++;
                St[top]=p->lchild;
            }
        }
        printf("\n");
    }
} 

//中序遍历的递归算法 
void InOrder(BTNode *b)           
{
    if(b!=NULL)
    {
        InOrder(b->lchild);       //中序遍历左子树 
        printf("%c",b->data);     //访问根节点 
        InOrder(b->rchild);       //中序遍历右子树 
    }
} 

void InOrder1(BTNode *b)          //中序非递归遍历算法 
{
    BTNode *St[MaxSize],*p;
    int top = -1;
    if(b!=NULL)
    {
        p=b;
        while(top>-1||p!=NULL)    //处理*b节点的左子树 
        {
            while(p!=NULL)        //扫描*p的所有左节点并进栈 
            {
                top++;
                St[top]=p;
                p=p->lchild; 
            }
            //执行到此处时，栈顶元素没有左孩子或左子树均已访问过 
            if(top>-1)
            {
                p=St[top];      //出栈*p节点 
                top--;
                printf("%c",p->data); //访问之 
                p=p->rchild;          //转向处理*p的右孩子节点 
            }
        }
        printf("\n");
    } 
} 

//后序遍历的递归算法 
void PostOrder(BTNode *b)        
{
    if(b!=NULL)
    {
        PostOrder(b->lchild);    //后序遍历左子树 
        PostOrder(b->rchild);    //后序遍历右子树   
        printf("%c",b->data);    //访问根节点 
    }
}

//后序非递归遍历算法
void Postorder(BTNode *b)                
{
    BTNode *St[MaxSize];
    BTNode *p;
    int flag,top=-1;              //栈顶指针top置初值 
    if(b!=NULL)
    {
        do
        {
            while(b!=NULL)       //将*b的所有左节点进栈 
            {
                top++;
                St[top]=b;
                b=b->lchild;
            }
            //执行到此处时，栈顶元素没有左孩子或左子树均已访问过 
            p=NULL;                 //p指向栈顶节点的前一个已访问的节点 
            flag=1;                 //表示*b的左孩子已访问过或为空 
            while(top!=-1&&flag)
            {
                b=St[top];          //取出当前的栈顶元素 
                if(b->rchild==p)
                /*
                *若p=NULL，表示b的右孩子不存在，
                *而其左子树不存在或已访问，
                *所以可以访问*b，若P不等于NULL，
                *表示b的右子树已访问
                *（原因是p指向b的右子树中刚访问过的节点，
                *而*P是b的孩子，
                *p一定是b的右子树中后序序列的最后一个节点），
                *所以可以访问*b   
                */ 
                {
                    printf("%c",b->data);  //访问*b节点 
                    top--;
                    p=b;                   //p指向刚访问过的节点 
                } 
                else
                {
                    b=b->rchild;           //b指向右孩子节点 
                    flag=0;                //表示*b的左孩子尚未访问过 
                }
            }
        }while(top!=-1);
        printf("\n");
    } 
} 
int main()
{
    //括号表示法字符串
    char a[] = "A(B(D(,G)),C(E,F))";
    char *b = "A(B(D(,G)),C(E,F))";
    return 0;
}