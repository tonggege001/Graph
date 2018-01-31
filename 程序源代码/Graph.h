//
// Created by Administrator on 2017/12/1.
//

#ifndef DATASTRUCTURE_GRAPH_H
#define DATASTRUCTURE_GRAPH_H

#endif //DATASTRUCTURE_GRAPH_H

#include "BasicConst.h"

#define MAX_VERTEX_NUM 20

#define DIRECTION_GRAPH 1
#define UNDIRECTION_GRAPH 0
//
#define UNEXIST -1
#define NEWLY 0
#define OLD 1


typedef int Status; //函数的状态码

typedef int Status; //函数返回值的状态码

typedef struct ElemType{
    char c[2];//一个字符
    int n;//一个数字
}ElemType;//基础数据类型

typedef struct InfoType{
    int weigtht;//存放弧的权值
}InfoType;//弧信息

typedef struct ArcNode{
    int adjvex;                //该弧指向的顶点位置
    struct ArcNode * nextarc;    //指向下一条弧
    InfoType info;				 //弧的信息
}ArcNode;//边类型

typedef struct Vnode{
    ElemType data;  //顶点信息
    ArcNode * firstarc;//指向第一条弧头节点
    ArcNode * lastArc; //最后一条弧头节点，用于方便插入
    ArcNode * cur;		//指向当前弧头节点，用于寻找第一个、下一个邻接点
    int tag;				//顶点的标志域，用于判断顶点是否被遍历到
}Vnode;//顶点类型

typedef struct Graph{
    Vnode vertices[MAX_VERTEX_NUM];//顶点集
    int vexnum,arcnum;			//边和顶点的数量
    int kind; 					//图的种类标志
}Graph;//图类型


int visit(Graph * G,Vnode * node);
Status CreateVex(Graph * G);
ArcNode * GenerateArc(int tail);
Status CreateArc(Graph * G);
Status CreateGraph(Graph ** Gra);
Status DestroyGraph(Graph **Gra);
int LocateVex(Graph * G,char * cmp,void *Gcompare);
Vnode * GetVex(Graph *G,int key);
Status PutVex(Graph * G,int key,ElemType e);
int FirstAdjVex(Graph *G,int key);
int NextAdjVex(Graph *G,int key);
Status InsertVex(Graph * G,Vnode *v,int key);
Status DeleteArcByKey(Graph * G,int head,int tail);
Status DeleteVex(Graph *G,Vnode *v);
int HasArc(Graph * G, int key_head, int key_tail);
Status InsertArc(Graph *G,int key_head,int key_tail,int weight);
Status DeleteArc(Graph *G,int key_head,int key_tail);
Status DFSTraverse(Graph *G,void * visit);
Status BFSTraverse(Graph *G,void * visit);
Status ChangeGraph(Graph * graph[], Graph ** G, int num);
Status SaveData(Graph * G);
Status LoadData(Graph ** G);
























