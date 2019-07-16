#include"acc.cpp"

namespace bank_namespace{


	class bank{

		//private data members

		std::map< std::string , acc* > username_to_acc_map;

		std::map< std::string , std::string > phone_to_username;

		std::map< std::string , std::string > email_to_username;

		std::string password;

		bank();

		static bool verify();

		int inner_menu();

		bool remove_user();

		bool change_password();

		void view_phoneno();

		void view_email();

		int admin_inner_menu();

		void admin_menu();

		void acc_login();

		std::string get_name();

		bool add_amount();

	public:

		static bank* get_bank();

		void display();

		bool create_account();

		void menu();


	};

	bank::bank(){

		
	}

	bool bank::verify(){

		std::string password,temp;

		std::fstream fin("log/private.txt");

		if( !fin ){

			std::cout<<"some internal essential files are missing\n";

			return 0;
		}

		fin>>password;

		password = bank_namespace::decrypt(password);

		std::cout<<"enter the password to get things done\n";

		temp=getpass("enter the password",true);

		if( temp != password){

			std::cout<<"wrong password\n";

			return 0;
		}

		return 1;
	}

	bank* bank::get_bank(){

		if(!bank::verify())return NULL ;

		return new bank();
	}

	void bank::display(){

		if(!bank::verify())return ;

		std::system("clear");

		std::system("whoami");

		std::cout<<"\n\n##### HAVE A NICE TOUR OF THE BANK #####\n\n";

		std::cout<<"\n\nuser name to account map\n";

		for(auto i:username_to_acc_map){

			i.second->display();
		}

		std::cout<<"\n\nphone to user_name map\n";

		for(auto i: phone_to_username){

			std::cout<<i.first<<"   "<<i.second<<"\n";
		}

		std::cout<<"\n\nemail_to_username map\n";

		for(auto i: email_to_username){

			std::cout<<i.first<<"   "<<i.second<<"\n";
		}

	}

	bool bank::create_account(){

		std::string user_name,pass1("pass"),pass2,phone,email;

		bool repeat(true);

		while(repeat){

			repeat = false;

			std::cout<<"enter you user_name\n";

			std::cin>>user_name;

			if(username_to_acc_map.find(user_name)!=username_to_acc_map.end()){
				
				repeat = true;

				std::cout<<"this user_name is already occupied\n";

			}


			if( !repeat ){

				std::cout<<"enter you phone\n";

				phone=get_phone();

				if(phone_to_username.find(phone)!=phone_to_username.end()){

					repeat = true;

					std::cout<<"this phone no is already used\n";
				}
			}

			if( !repeat ){

				std::cout<<"enter you email\n";

				std::cin>>email;

				if(email_to_username.find(email)!=email_to_username.end()){

					repeat = true;

					std::cout<<"this email no is already used\n";
				}
			}

			if(repeat){

				std::cout<<"Do you want to repeat\n\n";

				std::cin>>repeat;

				if(!repeat)return 0;
			}


		}

		while(pass1!=pass2 || pass1.length()<6 ){

			pass1=getpass("enter your password\n");

			pass2=getpass("enter the same password");

			if(pass1!=pass2)std::cout<<"you have entered wrong password\n";

			else if(pass1.length()<6)std::cout<<"password length must be 6 minimum\n";

		}

		acc* temp_acc = new acc(user_name,pass1,phone,email);

		username_to_acc_map[user_name] = temp_acc;

		phone_to_username[phone] = user_name;

		email_to_username[email] = user_name;

		return 1;

	}

	std::string bank::get_name(){

		std::string str;

		int choice;

		std::cout<<"1 :: user_name\n2 :: phone_no\n3 :: email\n";

		choice=get_int();

		if(choice==1){

			std::cout<<"enter your user_name\n";

			std::cin>>str;
		}

		else if(choice==2){

			str=get_phone();

			if(phone_to_username.find(str)==phone_to_username.end()){

				str="";
			}

			else str=phone_to_username[str];
		}

		else if(choice==3){

			std::cout<<"enter your email id\n";

			std::cin>>str;

			if(email_to_username.find(str)==email_to_username.end()){


				str="";
			}

			else str = email_to_username[str];
		}

		else {

			std::cout<<"wrong choice\n";

			str="";
		}

		return str;
	}

