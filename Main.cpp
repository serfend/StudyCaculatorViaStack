#include <iostream>
#include <stack>
#include <string.h>
#include <map>
#include <queue>
using namespace std;

int logIndex=0;
class Caculator{
		void Init(){
			op['+']=op['-']=1;
			op['*']=op['/']=2;
			Change();
		}
		bool IsNum(char chr){
			return (chr>='0'&&chr<='9');
		}
		void Change(){
			for(int i=0;i<str.length();){
				node thisChar;
				if(IsNum(str[i])){
					thisChar.isNum=true;
					thisChar.num=str[i++]-'0';
					while(i<str.length()&&IsNum(str[i])){
						thisChar.num=thisChar.num*10+str[i]-'0';
						i++;
					} 
					q.push(thisChar);
				}else{
					thisChar.isNum=false;
					while(!s.empty()&&op[str[i]]<=op[s.top().op]){
						q.push(s.top());
						s.pop();
					}
					thisChar.op=str[i];
					s.push(thisChar);
					i++;
				}
			}
			while(!s.empty()){
				q.push(s.top());
				s.pop();
			}
		}
		struct node{
			double num;
			char op;
			bool isNum;
		};
		string str;
		stack<node>s;
		queue<node>q;
		map<char,int>op;//ÓÅÏÈ¼¶ 
	public:
		Caculator(string expression){
			this->str=expression;	
			this->Init();
		}
		double result(){
			double tmp1,tmp2;
			node cur,tmp;
			while(!q.empty()){
				cur=q.front();
				q.pop();
				if(cur.isNum){
					s.push(cur);
				}else{
					tmp1=s.top().num;
					s.pop();
					tmp2=s.top().num;
					s.pop();
					tmp.isNum=true;
					switch(cur.op){
						case '+':{
							tmp.num=tmp1+tmp2;
							break;
						}
						case '-':{
							tmp.num=tmp2-tmp1;	
							break;
						}
						case '*':{
							tmp.num=tmp1*tmp2;
							break;
						}
						case '/':{
							tmp.num=tmp2/tmp1;	
							break;
						}
					}
					s.push(tmp);
				}
			}
			return s.top().num;
		}
};
int main(){
	Caculator c("1+2*3*4-5/10+3");
	printf("%lf",c.result());
	return 0;
}
