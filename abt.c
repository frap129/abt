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
  unsigned int cpus;
  const char* jobs;
  const char* device;
  char* sync = "repo sync -j";
  char* repoSync;
  char* clean = "make clean -j";
  char* makeClean;
  char* envsetup = "bash build/envsetup.sh";
  char* and = " && ";
  char* lunch = "lunch ";
  char* user = "-userdebug";
  char* make = "make otapackage -j";
  char* build;

 /*
  * Argument Handling.
  */
  if( argc == 1 ) {
     printf("Usage: abt device_name [OPTIONS]\n");
     printf("Options: -s = Sync before build\n");
     printf("         -c = Clean before build\n");
     exit(1);
  } else if( argc > 4 ) {
     printf("Usage: abt device_name [OPTIONS]\n");
     printf("Options: -s = Sync before build\n");
     printf("         -c = Clean before build\n");
     exit(1);
  }
  if( argv[2] == '-s' || argv[3] == '-s' ) {
     syncFlag = 1;
  } else { 
     syncFlag = 0;
  }
  if( argv[2] == '-c' || argv[3] == '-c' ) {
     cleanFlag = 1;
  } else { 
     cleanFlag = 0;
  }
  device = argv[1];
  
 /*
  * Sync and Clean
  */
  cpus = sysconf( _SC_NPROCESSORS_ONLN );
  jobs = ((( cpus / 2 ) + 1 ) * 2 );
  
  if( sync = 1 ) {
     strcpy(repoSync, sync);
     strcat(repoSync, jobs);
     system(repoSync);
  }
  if( clean = 1 ) {
     strcpy(makeClean, clean);
     strcat(makeClean, jobs);
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
  strcat(build, jobs);
  system(build);
}
