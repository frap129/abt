#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

 /*
  * Definitions
  */
  unsigned int syncFlag;
  unsigned int cleanFlag;
  unsigned int customCleanFlag;
  unsigned int cpus;
  char* jobs;
  char* device;
  char* sync = "repo sync -j";
  char* repoSync;
  char* make = "make ";
  char* clean;
  char* makeClean;
  char* envsetup = "bash build/envsetup.sh";
  char* and = " && ";
  char* lunch = "lunch ";
  char* user = "-userdebug";
  char* buildCommand = "otapackage -j";
  char* build;

 /*
  * Argument Handling.
  */
  if( argc == 1 ) {
     printf("Usage: abt device_name [OPTIONS]\n");
     printf("Options: -s = Sync before build\n");
     printf("         -c = Clean before build\n");
     printf("         -e [TARGET] = Custom clean command.\n");
     exit(1);
  } else if( argc > 6 ) {
     printf("Usage: abt device_name [OPTIONS]\n");
     printf("Options: -s = Sync before build.\n");
     printf("         -c = Clean before build.\n");
     printf("         -e [TARGET] = Custom clean command.\n");
     exit(1);
  }
  
  device = argv[1];
  if( argv[2] == '-s' || argv[3] == '-s' || argv[4] == '-s' || argv[5] == '-s' ) {
     syncFlag = 1;
  } else { 
     syncFlag = 0;
  }
  if( argv[2] == '-c' || argv[3] == '-c' || argv[4] == '-c' || argv[5] == '-c' ) {
     cleanFlag = 1;
  } else { 
     cleanFlag = 0;
  }
  if( argv[2] == '-e' ) {
     customCleanFlag = 1;
     clean = argv[3];
  } else if( argv[3] == '-e' ) {
     customCleanFlag = 1;
     clean = argv[4];
  } else if( argv[4] == '-e' ) {
     customCleanFlag = 1;
     clean = argv[5];
  } else {
     customCleanFlag = 0;
     clean = "clean";
  }
  
 /*
  * Sync and Clean
  */
  cpus = sysconf( _SC_NPROCESSORS_ONLN );
  jobs = ((( cpus / 2 ) + 1 ) * 2 );
  
  if( syncFlag == 1 ) {
     strcpy(repoSync, sync);
     strcat(repoSync, jobs);
     system(repoSync);
  }
  if( cleanFlag == 1 || customCleanFlag == 1 ) {
     strcpy(makeClean, make);
     strcat(makeClean, clean);
     system(makeClean);
  }
  
 /*
  * Start build
  */
  strcpy(build, envsetup);
  strcat(build, and);
  strcat(build, lunch);
  strcat(build, device);
  strcat(build, user);
  strcat(build, and);
  strcat(build, make);
  strcat(build, buildCommand);
  strcat(build, jobs);
  system(build);
}
