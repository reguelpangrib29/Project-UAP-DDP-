#include <iostream>
#include <conio.h>   //penggeseran kursor ke posisi tertentu pada layar
#include <stdlib.h>  //perhentian program
#include <windows.h>  //animasi teks

//Pendeklarasian area permainan
#define batas_atas 2 //batas_atas game
#define batas_bawah 23 //batas_bawah_game
#define batas_samping_kiri 2 // batas samping kiri game
#define batas_samping_kanan 78 //batas samping kanan game

using namespace std;

//Pendeklarasian variabel
int X(5), Y(5);  
int X1(4), Y1 (4);
int DelX(3), DelY(3);   //menghapus karakter posisi X dan Y
int SpeedX(1), SpeedY(0);   //mengatur kecepatan posisi X dan Y
int tailX[100], tailY[100]; //menyimpan posisi koordinat ekor

int nTail = 3;  //pengaturan ekor
int makX, makY; //maksimum X dan maksimum Y

void gotoxy (int x, int y)  //memindahkan cursor pada console nya
{
    COORD snake = {x , y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), snake);
}

void up ()
{
    SpeedY = -1; //kecepatan Y menjadi ke atas
    SpeedX = 0; //kecepatan X akan dinolkan 
}

void down ()
{
    SpeedY = 1; //kecepatan Y menjadi ke bawah
    SpeedX = 0; //kecepatan X akan dinolkan
}

void left ()
{
    SpeedX = -1; //kecepatan X menjadi ke kiri
    SpeedY = 0;  //kecepatan Y akan dinolkan
}

void right ()
{
    SpeedX = 1; //kecepatan X menjadi ke kanan
    SpeedY = 0; //kecepatan Y akan dinolkan 
}

void Del ()
{
    gotoxy(DelX,DelY);  //menghapus beberapa bagian yang dilewati X dan Y
    cout << " ";
}

void tail ()
{
    for (int j = 0; j <= 2; j++){	 
        gotoxy(tailX[j], tailY[j]);
        cout << "*";
    }
}

void show ()
{
    gotoxy(X,Y); // X dan Y adalah posisi gambar kepala
    cout << "O"; //gambar kepala
    gotoxy(makX, makY); //posisi makanan random
    cout << "@"; //gambar makanan 
}

void change_position () //mengganti posisi dari ekor - ekor snake
{
    DelX = tailX[nTail - 1];
    DelY = tailY[nTail - 1];
    for(int j = nTail - 1; j >= 1; j--){
        tailX[j] = tailX[j - 1];
        tailY[j] = tailY[j - 1];
    }
        tailX[0] = X;
        tailY[0] = Y;
}

void speed () //fungsi untuk melakukan update posisi snake sesuai tombol yang ditekan
{
    change_position();
    Del();
    X += SpeedX;
    Y += SpeedY;

    show();
    tail();
}

bool isDestroy () //fungsi menghapus kepala snake yang tersisa jika membentur dinding
{
    if(X == batas_samping_kanan){
        X = 3;
        gotoxy(78, Y);
        cout << " ";
    }
    if(X == batas_samping_kiri){
        X = 77;
        gotoxy(2, Y);
        cout << " ";
    }
    if(Y == batas_atas){
        Y = 22;
        gotoxy(X, 2);
        cout << " ";
    }
    if(Y == batas_bawah){
        Y = 3;
        gotoxy(X, 23);
        cout << " ";
    }

for (int j = 0; j <= nTail - 1; j++)
    if(tailX[j] == X && tailY[j] == Y) return true;
   return false;
    }


char getkey() //fungsi untuk mendapatkan tombol yang ditekan
{
    for(int i = 8; i <= 222; i++){
        if(GetAsyncKeyState(i) == -32767){
            switch(i)
            {
                case 38 : if(SpeedY != 1)up();
                break; //jika tombol yang ditekan adalah atas
                case 40 : if(SpeedY != -1)down();
                break; //jika tombol yang ditekan adalah bawah
                case 37 : if(SpeedX != 1)left();
                break; //jika tombol yang ditekan adalah kiri
                case 39 : if(SpeedX != -1)right();
                break; //jika tombol yang ditekan adalah kanan
            }
        }
    }
}

void random_food()
{
    makX = rand () % (batas_samping_kanan - 1);
    if(makX < 4)makX += 3 + (4-makX); //mencegah agar makanan tidak diluar batas
    makY = rand()%(batas_bawah - 1);
    if(makY < 4) makY += 3 + (4-makY);
    gotoxy(makX, makY);
    cout << "*";
}

bool isEaten ()
{
    if(X == makX && Y == makY)
    {
        return true;
    }else{
        return false;
    }
        
}

void Border () //fungsi untuk membuat garis tepi game
{
    for(int i = 1; i <= 78; i++){
        for(int j = 1; j <= 24; j+= 23){
            if(j > 1 || i >= 32){
                gotoxy(i , j);
                cout << "#";
            }
        }
    }
    for(int i = 1; i <= 24; i++){
        for(int k = 1; k <= 80; k += 78){
            gotoxy(k, i);
            cout << "#";
        }
    }
}

void score ()  //untuk penulisan skor
{
    gotoxy(3,1); cout << "Skor : ";
    gotoxy(19,1); cout << "Panjang : ";
}

void write_score ()  //untuk menulis skor terbaru dan panjang dari snake
{
    gotoxy(11,1);
    cout << (nTail - 3) * 10;
    gotoxy(29,1);
    cout << nTail;
}

void initialization ()  //fungsi yang menjalankan beberapa fungsi yang berjalan pada awal program
{
    Border();   //pinggiran game
    random_food();  //peletakan makanan secara random
    score();  //penulisan score di tepi atas 
    write_score();  //menulis skor
}

int main()
{
    system("cls");  //membersihkan layar
    initialization();  //menjalankan inisialisasi

    while(!(isDestroy())){     //selama snake belum rusak atau kalah
        speed();  //perubahan posisi snake berdasarkan kecepatan X dan Y
        getkey();  //mendapatkan tombol yang ditekan user dan menjalankan beberapa fungsi perulangan 
    
    if(isEaten()){     //mengecek makanan apakah telah dilalap oleh snake
        nTail += 3;    //panjang ekor ditambah tiga 
        random_food();  //makanan diletakkan lagi
        write_score();  //skor diupdate
    }
    Sleep(40 - (nTail / 10));   //delay yang semakin cepat dengan penambahan ekor 
    }
system("cls");  //layar telah bersihkan 
gotoxy(32, 12); cout << "Score : " << (nTail - 3) * 10;   //ditampilkan skor

//Pembuatan credits game
gotoxy(2,1);
cout<< "Kreator : ";
gotoxy(2,2);
cout<< "Moza Surya Putra (2217051014)";
gotoxy(2,3);
cout<< "Reguel Andreas A. Pangaribuan (2217051084)";
gotoxy(2,4);
cout<< "Kemas M. Aryadary Rasyad (2217051125)";
gotoxy(24, 14);
cout<< "Anda telah melakukan yang terbaik :D";
gotoxy(25, 18);
system("pause");  //game selesai
    
}
