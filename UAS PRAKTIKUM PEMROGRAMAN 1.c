#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MHS 100

struct Mahasiswa {
    char nim[15];
    char nama[40];
    float nilai_tugas;
    float nilai_uts;
    float nilai_uas;
    float nilai_akhir;
    char grade;
};

struct Mahasiswa mhs[MAX_MHS];
int jumlah_mhs = 0;
int is_logged_in = 0;

void login();
void hitung_grade(int index);
void tambah_data();
void tampilkan_data();
void cari_data();
void edit_data();
void hapus_data();
void simpan_ke_file();
void muat_dari_file();

int main() {
    int pilihan;
    
    do {
        printf("\n=== PENILAIAN MAHASISWA ===\n");
        if (!is_logged_in) {
            printf("1. Login \n2. Keluar \n");
            printf("Pilih: "); scanf("%d", &pilihan);
            if (pilihan == 1) login();
            else if (pilihan == 2) exit(0);
        } else {
            printf("1. Tambah Data Mahasiswa\n");
            printf("2. Tampilkan Semua Data\n");
            printf("3. Cari Data Berdasarkan NIM\n");
            printf("4. Edit Data Mahasiswa\n");
            printf("5. Hapus Data Mahasiswa\n");
            printf("6. Simpan Data ke file .txt\n");
            printf("7. Muat Data dari file .txt\n");
            printf("8. Logout\n");
            printf("9. Keluar Program\n");
            printf("Pilih: "); scanf("%d", &pilihan);

            switch(pilihan) {
                case 1: tambah_data(); break;
                case 2: tampilkan_data(); break;
                case 3: cari_data(); break;
                case 4: edit_data(); break;
                case 5: hapus_data(); break;
                case 6: simpan_ke_file(); break;
                case 7: muat_dari_file(); break;
                case 8: is_logged_in = 0; printf("Logout berhasil!\n"); break;
                case 9: exit(0);
                default: printf("Pilihan tidak valid!\n");
            }
        }
    } while (1);

    return 0;
}

void login() {
    char user[20], pass[20];
    printf("Username: "); scanf("%s", user);
    printf("Password: "); scanf("%s", pass);

    if (strcmp(user, "admin") == 0 && strcmp(pass, "admin123") == 0) {
        is_logged_in = 1;
        printf("Login Berhasil!\n");
    } else {
        printf("Username atau Password salah!\n");
    }
}

void hitung_grade(int i) {
    mhs[i].nilai_akhir = (0.30 * mhs[i].nilai_tugas) + (0.30 * mhs[i].nilai_uts) + (0.40 * mhs[i].nilai_uas);
    if (mhs[i].nilai_akhir >= 80) mhs[i].grade = 'A';
    else if (mhs[i].nilai_akhir >= 70) mhs[i].grade = 'B';
    else if (mhs[i].nilai_akhir >= 60) mhs[i].grade = 'C';
    else if (mhs[i].nilai_akhir >= 50) mhs[i].grade = 'D';
    else mhs[i].grade = 'E';
}

void tambah_data() {
    if (jumlah_mhs >= MAX_MHS) {
        printf("Kapasitas penuh!\n");
        return;
    }
    printf("NIM: "); scanf("%s", mhs[jumlah_mhs].nim);
    printf("Nama: "); scanf(" %[^\n]s", mhs[jumlah_mhs].nama);
    printf("Nilai Tugas: "); scanf("%f", &mhs[jumlah_mhs].nilai_tugas);
    printf("Nilai UTS: "); scanf("%f", &mhs[jumlah_mhs].nilai_uts);
    printf("Nilai UAS: "); scanf("%f", &mhs[jumlah_mhs].nilai_uas);
    hitung_grade(jumlah_mhs);
    jumlah_mhs++;
    printf("Data berhasil ditambahkan!\n");
}

