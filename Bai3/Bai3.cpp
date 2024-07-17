#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <limits.h>

// Định nghĩa kích thước mảng là một hằng số
#define SIZE 15

// Hàm kiểm tra số nguyên tố
bool laSoNguyenTo(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

// Hàm nhập vào số nguyên n và liệt kê các số nguyên tố nhỏ hơn n
void lietKeSoNguyenToNhoHonN(int n) {
    bool coSoNguyenTo = false;
    for (int i = 2; i < n; i++) {
        if (laSoNguyenTo(i)) {
            printf("%d ", i);
            coSoNguyenTo = true;
        }
    }
    if (!coSoNguyenTo) {
        printf("Khong co so nguyen to nao nho hon %d\n", n);
    }
    else {
        printf("\n");
    }
}

// Hàm lấy chữ số đầu tiên của một số
int chuSoDau(int n) {
    while (n >= 10) {
        n /= 10;
    }
    return n;
}

// Hàm tính tổng các phần tử có chữ số đầu là chữ số lẻ
int tongChuSoDauLaChuSoLe(int a[], int n) {
    int tong = 0;
    for (int i = 0; i < n; i++) {
        if (chuSoDau(abs(a[i])) % 2 != 0) {
            tong += a[i];
        }
    }
    return tong;
}

// Hàm liệt kê số lần xuất hiện của các phần tử trong mảng
void lietKeSoLanXuatHien(int a[], int n) {
    int dem[1000] = { 0 };
    for (int i = 0; i < n; i++) {
        dem[a[i]]++;
    }
    for (int i = 0; i < n; i++) {
        if (dem[a[i]] != 0) {
            printf("%d xuat hien %d lan\n", a[i], dem[a[i]]);
            dem[a[i]] = 0; // Đảm bảo mỗi phần tử chỉ in ra một lần
        }
    }
}

// Hàm sắp xếp mảng có số chẵn tăng dần, số lẻ giảm dần
void sapXepChanTangLeGiam(int a[], int n) {
    int chan[SIZE], le[SIZE];
    int soChan = 0, soLe = 0;

    for (int i = 0; i < n; i++) {
        if (a[i] % 2 == 0) {
            chan[soChan++] = a[i];
        }
        else {
            le[soLe++] = a[i];
        }
    }

    // Sắp xếp số chẵn tăng dần
    for (int i = 0; i < soChan - 1; i++) {
        for (int j = i + 1; j < soChan; j++) {
            if (chan[i] > chan[j]) {
                int temp = chan[i];
                chan[i] = chan[j];
                chan[j] = temp;
            }
        }
    }

    // Sắp xếp số lẻ giảm dần
    for (int i = 0; i < soLe - 1; i++) {
        for (int j = i + 1; j < soLe; j++) {
            if (le[i] < le[j]) {
                int temp = le[i];
                le[i] = le[j];
                le[j] = temp;
            }
        }
    }

    int idx = 0;
    for (int i = 0; i < soChan; i++) {
        a[idx++] = chan[i];
    }
    for (int i = 0; i < soLe; i++) {
        a[idx++] = le[i];
    }
}

// Hàm tìm dãy con giảm dài nhất trong mảng
void timDayConGiamDaiNhat(int a[], int n) {
    int maxLen = 1, len = 1;
    int start = 0, end = 0;

    for (int i = 1; i < n; i++) {
        if (a[i] < a[i - 1]) {
            len++;
            if (len > maxLen) {
                maxLen = len;
                end = i;
            }
        }
        else {
            len = 1;
        }
    }

    start = end - maxLen + 1;
    printf("Day con giam dai nhat: ");
    for (int i = start; i <= end; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

// Hàm tìm số nhỏ thứ 2 trong mảng
int timSoNhoThuHai(int a[], int n) {
    int min = INT_MAX, secondMin = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (a[i] < min) {
            secondMin = min;
            min = a[i];
        }
        else if (a[i] < secondMin && a[i] != min) {
            secondMin = a[i];
        }
    }
    return secondMin;
}

// Hàm kiểm tra nếu một số chứa các chữ số của x
bool chuaChuSo(int num, int x) {
    char strNum[20], strX[3];
    sprintf_s(strNum, "%d", num);
    sprintf_s(strX, "%d", x);

    int i = 0, j = 0;
    while (strNum[i] != '\0' && strX[j] != '\0') {
        if (strNum[i] == strX[j]) {
            j++;
        }
        i++;
    }
    return strX[j] == '\0';
}

// Hàm tìm các phần tử trong mảng chứa các chữ số của x
void timPhanTuChuaChuSo(int a[], int n, int x) {
    printf("Cac phan tu trong mang chua cac chu so cua %d: ", x);
    for (int i = 0; i < n; i++) {
        if (chuaChuSo(a[i], x)) {
            printf("%d ", a[i]);
        }
    }
    printf("\n");
}

// Hàm sắp xếp mảng: số chẵn tăng dần, số lẻ giữ nguyên vị trí
void sapXepChanTangLeGiuNguyen(int a[], int n) {
    int chan[SIZE];
    int soChan = 0;

    for (int i = 0; i < n; i++) {
        if (a[i] % 2 == 0) {
            chan[soChan++] = a[i];
        }
    }

    // Sắp xếp số chẵn tăng dần
    for (int i = 0; i < soChan - 1; i++) {
        for (int j = i + 1; j < soChan; j++) {
            if (chan[i] > chan[j]) {
                int temp = chan[i];
                chan[i] = chan[j];
                chan[j] = temp;
            }
        }
    }

    int idx = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] % 2 == 0) {
            a[i] = chan[idx++];
        }
    }
}

