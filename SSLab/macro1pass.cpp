#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
using namespace std;

map <string, string> deftab,argtab;
map<string,string>::iterator iter;
string a1,a2,a3,r1,r2,r3;

void tokenize(string line,string&l,string &op,string &oper)
{
    stringstream s(line);
    getline(s, l, '\t');
    getline(s, op, '\t');
    getline(s, oper, '\n');
}
//to be added for parameters
void token1(string line,string&l,string &op,string &oper)
{
    stringstream s(line);
    getline(s, l, ',');
    getline(s, op, ',');
    getline(s, oper, '\n');
}
//to be added for parameters
void findandreplaceALL (string &data,string toSearch,string replaceStr) {
	size_t pos = data.find(toSearch);
	while( pos != string::npos ){
		data.replace(pos,toSearch.size(),replaceStr);
		pos = data.find(toSearch,pos+toSearch.size());
	}
}
void parseInput()
{
    fstream input_file, output_file;
    string line, label, opcode, operand,mname;string data;

    // Open files
    input_file.open("macroinput.txt", ios::in );
    output_file.open("macrooutput.txt", ios::out);

    // Read input file till end
    while ( getline(input_file, line) )
	{
        tokenize(line,label,opcode,operand);

        if(opcode == "END")
        {
            output_file << line << endl;
            break;
        }
        if (opcode == "MACRO")
        {
            mname = label;
            size_t p=operand.find('&');
            if(p!=string::npos){
            	argtab[mname]=operand;
            }
            stringstream macro;
            while(getline(input_file,line))
            {
                if(line[0]=='.') continue;
                tokenize(line,label,opcode,operand);
                if(opcode == "MEND")
                {
                    deftab[mname] = macro.str();
                    break;
                }
                macro<<line<<endl;
            } 
            
        }
        // If macro is called
        else if ( (iter = deftab.find(opcode)) != deftab.end())
        {
            output_file<<"."<<opcode<<endl;
            // Write the label (if any) before macro call to file
            if(argtab[opcode]!=""){
            token1(argtab[opcode],a1,a2,a3);//takes parameters from macro defn
            token1(operand,r1,r2,r3);//takes parameters from macro call
            output_file << label;
            data=iter->second;
            //EXTREME JUGAAD......
            findandreplaceALL(data,a1,r1);
  	    findandreplaceALL(data,a2,r2);
       	    findandreplaceALL(data,a3,r3);        
            // Write out contents of macro_defintion to output file
            output_file << data << endl;
            }
            else{
            output_file << label;
            output_file << iter->second << endl;
            }                    
        }

        else
            {
                // Write out other lines
                output_file << line << endl;
            }
  }
}
int main ()
{
  parseInput();
  return 0;
}
