# RPTRF
**RPTRF: A Rapid Perfect Tandem Repeat Finder Tool for DNA Sequences**
<br><br>
## Run the executable
To run the executable file in Ubuntu, you may follow the steps:

1. Download the repository and unzip the file.  
2. Get access to the executable file from `executable/RPTRF` path or the Releases section of the the repository.
```
cd executable/
```
3. Make the RPTRF executable by the following command:
```
sudo chmod +x RPTRF
```
4. There are three options to get input DNA sequence: 
* Option 1:  Find sample sequnce from `dataset/Sample.fasta`.
* Option 2:  Download sequnce from NCBI ([GRCh38](https://www.ncbi.nlm.nih.gov/assembly/GCF_000001405.26/))
* Option 3:  Use your local DNA seuqnce in `.Fasta` format. 
5. To run with  the defult settings rund the following command(the output file will be created in your current directory):
```
./RPTRF -s ../dataset/sample.fasta
```
6. To use optional arguments use the follwoing command:

```
./RPTRF -s ../dataset/sample.fasta -m 100 -t 10
```

<br><br>
**Arguments table**:
<br>
 Flag | Definition                                                                                                  | Default |
|------|-------------------------------------------------------------------------------------------------------------|---------|
|  -s  | Input .Fasta sequnce path                                                                            |        |
|  -m  | Maximum motif length    	                                                                                  |    100    |
|  -t  | Minimum length of tandem repeats  	                                                                                    |   10   |
|  -h  | Access to manual in the command line	                                                                          |       |

<br><br>
**Output**:
Tandem repeats of the given sequence will be appeared in the result file with the following structure:
<br>




<br>

Tandem repeats of a given sequnce will be appeared in ``result-X.txt`` file(s).
<br>
* For each chromosome a seperete file will be reported.
* -X is a number for each of the given chromosomes.

<br><br>
## Compile the source code

The source code can be compiled with the following instructions:

1. Download content of the RPTRF source directory `src/`
2. Run the following command
```
g++ -fopenmp RPTRF.cpp -O3 -o RPTRF
```
3. The binary file will be named as : `./RPTRF` 

<br><br><br><br>





