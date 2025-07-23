/*
 * Program: writer.c
 * Description: this program tackes full path of the file 
 * and a text string which will be written within the file.
 * Author: levYKpi
 * Version: 1.0
 */

#include <stdio.h>      // Header file for standard input/output functions
#include <stdlib.h>     // EXIT_SUCCESS, EXIT_FAILURE, exit()
#include <string.h>     // strcmp, strlen, strchr
#include <libgen.h>     // dirname()
#include <syslog.h>     // LOG_USER
#include <errno.h>

int main(int argc, char *argv[]) {
    char *writefile = NULL;
    FILE *filePointer = NULL;
    openlog("writer_utility",  LOG_PID | LOG_PERROR | LOG_NDELAY, LOG_USER);
    
    // arguments checking

    if (argc < 3) {
        syslog( \
            LOG_ERR, "Usage Error: writefile or writestr was not specified. Usage: %s <filepath> <string_to_write>", \
            argv[0] \
        );
        fprintf(stderr, "error: no writefile or writestr was not specified.\n");
        fprintf(stderr, "Usage: %s <filepath> <string_to_write>\n", argv[0]);
        closelog();
        return EXIT_FAILURE;
    }

    syslog(LOG_USER, "Attempting to write to file: '%s'", writefile);
    writefile = argv[1];

    // Validate absolute path
    if (writefile[0] != '/') {
        syslog(LOG_ERR, "Validation Error: writefile '%s' is not a full path (must start with '/').", writefile);
        fprintf(stderr, "Error: writefile is not a full path to a file.\n");
        closelog();
        return EXIT_FAILURE;
    }

    // Write to file
    filePointer = fopen(writefile, "w");
    if (filePointer == NULL) {
        syslog(LOG_ERR, "File Error: Failed to open file '%s' for writing: %m", writefile);
        perror("Error opening file");
        fprintf(stderr, "Error: Failed to open file '%s' for writing.\n", writefile);
        closelog();
        return EXIT_FAILURE;
    }

    syslog(LOG_DEBUG, "Writing content to file.");
    for (int i = 2; i < argc - 1; i++) {
        fprintf(filePointer, "%s ", argv[i]);
    }
    fprintf(filePointer, "%s\n", argv[argc-1]);

    if (fclose(filePointer) != 0) {
        syslog(LOG_WARNING, "File Close Warning: Failed to correctly close file '%s': %m", writefile);
        perror("Error closing file");
        fprintf(stderr, "Warning: Failed to correctly close file '%s'.\n", writefile);
    }

    syslog(LOG_INFO, "Successfully wrote to '%s'.", writefile);
    printf("Successfully wrote to '%s'.\n", writefile);

    closelog();

    return EXIT_SUCCESS;
}
