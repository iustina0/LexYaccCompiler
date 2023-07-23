#pragma once 

#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include<math.h>
#include<string.h>
#include <stdbool.h>

struct nodARB {
  char val[100];
  char tip[100];
  struct nodARB* left;
  struct nodARB* right;
};

typedef struct nodARB nods;
typedef nods *nod;

