#include "pch.h"
#include <iostream>
#include"Header.h"

bool mainLoop(TradingShell& shell, char* commandInput) {
	//no command is going to be longer than 64 symbols
	std::cout << "Input Command: ";
	std::cin >> commandInput;
	if (!strcmp(commandInput, "add-wallet")) {
		char userName[264];
		double fiatMoney;
		std::cout << "Input the amount of lv: ";
		std::cin >> fiatMoney;
		std::cout << "Name of the user: ";
		std::cin >> userName;
		std::cout << "Account with id " << WALLET_ID << " has been credited " << toFMICoins(fiatMoney) << " FMI coins. \n";
		shell.createWallet(fiatMoney, userName);
		return true;
	}
	else if (!strcmp(commandInput, "make-order")) {
		char type[8];
		std::cin >> type;
		double fmiCoins;
		std::cin >> fmiCoins;
		unsigned WalletID;
		std::cin >> WalletID;
		shell.CreateOrder(type, fmiCoins, WalletID);
		
		return true;
	}
	else if (!strcmp(commandInput, "print-info")) {
		shell.wallets.printWalletsInfo();
		return true;
	}
	else if (!strcmp(commandInput, "orders-info")) {
		shell.orders.printOrders();
		return true;
	}
	else if (!strcmp(commandInput, "wallet-info")) {
		unsigned walletID;
		std::cin >> walletID;
		shell.wallets.printSingleWalletInfo(shell.transactions,walletID);
		return true;
	}
	else if (!strcmp(commandInput, "transfer")) {
		unsigned senderID,receiverID;
		double transCoins;
		std::cin >> senderID;
		std::cin >> receiverID;
		std::cin >> transCoins;
		shell.transfer(senderID, receiverID, transCoins);
		return true;
	}
	else if (!strcmp(commandInput, "quit")) {
		shell.wallets.saveData();
		shell.transactions.saveData();
		shell.orders.saveData();
		return false;
	}
	else if (!strcmp(commandInput, "print-trans")) {
		shell.transactions.printTransactions();
		return true;
	}
	else if (!strcmp(commandInput, "attract-investors")) {
		std::cout << "Printing top 10 richest wallets............\n\n";
		shell.attractInvestors();
		return true;
	}
	else {
		std::cout << "Invalid command!\n";
		return true;
	}

	return false;
}


int main()
{
	TradingShell shell;
	char command[64];
	while (mainLoop(shell,command))
	{
		std::cout << "==========================================================\n\n";
	}

}
