#include"log.cpp"

namespace bank_namespace{

	class acc;

	class transaction{

		friend class acc;

		//private data members

		std::string reciever;

		std::string note;

		long double before_balance;

		long double after_balance;

		long double amount;

		//public methords

	public:

		transaction(std::string,std::string,long double,long double);

		void display();

	};

	transaction::transaction(std::string reciever,std::string note,long double before_balance,long double amount){

		this->reciever =  reciever;

		this->note = note;

		this->before_balance = before_balance;

		this->after_balance  = before_balance-amount;

		this->amount =  amount;
	}

	void transaction::display(){

		std::cout<<"\n############## TRANSACTION ############\n";

		std::cout<<"reciever :: "<<this->reciever<<"\n";

		if(note!="")std::cout<<"note :: "<<this->note<<"\n";

		std::cout<<"before balance :: "<<this->before_balance<<"\n";

		std::cout<<"amount :: "<<this->amount<<"\n";

		std::cout<<"after_balance :: "<<this->after_balance<<"\n";
	}


};