	void bank::acc_login(){

		int choice;

		std::string str(get_name());

		if(username_to_acc_map.find(str)==username_to_acc_map.end()){

			std::cout<<"you entered wrong input\n";

			return ;
		}

		std::string pass;

		bool repeat(true);

		while(repeat){

			repeat = false;

			pass=getpass("enter you account password",true);

			if(pass!=username_to_acc_map[str]->password){

				std::cout<<"wrong password\n";

				repeat = true;

				std::cout<<"do you wish to continue (0/1)\n";

				choice = get_int();

				if(choice==0)return ;
			}

		}

		if(username_to_acc_map[str]->menu()){

			std::string user;

			std::cout<<"enter the user name of the benefactor\n";

			std::cin>>user;

			if(username_to_acc_map.find(user)==username_to_acc_map.end()){

				std::cout<<"this user doesn't exists\n";
			}

			else{

				long double amount;

				std::cout<<"enter the amount to be transferred\n";

				amount = get_int();

				if(amount > username_to_acc_map[str]->balance){

					std::cout<<"your current balance is insufficient\n";
				}

				else {

					long double balance1,balance2;

					balance1 = username_to_acc_map[str]->balance;

					balance2 = username_to_acc_map[user]->balance;

					transaction t1(user,"send",balance1,amount),t2(str,"recieved",-1*balance2,amount);

					username_to_acc_map[str]->transaction_list.push_back(t1);

					username_to_acc_map[user]->transaction_list.push_back(t2);

					username_to_acc_map[str]->balance-=amount;

					username_to_acc_map[user]->balance+=amount;

					std::cout<<"transfer succeded\n";
				}

			}

			username_to_acc_map[str]->menu();
		}

		return ;
	}

	bool bank::remove_user(){

		bool repeat(true);

		std::string user_name,phone,email;

		while(repeat){	

			repeat = true;

			user_name=get_name();

			if(username_to_acc_map.find(user_name)==username_to_acc_map.end()){

				std::cout<<"you entered wrong input\n";

				repeat = true;

				std::cout<<"do you wish to continue (1/0)\n";

				if(get_int()==0)return 0;
			}

		}

		phone = username_to_acc_map[user_name]->phone_no;

		email = username_to_acc_map[user_name]->email;

		username_to_acc_map.erase(user_name);

		phone_to_username.erase(phone);

		email_to_username.erase(email);

		return 1;
	}

	bool bank::change_password(){

		bool repeat(true);

		int choice;

		std::string pass1,pass2;

		while(repeat){

			repeat = false;

			pass1=getpass("enter your new password\n");

			pass2=getpass("enter the same password");

			if(pass1!=pass2){

				std::cout<<"you have entered wrong password\n";

				repeat = true;
			}

			else if(pass1.length()<6){

				std::cout<<"password length must be 6 minimum\n";

				repeat = true;
			}

			if(repeat){

				std::cout<<"do you want to repeat (1/0) \n";

				choice = get_int();

				if(choice==0)return false;

			}

		}

		password = pass1;

		std::fstream fout("log/private.txt",std::ios::out);

		fout<<pass1;

		fout.close();

		return true;

	}

	void bank::view_phoneno(){

		int srno(0);

		std::cout<<"Here are phone no of every user sorted acc to phone no\n";

		for(auto i:phone_to_username){

			std::cout<<srno++<<" "<<i.first<<" "<<i.first<<"\n";
		}

		return ;

	}

	void bank::view_email(){

		int srno(0);

		std::cout<<"Here are email of every user sorted acc to email\n";

		for(auto i:email_to_username){

			std::cout<<srno++<<" "<<i.first<<" "<<i.first<<"\n";
		}

		return ;

	}

	int bank::admin_inner_menu(){

		line_end

		std::cout<<"\n############## ADMIN MENU #############\n\n";

		std::cout<<std::fixed<<std::setw(20)<<" view the bank :: 0 \n";

		std::cout<<std::fixed<<std::setw(20)<<" view the phone_no :: 1 \n";

		std::cout<<std::fixed<<std::setw(20)<<" view the email :: 2 \n";

		std::cout<<std::fixed<<std::setw(20)<<" change password :: 3 \n";

		std::cout<<std::fixed<<std::setw(20)<<" remove a user :: 4 \n";

		std::cout<<std::fixed<<std::setw(20)<<" refresh balance of user :: 5 \n";

		std::cout<<std::fixed<<std::setw(20)<<" exit :: 6 \n";

		return get_int();

		line_end

	}

