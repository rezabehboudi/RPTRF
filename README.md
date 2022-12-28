# RPTRF
**RPTRF: A Rapid Perfect Tandem Repeat Finder Tool for DNA Sequences**
<br><br>
## Run the executable
To run the executable file follow the steps:

1. The executable file is available both in `Executable/RPTRF` and Releases section. 
2. Input sequnce options: 
* Download sample sequnce from `Sample_Sequnce/Choromosome22(Trimmed).fasta`.
* Download sequnce from NCBI ([GRCh38](https://www.ncbi.nlm.nih.gov/assembly/GCF_000001405.26/))
* Use your `.fasta` sequnce 
3. Run the following command for the defult arguments:
```
sudo ./RPTRF -s chromosome22(Trimmed).fasta
```
4. To use optional arguments use the follwoing command:

```
sudo ./RPTRF -s chromosome22(Trimmed).fasta -m 100 -t 10
```

<br><br>
Arguments table:
<br>
 Flag | Definition                                                                                                  | Default |
|------|-------------------------------------------------------------------------------------------------------------|---------|
|  -s  | Input .Fasta sequnce path                                                                            |        |
|  -m  | Maximum motife size    	                                                                                  |    100    |
|  -t  | Minimum length of tandem repeats  	                                                                                    |   10   |
|  -h  | Access to manual in the command lime	                                                                          |       |


<br><br>
## Compile the source code

The source code can be compiled with the following instructions:

1. Download content of the RPTRF source directory `src/`
2. Run the following command
```
sudo g++ -fopenmp RPTRF.cpp -O3 -o RPTRF
```
3. The binary file will be named as : `./RPTRF` 

<br><br><br><br>


