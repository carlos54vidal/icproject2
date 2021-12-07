// redirecting cout's output thrrough its stream buffer
#include <iostream>     // std::streambuf, std::cout
#include <fstream>      // std::ofstream

int main () {
  streambuf *psbuf, *backup;
  fstream filestr;
  filestr.open ("teste.txt");

  backup = cout.rdbuf();     // back up cout's streambuf

  psbuf = filestr.rdbuf();        // get file's streambuf
  cout.rdbuf(psbuf);         // assign streambuf to cout

  cout << "This is written to the file";

  cout.rdbuf(backup);        // restore cout's original streambuf

  filestr.close();

  return 0;
}
