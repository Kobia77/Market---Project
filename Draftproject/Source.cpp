#include<fstream>
#include<conio.h>
#include<string.h>
#include<iomanip>
#include<iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class product
{
    int total_amount;
    int total_discount;
    int product_number;
    char product_name[50];
    float product_price, product_quantity, tax, product_discount;

public:

    void set_new()
    {


        cout << "Set Today discount !" << endl;
        cout << "Set the amount you want : " << endl;
        cin >> total_amount;

        cout << "Enter the discount you want from " << total_discount << ": " << endl;
        cin >> total_discount;
    }


    void create_product()
    {
        cout << endl << "Enter The Product Number: ";
        cin >> product_number;
        cout << endl << "Enter The Name of The Product: ";
        cin.ignore();
        cin.getline(product_name, 50);
        cout << endl << "Enter The Price of The Product: ";
        cin >> product_price;
        cout << endl << "Enter The Discount (%): ";
        cin >> product_discount;
    }

    void show_product()
    {
        cout << endl << "Product Number: " << product_number;
        cout << endl << "Product Name: " << product_name;
        cout << endl << "Product Price: " << product_price;
        cout << endl << "Discount : " << product_discount;
    }

    int getProduct()
    {
        return product_number;
    }

    float getPrice()
    {
        return product_price;
    }

    char* getName()
    {
        return product_name;
    }

    float getDiscount()
    {
        return product_discount;
    }



    int get_total_Discount()
    {
        return total_discount;
    }

    void set_discount(int dis)
    {
        total_discount = dis;

    }
    int get_total_amount()
    {
        return total_amount;
    }
    void set_total_amount(int amount)
    {
        total_amount = amount;


    }

};



fstream fp;
product pro;

void save_product()
{
    fp.open("database.dat", ios::out | ios::app);
    pro.create_product();
    fp.write((char*)&pro, sizeof(product));
    fp.close();
    cout << endl << endl << "The Product Has Been Sucessfully Created...";
    getchar();
}


void Discount_total()
{

    fp.open("database.dat", ios::out | ios::app);

    pro.set_new();
    fp.write((char*)&pro, sizeof(product));
    fp.close();

    cout << endl << endl << "The details Has Been Sucessfully Updated...";
    getchar();
}


void show_all_product()
{
    system("cls");
    cout << endl << "\t\t-------------------------------------------";
    cout << endl << "\t\tRECORDS.";
    cout << endl << "\t\t------------------------------------------\n";
    fp.open("database.dat", ios::in);
    while (fp.read((char*)&pro, sizeof(product)))
    {
        pro.show_product();
        cout << endl << "------------------------------------------\n" << endl;
        getchar();
    }
    fp.close();
}


void display_record(int num)
{
    bool found = false;
    fp.open("database.dat", ios::in);
    while (fp.read((char*)&pro, sizeof(product)))
    {
        if (pro.getProduct() == num)
        {
            system("cls");
            pro.show_product();
            found = true;
        }
    }

    fp.close();
    if (found == true)
        cout << "\n\nNo record found";
    getchar();
}



void edit_product()
{

    int num;
    bool found = false;
    system("cls");
    cout << endl << endl << "\tPlease Enter The Product #: ";
    cin >> num;

    fp.open("database.dat", ios::in | ios::out);
    while (fp.read((char*)&pro, sizeof(product)) && found == false)
    {
        if (pro.getProduct() == num)
        {
            pro.show_product();
            cout << "\nPlease Enter The New Details of Product: " << endl;
            pro.create_product();
            int pos = -1 * sizeof(pro);
            fp.seekp(pos, ios::cur);
            fp.write((char*)&pro, sizeof(product));
            cout << endl << endl << "\t Record Successfully Updated...";
            found = true;
        }
    }
    fp.close();
    if (found == false)
        cout << endl << endl << "Record Not Found...";
    getchar();
}


