#ifndef _ANALYSISWIN_H_
#define _ANALYSISWIN_H_

#include "data.h"

typedef struct {
    int total;
    int done;
    int reject;
} StatOrder;

typedef struct {
    int in;
    int out;
    int stock;
} StatStore;

typedef struct {
    int transport;
    int delivered;
    int totalTransport;
} StatTransport;

int analysisWin();
int orderStatWin();
int storeStatWin();
int transportStatWin();
int exportReportWin();

#endif

