#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <iomanip>
#include <limits>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <cctype>

using namespace std;

/* =====================================================================
 *  FUNGSI BANTU (UTILITAS)
 * ===================================================================== */

// Membersihkan sisa input yang salah agar tidak terjadi loop error
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Membaca pilihan angka bermenu dengan validasi rentang [minVal, maxVal]
int bacaPilihan(int minVal, int maxVal) {
    int x;
    while (true) {
        cout << ">> Masukkan pilihan Anda: ";
        if (cin >> x && x >= minVal && x <= maxVal)
            return x;

        clearInput();
        cout << "   [!] Input tidak valid. Masukkan angka "
             << minVal << " - " << maxVal << ".\n";
    }
}

// Mengubah angka menjadi format Rupiah  (45000 -> "Rp45.000")
string rupiah(long long nilai) {
    string angka = to_string(nilai);
    string hasil;
    int hitung = 0;

    // Sisipkan titik setiap 3 digit dari belakang
    for (int i = (int)angka.size() - 1; i >= 0; --i) {
        hasil.push_back(angka[i]);
        if (++hitung % 3 == 0 && i != 0)
            hasil.push_back('.');
    }
    reverse(hasil.begin(), hasil.end());
    return "Rp" + hasil;
}

// Mencetak garis pembatas
void garis() {
    cout << "==================================================================\n";
}

/* =====================================================================
 *  STRUKTUR DATA
 * ===================================================================== */

struct Bioskop {
    string         nama;    // nama bioskop
    long long      harga;   // harga per tiket
    vector<string> film;    // daftar 4 judul film
    vector<string> genre;   // genre / "poster" tiap film
};

/* =====================================================================
 *  PROGRAM UTAMA
 * ===================================================================== */

