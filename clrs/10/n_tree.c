typedef struct tree_t {
    struct tree_t *child;
    struct tree_t *sibling;
    struct tree_t *parent;
    int key;
} tree_t;

void
print_n_tree(tree_t *tree)
{
    if (!tree)
        return;
    printf("%d ", tree->key);

    if (tree->child)
        print_n_tree(tree->child);
    if (tree->sibling)
        print_n_tree(tree->sibling);
}

