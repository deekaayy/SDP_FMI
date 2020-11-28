#pragma once
#include<fstream>
#include <ctime>
#include <iostream>
#include <cassert>
#include <algorithm>



static unsigned WALLET_ID = 0;

static const unsigned SYSTEM_ID = 4294967295;

bool is_empty(std::ifstream& pFile)
{
	return pFile.peek() == std::ifstream::traits_type::eof();
}

double toFMICoins(double fiatMoney)
{
	return fiatMoney / 375.0;
}

double toFiat(double coins) {
	return coins * 375.0;
}

long long getTime() {
	return time(nullptr);
}

int resizeOrInitialize(int source)
{
	if (source > 0) {
		return source * 2;
	}
	else return 16;
}

struct Transaction {
	long long time;
	unsigned senderId;
	unsigned receiverId;
	double fmiCoins;
};

class Transactions {
private:

	Transaction transaction;

	Transaction* transContainer = nullptr;
	size_t transCount;
	size_t transCapacity;

	void resize() {
		transCapacity *= 2;
		Transaction* tmp = nullptr;
		tmp = new Transaction[transCapacity];
		memcpy(tmp, transContainer, transCount * sizeof(Transaction));
		delete[] transContainer;
		transContainer = tmp;
		//delete[] tmp;
	}

	void initialiseTransactions() {
		std::ifstream infile("transactions.dat", std::ios::binary | std::ios::app);
		if (!infile) {
			std::cout << "Can't load trans file!";
			//exit(1);
			return;
		}
		infile.seekg(0, std::ios::end);
		size_t len = static_cast<size_t>(infile.tellg());
		transCount = static_cast<size_t>(infile.tellg() / sizeof(Transaction));
		transCapacity = resizeOrInitialize(transCount);
		infile.seekg(0, std::ios::beg);
		delete[] transContainer;
		transContainer = new(std::nothrow) Transaction[transCapacity];
		infile.read(reinterpret_cast<char*>(transContainer), len);
		infile.close();
	}

public:

	Transactions() {
		initialiseTransactions();
	}

	Transactions(const Transaction& otherTransaction) = delete;

	Transaction& operator=(const Transaction& otherTransaction) = delete;

	~Transactions() {
		delete[] transContainer;
	}

	void createTransaction(const unsigned newSenderId, const unsigned newReceiverId, const double newFmiCoins) {
		Transaction transaction;
		transaction.fmiCoins = newFmiCoins;
		transaction.receiverId = newReceiverId;
		transaction.senderId = newSenderId;
		if (transCount == transCapacity) {
			resize();
		}
		transContainer[transCount++] = transaction;
	}

	void saveData() {
		std::ofstream outfile("transactions.dat", std::ios::binary | std::ios::trunc);
		if (!outfile) {
			return;
		}
		outfile.write(reinterpret_cast<char*>(transContainer), transCount * sizeof(Transaction));
	}

	void printTransactions()const {
		for (int i = 0; i < transCount; ++i) {
			std::cout << transContainer[i].senderId << " => " << transContainer[i].receiverId << " : " << transContainer[i].fmiCoins << std::endl;
		}
	}

	double getCoinTotal(unsigned walletId) {
		double totalCoins = 0;
		for (int c = 0; c < transCount; c++) {
			Transaction& trans = transContainer[c];
			if (trans.receiverId == walletId) {
				totalCoins += trans.fmiCoins;
			}
			else if (trans.senderId == walletId) {
				totalCoins -= trans.fmiCoins;
			}
		}
		return totalCoins;
	}

	size_t getTransCount() const {
		return transCount;
	}
};

struct Wallet {
	char owner[256];
	unsigned id;
	double fiatMoney;
	struct walletInfo {
		double FMIcoins;//FMI coins
		int transactionsCount = 0;// number of transactions the wallet has made
		long long timeOfFirstTrans;// time of the first transaction
		long long timeOfLastTrans;// time of the last transaction
	};
	walletInfo walletInfo;

};

class Wallets {
private:
	Wallet wallet;
	Wallet* walletsContainer = nullptr;
	size_t walletsCapacity;
	size_t walletsCount;

