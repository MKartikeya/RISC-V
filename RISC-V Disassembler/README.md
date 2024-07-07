LAB3: RISC-V Machine-Level Instructions
--Kartikeya Mandapati 
--CS22BTECH11032

Contents:
->Two test case files. They are not compatible to be provided as input files as they also contain output in them.
->"main.cpp" is the file that contains the main code.
->README.md is the file with instructions  compile.
->"report.pdf" is the report file of the LAB assignment. 

Instructions to Compile:
-> The input must in a text file with instructions in hex form. The input file is named as "input.txt" in the following line. It could be changed to required name.
            ifstream input_file("input.txt");
-> The instructions shall be of this format:
    007201b3
    00720863
    00c0006f
    00533623
    100004b7
    00c50493
    Any disruptions would result in error or undesired output.

->The code is written in C++ for simplicity. Neccessary compiler must be installed.

->You can use the following commands to run the program:
    g++ -o main main.cpp
    ./main

****NOTE: THE CODE DOESN'T OUTPUT ANY ERROR MESSAGE FOR INVALID MACHINE LEVEL INSTRUCTION PROVIDED AS IT IS ASSUMED TO BE A VALID INSTRUCTION. IT COULD PRINT THE WRONG INSTRUCTION IF INPUT IS NOT VALID.
