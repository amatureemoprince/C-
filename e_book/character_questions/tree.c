#include<stdio.h>
#include<stdlib.h>
typedef struct TreeNode{
    struct TreeNode *lchild;
    int data;
    struct TreeNode *rchild;
}TreeNode;

void preOrder(TreeNode *root){
    if(root == NULL){
        return ;
    }
    printf("%d ", root->data);
    preOrder(root->lchild);
    preOrder(root->rchild);
}

TreeNode *create(int data){
	TreeNode * node = (TreeNode *)malloc(sizeof(TreeNode));
	node->data = data;
	node->lchild = NULL;
	node->rchild = NULL;
	return node;
 }
 
void inOrder(TreeNode *root){
    if(root == NULL){
        return ;
    }
    inOrder(root->lchild);
    printf("%d ", root->data);
    inOrder(root->rchild);
}

int main(void){
	TreeNode * root = create(3);
	TreeNode * node1 = create(2);
	TreeNode * node2 = create(5);
	TreeNode * node3 = create(1);
	TreeNode * node4 = create(6);
	
	root->lchild = node1;
	root->rchild = node2;
	node1->lchild = node3;
	node2->rchild = node4;
	preOrder(root);
	printf("\n");
	inOrder(root);
	free(root);
	free(node1);	
	free(node2);
	free(node3);
	free(node4);
	return 0;			
}
