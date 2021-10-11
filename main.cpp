/*
  Banking Managemnt System Project

  Author: Adarsha.S
  Created On: 11/10/21
  Modified On:
  Dependencies: None
*/

//Header files 
#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;

//class starts here
class account
{
private:
  double Interest_Rate=0.05,Service_Charges=0.00;
	int accno,deposit;
	char name[30],type;
public:
	void Get_Account();//function to get data from user
	void Modify();//function to add new data
	void Deposit(int);//function to accept amount and add to balance amount
	void Withdraw(int);//function to accept amount and subtract from balance amount
  void Interest(int);//function to find interest
  void Show_Account() const;//function to show data on screen
	void Tabular_form() const;//function to show data in tabular format
	int Account_no() const;//function to return account number
	int Balance_amount() const;//function to return balance amount
	char Type_of_Account() const;//function to return type of account
};//class ends here

void account::Get_Account()
{
	cout<<"\nEnter Account Number: ";
	cin>>accno;
	cout<<"Enter The Name of The account Holder: ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"Enter S for Saving Type a/c and C for Current Type a/c: ";
	cin>>type;
	type=toupper(type);
	cout<<"Enter Initial amount: ";
	cin>>deposit;
	cout<<"\nAccount is Created\n";
}

void account::Show_Account() const
{
	cout<<"Account Number: "<<accno<<endl;
	cout<<"Type of Account: "<<type<<endl;
	cout<<"Balance amount: "<<deposit<<"\n";
}


void account::Modify()
{
	cout<<"Account Number: "<<accno<<endl;
	cout<<"Modify Type of Account: "<<endl;
	cin>>type;
	type=toupper(type);
	cout<<"Modify Balance amount: "<<endl;
	cin>>deposit;
  cout<<"\n";
}

	
void account::Deposit(int x)
{
	deposit=deposit+x;
}
	
void account::Withdraw(int x)
{
	deposit=deposit-x;
}
	
void account::Tabular_form() const
{
	cout<<accno<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(10)<<deposit<<endl;
}

char account::Type_of_Account() const
{
	return type;
}
	
int account::Account_no() const
{
	return accno;
}

int account::Balance_amount() const
{
	return deposit;
}

void account::Interest(int n)
{
  double Interest_Rate=0.05,Service_Charges=5.00;
  double Monthly_Interest=(n*Interest_Rate)/12;
  cout<<"Balance in account: "<<n;
  cout<<"\nMonthly Interest: "<<Monthly_Interest<<endl;
  n=n+Monthly_Interest;
  cout<<"Balance after adding interest: "<<n<<endl;
  n=n-Service_Charges;
  cout<<"After taking service charges of 5 Rs & final Interest calculation is: "<<n;
}

//function declaration
void Write_Account();//function to write record in binary file
void Display_Details(int);//function to display account details given by user
void Modify_Account(int);//function to modify record of file
void Delete_Account(int);//function to delete record of file
void Display_All_Details();//function to display all account details
void Deposit_Withdraw(int,int);//function to desposit/withdraw amount for given account
void Calculate_Interest(int);//void Interest_Account();

