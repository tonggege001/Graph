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
        printf("    ��ѡ����Ĳ���[0~20]:");
        fflush(stdin);
        scanf("%d",&op);
        switch(op){
            case 1:
                if(CreateGraph(&G)==OK) printf("ͼ�����ɹ���\n");
                else printf("ͼ����ʧ�ܣ�\n");
                break;
            case 2:
                if(DestroyGraph(&G)==OK){
                    G = NULL;
                    printf("ͼ���ٳɹ���\n");
                }
                else{
                    printf("����ͼʧ�ܣ�");
                }
                break;
            case 3:
                printf("������Cֵ��\n");
                scanf("%s",c);
                (key = LocateVex(G,c,(void*)&strcmp))<0?printf("û���ҵ���Ԫ�أ�\n"):printf("ֵΪ%s��Ԫ�ص���λΪ�� %d",c,key);
                break;
            case 4:
                printf("��������Ҫ��õĽڵ㣺");
                scanf("%d",&key);
                Node = GetVex(G,key);
                Node == NULL?printf("��ָ�����\n"):printf("�ýڵ�nֵΪ�� %d, cֵΪ�� %s",Node->data.n,Node->data.c);
                break;
            case 5:
                printf("��������Ҫ�޸ĵĽڵ㣺");
                scanf("%d",&key);
                printf("������ڵ��nֵ��cֵ��\n");
                scanf("%d%s",&e.n,e.c);
                PutVex(G,key,e)==ERROR?printf("��������"):printf("�޸ĳɹ���");
                break;
            case 6:
                printf("������ڵ��keyֵ��");
                scanf("%d",&key);
                key = FirstAdjVex(G,key);
                key==-1?printf("�ڵ㲻���ڣ�\n"):printf("�ڵ��λ��Ϊ��%d",key);
                break;
            case 7:
                printf("������ڵ��keyֵ��");
                scanf("%d",&key);
                key = NextAdjVex(G,key);
                key==-1?printf("�ڵ㲻���ڣ�\n"):printf("�ڵ��λ��Ϊ��%d",key);
                break;
            case 8:
                printf("��������뵽��λ��key��ֱ�Ӽӵ�ĩβʱ������-1��");
                scanf("%d",&key);
                Node = (Vnode *)malloc(sizeof(Vnode));
                printf("������ڵ��nֵ��cֵ��\n");
                scanf("%d%s",&Node->data.n,Node->data.c);
                InsertVex(G,Node,key)==ERROR?printf("����ʧ�ܣ�"):printf("����ɹ�");
                break;
            case 9:
                printf("��������Ҫɾ���Ĺؼ���key��\n");
                scanf("%d",&key);
                Node = GetVex(G,key);
                if(Node!=NULL){
                    DeleteVex(G,Node)==ERROR?printf("ɾ��ʧ�ܣ�"):printf("ɾ���ɹ���");
                }else{
                    printf("ɾ��ʧ��\n");
                }
                break;
            case 10:
                printf("�����뻡β�ڵ��keyֵ��\n");
                scanf("%d",&key);
                printf("�����뻡ͷ�ڵ��keyֵ\n");
                scanf("%d",&key2);
                printf("������Ȩ�أ�\n");
                scanf("%d",&weight);
                InsertArc(G,key,key2,weight)==ERROR?printf("���ӱ�ʧ�ܣ�"):printf("���ӱ߳ɹ���");
                break;
            case 11:
                printf("�����뻡β�ڵ��keyֵ��\n");
                scanf("%d",&key);
                printf("�����뻡ͷ�ڵ��keyֵ\n");
                scanf("%d",&key2);
                DeleteArc(G,key,key2)==ERROR?printf("ɾ����ʧ�ܣ�\n"):printf("ɾ���߳ɹ���\n");
                break;
            case 12:
                DFSTraverse(G,(void*)(&visit))==OK?printf("��ȱ����ɹ���\n"):printf("��ȱ���ʧ�ܣ�\n");
                break;
            case 13:
                BFSTraverse(G,(void*)&visit)==OK?printf("��ȱ����ɹ���\n"):printf("��ȱ���ʧ�ܣ�\n");
                break;
            case 14:
                printf("�������л��ı�ţ�\n");
                scanf("%d",&key);
                ChangeGraph(graph,&G,key) ? (printf("�ɹ��л�����%d��ͼ",key),current = key):printf("�л�ʧ��");
                break;
            case 15:
                SaveData(G)==OK?printf("���̳ɹ�\n"):printf("����ʧ��\n");
                break;
            case 16:
                  LoadData(&G)==OK?printf("���سɹ�\n"):printf("����ʧ��\n");
                break;
            case 0:
                break;
        }//end of switch
    }//end of while
    printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
}//end of main()