void tampilkan_data() {
    if (jumlah_mhs == 0) {
        printf("Data kosong.\n");
        return;
    }
    printf("\n%-15s | %-20s | %-5s | %-5s | %-5s | %-11s | %-5s\n", "NIM", "NAMA", "TUGAS", "UTS", "UAS", "NILAI AKHIR", "GRADE");
    printf("--------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < jumlah_mhs; i++) {
        printf("%-15s | %-20s | %-5.2f | %-5.2f | %-5.2f | %-11.2f | %-5c\n", 
               mhs[i].nim, mhs[i].nama, mhs[i].nilai_tugas, mhs[i].nilai_uts, mhs[i].nilai_uas, mhs[i].nilai_akhir, mhs[i].grade);
    }
}

void cari_data() {
    char target[15];
    printf("Masukkan NIM yang dicari: "); scanf("%s", target);
    for (int i = 0; i < jumlah_mhs; i++) {
        if (strcmp(mhs[i].nim, target) == 0) {
            printf("Data Ditemukan: %s - %s - Nilai: %.2f (Grade: %c)\n", mhs[i].nim, mhs[i].nama, mhs[i].nilai_akhir, mhs[i].grade);
            return;
        }
    }
    printf("Data tidak ditemukan!\n");
}

void edit_data() {
    char target[15];
    printf("Masukkan NIM yang akan diedit: "); scanf("%s", target);
    for (int i = 0; i < jumlah_mhs; i++) {
        if (strcmp(mhs[i].nim, target) == 0) {
            printf("Masukkan Nama Baru: "); scanf(" %[^\n]s", mhs[i].nama);
            printf("Masukkan Nilai Tugas: "); scanf("%f", &mhs[i].nilai_tugas);
            printf("Masukkan Nilai UTS: "); scanf("%f", &mhs[i].nilai_uts);
            printf("Masukkan Nilai UAS: "); scanf("%f", &mhs[i].nilai_uas);
            hitung_grade(i);
            printf("Data berhasil diperbarui!\n");
            return;
        }
    }
    printf("NIM tidak ditemukan!\n");
}

void hapus_data() {
    char target[15];
    printf("Masukkan NIM yang akan dihapus: "); scanf("%s", target);
    for (int i = 0; i < jumlah_mhs; i++) {
        if (strcmp(mhs[i].nim, target) == 0) {
            for (int j = i; j < jumlah_mhs - 1; j++) {
                mhs[j] = mhs[j + 1];
            }
            jumlah_mhs--;
            printf("Data berhasil dihapus!\n");
            return;
        }
    }
    printf("NIM tidak ditemukan!\n");
}

void simpan_ke_file() {
    FILE *fp = fopen("data_mahasiswa.txt", "w");
    if (fp == NULL) return;
    for (int i = 0; i < jumlah_mhs; i++) {
        fprintf(fp, "%s;%s;%.2f;%.2f;%.2f;%.2f;%c\n", mhs[i].nim, mhs[i].nama, mhs[i].nilai_tugas, mhs[i].nilai_uts, mhs[i].nilai_uas, mhs[i].nilai_akhir, mhs[i].grade);
    }
    fclose(fp);
    printf("Data berhasil disimpan ke file.\n");
}

void muat_dari_file() {
    FILE *fp = fopen("data_mahasiswa.txt", "r");
    if (fp == NULL) {
        printf("File tidak ditemukan.\n");
        return;
    }
    jumlah_mhs = 0;
    while (fscanf(fp, " %14[^;];%39[^;];%f;%f;%f;%f;%c\n", mhs[jumlah_mhs].nim, mhs[jumlah_mhs].nama, &mhs[jumlah_mhs].nilai_tugas, &mhs[jumlah_mhs].nilai_uts, &mhs[jumlah_mhs].nilai_uas, &mhs[jumlah_mhs].nilai_akhir, &mhs[jumlah_mhs].grade) != EOF) {
        jumlah_mhs++;
    }
    fclose(fp);
    printf("Data berhasil dimuat dari file.\n");
}