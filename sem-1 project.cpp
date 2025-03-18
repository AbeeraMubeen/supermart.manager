#include <fstream>
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include<limits>
#include <thread>   // for sleep_for()
#include <chrono>  
#include<iomanip>
#include<sstream>
using namespace std;

//functions
void menu();
void login();
void administrator();
void buyer();
int admin_menu();
void addItem();
void editItem();
void deleteItem();
void viewItems();
void recipt();//function end
//-----------------------------------------


void menu(){//menu function start
	int choice;
	system("cls");
	cout<<"\n\t--------------------------------\n";
	cout<<"   \t SUPERMARKET MAIN MENU\n";
	cout<<"\t--------------------------------\n";
	cout<<"\t1.ADMINISTRATOR\n";
	cout<<"\t2.BUYER\n";
	cout<<"\t3.EXIT\n";
	cout<<"\tENTER YOUR CHOICE: ";
	while(true){
	cin>>choice;
	// Check if the input is an integer
        if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "\tInvalid input. Please enter a valid integer.\n";
        }//closing if of validdation check
            else if(choice<0||choice>7){
            	cout<<"\tNUMBER IS OUT OF RANGE...\n"<<"ENTER NUMBER FROM 1 TO 7\n";
			}//elseif of invalid choice
			else{
	switch(choice){//switch
		case 1:
		administrator();
		break;
		case 2:
		buyer();
		break;
		case 3:
			cout<<"\tTHANKYOU OR VISITIG!\n"<<"\tPLEASE COME AGAIN\n";
			break;
		default:
			cout<<"\tUNEXPECTED ERROR\n";
	}//switch end
	break;//break the loop if condition is false
}//else of validation
}//while of validation
}//menu closing

// Function to add an item
void addItem() {
	system("cls");
    ofstream file("supermarket_items.txt", ios::app);
    ifstream checkFile("supermarket_items.txt");
    if (!file || !checkFile) {
        cout << "Error opening file!" << endl;
        return;
    }

    while (true) {
        int itemID, quantity;
        string itemName;
        float price, discount;
        bool isUnique = false;

        // Check for unique ID
        while (!isUnique) {
            cout << "\tEnter Item ID: ";
            while (!(cin >> itemID)) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "\tInvalid input. Please enter a valid Item ID: ";
            }
            cin.ignore();

            // Reset file pointer and check for duplicate ID
            checkFile.clear();
            checkFile.seekg(0);
            int existingID;
            string tempName;
            float tempPrice;
            int tempQuantity;
            float tempDiscount;
            isUnique = true;

            while (checkFile >> existingID >> tempName >> tempPrice >> tempQuantity >> tempDiscount) {
                if (itemID == existingID) {
                    cout << "\tID already exists! Please enter a unique ID." << endl;
                    isUnique = false;
                    break;
                }
            }
        }

        cout << "\tEnter Item Name: ";
        getline(cin, itemName);

        cout << "\tEnter Item Price: ";
        while (!(cin >> price)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\tInvalid input. Please enter a valid Item Price: ";
        }

        cout << "\tEnter Item Quantity: ";
        while (!(cin >> quantity)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\tInvalid input. Please enter a valid Quantity: ";
        }

        cout << "\tEnter Item Discount (%): ";
        while (!(cin >> discount)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\tInvalid input. Please enter a valid Discount: ";
        }

        file << itemID << " " << itemName << " " << price << " " << quantity << " " << discount << endl;
        cout << "\tItem added successfully!" << endl;

        cout << "\tDo you want to add another item? (yes to continue, menu to return to Admin Menu): ";
        string choice;
        cin.ignore();
        getline(cin, choice);

        if (choice == "menu") {
            break;
        } else if (choice != "yes") {
            cout << "\tInvalid input! Returning to Admin Menu." << endl;
            break;
        }
    }

    file.close();
    checkFile.close();
}

