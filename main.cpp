#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;
#define MaxNode 100
int Asize,Bsize,BAim;
struct node{
    int aTemp;		//中间过程A壶水量
    int bTemp;		//中间过程B壶水量
    node *front;	//指向路径上一节点
//    vector<node*> next; //子节点,如果防止内存泄露,清除内存的适合使用这个，本代码制作颜色，没写清除内存的code
};
bool  isFind;
bool IsExist[MaxNode][MaxNode];
queue<node*>bfsQ;//广度优先存储队列
//B往A倒水
node* BtoA(node* temp){
    node *result=new node;
    if(temp->aTemp+temp->bTemp<=Asize){
        result->aTemp=temp->aTemp+temp->bTemp;
        result->bTemp=0;
        if(!IsExist[result->aTemp][result->bTemp]){
            result->front=temp;
            IsExist[result->aTemp][result->bTemp]= true;
            return result;
        } else {
            delete result;
            return nullptr;
        }
    } else{
        result->aTemp=Asize;
        result->bTemp=temp->bTemp-(Asize-temp->aTemp);
        if(!IsExist[result->aTemp][result->bTemp]){
            result->front=temp;
            IsExist[result->aTemp][result->bTemp]= true;
            return result;
        } else {
            delete result;
            return nullptr;
        }
    }
}
//A往B倒水
node* AtoB(node* temp){
    node *result=new node;
    if(temp->aTemp+temp->bTemp<=Bsize){
        result->bTemp=temp->aTemp+temp->bTemp;
        result->aTemp=0;
        if(!IsExist[result->aTemp][result->bTemp]){
            result->front=temp;
            IsExist[result->aTemp][result->bTemp]= true;
            return result;
        } else {
            delete result;
            return nullptr;
        }
    } else{
        result->bTemp=Bsize;
        result->aTemp=temp->aTemp-(Bsize-temp->bTemp);
        if(!IsExist[result->aTemp][result->bTemp]){
            result->front=temp;
            IsExist[result->aTemp][result->bTemp]= true;
            return result;
        } else {
            delete result;
            return nullptr;
        }
    }
}
//A倒空
node* AtoEmpty(node* temp){
    node *result=new node;
    result->aTemp=0;
    result->bTemp=temp->bTemp;
    if(!IsExist[result->aTemp][result->bTemp]){
        result->front=temp;
        IsExist[result->aTemp][result->bTemp]= true;
        return result;
    } else {
        delete result;
        return nullptr;
    }
}
//B倒空
node* BtoEmpty(node* temp){
    node *result=new node;
    result->aTemp=temp->aTemp;
    result->bTemp=0;
    if(!IsExist[result->aTemp][result->bTemp]){
        result->front=temp;
        IsExist[result->aTemp][result->bTemp]= true;
        return result;
    } else {
        delete result;
        return nullptr;
    }
}
//A倒满
node* AtoFull(node* temp){
    node *result=new node;
    result->aTemp=Asize;
    result->bTemp=temp->bTemp;
    if(!IsExist[result->aTemp][result->bTemp]){
        result->front=temp;
        IsExist[result->aTemp][result->bTemp]= true;
        return result;
    } else {
        delete result;
        return nullptr;
    }
}
//B倒满
node* BtoFull(node* temp){
    node *result=new node;
    result->aTemp=temp->aTemp;
    result->bTemp=Bsize;
    if(!IsExist[result->aTemp][result->bTemp]){
        result->front=temp;
        IsExist[result->aTemp][result->bTemp]= true;
        return result;
    } else {
        delete result;
        return nullptr;
    }
}

void DFS(node* head,node *& result){
    if(head&&head->front)//如果是头节点，则收集如IsExist
        IsExist[head->aTemp][head->bTemp];
    if(!head||isFind)return ;
    if (head->bTemp==BAim){
        isFind= true;
        result=head;
        return ;
    }
    node * temp;
    temp=BtoA(head);//B壶水到给A壶水
    DFS(temp,result);
    temp=AtoB(head);//A壶水到给B壶水
    DFS(temp,result);
    temp=AtoEmpty(head);//A壶水倒空
    DFS(temp,result);
    temp=BtoEmpty(head);//B壶水倒空
    DFS(temp,result);
    temp=AtoFull(head);//A壶水倒满
    DFS(temp,result);
    temp=BtoFull(head);//B壶水倒满
    DFS(temp,result);
}

node* BFS(node* head){
    if(!head)return nullptr;
    IsExist[head->aTemp][head->bTemp]= true;
    bfsQ.push(head);
    vector<node*> veTemp;
    while (!bfsQ.empty()){
        node* temp=bfsQ.front();
        bfsQ.pop();
        veTemp.push_back(AtoB(temp));//将通过规则得到的结果放入veTemp，此规则为A壶水向B倒水，下同
        veTemp.push_back(BtoA(temp));
        veTemp.push_back(AtoEmpty(temp));
        veTemp.push_back(BtoEmpty(temp));
        veTemp.push_back(AtoFull(temp));
        veTemp.push_back(BtoFull(temp));
        for(int i=0;i<veTemp.size();i++){

            if(veTemp[i]){
                if(veTemp[i]->bTemp==BAim)//判断是否是目标，是则返回，算法结束
                    return veTemp[i];
                bfsQ.push(veTemp[i]);//不是目标则放入队列
            }
        }
        veTemp.clear();
    }
    return nullptr;
}

void DisPlay(node *result){
    struct tempSize{
        int aTemp;
        int bTemp;
    };
    node* tempP=result;
    tempSize tS;
    stack<tempSize> sT;
    while (tempP)//转变为堆栈存储，可逆序输出
    {
        tS.aTemp=tempP->aTemp;
        tS.bTemp=tempP->bTemp;
        sT.push(tS);
        tempP=tempP->front;
    }
    int res=0;
    cout<<"过程如下"<<endl;
    while(!sT.empty()){
        res++;
        tempSize disPlay=sT.top();
        sT.pop();
        printf("第%d步----A水壶：%d       B水壶：%d     \n",res,disPlay.aTemp,disPlay.bTemp);
    }

    //将IsExist全部变为false
    for(int i=0;i<=Asize;i++){
        for(int j=0;j<=Bsize;j++){
            IsExist[i][j]= false;
        }
    }
}

int main() {
    cout<<"请输入A、B的容量以及B的最终态"<<endl;
    cin>>Asize>>Bsize>>BAim;
    node *head=new node;
    head->aTemp=Asize;
    head->bTemp=0;
    head->front= nullptr;
    node *result=BFS(head);
    cout<<"BFS结果如下"<<endl;
    DisPlay(result);
    delete result;//释放内存
    result= nullptr;//指向为空
    IsExist[head->aTemp][head->bTemp]= true;
    DFS(head,result);
    cout<<"DFS结果如下"<<endl;
    DisPlay(result);
    return 0;
}