//
//  bedutil.h
//
// Created by shiquan on 5/18/14.
// Copyright (c) 2014 ___BGIRESEARCH___. All rights reserved.
//

#ifndef BEDUTILS_H
#define BEDUTILS_H
#include <stdint.h>
#include "khash.h"

typedef struct
  {
  int m;
  int n;
  int flag;
  uint64_t *a;
  int *idx;
  void *data; // self defined data
  }
bedreglist_t;

typedef struct
  {
  uint32_t length;
  void *data;
  }
chromosome_t;

KHASH_MAP_INIT_STR(reg, bedreglist_t)
KHASH_MAP_INIT_STR(chr, chromosome_t)
typedef kh_reg_t regHash_t;
typedef kh_chr_t chrHash_t;

typedef struct
  {
  uint32_t region;
  uint32_t length;
  uint32_t total;
  }
inf_t;

typedef void (*bedvoid_destroy)(void *data);
void destroy_void(void *data);

typedef void (*handle_func)(regHash_t *bed);

struct _bedHandle
  {
  /* handle inf_t */
  inf_t * (*init)();
  /* handle whole struct */ 
  void (*read)(const char *fn, regHash_t *reg, int a, int b, int *ret);
  void (*merge)(regHash_t *bed);
  void (*uniq)(regHash_t *bed1, regHash_t *bed2);
  void (*diff)(regHash_t *bed1, regHash_t *bed2);
  void (*trim)(regHash_t *bed, int trim1, int trim2);
  /* handle each chromosome */
  bedreglist_t * (*reg_add)(bedreglist_t *reg1, bedreglist_t *reg2);
  void (*reg_merge)(bedreglist_t *reg1);
  bedreglist_t * (*reg_uniq)(bedreglist_t *reg1, bedreglist_t *reg2);
  bedreglist_t * (*reg_diff)(bedreglist_t *reg1, bedreglist_t *reg2);
  bedreglist_t * (*reg_trim)(bedreglist_t *reg, int trim1, int trim2);
  void (*sort_reg) (bedreglist_t *reg);
  /* save file */
  void (*save)(const char *fn, regHash_t *bed);
  /* destroy */
  void (*destroy)(regHash_t *rghsh, bedvoid_destroy func);
  /* stat */
  inf_t * (*stat)(regHash_t *bed);
  void (*base1to0) (regHash_t *bed);
  void (*base0to1) (regHash_t *bed);
  void (*pipeout)(regHash_t *bed);

  /* if the region is out of chromosome return khiter, else 
     return -1 : normal 
     return -2 : the chomosome is not contaioned in chrHash
  */
  int (*check_length)(regHash_t * bed, chrHash_t *chr);
  };

typedef struct _bedHandle bedHandle_t;

#endif
