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
 * func:访问函数
 * @param G 图地址G
 * @param node 顶点类型
 * @return 状态码
 */
int visit(Graph * G,Vnode * node){
    if(!G) return ERROR;
    if(!node||node->tag<0) return -1;
    cout << "key值为"<<LocateVex(G,node->data.c,(void * )(&strcmp))<<", n值为："<< node->data.n<<", c值为"<<node->data.c<<endl;
    return OK;
}


/**
 * func: 创造节点
 * @param G 图地址
 * @return 状态码
 */
Status CreateVex(Graph * G){
    if(!G) return ERROR;
    Vnode * vex = G->vertices;
    int count = 0;int type;
    int index = -1;
    int flag = 1;//判断输入是否合法
    cout << "请输入顶点数量"<< endl;
    cin >> count;
    G->vexnum = (count > 0?count:0); //设置图顶点的数量
    if(count <=0 ) return ERROR;
    cout << "请输入顶点的关键值key(范围0-"<<count-1<<")、n值、c值，以空格隔开,\n当key值为负值时输入结束"<< endl;
    int key;
    while(1){
        cin >> key;
        if(key < 0) break;//当k为负值时，输入结束
        //输入数据
        cin >> G->vertices[key].data.n;
        cin >> G->vertices[key].data.c;
        //初始时将顶点的指针域都设置为NULL
        G->vertices[key].firstarc = G->vertices[key].lastArc = G->vertices[key].cur = NULL;
        G->vertices[key].tag = NEWLY; //设置顶点的标志域为NEWLY
    }
    return OK;
}

/**
 * func: 产生边
 * @param tail 以tail为尾的边
 * @return 边地址
 */
ArcNode * GenerateArc(int tail,int weight){
    //生成一个以弧尾节点为tail权重为weight的邻接点
    ArcNode * newArc = (ArcNode*)malloc(sizeof(ArcNode));//分配空间
    //赋值
    newArc->nextarc = NULL;
    newArc->adjvex = tail;
    newArc->info.weigtht = weight;
    return newArc;
}

/**
 * func: 创造边
 * @param G 图地址
 * @return 状态码
 */
