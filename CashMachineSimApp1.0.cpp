/*COPYRIGHT STEPHENSONENG
*C++ code to simulate a cash machine
*/

#include<iostream>
#include<map>
#include<string>
#include<thread>
#include<mutex>
#include<chrono>

using std::cout;
using std::cin;
using std::endl;


struct Cashy{
	std::mutex my_mutex1;
	void homescreen() {
	std::lock_guard<std::mutex> lk1(my_mutex1);
	cout << "Welcome to StephensonCashMachine" << endl;
	cout << "  " << "FreeCashWithdraw" << "  " << endl;

	std::this_thread::sleep_for(std::chrono::seconds(2)); //function will sleep for 2 seconds after being called
}
void showscreen() {//menu function
	
	cout << "                          MENU                                   " << endl;
	cout << "1. Check Balance:                     " << "   ";         cout << "3. Withdraw:" << endl;
	cout << "2. Deposit Amount:                    " << "    ";        cout << "4. Logout" << endl;
}
};
using cashMap = std::map<std::string, int>;

int main() {
	Cashy c;
	cashMap cm;  //creating hashmap to display current balance as key value pair
	int option = 0;
	double currentBalance = 0;
	std::thread t1(&Cashy::homescreen,&c);
	t1.join();
	system("cls");
	do {
		std::thread t2(&Cashy::showscreen,&c); //calling showscreen function
		t2.join();
		cout << " select an option :" << endl;
		cin >> option;
		system("cls");
		switch (option) {
		case 1:
			cout << "Balance is :" << " " << currentBalance << static_cast<char>(156) << "\n"; //converting asci code 156 of GBP
			break;
		case 2:
			cout << "please deposit amount" << ":" << "\n";    //depositing amount
			double depositamount;
			cin >> depositamount;
			currentBalance += depositamount;
			cm["Current Balance"] = currentBalance;

			for (auto& [key, value] : cm)  //structure binding (c++17 version only) to traverse the map
				cout << key << " " << "=" << " " << value << static_cast<char>(156);
			break;
		case 3:
			try {                                                       //using try and catch block to handle error in case
				//of the user requesting to withdraw an amount greater than current balance
				cout << "How much you want to Withdraw?" << endl;
				double withdrawnAmount;
				cin >> withdrawnAmount;
				if (withdrawnAmount < currentBalance) {
					currentBalance -= withdrawnAmount;
					cm["Current Balance"] = currentBalance;
					for (auto& [key, value] : cm)
						cout << key << " " << ":" << " " << value << static_cast<char>(156);
				}

				else throw 353;
			}
			catch (...) {
				cout << "ERROR:" << " " << "Insuffiicient Funds" << "\n";
				std::this_thread::sleep_for(std::chrono::seconds(2));
				system("cls");
			}
			break;
		default: cout << "Thanks for using StephensonCashMachine" << "\n";
		}
	} while (option != 4);

	return 0;
	cin.get();
	
}