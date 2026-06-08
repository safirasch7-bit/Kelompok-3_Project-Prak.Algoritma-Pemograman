#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iomanip>
using namespace std;

struct Mahasiswa {
    string noPendaftaran;
    string nama;
    string jenisKelamin;
    string asalSekolah;
    string prodi;
};

struct JalurMasuk {
    string jalur;
    string kip;
};

struct UKT {
    double penghasilanOrtu;
    int tanggungan;
    string kelompokUKT;
};

struct DataMaba {
    Mahasiswa mhs;
    JalurMasuk jalur;
    UKT ukt;
} data[100];

string kip(double penghasilanOrtu){
	if (penghasilanOrtu <= 3000000) return "Aktif";
	else return "Nonaktif";
	}

void ukt(string *kip, double *penghasilanOrtu){
    int bayar;
    string kel;

    if (*kip == "Aktif"){
        bayar = 0;
        kel = "UKT Kelompok 0";
		}else if (*penghasilanOrtu <= 4000000){
			bayar = 3325000;
			kel = "UKT Kelompok 1";
			}else if (*penghasilanOrtu <= 5000000){
				bayar = 6650000;
				kel = "UKT Kelompok 2";
				}else if (*penghasilanOrtu <= 6000000){
					bayar = 9975000;
					kel = "UKT Kelompok 3";
					}else if (*penghasilanOrtu <= 7000000){
						bayar = 13300000;
						kel = "UKT Kelompok 4";
						}else{
							bayar = 16240000;
							kel = "UKT Kelompok 5";
							}

    cout << "Kelompok UKT : " << kel << endl;
    cout << "Nominal yang Harus Dibayar : " << bayar << endl;
}

void merge(DataMaba *mer, int kiri, int tengah, int kanan, int pil, int arah){
	int i = kiri, j = tengah + 1, k =1;
	DataMaba sort[100];
	while (i <= tengah && j <= kanan){
		bool ambil;
		
		if (pil == 1){//NOMOR PENDAFTARAN
			if (arah == 1) ambil = mer[i].mhs.noPendaftaran <= mer[j].mhs.noPendaftaran;
			else ambil = mer[i].mhs.noPendaftaran >= mer[j].mhs.noPendaftaran; 
			} else if (pil == 2){//NAMA
				if (arah == 1) ambil = mer[i].mhs.nama <= mer[j].mhs.nama;
				else ambil = mer[i].mhs.nama >= mer[j].mhs.nama; 
				} else {//PENGHASILAN ORTU
					if (arah == 1) ambil = mer[i].ukt.penghasilanOrtu <= mer[j].ukt.penghasilanOrtu;
					else ambil = mer[i].ukt.penghasilanOrtu >= mer[j].ukt.penghasilanOrtu;
					}
		if (ambil) sort[k++] = mer[i++];
		else sort[k++] = mer[j++];
		}
		while (i <= tengah) sort[k++] = mer[i++];
		while (j <= kanan) sort[k++] = mer[j++];
		for (int c = 0; c < k-1; c++) mer[kiri + c] = sort [c+1];
	};

void mergeSort(DataMaba mer[], int kiri, int kanan, int pil, int arah){
	if (kiri < kanan){
		int tengah = (kiri + kanan)/2;
		mergeSort(mer, kiri, tengah, pil, arah);
		mergeSort(mer, tengah + 1, kanan, pil, arah);
		merge(mer, kiri, tengah, kanan, pil, arah);
		}
	};

