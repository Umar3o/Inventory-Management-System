#include <iostream>
#include <fstream> // for file handling
#include <string>
#include <sstream> // for istringstream

using namespace std;



int AddItem(string FileName, string ItemName, int quantity, double price)
{
	// opens file for read
	ifstream InvDataR(FileName);
	
	// checks for errors while opening text file
	if (!InvDataR) {

	    // print error message
	    cout << "Error opening the file." << endl;
	
	    // exit the function
	    return 1;
	    
	}
	
	int ItemNumber;
	string oneline;

	
	while(getline(InvDataR, oneline))
	{
		istringstream iss(oneline);
		
		iss >> ItemNumber;
	}
	
	InvDataR.close();
	ItemNumber ++;
	
	ofstream InvDataA(FileName, ios::app);
	
	// checks for errors while opening text file
	if (!InvDataA) {

	    // print error message
	    cout << "Error opening the file." << endl;
	
	    // exit the function
	    return 1;
	    
	}
	
	InvDataA << ItemNumber << " " << ItemName << " " << price << " " << quantity << endl;
	
	InvDataA.close();
	return 0;
	
}

int UpdateQuantity(string FileName, int AddAmount, string ThisItem)
{
	// delaring variable to store one line from text file
	string oneline;
	
	// declaring variables to store elements from one line into
	string ItemName;
	int ItemNumber;
	int quantity;
	double price;
	bool updated = false;
	
	// opening files, InvData to read from and TempFile to write into
	ifstream InvData(FileName);
	ofstream TempFile("Tempfile.txt");
	
	// checks for errors while opening text file
	if (!InvData or !TempFile) {

	    // print error message
	    cout << "Error opening the file." << endl;
	
	    // exit the function
	    return 1;
	    
	}
	
	// iterates through file line by line until empty line found
	while(getline(InvData, oneline)){
		
		// function used to parse string line and treat it as a stream object where each word can be seperated
		istringstream iss(oneline);
		
		// extraction operator used to store values from stream into variables
		iss >> ItemNumber >> ItemName >> price >> quantity;
		
		// looks for item in file
		if (ThisItem == ItemName){
			// checks if updating amount gives an unreasonable value
			if (quantity+AddAmount >= 0){
				updated = true;
				// updates amount
				quantity = quantity + AddAmount;
			} else {
				// if amount becomes lower than 0
				cout << "Not enough items in stock" << endl;
			}
		}
	
		// updated line stored in temp file
		TempFile << ItemNumber << " " << ItemName << " " << price << " " << quantity << endl;
	
	}
	// both files closed
	InvData.close();
	TempFile.close();
	
	// checks updated flag to see if value was updated
	if (updated) {
		
		// removes original (outdated) file and checks if done successfully
        if (remove(FileName.c_str()) != 0) {
            cout << "Error deleting original file." << endl;
            return 1;
        }
		
		// renames the temp file to the original file and checks if done successfully
        if (rename("Tempfile.txt", FileName.c_str()) != 0) {
            cout << "Error renaming temporary file." << endl;
            return 1;
        }

        cout << "Quantity updated successfully!" << endl;
	} else {
	        cout << "Item not found." << endl;
	        remove("Tempfile.txt"); 
		}
	
	return 0;
}

   
int DisplayInventory(string FileName){
	// delaring variable to store one line from text file
	string oneline;
	
	// declaring variables to store elements from one line into
	string ItemName;
	int ItemNumber;
	int quantity;
	double price;
	
	
	// used to open file for read
    ifstream InvData(FileName);
    
    // if file not opened successfully, error message output and function exited
    if (!InvData) {

    // print error message
    cout << "Error opening the file." << endl;

    // exit the function
    return 1;
    
	}
	
    // iterate through lines of file until End Of File is reached and stores data from line into oneline
    while(getline(InvData, oneline))
    {	    	
    	// istringstream used to parse through string, iss converts string(oneline) into a stream and allows the words in string to be seperated
    	istringstream iss(oneline);
    	
    	// takes elements from object iss and uses extraction operator to store each part into variables. >> (extraction operator) automatically stops on whitespaces.
    	iss >> ItemNumber >> ItemName >> price >> quantity;
    	
    	// printing the inventory
    	cout << ItemNumber << ". " << ItemName << endl;
    	cout << "price: $" << price << endl;
    	cout << "quantity: " << quantity << endl << endl << endl;
	}

	// closing the file
    InvData.close();
    return 0;

}

