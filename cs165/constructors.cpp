#include <iostream>



class bank_account{

public:

	bank_account()
	{
		this->dollars = 0;
		this->cents = 0;
	}

	bank_account(bank_account &b)
	{
		this->dollars = b.dollars;
		this->cents = b.cents;
	}

	bank_account(double balance)
	{
		this->dollars = static_cast<int>(balance);
		this->cents = static_cast<int>((balance - this->dollars) * 100);
	}

	bank_account(int dollars, int cents = 0)
	{
		this->dollars = dollars;
		this->cents = cents;
	}

	~bank_account()
	{
		//intentionally left blank
	}

	// bank_account(int dollars)
	// {
	// 	this->dollars = dollars;
	// 	this->cents = 0;
	// }

	// bank_account() : dollars(0), cents(0)
	// {
	// 	//intentionally left blank
	// }

	double balance()
	{
		return this->dollars + static_cast<double>(this->cents) / 100.0;
	}

private:

	int dollars;
	int cents;

};

int main(int argc, char **argv)
{
	bank_account mine;
	bank_account yours(1000.37);
	bank_account ours(1300, 97);
	bank_account theirs(10);


	mine = bank_account(1000.37);
	mine = bank_account();

	std::cout << mine.balance() << std::endl;

	return 0;
}
