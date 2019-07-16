
#include"transaction.cpp"

namespace bank_namespace{

	class bank;

	class acc{

		friend class bank;

		//private data member of our class

		std::string user_name;

		std::list<transaction> transaction_list;

		std::string password;

		long double balance;

		std::string phone_no;

		std::string email;

		//private methords

		int inner_menu();

		bool menu();

		acc(std::string,std::string,std::string,std::string);

		void display();

		bool do_transaction(std::string,std::string,long double);

		void change_phoneno();

		void change_email();

		void change_password();

		void view_transaction();

	};

	acc::acc(std::string user_name,std::string password,std::string phone_no,std::string email){


		this->user_name = user_name;

		this->password = password;

		this->balance = 0;

		this->phone_no = phone_no;

		this->email = email;


	}

	void acc::display(){


		std::cout<<"\n\n***********   "<<this->user_name<<"   ***********\n\n";

		std::cout<<"\n###### THIS IS YOUR ACCOUNT ##########\n";

		std::cout<<std::setw(20)<<"user_name :: "<<this->user_name<<"\n";

		std::cout<<std::setw(20)<<"balance :: "<<this->balance<<"\n";

		std::cout<<std::setw(20)<<"phone_no :: "<<this->phone_no<<"\n";

		std::cout<<std::setw(20)<<"email :: "<<this->email<<"\n";
	}


	bool acc::do_transaction(std::string reciever,std::string note,long double amount){

		if(amount > balance){

			std::cout<<"\n!!! your balance is'nt sufficient\n";

			return false;

		}

		transaction temp_transaction(reciever,note,this->balance,amount);

		transaction_list.push_back(temp_transaction);

		this->balance -= amount;

		return true;

	}

	int acc::inner_menu(){

		
		//std::system("clear");

		std::cout<<"******* ACC MENU ********\n";

		std::cout<<"display :: 0\n";

		std::cout<<"change phone_no :: 1\n";

		std::cout<<"change email :: 2\n";

		std::cout<<"do transactions :: 3\n";

		std::cout<<"change password :: 4\n";

		std::cout<<"view transactions :: 5\n";

		std::cout<<" exit :: 6\n";

		return get_int();
	}

	void acc::change_phoneno(){


		std::string phoneno;

		phoneno = get_phone();

		this->phone_no = phoneno;

	}

	void acc::change_email(){


		std::string email;

		std::cout<<"enter your new email\n";

		std::cin>>email;

		this->email = email;

	}

	void acc::view_transaction(){

		for(auto i:transaction_list)i.display();

		return ;
	}

	void acc::change_password(){

		std::string pass;

		while(1){

			pass = getpass("enter your password",true);

			if(pass.length()<6){

				std::cout<<"password needs to have a minimum length of 6 characters\n";

			}

			else return ;
		}

	}


	bool acc::menu(){

		while(1){

			switch(inner_menu()){

				case 0:

				{
					this->display();

				}

				break;

				case 1:

				{
					this->change_phoneno();

				}

				break;

				case 2:

				{
					this->change_email();

				}

				break;

				case 3:

				{
					

					return 1;

				}

				break;

				case 4:

				{
					this->change_password();

				}

				break;

				case 5:

				{

					this->view_transaction();
				}

				break;

				case 6:

				{

					std::cout<<"have a hapy day\n";

					return 0;
				}

				break;

				default:

				{

					std::cout<<"wrong choice\n";

				}

				break;

			}
		}
	}


};


