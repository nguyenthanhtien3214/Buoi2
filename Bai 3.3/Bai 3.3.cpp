#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char hoTen[50];
    char soDienThoai[15];
    int soVeNguoiLon;
    int soVeTreEm;
    char tenPhim[50];
    char phongChieu[10];
    char xuatChieu[20];
    int tienPhaiTra;
} KhachHang;

KhachHang dskh[MAX];
int soKhachHang = 0;

void docFileKhachHang(const char* tenFile) {
    FILE* file;
    fopen_s(&file, tenFile, "r");
    if (!file) {
        printf("Khong the mo file de doc.\n");
        return;
    }

    fscanf_s(file, "%d\n", &soKhachHang);
    for (int i = 0; i < soKhachHang; i++) {
        fgets(dskh[i].hoTen, sizeof(dskh[i].hoTen), file);
        dskh[i].hoTen[strcspn(dskh[i].hoTen, "\n")] = '\0';

        fgets(dskh[i].soDienThoai, sizeof(dskh[i].soDienThoai), file);
        dskh[i].soDienThoai[strcspn(dskh[i].soDienThoai, "\n")] = '\0';

        fscanf_s(file, "%d\n", &dskh[i].soVeNguoiLon);
        fscanf_s(file, "%d\n", &dskh[i].soVeTreEm);

        fgets(dskh[i].tenPhim, sizeof(dskh[i].tenPhim), file);
        dskh[i].tenPhim[strcspn(dskh[i].tenPhim, "\n")] = '\0';

        fgets(dskh[i].phongChieu, sizeof(dskh[i].phongChieu), file);
        dskh[i].phongChieu[strcspn(dskh[i].phongChieu, "\n")] = '\0';

        fgets(dskh[i].xuatChieu, sizeof(dskh[i].xuatChieu), file);
        dskh[i].xuatChieu[strcspn(dskh[i].xuatChieu, "\n")] = '\0';

        fscanf_s(file, "%d\n", &dskh[i].tienPhaiTra);
    }

    fclose(file);
}

void xuatDanhSachKhachHang() {
    for (int i = 0; i < soKhachHang; i++) {
        printf("Ho ten: %s\n", dskh[i].hoTen);
        printf("So dien thoai: %s\n", dskh[i].soDienThoai);
        printf("So ve nguoi lon: %d\n", dskh[i].soVeNguoiLon);
        printf("So ve tre em: %d\n", dskh[i].soVeTreEm);
        printf("Ten phim: %s\n", dskh[i].tenPhim);
        printf("Phong chieu: %s\n", dskh[i].phongChieu);
        printf("Xuat chieu: %s\n", dskh[i].xuatChieu);
        printf("Tien phai tra: %d\n\n", dskh[i].tienPhaiTra);
    }
}

void tinhTienKhachHang() {
    for (int i = 0; i < soKhachHang; i++) {
        dskh[i].tienPhaiTra = dskh[i].soVeNguoiLon * 40000 + dskh[i].soVeTreEm * 20000;
    }
}


int tinhTongDoanhThu() {
    int tongDoanhThu = 0;
    for (int i = 0; i < soKhachHang; i++) {
        tongDoanhThu += dskh[i].tienPhaiTra;
    }
    return tongDoanhThu;
}


void tinhTongDoanhThuTheoPhim() {
    for (int i = 0; i < soKhachHang; i++) {
        int doanhThu = 0;
        for (int j = 0; j < soKhachHang; j++) {
            if (strcmp(dskh[i].tenPhim, dskh[j].tenPhim) == 0) {
                doanhThu += dskh[j].tienPhaiTra;
            }
        }
        printf("Tong doanh thu phim %s: %d\n", dskh[i].tenPhim, doanhThu);
    }
}

void xuatThongTinPhongChieuXuatChieu() {
    char phongChieu[10], xuatChieu[20];
    printf("Nhap phong chieu: ");
    getchar(); // Clear buffer
    fgets(phongChieu, sizeof(phongChieu), stdin);
    phongChieu[strcspn(phongChieu, "\n")] = '\0';

    printf("Nhap xuat chieu: ");
    fgets(xuatChieu, sizeof(xuatChieu), stdin);
    xuatChieu[strcspn(xuatChieu, "\n")] = '\0';

    for (int i = 0; i < soKhachHang; i++) {
        if (strcmp(dskh[i].phongChieu, phongChieu) == 0 && strcmp(dskh[i].xuatChieu, xuatChieu) == 0) {
            printf("Ho ten: %s\n", dskh[i].hoTen);
            printf("So dien thoai: %s\n", dskh[i].soDienThoai);
            printf("So ve nguoi lon: %d\n", dskh[i].soVeNguoiLon);
            printf("So ve tre em: %d\n", dskh[i].soVeTreEm);
            printf("Ten phim: %s\n", dskh[i].tenPhim);
            printf("Phong chieu: %s\n", dskh[i].phongChieu);
            printf("Xuat chieu: %s\n", dskh[i].xuatChieu);
            printf("Tien phai tra: %d\n\n", dskh[i].tienPhaiTra);
        }
    }
}