	void resize() {
		Wallet* tmp = walletsContainer;

		walletsCapacity *= 2;
		tmp = new Wallet[walletsCapacity];
		memcpy(tmp, walletsContainer, walletsCount * sizeof(Wallet));
		delete[] walletsContainer;
		walletsContainer = tmp;

	}

	void initialiseWallets()
	{
		std::ifstream infile("wallets.dat", std::ios::binary | std::ios::app);
		if (!infile) {
			std::cout << "Error opening file!" << std::endl;
			//exit(1);
			return;
		}
		infile.seekg(0, std::ios::end);
		size_t len = static_cast<size_t>(infile.tellg());
		walletsCount = static_cast<size_t>(infile.tellg() / sizeof(Wallet));
		WALLET_ID = walletsCount;
		walletsCapacity = resizeOrInitialize(walletsCount);
		infile.seekg(0, std::ios::beg);
		delete[] walletsContainer;
		walletsContainer = new(std::nothrow) Wallet[walletsCapacity];
		infile.read(reinterpret_cast<char*>(walletsContainer), len);
		infile.close();
	}

public:

	Wallets() {
		initialiseWallets();
	}
	~Wallets() {
		delete[] walletsContainer;
	}

	Wallets(const Wallet& otherWallet) = delete;

	Wallet& operator=(const Wallet& otherWallet) = delete;

	void addWallet(const double newFiatMoney, const char newName[256])
	{
		Wallet wallet;
		strcpy_s(wallet.owner, 256, newName);
		wallet.id = WALLET_ID++;
		wallet.fiatMoney = newFiatMoney;
		wallet.walletInfo.timeOfFirstTrans = getTime();
		wallet.walletInfo.timeOfLastTrans = getTime();
		wallet.walletInfo.transactionsCount++;

		if (walletsCount == walletsCapacity) {
			resize();
		}

		walletsContainer[walletsCount++] = wallet;
	}

	void saveData() {
		std::ofstream outfile("wallets.dat", std::ios::binary | std::ios::trunc);
		if (!outfile) {
			return;
		}
		outfile.write(reinterpret_cast<char*>(walletsContainer), walletsCount * sizeof(Wallet));
	}

	void printWalletsInfo() const {
		for (int i = 0; i < walletsCount; i++) {
			std::cout << walletsContainer[i].owner << " with id " << walletsContainer[i].id << " with balance " << walletsContainer[i].fiatMoney << std::endl;
		}
	}

	void printSingleWalletInfo(Transactions& transact, const unsigned walletID) {
		if (walletID >= WALLET_ID) {
			std::cout << "Unexisting wallet! \n";
			return;
		}
		std::cout << walletsContainer[walletID].owner << " with id " << walletsContainer[walletID].id << " which has "
			<< walletsContainer[walletID].fiatMoney << " lv, " << transact.getCoinTotal(walletID) << "FmiCoins" << ", time of first transaction: "
			<< walletsContainer[walletID].walletInfo.timeOfFirstTrans << " || time of last transaction: "
			<< walletsContainer[walletID].walletInfo.timeOfLastTrans << std::endl
			<< "The wallet has participated in " << walletsContainer[walletID].walletInfo.transactionsCount << " transactions. \n\n";
	}

	bool ifWalletExists(unsigned searched) {
		return searched < WALLET_ID;
	}

	void executeMoneyTransfer(unsigned senderID, unsigned receiverID, double FMIcoins) {
		walletsContainer[senderID].fiatMoney -= toFiat(FMIcoins);
		walletsContainer[senderID].walletInfo.timeOfLastTrans = getTime();
		walletsContainer[senderID].walletInfo.transactionsCount++;
		walletsContainer[receiverID].fiatMoney += toFiat(FMIcoins);
		walletsContainer[receiverID].walletInfo.timeOfLastTrans = getTime();
		walletsContainer[receiverID].walletInfo.transactionsCount++;
	}

	//uneeded

	double getFiatMoneyOfWallet(unsigned walletID) {
		return walletsContainer[walletID].fiatMoney;
	}

	size_t getWalletsCount() const {
		return walletsCount;
	}
	Wallet* returnPtrToContainer() {
		return walletsContainer;
	}
};


