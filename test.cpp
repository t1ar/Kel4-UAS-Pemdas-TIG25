// initial test
// Kel7
// TI-G

#include <iostream>
#include <fstream> // ubah oi ubahhhh
#include <string>
using namespace std;


// declare harga
const int MAX = 9,
          Harga_User [MAX] = {},
          Harga_Seller [MAX] = {};


// declare struct
struct structItem {
    string Nama;
    int Jumlah;
} Item[MAX]; 

// declare functions


int Beli() {
    
}

void Menu(int pilihan) {

}
// main function
int main() {

    fstream profit, stock;
    int Money;   // Mr. Krabs : Money!
    string Nama_Item, Jumlah;
    profit.open("Profit.txt");
    profit >> Money; //get the line for MONEYYYYYY
    profit.close();  //dont forget to close file
    stock.open("Stock.txt");  
    for (int i = 0; i < MAX; i++) {
        getline(stock, Nama_Item);//format Stock.txt = Nama Item\n 
        getline(stock, Jumlah);   //                   Jumlah
        Item[i].Nama = Nama_Item;
        Item[i].Jumlah = stoi(Jumlah);
    }






    //dont forget to close file
    profit.close();
    stock.close();
}
