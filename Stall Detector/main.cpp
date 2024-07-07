#include <iostream>
#include <cstring>
#include <sstream>
#include<string>
#include <vector>
#include <unordered_map>
#include <fstream>
using namespace std;
string rd1="0",rd2="0",ins1Type="alu",ins2Type="alu";
int ncycles=4;
string getRegister(string rg){
    if(rg=="ra,") return "x1,";
    else if(rg=="sp,") return "x2,";
    else if(rg=="gp,") return "x3,";
    else if(rg=="tp,")  return "x4,";
    else if(rg=="t0,")  return "x5,";
    else if(rg=="t1,")  return "x6,";
    else if(rg=="t2,")  return "x7,";
    else if(rg=="s0,")  return "x8,";
    else if(rg=="s1,")  return "x9,";
    else if(rg=="a0,")  return "x10,";
    else if(rg=="a1,")  return "x11,";
    else if(rg=="a2,")  return "x12,";
    else if(rg=="a3,")  return "x13,";
    else if(rg=="a4,")  return "x14,";
    else if(rg=="a5,")  return "x15,";
    else if(rg=="a6,")  return "x16,";
    else if(rg=="a7,")  return "x17,";
    else if(rg=="s2,")  return "x18,";
    else if(rg=="s3,")  return "x19,";
    else if(rg=="s4,")  return "x20,";
    else if(rg=="s5,")  return "x21,";
    else if(rg=="s6,")  return "x22,";
    else if(rg=="s7,")  return "x23,";
    else if(rg=="s8,")  return "x24,";
    else if(rg=="s9,")  return "x25,";
    else if(rg=="s10,")  return "x26,";
    else if(rg=="s11,")  return "x27,";
    else if(rg=="t3,")  return "x28,";
    else if(rg=="t4,")  return "x29,";
    else if(rg=="t5,")  return "x30,";
    else if(rg=="t6,")  return "x31,";
    else if(rg=="zero,")   return "x0,";
    else return rg;
}
int checkWithForwarding(string rs1,string rs2){
    if((rd2==rs1 || rd2==rs2) && rd2!="0" && rd2!="x0,"){
        if(ins2Type=="ld"){
        cout<<"nop"<<endl;
        ncycles+=1;
        return 1;
        }
        return 0;
    }
    else return 0;
}
int checkHazard(string rs1,string rs2,int forwarding){
    if(forwarding){
        checkWithForwarding(rs1,rs2);
        return 0;
    }
    // cout<<"rd: "<<rd2<<" rs1: "<<rs1<<" rs2: "<<rs2<<endl;
    if((rd2==rs1 || rd2==rs2) && rd2!="0" && rd2!="x0,"){
        cout<<"nop"<<endl;
        cout<<"nop"<<endl;
        ncycles+=2;
        return 1;
    }
    else if((rd1==rs1 || rd1==rs2) && rd1!="0" && rd1!="x0,"){
        cout<<"nop"<<endl;
        ncycles+=1;
        return 2;
    }
    else return 0;
}
bool isAluType(string ins){
    if(ins=="add" || ins=="sub" || ins=="and" || ins=="xor" || ins=="or" || ins=="sll" || ins=="srl" || ins=="sra" || ins=="slt" || ins=="sltu" || ins=="addi" || ins=="andi" || ins=="ori" || ins=="xori" || ins=="srli" || ins=="slli" || ins=="or" || ins=="srai" || ins=="slti" || ins=="sltiu") return true;
    else return false;
}
bool isLoadType(string ins){
    if(ins=="lb" || ins=="lh" || ins=="lw" || ins=="lbu" || ins=="lhu"|| ins=="ld") return true;
    else return false;
}
void decodeInstruction(unordered_map<int, string> pcRd,int pc,string instruction,int forwa){
    ncycles+=1;
    string token;
    string ins;
    istringstream iss(instruction);
    vector<string> tokens;
    while (getline(iss, token, ' ')) {
        tokens.push_back(token);
    }
    if (!tokens.empty()) {
        ins = tokens[0]; 
    }
    string srd, srs1, srs2;
    if (tokens.size() >= 2) {
        srd = tokens[1];
        pcRd[pc]=srd;
        }
    if (tokens.size() >= 3) {
        srs2 = tokens[2];
    }
    srd=getRegister(srd);
    srs2=getRegister(srs2);
        // cout<<srd<<" "<<srs2<<endl;
    if (isAluType(ins)) {
        if (tokens.size() >= 4) {
            srs1 = tokens[3];
            srs1+=",";
        }
        srs1=getRegister(srs1);
    int hz=checkHazard(srs1,srs2,forwa);
    if(hz==1 || hz==2){
        rd1="0";
        rd2=srd;
    }
    else {
        rd1=rd2;
        ins1Type=ins2Type;
        rd2=srd;
    }
    ins2Type="alu";
    cout<<instruction<<endl;
    } else if (isLoadType(ins)) {
        int index=srs2.find("(");
        srs2=srs2.substr(index+1,srs2.size()-index-2);
        srs2+=",";
        srs2=getRegister(srs2);
        int hz=checkHazard(srs2,"00",forwa);
        if(hz==1 || hz==2){
        rd1="0";
        rd2=srd;
    }
    else {
        rd1=rd2;
        ins1Type=ins2Type;
        rd2=srd;
    }
    ins2Type="ld";
    cout<<instruction<<endl;
    } else {
        int index=srs2.find("(");
        srs2=srs2.substr(index+1,srs2.size()-index-2);
        srs2+=",";
        srs2=getRegister(srs2);
        int hz=checkHazard(srs2,"00",forwa);
        if(hz==1 || hz==2){
            rd1="0";
            rd2="0";
        }
        else {
            rd1=rd2;
            ins1Type=ins2Type;
            rd2="0";
        }
        cout<<instruction<<endl;
    }
}
int main() {
    vector<int> rd;
    unordered_map<int, string> pcRd;
    ifstream input_file("input2.txt");
    if (!input_file) {
        cout<< "Failed to open the input file." << endl;
        return 1;
    }
    string input;
    vector<string> instructions;
    while (getline(input_file, input)) {
        instructions.push_back(input);
    }
    //without forwarding
    cout<<"Without data forwarding: "<<endl;
    for (const string& line : instructions) {
        decodeInstruction(pcRd,0,line,0);
    }
    cout<<"Total: "<<ncycles<<" cycles"<<endl;
    ncycles=4;
    rd1="0",rd2="0",ins1Type="alu",ins2Type="alu";
    //with forwarding
    cout<<"-----------------------------------------------"<<endl<<"With data forwarding and no hazard detection: "<<endl;
    for (const string& line : instructions) {
        decodeInstruction(pcRd,0,line,1);
    }
    cout<<"Total: "<<ncycles<<" cycles"<<endl;
    return 0;
}