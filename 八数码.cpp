#include<iostream>
#include<stack>
#include<stdlib.h>
#include<math.h>
#include<queue>

using namespace std;
int score(int **a);
//三维数组复制 
void tri(int **a,int **b,int n=3){
//	cout<<"tri"<<endl;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			a[i][j] = b[i][j];
		}
	}
}
//判断棋盘是否相同 
bool equal(int **a,int **b,int n=3){
//	cout<<"equal"<<endl;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(a[i][j] != b[i][j]){
				return false;
			}
		}
	}
	return true;
}

//节点结构体 
struct node{
//	父节点的索引，一定在closed表内 
	int father;
	int **a;
	int point;
	int step;
}*pnode;

void init_node(node* pn){
	pn->a = (int**)malloc(sizeof(int*)*3);
	for(int j=0;j<3;j++){
		pn->a[j] = (int*)malloc(sizeof(int)*3);
	}
}
node* init_node(int **a,int father,int point,int step=0){
	node* pn = (node*)malloc(sizeof(node));
	pn->a = (int**)malloc(sizeof(int*)*3);
	for(int i=0;i<3;i++){
		pn->a[i] = (int*)malloc(sizeof(int)*3);
	}
	tri(pn->a,a);
	pn->father = father;
	pn->step = step;
	pn->point = point;
	return pn;
}
//表 在存储位置不变的前提下维护open表和closed表
class list{
	public:
		node* l;
		int num;
	public:
		list(){
			num = 0;
			l = (node*)malloc(sizeof(node)*100);
			for(int i=0;i<100;i++){
				init_node(l+i);
			}
		}
		void update(){
			for(int i=1;i<num;i++){
				l[i].point -= l[i].step;
				l[i].step = l[l[i].father].step+1;
				l[i].point += l[i].step;
			}
		}
		int in_list(int **a){
//			cout<<"in_list"<<endl;
			for(int i=0;i<num;i++){
				if(equal(a,l[i].a)){
					return i;
				}
			}
			return -1;
		}
//		插入时需要的参数 
		int put_in(int **a,int father,int point,int step){
			int index = num;
//			节点已存在时 
			int pos = in_list(a);
			if(pos != -1){
				if(step < l[pos].step){
					l[pos].father = father;
					l[pos].point = point;
					l[pos].step = step;
					return pos;
				}
			}
			else{
				num++;
				l[index].father = father;
				l[index].point = point;
				l[index].step = step;
				tri(l[index].a,a);
				return index;
			}
		}
		int put_in(node* pn){
			int index = num;
//			节点已存在时 
			int pos = in_list(pn->a);
			if(pos != -1){
				if(pn->step < l[pos].step){
					l[pos].father = pn->father;
					l[pos].point = pn->point;
					l[pos].step = pn->step;
					return pos;
				}
			}
			else{
				num++;
				l[index].father = pn->father;
				l[index].point = pn->point;
				l[index].step = pn->step;
				tri(l[index].a,pn->a);
				return index;
			}
		}
//		open表最优节点放屁股上 
		void sort(){
			if(num <= 1) return;
			int min = num-1;
			int max = num-1;
			for(int i=0;i<num;i++){
				if(l[min].point > l[i].point){
					min = i;
				}
			}
			int i=num-1;
//			node *pn = init_node(,l[i].father,l[i].point,l[i].step);
			node n;
			init_node(&n);
			tri(n.a,l[i].a);
			n.father = l[i].father;
			n.point = l[i].point;
			n.step = l[i].step;
			node* pn = &n;
//			cout<<"ok\n";
			tri(l[i].a,l[min].a);
			l[i].father = l[min].father;
			l[i].point = l[min].point;
			l[i].step = l[min].step;
			tri(l[min].a,pn->a);
			l[min].father = pn->father;
			l[min].point = pn->point;
			l[min].step = pn->step; 
		}
		void show(){
			cout<<"list\n";
			for(int k=0;k<num;k++){
				for(int i=0;i<3;i++){
					for(int j=0;j<3;j++){
						cout<<l[k].a[i][j]<<' ';
					}
					cout<<endl;
				}
				cout<<"step:"<<l[k].step;
				cout<<endl;
			}
			cout<<num<<endl;
			cout<<"list end\n";
		}
}; 

//乱序 （生成棋盘时使用） 
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

//返回最小值索引 （移动优先级列表） 
int max_index(int *a,int n=4){
	int index = 0;
	for(int i=0;i<n;i++){
		if(a[i] < a[index]){
			index = i;
		}
	}
	return index;
}

