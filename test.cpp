// initial test
// Kel7
// TI-G

#include <iostream> // test commit
#include <fstream>
#include <string>
using namespace std;

// declare harga & duit
const int MAX = 9,
          Harga_Buyer [MAX] = {},
          Harga_Stock [MAX] = {};
int Wallet = 20000;    //buyer's wallet
int Money, pilihan;   // Mr. Krabs : Money! | global var 

// declare struct
struct structItem { 
    string Nama;
    int Jumlah;
} Item[MAX], Storage[MAX]; //item dalam vending, storage dalam warehouse

// Each vending "line" (row) contains a fixed number of items (PER_LINE)
// Limit the vending layout to at most 3 lines (rows). If MAX grows, we still only show up to MAX_LINES rows.
const int PER_LINE = 3;                      // items per line (3 columns)
const int MAX_LINES = 3;                     // maximum number of rows to display
const int NUM_LINES = (MAX / PER_LINE <= MAX_LINES) ? (MAX / PER_LINE) : MAX_LINES;        // how many lines/rows we will actually use
const int EFFECTIVE_MAX = NUM_LINES * PER_LINE; // maximum selectable item index (1-based)

struct line {
    structItem* Item[PER_LINE];
};

line Lines[NUM_LINES];

void BuyStock(int pilihan) {
    if (pilihan == 0) return; //in case of exit
    pilihan--; //due to how array works
    if (Money < Harga_Stock[pilihan]){
        cout << "Not enough money.\n\n";
        return;
    }
    
    Item[pilihan].Jumlah++;
    Wallet -= Harga_Stock[pilihan];
    cout << "Restock completed.\nCurrent balance : " << Money;
}

// declare functions
void Restock(int pilihan) 
{ // specific number of restock
    
    if (pilihan == 0) return; //in case of exit
    pilihan--; //due to how array works
    cout << "Are you sure to restock " << Item[pilihan].Nama << "? (y/n) : ";
    char confirm;
    cin >> confirm;
    if (confirm != 'y' && confirm != 'Y') {
        cout << "Restock cancelled.\n\n";
        return;
    }
    if (confirm == 'y' || confirm == 'Y')
    {
        for(int i = 0; i <= 5; i++) {
            if (Storage[pilihan].Nama == Item[pilihan].Nama) {
                if (Storage[pilihan].Jumlah == 0) {
                    cout << "No stock in warehouse.\n\n";
                    return;
                }
                Storage[pilihan].Jumlah--;
                Item[pilihan].Jumlah++;
                if (Item[pilihan].Jumlah == 5) {
                    cout << "Vending machine full.\n\n";
                    return;
                }
                return;
            }
        }
        cout << "Restock completed.\n\n";
    }
}

void Beli(int pilihan) { //buy 1 item
    if (pilihan == 0) return;
    pilihan--; //due to how array works
    if (Item[pilihan].Jumlah == 0){
        cout << "No stock.\n\n";
        return;
    }
    if (Wallet < Harga_Buyer[pilihan]){
        cout << "Not enough money.\n\n";
        return;
    }
    Item[pilihan].Jumlah--;
    Wallet -= Harga_Buyer[pilihan];
    cout << "Transaction completed.\nCurrent balance : " << Wallet;
}

void StockPilih(){ //data is stored in struct not file remember, oh and at the bottom give the line "0. Exit" ;
    cout << "\n=== STOCK ===\n";
    for (int l = 0; l < MAX; ++l) {
        // print names with index
        for (int j = l; j < l + 3; ++j) {
            cout << "[" << j << "] " << Item[j].Nama << "\t";
        }
        cout << '\n';
        // print quantities
        for (int j = l; j < l + 3; ++j) {
            cout << "   " << Item[j].Jumlah << " left\t";
        }
        cout << "\n\n";
    }
                                               

    
    cout << "\n0.Exit";
    do { //pilih
        cout << "\nPilih barang : ";
        cin >> pilihan;
        if (pilihan < 0 || pilihan > MAX) cout << "\nInvalid\n"; //countermeasure
    } while (pilihan < 0 || pilihan > MAX);
}

void Menu() {
                 //give entry message
                 //user's wallet


    cin >> pilihan;
    switch (pilihan)
    {
    case 0: //exit
        return;
        break;
    case 1: //buy
                    //give entry message
        StockPilih();
        Beli(pilihan);
        break;
    case 2: //view profit
        cout << "Profit : " << Money << endl;
        Menu();
        break;
    case 3: //buystock
                //give entry message
        
    case 4: //restock
        do {
                    //give entry message
            StockPilih();
            Restock(pilihan);
        } while (pilihan != 0);
        break;
    
    default:
        cout << "invalid menu" << endl;
        Menu();
        break;
    }
    ofstream profit ("Profit.txt"), stock ("Stock.txt"), warehouse ("Storage.txt"); //save data after each menu
    profit << Money;
    profit.close();
    for (int i = 0; i < MAX; i++) {
        stock << Item[i].Nama << endl << Item[i].Jumlah << endl;
    }
    stock.close();
    for (int i = 0; i < MAX; i++) {
        warehouse << Item[i].Nama << endl << Item[i].Jumlah << endl;
    }
    warehouse.close();
    Menu(); //recursive
}
// main function
int main() {
    // initialize data from file, Money for profit, structItem for stock,
    ifstream profit ("Profit.txt"), stock ("Stock.txt"), warehouse ("Storage.txt");
    string Nama_Item, Jumlah;
    profit >> Money; //get the line for MONEYYYYYY
    profit.close();
    for (int i = 0; i < MAX; i++) {
        getline(stock, Nama_Item);//format Stock.txt = Nama Item\n 
        getline(stock, Jumlah);   //                   Jumlah
        Item[i].Nama = Nama_Item;
        Item[i].Jumlah = stoi(Jumlah);
    }
    stock.close();
    for (int i = 0; i < MAX; i++) {
        getline(warehouse, Nama_Item);//format Warehouse.txt = Nama Item\n 
        getline(warehouse, Jumlah);   //                   Jumlah
        Storage[i].Nama = Nama_Item;
        Storage[i].Jumlah = stoi(Jumlah);
    }
    warehouse.close();
    Menu();

                //give exit message
    
}
