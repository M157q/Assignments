// written in C++11 by 0016043 shunyi
#include <iostream>
#include <fstream>          //file io
#include <string>           //string
#include <vector>           //vector
#include <unordered_map>    //unordered_map C++11
#include <unordered_set>    //unordered_set C++11
#include <utility>          //pair

class Transaction
{
    public:
        std::string transaction_id;
        char transaction_type;
        std::string receive_account;
        int transfer_money;
};

class TransactionsTable
{
    public:
        void addTransaction(Transaction t)
        {
            this->transactions.push_back(t);
        }

        void printTransactionsTable()
        {
            for (Transaction& fuck:transactions)
            {
                std::cout << fuck.transaction_id << ", " << fuck.transaction_type << ", " << fuck.receive_account << ", " << fuck.transfer_money << std::endl; 
            }
        }

        std::vector<Transaction> transactions;
};

class Account
{
    public:
        std::string account_id;
        int account_money;
        int n_of_transactions;
        int done_transactions;
        TransactionsTable account_transactions;
};

class AccountsTable
{
    public:
        void addAccount(Account a)
        {
            this->accounts.insert( std::pair<std::string, Account>(a.account_id, a) );
        }

        std::unordered_map<std::string, Account> accounts;
};

int main (int argc, char *argv[])
{
    //read file begin
    std::ifstream infile (argv[1], std::ifstream::in);
    AccountsTable A_table;
    std::unordered_set<std::string> fuck_wait;

    if (infile.is_open())
    {
        int total_accounts; 
        infile >> total_accounts;

        for (int i = 0; i < total_accounts; i++)
        {
            Account A;

            infile >> A.account_id;
            infile >> A.account_money;
            infile >> A.n_of_transactions;
            if (A.n_of_transactions > 0) fuck_wait.insert(A.account_id);

            //std::cout << A.account_id << ", " << A.account_money << ", " << A.n_of_transactions << std::endl;

            for (int i = 0; i < A.n_of_transactions; i++)
            {
                Transaction T;
                infile >> T.transaction_id;
                infile >> T.transaction_type;

                if (T.transaction_type == 'T')
                {
                    infile >> T.receive_account;
                    infile >> T.transfer_money;
                }

                if (T.transaction_type == 'B')
                {
                    // B for balance.
                    // set receive account as oneself
                    // for the convenience computing below
                    T.receive_account = A.account_id;
                    T.transfer_money = 0;
                }

                //std::cout << T.transaction_id << ", " << T.transaction_type << ", " << T.receive_account << ", " << T.transfer_money  << std::endl;

                A.account_transactions.addTransaction(T);
            }

            A.done_transactions = 0;
            //A.account_transactions.printTransactionsTable();
            A_table.addAccount(A);
            //std::cout << "-----" << std::endl;
        }
    }
    infile.close();
    //end of read file
    

    //do transactions and print transaciton_log
    std::ofstream translog("transaction_log.txt", std::ofstream::out);
    int timestamp = 1;

    std::unordered_set<std::string> no_money;

    //if there is still a account haven't finish transactions, keep do it.
    while (!fuck_wait.empty())
    {
        std::unordered_set<std::string> lock;
        for (auto it = fuck_wait.begin(); it != fuck_wait.end();)
        {
            //std::cout << *it << std::endl;
            // if current account id is not be locked or have enough money.
            if ( lock.find(*it) == lock.end() && no_money.find(*it) == no_money.end() )
            {
                std::unordered_map<std::string, Account>::iterator account = A_table.accounts.find(*it);

                int& account_money = account->second.account_money;
                int& tran_index = account->second.done_transactions;
                int& account_max_tran = account->second.n_of_transactions;
                Transaction& tran = account->second.account_transactions.transactions[tran_index];
                //std::cout << tran_index << std::endl;
                int& transfer_money = tran.transfer_money;

                std::string tran_id     = tran.transaction_id;
                std::string account_id  = account->first;
                std::string receiver_id = tran.receive_account;
                
                // if receiver_id is locked, do next account transaction.
                if ( lock.find(receiver_id) != lock.end() )
                {
                    it++;
                    continue;
                }
                // if money is not enough, move current account_id to no_money set
                else if (account_money < transfer_money)
                {
                    no_money.insert(account_id);
                    fuck_wait.erase(it++);
                    continue;
                }
                else //receiver is not locked and current account have enough money
                {
                    // lock current account and receive account
                    lock.insert(account_id);
                    lock.insert(receiver_id);

                    // do the money transfer
                    account_money -= transfer_money;
                    std::unordered_map<std::string, Account>::iterator receiver = A_table.accounts.find(receiver_id);
                    receiver->second.account_money += transfer_money;

                    // if receiver is in no_money set before get money
                    // move it to wait map because now he have money.
                    // and remove receiver_id from no_money set
                    if ( no_money.find(receiver_id) != no_money.end() )
                    {
                        fuck_wait.insert(receiver_id);
                        no_money.erase(receiver_id);
                    }

                    // print current transfer log
                    translog << tran_id << " " << timestamp;
                    if (tran.transaction_type == 'B')
                    {
                        // balance need to print the current money of the current account
                        translog << " " << account_money;
                    }
                    translog << std::endl;
                    tran_index++;

                    // check if the current account have finished all transactions or not
                    if (tran_index == account_max_tran)
                    {
                        fuck_wait.erase(it++);
                    }
                    else
                    {
                        it++;
                    }
                }
            }
            else
            {
                it++;
            }
        }
        timestamp++;
    }
    translog.close();
    //end of print transaction log
    
    //begin to print final_state
    std::ofstream finalstate ("final_state.txt", std::ofstream::out);
    for (auto it = A_table.accounts.begin(); it != A_table.accounts.end(); it++)
    {
        finalstate << it->first << " " << it->second.account_money << std::endl;
    }
    finalstate.close();
    //end of print final_state

    return 0;
}
