#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

// variable global ygy
FILE *tunjuk;
FILE *transaksi;
int ukuran = 0;
int jmlhinputroti = 0;

// struct menu ygy
struct menuroti
{
    int idroti;
    char namaroti[50];
    float hargaroti;
    int stokroti;
};
menuroti roti[100];

struct transaksicihuy
{
    int idroti;
    char namaroti[50];
    int jumlahbeli;
    float hargaroti;
    float totalharga;
};
transaksicihuy beliroticihuy[100];

// yes or no
bool yesorno(string yort)
{
    cout << "Kembali ke menu utama? (Y/T) : ";
    cin >> yort;

    if (yort == "ya" || yort == "Ya" || yort == "YA" || yort == "yA" || yort == "y" || yort == "Y")
    {
        system("cls");
        return false;
    }
    else if (yort == "tidak" || yort == "Tidak" || yort == "TIDAK" || yort == "t" || yort == "T")
    {
        cout << "Program Selesai!" << endl;
        cout << "Terima kasih telah menggunakan program ini!" << endl;
        return true;
    }
    else
    {
        cout << "Opsi tidak tersedia. Silahkan input kembali" << endl;
        return yesorno("");
    }
}

// function menu karyawan
void tambahmenu()
{
    bool found = false;
    bool valid = false;

    cout << "Masukkan jumlah data roti (max 100 menu): ";
    cin >> jmlhinputroti;
    cout << endl;

    while (found == false)
    {
        if (jmlhinputroti > 0 && jmlhinputroti <= 100)
        {
            found = true;
        }
        else
        {
            cout << "Tidak dapat menambahkan data lebih dari 100. Coba lagi!" << endl;
            cout << "Masukkan jumlah data roti (max 100 menu): ";
            cin >> jmlhinputroti;
            cout << endl;
        }
    }
    tunjuk = fopen("roti.txt", "a");
    // error handling ygy
    if (tunjuk == NULL)
    {
        cout << "Error Opening Data" << endl;
        exit(1);
    }

    // input menu roti ygy
    for (int i = 0; i < jmlhinputroti; i++)
    {
        valid = false;

        cout << "ID Roti: ";
        // error handling ygy
        //  agar input tidak huruf ygy
        while (!(cin >> roti[i].idroti))
        {
            cout << "Input harus angka! Masukkan ID kembali: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        cin.ignore();

        while (!valid)
        {
            cout << "Nama Roti (tanpa spasi): ";
            cin >> roti[i].namaroti;
            valid = true;
            // agar input bukan angka ygy
            for (int j = 0; roti[i].namaroti[j] != '\0'; j++)
            {
                if (roti[i].namaroti[j] >= '0' && roti[i].namaroti[j] <= '9')
                {
                    valid = false;
                    cout << "Nama tidak boleh mengandung angka!" << endl;
                    break;
                }
            }
        }

        cout << "Harga Roti: ";
        // agar tidak input huruf ygy
        while (!(cin >> roti[i].hargaroti))
        {
            cout << "Input harus angka! Masukkan harga kembali: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        cout << "Stok Roti: ";
        // agar tidak input huruf ygy
        while (!(cin >> roti[i].stokroti) || roti[i].stokroti <= 0)
        {
            cout << "Input harus angka bilangan cacah! Masukkan stok lagi: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        cin.ignore();
        cout << endl;

        fprintf(tunjuk, "%d %s %.2f %d \n", roti[i].idroti, roti[i].namaroti, roti[i].hargaroti, roti[i].stokroti);
        ukuran += 1;
    }
    fclose(tunjuk);
    cout << "Data telah tersimpan! \nTekan enter untuk melanjutkan." << endl;
    cin.ignore();
}

// edit menu ygy
void editmenu()
{
    system("cls");
    tunjuk = fopen("roti.txt", "r");
    // error handling ygy
    if (tunjuk == NULL)
    {
        cout << "Error Opening Data" << endl;
        exit(1);
    }
    int i = 0;
    while (fscanf(tunjuk, "%d %s %f %d", &roti[i].idroti, roti[i].namaroti, &roti[i].hargaroti, &roti[i].stokroti) == 4)
    {
        i++;
        if (i >= 100)
        {
            break;
        }
    }
    fclose(tunjuk);

    int cariid;
    bool found = false;
    bool valid = false;
    cout << "Masukkan ID Roti: ";
    cin >> cariid;
    cout << endl;

    for (int j = 0; j < i; j++)
    {
        if (roti[j].idroti == cariid)
        {
            found = true;
            cout << "Data ditemukan!" << endl;
            cout << "=============================" << endl;
            cout << " \t  DATA LAMA\t " << endl;
            cout << "=============================" << endl;
            cout << "Nama Roti  : " << roti[j].namaroti << endl;
            cout << "Harga Roti : " << roti[j].hargaroti << endl;
            cout << "Stok Roti  : " << roti[j].stokroti << endl;
            cout << endl;
            cout << "=============================" << endl;
            cout << " \t  DATA BARU\t " << endl;
            cout << "=============================" << endl;
            while (!valid)
            {
                cout << "Nama Roti (tanpa spasi): ";
                cin >> roti[j].namaroti;
                valid = true;
                // agar input bukan angka ygy
                for (int k = 0; roti[j].namaroti[k] != '\0'; k++)
                {
                    if (roti[j].namaroti[k] >= '0' && roti[j].namaroti[k] <= '9')
                    {
                        valid = false;
                        cout << "Nama tidak boleh mengandung angka!" << endl;
                        break;
                    }
                }
            }

            cout << "Harga Roti: ";
            // agar tidak input huruf ygy
            while (!(cin >> roti[j].hargaroti))
            {
                cout << "Input harus angka! Masukkan harga kembali: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }

            cout << "Stok Roti: ";
            // agar tidak input huruf ygy
            while (!(cin >> roti[j].stokroti) || roti[j].stokroti <= 0)
            {
                cout << "Input harus angka bilangan cacah! Masukkan stok lagi: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }

            cin.ignore();
            cout << endl;
            break;
        }
    }
    if (!found)
    {
        cout << "Data tidak ditemukan! Coba lagi." << endl;
        cout << "Masukkan ID Roti: ";
        cin >> cariid;
        cout << endl;
    }

    // overwrite file ygy
    tunjuk = fopen("roti.txt", "w");
    for (int j = 0; j < i; j++)
    {
        fprintf(tunjuk, "%d %s %.2f %d \n", roti[j].idroti, roti[j].namaroti, roti[j].hargaroti, roti[j].stokroti);
    }
    fclose(tunjuk);

    cout << "Data roti telah diperbarui!" << endl;
    system("pause");
}

// bubble sort asc ygy
void bubblesortasc(int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (roti[j].hargaroti > roti[j + 1].hargaroti)
            {
                swap(roti[j], roti[j + 1]);
            }
        }
    }
}

// quick sort dsc ygy
void quicksortdsc(int awal, int akhir)
{
    int low = awal, high = akhir;
    int pivot = roti[(awal + akhir) / 2].hargaroti;

    do
    {
        while (roti[low].hargaroti > pivot)
            low++;
        while (roti[high].hargaroti < pivot)
            high--;
        if (low <= high)
        {
            swap(roti[low], roti[high]);
            low++;
            high--;
        }
    } while (low <= high);
    if (awal < high)
        quicksortdsc(awal, high);
    if (low < akhir)
        quicksortdsc(low, akhir);
}

// buat lihat menu ygy
void lihatmenu()
{
    system("cls");
    int metode;
    bool found = false;
    tunjuk = fopen("roti.txt", "r");
    // error handling ygy
    if (tunjuk == NULL)
    {
        cout << "Error Opening Data" << endl;
        exit(1);
    }
    int i = 0;
    while (fscanf(tunjuk, "%d %s %f %d", &roti[i].idroti, roti[i].namaroti, &roti[i].hargaroti, &roti[i].stokroti) == 4)
    {
        i++;
        if (i >= 100)
        {
            break;
        }
    }
    fclose(tunjuk);
    // tampilan awal ygy
    cout << "Jumlah data roti: " << i << endl;
    cout << "Pilih metode lihat:" << endl;
    cout << "1. Ascending" << endl;
    cout << "2. Descending" << endl;
    cout << "Masukkan metode: ";
    // error handling ygy
    while (!(cin >> metode))
    {
        cout << "Input harus angka! Masukkan metode kembali: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    cout << endl;
    // error handling ygy
    while (found == false)
    {
        if (metode > 0 && metode < 3)
        {
            found = true;
        }
        else
        {
            system("cls");
            cout << "Opsi tidak sesuai! Silahkan input kembali." << endl;
            cout << "Jumlah data roti: " << i << endl;
            cout << "Pilih metode lihat:" << endl;
            cout << "1. Ascending" << endl;
            cout << "2. Descending" << endl;
            cout << "Masukkan metode: ";
            while (!(cin >> metode))
            {
                cout << "Input harus angka! Masukkan metode kembali: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cout << endl;
        }
    }
    switch (metode)
    {
    case 1:
        bubblesortasc(i);
        break;

    case 2:
        quicksortdsc(0, i - 1);
        break;
    }

    // menampilkan menu ygy
    for (int j = 0; j < i; j++)
    {
        cout << "ID Roti    : " << roti[j].idroti << endl;
        cout << "Nama Roti  : " << roti[j].namaroti << endl;
        cout << "Harga Roti : " << roti[j].hargaroti << endl;
        cout << "Stok Roti  : " << roti[j].stokroti << endl;
        cout << endl;
    }
    system("pause");
}

// function menu pelanggan ygy
// squentilan search ygy
void sequentialsearch(int i)
{
    char carinama[50];
    bool found = false;

    cout << "Masukkan nama roti yang ingin dicari: ";
    cin >> carinama;
    cout << endl;

    for (int j = 0; j < i; j++)
    {
        int k = 0;

        while (roti[j].namaroti[k] == carinama[k] && roti[j].namaroti[k] != '\0')
        {
            k++;
        }

        if (roti[j].namaroti[k] == '\0' && carinama[k] == '\0')
        {
            found = true;

            cout << "Jumlah data roti: " << i << endl;
            cout << "Roti ditemukan!" << endl;
            cout << "=============================" << endl;
            cout << "Nama Roti  : " << roti[j].namaroti << endl;
            cout << "Harga Roti : " << roti[j].hargaroti << endl;
            cout << "Stok Roti  : " << roti[j].stokroti << endl;
            cout << endl;
            break;
        }
    }
    if (!found)
    {
        cout << "Data tidak ditemukan!" << endl;
    }
    system("pause");
}

// binary search ygy
void binarysearch(int i)
{
    char carinama[50];
    cout << "Masukkan nama roti yang ingin dicari: ";
    cin >> carinama;
    cout << endl;

    int kiri = 0;
    int kanan = i - 1;
    bool found = false;

    while (kiri <= kanan)
    {
        int tengah = (kiri + kanan) / 2;

        int k = 0;
        while (roti[tengah].namaroti[k] == carinama[k] && roti[tengah].namaroti[k] != '\0')
        {
            k++;
        }

        if (roti[tengah].namaroti[k] == carinama[k])
        {
            found = true;

            cout << "Jumlah data roti: " << i << endl;
            cout << "Roti ditemukan!" << endl;
            cout << "=============================" << endl;
            cout << "Nama Roti  : " << roti[tengah].namaroti << endl;
            cout << "Harga Roti : " << roti[tengah].hargaroti << endl;
            cout << "Stok Roti  : " << roti[tengah].stokroti << endl;
            cout << endl;

            break;
        }
        else if (roti[tengah].namaroti[k] < carinama[k])
        {
            kiri = tengah + 1;
        }
        else
        {
            kanan = tengah - 1;
        }
    }

    if (!found)
    {
        cout << "Data tidak ditemukan!" << endl;
    }

    system("pause");
}

// cari roti ygy
void carairoti()
{
    system("cls");
    int metode;
    bool found = false;
    tunjuk = fopen("roti.txt", "r");
    // error handling ygy
    if (tunjuk == NULL)
    {
        cout << "Error Opening Data" << endl;
        exit(1);
    }
    int i = 0;
    while (fscanf(tunjuk, "%d %s %f %d", &roti[i].idroti, roti[i].namaroti, &roti[i].hargaroti, &roti[i].stokroti) == 4)
    {
        i++;
        if (i >= 100)
        {
            break;
        }
    }
    fclose(tunjuk);

    if (i == 0)
    {
        cout << "Tidak ada data roti" << endl;
        system("pause");
        return;
    }

    // tampilan awal ygy
    cout << "Pilih metode lihat:" << endl;
    cout << "1. Sequential" << endl;
    cout << "2. Binary" << endl;
    cout << "Masukkan metode: ";
    // error handling ygy
    while (!(cin >> metode))
    {
        cout << "Input harus angka! Masukkan metode kembali: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    cout << endl;
    // error handling ygy
    while (found == false)
    {
        if (metode > 0 && metode < 3)
        {
            found = true;
        }
        else
        {
            system("cls");
            cout << "Pilih metode lihat:" << endl;
            cout << "1. Sequential" << endl;
            cout << "2. Binary" << endl;
            cout << "Masukkan metode: ";
            while (!(cin >> metode))
            {
                cout << "Input harus angka! Masukkan metode kembali: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cout << endl;
        }
    }
    switch (metode)
    {
    case 1:
        sequentialsearch(i);
        break;

    case 2:
        bubblesortasc(i);
        binarysearch(i);
        break;
    }
}

// bubble sort asc by ID ygy
void bubblesortascbyid(int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (roti[j].idroti > roti[j + 1].idroti)
            {
                swap(roti[j], roti[j + 1]);
            }
        }
    }
}

// quick sort dsc by ID ygy
void quicksortdscbyid(int awal, int akhir)
{
    int low = awal, high = akhir;
    int pivot = roti[(awal + akhir) / 2].idroti;

    do
    {
        while (roti[low].idroti > pivot)
            low++;
        while (roti[high].idroti < pivot)
            high--;
        if (low <= high)
        {
            swap(roti[low], roti[high]);
            low++;
            high--;
        }
    } while (low <= high);
    if (awal < high)
        quicksortdscbyid(awal, high);
    if (low < akhir)
        quicksortdscbyid(low, akhir);
}

void lihatmenubeli()
{
    system("cls");
    int metode;
    bool found = false;
    tunjuk = fopen("roti.txt", "r");
    // error handling ygy
    if (tunjuk == NULL)
    {
        cout << "Error Opening Data" << endl;
        exit(1);
    }
    int i = 0;
    while (fscanf(tunjuk, "%d %s %f %d", &roti[i].idroti, roti[i].namaroti, &roti[i].hargaroti, &roti[i].stokroti) == 4)
    {
        i++;
        if (i >= 100)
        {
            break;
        }
    }
    fclose(tunjuk);
    // tampilan awal ygy
    cout << "Jumlah data roti: " << i << endl;
    cout << "Pilih metode lihat:" << endl;
    cout << "1. Ascending" << endl;
    cout << "2. Descending" << endl;
    cout << "Masukkan metode: ";
    // error handling ygy
    while (!(cin >> metode))
    {
        cout << "Input harus angka! Masukkan metode kembali: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    cout << endl;
    // error handling ygy
    while (found == false)
    {
        if (metode > 0 && metode < 3)
        {
            found = true;
        }
        else
        {
            system("cls");
            cout << "Opsi tidak sesuai! Silahkan input kembali." << endl;
            cout << "Jumlah data roti: " << i << endl;
            cout << "Pilih metode lihat:" << endl;
            cout << "1. Ascending" << endl;
            cout << "2. Descending" << endl;
            cout << "Masukkan metode: ";
            while (!(cin >> metode))
            {
                cout << "Input harus angka! Masukkan metode kembali: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cout << endl;
        }
    }
    switch (metode)
    {
    case 1:
        bubblesortascbyid(i);
        break;

    case 2:
        quicksortdscbyid(0, i - 1);
        break;
    }

    // menampilkan menu ygy
    for (int j = 0; j < i; j++)
    {
        cout << "ID Roti    : " << roti[j].idroti << endl;
        cout << "Nama Roti  : " << roti[j].namaroti << endl;
        cout << "Harga Roti : " << roti[j].hargaroti << endl;
        cout << "Stok Roti  : " << roti[j].stokroti << endl;
        cout << endl;
    }
    system("pause");
}

// menu beli roti ygy
void beliroti()
{
    int iddibeli;
    int jumlahbeli;
    int i = 0;
    bool found = false;
    int k = -1; // untuk index roti ygy

    system("cls");
    lihatmenubeli();
    tunjuk = fopen("roti.txt", "r");
    // error handling ygy
    if (tunjuk == NULL)
    {
        cout << "Error membuka file!" << endl;
        system("pause");
        return;
    }
    while (fscanf(tunjuk, "%d %s %f %d", &roti[i].idroti, roti[i].namaroti, &roti[i].hargaroti, &roti[i].stokroti) == 4)
    {
        i++;
        if (i >= 100)
            break;
    }
    fclose(tunjuk);

    if (i == 0)
    {
        cout << "Tidak ada data roti!" << endl;
        system("pause");
        return;
    }

    while (!found)
    {
        cout << "Masukkan ID roti yang ingin dibeli: ";

        // error handling
        while (!(cin >> iddibeli))
        {
            cout << "Input harus angka! Silahkan input kembali: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        for (int j = 0; j < i; j++)
        {
            if (iddibeli == roti[j].idroti)
            {
                found = true;
                k = j;
                break;
            }
        }
        if (!found)
        {
            cout << "ID roti tidak ditemukan! Silahkan coba lagi." << endl;
        }
    }
    bool validbeli = false;
    while (!validbeli)
    {
        cout << "Masukkan Jumlah beli: ";

        // error handling ygy
        while (!(cin >> jumlahbeli))
        {
            cout << "Input harus angka! Silahkan input kembali: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        // erro handling ygy
        if (jumlahbeli <= 0)
        {
            cout << "Jumlah harus lebih dari 0!" << endl;
        }
        else if (jumlahbeli > roti[k].stokroti)
        {
            cout << "Jumlah melebihi stok! Stok tersedia hanya: " << roti[k].stokroti << endl;
        }
        else
        {
            validbeli = true;
        }
    }
    // transaksi ygy
    float totalharga = jumlahbeli * roti[k].hargaroti;

    transaksi = fopen("transaksi.txt", "a");
    // error handling ygy
    if (transaksi == NULL)
    {
        cout << "Error membuka file!" << endl;
        system("pause");
        return;
    }
    if (transaksi != NULL)
    {
        fprintf(transaksi, "%d %s %d %.2f %.2f\n", roti[k].idroti, roti[k].namaroti, jumlahbeli, roti[k].hargaroti, totalharga);
        fclose(transaksi);
    }
    // mengurangi stok pada array ygy
    roti[k].stokroti -= jumlahbeli;

    // mengurangi stok pada file ygy
    tunjuk = fopen("roti.txt", "w");
    // error handling ygy
    if (tunjuk == NULL)
    {
        cout << "Error membuka file!" << endl;
        system("pause");
        return;
    }
    for (int j = 0; j < i; j++)
    {
        fprintf(tunjuk, "%d %s %.2f %d \n", roti[j].idroti, roti[j].namaroti, roti[j].hargaroti, roti[j].stokroti);
    }
    fclose(tunjuk);

    cout << "Pembelian berhasil! Silahkan pilih menu Invoice untuk mencetak struk." << endl;
}

// invoice ygy
void invoice()
{
    system("cls");
    transaksi = fopen("transaksi.txt", "r");
    if (transaksi == NULL)
    {
        cout << "Tidak ada transaksi!" << endl;
        system("pause");
        return;
    }

    int i = 0;
    while (fscanf(transaksi, "%d %s %d %f %f", &beliroticihuy[i].idroti, beliroticihuy[i].namaroti, &beliroticihuy[i].jumlahbeli, &beliroticihuy[i].hargaroti, &beliroticihuy[i].totalharga) == 5)
    {
        i++;
        if (i >= 100)
        {
            break;
        }
    }
    fclose(transaksi);

    if (i == 0)
    {
        cout << "Tidak ada transaksi!" << endl;
        system("pause");
        return;
    }
    cout << "======= STRUK PEMBELIAN =======" << endl;

    for (int j = 0; j < i; j++)
    {
        cout << "Nama Roti : " << beliroticihuy[j].namaroti << endl;
        cout << "Harga     : " << beliroticihuy[j].hargaroti << endl;
        cout << "Jumlah    : " << beliroticihuy[j].jumlahbeli << endl;
        cout << "Total     : Rp" << beliroticihuy[j].totalharga << endl;
        cout << "------------------------------" << endl;
    }

    string jawaban;
    cout << "Apakah ingin reset data transaksi? (y/n)";
    while (cin >> jawaban)
    {
        if (jawaban == "ya" || jawaban == "YA" || jawaban == "yA" || jawaban == "Ya" || jawaban == "y" || jawaban == "Y")
        {
            remove("transaksi.txt");
            cout << "Data transaksi telah direset!" << endl;
            break;
        }
        else if (jawaban == "no" || jawaban == "NO" || jawaban == "No" || jawaban == "nO" || jawaban == "n" || jawaban == "N")
        {
            break;
        }
        else
        {
            cout << "Jawaban tidak tersedia! Silahkan input kembali." << endl;
        }
    }
    system("pause");
}

// main program
int main()
{
    // variable local ygy
    int pilihan;
    string inputpassword;
    string inputusername;
    string password = "123";
    string username = "kry";
    bool found = false;
    int max_attempt = 5;
    bool kembalikemenuawal = true;

    // menu utama ygy
    while (kembalikemenuawal)
    {
        cout << "=============================" << endl;
        cout << " WELCOME TO WARM LOAF BAKERY " << endl;
        cout << "=============================" << endl;
        cout << "1. Masukkan sebagai karyawan" << endl;
        cout << "2. Masuk sebagai pembeli" << endl;
        cout << "Masukkan menu: ";
        cin >> pilihan;
        system("cls");

        // login karyawan ygy
        if (pilihan == 1)
        {
            for (int i = 1; i <= 5; i++)
            {
                cout << "==================================" << endl;
                cout << "\t  Halo Karyawan!\t" << endl;
                cout << " Silahkan login untuk melanjutkan " << endl;
                cout << "==================================" << endl;
                cout << "Masukkan Username: ";
                cin >> inputusername;
                cout << "Masukkan Password: ";
                cin >> inputpassword;

                found = false;
                if (inputusername == username && inputpassword == password)
                {
                    // submenu utama karyawan ygy
                    found = true;
                    do
                    {
                        system("cls");
                        cout << "==============================" << endl;
                        cout << "\tWELCOME BAKER!\t" << endl;
                        cout << "==============================" << endl;
                        cout << "1. Tambah menu roti" << endl;
                        cout << "2. Lihat menut roti" << endl;
                        cout << "3. Edit menu roti" << endl;
                        cout << "4. Logout" << endl;
                        cout << "Masukkan menu: ";
                        cin >> pilihan;

                        switch (pilihan)
                        {
                        case 1:
                            do
                            {
                                tambahmenu();
                            } while (yesorno(""));
                            break;
                        case 2:
                            do
                            {
                                lihatmenu();
                            } while (yesorno(""));
                            break;
                        case 3:
                            do
                            {
                                editmenu();
                            } while (yesorno(""));
                            break;
                        case 4:
                            kembalikemenuawal = true;
                            break;
                        }
                    } while (pilihan != 4);
                    cout << "Terima kasih, Baker. \nSelamat Beristirahat!\n";
                    system("pause");
                    system("cls");
                    break;
                }
                else
                {
                    if (i < max_attempt)
                    {
                        int sisakesempatan = max_attempt - i;
                        system("cls");
                        cout << "Login gagal! Username atau Password salah!" << endl;
                        cout << "Kesempatan tersisa " << sisakesempatan << endl;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            if (!found)
            {
                system("cls");
                cout << "Login gagal! Akses ditolak." << endl;
                return 0;
            }
        }
        else if (pilihan == 2)
        {
            do
            {
                system("cls");
                cout << "==============================" << endl;
                cout << "\tWELCOME BUYER!\t" << endl;
                cout << "==============================" << endl;
                cout << "1. Cari Roti" << endl;
                cout << "2. Beli Roti" << endl;
                cout << "3. Invoice" << endl;
                cout << "4. Logout" << endl;
                cout << "Masukkan menu: ";
                cin >> pilihan;

                switch (pilihan)
                {
                case 1:
                    do
                    {
                        carairoti();
                    } while (yesorno(""));
                    break;
                case 2:
                    do
                    {
                        beliroti();
                    } while (yesorno(""));
                    break;
                case 3:
                    do
                    {
                        invoice();
                    } while (yesorno(""));
                    break;
                case 4:
                    cout << "Terima kasih telah berbelanja disini! Semoga harimu menyenangkan" << endl;
                    system("pause");
                    system("cls");
                    break;
                }
            } while (pilihan != 4);
            kembalikemenuawal = true;
        }
        else
        {
            system("cls");
            cout << "Opsi tidak sesuai! Silahkan input kembali" << endl;
            kembalikemenuawal = true;
        }
    }
}