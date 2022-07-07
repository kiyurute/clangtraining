#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
  struct node *left;
  struct node *right;
  int value;
} node_t;

void bt_insert(node_t**, int);
void printTree(node_t*, int);
int bt_search(node_t**, int);
void bt_drop(node_t**, node_t**, int);
int bt_set_empty(node_t**, node_t**, int);


int find_mx_num = -1;
node_t* find_mx_address;

node_t *root = NULL;

int main(){

    // node_t *root = (struct node*)malloc(sizeof(struct node));

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
    bt_insert(&root, 0);

    bt_insert(&root, 30);
    bt_insert(&root, 25);
    bt_insert(&root, 35);
    bt_insert(&root, 22);
    bt_insert(&root, 27);
    bt_insert(&root, 37);


    printTree(root,0);
    printf("print fin\n");

    bt_search(&root, 5);
    bt_search(&root,25);

    node_t *pre = (struct node*)malloc(sizeof(struct node));
    find_mx_num = -1;
    bt_drop(&root, &pre, 30);
    printTree(root, 0);
    // bt_insert(&root, 30);
    // printTree(root, 0);


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

    node_t *node_address = *root_ref;

    //rootのノードが無かった時
    if(node_address == NULL){
        node_t *new_node = (struct node*)malloc(sizeof(struct node));
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->value = val;
        *root_ref = new_node;
        return; 
    }

    //追加する値が対象ノードの値より小さく、左ノードがない時は左に追加
    if(node_address->value > val && node_address->left == NULL){
        node_t *new_node = (struct node*)malloc(sizeof(struct node));
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->value = val;
        node_address->left = new_node;
        return;
    //左ノードがあった場合はさらに下へ
    }else if(node_address->value > val && node_address->left != NULL){
        bt_insert(&(node_address->left), val);
    }else{}

    //追加する値が対象ノードの値より大きく、右ノードがない時は右に追加
    if(node_address->value < val && node_address->right == NULL){
        node_t *new_node = (struct node*)malloc(sizeof(struct node));
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->value = val;
        node_address->right = new_node;
        return;
    //右ノードがあった場合はさらに下へ
    }else if(node_address->value < val && node_address->right != NULL){
        bt_insert(&(node_address->right), val);
    }else{}
    
}


//全ノード表示
void printTree(node_t *root, int depth){

  int i;

  node_t *node_address = root;

  if(node_address == NULL){
    return ;
  }

  /* 左の子孫ノードを表示 */
  printTree(node_address->left, depth+1);
 
  /* 深さをスペースで表現 */ 
//   for(i = 0; i < depth; i++){
//     printf("      ");
//   }

  /* ノードのデータを表示 */
  printf("val:%d address:%p\n", node_address->value, node_address);

  /* 右の子孫ノードを表示 */
  printTree(node_address->right, depth+1);

  depth++;
}

//値を検索する関数
int bt_search(node_t **root_ref, int val){
    
    node_t *node_address = *root_ref;

    if(node_address->value > val){
        if(node_address->left == NULL){
            printf("not found:%d\n", val);
            return -1;
        }
        bt_search(&(node_address->left), val);
    }else if(node_address->value < val){
        if(node_address->right == NULL){
            printf("not found:%d\n", val);
            return -1;
        }
        bt_search(&(node_address->right), val);
    }else if(node_address->value == val){
        printf("find:%d address:%p\n",val,node_address);
        if(val > find_mx_num){
            find_mx_num = val;
            find_mx_address = node_address;
        }
        return find_mx_num;
    }else{}

    return -1;

}


//削除する関数
void bt_drop(node_t **root_ref, node_t **pre_ref, int val){

   node_t *node_address = *root_ref;
   node_t *pre_address = *pre_ref;

    if(node_address->value == val){

        //削除対象が両ノードとも持っていた場合
        if(node_address->left != NULL && node_address->right != NULL){

            printf("have both nodes\n");
            printf("address:%p val:%d\n",node_address, node_address->value);
            printf("pre_address:%p val:%d\n",pre_address, pre_address->value);

            //削除対象以下の左側の最大の値を探す
            int max_val = -1;
            int search_val = node_address->value - 1;
            while(max_val < 0){
                max_val = bt_search(&(node_address->left),search_val);
                search_val -= 1;
            }

            printf("max_val:%d max_address:%p\n", find_mx_num,find_mx_address);

            bt_set_empty(&node_address,&pre_address,find_mx_num);

            node_address->value = find_mx_num;

            return;

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

//指定された値を右に持つノードをさがし、右のノードをnullにする関数
int bt_set_empty(node_t **root_ref, node_t **pre_ref, int val){
    
    node_t *node_address = *root_ref;
    node_t *pre_address = *pre_ref;

    printf("bt_set_empty:%p val:%d\n",node_address, node_address->value);
    printf("val:%d\n",val);

    if(node_address->value > val){
        if(node_address->left == NULL){
            printf("not found:%d\n", val);
            return -1;
        }
        bt_set_empty(&(node_address->left), &node_address, val);
    }else if(node_address->value < val){
        if(node_address->right == NULL){
            printf("not found:%d\n", val);
            return -1;
        }
        bt_set_empty(&(node_address->right), &node_address, val);

    }else if(node_address->value == val){
        printf("pre_address:%p\n", pre_address);
        pre_address->right = NULL;
        return -1;
    }else{}

    return -1;

}