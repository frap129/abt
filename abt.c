#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>

int main(int argc, char *argv[]) {

 /*
  * Definitions
  */
  unsigned int sync;
  unsigned int clean;
  unsigned int cpus;
  unsigned int jobs;
  const char* device;
  const char* repo = "repo sync -j";
  const char* repoSync;
  const char* clean = "make clean -j";
  const char* makeClean;
  const char* envsetup = "bash build/envsetup.sh";
  const char* and = " && ";
  const char* lunch = "lunch ";
  const char* user = "-userdebug";
  const char* make = "make otapackage -j"
  const char* build;

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
     sync = 1;
  } else { 
     sync = 0;
  }
  if( argv[2] == '-c' || argv[3] == '-c' ) {
     clean = 1;
  } else { 
     clean = 0;
  }
  device = argv[1];
  
 /*
  * Sync and Clean
  */
  cpus = sysconf( _SC_NPROCESSORS_ONLN );
  jobs = ((( cpus / 2 ) + 1 ) * 2 );
  
  if( sync = 1 ) {
     strcpy(repoSync, repo);
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
  system(build);
}
