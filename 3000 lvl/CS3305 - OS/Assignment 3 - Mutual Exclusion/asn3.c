//Nicole Chow	nchow24	(250725575)
//Dec 8, 2017
//Assignment3 main

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "Account.h"
#include "Transaction.h"
#include "Client.h"
#include "AccountArray.h"
#include "TransactionArray.h"
#include "ClientArray.h"

#define true 1
#define false 0

void *request(void * k);

pthread_mutex_t lock;
struct TransactionArray transactions;					//array of requested transactions
struct AccountArray accounts;							//array of accounts
struct ClientArray clients;								//array of clients
int numTransactions;									//number of transactions

int main(void)
{
	//initialize array of accounts with 1 NULL account (NULL account has index = 0)
	initAArray(&accounts, 1);
	struct Account accNull;
	accNull.index = 0;
	accNull.balance = 0;
	accounts.array[0] = accNull;

	//initialize array of transactions with 1 NULL transaction (NULL account has client = c0)
	initTArray(&transactions, 1);
	struct Transaction transactionNull;
	transactionNull.client = 0;
	transactions.array[0] = transactionNull;

	//initialize array of clients with 1 NULL client
	initCArray(&clients, 1);
	struct Client clientNull;
	clients.array[0] = clientNull;

	int numAccounts = 0;			//number of 'real' accounts
	numTransactions = 0;			//number of 'real' transactions
	int clientNum = 1;				//the client's index
	int numClients = 0;				//the number of clients

	//open input file for reading
	FILE * file;
	file = fopen("Assignment_3_input_file.txt", "r");
	if (file != NULL) {
		char line[256];
		while (fgets(line, sizeof line, file) != NULL) {
			//deposit initial amounts (depx, where x is a positive integer)
			if (strstr(line, "dep")) {
				char* token = strtok(line, " ");
				char prevToken[256];
				while (token) {
					//locate an amount to deposit
					if (strstr(prevToken, "acc") != NULL) {
						//get amount to deposit
						int amount = atoi(token);
						
						//get account index
						char index[256];
						strncpy(index, prevToken+3, sizeof(index));
						int accIndex = atoi(index);

						//check if account already exists
						int accFound = false;
						int arrayIndex = 0;
						for (int i = 0; i < numAccounts; i++) {
							if (accounts.array[i].index == accIndex) {
								accFound = true;
								arrayIndex = i;
							}
						}

						//update existing balance (account exists)
						if (accFound) {
							accounts.array[arrayIndex].balance = accounts.array[arrayIndex].balance + amount;
						//create new account and insert in array
						} else {
							struct Account acc;
							acc.index = accIndex;
							acc.balance = amount;
							insertAArray(&accounts, acc);
							numAccounts++;
						}
					}
					strcpy(prevToken, token);
					token = strtok(NULL, " ");
				}

			//get each client info (cx, where x is a positive integer)
			} else {
				//client lines contain "acc" and not "dep"
				if (strstr(line, "acc")) {
					numClients++;

					//store line as array of words
					char words[256];
					strcpy(words, line);
					char *pch;
					int i = 0;
					pch = strtok(words, " ");
					char arr[256][256];
					while (pch != NULL) {
						strcpy(arr[i++], pch);
						pch = strtok(NULL, " ");
					}

					//locate next transaction
					char* token = strtok(line, " ");
					char prevToken[256];
					int wordIndex = 0;
					while (token) {
						if (strcmp(prevToken, "d") == 0 || strcmp(prevToken, "w") == 0 || strcmp(prevToken, "t") == 0) {
							//create a deposit or withdrawal transaction
							if (strcmp(prevToken, "d") == 0 || strcmp(prevToken, "w") == 0) {
								
								//find the account
								int accIndex = atoi(token + 3);
								struct Account *account;
								for (int i = 0; i < numAccounts; i++) {
									if (accounts.array[i].index == accIndex) {
										account = &accounts.array[i];
									}
								}
							
								//create transaction and store in array
								struct Transaction trans;
								trans.client = numClients;
								strcpy(trans.type, prevToken);
								trans.accOne = account;
								trans.accTwo = &accNull;
								trans.amount = atoi(arr[wordIndex + 1]);
								insertTArray(&transactions, trans);

							//create a transfer transaction
							} else {
								//find the account to transfer from
								int accIndex = atoi(token + 3);
								struct Account *accountFrom;
								for (int i = 0; i < numAccounts; i++) {
									if (accounts.array[i].index == accIndex) {
										accountFrom = &accounts.array[i];
									}
								}

								//find the account to transfer to
								accIndex = atoi(arr[wordIndex + 1] + 3);
								struct Account *accountTo;
								for (int i = 0; i < numAccounts; i++) {
									if (accounts.array[i].index == accIndex) {
										accountTo = &accounts.array[i];
									}
								}

								//create transaction and store in array
								struct Transaction trans;
								trans.client = numClients;
								strcpy(trans.type, prevToken);
								trans.accOne = accountFrom;
								trans.accTwo = accountTo;
								trans.amount = atoi(arr[wordIndex + 2]);
								insertTArray(&transactions, trans);
							}
							numTransactions++;
						}
						wordIndex++;
						strcpy(prevToken, token);
						token = strtok(NULL, " ");
					}
				}
			}
		}
	}

	//create thread
	if (pthread_mutex_init(&lock, NULL) != 0) {
		return 1;
	}

	for (int i = 0; i < numClients; i++){
		struct Client client;
		insertCArray(&clients, client);
		clients.array[i].err_thread = pthread_create(&clients.array[i].thread, NULL, &request, (void *)(i+1));
	}

	for (int i = 0; i < numClients; i++) {
		pthread_join(clients.array[i].thread, NULL);
	}

	pthread_mutex_destroy(&lock);

	//write the final account values to output file
	FILE * fp;
	fp = fopen("Assignment_3_output_file.txt", "w");
	for (int i = 0; i < numAccounts; i++) {
		fprintf(fp, "acc%d %d ", accounts.array[i].index, accounts.array[i].balance);

	}
	fclose(fp);

	return 0;
}


