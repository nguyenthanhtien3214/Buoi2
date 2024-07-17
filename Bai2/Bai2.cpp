#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Định nghĩa cấu trúc cho hỗn số
typedef struct {
    int phan_nguyen;
    int tu_so;
    int mau_so;
} HonSo;

// Định nghĩa kích thước mảng là một hằng số
#define SIZE 15

// Hàm tạo mảng chứa hỗn số ngẫu nhiên
void taoMangHonSo(HonSo b[], int n) {
    for (int i = 0; i < n; i++) {
        b[i].phan_nguyen = rand() % 10; // Phần nguyên từ 0 đến 9
        b[i].tu_so = rand() % 10; // Tử số từ 0 đến 9
        do {
            b[i].mau_so = rand() % 10;
        } while (b[i].mau_so == 0); // Mẫu số khác 0
    }
}

// Hàm xuất danh sách hỗn số
void xuatDanhSachHonSo(HonSo b[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d %d/%d\n", b[i].phan_nguyen, b[i].tu_so, b[i].mau_so);
    }
}

// Hàm so sánh hai hỗn số
int soSanhHonSo(HonSo hs1, HonSo hs2) {
    int tu1 = hs1.phan_nguyen * hs1.mau_so + hs1.tu_so;
    int tu2 = hs2.phan_nguyen * hs2.mau_so + hs2.tu_so;
    int mau1 = hs1.mau_so;
    int mau2 = hs2.mau_so;

    if (tu1 * mau2 > tu2 * mau1) {
        return 1;
    }
    else if (tu1 * mau2 < tu2 * mau1) {
        return -1;
    }
    else {
        return 0;
    }
}

// Hàm chuyển hỗn số thành phân số
void chuyenHonSoThanhPhanSo(HonSo hs, int* tu_so, int* mau_so) {
    *tu_so = hs.phan_nguyen * hs.mau_so + hs.tu_so;
    *mau_so = hs.mau_so;
}

// Hàm chuyển phân số thành hỗn số
HonSo chuyenPhanSoThanhHonSo(int tu_so, int mau_so) {
    HonSo hs;
    hs.phan_nguyen = tu_so / mau_so;
    hs.tu_so = tu_so % mau_so;
    hs.mau_so = mau_so;
    return hs;
}

// Hàm tính tổng hai hỗn số
HonSo tongHonSo(HonSo hs1, HonSo hs2) {
    int tu1, mau1, tu2, mau2;
    chuyenHonSoThanhPhanSo(hs1, &tu1, &mau1);
    chuyenHonSoThanhPhanSo(hs2, &tu2, &mau2);

    int tu_kq = tu1 * mau2 + tu2 * mau1;
    int mau_kq = mau1 * mau2;

    return chuyenPhanSoThanhHonSo(tu_kq, mau_kq);
}

// Hàm tính hiệu hai hỗn số
HonSo hieuHonSo(HonSo hs1, HonSo hs2) {
    int tu1, mau1, tu2, mau2;
    chuyenHonSoThanhPhanSo(hs1, &tu1, &mau1);
    chuyenHonSoThanhPhanSo(hs2, &tu2, &mau2);

    int tu_kq = tu1 * mau2 - tu2 * mau1;
    int mau_kq = mau1 * mau2;

    return chuyenPhanSoThanhHonSo(tu_kq, mau_kq);
}

// Hàm tính tích hai hỗn số
HonSo tichHonSo(HonSo hs1, HonSo hs2) {
    int tu1, mau1, tu2, mau2;
    chuyenHonSoThanhPhanSo(hs1, &tu1, &mau1);
    chuyenHonSoThanhPhanSo(hs2, &tu2, &mau2);

    int tu_kq = tu1 * tu2;
    int mau_kq = mau1 * mau2;

    return chuyenPhanSoThanhHonSo(tu_kq, mau_kq);
}

// Hàm tính thương hai hỗn số
HonSo thuongHonSo(HonSo hs1, HonSo hs2) {
    int tu1, mau1, tu2, mau2;
    chuyenHonSoThanhPhanSo(hs1, &tu1, &mau1);
    chuyenHonSoThanhPhanSo(hs2, &tu2, &mau2);

    int tu_kq = tu1 * mau2;
    int mau_kq = mau1 * tu2;

    return chuyenPhanSoThanhHonSo(tu_kq, mau_kq);
}

// Hàm sắp xếp tăng/giảm theo Interchange Sort
void interchangeSortHonSo(HonSo b[], int n, int tang_dan) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (tang_dan ? soSanhHonSo(b[i], b[j]) > 0 : soSanhHonSo(b[i], b[j]) < 0) {
                HonSo temp = b[i];
                b[i] = b[j];
                b[j] = temp;
            }
        }
    }
}

// Hàm sắp xếp tăng/giảm theo Selection Sort
void selectionSortHonSo(HonSo b[], int n, int tang_dan) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (tang_dan ? soSanhHonSo(b[j], b[min_idx]) < 0 : soSanhHonSo(b[j], b[min_idx]) > 0) {
                min_idx = j;
            }
        }
        HonSo temp = b[min_idx];
        b[min_idx] = b[i];
        b[i] = temp;
    }
}

