/* 
VENDING MACHINE SIMULATOR
CREATED BY LIFESTREAM
KELOMPOK 7 TIG PEMDAS
MEMBER:
-NIKOLAS TIAR BANJARNAHOR (25051204056)
-HABIBI
-MUHAMMAD NUR FAJRI
-HAZQI
*/
#include <iostream> //basic io for terminal
#include <fstream> //file handling for write/read
#include <string> //getline and string handling
using namespace std;

//global variables
const int MAX = 9;
int Wallet = 20000;    //buyer's wallet
int profitMoney, pilihan;   // Mr. Krabs : Money! | global var 
string Nama_Item, Jumlah_Item, Harga_Item; //for ifstream
struct structItem { 
    string Nama;
    int Jumlah;
    int Harga;
} Vending[MAX], Storage[MAX]; //Item[] for stocks inside Vending machine, Storage[] for stocks inside Warehouse / Storage

//Function declarations
void Menu();    //Usable
void BuyVending(int pilihan);
void BuyStorage(int pilihan);
void Restock(int pilihan);
void StockView(structItem arr[], char confirm);

void read(ifstream &yap, structItem arr[]); //Technical 
bool getConfirmation(string message);
void Pilih();
bool isValidInt(int &input);

//main program
int main() {
    ifstream profit ("Profit.txt"), 
    VendingMachine ("Stock.txt"), 
    Warehouse ("Storage.txt"); // initialize data from file,  for profit, structItem for stock,
    
    profit >> profitMoney; //get the line for MONEYYYYYY
    profit.close();
    read(VendingMachine, Vending);
    VendingMachine.close();
    read(Warehouse, Storage);
    Warehouse.close();
    
    Menu();
    cout << "\nGoodbye!\n"; //After Exiting menu, give Exit messages
}

//Function definitions
//Backend stuff                                               data type 'struct' name ~~~~~v         v~~~~~ struct call variable
void read(ifstream &yap, structItem arr[]) { //Read the content of Stock / Storage .txt, structItem arr[] | ifstream &yap
    for (int i = 0; i < MAX; i++) {                                                                         //        ^~~~~~  takes ifstream variable by reference 
        getline(yap, Nama_Item);     //format .txt    =   Nama Item\n 
        getline(yap, Jumlah_Item);   //                   Jumlah\n
        getline(yap, Harga_Item);    //                   Harga\n
        arr[i].Nama = Nama_Item;
        arr[i].Jumlah = stoi(Jumlah_Item);
        arr[i].Harga = stoi(Harga_Item);
    }
}

bool getConfirmation(string message) {
    cout << message << " (y/n) : ";
    char confirm;
    cin >> confirm;
    if (confirm == 'y' || confirm == 'Y') {
        return true;
    }
    return false;
}

void Pilih() {
    do { //pilih
        cout << "\n\nPilih barang : ";
        cin >> pilihan;
        if (!isValidInt(pilihan)) {
            cout << "\nInvalid input. Please enter a number.";
            Pilih();
            return;
        }
        if (pilihan < 0 || pilihan > MAX) cout << "\nInvalid"; //countermeasure for invalid num
    } while (pilihan < 0 || pilihan > MAX);
}

bool isValidInt(int &input) { //set &input datatype as int
    if (cin.fail()) { //check (the last cin). if input != int data type, then cin.fail() = true
        cin.clear(); //clear error flag
        cin.ignore(10000, '\n'); //discard invalid input
        return false; //if != integer, false
    }
    return true;
}


//Real stuff starts here
void Menu() {   
    cout << 
    R"(


Welcome to Lifestream's Vending machine
    
    1. Buy item
    2. View Profit
    3. Buy stock
    4. Restock
    0. Exit

What do you want to do? : )";             
    cin >> pilihan;
    cout << endl;
    if (!isValidInt(pilihan)) {
        cout << "\nInvalid input. Please enter a number.";
        Menu();
        return;
    }
    switch (pilihan) {
    case 0: //exit sometime doesnt work idk why
        return;
    case 1: //buy
        do {
            cout << "\n=== Vending Machine ===\n";
            StockView(Vending, 'y'); // 'y' for display prices
            cout << "\n0.Exit\n\nYour balance : Rp." << Wallet;
            Pilih();
            BuyVending(pilihan);
        } while (pilihan != 0);
        break;
    case 2: //view profit
        cout << "\n\nVending Machine's Profit : Rp." << profitMoney;
        Menu();
        return;
    case 3: //buystock
        do {
            cout << "\n=== Storage ===\n";
            StockView(Storage, 'y');
            cout << "[0] Exit\n\nYour balance : Rp." << profitMoney << endl;
            Pilih();
            BuyStorage(pilihan);
        } while (pilihan != 0);
        break;
    case 4: //restock
        do {
            cout << "\n=== Storage ===\n";
            StockView(Storage, 'n'); // 'n' for not display prices
            cout << "\n=== Vending Machine ===\n";
            StockView(Vending, 'n');
            cout << "[0] Exit";
            Pilih();
            Restock(pilihan);
        } while (pilihan != 0);
        break;
    
    default:
        cout << "invalid menu" << endl;
        Menu();
        return;
    }
    //save file after each menu
    //cout << "testes"; //debugging
    ofstream profit("Profit.txt"), stock("Stock.txt"), warehouse("Storage.txt");
    profit << profitMoney;
    profit.close();
    for (int i = 0; i < MAX; i++) {
        stock << Vending[i].Nama << endl << Vending[i].Jumlah << endl << Vending[i].Harga << endl;
    }
    stock.close();
    for (int i = 0; i < MAX; i++) {
        warehouse << Storage[i].Nama << endl << Storage[i].Jumlah << endl << Storage[i].Harga << endl;
    }
    warehouse.close();
    Menu(); //recursive
}

