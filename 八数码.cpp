#include<iostream>
#include<stack>
#include<stdlib.h>
#include<math.h>
#include<queue>

using namespace std;
int score(int **a);
//��ά���鸴�� 
void tri(int **a,int **b,int n=3){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			a[i][j] = b[i][j];
		}
	}
}

//�ж������Ƿ���ͬ 
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

//�ڵ�ṹ�� 
struct node{
//	���ڵ��������һ����closed���� 
	int father;
	int **a;
	int point;
}*pnode;
//�� �ڴ洢λ�ò����ǰ����ά��open���closed������˫��������ͷ�洢�����ӽڵ㣨С���ѣ� 
class list{
	public:
		node* l;
	public:
		list(){
			l = NULL;
		} 
		in
}; 

//�ж��Ƿ��ڱ��� 
node* in_list(int **&a,node* pn){
	if(pn==NULL) return NULL;
	node* temp = pn;
	while(temp->next!=pn){
		if(equal(a,temp->a)){
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

void insert(node* pn1,node* pn2){
	
}
//����в��룬β�� 
void insert(int **a,node* &pn){
	if(!pn)
	{
		pn = (node*)malloc(sizeof(node));
		pn->a = (int**)malloc(sizeof(int)*3);
		for(int i=0;i<3;i++)
			pn->a[i] = (int*)malloc(sizeof(int)*3);
		tri(pn->a,a);
		pn->next = pn->pre = pn;
		pn->point = score(a);
		pn->oped = 0;
		return;
	}
	node* temp = (node*)malloc(sizeof(node));
	temp->a = (int**)malloc(sizeof(int)*3);
	for(int i=0;i<3;i++)
		temp->a[i] = (int*)malloc(sizeof(int)*3);
		
	temp->next = pn;
	temp->pre = pn->pre;
	pn->pre = temp;
	temp->pre->next = temp;
	tri(temp->a,a);
	temp->point = score(a);
	temp->oped = 0;
}

//ɾ���ڵ� 
void delete_node(node* pn){
	if(pn->next == pn){
		free(pn);
		pn=NULL;
		return;
	}
	pn->next->pre = pn->pre;
	pn->pre->next = pn->next;
	free(pn->a);
	free(pn);
} 

//���� ����������ʱʹ�ã� 
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

//������Сֵ���� ���ƶ����ȼ��б� 
int max_index(int *a,int n=4){
	int index = 0;
	for(int i=0;i<n;i++){
		if(a[i] < a[index]){
			index = i;
		}
	}
	return index;
}

//Խ�ӽ�Ŀ��scoreԽ�� 
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
	return score;
} 

//������ 
class board{
	public:
		int **a;
		int space[2];
		int score_list[4];
		int ops[4];
		node* open;
		node* closed;
		int step;
	public:
		board(){
			a = (int**)malloc(sizeof(int*)*3);
			for(int i=0;i<3;i++){
				a[i] = (int*)malloc(sizeof(int)*3);
			}
			step = 0;
			int x = rand()%8;
			space[0] = x%8;
			space[1] = x/8;
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
			//�������� 
			open = NULL;
			closed = NULL;
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
		//�����move�ƶ��Ĳ������֣����ǿհ׸��λ�� 
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
		//�õ��������ȼ��б� 
		//0->up 1->down 2->left 3->right
		void get_score_list(){
			score_list[0] = move_up();
//			show();
			if(score_list[0])
				move_down();
			
			score_list[1] = move_down();
//			show();
			if(score_list[1])
				move_up();
			
			score_list[2] = move_left();
//			show();
			if(score_list[2])
				move_right();
			
			score_list[3] = move_right();
//			show();
			if(score_list[3])
				move_left();
		}
//		�����б�
		void get_ops(){
			for(int i=0;i<4;i++){
				if(!score_list[i]){
					ops[i] = -1;
				}
				else{
					ops[i] = max_index(score_list, 4);
					score_list[ops[i]] = -10;
				}
			}
		}
		void showop(){
			cout<<endl;
			for(int i=0;i<4;i++)
				cout<<ops[i]<<',';
			cout<<endl;
		}
		void showsc(){
			cout<<endl;
			for(int i=0;i<4;i++)
				cout<<score_list[i]<<',';
			cout<<endl;
		}
		//A*�㷨 open&closed
		void A_star(){	
			int **b = (int**)malloc(sizeof(int*)*3);
			for(int i=0;i<3;i++){
				b[i] = (int*)malloc(sizeof(int)*3);
			}
			for(int i=0;i<3;i++){
				for(int j=0;j<3;j++){
					b[i][j] = 3*i+j;
				}
			}
			//open in
			//open���ʼ�� 
			insert(a,open);
			while(open!=NULL){
//				if(step>10)
//					break;
//				��÷����б� 
				get_score_list();
				showsc();
//				��ò����б� 
				get_ops();
				showop();
				node x = max_node(open);
//				��չ�ڵ㣬����ڵ���չ�����رսڵ�
				for(int i=0;i<4;i++){
					if(ops[i] < 0){
						cout<<"\ncant open\n";
					}
					else{
						if(ops[i] == 0){
							move_up();
							open
						}
					}
				} 
				
				if(equal(a,b)){
					cout<<"successed\n";
					return;
				}
			}
		}
};

int main()

{
	board B = board();
	B.show();
	
//	B.get_score_list();
//	B.showsc();
//	B.get_ops();
//	B.showop();
	B.A_star();
	return 0;
}
