#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode {
    int id;
    char name[31];
    int inheritance;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode* createNode(int id, const char* name, int inheritance) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->id = id;
    strncpy(node->name, name, 30);
    node->name[30] = '\0';
    node->inheritance = inheritance;
    node->left = node->right = NULL;
    return node;
}

TreeNode* insertNode(TreeNode* root, int id, const char* name, int inheritance) {
    if (root == NULL)
        return createNode(id, name, inheritance);
    if (id < root->id)
        root->left = insertNode(root->left, id, name, inheritance);
    else if (id > root->id)
        root->right = insertNode(root->right, id, name, inheritance);
    else
        printf("ID %d exists.\n", id);
    return root;
}

void inorder(TreeNode* root) {
    if (!root) return;
    inorder(root->left);
    printf("ID: %d, Name: %s, Inherit: %d\n", root->id, root->name, root->inheritance);
    inorder(root->right);
}

TreeNode* findNode(TreeNode* root, int id) {//pake id
    if (!root) return NULL;
    if (id == root->id) return root;
    if (id < root->id) return findNode(root->left, id);
    return findNode(root->right, id);
}

void distributeInheritance(TreeNode* node) {
    if (!node) return;
    int val = node->inheritance;
    node->inheritance = 0;
    if (node->left) {
        int shareL = val * 60 / 100;
        node->left->inheritance += shareL;
        distributeInheritance(node->left);
    }
    if (node->right) {
        int shareR = val * 40 / 100;
        node->right->inheritance += shareR;
        distributeInheritance(node->right);
    }
}

int main() {
    TreeNode* root = NULL;
    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Tambah anggota family\n");
        printf("2. Tampilkan pohon silsilah\n");
        printf("3. Simulasi bagi waris\n");
        printf("4. Keluar\n");
        printf("Pilih: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: {
                int id, inh;
                char name[31];
                printf("Masukkan ID anggota: ");
                scanf("%d", &id);
                printf("Masukkan Nama anggota: ");
                getchar(); 
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                printf("Masukkan Nilai warisan (juta): ");
                scanf("%d", &inh);
                root = insertNode(root, id, name, inh);
                break;
            }
            case 2:
                printf("\nPohon keluarga:\n");
                inorder(root);
                break;
            case 3: {
                int id;
                printf("Masukkan ID anggota yang meninggal: ");
                scanf("%d", &id);
                TreeNode* target = findNode(root, id);
                if (!target) {
                    printf("Anggota dengan ID %d tidak ditemukan.\n", id);
                } else {
                    distributeInheritance(target);
                    printf("Distribusi warisan dari ID %d selesai.\n", id);
                }
                break;
            }
            case 4:
                printf("Keluar program.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (choice != 4);
    return 0;
}
