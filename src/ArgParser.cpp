#include "ArgParser.hpp"


int ArgParser::readInt(char* value){
  // https://stackoverflow.com/questions/46208837/c-using-isdigit-to-check-if-optarg-is-a-digit
  char *end;
  errno = 0;
  int intValue = strtol(value, &end, 10);
  while (isspace(*end)) ++end;
  if (errno || *end) {
      return -1;
  }
  return intValue;
}


Arguments* ArgParser::parseArgs(int argc, char** argv){
  int option;

  while ( (option=getopt(argc,argv,"n:p:")) != -1 ){
    switch(option){
      case 'n':
        args->numThreads = this->readInt(optarg);
        if (args->numThreads <= 0){
          fprintf(stderr,"Flag -%c expects an integer input greater than 0. Found: '%s'\n", option, optarg);
          printUsage();
          exit(1);
        }
        break;

      case 'p':
        args->numTrapezoids = this->readInt(optarg);
        if (args->numTrapezoids <= 0){
          fprintf(stderr,"Flag -%c expects an integer input greater than 0. Found: '%s'\n", option, optarg);
          printUsage();
          exit(1);
        }
        break;
      
      case '?':
        printUsage();
        exit(1);
    }
  }

  return args;
}