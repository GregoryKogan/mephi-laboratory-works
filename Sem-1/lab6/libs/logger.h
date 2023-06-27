#ifndef LOGGER_H
#define LOGGER_H

void logError(char err[]);
void logErrorAndExit(char err[], int status);
void logWarning(char warning[]);
void logSuccess(char success[]);

#endif
