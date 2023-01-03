# RPTRF
**RPTRF: A Rapid Perfect Tandem Repeat Finder Tool for DNA Sequences**
<br>
In this manual, you can find guidelines for running the executable file and compiling the RPTRF from the source code.
<br>

Table of contents
=================

<!--ts-->
   * [Run the executable](#Run-the-executable)
   * [Compile the source code](#Compile-the-source-code)

<br><br>
<a name="run"/>
## Run the executable ##
To run the executable file, you may follow the bellow steps:

1. Download the repository and unzip the file.  
2. Get access to the executable file from `executable/RPTRF` path or the Releases section of the repository.
```
cd executable/

```
3. Make the RPTRF executable by the following command:
```
sudo chmod +x RPTRF

```
4. Input sequence can be obtained from `dataset/Sample.fasta` directory, downloaded from the NCBI website ([GRCh38](https://www.ncbi.nlm.nih.gov/assembly/GCF_000001405.26/)), or you may use your local DNA sequence in `.Fasta` format. 
5. To run the RPTRF with the default settings and the sample sequence, enter the following command(the output file will be created in your current directory):
```
./RPTRF -s ../dataset/sample.fasta

```
6. To use optional arguments use the following command(argument explanation is provided in the following table):

```
./RPTRF -s ../dataset/sample.fasta -m 100 -t 10

```

<br><br>
**Arguments table**:
<br>
 Flag | Definition                                                                                                  | Default |
|------|-------------------------------------------------------------------------------------------------------------|---------|
|  -s  | Input .Fasta sequnce path                                                                            |        |
|  -m  | Maximum motif size    	                                                                                  |    100    |
|  -t  | Minimum length of tandem repeats  	                                                                                    |   10   |
|  -h  | Access to manual in the command line	                                                                          |       |

<br><br>
**Output**:
<br>
Tandem repeats of the given sequence will be reported as `result-X.txt` in your current directory. The `result-X.txt` file has four columns each indicating the following information:
<br>
| Start | End | Len | Motif length( Sequence ) |
| :---:        |     :---:      |     :---:     |          :---: |
| The starting point of the Tandem Repeat   | Ending point of the Tandem Repeat     | The length of the Tandem Repeat    | Motif Size(the motif that is repeated in the Tandem Repeat)    |

<br><br><br><br>
## Compile the source code ##

The source code can be compiled with the following instructions:

1. Download the repository and unzip the file
2. Get the source code of RPTRF from `src/` directory
3. Ensure that you have installed boost-devel package. To install the package use the following command:
```
sudo apt-get install libboost-all-dev

```
4. Once the package is installed, run the following command to compile the source code:
```
g++ -fopenmp RPTRF.cpp -O3 -o RPTRF

```
5. The binary file will be named as: `./RPTRF`. 

<br><br><br><br>





