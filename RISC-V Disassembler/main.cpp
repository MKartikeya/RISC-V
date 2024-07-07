#include <iostream>
#include <cstring>
#include <sstream>
#include<string>
#include <vector>
#include <unordered_map>
#include <fstream>
using namespace std;

string hexToBinary(char hexDigit) {
    switch (hexDigit) {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'a': return "1010";
        case 'A': return "1010";
        case 'b': return "1011";
        case 'B': return "1011";
        case 'c': return "1100";
        case 'C': return "1100";
        case 'd': return "1101";
        case 'D': return "1101";
        case 'e': return "1110";
        case 'E': return "1110";
        case 'f': return "1111";
        case 'F': return "1111";
        default: return ""; 
    }
}
int binaryStringToInt(const std::string&binaryString) {
    int result=0;

    for (char bit : binaryString) {
        if (bit == '0') {
            result=(result<<1); 
        } else if (bit == '1') {
            result=(result<<1)|1; 
        } else {
            throw std::invalid_argument("Invalid binary digit: " + std::string(1, bit));
        }
    }

    return result;
}
void R_format(string output){
    string funct3="",rd="",rs1="",rs2="",function="",funct7="";
        funct3=output.substr(17,3);
        rd=output.substr(20,5);
        rs1=output.substr(12,5);
        rs2=output.substr(7,5);
        funct7=output.substr(0,7);
        int dest=binaryStringToInt(rd);
        int src1=binaryStringToInt(rs1);
        int src2=binaryStringToInt(rs2);
        if(funct3=="000"){
            if(funct7=="0000000"){
                //add
                function="add";
            }
            else{
                //subtraction
                function="sub";
            }
        }
        else if(funct3=="100"){
            //xor   
            function="xor";
        }
         else if(funct3=="110"){
            //or   
            function="or";
        }
         else if(funct3=="111"){
            //and   
            function="and";
        }
        else if(funct3=="001"){
            //sll  
            function="sll";
        }
         else if(funct3=="101"){
            string funct7="";
            for(int i=0;i<7;i++){
            funct7=output[i]+funct7;
            }
            if(funct7=="0000000"){
                //srl
                function="srl";
            }
            else{
                //sra
                function="sra";
            }
        }
         else if(funct3=="010"){
            //sll  
            function="slt";
        }
         else if(funct3=="011"){
            //sltu 
            function="sltu";
        }
        cout<<function<<" x"<<dest<<" x"<<src1<<" x"<<src2<<endl;
}
void I_format1(string output){
    string funct3="",rd="",rs1="",imm="",function="";
        funct3=output.substr(17,3);
        rd=output.substr(20,5);
        rs1=output.substr(12,5);
        imm=output.substr(0,12);
        int dest=binaryStringToInt(rd);
        int src1=binaryStringToInt(rs1);
        int immsrc=binaryStringToInt(imm);
        if (imm[0] == '1') {
        immsrc=(immsrc|0xFFFFF000);  
        }
        
        if(funct3=="000"){
            //addi
            function="addi";
        }
        else if(funct3=="100"){
            //xori   
            function="xori";
        }
         else if(funct3=="110"){
            //ori 
            function="ori";
        }
         else if(funct3=="111"){
            //andi
            function="andi";
        }
        else if(funct3=="001"){
            //slli
            function="slli";
        }
         else if(funct3=="101"){
            string funct7="";
            for(int i=0;i<6;i++){
            funct7=output[i]+funct7;
            }
            if(funct7=="000000"){
                function="srli";
            }
            else{
                function="srai";
                imm=imm.substr(7,5);
                immsrc=binaryStringToInt(imm);
                if (imm[0] == '1') {
                    immsrc=(immsrc|0xFFFFF000);  
                }
            }
        }
         else if(funct3=="010"){
            //slti
            function="slti";
        }
         else if(funct3=="011"){
            //sltiu 
            function="sltiu";
        }
        cout<<function<<" x"<<dest<<" x"<<src1<<" "<<immsrc<<endl;
}
void I_format2(string output){
        string funct3="",rd="",rs1="",imm="",function="";
        funct3=output.substr(17,3);
        rd=output.substr(20,5);
        rs1=output.substr(12,5);
        imm=output.substr(0,12);

        int dest=binaryStringToInt(rd);
        int src1=binaryStringToInt(rs1);
        int immsrc=binaryStringToInt(imm);
        if (imm[0] == '1') {
        immsrc=(immsrc|0xFFFFF000);  
        }
        if(funct3=="000"){
            //lb
            function="lb";
        }
        else if(funct3=="001"){
            //lh
            function="lh";
        }
        else if(funct3=="010"){
            //lw
            function="lw";
        }
        else if(funct3=="011"){
            //ld
            function="ld";
        }
        else if(funct3=="100"){
            //lbu
            function="lbu";
        }
        else if(funct3=="110"){
            //lwu
            function="lwu";
        }
        else if(funct3=="101"){
            //lhu
            function="lhu";
        }
        cout<<function<<" x"<<dest<<" "<<immsrc<<"(x"<<src1<<")"<<endl;
}
void S_format(string output){
     string funct3="",rs1="",rs2="",imm="",function="";
        funct3=output.substr(17,3);
        rs1=output.substr(12,5);
        rs2=output.substr(7,5);
        imm=output.substr(0,7);
        imm+=output.substr(20,5);
        int immsrc=binaryStringToInt(imm);
        if (imm[0] == '1') {
            immsrc=(immsrc|0xFFFFF000);  
        }
        if(funct3=="000"){
            //sb
            function="sb";
        }
        else if(funct3=="001"){
            //sh
            function="sh";
        }
        else if(funct3=="010"){
            //sw
            function="sw";
        }
        else if(funct3=="011"){
            //sd
            function="sd";
        }
        int src2=binaryStringToInt(rs2);
        int src1=binaryStringToInt(rs1);
        cout<<function<<" x"<<src2<<" "<<immsrc<<"(x"<<src1<<")"<<endl;
}
int32_t B_format(string output){
        int ss=binaryStringToInt(output);
        uint32_t imm12=(ss>>31)&0x01;
        uint32_t imm10to5=(ss>>25)&0x3F;
        uint32_t imm4to1=(ss>>8)&0x0F;
        uint32_t imm11=(ss>>7)&0x01;
        int32_t imm=(imm12<<12)|(imm11<<11)|(imm10to5<<5)|(imm4to1<<1);
        if (imm12) {
        imm=imm|0xFFFFF000;
        }
        int32_t branchTarget=imm ;
        string funct3="",rs1="",rs2="",function="";
        for(int i=12;i<15;i++){
            funct3=output[31-i]+funct3;
        }
        for(int i=15;i<20;i++){
            rs1=output[31-i]+rs1;
        }
        for(int i=20;i<25;i++){
            rs2=output[31-i]+rs2;
        }
        if(funct3=="000"){
            //beq
            function="beq";
        }
        else if(funct3=="001"){
            //bne
            function="bne";
        }
        else if(funct3=="100"){
            //blt
            function="blt";
        }
        else if(funct3=="101"){
            //bge
            function="bge";
        }
        else if(funct3=="110"){
            //bltu
            function="bltu";
        }
        else if(funct3=="111"){
            //bltu
            function="bgeu";
        }
        int src2=binaryStringToInt(rs2);
        int src1=binaryStringToInt(rs1);
        cout<<function<<" x"<<src1<<" x"<<src2<<" ";
        return branchTarget;
}
int32_t B_return(string output){
    int ss=binaryStringToInt(output);
        uint32_t imm12=(ss>>31)&0x01;
        uint32_t imm10to5=(ss>>25)&0x3F;
        uint32_t imm4to1=(ss>>8)&0x0F;
        uint32_t imm11=(ss>>7)&0x01;
        int32_t imm=(imm12<<12)|(imm11<<11)|(imm10to5<<5)|(imm4to1<<1);
        if (imm12) {
        imm=imm|0xFFFFF000;
    }
        int32_t branchTarget=imm ;
        return branchTarget;
}
int32_t J_format(int instruction){
    uint32_t imm20=(instruction>>31)&0x01;
    uint32_t imm10to1=(instruction>>21)&0x3FF;
    uint32_t imm11=(instruction>>20)&0x01;
    uint32_t imm19to12=(instruction>>12)&0xFF;
    uint32_t funct3=(instruction>>12)&0x07;
    uint32_t rd=(instruction>>7)&0x1F;
    int32_t imm=(imm20<<20)|(imm19to12<<12)|(imm11<<11)|(imm10to1<<1);
    if (imm20) {
        imm=imm|0xFFFF0000;
    }
    int32_t jumpTarget=imm;
    cout<<"jal"<<" x"<<rd<<" ";
    return jumpTarget;
}
int32_t J_return(int instruction){
    uint32_t imm20=(instruction>>31)&0x01;
    uint32_t imm10to1=(instruction>>21)&0x3FF;
    uint32_t imm11=(instruction>>20)&0x01;
    uint32_t imm19to12=(instruction>>12)&0xFF;
    uint32_t funct3=(instruction>>12)&0x07;
    uint32_t rd=(instruction>>7)&0x1F;
    int32_t imm=(imm20<<20)|(imm19to12<<12)|(imm11<<11)|(imm10to1<<1);
        if (imm20) {
        imm=imm|0xFFFF0000;
    }
    int32_t jumpTarget=imm;
    return jumpTarget;
}
void JAL_format(int instruction,string output){
    int imm=binaryStringToInt(output.substr(0,12));
    if(output.substr(0,12)[0]=='1') imm=(imm|0xFFFFF000);  
    uint32_t funct3=(instruction>>12)&0x07;
    uint32_t rd=(instruction>>7)&0x1F;
    uint32_t rs1=(instruction>>15)&0x1F; 
    int32_t jumpTarget=imm;
    cout<<"jalr x"<<rd<<" "<<imm<<"(x"<<rs1<<")"<<endl;
}
void U_format(int instruction,string opcode){
    uint32_t imm=(instruction>>12)&0xFFFFF;
    uint32_t rd=(instruction>>7)&0x1F;
    string function="";
    if(opcode=="0110111")function="lui";
    else function="auipc";
    stringstream stream;
    stream<<hex <<imm;
    string hexString=stream.str();
    cout<<function<<" x"<<rd<<" 0x"<<hexString<<endl;
}
void I_format3(string output){
    string imm=output.substr(0,12);
    if(imm=="000000000000") cout<<"ecall"<<endl;
    else cout<<"ebreak"<<endl;

}
int main() {
        ifstream input_file("input.txt");
    if (!input_file) {
       cout<<"Failed to open the input file."<<endl;
        return 1;
    }
    string input;
    vector<string> instructions;
    while (input_file>>input) {
        if (input.length() != 8) {
           cout<<"Invalid instruction length: "<<input<<endl;
            return 1;
        }
        instructions.push_back(input);
    }
    unordered_map<string,int>labels;
    int pc=0,ic=0; 
    int tag=1;
    for (int i=0; i < instructions.size(); i++) {
        string string_instruction=instructions[i];
        string output="";
        for(int i=0;i<8;i++){
            char hexDigit=string_instruction[i];
            string binary=hexToBinary(hexDigit);
            if (binary.empty()) {
                return 1;
            }
            output+=binary;
        }
        int instruction=binaryStringToInt(output);
        string opcode="";
        for(int i=0;i<7;i++){
            opcode=output[31-i]+opcode;
        }
        if(opcode=="1100011"){
            int btarget=B_return(output),isthere=1;
            for (const auto&label : labels) {
                if (btarget+pc == label.second) {
                    isthere=0;
                }
            }
            if(isthere){
            stringstream labelName;
            labelName<<"L"<< tag;
            tag++;
            labels[labelName.str()] =btarget +pc;
            }
        }
        else if(opcode=="1101111"){
            int jtarget=J_return(instruction),isthere=1,label=0;
            for (const auto&label : labels) {
                if (jtarget+pc == label.second) {
                    isthere=0;
                }
            }
            if(isthere){
            stringstream labelName;
            labelName<<"L"<< tag;
            tag++;
            labels[labelName.str()] =jtarget +pc;
            }
        }
        pc += 4;  
    }
    ic=pc;pc=0;
    for (int i=0; i < instructions.size(); i++) {
        string string_instruction=instructions[i];
        string output="";
        for(int i=0;i<8;i++){
            char hexDigit=string_instruction[i];
            string binary=hexToBinary(hexDigit);
            if (binary.empty()) {
                return 1;
            }
            output+=binary;
        }
        int instruction=binaryStringToInt(output);
        string opcode="";
        for(int i=0;i<7;i++){
            opcode=output[31-i]+opcode;
        }
        for (const auto&label : labels) {
                if (pc == label.second) {
                cout<<label.first<<":" ;
            }
        }
        if(opcode=="0110011"){ R_format(output);}
        else if(opcode=="0010011"){I_format1(output); }
        else if(opcode=="0000011"){I_format2(output); }
        else if(opcode=="0100011"){S_format(output);  }
        else if(opcode=="1100011"){
            int btarget=B_format(output),isthere=1;
            for (const auto&label : labels) {
                if (btarget+pc == label.second) {
                    isthere=0;
                    if(btarget+pc<ic) cout<<label.first <<endl ;
                    else cout<<btarget<<endl;
                }
            }
            if(isthere){

            stringstream labelName;
            labelName<<"L"<< tag;
            tag++;
            labels[labelName.str()] =btarget +pc;
            cout<<labelName.str()<<endl;
            }
        }
        else if(opcode=="1100111"){
                JAL_format(instruction,output);
        }
        else if(opcode=="1101111"){
            int jtarget=J_format(instruction),isthere=1,label=0;
            for (const auto&label : labels) {
                if (jtarget+pc == label.second) {
                    isthere=0;
                    if(jtarget+pc<ic) cout<<label.first <<endl;
                    else cout<<jtarget<<endl;
                }
            }
            if(isthere){
            stringstream labelName;
            labelName<<"L"<< tag;
            tag++;
            labels[labelName.str()] =jtarget +pc;
            cout<<labelName.str()<<endl;
            }
        }
        else if(opcode=="0110111" || opcode=="0010111"){
            U_format(instruction,opcode);
        }
        else if(opcode=="1110011") I_format3(output);
        pc += 4;   
    }
    return 0;
}
