//Nicole Chow	nchow24	(250725575)
//Dec. 8, 2017
//Transaction class header
//Transaction structure contains a client, amount and accounts involved

struct Transaction
{
	int amount;					//amount requested in the transaction
	char type[256];				//transaction type (d, w or t)
	int client;					//the client requesting the transaction
	struct Account *accOne;		//the account involved in the transaction
	struct Account *accTwo;		//second account involved in the transacton (only used for type t)
};