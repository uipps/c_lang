//
/*
已知五个互不相同的正整数之和为23，且从这五个数中挑选若干个加起来可以表示从1到23之内的全部自然数。问这五个数是什么

参考 https://blog.csdn.net/csy981848153/article/details/7650159?spm=1001.2014.3001.5501

-- 结果
1 2 3 5 12
1 2 3 6 11
1 2 3 7 10
1 2 4 5 11
1 2 4 6 10
1 2 4 7 9

*/
#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

void zuhe(int* nData,int len,int cur,int num);//组合函数
vector<int> nVecTmp;
bitset<23> bs;//23位来检测是否能组成23，当每位都为1时就说明可以组成23
int main()
{
	int i,j,m,n,k;
	int nNum[5] = {0};
	for (i=1;i<23;++i)
		for(j=i+1;j<23;++j)
			for(m=j+1;m<23;++m)
				for(n=m+1;n<23;++n)
						{
							k = 23-i-j-m-n;
							if(k>n){
							   nNum[0] = i;
							   nNum[1] = j;
							   nNum[2] = k;
							   nNum[3] = m;
							   nNum[4] = n;
							     bs.reset();
							     for(int t=1;t!=6;++t){//穷举所有的组合
								      zuhe(nNum,5,0,t);
									  nVecTmp.clear();
							     }
								 if(bs.count() == 23){
									 cout<<i<<" "<<j<<" "<<m<<" "<<n<<" "<<k<<endl;
                                     //printf("%d %d %d %d %d", i,j,m,n,k)
								 }
							}
						}

	return 0;
}

void zuhe(int* nData,int len,int cur,int num)
{
   if (num == 0){
	   int t=0;
	   for(size_t i=0;i!=nVecTmp.size();++i){
                     t += nVecTmp[i];
      }
	   bs.set(t-1);
   }

   for (int i=cur;i!=len;++i)
   {
	   nVecTmp.push_back(nData[i]);
	   zuhe(nData,len,i+1,num-1);
	   nVecTmp.pop_back();
   }
}