void interchangeSort() {
    for (int i = 0; i < soKhachHang - 1; i++) {
        for (int j = i + 1; j < soKhachHang; j++) {
            if (dskh[i].tienPhaiTra > dskh[j].tienPhaiTra) {
                KhachHang temp = dskh[i];
                dskh[i] = dskh[j];
                dskh[j] = temp;
            }
        }
    }
}

void selectionSort() {
    for (int i = 0; i < soKhachHang - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < soKhachHang; j++) {
            if (dskh[j].tienPhaiTra < dskh[minIdx].tienPhaiTra) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            KhachHang temp = dskh[i];
            dskh[i] = dskh[minIdx];
            dskh[minIdx] = temp;
        }
    }
}

void quickSort(int left, int right) {
    int i = left, j = right;
    int pivot = dskh[(left + right) / 2].tienPhaiTra;
    while (i <= j) {
        while (dskh[i].tienPhaiTra < pivot) i++;
        while (dskh[j].tienPhaiTra > pivot) j--;
        if (i <= j) {
            KhachHang temp = dskh[i];
            dskh[i] = dskh[j];
            dskh[j] = temp;
            i++;
            j--;
        }
    }
    if (left < j) quickSort(left, j);
    if (i < right) quickSort(i, right);
}
void sapXepTheoHoTen() {
    for (int i = 0; i < soKhachHang - 1; i++) {
        for (int j = i + 1; j < soKhachHang; j++) {
            if (strcmp(dskh[i].hoTen, dskh[j].hoTen) > 0) {
                KhachHang temp = dskh[i];
                dskh[i] = dskh[j];
                dskh[j] = temp;
            }
        }
    }
}


int binarySearch(KhachHang arr[], int left, int right, char* hoTen) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int res = strcmp(arr[mid].hoTen, hoTen);
        if (res == 0) return mid;
        if (res < 0) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}


void timKiemKhachHang() {
    char hoTen[50];
    printf("Nhap ho ten khach hang can tim: ");
    getchar(); // Clear buffer
    fgets(hoTen, sizeof(hoTen), stdin);
    hoTen[strcspn(hoTen, "\n")] = '\0';

    sapXepTheoHoTen(); // Sắp xếp danh sách trước khi tìm kiếm
    int index = binarySearch(dskh, 0, soKhachHang - 1, hoTen);
    if (index != -1) {
        printf("Khach hang %s duoc tim thay:\n", hoTen);
        printf("Ho ten: %s\n", dskh[index].hoTen);
        printf("So dien thoai: %s\n", dskh[index].soDienThoai);
        printf("So ve nguoi lon: %d\n", dskh[index].soVeNguoiLon);
        printf("So ve tre em: %d\n", dskh[index].soVeTreEm);
        printf("Ten phim: %s\n", dskh[index].tenPhim);
        printf("Phong chieu: %s\n", dskh[index].phongChieu);
        printf("Xuat chieu: %s\n", dskh[index].xuatChieu);
        printf("Tien phai tra: %d\n\n", dskh[index].tienPhaiTra);
    }
    else {
        printf("Khach hang %s khong duoc tim thay.\n", hoTen);
    }
}


int main() {
    int luaChon;

    do {
        printf("Chuong trinh quan ly dat ve rap chieu phim\n");
        printf("1. Doc file khach hang\n");
        printf("2. Xuat danh sach khach hang\n");
        printf("3. Tinh tien khach hang\n");
        printf("4. Xuat tong doanh thu\n");
        printf("5. Xuat doanh thu theo phim\n");
        printf("6. Xuat thong tin phong chieu va xuat chieu\n");
        printf("7. Sap xep theo so tien phai tra\n");
        printf("8. Sap xep theo ho ten\n");
        printf("9. Tim khach hang theo ten\n");
        printf("10. Thoat\n");
        printf("Nhap lua chon: ");
        scanf_s("%d", &luaChon);

        switch (luaChon) {
        case 1:
            docFileKhachHang("dskh.txt");
            break;
        case 2:
            xuatDanhSachKhachHang();
            break;
        case 3:
            tinhTienKhachHang();
            break;
        case 4:
            printf("Tong doanh thu: %d\n", tinhTongDoanhThu());
            break;
        case 5:
            tinhTongDoanhThuTheoPhim();
            break;
        case 6:
            xuatThongTinPhongChieuXuatChieu();
            break;
        case 7:
            interchangeSort();
            xuatDanhSachKhachHang();
            break;
        case 8:
            sapXepTheoHoTen();
            xuatDanhSachKhachHang();
            break;
        case 9:
            timKiemKhachHang();
            break;
        case 10:
            printf("Thoat chuong trinh.\n");
            break;
        default:
            printf("Lua chon khong hop le. Vui long chon lai.\n");
        }
    } while (luaChon != 10);

    return 0;
}