//越接近目标score越大 
int score(int **a){
	int score=0;
	int t=0;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(!a[i][j]){
				t = a[i][j] - 1;
				int temp = abs(2-i) + abs(2-j);
				score += temp;
//				cout<<a[i][j]<<','<<temp<<endl;
			}
			else{
				t = a[i][j] - 1;
				int temp = abs(t/3-i) + abs(t%3-j);
				score +=  temp;
//				cout<<a[i][j]<<','<<temp<<endl;
			}
		}
	}
	score += 1;
	return score;
} 

//八数码 
class board{
	public:
		int **a;
		int space[2];
		int score_list[4];
		int ops[4];
	public:
		board(){
			a = (int**)malloc(sizeof(int*)*3);
			for(int i=0;i<3;i++){
				a[i] = (int*)malloc(sizeof(int)*3);
			}
			a = (int**)malloc(sizeof(int*)*3);
			for(int i=0;i<3;i++){
				a[i] = (int*)malloc(sizeof(int)*3);
			}
			for(int i=0;i<3;i++){
				for(int j=0;j<3;j++){
					a[i][j] = 3*i+j+1;
				}
			}
			a[2][2] = 0;
			show();
			space[0] = 2;
			space[1] = 2;
			int op;
			for(int i=0;i<30;i++){
				op = rand()%4;
				if(op==0)
					move_up();
				else if(op==1)
					move_down();
				else if(op==2)
					move_left();
				else if(op==3)
					move_right();
			}
//			int x = rand()%8;
//			space[0] = x%8;
//			space[1] = x/8;
//			int arr[8];
//			for(int i=0;i<8;i++){
//				arr[i] = i+1;
//			}
//			rand_sort(arr,8);
//			int t=0;
//			for(int i=0;i<3;i++){
//				for(int j=0;j<3;j++){
//					if(i==space[0]&&j==space[1]){
//						a[i][j] = 0;
//					}
//					else{
//						a[i][j] = arr[t];
//						t++;
//					}
//				}
//			}
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
//				cout<<"can not move up\n";
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
//				cout<<"can not move down\n";
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
//				cout<<"can not move left\n";
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
//				cout<<"can not move right\n";
				return 0;
			}
			else{
				a[space[0]][space[1]] = a[space[0]][space[1]+1];
				space[1]++;
				a[space[0]][space[1]] = 0;
				return score(a);
			}
		}
		
		void get_space(){
			for(int i=0;i<3;i++){
				for(int j=0;j<3;j++){
					if(!a[i][j]){
						space[0] = i;
						space[1] = j;
						return;
					}
				}
			}
		}
		//A*算法 open&closed
		void A_star(){
			int **b = (int**)malloc(sizeof(int*)*3);
			for(int i=0;i<3;i++){
				b[i] = (int*)malloc(sizeof(int)*3);
			}
			for(int i=0;i<3;i++){
				for(int j=0;j<3;j++){
					b[i][j] = 3*i+j+1;
				}
			}
			b[2][2] = 0;
			list open = list();
			list closed = list();
			open.put_in(a,-1,score(a),0);
//			show();
			int deep=0;
			while(open.num){
//				if(deep++ > 50) return;
				//从open表中取出一个最好的节点
				if(score(a) >= 3) 
				open.sort();
				node* tmp = &(open.l[open.num-1]);
				tri(a,tmp->a);
				get_space();
				
				//判断这个节点是否是目的节点
				if(equal(a,b)){
					show();
					cout<<"\nsuccess\n";
					return;
				}
				open.num--;
				//放入closed 
				int father = closed.put_in(tmp);
				if(father != closed.num-1){
					closed.update();
					continue;
				}
				int step = closed.l[father].step + 1;
				
				show();
				int score = move_up();
					cout<<score<<',';
				if(score){
					open.put_in(a,father,score+step,step);
					move_down();
				}
				score = move_down();
					cout<<score<<',';
				if(score){
					open.put_in(a,father,score+step,step);
					move_up();
				}
				
				score = move_left();
					cout<<score<<',';
				if(score){
					open.put_in(a,father,score+step,step);
					move_right();
				}
				
				score = move_right();
					cout<<score<<'\n';
				if(score){
					open.put_in(a,father,score+step,step);
					move_left();
				}
//				open.sort();
//				open.show();
//				cout<<"\ndebug\n";
			}
			show();
		}
};

int main()

{
	board B = board();
	B.A_star();
	return 0;
}
