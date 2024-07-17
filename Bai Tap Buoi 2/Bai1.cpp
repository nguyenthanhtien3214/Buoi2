#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Định nghĩa kích thước mảng là một hằng số
#define SIZE 15

// Ham tao mang mot chieu ngau nhien co so phan tu lon hon hoac bang 15
void taoMangNgauNhien(int mang[], int n, int min, int max) {
    for (int i = 0; i < n; i++) {
        mang[i] = min + rand() % (max - min + 1);
    }
}

// Ham tao mang chua toan so chan
void taoMangSoChan(int mang[], int n) {
    for (int i = 0; i < n; i++) {
        mang[i] = 2 * (rand() % 50); // Tao so chan ngau nhien tu 0 den 98
    }
}

// Ham tim kiem tuyen tinh
int timKiemTuyenTinh(int mang[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (mang[i] == x) {
            return i;
        }
    }
    return -1;
}

// Ham sap xep tang dan theo giai thuat Interchange Sort
void interchangeSortTangDan(int mang[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (mang[i] > mang[j]) {
                int temp = mang[i];
                mang[i] = mang[j];
                mang[j] = temp;
            }
        }
    }
}

// Ham sap xep giam dan theo giai thuat Interchange Sort
void interchangeSortGiamDan(int mang[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (mang[i] < mang[j]) {
                int temp = mang[i];
                mang[i] = mang[j];
                mang[j] = temp;
            }
        }
    }
}

// Ham tim kiem nhi phan (yeu cau mang da duoc sap xep tang dan)
int timKiemNhiPhan(int mang[], int n, int x) {
    int trai = 0, phai = n - 1;
    while (trai <= phai) {
        int giua = (trai + phai) / 2;
        if (mang[giua] == x) {
            return giua;
        }
        else if (mang[giua] < x) {
            trai = giua + 1;
        }
        else {
            phai = giua - 1;
        }
    }
    return -1;
}

// Ham sap xep tang dan theo giai thuat Selection Sort
void selectionSort(int mang[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (mang[j] < min_idx) {
                min_idx = j;
            }
        }
        int temp = mang[min_idx];
        mang[min_idx] = mang[i];
        mang[i] = temp;
    }
}

// Ham sap xep tang dan theo giai thuat Quick Sort
void quickSort(int mang[], int trai, int phai) {
    int i = trai, j = phai;
    int pivot = mang[(trai + phai) / 2];

    while (i <= j) {
        while (mang[i] < pivot) {
            i++;
        }
        while (mang[j] > pivot) {
            j--;
        }
        if (i <= j) {
            int temp = mang[i];
            mang[i] = mang[j];
            mang[j] = temp;
            i++;
            j--;
        }
    }

    if (trai < j) {
        quickSort(mang, trai, j);
    }
    if (i < phai) {
        quickSort(mang, i, phai);
    }
}

// Ham in mang
void inMang(int mang[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", mang[i]);
    }
    printf("\n");
}

int main() {
    srand((unsigned int)time(0));

    int mang[SIZE];

    // 1. Tao mang mot chieu ngau nhien
    taoMangNgauNhien(mang, SIZE, 0, 100);
    printf("Mang ngau nhien: ");
    inMang(mang, SIZE);

    // 2. Tao mang chua toan so chan
    taoMangSoChan(mang, SIZE);
    printf("Mang chua toan so chan: ");
    inMang(mang, SIZE);

    // 3. Tim kiem tuyen tinh
    int x = 4;
    int vi_tri = timKiemTuyenTinh(mang, SIZE, x);
    if (vi_tri != -1) {
        printf("Phan tu %d tim thay tai vi tri %d\n", x, vi_tri);
    }
    else {
        printf("Phan tu %d khong tim thay\n", x);
    }

    // 4. Sap xep tang dan theo Interchange Sort
    interchangeSortTangDan(mang, SIZE);
    printf("Mang sau khi sap xep tang dan (Interchange Sort): ");
    inMang(mang, SIZE);

    // Sap xep giam dan theo Interchange Sort
    interchangeSortGiamDan(mang, SIZE);
    printf("Mang sau khi sap xep giam dan (Interchange Sort): ");
    inMang(mang, SIZE);

    // 5. Tim kiem nhi phan
    interchangeSortTangDan(mang, SIZE); // Dam bao mang da duoc sap xep tang dan
    vi_tri = timKiemNhiPhan(mang, SIZE, x);
    if (vi_tri != -1) {
        printf("Phan tu %d tim thay tai vi tri %d (Binary Search)\n", x, vi_tri);
    }
    else {
        printf("Phan tu %d khong tim thay (Binary Search)\n", x);
    }

    // 6. Sap xep tang dan theo Selection Sort
    selectionSort(mang, SIZE);
    printf("Mang sau khi sap xep tang dan (Selection Sort): ");
    inMang(mang, SIZE);

    // 7. Sap xep tang dan theo Quick Sort
    quickSort(mang, 0, SIZE - 1);
    printf("Mang sau khi sap xep tang dan (Quick Sort): ");
    inMang(mang, SIZE);

    return 0;
}
