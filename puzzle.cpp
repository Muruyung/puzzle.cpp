#include <iostream> //-----------------------------------Standard i/o bahasa C++
#include <stdio.h> //------------------------------------Standard i/o bahasa C
#include <conio.h> //------------------------------------Untuk dapat menggunakan getch()
#include <stdlib.h> //-----------------------------------Untuk dapat mengguanakan random
#include <time.h> //-------------------------------------Untuk dapat menggunakan time()
#include <windows.h> //----------------------------------Untuk dapat menggunakan system("cls")

using namespace std;

int nilai; //--------------------------------------------Untuk counter langkah

// Tipe data untuk isi puzzle
typedef struct{
  int isi[25];
}puzzle;

// Fungsi untuk memmulai permainan
int play(int n, puzzle kotak, int hasil){ //--n sebagai ukuran puzzle, kotak sebagai isi puzzle, hasil sebagai best move level
  int c,d,e; //-------------------------------c dan d sebagai iterasi looping, e sebagai boolean
  int x,y; //---------------------------------sebagai koordinat kotak kosong
  int cursor; //------------------------------untuk menggerakan puzzle
  e = 1; //-----------------------------------kondisi true

  system("cls"); //---------------------------Untuk menghapus tampilan cmd

  // Membuat tampilan score
  cout << "Move : " << nilai << " move      Best Move : " << hasil << " move"<< endl;

  // Looping untuk membuat pola puzzle
  for (c = 0 ; c < n ; c++){
    for (d = 0 ; d < (4*n)+(n+1) ; d++){
      if (d % 5 != 0){
        cout << '-';
      }else{
        cout << '+';
      }
    }
    cout << endl;

    // Loopiing untuk mencetak isi puzzle
    for (d = c*n ; d < (c*n)+n ; d++){
      // Kondisi jika angka 1 digit
      if (kotak.isi[d] != 0 && kotak.isi[d]/10 == 0){
        printf("| %d  ", kotak.isi[d]);
      }else

      // Kondisi jika angka 2 digit
      if (kotak.isi[d] != 0 && kotak.isi[d]/10 != 0){
        printf("| %d ", kotak.isi[d]);
      }else{ // Kondisi jika tabel kosong
        cout << "|    ";
        // Menyimpan kordinat kotak kosong pada puzzle
        x = (d % n)+1;
        y = (d / n)+1;
      }
    }
    cout << "|\n";
  }
  for (d = 0 ; d < (4*n)+(n+1) ; d++){
    if (d % 5 != 0){
      cout << '-';
    }else{
      cout << '+';
    }
  }

  // Sebagai intruksi permainan
  printf("\n(Gunakan w/a/s/d untuk menggerakan puzzle)\n\nPress 'ESC' for exit, press n for return to menu.");

  // Loopiing untuk mengecek susunan angka pada puzzle
  for (c = 0 ; c < (n*n)-1 ; c++){

    // Kondisi jika masih belum tersusun
    if (kotak.isi[c] != c+1){
      e = 0;
      c = n*n;
    }
  }

  // Kondisi jika sudah tersusun, maka rekursif berhenti
  if (e == 1){
    return 1;
  }else{ // Kondisi jika masih belum tersusun, maka melakukan rekursif
    cursor = getch(); //----------------------------------------------Untuk membaca inputan keyboard tanpa menggunakan enter

    // Kondisi untuk menggerakan puzzle ke atas
    if ((char)cursor == 'w' || (char)cursor == 'W'){
      // Kondisi jika letak kotak kosong bukan di paling bawah
      if (y != n){
        x--;
        y--;
        kotak.isi[(n*y)+x] = kotak.isi[(n*y)+x+n];
        kotak.isi[(n*y)+x+n] = 0;
        nilai++; //--------------------------------------------------Counter langkah pemain
      }
    }else

    // Kondisi untuk menggerakan puzzle ke bawah
    if ((char)cursor == 's' || (char)cursor == 'S'){
      // Kondisi jika letak kotak kosong bukan paling atas
      if (y != 1){
        x--;
        y--;
        kotak.isi[(n*y)+x] = kotak.isi[(n*y)+x-n];
        kotak.isi[(n*y)+x-n] = 0;
        nilai++; //--------------------------------------------------Counter langkah pemain
      }
    }else

    // Kondisi untuk menggerakan puzzle ke kiri
    if ((char)cursor == 'a' || (char)cursor == 'A'){
      // Kondisi jika letak kotak kosong bukan paling kanan
      if (x != n){
        x--;
        y--;
        kotak.isi[(n*y)+x] = kotak.isi[(n*y)+x+1];
        kotak.isi[(n*y)+x+1] = 0;
        nilai++; //--------------------------------------------------Counter langkah pemain
      }
    }else

    // Kondisi untuk menggerakan puzzle ke kanan
    if ((char)cursor == 'd' || (char)cursor == 'D'){
      // Kondisi jika letak kotak kosong bukan paling kiri
      if (x != 1){
        x--;
        y--;
        kotak.isi[(n*y)+x] = kotak.isi[(n*y)+x-1];
        kotak.isi[(n*y)+x-1] = 0;
        nilai++; //--------------------------------------------------Counter langkah pemain
      }
    }else

    // Kondisi jika pemain memberhentikan permainan
    if ((char)cursor == 'n' || (char)cursor == 'N' || cursor == 27){
      return cursor;
    }
    play(n,kotak,hasil); //-----,hasil[]-------------------------------------Melakukan rekursif
  }
}

