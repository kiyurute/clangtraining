#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct node {
  struct node *left;
  struct node *right;
  int value;
} node_t;

void add_element(node_t*, int);
void printTree(node_t*, int);




int main(){
    node_t *root_node = (struct node*)malloc(sizeof(struct node));

    if(root_node->value == '\0'){
        printf("value is empty\n:%d",root_node->value);
    }

    add_element(root_node, 100);
    add_element(root_node, 200);
    add_element(root_node, 150);
    add_element(root_node, 300);
    add_element(root_node, 130);
    add_element(root_node, 30);
    add_element(root_node, 800);
    add_element(root_node, 40);


    printTree(root_node,0);



}

//要素の登録
void add_element(node_t *root_ref, int val){

    node_t *new_node = (struct node*)malloc(sizeof(struct node));

    new_node->value = val;

    node_t *node_address = root_ref;

    if(node_address->value == '\0'){
        root_ref->value = val;
        return;
    }


    while(1){
        printf("in while\n");
        if(node_address->value > val){
            if(node_address->left == NULL){
                break;
            }
            node_address = node_address->left;

        }else{
            if(node_address->right == NULL){
                break;
            }
            node_address = node_address->right;

        }

    }

    if(node_address->value > val){
        node_address->left = new_node;
    }else{
        node_address->right = new_node;
    }

    return;

}

//全ノード表示
void printTree(node_t *root, int depth){
  int i;

  if(root == NULL){
    return ;
  }

  /* 右の子孫ノードを表示 */
  printTree(root->right, depth+1);
 
  /* 深さをスペースで表現 */ 
  for(i = 0; i < depth; i++){
    printf("      ");
  }

  /* ノードのデータを表示 */
  printf("val:%d\n", root->value);

  /* 左の子孫ノードを表示 */
  printTree(root->left, depth+1);

  depth++;
}