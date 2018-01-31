//
// Created by Administrator on 2017/12/1.
//

#include "Graph.h"
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <stack>
#include <queue>

using namespace std;


/**
 * func:���ʺ���
 * @param G ͼ��ַG
 * @param node ��������
 * @return ״̬��
 */
int visit(Graph * G,Vnode * node){
    if(!G) return ERROR;
    if(!node||node->tag<0) return -1;
    cout << "keyֵΪ"<<LocateVex(G,node->data.c,(void * )(&strcmp))<<", nֵΪ��"<< node->data.n<<", cֵΪ"<<node->data.c<<endl;
    return OK;
}


/**
 * func: ����ڵ�
 * @param G ͼ��ַ
 * @return ״̬��
 */
Status CreateVex(Graph * G){
    if(!G) return ERROR;
    Vnode * vex = G->vertices;
    int count = 0;int type;
    int index = -1;
    int flag = 1;//�ж������Ƿ�Ϸ�
    cout << "�����붥������"<< endl;
    cin >> count;
    G->vexnum = (count > 0?count:0); //����ͼ���������
    if(count <=0 ) return ERROR;
    cout << "�����붥��Ĺؼ�ֵkey(��Χ0-"<<count-1<<")��nֵ��cֵ���Կո����,\n��keyֵΪ��ֵʱ�������"<< endl;
    int key;
    while(1){
        cin >> key;
        if(key < 0) break;//��kΪ��ֵʱ���������
        //��������
        cin >> G->vertices[key].data.n;
        cin >> G->vertices[key].data.c;
        //��ʼʱ�������ָ��������ΪNULL
        G->vertices[key].firstarc = G->vertices[key].lastArc = G->vertices[key].cur = NULL;
        G->vertices[key].tag = NEWLY; //���ö���ı�־��ΪNEWLY
    }
    return OK;
}

/**
 * func: ������
 * @param tail ��tailΪβ�ı�
 * @return �ߵ�ַ
 */
ArcNode * GenerateArc(int tail,int weight){
    //����һ���Ի�β�ڵ�ΪtailȨ��Ϊweight���ڽӵ�
    ArcNode * newArc = (ArcNode*)malloc(sizeof(ArcNode));//����ռ�
    //��ֵ
    newArc->nextarc = NULL;
    newArc->adjvex = tail;
    newArc->info.weigtht = weight;
    return newArc;
}

/**
 * func: �����
 * @param G ͼ��ַ
 * @return ״̬��
 */
Status CreateArc(Graph * G){
    if(!G) return ERROR;
    int head;//��β
    int tail;//��ͷ
    ArcNode * p = NULL;
    ArcNode * q;

    //������ʾ
    (G->kind==UNDIRECTION_GRAPH)?(cout << "�������������������Ĺؼ�ֵ\n"):(cout<<"�����������յ�Ĺؼ�ֵ\n");
    while(1){
        cin >> head;
        if(head<0)  break;//������Ϊ��ֵ��ʱ���˳�ѭ��
        cin>>tail;
        //��������������ʱ�򷵻ش�����
        if(head >=MAX_VERTEX_NUM||tail < 0 || tail >= MAX_VERTEX_NUM||
           G->vertices[tail].tag<0||G->vertices[head].tag<0) return ERROR;
        int weight;
        cout << "������Ȩֵ��"<<endl;
        cin >> weight;
        p = GenerateArc(tail,weight);//����һ���ڽӵ�
        if(G->vertices[head].firstarc==NULL) { //���������Ԫ��
            G->vertices[head].firstarc = p;
            G->vertices[head].lastArc = p;
        }
        else{//����㲻����Ԫ��
            G->vertices[head].lastArc->nextarc = p;
            G->vertices[head].lastArc = p;
        }
        G->arcnum++;
        //��������ͼ���Σ������෴�ı߼���
        if(G->kind==UNDIRECTION_GRAPH){
            q = GenerateArc(head,weight);
            if(G->vertices[tail].firstarc==NULL){
                G->vertices[tail].firstarc = q;
                G->vertices[tail].lastArc = q;
            }
            else{
                G->vertices[tail].lastArc->nextarc = q;
                G->vertices[tail].lastArc = q;
            }
            G->arcnum++;
        }
    }
    return OK;
}