// Function to view all items
void viewItems() {
system("cls");
	int counter=1;
    ifstream file("supermarket_items.txt");
    
    if (!file) {
        cout << "No items found!" << endl;
        return;
    }

    int itemID, quantity;
    string itemName;
    float price, discount;

    cout << "\n\tItems in Supermarket:\n";
    cout << "\ts.no\tID\tName\t\tPrice\tQuantity\tDiscount\n";
    cout << "\t---------------------------------------------------------\n";

    while (file >> itemID) {
        file.ignore();
        getline(file, itemName, ' ');
        file >> price >> quantity >> discount;
        cout <<"\t"<<counter<<"\t"<< itemID << "\t" << itemName << "\t\t" << price << "\t" << quantity << "\t\t" << discount <<"%" << endl;
        counter++;
    }
getch();
    file.close();
}
// Function to edit an item
void editItem() {
	//system("cls");
    while (true) {
        ifstream file("supermarket_items.txt");
        ofstream tempFile("temp.txt");
        if (!file || !tempFile) {
            cout << "Error opening file!" << endl;
            return;
        }

        int itemIDToEdit;
        cout << "\tEnter Item ID to Edit: ";
        while (!(cin >> itemIDToEdit)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\tInvalid input. Please enter a valid Item ID: ";
        }

        int itemID, quantity;
        string itemName;
        float price, discount;
        bool itemFound = false;

        while (file >> itemID) {
            file.ignore();
            getline(file, itemName, ' ');
            file >> price >> quantity >> discount;

            if (itemID == itemIDToEdit) {
                itemFound = true;
                cout << "\tEnter New Item Name: ";
                cin.ignore();
                getline(cin, itemName);

                cout << "\tEnter New Item Price: ";
                while (!(cin >> price)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "\tInvalid input. Please enter a valid Price: ";
                }

                cout << "\tEnter New Item Quantity: ";
                while (!(cin >> quantity)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "\tInvalid input. Please enter a valid Quantity: ";
                }

                cout << "\tEnter New Item Discount (%): ";
                while (!(cin >> discount)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "\tInvalid input. Please enter a valid Discount: ";
                }
            }

            tempFile << itemID << " " << itemName << " " << price << " " << quantity << " " << discount << endl;
        }

        file.close();
        tempFile.close();

        if (itemFound) {
            remove("supermarket_items.txt");
            rename("temp.txt", "supermarket_items.txt");
            cout << "\tItem updated successfully!" << endl;
        } else {
            remove("temp.txt");
            cout << "\tItem not found!" << endl;
        }

        cout << "\tDo you want to edit another item? (y/no): ";
        string choice;
        cin.ignore();
        getline(cin, choice);
        if (choice != "y") {
            admin_menu();
            break;
        }
    }
}

