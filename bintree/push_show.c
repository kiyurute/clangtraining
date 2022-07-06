#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct node {
  struct node *left;
  struct node *right;
  int value;
} node_t;

void bt_insert(node_t**, int);
void printTree(node_t**, int);
void bt_search(node_t**, int);
void bt_drop(node_t**, node_t**, int);



int main(){
    node_t *root = (struct node*)malloc(sizeof(struct node));

    bt_insert(&root, 5);
    bt_insert(&root, 3);
    bt_insert(&root, 1);
    bt_insert(&root, 15);
    bt_insert(&root, 12);
    bt_insert(&root, 19);
    bt_insert(&root, 10);
    bt_insert(&root, 8);
    bt_insert(&root, 9);
    bt_insert(&root, 4);


    printTree(&root,0);

    bt_search(&root, 12);
    bt_search(&root,18);

    // node_t *pre = (struct node*)malloc(sizeof(struct node));
    // bt_drop(&root, &pre, 3);
    // printTree(&root,0);


}

//while文で要素の登録
void bt_insert_spare(node_t **root_ref, int val){

    node_t *new_node = (struct node*)malloc(sizeof(struct node));

    new_node->value = val;

    node_t *node_address = *root_ref;

    if(node_address->value == '\0'){
        node_address->value = val;
        return;
    }


    while(1){
        // printf("in while\n");
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

//再帰呼び出しでの要素の登録
void bt_insert(node_t **root_ref, int val){

    node_t *new_node = (struct node*)malloc(sizeof(struct node));
    new_node->value = val;

    node_t *node_address = *root_ref;

    if(node_address->value == '\0'){
        node_address->value = val;
        return;
    }


    if(node_address->value > val && node_address->left == NULL){
        node_address->left = new_node;
        return;
    }else if(node_address->value > val && node_address->left != NULL){
        bt_insert(&(node_address->left), val);
    }else{}

    if(node_address->value < val && node_address->right == NULL){
        node_address->right = new_node;
        return;
    }else if(node_address->value < val && node_address->right != NULL){
        bt_insert(&(node_address->right), val);
    }else{}

    
}


//全ノード表示
void printTree(node_t **root, int depth){

  int i;

  node_t *node_address = *root;

  if(node_address == NULL){
    return ;
  }

  /* 左の子孫ノードを表示 */
  printTree(&node_address->left, depth+1);
 
  /* 深さをスペースで表現 */ 
//   for(i = 0; i < depth; i++){
//     printf("      ");
//   }

  /* ノードのデータを表示 */
  printf("val:%d\n", node_address->value);

  /* 右の子孫ノードを表示 */
  printTree(&node_address->right, depth+1);

  depth++;
}

//検索する関数
void bt_search(node_t **root_ref, int val){
    
    node_t *node_address = *root_ref;

    if(node_address->value > val){
        if(node_address->left == NULL){
            printf("not found:%d\n", val);
            return;
        }
        bt_search(&(node_address->left), val);
    }else if(node_address->value < val){
        if(node_address->right == NULL){
            printf("not found:%d\n", val);
            return;
        }
        bt_search(&(node_address->right), val);
    }else{
        printf("find:%d\n",val);
        return;
    }


}


//削除する関数
void bt_drop(node_t **root_ref, node_t **pre_ref, int val){

   node_t *node_address = *root_ref;
   node_t *pre_address = *pre_ref;

    if(node_address->value == val){

        printf("find:%d\n",val);

        //削除対象が両ノードとも持っていた場合
        if(node_address->left != NULL && node_address->right != NULL){

            printf("have both nodes\n");
            printf("address:%p val:%d\n",node_address, node_address->value);
            printf("pre_address:%p val:%d\n",pre_address, pre_address->value);

            if(pre_address->value < val){
                pre_address->right = node_address->left;
            }else if(pre_address->value < val){
                pre_address->left = node_address->right;
            }else{}

        }

        //削除対象が左ノードのみ持っていた場合
        if(node_address->left != NULL && node_address->right == NULL){

            if(pre_address->value < val){
                pre_address->right = node_address->left;
            }else if(pre_address->value > val){
                pre_address->left = node_address->left;
            }else{}

        }

        //削除対象が右ノードのみ持っていた場合
        if(node_address->left == NULL && node_address->right != NULL){

            if(pre_address->value < val){
                pre_address->right = node_address->right;
            }else if(pre_address->value > val){
                pre_address->left = node_address->right;
            }else{}

        }

        //削除対象が末端だった場合
        if(node_address->left == NULL && node_address->right == NULL){

            if(pre_address->value < val){
                pre_address->right = NULL;
            }else if(pre_address->value > val){
                pre_address->left = NULL;
            }else{}
            
            
        } 

        return;


    }else if(node_address->value < val){

        if(node_address->right == NULL){
            printf("not found:%d\n", val);
            return;
        }
        pre_address = node_address;
        bt_drop(&(node_address->right), &pre_address, val);

    }else{

        if(node_address->left == NULL){
            printf("not found:%d\n", val);
            return;
        }
        pre_address = node_address;
        bt_drop(&(node_address->left), &pre_address, val);


    }

}