#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

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
// Ham chen mot nut con vao nut cha
Node* insertChild(Node* root, Fraction parent, Fraction child, char position) {
    if (root == NULL) {
        printf("\n\t\tKhong tim thay nut cha.\n");
        return NULL;
    }
    if (root->data.tuSo == parent.tuSo && root->data.mauSo == parent.mauSo) {
        Node* childNode = createNode(child);
        if (position == 'L' || position == 'l') {
            root->left = childNode;
        }
        else if (position == 'R' || position == 'r') {
            root->right = childNode;
        }
        else {
            printf("\n\t\tVi tri khong hop le.\n");
        }
    }
    else {
        insertChild(root->left, parent, child, position);
        insertChild(root->right, parent, child, position);

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

Fraction addFractions(Fraction fraction1, Fraction fraction2) {
    Fraction sum;
    sum.tuSo = fraction1.tuSo * fraction2.mauSo + fraction2.tuSo * fraction1.mauSo;
    sum.mauSo = fraction1.mauSo * fraction2.mauSo;
    return rutGonPhanSo(sum);
}

Fraction findSmallestFraction(Node* root) {
    if (root->left == NULL) {
        return root->data;
    }
    return findSmallestFraction(root->left);
}
// Ham so nguyen to 
int isPrime(int number) {
    if (number < 2) {
        return 0;
    }
    for (int i = 2; i * i <= number; i++) {
        if (number % i == 0) {
            return 0;
        }
    }
    return 1;
}
// danh sách tu so mau so deu la so nguyen to
void listPrimeFractions(Node* root) {
    if (root != NULL) {
        if (isPrime(root->data.tuSo) && isPrime(root->data.mauSo)) {
            printf("%d/%d ", root->data.tuSo, root->data.mauSo);
        }
        listPrimeFractions(root->left);
        listPrimeFractions(root->right);
    }
}

// Hàm hiển thị menu
void displayMenu() {
    printf("\n\t\t======================MENU==========================");
    printf("\n\t\t|       0. Thoat Chuong Trinh                       |");
    printf("\n\t\t|       1. Them mot nut vao cay                     |");
    printf("\n\t\t|       2. Them mot nut con vao nut cha             |");
    printf("\n\t\t|       3. Duyet cay theo thu tu tu chon            |");
    printf("\n\t\t|       4. Dem so luong phan so lon hon 1           |");
    printf("\n\t\t|       5. Toi gian cac nut cua cay                 |");
    printf("\n\t\t|       6. Kiem tra gia tri mot phan so trong cay   |");
    printf("\n\t\t|       7. Tinh tong cac phan so                    |");
    printf("\n\t\t|       8. Tim phan so nho nhat                     |");
    printf("\n\t\t|       9. Liet ke PS co tu, mau so la so nguyen to |");
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
    Fraction fraction, parentFraction, childFraction;
    char position;
    int result;
    Fraction sum, smallestFraction;

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
            printf("\n\t\tNhap phan so cha:\n");
            printf("\n\t\tNhap tu so: ");
            scanf("%d", &parentFraction.tuSo);
            printf("\n\t\tNhap mau so: ");
            scanf("%d", &parentFraction.mauSo);
            printf("\n\t\tNhap phan so con:\n");
            printf("\n\t\tNhap tu so: ");
            scanf("%d", &childFraction.tuSo);
            printf("\n\t\tNhap mau so: ");
            scanf("%d", &childFraction.mauSo);
            printf("\n\t\tNhap vi tri (L/R): ");
            scanf(" %c", &position);
            root = insertChild(root, parentFraction, childFraction, position);
            prinNgatDong();
            break;
        case 3:
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
                prinNgatDong();
                break;
            }
            break;
        case 4:
            result = demPhanSoLonHonMot(root);
            printf("\n\t\t\tSo luong phan so lon hon 1: %d\n", result);
            prinNgatDong();
            break;
        case 5:
            simplifyTree(root);
            printf("\n\t\t\tDa toi gian cac nut cua cay.\n");
            prinNgatDong();
            break;
        case 6:
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
        case 7:
            sum.tuSo = 0;
            sum.mauSo = 1;
            sum = rutGonPhanSo(sum);
            printf("\n\t\tNhap so luong phan so: ");
            int n;
            scanf("%d", &n);
            for (int i = 0; i < n; i++) {
                printf("\n\t\tNhap phan so thu %d:\n", i + 1);
                printf("\n\t\tNhap tu so: ");
                scanf("%d", &fraction.tuSo);
                printf("\n\t\tNhap mau so: ");
                scanf("%d", &fraction.mauSo);
                sum = addFractions(sum, fraction);
            }
            printf("\n\t\tTong cac phan so: %d/%d\n", sum.tuSo, sum.mauSo);
            prinNgatDong();
            break;
        case 8:
            smallestFraction = findSmallestFraction(root);
            printf("\n\t\tPhan so nho nhat trong cay: %d/%d\n", smallestFraction.tuSo, smallestFraction.mauSo);
            prinNgatDong();
            break;
        case 9:
            printf("\n\t\tCac phan so co tu so, mau so la so nguyen to: ");
            listPrimeFractions(root);
            printf("\n");
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