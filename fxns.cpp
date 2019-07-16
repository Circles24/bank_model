#include"include.cpp"

namespace bank_namespace{

	#define line_end std::cout<<"\n\n***********************************************\n\n";

	std::string get_phone(){

		std::string phone_no;

		bool possible(false);

		while( !possible ){

			possible = true;

			std::cout<<"please enter your phone no\n";

			std::cin>>phone_no;

			if( phone_no.size() != 10 ){

				std::cout<<"phone no should be of only 10 digit\n";

				possible = false;
			}

			for(auto i: phone_no)if( i>'9' || i<'0' ){

				std::cout<<"alpha numiric character in phone no isn't possible \n";
			
				possible = false;

				break;
			}

			if( !possible )std::cout<<"you entered wrong phone no\n";
 
		}
		
		return phone_no;


	}


	std::string decrypt(std::string str){

		for(int i=0;i<str.length();i++)str[i]=str[i];

		return str;
	}

	
	int getch() {

	    int ch;

	    struct termios t_old, t_new;

	    tcgetattr(STDIN_FILENO, &t_old);

	    t_new = t_old;

	    t_new.c_lflag &= ~(ICANON | ECHO);

	    tcsetattr(STDIN_FILENO, TCSANOW, &t_new);

	    ch = getchar();

	    tcsetattr(STDIN_FILENO, TCSANOW, &t_old);

	    return ch;
	}





	std::string getpass(const char *prompt, bool show_asterisk=true)
	{

		int x=0;

	  const char BACKSPACE=127;

	  const char RETURN=10;

	  std::string password;

	  unsigned char ch=0;

	  std::cout <<prompt<<std::endl;

	  while((ch=getch())!=RETURN || x==0)

	    {

	    	if(ch==RETURN)continue;
	       if(ch==BACKSPACE)

	         {
	            if(password.length()!=0)

	              {
	                 if(show_asterisk)

	                 std::cout <<"\b \b";

	                 password.resize(password.length()-1);

	              }
	         }

	       else
	         {

	             password+=ch;

	             if(show_asterisk)

	                 std::cout <<'*';

	         }

	         x++;
	    }

	  std::cout <<std::endl;

	  return password;

	}

	int get_int(){

		std::string s;

		int x=0;

		bool repeat(true);

		while(repeat){

			repeat = false;

			std::cin>>s;

			for(int i=0;i<s.length();i++)if(s[i]>'9' || s[i]<'0'){

				repeat = true;

				std::cout<<"thats not a number\n";

				break;
			}

			if(s.length()>=9){

				std::cout<<"out of range\n";

				repeat =  true;
			}
		}



		for(int i=0;i<s.length();i++){

			x+=s[i]-'0';

			if(i<s.length()-1)x*=10;
		}

		return x;

	}

	std::string get_str(int num){

		std::string str;

		if(num==0)return "0";

		while(num){

			str+=(char)('0'+num%10);

			num/=10;
		}

		for(int i=0;i<str.length()/2;i++){

			std::swap(str[i],str[str.length()-1-i]);
		}

		return str;
	}


}