/**
 * func������ͼ
 * @param Gra
 * @return ״̬��
 */
Status CreateGraph(Graph **Gra) {
    if(*Gra) return ERROR;
    Graph * G = (Graph *)malloc(sizeof(Graph));
    (*Gra) = G;
    if(!G) return ERROR;
    int type;
    std::cout << "��ѡ��ͼ�����ͣ�1������ͼ����0������ͼ��";
    std::cin >> type;
    //��ȡ����
    G->kind = (type==1?UNDIRECTION_GRAPH:DIRECTION_GRAPH);
    G->vexnum = 0;G->arcnum = 0;
    //�����ж������óɲ�����
    for(int i = 0;i<MAX_VERTEX_NUM;i++) G->vertices[i].tag = UNEXIST;
    int flag1,flag2;
    flag1 = CreateVex(G);//��������
    flag2 = CreateArc(G);//�����ߣ�ע��˳���ܵߵ���
    //��cur���λ�ɵ�һ����cur��Ϊ��first��nextAdj׼����
    for(int i = 0;i<MAX_VERTEX_NUM;i++){
        G->vertices[i].cur = G->vertices[i].firstarc;
    }
    return flag1 && flag2;
}

/**
 * func:����ͼ
 * @param Gra
 * @return
 */
Status DestroyGraph(Graph **Gra){
    Graph *G = *Gra;
    ArcNode * p = NULL;
    for(int i = 0;i<MAX_VERTEX_NUM;i++){
        G->vertices[i].tag = -1;
        p = G->vertices[i].firstarc;
        ArcNode * tmp;
        //�����ͷ��ڽӱ�ڵ�
        while(p){
            tmp = p;
            p = p->nextarc;
            free(tmp);
        }
    }
    free(G);//�ͷŷ���Ŀռ�
    (*Gra) = NULL;//�������Ҫ����
    return OK;
}
/**
 * ��ȡ�����ַ
 * @param G ͼ
 * @param Info ���Ƚ���Ϣ
 * @param Gcompare �ȽϺ���
 * @param node ���صĶ����ַ
 * @return λ�û���-1
*/
int LocateVex(Graph * G,char * cmp,void *Gcompare){
    if(!G) return ERROR;
    //ֱ�ӴӶ���������������Ѱ�ң�����BFS��DFS
    int (*Gcmp)(char *,char *);//����ָ��
    Gcmp = (int(*)(char *, char *))(Gcompare);
    for(int i = 0;i<MAX_VERTEX_NUM;i++){
        if(G->vertices[i].tag==UNEXIST)  continue;//���������ڵ�λ��ֱ������
        if(Gcmp(G->vertices[i].data.c,cmp)==0){
            return i;//���ҵ�ֱ�ӷ�����λ
        }
    }
    return -1;//���Ҳ��ɹ�����-1
}

Vnode * GetVex(Graph *G,int key){
    if(!G||key<0||key>=MAX_VERTEX_NUM||G->vertices[key].tag<0) return NULL;
    return &G->vertices[key];//����keyֱ�ӻ�ö��㣬ʱ�临�Ӷ�ΪO(1)
}
/**
 * func �������㸳ֵ
 * @param G ͼG
 * @param key ����ֵ����ı��
 * @param e ��ֵ��data��
 * @return ״̬��
 */
Status PutVex(Graph * G,int key,ElemType e){
    if(!G||key<0||key>=MAX_VERTEX_NUM||G->vertices[key].tag<0) return ERROR;
    G->vertices[key].data = e;
    return OK;
}

/**
 * func:��ȡ��һ���ڽ��
 * @param G
 * @param key
 * @return
 */
