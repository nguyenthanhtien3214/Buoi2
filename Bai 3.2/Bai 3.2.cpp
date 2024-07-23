#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char ten[50];
    char mssv[10];
    float dtb;
    char xeploai[20];
} SinhVien;

typedef struct {
    char tenLop[50];
    int siSo;
    SinhVien danhSachSV[MAX];
} LopHoc;

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

void taoFileLopHoc() {
    FILE* file;
    fopen_s(&file, "dslop.txt", "w");
    if (!file) {
        printf("Khong the mo file de ghi.\n");
        return;
    }

    int n;
    printf("Nhap so luong lop hoc: ");
    scanf_s("%d", &n);
    fprintf(file, "%d\n", n);

    for (int i = 0; i < n; i++) {
        LopHoc lop;
        printf("Nhap ten lop: ");
        getchar(); // clear buffer
        fgets(lop.tenLop, sizeof(lop.tenLop), stdin);
        lop.tenLop[strcspn(lop.tenLop, "\n")] = '\0'; // remove newline

        printf("Nhap si so: ");
        scanf_s("%d", &lop.siSo);
        fprintf(file, "%s\n%d\n", lop.tenLop, lop.siSo);

        for (int j = 0; j < lop.siSo; j++) {
            printf("Nhap thong tin sinh vien thu %d:\n", j + 1);
            nhapSinhVien(&lop.danhSachSV[j]);
            fprintf(file, "%s\n%s\n%f\n%s\n",
                lop.danhSachSV[j].ten,
                lop.danhSachSV[j].mssv,
                lop.danhSachSV[j].dtb,
                lop.danhSachSV[j].xeploai);
        }
    }

    fclose(file);
}

void docFileLopHoc(LopHoc dsLop[], int* soLop) {
    FILE* file;
    fopen_s(&file, "dslop.txt", "r");
    if (!file) {
        printf("Khong the mo file de doc.\n");
        return;
    }

    fscanf_s(file, "%d\n", soLop);
    for (int i = 0; i < *soLop; i++) {
        fgets(dsLop[i].tenLop, sizeof(dsLop[i].tenLop), file);
        dsLop[i].tenLop[strcspn(dsLop[i].tenLop, "\n")] = '\0'; // remove newline

        fscanf_s(file, "%d\n", &dsLop[i].siSo);
        for (int j = 0; j < dsLop[i].siSo; j++) {
            fgets(dsLop[i].danhSachSV[j].ten, sizeof(dsLop[i].danhSachSV[j].ten), file);
            dsLop[i].danhSachSV[j].ten[strcspn(dsLop[i].danhSachSV[j].ten, "\n")] = '\0'; // remove newline

            fgets(dsLop[i].danhSachSV[j].mssv, sizeof(dsLop[i].danhSachSV[j].mssv), file);
            dsLop[i].danhSachSV[j].mssv[strcspn(dsLop[i].danhSachSV[j].mssv, "\n")] = '\0'; // remove newline

            fscanf_s(file, "%f\n", &dsLop[i].danhSachSV[j].dtb);

            fgets(dsLop[i].danhSachSV[j].xeploai, sizeof(dsLop[i].danhSachSV[j].xeploai), file);
            dsLop[i].danhSachSV[j].xeploai[strcspn(dsLop[i].danhSachSV[j].xeploai, "\n")] = '\0'; // remove newline
        }
    }

    fclose(file);
}

void hienThiDanhSachLopHoc(LopHoc dsLop[], int soLop) {
    for (int i = 0; i < soLop; i++) {
        printf("Ten lop: %s\n", dsLop[i].tenLop);
        printf("Si so: %d\n", dsLop[i].siSo);
        for (int j = 0; j < dsLop[i].siSo; j++) {
            hienThiSinhVien(dsLop[i].danhSachSV[j]);
        }
    }
}

void inLopCoNhieuSinhVienGioi(LopHoc dsLop[], int soLop) {
    for (int i = 0; i < soLop; i++) {
        int demGioi = 0;
        for (int j = 0; j < dsLop[i].siSo; j++) {
            if (strcmp(dsLop[i].danhSachSV[j].xeploai, "Gioi") == 0) {
                demGioi++;
            }
        }
        if (demGioi > 5) {
            printf("Lop: %s co %d sinh vien gioi.\n", dsLop[i].tenLop, demGioi);
        }
    }
}

void inLopCoNhieuSinhVienNhat(LopHoc dsLop[], int soLop) {
    if (soLop == 0) {
        printf("Khong co lop nao.\n");
        return;
    }

    LopHoc* lopMaxSiSo = &dsLop[0];
    for (int i = 1; i < soLop; i++) {
        if (dsLop[i].siSo > lopMaxSiSo->siSo) {
            lopMaxSiSo = &dsLop[i];
        }
    }

    printf("Lop co nhieu sinh vien nhat:\n");
    printf("Ten lop: %s\n", lopMaxSiSo->tenLop);
    printf("Si so: %d\n", lopMaxSiSo->siSo);
    for (int j = 0; j < lopMaxSiSo->siSo; j++) {
        hienThiSinhVien(lopMaxSiSo->danhSachSV[j]);
    }
}

void inSinhVienDiemCaoNhat(LopHoc dsLop[], int soLop) {
    if (soLop == 0) {
        printf("Khong co lop nao.\n");
        return;
    }

    SinhVien* svMaxDTB = &dsLop[0].danhSachSV[0];
    for (int i = 0; i < soLop; i++) {
        for (int j = 0; j < dsLop[i].siSo; j++) {
            if (dsLop[i].danhSachSV[j].dtb > svMaxDTB->dtb) {
                svMaxDTB = &dsLop[i].danhSachSV[j];
            }
        }
    }

    printf("Sinh vien co diem trung binh cao nhat:\n");
    hienThiSinhVien(*svMaxDTB);
}

int main() {
    LopHoc dsLop[MAX];
    int soLop = 0;
    int luaChon;

    do {
        printf("Chuong trinh quan ly lop hoc\n");
        printf("1. Tao file lop hoc\n");
        printf("2. Doc file lop hoc\n");
        printf("3. Hien thi danh sach lop hoc\n");
        printf("4. In lop co nhieu sinh vien gioi\n");
        printf("5. In lop co nhieu sinh vien nhat\n");
        printf("6. In sinh vien co diem trung binh cao nhat\n");
        printf("7. Thoat\n");
        printf("Nhap lua chon: ");
        scanf_s("%d", &luaChon);

        switch (luaChon) {
        case 1:
            taoFileLopHoc();
            break;
        case 2:
            docFileLopHoc(dsLop, &soLop);
            break;
        case 3:
            hienThiDanhSachLopHoc(dsLop, soLop);
            break;
        case 4:
            inLopCoNhieuSinhVienGioi(dsLop, soLop);
            break;
        case 5:
            inLopCoNhieuSinhVienNhat(dsLop, soLop);
            break;
        case 6:
            inSinhVienDiemCaoNhat(dsLop, soLop);
            break;
        case 7:
            printf("Thoat chuong trinh.\n");
            break;
        default:
            printf("Lua chon khong hop le. Vui long chon lai.\n");
        }
    } while (luaChon != 7);

    return 0;
}
