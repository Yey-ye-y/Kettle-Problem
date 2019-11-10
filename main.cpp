#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;
#define MaxNode 100
int Asize,Bsize,BAim;
struct node{
    int aTemp;		//�м����A��ˮ��
    int bTemp;		//�м����B��ˮ��
    node *front;	//ָ��·����һ�ڵ�
//    vector<node*> next; //�ӽڵ�,�����ֹ�ڴ�й¶,����ڴ���ʺ�ʹ�������������������ɫ��ûд����ڴ��code
};
bool  isFind;
bool IsExist[MaxNode][MaxNode];
queue<node*>bfsQ;//������ȴ洢����
//B��A��ˮ
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
//A��B��ˮ
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
//A����
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
//B����
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
//A����
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
//B����
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
    if(head&&head->front)//�����ͷ�ڵ㣬���ռ���IsExist
        IsExist[head->aTemp][head->bTemp];
    if(!head||isFind)return ;
    if (head->bTemp==BAim){
        isFind= true;
        result=head;
        return ;
    }
    node * temp;
    temp=BtoA(head);//B��ˮ����A��ˮ
    DFS(temp,result);
    temp=AtoB(head);//A��ˮ����B��ˮ
    DFS(temp,result);
    temp=AtoEmpty(head);//A��ˮ����
    DFS(temp,result);
    temp=BtoEmpty(head);//B��ˮ����
    DFS(temp,result);
    temp=AtoFull(head);//A��ˮ����
    DFS(temp,result);
    temp=BtoFull(head);//B��ˮ����
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
        veTemp.push_back(AtoB(temp));//��ͨ������õ��Ľ������veTemp���˹���ΪA��ˮ��B��ˮ����ͬ
        veTemp.push_back(BtoA(temp));
        veTemp.push_back(AtoEmpty(temp));
        veTemp.push_back(BtoEmpty(temp));
        veTemp.push_back(AtoFull(temp));
        veTemp.push_back(BtoFull(temp));
        for(int i=0;i<veTemp.size();i++){

            if(veTemp[i]){
                if(veTemp[i]->bTemp==BAim)//�ж��Ƿ���Ŀ�꣬���򷵻أ��㷨����
                    return veTemp[i];
                bfsQ.push(veTemp[i]);//����Ŀ����������
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
    while (tempP)//ת��Ϊ��ջ�洢�����������
    {
        tS.aTemp=tempP->aTemp;
        tS.bTemp=tempP->bTemp;
        sT.push(tS);
        tempP=tempP->front;
    }
    int res=0;
    cout<<"��������"<<endl;
    while(!sT.empty()){
        res++;
        tempSize disPlay=sT.top();
        sT.pop();
        printf("��%d��----Aˮ����%d       Bˮ����%d     \n",res,disPlay.aTemp,disPlay.bTemp);
    }

    //��IsExistȫ����Ϊfalse
    for(int i=0;i<=Asize;i++){
        for(int j=0;j<=Bsize;j++){
            IsExist[i][j]= false;
        }
    }
}

int main() {
    cout<<"������A��B�������Լ�B������̬"<<endl;
    cin>>Asize>>Bsize>>BAim;
    node *head=new node;
    head->aTemp=Asize;
    head->bTemp=0;
    head->front= nullptr;
    node *result=BFS(head);
    cout<<"BFS�������"<<endl;
    DisPlay(result);
    delete result;//�ͷ��ڴ�
    result= nullptr;//ָ��Ϊ��
    IsExist[head->aTemp][head->bTemp]= true;
    DFS(head,result);
    cout<<"DFS�������"<<endl;
    DisPlay(result);
    return 0;
}