int FirstAdjVex(Graph *G,int key){
    if(!G||key<0||key>MAX_VERTEX_NUM||G->vertices[key].tag<0||!G->vertices[key].firstarc) return -1;
    G->vertices[key].cur = G->vertices[key].firstarc;//cur����
    if(!G->vertices[key].firstarc) return -1;//���first��Ϊ�գ���ô����-1
    else{
        G->vertices[key].cur =  G->vertices[key].firstarc->nextarc;
        return G->vertices[key].firstarc->adjvex;
    }//���򷵻ص�һ���ڽӵ�
}

/**
 * func : �����һ������
 * @param G ͼָ��
 * @param key �ؼ�ֵ
 * @return �ڵ�
 */
int NextAdjVex(Graph *G,int key){
    if(G==NULL||key<0||key>=MAX_VERTEX_NUM||G->vertices[key].tag<0) return -1;
    if(G->vertices[key].cur ==NULL) return -1;//��ǰ��curΪ�գ��򷵻�-1
    int kkk = G->vertices[key].cur->adjvex;//��������ص�ֵ
    G->vertices[key].cur = G->vertices[key].cur->nextarc;//��ǰָ��������һ��
    return kkk;
}

/**
 * func : ����ڵ�
 * @param G ͼG
 * @param v ����ָ�루����ǿգ�
 * @param key ; ��keyΪ-1ʱ��ֱ�ӷ��ں���
 * @return ״̬��
 */
Status InsertVex(Graph * G,Vnode *v,int key){
    if(!G||!v) return ERROR;
    v->firstarc = v->cur = v->lastArc = NULL;//�²����Ķ�����ڽ���ȫ����Ϊ��
    v->tag = NEWLY;
    if(key == -1){//-1����ֱ�Ӳ��뵽β��
        G->vertices[G->vexnum] = (*v);//���и�ֵ
    }
    else{
        if(G->vertices[key].tag>0) return ERROR;//���������ж��㣬�򷵻ش�����
        G->vertices[key] = (*v);//���и�ֵ
    }
    G->vexnum++;
    return OK;
}

/**
 * func :����keyֵɾ����
 * @param G ͼ��ַ
 * @param head ��β�ڵ�
 * @param tail ��ͷ�ڵ�
 * @return ״̬��
 */
Status DeleteArcByKey(Graph * G,int head,int tail){
    if(!G) return ERROR;
    ArcNode * tmp,*p;
    //ɾ��������tailΪ��ͷ�Ľڵ㣬��ѭ�����Է�ֹ�ж����
    while(G->vertices[head].firstarc&&G->vertices[head].firstarc->adjvex==tail){
        tmp = G->vertices[head].firstarc;
        G->vertices[head].firstarc = G->vertices[head].firstarc->nextarc;
        free(tmp);
        G->arcnum--;
    }
    //ɾ����tail���ӵıߣ�����tail���ǵ�һ���ڽӱ�ڵ�
    for(p = G->vertices[head].firstarc;p&&p->nextarc;p = p->nextarc){
        if(p->nextarc->adjvex==tail){
            tmp = p->nextarc;
            p->nextarc = tmp->nextarc;
            free(tmp);
            G->arcnum--;
        }
    }
    return OK;
}

/**
 * func :ɾ������
 * @param G ͼ��ַ
 * @param v ����
 * @return ״̬��
 */
Status DeleteVex(Graph *G,Vnode *v){
    if(!G||!v) return ERROR;
    //ɾ������ķ�ʽ���ǽ���tag����ΪUNEXIST
    int d_key = LocateVex(G,v->data.c,(void *)&strcmp);
    v->tag = -1;
    for(int i = 0;i<MAX_VERTEX_NUM;i++){
        //ѭ������
        DeleteArcByKey(G,d_key,i); //ɾ����
        DeleteArcByKey(G,i,d_key);
    }
    return OK;
}

/**
 * func: �ж��Ƿ������key_headΪ��β����key_tailΪ��ͷ�ı�
 * @param G ͼ��ַ
 * @param key_head ��β�ڵ�
 * @param key_tail ��ͷ�ڵ�
 * @return ״̬��
 */