void delete_product()
{
    int num;
    system("cls");
    cout << endl << endl << "Please Enter The product #: ";
    cin >> num;
    fp.open("database.dat", ios::in | ios::out);
    fstream fp2;
    fp2.open("Temp.dat", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char*)&pro, sizeof(product)))
    {
        if (pro.getProduct() != num)
        {
            fp2.write((char*)&pro, sizeof(product));
        }
    }
    fp2.close();
    fp.close();
    remove("database.dat");
    rename("Temp.dat", "database.dat");
    cout << endl << endl << "\tRecord Deleted...";
    getchar();
}


void product_menu()
{
    system("cls");
    fp.open("database.dat", ios::in);

    cout << endl << endl << "\t\tProduct MENU\n\n";
    cout << "-----------------------------------------------------\n";
    cout << "P.NO.\t\tNAME\t\tPRICE\n";
    cout << "-----------------------------------------------------\n";
    while (fp.read((char*)&pro, sizeof(product)))
    {
        cout << pro.getProduct() << "\t\t" << pro.getName() << "\t\t" << pro.getPrice() << endl;
    }
    fp.close();
}

float Charityfunc(float total)
{
    string tmp;
    int cha = 0;
    cout << "\n\nHow much do you want to donate?" << endl;
    cin >> cha;
    cout << "\n\nWhich association do you want to donate for? " << endl;
    cin >> tmp;
    total += cha;
    cout << "\n\n" << cha << " Shekels charge for " << tmp << ":)\n" << endl;
    return total;
}

float lucky_func(int total)
{
    //system("cls");
    int prize;
    int pick_choise;
    cout << "****Lets see how much lucky you have today sir**** \n\n";
    cout << "Which lucky card are you interested in?" << endl << "(1)*regular* ticket= 10 ILS" << endl << "(2)**special ticket** = 50 ILS" << "(3)else: Return Menu" << endl;
    cin >> pick_choise;
    if (pick_choise == 1)
    {
        total += 10;
        cout << "You'v been charged 10 [ILS]-----done" << endl;
        cout << "Regular ticket for you:" << endl << " You may win up to 50 ILS---->lets roll " << endl;

        prize = (rand() % 50);
        cout << "YOU WON : " << prize << " [ILS]" << endl;
        total -= prize;
        return total;
    }
    if (pick_choise == 2)
    {
        total += 50;
        cout << "You'v been charged 50 [ILS]-----done" << endl;
        cout << "Special ticket for you:" << endl << "you may win up to 100 ILS---->lets roll " << endl;

        prize = (rand() % 100);
        cout << "YOU WON : " << prize << endl;
        total -= prize;
        return total;
    }
    else
        return total;


}

float coin_change(int total)
{
    int pick_coin = 0;
    float new_total = 0;
    cout << "Which coin do want to pay with?" << endl;
    cout << "1.EUR  \n2.USD ($) \n3.GBP \n------pick a number------" << endl;
    cin >> pick_coin;
    if (pick_coin == 1) {
        cout << "Calculate to EUR:\n" << endl;
        cout << "Price in ILS:" << total << endl;
        new_total = total * 0.2729;
        return new_total;
    }
    if (pick_coin == 2) {
        cout << "Calculate to USD:\n" << endl;
        cout << "Price in ILS:" << total << endl;
        new_total = total * 0.2903;
        return new_total;
    }
    if (pick_coin == 3) {
        cout << "Calculate to GBP:\n" << endl;
        cout << "Price in ILS:" << total << endl;
        new_total = total * 0.2369;
        return new_total;
    }



}