int main(){
  puzzle kotak; //---------------------------------------------------Deklarasi typedef struct
  int c,d; //--------------------------------------------------------Sebagai iterasi looping
  int menu; //-------------------------------------------------------Sebagai menu permainan
  int hasil[3]; //---------------------------------------------------Menampung best move setiap level

  // Read file best move setiap level
  FILE *in;
  in = fopen("highs.dat","r");

  // Kondisi jika sudah ada record file
  if (in){
    c = 0;

    // Menampung best move setiap level
    while(!feof(in)){
      fscanf(in,"%d",&hasil[c]);
      c++;
    }
  }else{ // Kondisi jika belum ada record best move

    // Menginisialisasi hasil sebagai nol
    for (c = 0 ; c < 3 ; c++){
      hasil[c] = 0;
    }
  }
  fclose(in);
  do{
    nilai = 0; //---------------------------------------------------------------Menginisialisasi nilai sebagai nol

    // Menghapus tampilan cmd
    system("cls");

    // Membuat menu awal game
    cout << "Pilih Level :\n1. Easy\n2. Medium\n3. Hard\n4. Best Move\n5. Reset Game\n\n(Press 'ESC' for exit)";
    menu = getch(); //----------------------------------------------------------Memilih menu

    // Kondisi untuk menu-menu
    switch (menu){

      // Kondisi jika menekan menu '1'
      case 49:
        srand(time(0)); //------------------------------------------------------Agar angka random setiap detik nya

        // Membuat angka random
        for (c = 0 ; c < 9 ; c++){
          d = 0;
          kotak.isi[c] = rand()%9; //-------------------------------------------Membuat random angka

          // Looping agar tidak ada angka yang sama ketika di random kan
          while(d < c){

            // Kondisi jika terdapat angka yang sama ketika di random kan, maka random kembali
            if (kotak.isi[c] == kotak.isi[d]){
              kotak.isi[c] = rand()%9;
              d = 0;
            }else{
              d++;
            }
          }
        }
        system("cls");
        cout << "Pilih Mode : \n1. Ganjil\n2. Genap\n3. Normal\n";

        menu = getch();
        switch (menu) {
          // Kondisi jika memilih ganjil
          case 49:
            for (c = 0 ; c < 9 ; c++){
              kotak.isi[c] *= 2; //-------------------------------------------------D kali dua agar angka menjadi genap
              if (kotak.isi[c] != 0){
                kotak.isi[c] -= 1; //-----------------------------------------------Dikurang satu agar menjadi ganjili
              }
            }
            menu = play(3,kotak,hasil[0]); //---------------------------------------Masuk ke dalam permainan
            break;

          // Kondisi jika memilih genap
          case 50:
            for (c = 0 ; c < 9 ; c++){
              kotak.isi[c] *= 2; //-------------------------------------------------Dikali dua agar menjadi genap
            }
            menu = play(3,kotak,hasil[0]); //---------------------------------------Masuk ke dalam permainan
            break;

          // Kondisi jika angka biasa
          case 51:
            menu = play(3,kotak,hasil[0]); //---------------------------------------Masuk ke dalam permainan
            break;

          // Kondisi jika memilih exit
          case 27:
            break;

          default:
            printf("Error!\n");

        }


        // Kondisi jika pemain berhasil menyelesaikan puzzle
        if (menu == 1){
          cout << "Selamat berhasil...\n";

          // Kondisi jika pemain berhasil memecahkan record
          if (nilai < hasil[0] || hasil[0] == 0){
            hasil[0] = nilai;
            printf("Best Move : %d move\n", nilai);
          }
        }else

        // Kondisi jika pemain menyerah atau memberhentikan permainan sebelum selesai
        if ((char)menu == 'n' || (char)menu == 'N'){
          cout << "Game Over...\n";
        }
        menu = getch();
        break;

      // Kondisi jika menekan menu '2'
      case 50:
        srand(time(0)); //------------------------------------------------------Agar angka random setiap detik nya

        // Membuat angka random
        for (c = 0 ; c < 16 ; c++){
          d = 0;
          kotak.isi[c] = rand()%16; //------------------------------------------Membuat random angka

          // Looping agar tidak ada angka yang sama ketika di random kan
          while(d < c){

            // Kondisi jika terdapat angka yang sama ketika di random kan, maka random kembali
            if (kotak.isi[c] == kotak.isi[d]){
              kotak.isi[c] = rand()%16;
              d = 0;
            }else{
              d++;
            }
          }
        }
        system("cls");
        cout << "Pilih Mode : \n1. Ganjil\n2. Genap\n3. Normal\n";

        menu = getch();
        switch (menu) {
          // Kondisi jika memilih ganjil
          case 49:
            for (c = 0 ; c < 16 ; c++){
              kotak.isi[c] *= 2; //-------------------------------------------------Dikali dua agar angka menjadi genap
              if (kotak.isi[c] != 0){
                kotak.isi[c] -= 1; //-----------------------------------------------Dikurangi satu agar menjadi ganjil
              }
            }
            menu = play(4,kotak,hasil[1]); //---------------------------------------Masuk ke dalam permainan
            break;

          // Kondisi jika memilih genap
          case 50:
            for (c = 0 ; c < 16 ; c++){
              kotak.isi[c] *= 2; //-------------------------------------------------Dikali dua agar menjadi genap
            }
            menu = play(4,kotak,hasil[1]); //---------------------------------------Masuk ke dalam permainan
            break;

          // Kondisi jika angka biasa
          case 51:
            menu = play(4,kotak,hasil[1]); //---------------------------------------Masuk ke dalam permainan
            break;

          // Kondisi jika memilih exit
          case 27:
            break;

          default:
            printf("Error!\n");

        }

        // Kondisi jika pemain berhasil menyelesaikan puzzle
        if (menu == 1){
          cout << "Selamat berhasil...\n";

          // Kondisi jika pemain berhasil memecahkan record
          if (nilai < hasil[1] || hasil[1] == 0){
            hasil[1] = nilai;
            printf("Best Move : %d move\n", nilai);
          }
        }else

        // Kondisi jika pemain menyerah atau memberhentikan permainan sebelum selesai
        if ((char)menu == 'n' || (char)menu == 'N'){
          cout << "Game Over...\n";
        }
        menu = getch();
        break;

      // Kondisi jika menekan menu '3'
      case 51:
        srand(time(0)); //------------------------------------------------------Agar angka random setiap detik nya

        // Membuat angka random
        for (c = 0 ; c < 25 ; c++){
          d = 0;
          kotak.isi[c] = rand()%25; //------------------------------------------Membuat random angka

          // Looping agar tidak ada angka yang sama ketika di random kan
          while(d < c){

            // Kondisi jika terdapat angka yang sama ketika di random kan, maka random kembali
            if (kotak.isi[c] == kotak.isi[d]){
              kotak.isi[c] = rand()%25;
              d = 0;
            }else{
              d++;
            }
          }
        }
        system("cls");
        cout << "Pilih Mode : \n1. Ganjil\n2. Genap\n3. Normal\n";

        menu = getch();
        switch (menu) {
          // Kondisi jika memilih ganjil
          case 49:
            for (c = 0 ; c < 25 ; c++){
              kotak.isi[c] *= 2; //-------------------------------------------------Dikali dua agar angka menjadi genap
              if (kotak.isi[c] != 0){
                kotak.isi[c] -= 1; //-----------------------------------------------Dikurangi satu agar menjadi ganjil
              }
            }
            menu = play(5,kotak,hasil[2]); //---------------------------------------Masuk ke dalam permainan
            break;

          // Kondisi jika memilih genap
          case 50:
            for (c = 0 ; c < 25 ; c++){
              kotak.isi[c] *= 2; //-------------------------------------------------Dikali dua agar menjadi genap
            }
            menu = play(5,kotak,hasil[2]); //---------------------------------------Masuk ke dalam permainan
            break;

          // Kondisi jika angka biasa
          case 51:
            menu = play(5,kotak,hasil[2]); //---------------------------------------Masuk ke dalam permainan
            break;

          // Kondisi jika memilih exit
          case 27:
            break;

          default:
            printf("Error!\n");

        }

        // Kondisi jika pemain berhasil menyelesaikan puzzle
        if (menu == 1){
          cout << "Selamat berhasil...\n";

          // Kondisi jika pemain berhasil memecahkan record
          if (nilai < hasil[2] || hasil[2] == 0){
            hasil[2] = nilai;
            printf("Best Move : %d move\n", nilai);
          }
        }else

        // Kondisi jika pemain menyerah atau memberhentikan permainan sebelum selesai
        if ((char)menu == 'n' || (char)menu == 'N'){
          cout << "Game Over...\n";
        }
        menu = getch();
        break;

      // Kondisi jika menekan menu '4'
      case 52:
        system("cls"); //-------------------------------------------------------Menghapus tampilan cmd
        cout << "Easy   : " << hasil[0] << " move."<< endl; //------------------Menampilkan best move level easy
        cout << "Medium : " << hasil[1] << " move."<< endl; //------------------Menampilkan best move level medium
        cout << "Hard   : " << hasil[2] << " move."<< endl; //------------------Menampilkan best move level hard
        menu = getch();
        break;

      // Kondisi jika menekan menu '5'
      case 53:
        system("cls");
        printf("Anda yakin? (y/n)\n");
        menu = getch();
        switch ((char)menu) {
          case 'y':
            // Menghapus record
            for (c = 0 ; c < 3 ; c++){
              hasil[c] = 0;
            }
            break;

          case 'n':
            break;

          default :
            printf("\aError %c input\n", (char)menu);
        }

      // Kondisi jika menekan menu 'ESC'
      case 27:
        break;

      // Kondisi jika user memasukkan input yang tidak ada menu nya
      default:
        printf("\a\nError input %c for menu.\n", (char)menu);
        menu = getch();
    }
  }while(menu != 27); //--------------------------------------------------------Melakukan loping selama user tidak menekan menu keluar

  // Melakukan sequential file untuk menyimpan record permainan
  in = fopen("highs.dat","w");
  for (c = 0 ; c < 3 ; c++){
    fprintf(in, "%d\n", hasil[c]);
  }
  fclose(in);
  system("cls"); //-------------------------------------------------------------Menghapus tampilan cmd
  return 0;
}