void quick(DataMaba qui[], int kiri, int kanan, int pil, int arah){
	int i = kiri, j = kanan;
	DataMaba pivot = qui[(kiri + kanan)/2];

	while (i<=j) { 
		if (pil == 1) {//NOMOR PENDAFTARAN
			if (arah == 1){
				while (qui[i].mhs.noPendaftaran < pivot.mhs.noPendaftaran) i++;
				while (qui[j].mhs.noPendaftaran > pivot.mhs.noPendaftaran) j--;
				} else {
					while (qui[i].mhs.noPendaftaran > pivot.mhs.noPendaftaran) i++;
					while (qui[j].mhs.noPendaftaran < pivot.mhs.noPendaftaran) j--;
					} 
			} else if (pil == 2){// NAMA
				if (arah == 1){
					while (qui[i].mhs.nama < pivot.mhs.nama) i++;
					while (qui[j].mhs.nama > pivot.mhs.nama) j--;
					} else {
						while (qui[i].mhs.nama > pivot.mhs.nama) i++;
						while (qui[j].mhs.nama < pivot.mhs.nama) j--;
						} 
				}else {//PENGHASILAN ORTU
					if (arah == 1){
						while (qui[i].ukt.penghasilanOrtu < pivot.ukt.penghasilanOrtu) i++;
						while (qui[j].ukt.penghasilanOrtu > pivot.ukt.penghasilanOrtu) j--;
						} else {
							while (qui[i].ukt.penghasilanOrtu > pivot.ukt.penghasilanOrtu) i++;
							while (qui[j].ukt.penghasilanOrtu < pivot.ukt.penghasilanOrtu) j--;
							}
					}
		if (i <= j){
			swap (qui[i],qui[j]);
			i++;
			j--;
			}
		}
		if (kiri < j) quick(qui, kiri, j, pil, arah);
		if (i < kanan) quick(qui, i, kanan, pil, arah);
	};

void bubble(DataMaba arr[], int n, int pil, int arah){
	for (int i = 0; i < n - 1; i++){
		for (int j = 0; j < n - i - 1; j++){
			bool tukar = false;
			// NOMOR PENDAFTARAN
			if (pil == 1){
				if (arah == 1){
					if (arr[j].mhs.noPendaftaran > arr[j+1].mhs.noPendaftaran){
						tukar = true;
						}
					} else {
						if (arr[j].mhs.noPendaftaran < arr[j+1].mhs.noPendaftaran){
							tukar = true;
							}
						}
						//NAMA
				} else if (pil == 2){
							if (arah == 1){
							if (arr[j].mhs.nama > arr[j+1].mhs.nama){
								tukar = true;
								}
							} else {
								if (arr[j].mhs.nama < arr[j+1].mhs.nama){
									tukar = true;
								}
						}
							//PENGHASILAN ORTU
					} else if (pil == 3){
						if (arah == 1){
							if (arr[j].ukt.penghasilanOrtu > arr[j+1].ukt.penghasilanOrtu){
								tukar = true;
								}
							} else {
								if (arr[j].ukt.penghasilanOrtu < arr[j+1].ukt.penghasilanOrtu){
									tukar = true;
								}
						}
			}
			if(tukar){
				swap(arr[j], arr[j + 1]);
				}
		}
	}
}

void selection(DataMaba arr[], int n, int pil, int arah){
    for(int i = 0; i < n - 1; i++){
        int idx = i;

        for(int j = i + 1; j < n; j++){
            bool pilih = false;
            // Nomor Pendaftaran
            if(pil == 1){
                if(arah == 1){
                    if(arr[j].mhs.noPendaftaran < arr[idx].mhs.noPendaftaran)
                        pilih = true;
                }else{
                    if(arr[j].mhs.noPendaftaran > arr[idx].mhs.noPendaftaran)
                        pilih = true;
                }
            }
            // Nama
            else if(pil == 2){
                if(arah == 1){
                    if(arr[j].mhs.nama < arr[idx].mhs.nama)
                        pilih = true;
                }else{
                    if(arr[j].mhs.nama > arr[idx].mhs.nama)
                        pilih = true;
                }
            }
            // Penghasilan Ortu
            else if(pil == 3){
                if(arah == 1){
                    if(arr[j].ukt.penghasilanOrtu < arr[idx].ukt.penghasilanOrtu)
                        pilih = true;
                }else{
                    if(arr[j].ukt.penghasilanOrtu > arr[idx].ukt.penghasilanOrtu)
                        pilih = true;
                }
            }
            if(pilih)
                idx = j;
        }
        if(idx != i)
            swap(arr[i], arr[idx]);
    }
}

