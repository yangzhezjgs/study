#include <stdio.h>

typedef struct tree_t {
    tree_t *left;
    tree_t *right;
    tree_t *parent;
    int key;
} tree_t;

void
print_tree(tree_t *tree)
{
    if (tree == NULL)
        return;

    printf("%d ", tree->key);
    if (tree->left)
        print_tree(tree->left);
    if (tree->right)
        print_tree(tree->right);
}

void
nonrecursive_print_tree_with_stack(tree_t *tree)
{
    tree_t *buf[1024];
    int count;
    tree_t *branch;

    buf[0] = tree;
    count = 0;
    while (count >= 0) {
        branch = buf[count];
        printf("%d ", branch->key);
        if (branch->right)
            buf[count] = branch->right;
        if (branch->left)
            buf[++count] = branch->left;
    }
}

/* 需要使用prev来保留遍历路线，路线不同，操作不同，有4种情况。
 * prev是tree的parent： 继续向左下遍历，如果tree没有子节点，则向右或向父结点移动
 * prev是tree的左子结点： 向右移动
 * prev是tree的右子结点或者prev是tree的兄弟结点： 向父结点移动
 */
void
nonrecursive_print_tree(tree_t *tree)
{
    tree_t *prev;

    prev = NULL;
    while (tree) {
        if (prev == tree->parent) {
            tree_t *parent;

            parent = prev;
            printf("%d\n", tree->key);
            prev = tree;
            tree = tree->left ? tree->left :
                   tree->right ? tree->right :
                   parent->right ? parent->right :
                   parent;
        } else if (prev == tree->left && tree->right) {
            prev = tree;
            tree = tree->right;
        } else {
            prev = tree;
            tree = tree->parent;
        }
    }
}