// Hàm sắp xếp tăng/giảm theo Quick Sort
void quickSortHonSo(HonSo b[], int trai, int phai, int tang_dan) {
    int i = trai, j = phai;
    HonSo pivot = b[(trai + phai) / 2];

    while (i <= j) {
        while (tang_dan ? soSanhHonSo(b[i], pivot) < 0 : soSanhHonSo(b[i], pivot) > 0) {
            i++;
        }
        while (tang_dan ? soSanhHonSo(b[j], pivot) > 0 : soSanhHonSo(b[j], pivot) < 0) {
            j--;
        }
        if (i <= j) {
            HonSo temp = b[i];
            b[i] = b[j];
            b[j] = temp;
            i++;
            j--;
        }
    }

    if (trai < j) {
        quickSortHonSo(b, trai, j, tang_dan);
    }
    if (i < phai) {
        quickSortHonSo(b, i, phai, tang_dan);
    }
}

// Hàm main
int main() {
    srand((unsigned int)time(0));

    HonSo b[SIZE];

    // 1. Tạo mảng b chứa giá trị hỗn số ngẫu nhiên
    taoMangHonSo(b, SIZE);
    printf("Danh sach hon so ngau nhien:\n");
    xuatDanhSachHonSo(b, SIZE);

    // 2. Xuất danh sách hỗn số
    printf("Danh sach hon so:\n");
    xuatDanhSachHonSo(b, SIZE);

    // 3. So sánh hai hỗn số
    HonSo hs1 = b[0];
    HonSo hs2 = b[1];
    int ketQuaSoSanh = soSanhHonSo(hs1, hs2);
    if (ketQuaSoSanh > 0) {
        printf("Hon so 1 lon hon hon so 2\n");
    }
    else if (ketQuaSoSanh < 0) {
        printf("Hon so mot nho hon hon so 2\n");
    }
    else {
        printf("Hon so 1 bang hon so 2\n");
    }

    // 4. Chuyển hỗn số thành phân số
    int tu_so, mau_so;
    chuyenHonSoThanhPhanSo(hs1, &tu_so, &mau_so);
    printf("Hon so 1 thanh phan so: %d/%d\n", tu_so, mau_so);

    // 5. Chuyển phân số thành hỗn số
    HonSo hs_moi = chuyenPhanSoThanhHonSo(tu_so, mau_so);
    printf("Phan so thanh hon so: %d %d/%d\n", hs_moi.phan_nguyen, hs_moi.tu_so, hs_moi.mau_so);

    // 6. Tính tổng, hiệu, tích, thương hai hỗn số
    HonSo tong = tongHonSo(hs1, hs2);
    HonSo hieu = hieuHonSo(hs1, hs2);
    HonSo tich = tichHonSo(hs1, hs2);
    HonSo thuong = thuongHonSo(hs1, hs2);

    printf("Tong: %d %d/%d\n", tong.phan_nguyen, tong.tu_so, tong.mau_so);
    printf("Hieu: %d %d/%d\n", hieu.phan_nguyen, hieu.tu_so, hieu.mau_so);
    printf("Tich: %d %d/%d\n", tich.phan_nguyen, tich.tu_so, tich.mau_so);
    printf("Thuong: %d %d/%d\n", thuong.phan_nguyen, thuong.tu_so, thuong.mau_so);

    // 7. Sắp xếp b tăng/giảm theo 3 giải thuật sắp xếp 
    // Interchange Sort
    interchangeSortHonSo(b, SIZE, 1); // Tăng dần
    printf("Mang sau khi sap xep tang dan (Interchange Sort):\n");
    xuatDanhSachHonSo(b, SIZE);

    interchangeSortHonSo(b, SIZE, 0); // Giảm dần
    printf("Mang sau khi sap xep giam dan (Interchange Sort):\n");
    xuatDanhSachHonSo(b, SIZE);

    // Selection Sort
    selectionSortHonSo(b, SIZE, 1); // Tăng dần
    printf("Mang sau khi sap xep tang dan (Selection Sort):\n");
    xuatDanhSachHonSo(b, SIZE);

    selectionSortHonSo(b, SIZE, 0); // Giảm dần
    printf("Mang sau khi sap xep giam dan (Selection Sort):\n");
    xuatDanhSachHonSo(b, SIZE);

    // Quick Sort
    quickSortHonSo(b, 0, SIZE - 1, 1); // Tăng dần
    printf("Mang sau khi sap xep tang dan (Quick Sort):\n");
    xuatDanhSachHonSo(b, SIZE);

    quickSortHonSo(b, 0, SIZE - 1, 0); // Giảm dần
    printf("Mang sau khi sap xep giam dan (Quick Sort):\n");
    xuatDanhSachHonSo(b, SIZE);

    return 0;
}