void place_order()
{
    int order_arr[50], quan[50], c = 0;
    float amt, damt, total = 0, New_total;
    char ch = 'Y';
    char donate, lucky_pick, choice;
    product_menu();
    cout << "\n------------------------------------------------";
    cout << "\n PLACE YOUR ORDER";
    cout << "\n------------------------------------------------\n";
    do
    {
        cout << "\n\nEnter The Product number: ";
        cin >> order_arr[c];
        cout << "\nQuantity: ";
        cin >> quan[c];
        c++;

        cout << "\nDo You Want To Order Another Product ? (y/n)";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');



    cout << "\n\nFeeling lucky for lucky coupons? (y/n)" << endl;
    cin >> lucky_pick;
    if (lucky_pick == 'Y' || lucky_pick == 'y')
        total = lucky_func(total);
    else
        cout << "\n\nMaybe next time kido " << endl;


    getchar();
    //system("cls");
    cout << "\n\n--------------INVOICE-----------------------\n";
    cout << "\nPr No.\tPr Name\tQuantity \tPrice \tAmount \tAmount after discount\n";
    for (int x = 0; x <= c; x++)
    {
        fp.open("database.dat", ios::in);
        fp.read((char*)&pro, sizeof(product));
        while (!fp.eof())
        {
            if (pro.getProduct() == order_arr[x])
            {
                amt = pro.getPrice() * quan[x];
                damt = amt - (amt * pro.getDiscount() / 100);
                cout << "\n" << order_arr[x] << "\t" << pro.getName() << "\t" << quan[x] << "\t\t" << pro.getPrice() << "\t" << amt << "\t\t" << damt;
                total += damt;
            }
            fp.read((char*)&pro, sizeof(product));
        }
        fp.close();
    }
    cout << "\n\nDo you want to donate for charity? (y/n)" << endl;
    cin >> donate;
    if (donate == 'Y' || donate == 'y')
        total = Charityfunc(total);
    else
        cout << "\n\nThank you anyways :)" << endl;

    cout << "\n\nDo you want to pay with another coins? (y/n)" << endl;
    cin >> choice;



    if (choice == 'Y' || choice == 'y')
    {

        if (pro.get_total_amount() <= total)
        {
            cout << "You have the terms for the discount !!!" << endl;
            float percentege = 0;
            percentege = (total * pro.get_total_Discount()) / 100;
            total -= percentege;
            cout << "\n\n\t\t\t\t\tTOTAL = " << total << endl;


        }
        else
        {
            cout << "You are not have the terms to get the discount !" << endl;
        }

        New_total = coin_change(total);
        cout << "\n\n\t\t\t\t\tTOTAL = " << New_total << endl;
        getchar();

    }
    else
    {

        if (pro.get_total_amount() <= total)
        {
            cout << "You have the terms for the discount !!!" << endl;
            float percentege = 0;
            percentege = (total * pro.get_total_Discount()) / 100;
            total -= percentege;
            cout << "\n\n\t\t\t\t\tTOTAL = " << total;

        }
        else
        {
            cout << "You are not have the terms to get the discount !" << endl;

        }

    }

}



void admin_menu()
{
    system("cls");
    int option;
    cout << "\t------------------------------------------";
    cout << "\n\tPress 1 to CREATE PRODUCT";
    cout << "\n\tPress 2 to DISPLAY ALL PRODUCTS";
    cout << "\n\tPress 3 to QUERY ";
    cout << "\n\tPress 4 to MODIFY PRODUCT";
    cout << "\n\tPress 5 to DELETE PRODUCT";
    cout << "\n\tPress 6 to Set Today discounts ";
    cout << "\n\tPress 7 to GO BACK TO MAIN MENU";
    cout << "\n\t-----------------------------------------";


    cout << "\n\n\tOption: ";
    cin >> option;
    switch (option)
    {
        case 1: system("cls");
            save_product();
            break;

        case 2: show_all_product();
            break;

        case 3:
            int num;
            system("cls");
            cout << "\n\n\tPlease Enter The Product Number: ";
            cin >> num;
            display_record(num);
            break;

        case 4: edit_product();
            break;

        case 5: delete_product();
            break;

        case 6:
            Discount_total();


        case 7: system("cls");
            break;

        default:admin_menu();
    }
}


int main(int argc, char* argv[])
{
    system("cls");
    int option;
    for (;;)
    {

        cout << "\n\t------------------------------------";
        cout << "\n\t1. CUSTOMER";
        cout << "\n\t2. ADMINISTRATOR";
        cout << "\n\t3. EXIT";
        cout << "\n\t------------------------------------";

        cout << "\n\tOption: ";
        cin >> option;

        switch (option)
        {
            case 1: system("cls");
                place_order();
                getchar();
                break;

            case 2: admin_menu();
                break;

            case 3:
                cout << "\n\t------------------------------------------";
                cout << "\n\tGood Bye!";
                cout << "\n\t------------------------------------------\n";
                exit(0);

            default:cout << "Invalid Input...\n";
        }

    }
}