int HasArc(Graph * G, int key_head, int key_tail){
    if(!G) return ERROR;
    Vnode *head = GetVex(G,key_head);//��ȡ��β�ڵ�
    ArcNode * p = NULL;
    for(p = head->firstarc;p;p = p->nextarc){
        if(p->adjvex==key_tail) return 1;
    }
    return 0;
}

/**
 * func: �����
 * @param G ͼ��ַ
 * @param key_head ��β�ڵ㣨�����㣩
 * @param key_tail ��ͷ�ڵ㣨�����㣩
 * @param weight Ȩ��
 * @return ״̬��
 */
Status InsertArc(Graph *G,int key_head,int key_tail,int weight){
    if(!G) return ERROR;
    Vnode * head = GetVex(G,key_head);//����keyֵ��ȡ�ڵ�
    Vnode * tail = GetVex(G,key_tail);
    if((!head)||(head->tag==UNEXIST)||(!tail)||tail->tag==UNEXIST) return ERROR;
    if(HasArc(G,key_head,key_tail)) return OK;//����Ѿ����ڱߣ���ôֱ�ӷ���OK
    ArcNode * p = (ArcNode * )malloc(sizeof(ArcNode));
    if(!p) return ERROR;
    p->nextarc = NULL;p->adjvex = key_tail; //���²����ı߽��и�ֵ
    if(head->firstarc==NULL){ //���first��Ϊ�գ���ô�²����ı߾���first
        head->lastArc = head->cur = head->firstarc = p;
    }
    else{//�����²����ı߲��뵽β��
        head->lastArc->nextarc = p;
        head->lastArc = head->lastArc->nextarc;
    }
    p->info.weigtht = weight;//����Ȩ�ظ�ֵ
    G->arcnum++;
    //��������ͼ
    if(G->kind==UNDIRECTION_GRAPH){
        if(HasArc(G,key_tail,key_head)) return OK;
        //���������������ϵ�ʱ�򣬾Ͳ���һ����
        ArcNode * q = (ArcNode *)malloc(sizeof(ArcNode));
        q->nextarc = NULL;
        q->adjvex = key_head;
        q->info.weigtht = p->info.weigtht;
        if(tail->firstarc==NULL){
            tail->cur = tail->lastArc = tail->firstarc = q;
        } else{
            tail->lastArc->nextarc = q;
            tail->lastArc = tail->lastArc->nextarc;
        }
        G->arcnum++;
    }
    return OK;
}

/**
 * func : ɾ����
 * @param G ͼ��ַ
 * @param key_head ��β�ڵ�
 * @param key_tail ��ͷ�ڵ�
 * @return ״̬��
 */
Status DeleteArc(Graph *G,int key_head,int key_tail){
    if(!G) return ERROR;
    //��ȡ�ڵ�
    Vnode * head = GetVex(G,key_head);
    Vnode * tail = GetVex(G,key_tail);
    if(!head||!tail) return ERROR;
    //ɾ����
    int flag1 = DeleteArcByKey(G,key_head,key_tail);
    int flag2;
    if(G->kind==UNDIRECTION_GRAPH) flag2 = DeleteArcByKey(G,key_tail,key_head);
    return flag1&&flag2;
}


Status DFSOneVex(Graph * G,void * visit,int first_key);
/**
 * func��������ȱ���
 * @param G ͼ��ַ
 * @param visit ���ʺ���ָ��
 * @return ״̬��
 */
Status DFSTraverse(Graph *G,void * visit){
    if(!G) return ERROR;
    //��ʼ���ڵ�
    for(int i = 0;i<MAX_VERTEX_NUM;i++){
        if(G->vertices[i].tag!=UNEXIST){
            G->vertices[i].tag=NEWLY;
        }
    }
    cout << "������������"<<endl;
    int first_key;
    cin >> first_key;
    //��һ�����㿪ʼ����
    int flag = DFSOneVex(G,visit,first_key);
    //���ڷ���ͨͼ����Ҫ����Ƿ���δ�������Ľڵ�
    for(int i = 0;i<MAX_VERTEX_NUM;i++){
        if(G->vertices[i].tag==NEWLY)
            DFSOneVex(G,visit,i);
    }
    return OK;
}