void BuyVending(int pilihan) { //buy 1 item as buyer
    if (pilihan == 0) return;
    pilihan--; //due to how array works
    if (Vending[pilihan].Jumlah == 0){
        cout << "\nNo stock.";
        return;
    }
    if (Wallet < Vending[pilihan].Harga){
        cout << "\nNot enough money.";
        return;
    }
    if (!getConfirmation("Are you sure to buy " + Vending[pilihan].Nama + "?")) {
        cout << "\nPurchase cancelled.\n\n";
        return;
    }
    Vending[pilihan].Jumlah--;
    Wallet -= Vending[pilihan].Harga;
    profitMoney += Vending[pilihan].Harga;
    cout << "Transaction completed.\nCurrent balance : " << Wallet;
}

void BuyStorage(int pilihan) { //buy stocks for storage, need specified amount
    if (pilihan == 0) return; //in case of exit
    pilihan--; //due to how array works
    if (profitMoney < Storage[pilihan].Harga){
        cout << "Not enough money.\n\n";
        return;
    }
    int amount;
    do {
        cout << "Select amount : ";
        cin >> amount;
        if (!isValidInt(amount)) {
            cout << "\n Must be a number.\n\n";
            continue;
        }
        if (amount <= 0){
            cout << "\nMust be greater than 0.\n\n";
            continue;
        }
        if (Storage[pilihan].Harga * amount > profitMoney) {
            cout << "\nNot enough money.\n\n";
        }
    } while (Storage[pilihan].Harga * amount > profitMoney || amount <= 0);
    if (!getConfirmation("Are you sure to buy " + to_string(amount) + " unit(s) of " + Storage[pilihan].Nama + " ?")) {
        cout << "\nStock purchase cancelled.\n\n";
        return;
    }   
    Storage[pilihan].Jumlah += amount;
    profitMoney -= Storage[pilihan].Harga * amount;
    cout << "\nStock purchased.\n\nCurrent balance : Rp." << profitMoney;
}

void Restock(int pilihan) { // specific number of restock
    if (pilihan == 0) return; //in case of exit
    pilihan--; //due to how array works
    if (Storage[pilihan].Nama != Vending[pilihan].Nama) {
        cout << "\nNot matching in warehouse.\n\n";
        return;
    }
    if (Vending[pilihan].Jumlah == 5) { //check first, add later. in case vending machine already full from the start
        cout << "\nVending machine full.\n\n";
        return;
    }  
    if (!getConfirmation("Are you sure to restock " + Vending[pilihan].Nama + "?")) {
        cout << "\nRestock cancelled.\n\n";
        return;
    }
    while (Vending[pilihan].Jumlah < 5) {      
        if (Storage[pilihan].Jumlah == 0) {  //check item in warehouse 
            cout << "\nOut of stock.\n\n";
            return;
        };
        Storage[pilihan].Jumlah--;
        Vending[pilihan].Jumlah++;           
    }
        cout << "Restock completed.\n";
}

void StockView(structItem arr[], char confirm){ //data is stored in struct not file, also needs confirmation whether u want to display price or not
    for (int l = 0; l < MAX; l += 3) {
        // print names with j as index
        for (int j = l; j < (l + 3); ++j) {
            cout << "[" << j + 1 << "] " << arr[j].Nama << "\t" ; // '\t' for tab spacing 
            if (arr[j].Nama.length() < 12) cout << "\t";
        }
        cout << '\n';
        // print quantities
        for (int j = l; j < (l + 3); ++j) {
            cout << arr[j].Jumlah << " left\t\t\t";
        }
        if (confirm == 'y' || confirm == 'Y') { // 'y' || 'Y' for display, else for no
            cout << "\n";
            for (int j = l; j < (l + 3); ++j) {
                cout << "Rp." << arr[j].Harga << "        \t\t";
            }
        }
        cout << "\n\n";
    }
}