	bool bank::add_amount(){

		log_save("add_amount");

		bool repeat(true);

		std::string user_name;

		while(repeat){

			repeat = false;

			std::cout<<"enter the user name\n";

			std::cin>>user_name;

			if(username_to_acc_map.find(user_name)==username_to_acc_map.end()){

				repeat = true;

				std::cout<<"wrong input\n";
			}

			if(repeat){

				std::cout<<"do you wish to continue (1/0)\n";

				if(get_int()==0){

					log_save("returning 0");

					return 0;
				}
			}

		}

		log_save("user_name "+user_name);

		std::cout<<"enter the amount you wish to add\n";

		 int amount=get_int();

		username_to_acc_map[user_name]->balance+=amount;

		log_save(user_name + "amount"+get_str(amount));

		return true;
	}

	void bank::admin_menu(){

		log_save("admin menu");

		if(!verify)return ;

		while(1){

			switch(admin_inner_menu()){

				case 0:

				{
					log_save("admin case 0");

					this->display();

				}

				break;

				case 1:

				{
					log_save("admin case 1");

					this->view_phoneno();

				}

				break;

				case 2:

				{

					log_save("admin case 2");

					this->view_email();

				}

				break;

				case 3:

				{
					log_save("admin case 3");

					if(this->change_password()){

						std::cout<<"OP SUCESSFUL\n";

						log_save("op succeeded");
					}

					else {

						std::cout<<"OP FALED\n";

						log_save("op faiiled");
					}

				}

				break;

				case 4:

				{
					log_save("admin case 4");

					if(this->remove_user()){

						log_save("op success");

						std::cout<<"Done\n";
					}

					else {

						std::cout<<"failed\n";

						log_save("op faiiled");

					}

				}

				break;

				case 5:

				{
					log_save("admin case 5");

					if(add_amount()){

						std::cout<<"Done\n";

						log_save("op sccess");
					}

					else {

						std::cout<<"failed\n";

						log_save("op failed");

					}

				}

				break;

				case 6:

				{	
					log_save("admin case 6");

					std::cout<<"have a happy ay ahead ADMIN\n";

					return ;

				}

				break;

				default:

				{

					log_save("admin default");

					std::cout<<"you entered a wrong choice\n";

				}


			}
		}

		log_save("admin menu return");
	}

	int bank::inner_menu(){

		log_save("inner_MENU");

		//std::system("clear");

		line_end

		std::cout<<"\n################ MENU ################\n\n";

		std::cout<<std::fixed<<std::setw(15)<<"ADMIN log in "<<std::setw(10)<<" :: 0\n";

		std::cout<<std::fixed<<std::setw(15)<<"log in"<<std::setw(10)<<" :: 1\n";

		std::cout<<std::fixed<<std::setw(15)<<"sign_up"<<std::setw(10)<<" :: 2\n";

		std::cout<<std::fixed<<std::setw(15)<<"exit "<<std::setw(10)<<" :: 3\n";

		int choice;

		choice = get_int();

		line_end

		log_save("inner menu return");

		return choice;
	}

	void bank::menu(){

		log_save("menu");

		while(1){

			switch(inner_menu()){


				case 0:
				{
					log_save("case 0");

					if(verify())admin_menu();

				}

				break;

				case 1:
				{

					log_save("case 1");

					acc_login();

				}

				break;

				case 2:
				{

					log_save("case 2");

					create_account();

				}

				break;

				case 3:

				{

					log_save("case 3");

					std::cout<<"have a happy day ahead\n";

					return ;

				}

				break;

				default:

				{
					log_save("default");

					std::cout<<"Wrong choice\n";
				}

				break;
			}

		}

		log_save("menu return");

	}
	

};


int main(){

	log_save("main");

	std::system("whoami");

	std::cout<<"welcome\n";

	bank_namespace::bank* b(NULL);

	b = bank_namespace::bank::get_bank();

	if(b)b->menu();

	return 0;

}