//��һ�����㿪ʼ�������ݹ���ʽ��
Status DFSOneVexRec(Graph * G,void *visit,int first_key){
    int (* vst)(Graph * G, Vnode * node);
    vst = (int (* )(Graph * G,Vnode *node))visit;//���ʺ���

    if(first_key<0||first_key>=MAX_VERTEX_NUM||G->vertices[first_key].tag==UNEXIST) return ERROR;

    if(G->vertices[first_key].tag==NEWLY){
        vst(G,&G->vertices[first_key]);
        G->vertices[first_key].tag=OLD;
        for(int key = FirstAdjVex(G,first_key);key>=0;key = NextAdjVex(G,first_key)){
            DFSOneVex(G,visit,key);
        }
    }
    return OK;
}

//��һ�����㿪ʼ�������ǵݹ���ʽ��
Status DFSOneVex(Graph * G,void *visit,int first_key){
    int (* vst)(Graph * G, Vnode * node);
    vst = (int (* )(Graph * G,Vnode *node))visit;//���ʺ���
    int key;
    if(first_key<0||first_key>=MAX_VERTEX_NUM||G->vertices[first_key].tag==UNEXIST) return ERROR;
    stack<int> st;
    st.push(first_key);
    do{
        first_key = st.top();st.pop();
        if(GetVex(G,first_key)->tag!=NEWLY) continue;
        vst(G,&G->vertices[first_key]);
        G->vertices[first_key].tag=OLD;
        for(int key = FirstAdjVex(G,first_key);key>=0;key = NextAdjVex(G,first_key)){
            if(GetVex(G,key)->tag==NEWLY) st.push(key);
        }
    }while(!st.empty());
    return OK;
}
Status BFSOneVex(Graph * G,void * visit,int first_key);
/**
 * func:������ȱ���
 * @param G ͼ��ַ
 * @param visit ���ʺ���
 * @return ״̬��
 */
Status BFSTraverse(Graph *G,void * visit){
    if(!G) return ERROR;
    //��ʼ���ڵ��tag��ΪNEWLY
    for(int i = 0;i<MAX_VERTEX_NUM;i++){
        if(G->vertices[i].tag!=UNEXIST){
            G->vertices[i].tag=NEWLY;
        }
    }
    cout << "������������"<<endl;
    int first_key;
    cin >> first_key;
    if(first_key<0||first_key>=MAX_VERTEX_NUM||G->vertices[first_key].tag==UNEXIST) return ERROR;
    BFSOneVex(G,visit,first_key);//��һ���ڵ㿪ʼ���й�ȱ���
    //��ͼΪ����ͨͼ��ʱ���ٽ��б���
    for(int i = 0;i<MAX_VERTEX_NUM;i++){
        if(G->vertices[i].tag==NEWLY) BFSOneVex(G,visit,i);
    }
    return OK;
}
//��һ���ڵ㿪ʼ���й�ȱ���

Status BFSOneVex(Graph * G,void * visit,int first_key){
    int (* vst)(Graph * G, Vnode *node);
    vst = (int (* )(Graph * G,Vnode *node))visit;
    queue<int> Q;//��������ʵ�ֹ�ȱ���
    Q.push(first_key);
    do{
        first_key = Q.front();Q.pop(); //��ȡ����Ԫ�أ���������
        //���α��������е��ڽӵ㣬�����뵽������
        for(int key = FirstAdjVex(G,first_key);key>= 0;key = NextAdjVex(G,first_key)){
            if(GetVex(G,key)->tag!=NEWLY) continue;
            Q.push(key);
        }
        //�����Ԫ��δ����������ô���б���
        if(GetVex(G,first_key)->tag==NEWLY){
            vst(G,GetVex(G,first_key));
            G->vertices[first_key].tag=OLD;
        }
    }while(!Q.empty());//ѭ�����������Ƕ��п�
    return OK;
}
/**
 * func: �л�ͼ
 * @param graph ͼ����
 * @param G ͼָ��ĵ�ַ
 * @param num ͼ���
 * @return ״̬��
 */
