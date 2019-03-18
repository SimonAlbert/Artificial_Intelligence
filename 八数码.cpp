#include<iostream>
#include<stack>
#include<stdlib.h>

using namespace std;

bool equal(int **a,int **b,int n=3){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(a[i][j] != b[i][j]){
				return false;
			}
		}
	}
	return true;
}

struct node{
	node* next;
	int a[3][3];
}*pnode;

struct ops{
	int a[4];
	int i;
};

//乱序 
void rand_sort(int *a,int n){
	stack<int>s;
	while(n){
		int i = (rand())%n;
		s.push(a[i]);
		a[i] = a[n-1];
		n--;
	}
	while(!s.empty()){
		a[n] = s.top();
		s.pop();
		n++;
	}
}

int max_index(int *a,int n){
	int max = 0;
	for(int i=0;i<n;i++){
		if(a[i] > a[max]){
			max = i;
		}
	}
	return max;
}

//形势判断
int score(int a[][3]){
	int score=0;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(!a[i][j]){
				score += 4-i-j;
			}
			else{
				score += (a[i][j]/3+a[i][j]%3)-i-j;
			}
		}
	}
	return score;
} 



//八数码 
class board{
	public:
		int a[3][3];
		int space[2];
		int move_list[4];
		stack<struct ops>op_list;
	public:
		board(){
			cin>>space[0]>>space[1];
			int arr[8];
			for(int i=0;i<8;i++){
				arr[i] = i+1;
			}
			rand_sort(arr,8);
			int t=0;
			for(int i=0;i<3;i++){
				for(int j=0;j<3;j++){
					if(i==space[0]&&j==space[1]){
						a[i][j] = 0;
					}
					else{
						a[i][j] = arr[t];
						t++;
					}
				}
			}
			//生成棋盘 
		}
		void show(){
			for(int i=0;i<3;i++){
				for(int j=0;j<3;j++){
					cout<<a[i][j]<<' ';
				}
				cout<<endl;
			}
			cout<<endl;
		}
		//这里的move移动的不是数字，而是空白格的位置 
		int move_up(){
			if(space[0] == 0){
				cout<<"can not move up\n";
				return 0;
			}
			else{
				a[space[0]][space[1]] = a[space[0]-1][space[1]];
				space[0]--;
				a[space[0]][space[1]] = 0;
				return score(a);
			}
		}
		int move_down(){
			if(space[0] == 2){
				cout<<"can not move down\n";
				return 0;
			}
			else{
				a[space[0]][space[1]] = a[space[0]+1][space[1]];
				space[0]++;
				a[space[0]][space[1]] = 0;
				return score(a);
			}
		}
		int move_left(){
			if(space[1] == 0){
				cout<<"can not move left\n";
				return 0;
			}
			else{
				a[space[0]][space[1]] = a[space[0]][space[1]-1];
				space[1]--;
				a[space[0]][space[1]] = 0;
				return score(a);
			}
		}
		int move_right(){
			if(space[1] == 2){
				cout<<"can not move right\n";
				return 0;
			}
			else{
				a[space[0]][space[1]] = a[space[0]][space[1]+1];
				space[1]++;
				a[space[0]][space[1]] = 0;
				return score(a);
			}
		}
		int move(int x,int y){
			if((space[0]+x > 2||space[0]+x <= 0)
				||(space[1]+y > 2||space[1]+y <= 0)){
				cout<<"can not move\n";
				return 0;
			}
			else{
				a[space[0]][space[1]] = a[space[0]+x][space[1]+y];
				space[0] += x;
				space[1] += y;
				a[space[0]][space[1]] = 0;
				return score(a);
			}
		}
		//得到方向优先级列表 
		//0->up 1->down 2->left 3->right
		void get_score_list(){
			move_list[0] = move_up();
//			show();
			if(move_list[0])
			move_down();
			
			move_list[1] = move_down();
//			show();
			if(move_list[1])
			move_up();
			
			move_list[2] = move_left();
//			show();
			if(move_list[2])
			move_right();
			
			move_list[3] = move_right();
//			show();
			if(move_list[3])
			move_left();
		}
		//移动过程，将移动操作列表存入栈里 (非递归形式)
		void play(){
			int point = score(a);
			int t = 0;
			while(point&&t<40){
				get_score_list();
				ops op;
				op.i = 0;
				for(int i=0;i<4;i++){
					op.a[i] = max_index(move_list,4);
					move_list[i] = -1;
				}
				if(!op_list.empty())
				if(op.a[op.i]+op_list.top().a[op_list.top().i] == 1
				 ||op.a[op.i]+op_list.top().a[op_list.top().i] == 4)
				 {
				 	op = op_list.top();
				 	op_list.pop();
				 	op.i +=1 ;
				 }
				
//				cout<<op<<endl;
				op_list.push(op);
				if(op.a[op.i] == 0){
					move_up();
				}
				else if(op.a[op.i] == 1){
					move_down();
				}
				else if(op.a[op.i] == 2){
					move_left();
				}
				else if(op.a[op.i] == 3){
					move_right();
				}
				show();
				t++;
				point = score(a);
			}
		}
		
		//A*算法 open&closed
		void A_star(){
			
		}
};

int main()

{
	board B = board();
	B.play();
	return 0;
}
