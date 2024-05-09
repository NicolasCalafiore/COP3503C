// write your code here!
#include <string>
#include <iomanip>

using namespace std;
class BankAccount{
protected:
    int id;
    std::string name;
public:
    BankAccount(int id, string name){
        this->id = id;
        this->name = name;
    };
    virtual void CalculateAmount() const = 0;
    virtual void Display() const = 0;
    virtual void Deposit(float amount) = 0;
    virtual bool Withdraw(int amount) = 0;
    virtual int getType() = 0;

    int getID(){return id;}
    string getName(){return name;}

};

class CheckingAccount : virtual public BankAccount{
protected:
    float amount;

public:

    int type = 1;
    CheckingAccount(float amount,int id, string name) : BankAccount(id, name){
        this->amount = amount;
    }
    void CalculateAmount() const override{}
    void Display() const override {
        std::cout << std::fixed << std::setprecision(2);

        cout << this->name << "(" << id << "):" << endl;
        cout << "\tChecking Account: $" << amount << endl;
    }
    void Deposit(float deposit) override {
        this->amount += deposit;
    }
    int getType() override{ return 1;}
    bool Withdraw(int value) override {
        if(this->amount - value < 0) return false;

        this->amount -= value;
        return true;

    } //


    float getAmount() const{
        return amount;
    }

    void setAmount(float amount){
        this->amount = amount;
    }
};

class SavingsAccount : virtual public BankAccount{

protected:
    float amount;
    void setAmount(float value){
        this->amount = value;
    }

public:
    int getType() override{ return 2;}

    SavingsAccount(float amount,int id, string name) : BankAccount(id, name){
        this->amount = amount;
    }

    void CalculateAmount() const override{}
    void Display() const override {
        std::cout << std::fixed << std::setprecision(2);
        cout << this->name << "(" << id << "):" << endl;
        cout << "\tSavings Account: $" << amount << endl;
    }
    void Deposit(float deposit) override {
        this->amount += deposit;
    }
    bool Withdraw(int amount) override {}

    float getAmount() const{
        return amount;
    }
    bool Transfer(CheckingAccount& check_acc, float value){
        if(this->amount - value < 0) return false;
        check_acc.Deposit(value);
        this->amount -= value;
        return true;
    }

    float CompoundEarnings(float rate){
        float increase =  this->amount * rate;
        this->amount += increase;
        return increase;
    }

};

class InvestmentAccount : virtual public CheckingAccount, virtual private SavingsAccount{
    // The idea is for any earnings from the investment side to
    //be immediately available in a checking account format as to not have the user worry about transferring
    //money at all.

protected:
    float amount;
    SavingsAccount save;
    CheckingAccount check;
public:

    int getType() override{ return 3;}
    InvestmentAccount(float amount, int id, string name) : BankAccount(id, name), CheckingAccount(0, id, name), SavingsAccount(amount, id, name), save(amount, id, name), check(0, id, name) {
        this->amount = amount;
    }

    void CalculateAmount() const override{}
    void Display() const override {
        std::cout << std::fixed << std::setprecision(2);
        cout << this->name << "(" << id << "):" << endl;
        cout << "\tTotal: $" << (save.getAmount() + check.getAmount()) << endl;
        cout << "\t\tImmediate Funds: $" << check.getAmount() << endl;
        cout << "\t\tInvestment: $" << save.getAmount() << endl;
    }
    void Deposit(float deposit) override {
        save.Deposit(deposit);
    }  //Go to savings account
    bool Withdraw(int amount) override {}

    float getAmount(){  //Get total in both savings and checkings
        return save.getAmount() + check.getAmount();
    }

    float CompoundEarnings(float rate){
        float increase =  this->amount * rate;
        this->check.Deposit(increase);
        return increase;
    }

};

