Status ChangeGraph(Graph * graph[], Graph ** G, int num){
    if(!graph[num]) (*G) = graph[num];
    else return ERROR;
    return OK;
}

/**
 * func: ��������
 * @param G ͼ��ַ
 * @return ״̬��
 */
Status SaveData(Graph * G){
    FILE * fvex, * farc, *finfo;
    fvex = fopen("vex","w");
    if(!fvex) return ERROR;
    //����д�붥����Ϣ
    for(int i = 0;i<MAX_VERTEX_NUM;i++){
        if(G->vertices[i].tag!=UNEXIST){
            fprintf(fvex,"%d %d %s ",i,G->vertices[i].data.n,G->vertices[i].data.c);
        }
    }
    fprintf(fvex,"%d",-1);//�ļ�ĩβ-1
    fclose(fvex);//�ر��ļ�
    farc = fopen("arc","w");
    if(!farc) return ERROR;
    ArcNode * p;
    //����д��ߵ���Ϣ
    for(int i = 0;i<MAX_VERTEX_NUM;i++){
        if(G->vertices[i].tag!=UNEXIST){
            p = G->vertices[i].firstarc;
            while(p){
                fprintf(farc,"%d %d %d ",i,p->adjvex,p->info.weigtht);
                p = p->nextarc;
            }
        }
    }
    fprintf(farc,"%d",-1);//�ļ�ĩβ-1
    fclose(farc);//�ر��ļ�
    finfo = fopen("info","w");
    if(!finfo) return ERROR;
    //д��ͼ����Ϣ
    fprintf(finfo,"%d %d %d",G->kind,G->vexnum, G->arcnum);
    fclose(finfo);//�ر��ļ�
    return OK;
}

/**
 * func:��������
 * @param Gra ͼָ��ĵ�ַ
 * @return ״̬��
 */
Status LoadData(Graph ** Gra){
    //���ͼ�����ڣ������ռ�
    if(*Gra==NULL) *Gra = (Graph *)malloc(sizeof(Graph));
    Graph * G = *Gra;
    //��ʼ���ڵ�ȫ��Ϊ������
    for(int i = 0;i<MAX_VERTEX_NUM;i++) G->vertices[i].tag = UNEXIST;
    FILE * fvex, *farc, *finfo;
    //ֻ��Ҫ��ȡ�����㣬Ȼ��߼�ͨ��InsertArc���
    finfo = fopen("info","r");
    if(!finfo) return ERROR;
    //��ȡͼ��Ϣ
    fscanf(finfo,"%d%d%d",&G->kind,&G->vexnum,&G->arcnum);
    fclose(finfo);
    fvex = fopen("vex","r");
    if(!fvex) return ERROR;
    int key;
    //ѭ����ȡ������Ϣ
    while(fscanf(fvex,"%d",&key) && key>=0&&key<MAX_VERTEX_NUM){
        fscanf(fvex,"%d%s",&G->vertices[key].data.n,G->vertices[key].data.c);
        G->vertices[key].tag=NEWLY;
        G->vertices[key].firstarc = G->vertices[key].cur = G->vertices[key].cur = NULL;
    }
    fclose(fvex);//�ر��ļ�
    farc = fopen("arc","r");
    if(!farc) return ERROR;
    int head,tail,weight;
    //ѭ�������
    while(fscanf(farc,"%d",&head)&&head>=0&&head<MAX_VERTEX_NUM){
        fscanf(farc,"%d%d",&tail,&weight);
        InsertArc(G,head,tail,weight);
    }
    fclose(farc);
    //��cur���λ�ɵ�һ����cur��Ϊ��first��nextAdj׼����
    for(int i = 0;i<MAX_VERTEX_NUM;i++){
        G->vertices[i].cur = G->vertices[i].firstarc;
    }
    return OK;
}





