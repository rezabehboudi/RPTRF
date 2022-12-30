#include "FindTRs.cpp"
#include <fstream>
string seq, ID, line;
void help();
ifstream Input_File;
int main(int argc, char *argv[])
{
	int MaxCore = 100, MinTR = 10;
	string Input = "sequence.fasta", temp;
	int opt;

	while ((opt = getopt(argc, argv, ":m:t:s:h")) != -1)
	{
		switch (opt)
		{
		case 'm':
			MaxCore = atoi(optarg);
			break;
		case 't':
			MinTR = atoi(optarg);
			break;
		case 's':
			Input = optarg;
			break;
		case 'h':
			help();
			break;
		}
	}

	seq = "";
	Input_File.open(Input, ios::in);
	getline(Input_File, line);

	int NumberOfChromosomes = 0, Reported = 0;
	if (line != "")
	{
		NumberOfChromosomes++;
		ID = line[2];
		while (getline(Input_File, line))
		{
			if (line[0] == '>')
			{
				NumberOfChromosomes++;
				Reported++;
				TandemRepeatsFinder TR;
				TR.initiate(to_string(NumberOfChromosomes), seq, MaxCore, MinTR);
				seq = "";
				ID = line;
				cout << ID << "\n";
			}
			seq += line;
		}
		if (NumberOfChromosomes != Reported)
		{
			TandemRepeatsFinder TR;
			TR.initiate(to_string(NumberOfChromosomes), seq, MaxCore, MinTR);
		}
	}
	else
		cout << "The file is empty...";

	cout << "\nDone...\n\n";
	Input_File.close();
	return 0;
}

void help()
{
	cout <<
		"\n\
****RPTRF: A Rapid Perfect Tandem Repeat Finder Tool for DNA Sequences**** \n\n\
	To run RPTRF with the defult parameters use the following command: \n\
		./RPTRF -s  Input_Sequence.fasta\n\n\
	Example of using arguments:\n\
		./RPTRF -s  Input_Sequence.fasta -m 100 -t 10\n\n\
	Arguments:\n\
	-s		Input sequencce\n\
	-m		Maximum Motif Size(Defult value = 100)\n\
	-t		Minimum length of Tandem Repeats(Defult value = 10) \n\
";
	exit(0);
}