// Function to delete an item
void deleteItem() {
	system("cls");
    ifstream file("supermarket_items.txt");
    ofstream tempFile("temp.txt");
    if (!file || !tempFile) {
        cout << "Error opening file!" << endl;
        return;
    }

    int itemIDToDelete;
    cout << "\tEnter Item ID to Delete: ";
    while (!(cin >> itemIDToDelete)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\tInvalid input. Please enter a valid Item ID: ";
    }

    int itemID, quantity;
    string itemName;
    float price, discount;
    bool itemFound = false;

    while (file >> itemID) {
        file.ignore();
        getline(file, itemName, ' ');
        file >> price >> quantity >> discount;

        if (itemID == itemIDToDelete) {
            itemFound = true;
            continue; // Skip the item to be deleted
        }

        tempFile << itemID << " " << itemName << " " << price << " " << quantity << " " << discount << endl;
    }

    file.close();
    tempFile.close();

    if (itemFound) {
        remove("supermarket_items.txt");
        rename("temp.txt", "supermarket_items.txt");
        cout << "\tItem deleted successfully!" << endl;
    }
	else {
        remove("temp.txt");
        cout << "\tItem not found!" << endl;
    }
    getch();
}
//-----------------------------------------
//           LOGIN FUNCTION
//-----------------------------------------
void login() {
	system("cls");
    const string correctpassword="abeera123";
    const string correctemail="abeera@gmail.com";
    string password, email;
    int maxatt=3;
    int att=0;
    bool loggedIn=false;
    while(!loggedIn) {
        cout<<"\n\tENTER THE PASSWORD and EMAIL FOR LOGIN\n";
        for(int i=1; i<=maxatt; i++) {
            cin>>password;
            cout<<endl;
            cin>>email;
            att++;
            if(password==correctpassword&&email==correctemail) {
                cout<<"\tSUCCESSFULLY LOGGED IN\n\n";
                cout<<"\tPlease wait for few seconds\n";
                this_thread::sleep_for(std::chrono::seconds(2));
                loggedIn=true;
                break;
            } else {
                if(password!=correctpassword&&email!=correctemail) {
                    cout<<"\tINVALID PASSWORD AND EMAIL. PLEASE TRY AGAIN\n";
                } else if(email!=correctemail) {
                    cout<<"\tINCORRECT EMAIL, PLEASE TRY AGAIN\n";
                } else if(password!=correctpassword) {
                    cout<<"\tINCORRECT PASSWORD. PLEASE TRY AGAIN\n";
                }
            }
        }
        if(att>=maxatt) {
            cout<<"\tTOO MANY FAILED ATTEMPTS. NOW PLEASE WAIT FOR 5 SECONDS BEFORE RE-ENTERING THE PASSWORD\n";
            for(int i=5;i>=0;i--) {
                cout << "\t\r\tRemaining time is " << i << " ";
                this_thread::sleep_for(chrono::seconds(1));
                cout.flush();
            }
            system("cls");
            cout << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            att = 0;
        }
    }
    
}
//--------------------------------------------------
//------------------------------
void administrator(){
	int ch;
	system("cls");
login();
admin_menu();
system("cls");
cout<<"\n \tWELCOME TO ADMINISTRATIVE PAGE\n";
while(true){
	admin_menu();
	cin>>ch;
	if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "\tInvalid input. Please enter a valid integer.\n";
        }//closing if of validdation check
        else if(ch<1||ch>6){
        	
        	cout<<"\tPLEASE ENTER A NUMBER BETWEEN(1-5)\n";
		}
        else{
        	
        
			switch(ch){
	case 1:
		
		 addItem();
		break;
		case 2:
			editItem();
			break;
			case 3:
			deleteItem();
			 break;
				case 4:
				viewItems();
			    break;	
					case 5:
					cout << "\tExiting administrative page...\n";
					menu();
                    return; // Exit the function and break the loop
                default:
                    cout << "\tINVALID INPUT. Please select a number from 1-5.\n"; 
                    // Prompt the admin menu again
                    break;	
}//switch
		}//else
}//while

}//admin end

int admin_menu(){	
system("cls");	
cout<<" \n\tMENU OF ADMINISTRATIVE PAGE\n";
cout<<" \t1.ADD PRODUCT\n";
cout<<" \t2.EDIT PRODUCT\n";
cout<<" \t3.DELETE PRODUCT\n";
cout<<" \t4.VIEW PRODUCT\n";
cout<<" \t5.GOTO MAIN MENU\n";
cout<<"\tENTER YOUR CHOICE: ";
}//admin_menu function end
//--------------------------------------

