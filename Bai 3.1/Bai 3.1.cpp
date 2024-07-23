#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    char ten[50];
    char mssv[10];
    float dtb;
    char xeploai[20];
} SinhVien;

void nhapSinhVien(SinhVien* sv) {
    printf("Nhap ten sinh vien: ");
    getchar(); // Clear newline buffer
    fgets(sv->ten, sizeof(sv->ten), stdin);
    sv->ten[strcspn(sv->ten, "\n")] = '\0'; // Remove newline character

    printf("Nhap MSSV: ");
    fgets(sv->mssv, sizeof(sv->mssv), stdin);
    sv->mssv[strcspn(sv->mssv, "\n")] = '\0'; // Remove newline character

    printf("Nhap diem trung binh: ");
    scanf_s("%f", &sv->dtb);

    if (sv->dtb >= 8.0) {
        strcpy_s(sv->xeploai, sizeof(sv->xeploai), "Gioi");
    }
    else if (sv->dtb >= 6.5) {
        strcpy_s(sv->xeploai, sizeof(sv->xeploai), "Kha");
    }
    else if (sv->dtb >= 5.0) {
        strcpy_s(sv->xeploai, sizeof(sv->xeploai), "Trung binh");
    }
    else {
        strcpy_s(sv->xeploai, sizeof(sv->xeploai), "Yeu");
    }
}

void hienThiSinhVien(SinhVien sv) {
    printf("Ten: %s\n", sv.ten);
    printf("MSSV: %s\n", sv.mssv);
    printf("Diem trung binh: %.2f\n", sv.dtb);
    printf("Xep loai: %s\n", sv.xeploai);
}

void nhapDanhSachSinhVien(SinhVien ds[], int* n) {
    printf("Nhap so luong sinh vien: ");
    scanf_s("%d", n);
    for (int i = 0; i < *n; i++) {
        printf("\nNhap thong tin sinh vien thu %d:\n", i + 1);
        nhapSinhVien(&ds[i]);
    }
}

void hienThiDanhSachSinhVien(SinhVien ds[], int n) {
    for (int i = 0; i < n; i++) {
        printf("\nThong tin sinh vien thu %d:\n", i + 1);
        hienThiSinhVien(ds[i]);
    }
}

void interchangeSort(SinhVien ds[], int n) {
    SinhVien temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (ds[i].dtb > ds[j].dtb) {
                temp = ds[i];
                ds[i] = ds[j];
                ds[j] = temp;
            }
        }
    }
}

void selectionSort(SinhVien ds[], int n) {
    int minIdx;
    SinhVien temp;
    for (int i = 0; i < n - 1; i++) {
        minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (ds[j].dtb < ds[minIdx].dtb) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            temp = ds[i];
            ds[i] = ds[minIdx];
            ds[minIdx] = temp;
        }
    }
}

void quickSort(SinhVien ds[], int left, int right) {
    int i = left, j = right;
    float pivot = ds[(left + right) / 2].dtb;
    SinhVien temp;
    while (i <= j) {
        while (ds[i].dtb < pivot) i++;
        while (ds[j].dtb > pivot) j--;
        if (i <= j) {
            temp = ds[i];
            ds[i] = ds[j];
            ds[j] = temp;
            i++;
            j--;
        }
    }
    if (left < j) quickSort(ds, left, j);
    if (i < right) quickSort(ds, i, right);
}

void timSinhVienCaoNhatThapNhat(SinhVien ds[], int n) {
    if (n == 0) {
        printf("Danh sach sinh vien rong.\n");
        return;
    }
    SinhVien* maxSV = &ds[0];
    SinhVien* minSV = &ds[0];
    for (int i = 1; i < n; i++) {
        if (ds[i].dtb > maxSV->dtb) {
            maxSV = &ds[i];
        }
        if (ds[i].dtb < minSV->dtb) {
            minSV = &ds[i];
        }
    }
    printf("\nSinh vien co diem trung binh cao nhat:\n");
    hienThiSinhVien(*maxSV);
    printf("\nSinh vien co diem trung binh thap nhat:\n");
    hienThiSinhVien(*minSV);
}

void inSinhVienGioiKha(SinhVien ds[], int n) {
    printf("\nDanh sach sinh vien xep loai Gioi va Kha:\n");
    for (int i = 0; i < n; i++) {
        if (strcmp(ds[i].xeploai, "Gioi") == 0 || strcmp(ds[i].xeploai, "Kha") == 0) {
            hienThiSinhVien(ds[i]);
        }
    }
}

int demSinhVienHoNguyen(SinhVien ds[], int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (strncmp(ds[i].ten, "Nguyen", 6) == 0) {
            count++;
        }
    }
    return count;
}

void menu() {
    printf("Chuong trinh quan ly sinh vien\n");
    printf("1. Nhap danh sach sinh vien\n");
    printf("2. Hien thi danh sach sinh vien\n");
    printf("3. Sap xep danh sach sinh vien tang dan theo diem trung binh (InterchangeSort)\n");
    printf("4. Sap xep danh sach sinh vien tang dan theo diem trung binh (SelectionSort)\n");
    printf("5. Sap xep danh sach sinh vien tang dan theo diem trung binh (QuickSort)\n");
    printf("6. Tim sinh vien co diem trung binh cao nhat va thap nhat\n");
    printf("7. In danh sach sinh vien xep loai Gioi va Kha\n");
    printf("8. Dem so luong sinh vien co ho 'Nguyen'\n");
    printf("9. Thoat\n");
}

int main() {
    SinhVien ds[MAX];
    int n = 0;
    int luaChon;

    do {
        menu();
        printf("Nhap lua chon: ");
        scanf_s("%d", &luaChon);

        switch (luaChon) {
        case 1:
            nhapDanhSachSinhVien(ds, &n);
            break;
        case 2:
            hienThiDanhSachSinhVien(ds, n);
            break;
        case 3:
            interchangeSort(ds, n);
            printf("Danh sach sinh vien sau khi sap xep tang dan theo diem trung binh (InterchangeSort):\n");
            hienThiDanhSachSinhVien(ds, n);
            break;
        case 4:
            selectionSort(ds, n);
            printf("Danh sach sinh vien sau khi sap xep tang dan theo diem trung binh (SelectionSort):\n");
            hienThiDanhSachSinhVien(ds, n);
            break;
        case 5:
            quickSort(ds, 0, n - 1);
            printf("Danh sach sinh vien sau khi sap xep tang dan theo diem trung binh (QuickSort):\n");
            hienThiDanhSachSinhVien(ds, n);
            break;
        case 6:
            timSinhVienCaoNhatThapNhat(ds, n);
            break;
        case 7:
            inSinhVienGioiKha(ds, n);
            break;
        case 8:
            printf("So luong sinh vien co ho 'Nguyen': %d\n", demSinhVienHoNguyen(ds, n));
            break;
        case 9:
            printf("Thoat chuong trinh.\n");
            break;
        default:
            printf("Lua chon khong hop le. Vui long chon lai.\n");
        }
    } while (luaChon != 9);

    return 0;
}