int StockWarning(string FileName)
{
	ifstream InvDataJ(FileName);
	// checks for errors while opening text file
	if (!InvDataJ) {

	    // print error message
	    cout << "Error opening the file." << endl;
	
	    // exit the function
	    return 1;   
	}
	
	string oneline;
	int ItemNumber, quantity, AddedQuantity;
	double price;
	string ItemName;
	char ans;
	
	
	while(getline(InvDataJ, oneline))
	{
		istringstream iss(oneline);
		
		iss >> ItemNumber >> ItemName >> price >> quantity;
		
		if(quantity < 10){ 
			cout << "Please restock "<< ItemName << " as only " << quantity << " items are left." << endl << endl;
		}
	}
	
	InvDataJ.close();
	return 0;
	
}


int main()
{
	int Ans, Price, Quantity;
	string ItemName;
	int Update;	  
	cout << "WELCOME TO YOUR INVENTORY MANAGEMENT SYSTEM!!" << endl << endl;
	
	while (Ans != -1)
	{
		cout << "Functions Available: " << endl;
		cout << "1) Display Inventory List" << endl;
		cout << "2) Add Item To Inventory List" << endl;
		cout << "3) Update Quantity Of An Item In The Inventory List" << endl;
		cout << "4) Check If You Have A Stock Warning" << endl << endl;
		cout << "Please choose which one of these fucntions you want to perform " << endl;
		cout << "Enter -1 to exit your inventory management system" << endl;
		cin >> Ans;
		cout << "---------------------------------------------------------------------" << endl;
		if (Ans==1)
		{
			cout << endl;
			cout << "You have chosen to display your inventory list" << endl;
			cout << "Here is your current inventory list:" << endl << endl;
			DisplayInventory("InventoryData.txt");
		}
		else if (Ans==2)
		{
			cout << endl;
			cout << "You have chosen to add a new item your inventory list" << endl;
			cout << "Please enter name of the item you want to add in to the list: " << endl;
			cin >> ItemName;
			cout << endl;
			cout << "Please enter the quantity of the item: " << endl;
			cin >> Quantity;
			cout << endl;
			cout << "Please enter the price of a single item: " << endl;
			cin >> Price;
			cout << endl;
			AddItem("InventoryData.txt", ItemName, Quantity, Price);
			cout << ItemName << " has been added to the list." << endl;
		}
		else if (Ans==3)
		{
			cout << endl;
			cout << "You have chosen to update the quantity of an item in your inventory list" << endl;
			cout << "Please enter the name of the item in the list you want to update the quantity of: " << endl;
			cin >> ItemName;
			cout << endl;
			cout << "Please enter the update in the quantity of the item" << endl;
			cin >> Update;
			cout << endl;
			UpdateQuantity("InventoryData.txt", Update, ItemName);
		}
		else if (Ans==4)
		{
			cout << endl;
			cout << "You have chosen to check if you have a stock warning" << endl;
			cout << endl;
			StockWarning("InventoryData.txt");
		}
		else if (Ans==-1)
		{
			cout << endl;
			cout << "Thank you for using your inventory management system. Hope you had a comfortable experience!!" << endl << endl;
		}
		else
		{
			cout << endl;
			cout << "Please enter valid number of the function you want to perform." << endl;
		}
		cout << "---------------------------------------------------------------------" << endl << endl;
	}
	
	
	return 0;
}