//MAIN FUNCTION OF PROGRAM
int main()
{
	char c;
	int no;

	do
	{
		cout<<"MAIN MENU\n";
    cout<<"1.NEW ACCOUNT\n";
    cout<<"2.DEPOSIT AMOUNT\n";
    cout<<"3.WITHDRAW AMOUNT\n";
    cout<<"4.BALANCE CHECK\n";
    cout<<"5.ALL ACCOUNT HOLDER LIST\n";
    cout<<"6.DELETE AN ACCOUNT\n";
    cout<<"7.MODIFY AN ACCOUNT\n";
    cout<<"8.CALCULATE INTEREST\n";
    cout<<"9.EXIT\n";
    cout<<"Select Your Option from (1-9): ";
    cin>>c;

		switch(c)
		{

		case '1':
			Write_Account();
			break;

		case '2':
			cout<<"Enter Account Number: "; 
      cin>>no;
			Deposit_Withdraw(no,1);
			break;

		case '3':
			cout<<"Enter Account Number: "; 
      cin>>no;
			Deposit_Withdraw(no,2);
			break;

		case '4': 
			cout<<"Enter Account Number: "; 
      cin>>no;
			Display_Details(no);
			break;

		case '5':
			Display_All_Details();
			break;

		case '6':
			cout<<"Enter Account Number: "; 
      cin>>no;
			Delete_Account(no);
			break;

		 case '7':
			cout<<"Enter Account Number: ";  
      cin>>no;
			Modify_Account(no);
			break;

      case '8':
      cout<<"Enter Account Number: ";
      cin>>no;
      Calculate_Interest(no);
      break;

		 case '9':
			cout<<"\nThanks for using Bank Managemnt system";
			break;

		 default :
     cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}while(c!='9');
	return 0;
}

//function to write 
void Write_Account()
{
	account acc;
	ofstream outFile;
	outFile.open("account.txt",ios::binary|ios::app);
	acc.Get_Account();
	outFile.write(reinterpret_cast<char *> (&acc), sizeof(account));
	outFile.close();
}

//function to read
void Display_Details(int n)
{
	account acc;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.txt",ios::binary);
	if(!inFile)
	{
		cout<<"File couldn't be opened, press enter to return to Menu\n";
		return;
	}
	cout<<"BALANCE DETAILS\n";

    	while(inFile.read(reinterpret_cast<char *> (&acc), sizeof(account)))
	{
		if(acc.Account_no()==n)
		{
			acc.Show_Account();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\nAccount number doesn't exist!\n";
}

//function to modify 
void Modify_Account(int n)
{
	bool found=false;
	account acc;
	fstream File;
	File.open("account.txt",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File couldn't be opened, press enter to return to Menu\n";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&acc), sizeof(account));
		if(acc.Account_no()==n)
		{
			acc.Show_Account();
			cout<<"Enter The New Details of account: "<<endl;
			acc.Modify();
			int pos=(-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&acc), sizeof(account));
			cout<<"\nDetails are Updated\n";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\nDetails Not found\n";
}

//function to delete 
void Delete_Account(int n)
{
	account acc;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.txt",ios::binary);
	if(!inFile)
	{
		cout<<"File couldn't be opened, press enter to return to Menu\n";
		return;
	}
	outFile.open("Temp.txt",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&acc), sizeof(account)))
	{
		if(acc.Account_no()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&acc), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.txt");
	rename("Temp.txt","account.txt");
	cout<<"\nDetails is Deleted\n";
}

//function to display all details 
void Display_All_Details()
{
	account acc;
	ifstream inFile;
	inFile.open("account.txt",ios::binary);
	if(!inFile)
	{
		cout<<"File couldn't be opened, press enter to return to Menu\n";
		return;
	}
	cout<<"        ACCOUNT HOLDER LIST\n";
	cout<<"--------------------------------------\n";
	cout<<"A/c no.   NAME     Type     Balance\n";
	cout<<"---------------------------------------\n";
	while(inFile.read(reinterpret_cast<char *> (&acc), sizeof(account)))
	{
		acc.Tabular_form();
	}
	inFile.close();
}

//function to deposit and withdraw amount
void Deposit_Withdraw(int n, int option)
{
	int amount;
	bool found=false;
	account acc;
	fstream File;
	File.open("account.txt", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File couldn't be opened, press enter to return to Menu\n";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&acc), sizeof(account));
		if(acc.Account_no()==n)
		{
			acc.Show_Account();
			if(option==1)
			{
				cout<<"TO DEPOSITE THE AMOUNT\n";
				cout<<"Enter The amount to be deposited: ";
				cin>>amount;
				acc.Deposit(amount);
			}
			if(option==2)
			{
				cout<<"TO WITHDRAW AMOUNT\n";
				cout<<"Enter Amount to be withdrawn: ";
				cin>>amount;
				int balance=acc.Balance_amount()-amount;
				if((balance<500 && acc.Type_of_Account()=='S') || (balance<1000 && acc.Type_of_Account()=='C'))
					cout<<"\nINSUFFICIENT BALANCE!!";
				else
					acc.Withdraw(amount);
			}
			int pos=(-1)*static_cast<int>(sizeof(acc));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&acc), sizeof(account));
			cout<<"\nDetails is updated\n";
			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout<<"\nRecord is not found!\n";
}

//funtion to calculate interest
void Calculate_Interest(int n)
{
  int bal;
  account acc;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.txt",ios::binary);
	if(!inFile)
	{
		cout<<"File couldn't be opened, press enter to return to Menu\n";
		return;
	}
	cout<<"Interest Calculation\n";

    	while(inFile.read(reinterpret_cast<char *> (&acc), sizeof(account)))
	{
		if(acc.Account_no()==n)
		{
			bal = acc.Balance_amount();
		}
	}
	inFile.close();
  acc.Interest(bal);
}