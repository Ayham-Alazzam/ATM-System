#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

void Login();

enum enMenueCoice {
	enQuickWithdraw = 1, enNormalWithdraw = 2,
	enDeposite = 3, enCheckBalance = 4, enLogout = 5
};

struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkDelete = false;
};

string ReadString(string message)
{
	string S;
	cout << message << endl;
	cin >> S;
	return S;
}

string ConvertRecordToLine(sClient Client, string seperator = "#//#")
{
	string stString = "";

	stString += Client.AccountNumber + seperator;
	stString += Client.PinCode + seperator;
	stString += Client.Name + seperator;
	stString += Client.Phone + seperator;
	stString += to_string(Client.AccountBalance);

	return stString;
}

sClient UploadClientInfo(vector <sClient> Clients, sClient& Client)
{
	for (sClient& C : Clients)
	{
		if (C.AccountNumber == Client.AccountNumber)
		{
			Client = C;
			break;
		}
	}
	return Client;
}

vector <string> Split(string S, string delim)
{
	vector <string> vString;
	string word;
	short pos = 0;

	S.erase(0, S.find_first_not_of(" \t"));
	S.erase(S.find_last_not_of(" \t") + 1);

	while ((pos = S.find(delim)) != std::string::npos)
	{
		word = S.substr(0, pos);
		if (word != "")
		{
			vString.push_back(word);
		}
		S.erase(0, pos + delim.length());
	}
	if (S != "")
	{
		vString.push_back(S);
	}

	return vString;
}

sClient ConvertLineToRecord(string line, string seperator = "#//#")
{
	vector <string> vString;
	sClient Client;

	vString = Split(line, seperator);

	Client.AccountNumber = vString[0];
	Client.PinCode = vString[1];
	Client.Name = vString[2];
	Client.Phone = vString[3];
	Client.AccountBalance = stod(vString[4]);

	return Client;
}

void PrintClientRecord(sClient Client)
{
	cout << "The following are the client's details\n\n";

	cout << "\nClient's Account Number: ";
	cout << Client.AccountNumber;
	cout << "\nClient's PinCode: ";
	cout << Client.PinCode;
	cout << "\nClient's Name: ";
	cout << Client.Name;
	cout << "\nClient's Phone: ";
	cout << Client.Phone;
	cout << "\nClient's Account Balance: ";
	cout << Client.AccountBalance;
}

void SaveRecordToFile(vector <sClient>& Clients)
{
	fstream ClientFile("Client.txt", ios::out);

	if (ClientFile.is_open())
	{
		for (sClient& C : Clients)
		{
			ClientFile << ConvertRecordToLine(C) << endl;
		}
		ClientFile.close();
	}
}

void SaveClientInVector(vector <sClient>& Clients, sClient& Client)
{
	for (sClient& C : Clients)
	{
		if (C.AccountNumber == Client.AccountNumber)
		{
			C = Client;
			break;
		}
	}
}

bool SearchByAccountNumberAndPIN(string AccountNumber, string PinCode, vector <sClient>& Clients, sClient& Client)
{
	for (sClient C : Clients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			if (PinCode == C.PinCode)
			{
				Client = C;
				return true;
			}
		}
	}
	return false;
}

