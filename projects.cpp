#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <windows.h>
#include <conio.h>
using namespace std;
//Global Variables

//Product structure
struct prod{
    int id,cnt;
    char name[100];
    double rate;
} product;

//Add New Products
class addProduct{
public:
    //Adding Products to the main list
    void add_Products(FILE *f){
        char add_again = 'y';
        while(add_again == 'y' || add_again == 'Y'){

            system("cls");

            cout<<"------------------------------------------------------------\n";
            cout<<setw(36)<<"Add Products\n";
            cout<<"------------------------------------------------------------\n\n";

            //Display Products
            rewind(f);
            int has_Product = 0;
            cout<<"------------------------------------------------------------\n";
            cout<<setw(5)<<"ID"<<setw(25)<<"Name"<<setw(7)<<"Count"<<setw(10)<<"Rate"<<setw(13)<<"Total($)\n";
            cout<<"------------------------------------------------------------\n";
            while(fread(&product, sizeof(product), 1, f)==1){
                has_Product = 1;
                cout<<setw(5)<<product.id<<setw(25)<<product.name<<setw(7)<<product.cnt<<setw(10)<<fixed<<setprecision(2)<<product.rate<<setw(13)<<fixed<<setprecision(2)<<(product.rate*product.cnt)<<"\n";
            }
            if(has_Product){
            cout<<"------------------------------------------------------------\n\n";
            }
            else{
                cout<<"No Entry!\n";
            }

            //Search by Product id
            cout<<"ID of the product you want to add : ";
            int pid,add_isFound = 0; cin>>pid;

            //Search Product Availability
            rewind(f);
            FILE *f2;
            f2 = fopen("temp.log","a+");

            while(fread(&product, sizeof(product), 1, f)==1){
                if(pid==product.id){
                    add_isFound = 1;

                    system("cls");

                    cout<<"------------------------------------------------------------\n";
                    cout<<setw(36)<<"Add Products\n";
                    cout<<"------------------------------------------------------------\n\n";

                    cout<<"------------------------------------------------------------\n";
                    cout<<setw(5)<<"ID"<<setw(25)<<"Name"<<setw(7)<<"Count"<<setw(10)<<"Rate"<<setw(13)<<"Total($)\n";
                    cout<<"------------------------------------------------------------\n";
                    cout<<setw(5)<<product.id<<setw(25)<<product.name<<setw(7)<<product.cnt<<setw(10)<<fixed<<setprecision(2)<<product.rate<<setw(13)<<fixed<<setprecision(2)<<(product.rate*product.cnt)<<"\n";
                    cout<<"------------------------------------------------------------\n\n";

                    cout<<"Enter the following information....\n";
                    cout<<"Amount of the Product you want to add : ";

                    int pro_count;
                    cin>>pro_count;
                    product.cnt += pro_count;

                    cout<<"New rate of the product : ";
                    cin>>product.rate;
                    fwrite(&product,sizeof(product),1,f2);
                }

                else{
                    fwrite(&product,sizeof(product),1,f2);
                }
            }

            remove("file.log"); //Removing main file.

            fclose(f2); //Closing temp.log File
            fclose(f);  //Closing file.log File
            remove("file.log");
            rename("temp.log","file.log");
            f = fopen("file.log","a+");

            if(add_isFound == 0){
                cout<<"\nThis Item is not Listed in the List.\nDo You want to add? (Y?N) : ";
                char list_product;
                cin>>list_product;
                if(list_product == 'Y' ||list_product == 'y'){
                    product.id = pid;
                    cout<<"\nID of the product : "<<product.id<<"\n";
                    fflush(stdin);
                    cout<<"Name of the product : ";
                    //fgets(product.name, 100, stdin);
                    scanf("%[^\n]s",product.name);
                    cout<<"Quantity of the product : ";
                    cin>>product.cnt;
                    cout<<"Rate of the product($) : ";
                    cin>>product.rate;
                    fwrite(&product,sizeof(product),1,f);
                }
            }

            // Add Again?
            cout<<"Do you want to add more ? (Y/N) : ";
            cin>>add_again;
        }
    }
};

//View Products Unsold Products
class viewUnsoldProd{
public:
    void view_Unsold_Product(FILE *f){
        rewind(f);
        int has_Product = 0;
        system("cls");

        cout<<"------------------------------------------------------------\n";
        cout<<setw(39)<<"Remaining Products\n";
        cout<<"------------------------------------------------------------\n\n";
        cout<<"------------------------------------------------------------\n";
        cout<<setw(5)<<"ID"<<setw(25)<<"Name"<<setw(7)<<"Count"<<setw(10)<<"Rate"<<setw(13)<<"Total($)\n";
        cout<<"------------------------------------------------------------\n";
        while(fread(&product, sizeof(product), 1, f)==1){
            has_Product = 1;
            cout<<setw(5)<<product.id<<setw(25)<<product.name<<setw(7)<<product.cnt<<setw(10)<<fixed<<setprecision(2)<<product.rate<<setw(13)<<fixed<<setprecision(2)<<(product.rate*product.cnt)<<"\n";
        }
        if(has_Product){
        cout<<"------------------------------------------------------------\n\n";
        }
        else{
            cout<<"No Entry!\n";
        }
        cout<<"Enter Any Key to return main menu....";
        getch();
    }
};
class mainMenu: public addProduct,viewUnsoldProd{
public:
    mainMenu(FILE *f){
        while(1){
            system("cls");

            //Main Menu
            cout<<"------------------------------------------------------------\n";
            cout<<setw(36)<<"Welcome Home\n";
            cout<<"------------------------------------------------------------\n";
            cout<<"[1] ---------- Add Products\n";
            cout<<"[2] ---------- Sell Products\n";
            cout<<"[3] ---------- View Sold Products\n";
            cout<<"[4] ---------- View Unsold Products\n";
            cout<<"[0] ---------- Exit Programm\n";
            cout<<"------------------------------------------------------------\n\n";

            //Choosing from main menu;
            cout<<"Enter Your Choice : ";
            int main_Menu_opt;
            cin>>main_Menu_opt;

            //switch using main menu options
            switch(main_Menu_opt){
                case 1:{
                    add_Products(f);
                    break;
                }
                case 2:{
                    //sell_Product(f);
                    break;
                }
                case 3:{
                    //view_Sold_Product(fs);
                    break;
                }
                case 4:{
                    view_Unsold_Product(f);
                    break;
                }
                case 0:{
                    cout<<"-----------------------------**-----------------------------\n\n";
                    exit(1);
                }
                default:{
                    cout<<"Wrong Option Selected!\nDouble Press Any Key to continue to Main Manu...";
                    getch();
                }
            }
            //getch();
        }
    }
};
int main(){
    FILE *f;
    f = fopen("file.log","a+");
    mainMenu mainMenu(f);
    fclose(f);
}