#pragma once
#include"transactionsHeader.h"
#include"Header.h"
struct Order {
	enum Type { SELL, BUY } type;
	unsigned walletId;
	double fmiCoins;
};

class Orders {
private:

	Order order;
	Order* ordersContainer = nullptr;
	size_t ordersCapacity;
	size_t ordersCount;
	void resize() {
		Order* tmp;
		ordersCapacity *= 2;
		tmp = new Order[ordersCapacity];
		memcpy(tmp, ordersContainer, ordersCount * sizeof(Order));
		delete[] ordersContainer;
		ordersContainer = tmp;
		//delete[] tmp;
	}

	void initialiseOrders() {
		std::ifstream infile("orders.dat", std::ios::binary | std::ios::app);
		if (!infile) {
			std::cout << "Error opening orders file.";
			//exit(1);
			return;
		}

		infile.seekg(0, std::ios::end);
		size_t len = static_cast<size_t>(infile.tellg());
		ordersCount = static_cast<size_t>(infile.tellg() / sizeof(Order));
		ordersCapacity = resizeOrInitialize(ordersCount);
		infile.seekg(0, std::ios::beg);
		delete[] ordersContainer;
		ordersContainer = new (std::nothrow) Order[ordersCapacity];
		infile.read(reinterpret_cast<char*>(ordersContainer), len);
		infile.close();
	}

public:

	Orders() {
		initialiseOrders();
	}

	~Orders() {
		delete[] ordersContainer;
	}

	Order& operator=(const Order& otherOrder) = delete;

	void createOrder(Order::Type ordType, double fmiCoins, unsigned WalletID) {


		bool completedOrder = false;
		//if an order can be completed, complete and don't add but first check for orders that are already queued
		//create a function to run through the existing orders - check
		//create a log file for one order?? - ask
		//TODO

		if (!completedOrder) {
			Order order;
			order.type = ordType;
			order.walletId = WalletID;
			order.fmiCoins = fmiCoins;
			ordersContainer[ordersCount++] = order;
		}



	};

	void runThroughOrders(Order& order, Wallets& wallets, Transactions& transactions) {
		//this function needs to be called when a new order is being created and stored into the ordersContainer
		//every completed order should be stored into a log file TODO (file must be .txt)
		//maybe use good 'ol fashioned %u %d
		//create a log file and attach to wallet or create a log file with index of wallet	
		double coinsToGive = order.fmiCoins;
		int transactionsToBeMade = 0;

		//get the number of transactions that are possible to be made
		for (int i = 0; i < ordersCount; ++i) {
			Order& currOrder = ordersContainer[i];
			coinsToGive -= currOrder.fmiCoins;
			transactionsToBeMade++;
			if (coinsToGive <= 0.0) {
				break;
			}
		}

		//start executing transactions
		//the idea is to play around one type of order as giver and the other one will be the consumer (done by rotating places of the two ID's)
		//the completed orders must be removed and stored into a log file
		//a simple 'for' cycle will do the trick for small amounts of data but for bigger ones a new type of search cycle must be implemented
		size_t completedOrders = 0;
		for (int i = 0; i < ordersCount; ++i) {
			Order& executingOrder = ordersContainer[i];
			unsigned senderID, receiverID;
			double transactCoins;

			//get coins for the current transaction
			if (order.fmiCoins < executingOrder.fmiCoins) {
				transactCoins = order.fmiCoins;
			}
			else {
				transactCoins = executingOrder.fmiCoins;
			}

			if (order.type == Order::Type::SELL) {
				senderID = executingOrder.walletId;
				receiverID = order.walletId;
			}
			else {		//risky play but assuming there are only 2 types of order
				senderID = order.walletId;
				receiverID = executingOrder.walletId;
			}

			bool flag = false; // a more flexible break point for the cycle when the execution is unable to continue
								//due to unavaiable resources
			if (order.fmiCoins >= executingOrder.fmiCoins) {
				completedOrders++;
				order.fmiCoins -= executingOrder.fmiCoins;//deduct and return the remaining coins
			}
			else {
				executingOrder.fmiCoins -= order.fmiCoins;
				order.fmiCoins = 0;
				flag = true;//break since unable to continiue
			}

			if (wallets.ifWalletExists(senderID) && wallets.ifWalletExists(receiverID)) { //maybe not needed, could remove later
				if (transactions.getCoinTotal(senderID) >= transactCoins) {
					wallets.executeMoneyTransfer(senderID, receiverID, transactCoins);
					transactions.createTransaction(senderID, receiverID, transactCoins);
				}
				else std::cout << "Insufficient funds. \n";
			}

			if (flag) {
				break;
			}
		}

		if (completedOrders > 0) {
			//deleting the completed orders
			const int newOrderCount = ordersCount - completedOrders;
			memcpy(ordersContainer, ordersContainer + completedOrders /*move the pointer that many postions*/, newOrderCount * sizeof(Order));
			//since there is a danger of overlapping memory blocks, memmove should be a safer approach
			ordersCount = newOrderCount;
			//if too many orders get completed maybe lower the capacity
		}
	}