void insertion(DataMaba *arr, int n, int pil, int arah){
    for(int i = 1; i < n; i++){
        DataMaba key = *(arr + i);
        int j = i - 1;

        while(j >= 0){
            bool geser = false;

            if(pil == 1){
                if(arah == 1)
                    geser = (*(arr + j)).mhs.noPendaftaran >
                            key.mhs.noPendaftaran;
                else
                    geser = (*(arr + j)).mhs.noPendaftaran <
                            key.mhs.noPendaftaran;
            }
            else if(pil == 2){
                if(arah == 1)
                    geser = (*(arr + j)).mhs.nama >
                            key.mhs.nama;
                else
                    geser = (*(arr + j)).mhs.nama <
                            key.mhs.nama;
            }
            else if(pil == 3){
                if(arah == 1)
                    geser = (*(arr + j)).ukt.penghasilanOrtu >
                            key.ukt.penghasilanOrtu;
                else
                    geser = (*(arr + j)).ukt.penghasilanOrtu <
                            key.ukt.penghasilanOrtu;
            }

            if(geser){
                *(arr + j + 1) = *(arr + j);
                j--;
            } else {
                break;
            }
        }
        
        *(arr + j + 1) = key;
    }
}

void shell(DataMaba *arr, int n, int pil, int arah){
    for(int gap = n/2; gap > 0; gap /= 2){

        for(int i = gap; i < n; i++){

            DataMaba temp = *(arr + i);
            int j = i;

            while(j >= gap){
                bool geser = false;

                if(pil == 1){
                    if(arah == 1)
                        geser = (*(arr + j - gap)).mhs.noPendaftaran >
                                temp.mhs.noPendaftaran;
                    else
                        geser = (*(arr + j - gap)).mhs.noPendaftaran <
                                temp.mhs.noPendaftaran;
                }
                else if(pil == 2){
                    if(arah == 1)
                        geser = (*(arr + j - gap)).mhs.nama >
                                temp.mhs.nama;
                    else
                        geser = (*(arr + j - gap)).mhs.nama <
                                temp.mhs.nama;
                }
                else if(pil == 3){
                    if(arah == 1)
                        geser = (*(arr + j - gap)).ukt.penghasilanOrtu >
                                temp.ukt.penghasilanOrtu;
                    else
                        geser = (*(arr + j - gap)).ukt.penghasilanOrtu <
                                temp.ukt.penghasilanOrtu;
                }

                if(geser){
                    *(arr + j) = *(arr + j - gap);
                    j -= gap;
                } else {
                    break;
                }
            }

            *(arr + j) = temp;
        }
    }
}