// Hàm sắp xếp mảng: số lẻ ở đầu mảng, số chẵn ở cuối mảng
void sapXepLeDauChanCuoi(int a[], int n) {
    int b[SIZE];
    int idx = 0;

    // Sắp xếp số lẻ vào đầu mảng
    for (int i = 0; i < n; i++) {
        if (a[i] % 2 != 0) {
            b[idx++] = a[i];
        }
    }

    // Sắp xếp số chẵn vào cuối mảng
    for (int i = 0; i < n; i++) {
        if (a[i] % 2 == 0) {
            b[idx++] = a[i];
        }
    }

    for (int i = 0; i < n; i++) {
        a[i] = b[i];
    }
}


int main() {
    srand((unsigned int)time(0));

    int n = SIZE;
    int a[SIZE];

    // Tạo mảng ngẫu nhiên
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 100;
    }

    // Xuất mảng
    printf("Mang ban dau: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    // 1. Liệt kê các số nguyên tố nhỏ hơn n
    int soNguyen = 50;
    printf("Cac so nguyen to nho hon %d: ", soNguyen);
    lietKeSoNguyenToNhoHonN(soNguyen);

    // 2. Tính tổng các phần tử có chữ số đầu là chữ số lẻ
    int tong = tongChuSoDauLaChuSoLe(a, n);
    printf("Tong cac phan tu co chu so dau la chu so le: %d\n", tong);

    // 3. Liệt kê số lần xuất hiện của các phần tử trong mảng
    printf("So lan xuat hien cua cac phan tu trong mang:\n");
    lietKeSoLanXuatHien(a, n);

    // 4. Sắp xếp mảng có số chẵn tăng dần, số lẻ giảm dần
    sapXepChanTangLeGiam(a, n);
    printf("Mang sau khi sap xep chan tang le giam: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    // 5. Tìm dãy con giảm dài nhất trong a
    timDayConGiamDaiNhat(a, n);

    // 6. Tìm số nhỏ thứ 2 trong mảng
    int soNhoThuHai = timSoNhoThuHai(a, n);
    printf("So nho thu hai trong mang: %d\n", soNhoThuHai);

    // 7. Tìm các phần tử trong a chứa các chữ số của x
    int x = 28;
    timPhanTuChuaChuSo(a, n, x);

    // 8. Sắp xếp mảng: số chẵn tăng dần, số lẻ giữ nguyên vị trí
    sapXepChanTangLeGiuNguyen(a, n);
    printf("Mang sau khi sap xep chan tang le giu nguyen: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    // 9. Sắp xếp mảng: số lẻ ở đầu mảng, số chẵn ở cuối mảng
    sapXepLeDauChanCuoi(a, n);
    printf("Mang sau khi sap xep le dau chan cuoi: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}