bool SearchByAccountNumber(string AccountNumber, vector <sClient>& Clients, sClient& Client)
{
	for (sClient C : Clients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}//

vector <sClient> ConvertDataFromFileToRecord()
{
	vector <sClient> Clients;

	string line = "";
	fstream ClientFile;

	ClientFile.open("Client.txt", ios::in);

	while (getline(ClientFile, line))
	{
		sClient Client;

		Client = ConvertLineToRecord(line);
		Clients.push_back(Client);
	}
	ClientFile.close();

	return Clients;
}

void NormalWithdrawScreen()
{
	cout << "=====================================\n";
	cout << "\tNormal Withdraw Screen\n";
	cout << "=====================================\n";
}

void NormalWithDraw(sClient& Client, vector<sClient>& Clients)
{
	system("cls");

	NormalWithdrawScreen();

	Clients = ConvertDataFromFileToRecord();
	string AccountNumber;
	double Amount = 0;
	char sure = 'n';


	PrintClientRecord(Client);
	cout << "\n\nEnter Withdrawal Amount:\n";
	cin >> Amount;

	if (Amount > Client.AccountBalance)
	{
		cout << "The amount exeeds the balance!\n";
		return;
	}

	cout << "Are you sure you want to perform this transaction? (Y/N)\n";
	cin >> sure;
	Client.AccountBalance -= Amount;

	SaveClientInVector(Clients, Client);

	SaveRecordToFile(Clients);

	cout << "Withdrawal completed successfully.\n";
	cout << "Your new balance is: " << Client.AccountBalance << endl;
}

void DepositeScreen()
{
	cout << "=====================================\n";
	cout << "\tDeposite Screen\n";
	cout << "=====================================\n";
}

void Deposite(sClient& Client, vector<sClient>& Clients)
{
	system("cls");

	DepositeScreen();

	Clients = ConvertDataFromFileToRecord();

	string AccountNumber;
	double Amount = 0;
	char sure = 'n';


	PrintClientRecord(Client);
	cout << "\n\nEnter Deposit Amount:\n";
	cin >> Amount;
	cout << "Are you sure you want to perform this transaction? (Y/N)\n";
	cin >> sure;
	Client.AccountBalance += Amount;

	SaveClientInVector(Clients, Client);

	SaveRecordToFile(Clients);

	cout << "Deposit completed successfully.\n";
	cout << "Your new Balance is: " << Client.AccountBalance << endl;

}

void QuickWithdrawScreen()
{
	cout << "=====================================\n";
	cout << "\tQuick Withdraw\n";
	cout << "=====================================\n";

	cout << "[1]20\t[2]50\n";
	cout << "[3]100\t[4]200\n";
	cout << "[5]400\t[6]600\n";
	cout << "[7]800\t[8]1000\n";
	cout << "[9]Exit\n";
	cout << "=====================================\n";
}

void NormalBalanceScreen()
{
	cout << "=====================================\n";
	cout << "\tBalance Screen\n";
	cout << "=====================================\n";
}

void ShowMenueScreen()
{
	system("cls");
	cout << "=====================================\n";
	cout << "\tATM Main Menue Screen\n";
	cout << "=====================================\n";
	cout << "\t[1]Quick Withdraw\n";
	cout << "\t[2]Normal Withdraw\n";
	cout << "\t[3]Deposite\n";
	cout << "\t[4]Check Balance\n";
	cout << "\t[5]Logout\n";
	cout << "=====================================\n";
}

void BackToMenue()
{
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	system("cls");
	//ShowMenueScreen();
}

void QuickWithdraw(sClient& Client, vector <sClient>& Clients)
{
	system("cls");

	QuickWithdrawScreen();

	Clients = ConvertDataFromFileToRecord();

	short Choice;

	cout << "Enter Choice From [0,8]\n";
	cin >> Choice;

	switch (Choice)
	{
	case 1:
		Client.AccountBalance -= 20;
		break;
	case 2:
		Client.AccountBalance -= 50;
		break;
	case 3:
		Client.AccountBalance -= 100;
		break;
	case 4:
		Client.AccountBalance -= 200;
		break;
	case 5:
		Client.AccountBalance -= 400;
		break;
	case 6:
		Client.AccountBalance -= 600;
		break;
	case 7:
		Client.AccountBalance -= 800;
		break;
	case 8:
		Client.AccountBalance -= 1000;
		break;
	default:
		BackToMenue();
	}

	SaveClientInVector(Clients, Client);

	SaveRecordToFile(Clients);
	cout << "Witdrawel Added Successfuly, Your Balance:\n";
	cout << Client.AccountBalance;

}

void CheckTheBalance(sClient Client, vector <sClient> Clients)
{
	system("cls");
	NormalBalanceScreen();
	cout << "\tYour Balance is: " << Client.AccountBalance << endl;
	BackToMenue();
}

void LoginScreen()
{
	system("cls");
	cout << "=====================================\n";
	cout << "\tLogin Screen\n";
	cout << "=====================================\n";
}

void ChooseFromATMScreenMenue(sClient Client)
{
	while (true)
	{
		enMenueCoice  MenueCoice;

		vector <sClient> Clients = ConvertDataFromFileToRecord();

		short Choice;
		ShowMenueScreen();
		cout << "Enter What You Want To Do From [1,5]? ";
		cin >> Choice;

		switch (Choice)
		{
		case enMenueCoice::enQuickWithdraw:
		{
			system("cls");
			QuickWithdraw(Client, Clients);
			BackToMenue();
			break;
		}
		case enMenueCoice::enNormalWithdraw:
		{
			system("cls");
			NormalWithDraw(Client, Clients);
			BackToMenue();
			break;
		}
		case enMenueCoice::enDeposite:
		{
			system("cls");
			Deposite(Client, Clients);
			BackToMenue();
			break;
		}
		case enMenueCoice::enCheckBalance:
		{
			system("cls");
			CheckTheBalance(Client, Clients);
			BackToMenue();
			break;
		}
		case enMenueCoice::enLogout:
		{
			system("cls");
			Login();
			break;
		}

		}
	}
}

void Login()
{
	sClient Client;
	string AccountNumber, PinCode;
	vector <sClient> Clients = ConvertDataFromFileToRecord();
	LoginScreen();
	do {
		cout << "Enter the AccountNumber? ";
		cin >> AccountNumber;
		cout << "Enter the PIN code ? ";
		cin >> PinCode;

	} while (!SearchByAccountNumberAndPIN(AccountNumber, PinCode, Clients, Client));
	system("cls");
	ChooseFromATMScreenMenue(Client);

}


int main()
{
	Login();




	system("pause>0");

	return 0;
}
