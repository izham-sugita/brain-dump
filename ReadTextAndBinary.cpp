/*
This program demonstrate how to write a mixed ASCII and binary data into a binary file, and the read the file content. The file content looks like this:
10
Hello World
'gibberish non-human-readable data'

This type of file is common for large data application, where only the headings are human readable, but the numerical data is in binary format.

*/

#include<iostream>
#include<fstream>
#include<string>
#include<sstream> //stringstream <-to convert string as input from device

using namespace std;

int main()
{

  //binary data
  int N = 10;
  double* dummy;
  dummy = new double[N];
  for(int i=0; i<N; ++i){
    dummy[i] = (double)i;
    cout<<dummy[i]<<endl;
  }
  
  //writing output
  ofstream file1;
  file1.open("textwithbinary.bin", ios::binary);
  file1 << N <<endl;
  file1 << "Hello World\n";
  //binary data output
  for(int i=0; i<N; ++i){
    file1.write(reinterpret_cast<char*>(&dummy[i]), sizeof(dummy[0]));
  }
  file1.close();

  //reading from file
  int Nread;
  double* dummyread;
  string line;
  ifstream file2;
  file2.open("textwithbinary.bin", ios::binary);
  
  getline(file2,line);
  stringstream ss(line);
  ss >> Nread;
  dummyread = new double[Nread];
  cout<<"Nread= "<<Nread<<endl;
  getline(file2,line);
  cout<<line<<endl;
  for(int i=0; i<Nread; ++i){
    file2.read(reinterpret_cast<char*>(&dummyread[i]),sizeof(dummyread[0]));
  }
  
   for(int i=0; i<Nread; ++i){
	cout<<dummyread[i]<<endl;
      }
  
  file2.close();
  
}