int main() {

    /* ---------- Data 3 bioskop (masing-masing 4 film) ---------- */
    vector<Bioskop> bioskop = {
        { "CGI", 45000,
          { "Avengers: Endgame", "Interstellar", "Dilan 1990", "The Conjuring" },
          { "[ Action / Superhero ]", "[ Sci-Fi / Drama ]",
            "[ Romance / Remaja ]",   "[ Horror / Thriller ]" } },

        { "XX1", 50000,
          { "Oppenheimer", "Spiderman: No Way Home", "KKN di Desa Penari", "Inside Out 2" },
          { "[ Biografi / Sejarah ]", "[ Action / Superhero ]",
            "[ Horror ]",             "[ Animasi / Keluarga ]" } },

        { "Cinepolis", 55000,
          { "Dune: Part Two", "Joker", "Agak Laen", "Kung Fu Panda 4" },
          { "[ Sci-Fi / Epic ]",   "[ Drama / Psikologi ]",
            "[ Komedi / Horror ]", "[ Animasi / Komedi ]" } }
    };

    /* ---------- Daftar jam tayang ---------- */
    vector<string> jamTayang = { "12:00", "14:30", "17:00", "19:30", "21:45" };

    garis();
    cout << "          SELAMAT DATANG DI APLIKASI TIKET BIOSKOP\n";
    garis();

    /* ============== 1. PILIH TEMPAT BIOSKOP ============== */
    cout << "\n[1] PILIH TEMPAT BIOSKOP\n";
    for (size_t i = 0; i < bioskop.size(); ++i) {
        cout << "    " << (i + 1) << ". " << bioskop[i].nama
             << "  (" << rupiah(bioskop[i].harga) << " / tiket)\n";
    }
    int pBio = bacaPilihan(1, (int)bioskop.size()) - 1;
    Bioskop& b = bioskop[pBio];   // referensi bioskop terpilih

    /* ============== 2. PILIH JUDUL FILM ============== */
    cout << "\n[2] PILIH FILM di " << b.nama << "\n";
    for (size_t i = 0; i < b.film.size(); ++i) {
        cout << "    " << (i + 1) << ". " << b.film[i]
             << "  " << b.genre[i] << "\n";
    }
    int pFilm = bacaPilihan(1, (int)b.film.size()) - 1;

    /* ============== 3. PILIH JAM TAYANG ============== */
    cout << "\n[3] PILIH JAM TAYANG\n";
    for (size_t i = 0; i < jamTayang.size(); ++i) {
        cout << "    " << (i + 1) << ". " << jamTayang[i] << " WIB\n";
    }
    int pJam = bacaPilihan(1, (int)jamTayang.size()) - 1;

    /* ============== 4. JUMLAH TIKET (+ DISKON) ============== */
    cout << "\n[4] JUMLAH TIKET\n";
    cout << "    (Beli >= 2 tiket otomatis DISKON 10%)\n";

    int jumlah;
    while (true) {
        cout << "    Masukkan jumlah tiket (1 - 10): ";
        if (cin >> jumlah && jumlah >= 1 && jumlah <= 10) break;
        clearInput();
        cout << "    [!] Jumlah tidak valid.\n";
    }

    // Hitung subtotal, diskon, dan total
    long long subtotal = b.harga * (long long)jumlah;
    long long diskon   = (jumlah >= 2) ? subtotal / 10 : 0;   // 10%
    long long total    = subtotal - diskon;

    cout << "\n    Subtotal : " << rupiah(subtotal) << "\n";
    if (diskon > 0)
        cout << "    Diskon   : -" << rupiah(diskon) << " (10%)\n";
    else
        cout << "    Diskon   : - (beli 2+ untuk dapat diskon)\n";
    cout << "    TOTAL    : " << rupiah(total) << "\n";

    /* ============== 5. METODE PEMBAYARAN (NONTUNAI) ============== */
    // Pembayaran hanya nontunai. User memilih salah satu jenis di bawah.
    cout << "\n[5] METODE PEMBAYARAN (NONTUNAI)\n";
    cout << "    1. QRIS\n";
    cout << "    2. Kartu Debit\n";
    cout << "    3. E-Wallet (OVO / GoPay / DANA / ShopeePay)\n";
    int jenis = bacaPilihan(1, 3);

    string metode;
    if (jenis == 1) {
        metode = "Nontunai - QRIS";
    } else if (jenis == 2) {
        // Kartu Debit -> pilih bank penerbit
        cout << "\n    Pilih Bank:\n";
        cout << "    1. BCA\n";
        cout << "    2. BNI\n";
        cout << "    3. BRI\n";
        cout << "    4. Mandiri\n";
        cout << "    5. SeaBank\n";
        cout << "    6. CIMB Niaga\n";
        int bank = bacaPilihan(1, 6);

        string namaBank[] = { "BCA", "BNI", "BRI", "Mandiri", "SeaBank", "CIMB Niaga" };
        metode = "Nontunai - Kartu Debit (" + namaBank[bank - 1] + ")";
    } else {
        metode = "Nontunai - E-Wallet";
    }

    cout << "    [OK] Pembayaran " << metode << " sebesar "
         << rupiah(total) << " berhasil diproses.\n";

    /* ============== 6. PEMILIHAN KURSI (ANTI GANDA) ============== */
    // Denah: baris A-E, kolom 1-10  (contoh kode: A10, B3, E7)
    const char barisAwal = 'A', barisAkhir = 'E';
    const int  kolomMax  = 10;

    // Kursi yang sudah terisi penonton lain (contoh bawaan)
    set<string> terisi = { "A1", "A2", "C5", "E10" };
    set<string> kursiSaya;   // kursi yang dipilih user sesi ini

    cout << "\n[6] PEMILIHAN KURSI\n";

    for (int t = 1; t <= jumlah; ++t) {

        // --- Tampilkan denah kursi ---
        cout << "\n    DENAH KURSI  ([X] = terisi)\n";
        cout << "    ----------------------------------\n";
        for (char r = barisAwal; r <= barisAkhir; ++r) {
            cout << "    " << r << " | ";
            for (int c = 1; c <= kolomMax; ++c) {
                string kode = string(1, r) + to_string(c);
                if (terisi.count(kode) || kursiSaya.count(kode))
                    cout << "[X]  ";
                else
                    cout << setw(3) << left << kode << "  ";
            }
            cout << "\n";
        }
        cout << "    ----------------------------------\n";

        // --- Minta input kursi untuk tiket ke-t ---
        while (true) {
            cout << "    Pilih kursi untuk tiket #" << t << " (contoh A10): ";
            string kode;
            cin >> kode;

            // Ubah huruf jadi kapital (a1 -> A1)
            for (char& ch : kode) ch = toupper((unsigned char)ch);

            // Validasi: huruf baris benar + sisanya angka 1..kolomMax
            bool valid = kode.size() >= 2 &&
                         kode[0] >= barisAwal && kode[0] <= barisAkhir;
            if (valid) {
                string angka = kode.substr(1);
                for (char d : angka)
                    if (!isdigit((unsigned char)d)) valid = false;
                if (valid) {
                    int nomor = stoi(angka);
                    valid = (nomor >= 1 && nomor <= kolomMax);
                }
            }

            if (!valid) {
                cout << "      [!] Kode kursi salah. Gunakan A1 s/d E"
                     << kolomMax << ".\n";
                continue;
            }
            if (terisi.count(kode) || kursiSaya.count(kode)) {
                cout << "      [!] Kursi " << kode
                     << " SUDAH TERISI. Pilih kursi lain.\n";
                continue;
            }

            // Kursi valid & kosong -> simpan
            kursiSaya.insert(kode);
            cout << "      [OK] Kursi " << kode << " berhasil dipilih.\n";
            break;
        }
    }

    /* ============== 7. CETAK RESI / BUKTI BAYAR ============== */

    // Kode booking acak + waktu transaksi
    srand((unsigned)time(nullptr));
    int kodeBooking = 100000 + rand() % 900000;

    time_t now = time(nullptr);
    char   waktu[64];
    strftime(waktu, sizeof(waktu), "%d-%m-%Y %H:%M:%S", localtime(&now));

    // Gabungkan daftar kursi menjadi satu teks
    string daftarKursi;
    for (auto it = kursiSaya.begin(); it != kursiSaya.end(); ++it) {
        if (it != kursiSaya.begin()) daftarKursi += ", ";
        daftarKursi += *it;
    }

    cout << "\n\n";
    garis();
    cout << "                 BUKTI PEMBAYARAN / RESI\n";
    garis();
    cout << " Kode Booking   : #" << kodeBooking << "\n";
    cout << " Waktu          : " << waktu << "\n";
    cout << "------------------------------------------------------------------\n";
    cout << " Bioskop        : " << b.nama << "\n";
    cout << " Film           : " << b.film[pFilm] << " " << b.genre[pFilm] << "\n";
    cout << " Jam Tayang     : " << jamTayang[pJam] << " WIB\n";
    cout << " Jumlah Tiket   : " << jumlah << " tiket\n";
    cout << " Kursi          : " << daftarKursi << "\n";
    cout << "------------------------------------------------------------------\n";
    cout << " Harga / tiket  : " << rupiah(b.harga) << "\n";
    cout << " Subtotal       : " << rupiah(subtotal) << "\n";
    cout << " Diskon         : -" << rupiah(diskon) << (diskon > 0 ? " (10%)" : "") << "\n";
    cout << " TOTAL BAYAR    : " << rupiah(total) << "\n";
    cout << "------------------------------------------------------------------\n";
    cout << " Metode Bayar   : " << metode << "\n";
    cout << "           Status : LUNAS\n";
    garis();
    cout << "        Terima kasih telah memesan. Selamat menonton! :)\n";
    garis();

    return 0;
}