void buyer() {
    system("cls");
    string email;

    while (true) {
    	cout<<"\n\tWELCOME TO BUYER FUNCTION.\n";
        cout << "\tPLease Enter your email for login: ";
        cin >> email;

        // Basic email validation
        if (email.find('@') != string::npos && email.find('.') != string::npos) {
            break; // Valid email
        }
        cout << "\tInvalid email! Please enter a valid email.\n";
    }

    float grandTotal = 0.0, totalGST = 0.0, totalDiscount = 0.0;
    const int MAX_ITEMS = 100;
    string receiptItems[MAX_ITEMS];
    int receiptIndex = 0;

    while (true) {
        // Display available items (same as before)
        ifstream file("supermarket_items.txt");
        if (!file) {
            cout << "\tError: Could not load items.\n";
            return;
        }
        cout << "\n\tAvailable Items:\n";
        cout << "\tID\tName\tPrice\tQuantity\tDiscount\n";
        cout << "\t--------------------------------------------------\n";

        int itemID, availableQuantity;
        float price, discount;
        string itemName;

        // Read and display items
        while (file >> itemID >> itemName >> price >> availableQuantity >> discount) {
            cout <<"\t"<< itemID << "\t" << itemName << "\t" << price << "\t" << availableQuantity << "\t\t" << discount << "%\n";
        }
        file.close();

        cout << "\n\tEnter Item ID to purchase: ";
        int purchaseID, purchaseQty;
        cin >> purchaseID;

        cout << "\tEnter quantity: ";
        cin >> purchaseQty;

        // Check and update item availability
        ifstream readFile("supermarket_items.txt");
        ofstream tempFile("buyertemp.txt");
        bool itemFound = false;

        while (readFile >> itemID >> itemName >> price >> availableQuantity >> discount) {
            if (itemID == purchaseID) {
                itemFound = true;

                if (purchaseQty > availableQuantity) {
                    cout << "\tSorry, not enough stock available!\n";
                    tempFile << itemID << " " << itemName << " " << price << " " << availableQuantity << " " << discount << "\n";
                } else {
                    int updatedQuantity = availableQuantity - purchaseQty;
                    tempFile << itemID << " " << itemName << " " << price << " " << updatedQuantity << " " << discount << "\n";

                    float subtotal = price * purchaseQty;
                    float discountAmount = (subtotal * discount) / 100.0;
                    float gst = (subtotal - discountAmount) * 0.30;
                    float total = subtotal - discountAmount + gst;

                    // Format each value to 2 decimal places using ostringstream
                    ostringstream priceStream, discountStream, gstStream, totalStream;
                    priceStream << fixed << setprecision(2) << price;
                    discountStream << fixed << setprecision(2) << discountAmount;
                    gstStream << fixed << setprecision(2) << gst;
                    totalStream << fixed << setprecision(2) << total;

                    // Store formatted details in the receipt
                    receiptItems[receiptIndex++] = itemName + "\t" + to_string(purchaseQty) + "\t" +
                        priceStream.str() + "\t" + discountStream.str() + "\t" +
                        gstStream.str() + "\t" + totalStream.str();

                    grandTotal += total;
                    totalDiscount += discountAmount;
                    totalGST += gst;
                }
            } else {
                tempFile << itemID << " " << itemName << " " << price << " " << availableQuantity << " " << discount << "\n";
            }
        }

        readFile.close();
        tempFile.close();

        if (!itemFound) {
            cout << "\tItem not found! Please try again.\n";
            remove("buyertemp.txt");
        } else {
            remove("supermarket_items.txt");
            rename("buyertemp.txt", "supermarket_items.txt");
        }

        // Ask if user wants to continue shopping
        cout << "\n\tDo you want to add more items? (y/Y for yes, n/N for no): ";
        char choice;
        cin >> choice;
        system("cls");
        if (choice == 'n' || choice == 'N') {
            // Display final receipt
            cout << "\n********************* RECEIPT **************************\n";
            cout << "     Customer Email: " << email << "\n";
            cout << "----------------------------------------------------------\n";

            cout << "Item\tQty\tPrice\tDiscount\tGST\tTotal\n";
            cout << "----------------------------------------------------------\n";

            for (int i = 0; i < receiptIndex; i++) {
                cout << receiptItems[i] << "\n";
            }

            cout << "----------------------------------------------------------\n";
            // Format total values
            ostringstream totalDiscountStream, totalGSTStream, grandTotalStream;
            totalDiscountStream << fixed << setprecision(2) << totalDiscount;
            totalGSTStream << fixed << setprecision(2) << totalGST;
            grandTotalStream << fixed << setprecision(2) << grandTotal;

            cout << "Total Discount: \t\t" << totalDiscountStream.str() << "\n";
            cout << "Total GST: \t\t\t" << totalGSTStream.str() << "\n";
            cout << "Grand Total: \t\t\t" << grandTotalStream.str() << "\n";
            cout << "**********************************************************\n";
            cout << "\nThank you for shopping with us! Exiting...\n";
            return;
        } else if (choice != 'y' && choice != 'Y') {
            cout << "\tInvalid choice! Please enter 'y' or 'n'.\n";
        }
    }
}
int main(){	
system("cls");	
menu();
}//admin_menu functi
