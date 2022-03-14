#include "FindTRs.c"
#include <fstream>
string seq, ID,line;

ifstream Input_File;
int main(int argc, char *argv[])
{
	int MaxCore =100, MinTR = 10;
	string Input = "",temp;
	
	if( argc < 2 ) 
	{
		cout<<"Arguments format is wrong!.....Arguments: (Fasta file)   (Max Core size)  (Min TR length)\n";
		return 0;
	}
   else if( argc == 2)
   {
	   temp = argv[1];
	   
	   if( temp.find(".fasta"))
	   {
			cout<<"defualt settings are: Maximum Core Size = 100, Minimum TR size = 10\n";
			Input = temp;
	   }
		else
		{
			cout<<"Arguments format is wrong!.....Arguments: (Fasta file)   (Max Core size)  (Min TR length)\n";
			return 0;
		}
		
    }
	else if( argc == 4)
	{
		 temp = argv[1];
		if( temp.find(".fasta"))
	    {
			Input = temp;
			MaxCore = stoi(argv[2]);
			MinTR =  stoi(argv[3]);
			cout<<"(Max Core size): "<<MaxCore<<"\n(Min TR length): "<<MinTR<<"\n";
	    }
	}
	else
	{
		cout<<"Arguments format is wrong!.....Arguments: (Fasta file)   (Max Core size)  (Min TR length)\n";
		return 0;
	}

	

	
	
	
	seq = "";
	Input_File.open(Input,ios::in);
	getline(Input_File, line);
	
	int NumberOfChromosomes = 0, Reported =0;
	if(line != "")
	{
		NumberOfChromosomes++;
		ID = line;
		while(getline(Input_File, line))
		{
			if( line[0] == '>')
			{
				NumberOfChromosomes++;
				Reported++;
				TandemRepeatsFinder TR;
				TR.initiate(ID, seq, MaxCore, MinTR);
				seq = "";
				ID = line;
				cout<<ID<<"\n";
			}
			seq += line;
		}
		if(NumberOfChromosomes != Reported)
		{
			TandemRepeatsFinder TR;
			TR.initiate(ID, seq, MaxCore, MinTR);
		}

	}
	else
		cout<<"The file is empty...";
	
	cout<<"\nDone...";
	Input_File.close();
	return 0;
}

