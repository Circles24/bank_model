#include"fxns.cpp"

namespace{

	const std::string currentDateTime() {

	    time_t     now = time(0);

	    struct tm  tstruct;

	    char       buf[80];

	    tstruct = *localtime(&now);

	    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	    return buf;
	}

	void log_save(std::string arg){

		int srno;

		std::fstream fin("log/srno.txt",std::ios::in);

		if( !fin )std::cout<<"unable to find required serial no file\n";

		fin>>srno;

		srno++;

		fin.close();

		std::fstream fout("log/srno.txt",std::ios::out);

		fout<<srno;

		fout.close();

		fout.open("log/log.txt",std::ios::out|std::ios::app);

		fout<<currentDateTime()<<" "<<arg<<"\n";

		fout.close();


	}

};

