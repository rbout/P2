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
#include <stdio.h>
using namespace std;

extern int opterr;

class Params {
  private:
    bool case_sensitive;
    bool recursive;
    bool verbose;
    string directory;
    string output_file;
    string search_text;

  public:
    Params(int argc, char* argv[]) {
      case_sensitive = true;
      recursive      = false;
      verbose        = false;
      directory    = "";
      output_file  = "";
      search_text  = "";

      // Switches
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
            remove(optarg);
            output_file = string(optarg);
            break;
          case 'v':
            verbose = true;
            break;
        }
      };

      // Non-option argument is the search text
      search_text = string(argv[optind]);
      print();
    }

    void print() {
      ofstream OutFile;
      OutFile.open(output_file, ios::out | ios::app);

      if (!directory.empty()) {
        OutFile << "Verbose? " << (verbose != 0 ? "Yes" : "No") << endl;
        OutFile << "Case insensitive? " << (!case_sensitive ? "No" : "Yes") << endl;
        OutFile << "Recursive? " << (recursive ? "Yes" : "No") << endl;
        OutFile << "Output file name: " << (output_file.empty() ? "None" : output_file) << endl;
        OutFile << "Directory: " << directory << endl;
      } else {
        OutFile << "Directory path required. Exiting..." << endl;
      }

      OutFile.close();
    }
};

int main(int argc, char *argv[]) {
  Params(argc, argv);
  return 0;
}
