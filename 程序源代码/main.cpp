//
// Created by tonggege on 17-11-14.
//

#include <stdio.h>
#include <cstring>
#include "BasicConst.h"
#include "Graph.h"



Graph * graph[10];
int current;
int main(void){
    Graph * G = NULL;  int op=1;
    int key;int key2;int weight;
    current = 1;
    char c[2];
    ElemType e;
    ElemType e2;
    Vnode * Node = NULL;Vnode * Node2 = NULL;
    ArcNode * arc1 = NULL;ArcNode * arc2 = NULL;
    while(op){
        //  system("cls");
        printf("\n\n");
        printf("             Menu for Graph Based on Adjacency list \n");
        printf("-------------------------------------------------\n");
        printf("    	  1. CreateGraph           7. NextAdjVex\n");
        printf("    	  2. DestroyGraph          8. InsertVex\n");
        printf("    	  3. LocateVex             9. DeleteVex\n");
        printf("    	  4. GetVex                10.InsertArc \n");
        printf("    	  5. PutVex                11. DeleteArc \n");
        printf("    	  6. FirstAdjVex           12. DFSTraverse \n");
        printf("    	  13. BFSTraverse          14. ChangeGraph. \n");
        printf("          15. SaveData             16.LoadData\n");
        printf("          0.Exit\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~20]:");
        fflush(stdin);
        scanf("%d",&op);
        switch(op){
            case 1:
                if(CreateGraph(&G)==OK) printf("图创建成功！\n");
                else printf("图创建失败！\n");
                break;
            case 2:
                if(DestroyGraph(&G)==OK){
                    G = NULL;
                    printf("图销毁成功！\n");
                }
                else{
                    printf("销毁图失败！");
                }
                break;
            case 3:
                printf("请输入C值：\n");
                scanf("%s",c);
                (key = LocateVex(G,c,(void*)&strcmp))<0?printf("没有找到该元素！\n"):printf("值为%s的元素的序位为： %d",c,key);
                break;
            case 4:
                printf("请输入需要获得的节点：");
                scanf("%d",&key);
                Node = GetVex(G,key);
                Node == NULL?printf("空指针错误！\n"):printf("该节点n值为： %d, c值为： %s",Node->data.n,Node->data.c);
                break;
            case 5:
                printf("请输入需要修改的节点：");
                scanf("%d",&key);
                printf("请输入节点的n值和c值：\n");
                scanf("%d%s",&e.n,e.c);
                PutVex(G,key,e)==ERROR?printf("输入有误！"):printf("修改成功！");
                break;
            case 6:
                printf("请输入节点的key值：");
                scanf("%d",&key);
                key = FirstAdjVex(G,key);
                key==-1?printf("节点不存在！\n"):printf("节点的位置为：%d",key);
                break;
            case 7:
                printf("请输入节点的key值：");
                scanf("%d",&key);
                key = NextAdjVex(G,key);
                key==-1?printf("节点不存在！\n"):printf("节点的位置为：%d",key);
                break;
            case 8:
                printf("请输入加入到的位置key，直接加到末尾时请输入-1：");
                scanf("%d",&key);
                Node = (Vnode *)malloc(sizeof(Vnode));
                printf("请输入节点的n值和c值：\n");
                scanf("%d%s",&Node->data.n,Node->data.c);
                InsertVex(G,Node,key)==ERROR?printf("插入失败！"):printf("插入成功");
                break;
            case 9:
                printf("请输入需要删除的关键字key：\n");
                scanf("%d",&key);
                Node = GetVex(G,key);
                if(Node!=NULL){
                    DeleteVex(G,Node)==ERROR?printf("删除失败！"):printf("删除成功！");
                }else{
                    printf("删除失败\n");
                }
                break;
            case 10:
                printf("请输入弧尾节点的key值：\n");
                scanf("%d",&key);
                printf("请输入弧头节点的key值\n");
                scanf("%d",&key2);
                printf("请输入权重：\n");
                scanf("%d",&weight);
                InsertArc(G,key,key2,weight)==ERROR?printf("增加边失败！"):printf("增加边成功！");
                break;
            case 11:
                printf("请输入弧尾节点的key值：\n");
                scanf("%d",&key);
                printf("请输入弧头节点的key值\n");
                scanf("%d",&key2);
                DeleteArc(G,key,key2)==ERROR?printf("删除边失败！\n"):printf("删除边成功！\n");
                break;
            case 12:
                DFSTraverse(G,(void*)(&visit))==OK?printf("深度遍历成功！\n"):printf("深度遍历失败！\n");
                break;
            case 13:
                BFSTraverse(G,(void*)&visit)==OK?printf("广度遍历成功！\n"):printf("广度遍历失败！\n");
                break;
            case 14:
                printf("请输入切换的编号：\n");
                scanf("%d",&key);
                ChangeGraph(graph,&G,key) ? (printf("成功切换到第%d张图",key),current = key):printf("切换失败");
                break;
            case 15:
                SaveData(G)==OK?printf("存盘成功\n"):printf("存盘失败\n");
                break;
            case 16:
                  LoadData(&G)==OK?printf("加载成功\n"):printf("加载失败\n");
                break;
            case 0:
                break;
        }//end of switch
    }//end of while
    printf("欢迎下次再使用本系统！\n");
}//end of main()

