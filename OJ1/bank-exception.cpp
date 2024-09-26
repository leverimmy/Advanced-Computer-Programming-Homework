#include <iostream>
#include <string>
#include <stdexcept>

// 填空定义
#define FILL_1 InvalidInitialDepositException()
#define FILL_2 amount < 0
#define FILL_3 balance < amount
#define FILL_4 InsufficientFundsException()
#define FILL_5 InvalidInitialDepositException

// 自定义异常类
class InvalidInitialDepositException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid initial deposit";
    }
};

class InsufficientFundsException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Insufficient funds";
    }
};

class InvalidAmountException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid amount";
    }
};

// 银行账户类
class BankAccount {
private:
    std::string accountNumber;
    std::string holderName;
    int balance;

public:
    BankAccount(const std::string& number, const std::string& name, int initialDeposit) {
        if (initialDeposit < 0) {
            // 填空1: 抛出适当的异常
            throw FILL_1;
        }
        accountNumber = number;
        holderName = name;
        balance = initialDeposit;
    }

    void deposit(int amount) {
        // 填空2: 检查金额是否为负,如果是则抛出异常
        if (FILL_2) {
            throw InvalidAmountException();
        }
        balance += amount;
    }

    void withdraw(int amount) {
        if (amount < 0) {
            throw InvalidAmountException();
        }
        // 填空3: 检查余额是否足够,如果不够则抛出异常
        if (FILL_3) {
            throw FILL_4;
        }
        balance -= amount;
    }

    int getBalance() const {
        return balance;
    }
};

int main() {
    try {
        // 创建账户
        int m;
        std::cin>>m;
        BankAccount account("1234567890", "John Doe", m);
        int n;
        std::cin >> n;
        
        for (int i = 0; i < n; i++) {
            int operation, amount;
            std::cin >> operation >> amount;
            
            try {
                if (operation == 1) {
                    account.deposit(amount);
                } else if (operation == 2) {
                    account.withdraw(amount);
                }
                std::cout << account.getBalance() << std::endl;
            }
            catch (const InsufficientFundsException& e) {
                std::cout << e.what() << std::endl;
            }
            catch (const InvalidAmountException& e) {
                std::cout << e.what() << std::endl;
            }
        }
    }
    // 填空5: 捕获 初始金额为负数 的异常
    catch (const FILL_5& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}