	void saveData() {
		std::ofstream outfile("orders.dat", std::ios::binary | std::ios::trunc);
		if (!outfile) {
			return;
		}
		outfile.write(reinterpret_cast<char*>(ordersContainer), ordersCount * sizeof(Order));
	}

	void printOrders() {
		for (int i = 0; i < ordersCount; i++) {
			std::cout << ordersContainer[i].type << " " << ordersContainer[i].walletId << " " << ordersContainer[i].fmiCoins << std::endl;
		}
	}

	size_t getOrdersCount() const {
		return ordersCount;
	}


};


struct TradingShell
{

	Wallets wallets;
	Transactions transactions;
	Orders orders;


	void createWallet(const double newFiatMoney, const char newName[256])
	{
		wallets.addWallet(newFiatMoney, newName);

		transactions.createTransaction(-1, WALLET_ID - 1, toFMICoins(newFiatMoney));
	}

	void transfer(unsigned senderID, unsigned receiverID, double FMIcoins) {
		if (wallets.ifWalletExists(senderID) && wallets.ifWalletExists(receiverID)) {
			if (transactions.getCoinTotal(senderID) > FMIcoins) {
				//wallets.executeMoneyTransfer(senderID, receiverID, FMIcoins);
				transactions.createTransaction(senderID, receiverID, FMIcoins);
			}
			else std::cout << "Insufficient funds. \n";
		}
	}

	void CreateOrder(char type[8], double fmiCoins, unsigned WalletID) {

		if (WalletID > WALLET_ID) {
			std::cout << "Invalid wallet info. Order creation cancelled. \n";
			return;
		}

		Order::Type ordType;
		if (!strcmp(type, "SELL")) {
			ordType = Order::SELL;
		}
		else if (!strcmp(type, "BUY")) {
			ordType = Order::BUY;
		}
		else {
			std::cout << "Invalid order type. Order creation cancelled. \n";
			return;
		}

		if (ordType == Order::SELL) {
			const double walletBalance = transactions.getCoinTotal(WalletID);
			if (walletBalance < fmiCoins) {
				std::cout << "Wallet has insufficient funds to create order. Order creation terminated. \n";
				return;
			}
		}

		else { // assuming there are only 2 types of order
			const double wanted = toFiat(fmiCoins);
			if (wallets.getFiatMoneyOfWallet(WalletID) < wanted) {
				std::cout << "Wallet has insufficient funds to complete order. Order creation terminated. \n";
				return;
			}
		}

		orders.createOrder(ordType, fmiCoins, WalletID);
	}

	void attractInvestors() {

		unsigned marked[10];
		short index = 0;

		for (int i = 0; i < std::fmin(wallets.getWalletsCount(), 10); ++i) //get 10 or less
		{
			double maxMoney = 0;
			short currIndex = 0;
			for (int j = 0; j < wallets.getWalletsCount(); ++j)
			{
				double fmiCoins = transactions.getCoinTotal(j);

				if (maxMoney <= fmiCoins)
				{
					bool flag = true;
					for (int k = 0; k < index; ++k)
					{
						if (marked[k] == j)
						{
							flag = false;
						}
					}
					if (flag)
					{
						maxMoney = fmiCoins;
						currIndex = j;
					}
				}
			}
			wallets.printSingleWalletInfo(transactions,currIndex);
			marked[index++] = currIndex;
			std::cout << std::endl;
		}
	}
	
};  

