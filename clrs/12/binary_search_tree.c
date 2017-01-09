#include <stdio.h>

typedef struct tree_t {
    struct tree_t *parent;
    struct tree_t *left;
    struct tree_t *right;
    int key;
} tree_t;

void
inorder_tree_walk(tree_t *tree)
{
    if (tree) {
        /* 中序 */
        inorder_tree_walk(tree->left);
        printf("%d ", tree->key);
        inorder_tree_walk(tree->right);
        /* 前序
        printf("%d ", tree->key);
        inorder_tree_walk(tree->left);
        inorder_tree_walk(tree->right);
           后序
        inorder_tree_walk(tree->left);
        inorder_tree_walk(tree->right);
        printf("%d ", tree->key);
         */
    }
}

/* 先向左逐个压入栈，之后向右子树遍历，在栈顶的是需要输出的 */
void
nonrecursive_inorder_tree_walk(tree_t *tree)
{
    tree_t *stack[1024];
    int top;

    top = -1;
    while (tree || top != -1) {
        while (tree) {
            stack[++top] = tree;
            tree = tree->left;
        }
        
        tree = stack[top--];
        printf("%d ", tree->key);
        tree = tree->right;
    }
}

/* Morris二叉树遍历
 * 使用叶结点的右指针指向之前的、需要下一个输出的结点，构成环
 * 非递归遍历需要保存搜索路径，使用栈保存了每一步的路径，使用指针，保存了已
 * 遍历完的子树的父节点
 */
void
morris_nonrecursive_inorder_tree_walk(tree_t *tree)
{
    tree_t *temp;

    while (tree) {
        if (tree->left == NULL) {
            printf("%d ", tree->key);
            tree = tree->right;
        } else {
            temp = tree->left;
            while (temp->right && temp->right != tree)
                temp = temp->right;

            if (!temp->right) {
                temp->right = tree;
                tree = tree->left;
            } else {
                printf("%d ", tree->key);
                temp->right = NULL;
                tree = tree->right;
            }
        }
    }
}

tree_t *
recursive_tree_search(tree_t *tree, int key)
{
    if (!tree || tree->key == key)
        return tree;

    if (tree->key < key)
        return recursive_tree_search(tree->left, key);
    else
        return recursive_tree_search(tree->right, key);
}

tree_t *
iterative_tree_search(tree_t *tree, int key)
{
    while (tree && tree->key != key)
        if (tree->key < key)
            tree = tree->left;
        else
            tree = tree->right;

    return tree;
}

tree_t *
tree_minimum(tree_t *tree)
{
    while (tree && tree->left != NULL)
        tree = tree->left;

    return tree;
}

tree_t *
tree_maximum(tree_t *tree)
{
    while (tree && tree->right != NULL)
        tree = tree->right;

    return tree;
}

tree_t *
recursive_tree_minimum(tree_t *tree)
{
    if (tree->left)
        return recursive_tree_minimum(tree->left);
    else
        return tree;
}

tree_t *
recursive_tree_maximum(tree_t *tree)
{
    if (tree->right)
        return recursive_tree_maximum(tree->right);
    else
        return tree;
}

tree_t *
tree_successor(tree_t *x)
{
    tree_t *y;

    if (x->right)
        return tree_minimum(x->right);
    
    /* 后继为第一个比目标结点大的祖先结点，也就是第一个左结点为祖先结点的祖先结点 */
    y = x->parent;
    while (y && x == y->right) {
        x = y;
        y = x->parent;
    }
    return y;
}

tree_t *
tree_predecessor(tree_t *x)
{
    tree_t *y;

    if (x->left)
        return tree_maximum(x->left);
    
    /* 同上，前驱为第一个比x小的祖先结点，也就是第一个右结点为祖先结点的祖先结点 */
    y = x->parent;
    while (y && x == y->left) {
        x = y;
        y = x->parent;
    }
    return y;
}

void
tree_insert(tree_t **tree, tree_t *key)
{
    tree_t *node;
    tree_t *parent;

    parent = NULL;
    node = *tree;
    while (node) {
        parent = node;
        if (key->key < node->key)
            node = node->left;
        else
            node = node->right;
    }

    key->parent = parent;
    if (!parent)
        *tree = key;
    else if (key->key < parent->key)
        parent->left = key;
    else
        parent->right = key;
}

/* 因为要保存父指针，所以需要检查当前结点的子节点 */
void
recursive_tree_insert(tree_t **tree, tree_t *key)
{
    /* 空树 */
    if (*tree == NULL)
        *tree = key;
    else if (!((*tree)->left) && (*tree)->key < key->key) {
        key->parent = tree;
        tree->left = key;
    } else if (!((*tree)->right) && (*tree)->key >= key->key) {
        key->parent = tree;
        tree->right = key;
    } else if ((*tree)->key < key->key)
        recursive_tree_insert(&(*tree)->left, key);
    else
        recursive_tree_insert(&(*tree)->right, key);
}

/* 没有父指针，找到空的就放置，用赋值来保存信息 */
tree_t *
recursive_tree_insert_without_parent(tree_t **tree, tree_t *key)
{
    if (!*tree)
        *tree = key;
    else if ((*tree)->key < key->key) 
        (*tree)->left = recursive_tree_insert(&(*tree)->left, key);
    else
        (*tree)->right = recursive_tree_insert(&(*tree)->right, key);

    return *tree;
}

void
transplant(tree_t **tree, tree_t *u, tree_t *v)
{
    if (!u->parent)
        *tree = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else 
        u->parent->right = v;

    if (!v)
        v->parent = u->parent;
}

void
tree_delete(tree_t **tree, tree_t *z)
{
    tree_t *successor;

    if (!z->left)
        transplant(tree, z, z->right);
    else if (!z->right)
        transplant(tree, z, z->left);
    else {
        successor = tree_successor(z);
        if (successor->parent != z) {
            transplant(tree, successor, successor->right);
            successor->right = z->right;
            successor->right->parent = successor;
        }

        transplant(tree, z, successor);
        successor->left = z->left;
        successor->left->parent = successor;
    }
}


