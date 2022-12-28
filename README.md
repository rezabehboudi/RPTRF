# RPTRF
**RPTRF: A Rapid Perfect Tandem Repeat Finder Tool for DNA Sequences**
<br><br>
## Run the executable
To run the executable file follow the steps:

1. The executable file is available both in `Executable/RPTRF` and Releases section. 
2. Input sequence: 
* Download sample sequnce from `Sample_Sequnce/Choromosome22(Trimmed).fasta`.
* Download sequnce from NCBI ([GRCh38](https://www.ncbi.nlm.nih.gov/assembly/GCF_000001405.26/))
* Use your `.fasta` sequnce 
3. Run the following command:

```
sudo ./RPTRF -s chromosome22(Trimmed).fasta -m 100 -t 10
```


<br><br>
## Compile the source code

Once the 
```
gcc -O3 -o -w tandem tandem.c
```
