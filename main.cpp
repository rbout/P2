/* ===================================================================
 * Authors     : Robert Boutillier and Marcus Novoa
 * Class       : CSCI4547-01 - Systems Programming
 * Date        : September 17, 2020
 * Description : Program 2 - Design a command language.
 * Version     : 1.0.0
 * =================================================================== */

#include <fstream>
#include <getopt.h>
#include <iostream>
#include <string.h>
using namespace std;

extern int opterr;
// ofstream OutFile(output_file, ios::out | ios::app);

class Params {
  private:
    bool case_sensitive;
    bool recursive;
    bool verbose;
    string directory;
    string output_file;

  public:
    Params(int argc, char* argv[]) {
      case_sensitive = true;
      recursive      = false;
      verbose        = false;
      directory    = "";
      output_file  = "";

      // Flags
      const char* const short_opts = "d:2:io:Rv";
      const option long_opts[7] = {
        {"d",       required_argument, 0, 'd'},
        {"dir",     required_argument, 0, '2'}, // Use "--" for this command
        {"i",       no_argument,       0, 'i'},
        {"o",       required_argument, 0, 'o'},
        {"R",       no_argument,       0, 'R'},
        {"verbose", no_argument,       0, 'v'}, // Use "--" for this command
        {0, 0, 0, 0}
      };

      // Traverse the arguments checking for switch values.
      while (1) {
        const auto opt = getopt_long(argc, argv, short_opts, long_opts, 0);
        opterr = 0; // Do not print option value if there is an error.
        if (opt == -1)
          break; // End of options
        switch (opt) {
          case 'd':
          case '2':
            directory = string(optarg);
            break;
          case 'i':
            case_sensitive = false;
            break;
          case 'R':
            recursive = true;
            break;
          case 'o':
            output_file = string(optarg);
            break;
          case 'v':
            verbose = true;
            break;
        }
      };
      
      Params::print();
    }

    void print() {
      if (!directory.empty()) {
        cout << "Verbose? " << (verbose != 0 ? "Yes" : "No") << endl;
        cout << "Case insensitive? " << (!case_sensitive ? "No" : "Yes") << endl;
        cout << "Recursive? " << (recursive ? "Yes" : "No") << endl;
        cout << "Output file name: " << (output_file.empty() ? "None" : output_file) << endl;
        cout << "Directory: " << directory << endl;
      } else {
        cout << "Directory path required. Exiting..." << endl;
      }
    }
};

int main(int argc, char *argv[]) {
  Params(argc, argv);
  return 0;
}
