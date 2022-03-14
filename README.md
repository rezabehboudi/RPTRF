# RPTRF
RPTRF: A Rapid Perfect Tandem Repeat Finder Tool for DNA Sequences

Link to download Human Genome 38. https://www.ncbi.nlm.nih.gov/assembly/GCF_000001405.26/
------------------


**Guideline for running:**
A directory named RPTRF contains portable application written by c++.

Insert following command on Linux command-line to run the application: "./RPTRF File_Address Min_Core_Size Min_TR_length)."

File_Address : Refers to the location of the Fasta sequence.

Min_Core_Size: Determines the minimum core size of TRs.

Min_TR_length: Determines the minimum length of reported TRs.

------------------



**Source code**: Directory named Source code contains the source code of the RPTRF.

Compiling the source code: "g++ -fopenmp RPTRF.c -O -o RPTRF"

-o : Determines output file name..

-O : It is a director to the compiler with which code becomes a little efficient.
