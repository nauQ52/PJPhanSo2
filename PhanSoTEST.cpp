#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
//yeu em nhiu chut
// Định nghĩa cấu trúc phân số
typedef struct {
    int tuSo;   // Tử số
    int mauSo; // Mẫu số
} Fraction;

// Định nghĩa cấu trúc nút cây nhị phân
typedef struct Node {
    Fraction data;
    struct Node* left;
    struct Node* right;
} Node;

// Hàm tạo một nút mới với phân số cho trước
Node* createNode(Fraction value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Hàm chèn một phân số vào cây nhị phân
Node* insertNode(Node* root, Fraction value) {
    if (root == NULL) {
        root = createNode(value);
    }
    else if (value.tuSo * root->data.mauSo < root->data.tuSo * value.mauSo) {
        root->left = insertNode(root->left, value);
    }
    else {
        root->right = insertNode(root->right, value);
    }
    return root;
}

// Hàm duyệt cây theo thứ tự NLR
void traverseNLR(Node* root) {
    if (root != NULL) {
        printf("%d/%d ", root->data.tuSo, root->data.mauSo);
        traverseNLR(root->left);
        traverseNLR(root->right);
    }
}
// Ham duyet cay theo thu tu
//void traverse_NLR(Node* root) {
//    if (root == NULL)
//        return;
//    printf("%d/%d ", root->data.tuSo, root->data.mauSo);
//    traverse_NLR(root->left);
//    traverse_NLR(root->right);
//}
void traverseLNR(Node* root) {
    if (root == NULL)
        return;
    traverseLNR(root->left);
    printf("%d/%d ", root->data.tuSo, root->data.mauSo);
    traverseLNR(root->right);
}
void traverseLRN(Node* root) {
    if (root == NULL)
        return;
    traverseLRN(root->left);
    traverseLRN(root->right);
    printf("%d/%d ", root->data.tuSo, root->data.mauSo);
}
void traverseNRL(Node* root) {
    if (root == NULL)
        return;
    printf("%d/%d ", root->data.tuSo, root->data.mauSo);
    traverseNRL(root->right);
    traverseNRL(root->left);

}
void traverseRNL(Node* root) {
    if (root == NULL)
        return;
    traverseRNL(root->right);
    printf("%d/%d ", root->data.tuSo, root->data.mauSo);
    traverseRNL(root->left);
}
void traverseRLN(Node* root) {
    if (root == NULL)
        return;
    traverseRLN(root->right);
    traverseRLN(root->left);
    printf("%d/%d ", root->data.tuSo, root->data.mauSo);
}




// Hàm đếm số lượng phân số lớn hơn 1 trong cây
int demPhanSoLonHonMot(Node* root) {
    if (root == NULL) {
        return 0;
    }
    int count = demPhanSoLonHonMot(root->left) + demPhanSoLonHonMot(root->right);
    if ((float)root->data.tuSo / root->data.mauSo > 1) {
        count++;
    }
    return count;
}

// Hàm tối giản phân số
Fraction rutGonPhanSo(Fraction fraction) {
    int a = fraction.tuSo;
    int b = fraction.mauSo;
    int temp;
    while (b != 0) {
        temp = a % b;
        a = b;
        b = temp;
    }
    fraction.tuSo /= a;
    fraction.mauSo /= a;
    return fraction;
}

// Hàm tối giản tất cả các nút trong cây
void simplifyTree(Node* root) {
    if (root != NULL) {
        root->data = rutGonPhanSo(root->data);
        simplifyTree(root->left);
        simplifyTree(root->right);
    }
}

// Hàm kiểm tra xem cây có nút nào có giá trị bằng với phân số x hay không
int timPhanSo(Node* root, Fraction x) {
    if (root == NULL) {
        return 0;
    }
    if (root->data.tuSo * x.mauSo == x.tuSo * root->data.mauSo) {
        return 1;
    }
    return timPhanSo(root->left, x) || timPhanSo(root->right, x);
}

// Hàm hiển thị menu
void displayMenu() {
    printf("\n\t\t======================MENU==========================");
    printf("\n\t\t|       0. Thoat Chuong Trinh                      |");
    printf("\n\t\t|       1. Them mot nut vao cay                    |");
    printf("\n\t\t|       2. Duyet cay theo thu tu tu chon           |");
    printf("\n\t\t|       3. Dem so luong phan so lon hon 1          |");
    printf("\n\t\t|       4. Toi gian cac nut cua cay                |");
    printf("\n\t\t|       5. Kiem tra gia tri mot phan so trong cay  |");
    printf("\n\t\t====================================================");
    printf("\n\t\t        Lua chon cua ban: ");
}
void MenuCon() {
    printf("\n\t\t======================MENU==========================");
    printf("\n\t\t|       0. Thoat Chuong Trinh                      |");
    printf("\n\t\t|       1. Duyet cay theo thu tu NLR               |");
    printf("\n\t\t|       2. Duyet cay theo thu tu LNR               |");
    printf("\n\t\t|       3. Duyet cay theo thu tu LRN               |");
    printf("\n\t\t|       4. Duyet cay theo thu tu NRL               |");
    printf("\n\t\t|       5. Duyet cay theo thu tu RNL               |");
    printf("\n\t\t|       6. Duyet cay theo thu tu RLN               |");
    printf("\n\t\t====================================================");

}
void prinNgatDong() {
    printf("\n\t\t=====================================================");
}

int main() {
    Node* root = NULL; // Khởi tạo cây rỗng

    int choice;
    Fraction fraction;
    int result;


    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
        case 0:
            printf("Ket thuc chuong trinh.\n");
            break;
        case 1:
            printf("\n\t\t\tNhap tu so: ");
            scanf("%d", &fraction.tuSo);
            printf("\n\t\t\tNhap mau so: ");
            scanf("%d", &fraction.mauSo);
            root = insertNode(root, fraction);
            printf("\n\t\t\tDa them phan so %d/%d vao cay.\n", fraction.tuSo, fraction.mauSo);
            prinNgatDong();
            break;
        case 2:
            int chon2;
            MenuCon();
            printf("\n\t\tVui long chon chuc nang (0 -> 6): ");
            scanf("%d", &chon2);
            printf("\n");
            switch (chon2)
            {
            case 0:
                printf("\n\t\tThoat ra Menu Chinh.\n");
                prinNgatDong();
                break;
            case 1:
                printf("\n\t\t\tDuyet cay theo thu tu NLR: ");
                traverseNLR(root);
                printf("\n");
                prinNgatDong();
                break;
            case 2:
                printf("\n\t\t\tDuyet cay theo thu tu LNR: ");
                traverseLNR(root);
                printf("\n");
                prinNgatDong();
                break;
            case 3:
                printf("\n\t\t\tDuyet cay theo thu tu LRN: ");
                traverseLRN(root);
                printf("\n");
                prinNgatDong();
                break;
            case 4:
                printf("\n\t\t\tDuyet cay theo thu tu NRL: ");
                traverseNRL(root);
                printf("\n");
                prinNgatDong();
                break;
            case 5:
                printf("\n\t\t\tDuyet cay theo thu tu RNL: ");
                traverseRNL(root);
                printf("\n");
                prinNgatDong();
                break;
            case 6:
                printf("\n\t\t\tDuyet cay theo thu tu RLN: ");
                traverseRLN(root);
                printf("\n");
                prinNgatDong();
                break;
            default:
                printf("\nChuc nang khong phu hop. Vui long thu lai...\n");
                break;
            }
            break;
        case 3:
            result = demPhanSoLonHonMot(root);
            printf("\n\t\t\tSo luong phan so lon hon 1: %d\n", result);
            prinNgatDong();
            break;
        case 4:
            simplifyTree(root);
            printf("\n\t\t\tDa toi gian cac nut cua cay.\n");
            prinNgatDong();
            break;
        case 5:
            printf("\n\t\t\tNhap tu so: ");
            scanf("%d", &fraction.tuSo);
            printf("\n\t\t\tNhap mau so: ");
            scanf("%d", &fraction.mauSo);
            result = timPhanSo(root, fraction);
            if (result) {
                printf("\n\t\t\tPhan so %d/%d co gia tri trong cay.\n", fraction.tuSo, fraction.mauSo);
            }
            else {
                printf("\n\t\t\tPhan so %d/%d khong co gia tri trong cay.\n", fraction.tuSo, fraction.mauSo);
            }
            prinNgatDong();
            break;
        default:
            printf("\n\t\t\tLua chon khong hop le. Vui long chon lai.\n");
            prinNgatDong();
            break;
        }
    } while (choice != 0);

    return 0;
}

