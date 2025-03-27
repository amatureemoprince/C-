//定义AVL节点
typedef struct AVL_TREE {
    int data;
    int height;
    struct AVL_TREE *left;
    struct AVL_TREE *right;
}AVL_TREE_NODE;

//定义右旋操作
void LL(AVL_TREE_NODE *root) {
    if (!root) {
        return ;
    }
    //右旋操作
    //传入的root，将new_root替代root，new_root->right替代root->left，root替代new_root->right则可
    AVL_TREE_NODE *new_root = root->left;
    AVL_TREE_NODE *temp;
    temp = new_root->right;
    new_root->right = root;
}
//定义左旋操作
void RR(AVL_TREE_NODE *root) {

}
//定义左右旋操作
void LR(AVL_TREE_NODE *root) {

}
//定义右左旋操作
void RL(AVL_TREE_NODE *root) {

}
//初始化一颗AVL树
AVL_TREE_NODE *init_avl_tree(){

}