int main() {
	char out;
    int menu, n = 0;
    string mabafile;
    bool exit = false;

    do {

        cout << setfill('=') << setw(40) << "" << endl;
        cout << "SISTEM AKADEMIK MAHASISWA BARU\n";
        cout << setfill('=') << setw(40) << "" << endl;
        cout << "1. Pendaftaran Mahasiswa Baru\n";
        cout << "2. Searching Data Maba\n";
        cout << "3. Sorting Data Maba\n";
        cout << "4. Informasi UKT\n";
        cout << "5. Keluar\n";
        cout << "Pilih Menu : ";
        cin >> menu;
		system("cls");
        switch(menu) {
        case 1: {
            system("cls");
            cout << setfill('=') << setw(40) << "" << endl;
            cout << "PENDAFTARAN MABA\n";
            cout << setfill('=') << setw(40) << "" << endl;
            cout << "\nMasukkan Jumlah Mahasiswa : ";
            cin >> n;
            cout << "Data disimpan ke file : ";
            cin >> mabafile;
            cin.ignore();

            ofstream file(mabafile.c_str());

            if (!file) {
                cout << "File gagal dibuat!\n";
                break;
            }

            for (int i = 0; i < n; i++) {
                cout << "\nData ke-" << i + 1 << endl;
                cout << "A. Nomor Pendaftaran              : ";
                getline(cin, data[i].mhs.noPendaftaran);
                cout << "B. Nama Lengkap                   : ";
                getline(cin, data[i].mhs.nama);
                cout << "C. Jenis Kelamin (L/P)            : ";
                getline(cin, data[i].mhs.jenisKelamin);
                cout << "D. Penghasilan Orang Tua          : ";
                cin >> data[i].ukt.penghasilanOrtu;
                cin.ignore();
                data[i].jalur.kip = kip(data[i].ukt.penghasilanOrtu);
                cout << "E. Status KIP (aktif/nonaktif)    : ";
                cout << data[i].jalur.kip << endl;
                cout << "F. Jumlah Tanggungan              : ";
                cin >> data[i].ukt.tanggungan;
                cout << "G. Jalur Masuk                    : ";
                cin >> data[i].jalur.jalur;
                cin.ignore();

                // Simpan ke file
                file << data[i].mhs.noPendaftaran << "|"
                     << data[i].mhs.nama << "|"
                     << data[i].mhs.jenisKelamin << "|"
                     << data[i].ukt.penghasilanOrtu << "|"
                     << data[i].jalur.kip << "|"
                     << data[i].ukt.tanggungan << "|"
                     << data[i].jalur.jalur
                     << endl;
            }

            file.close();
            cout << "\nData berhasil disimpan!\n";

            break;
        }
        case 2: {
            string cari;
            int pilih, opsi;
            bool found = false;

            cout << "\n=== Daftar File ===\n";
            system("dir /b *.txt");

            cout << "\nMasukkan nama file : ";
            cin >> mabafile;

            ifstream file(mabafile.c_str());

            if (!file) {
                cout << "File tidak ditemukan!\n";
                break;
            }

            while (
                getline(file, data[n].mhs.noPendaftaran, '|') &&
                getline(file, data[n].mhs.nama, '|') &&
                getline(file, data[n].mhs.jenisKelamin, '|')
            ) {
				string temp;
				getline(file, temp, '|');
				data[n].ukt.penghasilanOrtu = atof(temp.c_str());

				getline(file, data[n].jalur.kip, '|');

				getline(file, temp, '|');
				data[n].ukt.tanggungan = atoi(temp.c_str());

				getline(file, data[n].jalur.jalur);
	
				n++;
            }

            file.close();

            if (n == 0) {
                cout << "Data kosong!\n";
                break;
            }

            cout << "\n1. Sequential Search\n";
            cout << "Pilih : ";
            cin >> pilih;

            cin.ignore();

            if (pilih == 1) {
                cout << "\n=== SEQUENTIAL SEARCH ===\n";
                cout << "1. Cari berdasarkan Nomor Pendaftaran\n";
                cout << "2. Cari berdasarkan Nama\n";
                cout << "Pilih : ";
                cin >> opsi;
                cin.ignore();

                // SEARCH NOMOR
                if (opsi == 1) {

                    cout << "Masukkan Nomor Pendaftaran : ";
                    getline(cin, cari);

                    for (int i = 0; i < n; i++) {
                        if (data[i].mhs.noPendaftaran == cari) {
                            cout << "\nData ditemukan!\n";
                            cout << "\nNo Pendaftaran   : "
                                 << data[i].mhs.noPendaftaran;
                            cout << "\nNama Lengkap     : "
                                 << data[i].mhs.nama;
                            cout << "\nJenis Kelamin    : "
                                 << data[i].mhs.jenisKelamin;
                            cout << fixed << setprecision(0);
                            cout << "\nPenghasilan Ortu : "
                                 << data[i].ukt.penghasilanOrtu;
                            cout << "\nStatus KIP       : "
                                 << data[i].jalur.kip;
                            cout << "\nTanggungan       : "
                                 << data[i].ukt.tanggungan << "\n\n";

                            found = true;
                            break;
                        }
                    }
                }

                // SEARCH NAMA
                else if (opsi == 2) {
                    cout << "Masukkan Nama : ";
                    getline(cin, cari);
                    for (int i = 0; i < n; i++) {
                        if (data[i].mhs.nama == cari) {
                            cout << "\nData ditemukan!\n";
                            cout << "\nNo Pendaftaran   : "
                                 << data[i].mhs.noPendaftaran;
                            cout << "\nNama Lengkap     : "
                                 << data[i].mhs.nama;
                            cout << "\nJenis Kelamin    : "
                                 << data[i].mhs.jenisKelamin;
                            cout << "\nPenghasilan Ortu : "
                                 << data[i].ukt.penghasilanOrtu;
                            cout << "\nStatus KIP       : "
                                 << data[i].jalur.kip;
                            cout << "\nTanggungan       : "
                                 << data[i].ukt.tanggungan;

                            found = true;
                            break;
                        }
                    }
                }

                if (!found) {
                    cout << "\nData tidak ditemukan!\n";
                }
            }
            cout << endl;
            break;
        }
        case 3: {
			system("cls");
			int metode, pil, arah;
			string pilFile, saveFile;
			
			cout << "=== Daftar File ===" << endl;
			system("dir /b *.txt");
			cout << "File yang mau di sorting (namafile.txt) : ";
			cin >> pilFile;
			ifstream file(pilFile.c_str());
			if (!file){
				cout << endl << "File tidak ditemukan!" << endl;
				break;
				}
			n = 0;
			while (
                getline(file, data[n].mhs.noPendaftaran, '|') &&
                getline(file, data[n].mhs.nama, '|') &&
                getline(file, data[n].mhs.jenisKelamin, '|')
            ) {
				string temp;
				getline(file, temp, '|');
				data[n].ukt.penghasilanOrtu = atof(temp.c_str());

				getline(file, data[n].jalur.kip, '|');

				getline(file, temp, '|');
				data[n].ukt.tanggungan = atoi(temp.c_str());

				getline(file, data[n].jalur.jalur);
	
				n++;
            }
			file.close();
			if (n == 0){
				cout << endl << "Data Kosong!" << endl;
				break;
				}
			cout << endl << "1. Bubble Sort" << endl;
			cout << "2. Selection Sort" << endl;
			cout << "3. Insertion Sort" << endl;
			cout << "4. Shell Sort" << endl;
			cout << "5. Merge Sort" << endl;
			cout << "6. Quick Sort" << endl;
			cout << "Pilih metode sorting : ";
			cin >> metode;
			if(metode < 1 || metode > 6){
				cout << "Pilihan Tidak Tersedia!" << endl;
				break;
				}
			cout << endl << "1. Nomor Pendaftaran" << endl;
			cout << "2. Nama" << endl;
			cout << "3. Penghasilan Ortu" << endl;
			cout << "Sorting berdasarkan : ";
			cin >> pil;
			if(pil < 1 || pil > 3){
				cout << "Pilihan Tidak Tersedia!" << endl;
				break;
				}
			cout << endl << "1. Ascending" << endl;
			cout << "2. Descending" << endl;
			cout << "Pilih arah : ";
			cin >> arah;
			if(arah < 1 || arah > 2){
				cout << "Pilihan Tidak Tersedia!" << endl;
				break;
				}
			if (metode == 1){
				bubble(data, n, pil, arah);
				} else if (metode == 2){
				  selection(data, n, pil, arah);
					} else if (metode == 3){
						insertion(data, n, pil, arah);
						} else if (metode == 4){
							shell(data, n, pil, arah);
							} else if (metode == 5){
								mergeSort(data, 0, n - 1, pil, arah);
								} else if (metode == 6){
									quick(data, 0, n - 1, pil, arah);
									}
			cout << endl << "===== HASIL SORTING =====" << endl;
				cout << fixed << setprecision(0);
				cout << left;
				cout << setfill('=') << setw(120) << "" << endl;
				cout << setfill(' ') 
				<< setw(5)  << "No" 
				<< setw(18) << "No Pendaftaran" 
				<< setw(18) << "Nama" 
				<< setw(18) << "Jenis Kelamin" 
				<< setw(25) << "Penghasilan Orangtua"
				<< setw(15) << "Status KIP" 
				<< setw(12) << "Tanggungan" 
				<< setw(15) << "Jalur Masuk"<< endl;
				cout << setfill('=') << setw(120) << "" << endl;
			for (int i = 0; i < n; i++){
				cout << setfill(' ') 
				<< setw(5)  << i + 1 
				<< setw(18) << data[i].mhs.noPendaftaran 
				<< setw(30) << data[i].mhs.nama 
				<< setw(18) << data[i].mhs.jenisKelamin 
				<< setw(25) << data[i].ukt.penghasilanOrtu
				<< setw(15) << data[i].jalur.kip 
				<< setw(12) << data[i].ukt.tanggungan
				<< setw(15) << data[i].jalur.jalur << endl;
				}
			break;
			}
		case 4 : {
			string pilFile, no;
			bool ketemu = false;
			cout << "=== Daftar File ===" << endl;
			system("dir /b *.txt");
			cout << "File yang mau ditampilkan (namafile.txt) : ";
			cin >> pilFile;
			ifstream file(pilFile.c_str());
			if (!file){
				cout << endl << "File tidak ditemukan!" << endl;
				break;
				}
			n = 0;
			while (
                getline(file, data[n].mhs.noPendaftaran, '|') &&
                getline(file, data[n].mhs.nama, '|') &&
                getline(file, data[n].mhs.jenisKelamin, '|')
            ) {
				string temp;
				getline(file, temp, '|');
				data[n].ukt.penghasilanOrtu = atof(temp.c_str());
				
				getline(file, data[n].jalur.kip, '|');

				getline(file, temp, '|');
				data[n].ukt.tanggungan = atoi(temp.c_str());

				getline(file, data[n].jalur.jalur);
	
				n++;
			}
			file.close();
			if (n == 0){
				cout << endl << "Data Kosong!" << endl;
				break;
				}
			cout << "Masukkan nomor pendaftaran : ";
			cin >> no;
			for (int i = 0; i < n; i++){
				if (data[i].mhs.noPendaftaran == no){
					cout << "===== INFORMASI UKT =====" << endl;
					cout << "Nomor Pendaftaran 		: " << data[i].mhs.noPendaftaran << endl;
					cout << "Nama Mahasiswa 		: " << data[i].mhs.nama << endl;
					cout << fixed << setprecision(0);
					cout << "Penghasilan Orangtua 	: " << data[i].ukt.penghasilanOrtu << endl;
					cout << "Status KIP 			: " << data[i].jalur.kip << endl;
					ukt(&data[i].jalur.kip, &data[i].ukt.penghasilanOrtu);
					ketemu = true;
					}
				}
			if (!ketemu){
				cout << endl << "Nomor Pendaftaran Tidak Ditemukan!" << endl;
			}
			}
		break;
        default:
            cout << "\nMenu tidak tersedia!\n";
        }
        
	if (menu == 5){
			system ("cls");
			cout << "Keluar dari Program...";
			exit = true;
			} else {
				cout << "Kembali ke Menu Utama (y/n)? ";
				cin >> out;
				system ("cls");
				if (out == 'n' || out == 'N') {
					
					cout << "Selamat Tinggal!" << endl;
					exit = true;
				}
			}
	
    } while (exit == false);

    return 0;
}

