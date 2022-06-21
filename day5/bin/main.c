// リンクリストの構造は

typedef struct node {
  int key;
  int value;
  struct node *next;
} node_t;

typedef struct linked_list {
  node_t *front;
} linked_list_t;


// 作成するリンクリストの操作関数は、

/* リンクリストの一番最後に追加 */
int push_back(linked_list_t *linked_list, int key, int value);
/* リンクリストの一番先頭に追加 */
int push_front(linked_list_t *linked_list, int key, int value);
/* リンクリストの一番後ろを削除 */
void pop_back(linked_list_t *linked_list);
/* リンクリストの一番先頭を削除 */
void pop_front(linked_list_t *linked_list);
/* リンクリストに、keyでソートされた位置（昇順）に追加 */
int sorted_insert(linked_list_t *linked_list, int key, int value);
/* リンクリストのすべての要素を出力 */
void show(const linked_list_t *linked_list);
/* リンクリストの要素をすべて解放 */
void clear(linked_list_t *linked_list);

// です。
// リンクリストの追加はmallocやcallocを用いてheapにメモリを確保し、リンクリストに連結してください。
// リンクリストからの削除は、freeを用いて確保したメモリを適切に解放してください。

// リンクリストの操作はmain関数で行い、追加したり削除するのはハードコーディングで構いません。



int main(void)
{
  linked_list_t linked_list = { 'NULL' };

  push_back(&linked_list, 3, 4);
  show(&linked_list);
  push_back(&linked_list, 2, 10);
  show(&linked_list);
  push_back(&linked_list, 5, 20);
  show(&linked_list);
  push_back(&linked_list, 1, 0);
  show(&linked_list);
  push_back(&linked_list, -1, -100);
  show(&linked_list);

  pop_front(&linked_list);
  show(&linked_list);
  pop_front(&linked_list);
  show(&linked_list);
  pop_front(&linked_list);
  show(&linked_list);
  pop_front(&linked_list);
  show(&linked_list);
  pop_front(&linked_list);
  show(&linked_list);

  clear(&linked_list);

  push_front(&linked_list, 30, 12);
  show(&linked_list);
  push_front(&linked_list, 100, 120);
  show(&linked_list);
  push_front(&linked_list, 3, 2);
  show(&linked_list);
  push_front(&linked_list, -100, 1000);
  show(&linked_list);

  pop_back(&linked_list);
  show(&linked_list);
  pop_back(&linked_list);
  show(&linked_list);
  pop_back(&linked_list);
  show(&linked_list);
  pop_back(&linked_list);
  show(&linked_list);
  pop_back(&linked_list);
  show(&linked_list);

  clear(&linked_list);

  sorted_insert(&linked_list, 1, 1);
  show(&linked_list);
  sorted_insert(&linked_list, 2, 2);
  show(&linked_list);
  sorted_insert(&linked_list, 3, 3);
  show(&linked_list);
  sorted_insert(&linked_list, 4, 4);
  show(&linked_list);
  sorted_insert(&linked_list, 4, -4);
  show(&linked_list);
  sorted_insert(&linked_list, 1, -1);
  show(&linked_list);
  sorted_insert(&linked_list, 2, -2);
  show(&linked_list);

  clear(&linked_list);

  sorted_insert(&linked_list, 99, 199);
  sorted_insert(&linked_list, 32, -32);
  sorted_insert(&linked_list, 1000, 10);
  sorted_insert(&linked_list, 2, 22);
  sorted_insert(&linked_list, 50, 0);
  sorted_insert(&linked_list, 23, 100);
  sorted_insert(&linked_list, 490, 99);
  show(&linked_list);

  return 0;
}