/*
THREAD FUNCTION: DEPOSIT, WITHDRAW, TRANSFER
Parameter k is the index of a client
*/
void *request(void * k) {
	//find all transactions requested by client k
	for (int i = 0; i < numTransactions; i++) {
		//deposit (no checking of balance needed for a deposit)
		if ((transactions.array[i].client) == k && (strcmp(transactions.array[i].type, "d") == 0)) {
			pthread_mutex_lock(&lock);
			transactions.array[i].accOne->balance = transactions.array[i].accOne->balance + transactions.array[i].amount;
			pthread_mutex_unlock(&lock);
		} else {
			//withdraw
			if ((transactions.array[i].client) == k && (strcmp(transactions.array[i].type, "w") == 0)) {
				pthread_mutex_lock(&lock);
				
				//check if money can be withdrawn
				if (transactions.array[i].accOne->balance >= transactions.array[i].amount) {
					transactions.array[i].accOne->balance = transactions.array[i].accOne->balance - transactions.array[i].amount;
				}
				pthread_mutex_unlock(&lock);
			} else {
				//transfer
				if ((transactions.array[i].client) == k && (strcmp(transactions.array[i].type, "t") == 0)) {
					pthread_mutex_lock(&lock);
					//check if money can be transfered
					if (transactions.array[i].accOne->balance >= transactions.array[i].amount) {
						transactions.array[i].accOne->balance = transactions.array[i].accOne->balance - transactions.array[i].amount;
						transactions.array[i].accTwo->balance = transactions.array[i].accTwo->balance + transactions.array[i].amount;
					}
					pthread_mutex_unlock(&lock);
				}
			}
		}
	}
	return 0;
}