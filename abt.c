#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

 /*
  * Definitions
  */
  int syncFlag;
  int cleanFlag;
  int customCleanFlag;
  int cpus;
  char* device;
  const char* ssync = "repo sync -j";
  char* repoSync;
  const char* make = "make ";
  char* clean;
  char* makeClean;
  const char* envsetup = "bash build/envsetup.sh";
  char* andand = " && ";
  char* lunch = "lunch ";
  const char* user = "-userdebug";
  const char* buildCommand = "otapackage -j";
  char* build;

 /*
  * Argument Handling
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

  if( syncFlag == 1 ) {
     strcpy(repoSync, ssync);
     strcat(repoSync, cpus);
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
  strcat(build, andand);
  strcat(build, lunch);
  strcat(build, device);
  strcat(build, user);
  strcat(build, andand);
  strcat(build, make);
  strcat(build, buildCommand);
  strcat(build, cpus);
  system(build);
}
