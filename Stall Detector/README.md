LAB5: Pipeline Stall Detector
--Kartikeya Mandapati 
--CS22BTECH11032

Contents:
->Two test case files.
->"main.cpp" is the file that contains the main code.
->README.md is the file with instructions  compile.
->"report.pdf" is the report file of the LAB assignment. 

Instructions to Compile:
-> The input must in a text file as specified. The input file is named as "input.txt" in the following line. It could be changed to required name.
            ifstream input_file("input.txt");
-> The instructions shall be of this format:
        The program is syntactically correct (there is no syntax error)
        There is only 1 space in between the instruction and the first operand. Also, only 1 space between “,” and second operand and so on.
        The program starts on the first character in each line
        There is only one instruction in each line
        There are no blank lines in the input file
        No branch/jump instructions are used
        There are no labels used in the program (to ease the parsing of the assembly code)

    Any disruptions would result in error or undesired output.

->The code is written in C++ for simplicity. Neccessary compiler must be installed.

->You can use the following commands to run the program:
    g++ -o main main.cpp
    ./main