Status CreateArc(Graph * G){
    if(!G) return ERROR;
    int head;//弧尾
    int tail;//弧头
    ArcNode * p = NULL;
    ArcNode * q;

    //给出提示
    (G->kind==UNDIRECTION_GRAPH)?(cout << "请输入关联的两个顶点的关键值\n"):(cout<<"请输入起点和终点的关键值\n");
    while(1){
        cin >> head;
        if(head<0)  break;//当输入为负值的时候退出循环
        cin>>tail;
        //当不满足条件的时候返回错误码
        if(head >=MAX_VERTEX_NUM||tail < 0 || tail >= MAX_VERTEX_NUM||
           G->vertices[tail].tag<0||G->vertices[head].tag<0) return ERROR;
        int weight;
        cout << "请输入权值："<<endl;
        cin >> weight;
        p = GenerateArc(tail,weight);//产生一个邻接点
        if(G->vertices[head].firstarc==NULL) { //插入点是首元素
            G->vertices[head].firstarc = p;
            G->vertices[head].lastArc = p;
        }
        else{//插入点不是首元素
            G->vertices[head].lastArc->nextarc = p;
            G->vertices[head].lastArc = p;
        }
        G->arcnum++;
        //处理无向图情形，补充相反的边即可
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
 * func：产生图
 * @param Gra
 * @return 状态码
 */
Status CreateGraph(Graph **Gra) {
    if(*Gra) return ERROR;
    Graph * G = (Graph *)malloc(sizeof(Graph));
    (*Gra) = G;
    if(!G) return ERROR;
    int type;
    std::cout << "请选择图的类型：1（无向图），0（有向图）";
    std::cin >> type;
    //获取类型
    G->kind = (type==1?UNDIRECTION_GRAPH:DIRECTION_GRAPH);
    G->vexnum = 0;G->arcnum = 0;
    //将所有顶点设置成不存在
    for(int i = 0;i<MAX_VERTEX_NUM;i++) G->vertices[i].tag = UNEXIST;
    int flag1,flag2;
    flag1 = CreateVex(G);//产生顶点
    flag2 = CreateArc(G);//产生边（注：顺序不能颠倒）
    //将cur域归位成第一个，cur是为了first和nextAdj准备的
    for(int i = 0;i<MAX_VERTEX_NUM;i++){
        G->vertices[i].cur = G->vertices[i].firstarc;
    }
    return flag1 && flag2;
}

/**
 * func:销毁图
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
        //依次释放邻接表节点
        while(p){
            tmp = p;
            p = p->nextarc;
            free(tmp);
        }
    }
    free(G);//释放分配的空间
    (*Gra) = NULL;//销毁完后要归零
    return OK;
}
/**
 * 获取顶点地址
 * @param G 图
 * @param Info 待比较信息
 * @param Gcompare 比较函数
 * @param node 返回的顶点地址
 * @return 位置或者-1
*/
int LocateVex(Graph * G,char * cmp,void *Gcompare){
    if(!G) return ERROR;
    //直接从顶点数组依次向下寻找，不用BFS和DFS
    int (*Gcmp)(char *,char *);//函数指针
    Gcmp = (int(*)(char *, char *))(Gcompare);
    for(int i = 0;i<MAX_VERTEX_NUM;i++){
        if(G->vertices[i].tag==UNEXIST)  continue;//遇见不存在的位置直接跳过
        if(Gcmp(G->vertices[i].data.c,cmp)==0){
            return i;//查找到直接返回序位
        }
    }
    return -1;//查找不成功返回-1
}

Vnode * GetVex(Graph *G,int key){
    if(!G||key<0||key>=MAX_VERTEX_NUM||G->vertices[key].tag<0) return NULL;
    return &G->vertices[key];//根据key直接获得顶点，时间复杂度为O(1)
}
/**
 * func ：给顶点赋值
 * @param G 图G
 * @param key 待赋值顶点的编号
 * @param e 赋值的data域
 * @return 状态码
 */
Status PutVex(Graph * G,int key,ElemType e){
    if(!G||key<0||key>=MAX_VERTEX_NUM||G->vertices[key].tag<0) return ERROR;
    G->vertices[key].data = e;
    return OK;
}

/**
 * func:获取第一个邻结点
 * @param G
 * @param key
 * @return
 */
int FirstAdjVex(Graph *G,int key){
    if(!G||key<0||key>MAX_VERTEX_NUM||G->vertices[key].tag<0||!G->vertices[key].firstarc) return -1;
    G->vertices[key].cur = G->vertices[key].firstarc;//cur归零
    if(!G->vertices[key].firstarc) return -1;//如果first域为空，那么返回-1
    else{
        G->vertices[key].cur =  G->vertices[key].firstarc->nextarc;
        return G->vertices[key].firstarc->adjvex;
    }//否则返回第一个邻接点
}

/**
 * func : 获得下一个领结点
 * @param G 图指针
 * @param key 关键值
 * @return 节点
 */
int NextAdjVex(Graph *G,int key){
    if(G==NULL||key<0||key>=MAX_VERTEX_NUM||G->vertices[key].tag<0) return -1;
    if(G->vertices[key].cur ==NULL) return -1;//当前域cur为空，则返回-1
    int kkk = G->vertices[key].cur->adjvex;//保存待返回的值
    G->vertices[key].cur = G->vertices[key].cur->nextarc;//当前指针移向下一个
    return kkk;
}

/**
 * func : 插入节点
 * @param G 图G
 * @param v 顶点指针（必须非空）
 * @param key ; 当key为-1时，直接放在后面
 * @return 状态码
 */
Status InsertVex(Graph * G,Vnode *v,int key){
    if(!G||!v) return ERROR;
    v->firstarc = v->cur = v->lastArc = NULL;//新产生的顶点的邻接域全部置为零
    v->tag = NEWLY;
    if(key == -1){//-1代表直接插入到尾部
        G->vertices[G->vexnum] = (*v);//进行赋值
    }
    else{
        if(G->vertices[key].tag>0) return ERROR;//如果插入点有顶点，则返回错误码
        G->vertices[key] = (*v);//进行赋值
    }
    G->vexnum++;
    return OK;
}

/**
 * func :根据key值删除边
 * @param G 图地址
 * @param head 弧尾节点
 * @param tail 弧头节点
 * @return 状态码
 */
Status DeleteArcByKey(Graph * G,int head,int tail){
    if(!G) return ERROR;
    ArcNode * tmp,*p;
    //删除所有以tail为弧头的节点，用循环，以防止有多个边
    while(G->vertices[head].firstarc&&G->vertices[head].firstarc->adjvex==tail){
        tmp = G->vertices[head].firstarc;
        G->vertices[head].firstarc = G->vertices[head].firstarc->nextarc;
        free(tmp);
        G->arcnum--;
    }
    //删除与tail连接的边，其中tail不是第一个邻接表节点
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
 * func :删除顶点
 * @param G 图地址
 * @param v 顶点
 * @return 状态码
 */
Status DeleteVex(Graph *G,Vnode *v){
    if(!G||!v) return ERROR;
    //删除顶点的方式就是将其tag域置为UNEXIST
    int d_key = LocateVex(G,v->data.c,(void *)&strcmp);
    v->tag = -1;
    for(int i = 0;i<MAX_VERTEX_NUM;i++){
        //循环查找
        DeleteArcByKey(G,d_key,i); //删除边
        DeleteArcByKey(G,i,d_key);
    }
    return OK;
}

/**
 * func: 判断是否存在以key_head为弧尾，以key_tail为弧头的边
 * @param G 图地址
 * @param key_head 弧尾节点
 * @param key_tail 弧头节点
 * @return 状态码
 */
int HasArc(Graph * G, int key_head, int key_tail){
    if(!G) return ERROR;
    Vnode *head = GetVex(G,key_head);//获取弧尾节点
    ArcNode * p = NULL;
    for(p = head->firstarc;p;p = p->nextarc){
        if(p->adjvex==key_tail) return 1;
    }
    return 0;
}

/**
 * func: 插入边
 * @param G 图地址
 * @param key_head 弧尾节点（出发点）
 * @param key_tail 弧头节点（结束点）
 * @param weight 权重
 * @return 状态码
 */
Status InsertArc(Graph *G,int key_head,int key_tail,int weight){
    if(!G) return ERROR;
    Vnode * head = GetVex(G,key_head);//根据key值获取节点
    Vnode * tail = GetVex(G,key_tail);
    if((!head)||(head->tag==UNEXIST)||(!tail)||tail->tag==UNEXIST) return ERROR;
    if(HasArc(G,key_head,key_tail)) return OK;//如果已经存在边，那么直接返回OK
    ArcNode * p = (ArcNode * )malloc(sizeof(ArcNode));
    if(!p) return ERROR;
    p->nextarc = NULL;p->adjvex = key_tail; //对新产生的边进行赋值
    if(head->firstarc==NULL){ //如果first域为空，那么新产生的边就是first
        head->lastArc = head->cur = head->firstarc = p;
    }
    else{//否则新产生的边插入到尾部
        head->lastArc->nextarc = p;
        head->lastArc = head->lastArc->nextarc;
    }
    p->info.weigtht = weight;//进行权重赋值
    G->arcnum++;
    //处理无向图
    if(G->kind==UNDIRECTION_GRAPH){
        if(HasArc(G,key_tail,key_head)) return OK;
        //当所有条件都符合的时候，就产生一条边
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
 * func : 删除边
 * @param G 图地址
 * @param key_head 弧尾节点
 * @param key_tail 弧头节点
 * @return 状态码
 */
Status DeleteArc(Graph *G,int key_head,int key_tail){
    if(!G) return ERROR;
    //获取节点
    Vnode * head = GetVex(G,key_head);
    Vnode * tail = GetVex(G,key_tail);
    if(!head||!tail) return ERROR;
    //删除边
    int flag1 = DeleteArcByKey(G,key_head,key_tail);
    int flag2;
    if(G->kind==UNDIRECTION_GRAPH) flag2 = DeleteArcByKey(G,key_tail,key_head);
    return flag1&&flag2;
}


Status DFSOneVex(Graph * G,void * visit,int first_key);
/**
 * func：深度优先遍历
 * @param G 图地址
 * @param visit 访问函数指针
 * @return 状态码
 */
Status DFSTraverse(Graph *G,void * visit){
    if(!G) return ERROR;
    //初始化节点
    for(int i = 0;i<MAX_VERTEX_NUM;i++){
        if(G->vertices[i].tag!=UNEXIST){
            G->vertices[i].tag=NEWLY;
        }
    }
    cout << "请输入遍历起点"<<endl;
    int first_key;
    cin >> first_key;
    //从一个顶点开始遍历
    int flag = DFSOneVex(G,visit,first_key);
    //对于非连通图，需要检查是否还有未被遍历的节点
    for(int i = 0;i<MAX_VERTEX_NUM;i++){
        if(G->vertices[i].tag==NEWLY)
            DFSOneVex(G,visit,i);
    }
    return OK;
}

//从一个顶点开始遍历（递归形式）
Status DFSOneVexRec(Graph * G,void *visit,int first_key){
    int (* vst)(Graph * G, Vnode * node);
    vst = (int (* )(Graph * G,Vnode *node))visit;//访问函数

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

//从一个顶点开始遍历（非递归形式）
Status DFSOneVex(Graph * G,void *visit,int first_key){
    int (* vst)(Graph * G, Vnode * node);
    vst = (int (* )(Graph * G,Vnode *node))visit;//访问函数
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
 * func:广度优先遍历
 * @param G 图地址
 * @param visit 访问函数
 * @return 状态码
 */
Status BFSTraverse(Graph *G,void * visit){
    if(!G) return ERROR;
    //初始化节点的tag域为NEWLY
    for(int i = 0;i<MAX_VERTEX_NUM;i++){
        if(G->vertices[i].tag!=UNEXIST){
            G->vertices[i].tag=NEWLY;
        }
    }
    cout << "请输入遍历起点"<<endl;
    int first_key;
    cin >> first_key;
    if(first_key<0||first_key>=MAX_VERTEX_NUM||G->vertices[first_key].tag==UNEXIST) return ERROR;
    BFSOneVex(G,visit,first_key);//从一个节点开始进行广度遍历
    //当图为非连通图的时候，再进行遍历
    for(int i = 0;i<MAX_VERTEX_NUM;i++){
        if(G->vertices[i].tag==NEWLY) BFSOneVex(G,visit,i);
    }
    return OK;
}
//从一个节点开始进行广度遍历

Status BFSOneVex(Graph * G,void * visit,int first_key){
    int (* vst)(Graph * G, Vnode *node);
    vst = (int (* )(Graph * G,Vnode *node))visit;
    queue<int> Q;//借助队列实现广度遍历
    Q.push(first_key);
    do{
        first_key = Q.front();Q.pop(); //获取队首元素，并出队列
        //依次遍历出队列的邻接点，并加入到队列中
        for(int key = FirstAdjVex(G,first_key);key>= 0;key = NextAdjVex(G,first_key)){
            if(GetVex(G,key)->tag!=NEWLY) continue;
            Q.push(key);
        }
        //如果该元素未被遍历，那么进行遍历
        if(GetVex(G,first_key)->tag==NEWLY){
            vst(G,GetVex(G,first_key));
            G->vertices[first_key].tag=OLD;
        }
    }while(!Q.empty());//循环结束条件是队列空
    return OK;
}
/**
 * func: 切换图
 * @param graph 图数组
 * @param G 图指针的地址
 * @param num 图编号
 * @return 状态码
 */
Status ChangeGraph(Graph * graph[], Graph ** G, int num){
    if(!graph[num]) (*G) = graph[num];
    else return ERROR;
    return OK;
}

/**
 * func: 保存数据
 * @param G 图地址
 * @return 状态码
 */
Status SaveData(Graph * G){
    FILE * fvex, * farc, *finfo;
    fvex = fopen("vex","w");
    if(!fvex) return ERROR;
    //依次写入顶点信息
    for(int i = 0;i<MAX_VERTEX_NUM;i++){
        if(G->vertices[i].tag!=UNEXIST){
            fprintf(fvex,"%d %d %s ",i,G->vertices[i].data.n,G->vertices[i].data.c);
        }
    }
    fprintf(fvex,"%d",-1);//文件末尾-1
    fclose(fvex);//关闭文件
    farc = fopen("arc","w");
    if(!farc) return ERROR;
    ArcNode * p;
    //依次写入边的信息
    for(int i = 0;i<MAX_VERTEX_NUM;i++){
        if(G->vertices[i].tag!=UNEXIST){
            p = G->vertices[i].firstarc;
            while(p){
                fprintf(farc,"%d %d %d ",i,p->adjvex,p->info.weigtht);
                p = p->nextarc;
            }
        }
    }
    fprintf(farc,"%d",-1);//文件末尾-1
    fclose(farc);//关闭文件
    finfo = fopen("info","w");
    if(!finfo) return ERROR;
    //写入图的信息
    fprintf(finfo,"%d %d %d",G->kind,G->vexnum, G->arcnum);
    fclose(finfo);//关闭文件
    return OK;
}

/**
 * func:加载数据
 * @param Gra 图指针的地址
 * @return 状态码
 */
Status LoadData(Graph ** Gra){
    //如果图不存在，则分配空间
    if(*Gra==NULL) *Gra = (Graph *)malloc(sizeof(Graph));
    Graph * G = *Gra;
    //初始化节点全部为不存在
    for(int i = 0;i<MAX_VERTEX_NUM;i++) G->vertices[i].tag = UNEXIST;
    FILE * fvex, *farc, *finfo;
    //只需要读取各个点，然后边集通过InsertArc完成
    finfo = fopen("info","r");
    if(!finfo) return ERROR;
    //读取图信息
    fscanf(finfo,"%d%d%d",&G->kind,&G->vexnum,&G->arcnum);
    fclose(finfo);
    fvex = fopen("vex","r");
    if(!fvex) return ERROR;
    int key;
    //循环读取顶点信息
    while(fscanf(fvex,"%d",&key) && key>=0&&key<MAX_VERTEX_NUM){
        fscanf(fvex,"%d%s",&G->vertices[key].data.n,G->vertices[key].data.c);
        G->vertices[key].tag=NEWLY;
        G->vertices[key].firstarc = G->vertices[key].cur = G->vertices[key].cur = NULL;
    }
    fclose(fvex);//关闭文件
    farc = fopen("arc","r");
    if(!farc) return ERROR;
    int head,tail,weight;
    //循环插入边
    while(fscanf(farc,"%d",&head)&&head>=0&&head<MAX_VERTEX_NUM){
        fscanf(farc,"%d%d",&tail,&weight);
        InsertArc(G,head,tail,weight);
    }
    fclose(farc);
    //将cur域归位成第一个，cur是为了first和nextAdj准备的
    for(int i = 0;i<MAX_VERTEX_NUM;i++){
        G->vertices[i].cur = G->vertices[i].firstarc;
    }
    return OK;
}





