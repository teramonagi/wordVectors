//  Copyright 2013 Google Inc. All Rights Reserved.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.

#include <stdio.h>
#include <string.h>
#include <math.h>

const long long max_size = 2000;         // max length of strings
const long long N = 20;                  // number of closest words that will be shown
const long long max_w = 50;              // max length of vocabulary entries

void distance(char *file_name0, char *word0, char *returnw, double *returnd) {
  FILE *f;
  char st1[max_size];
  char bestw[N][max_size];
  char file_name[max_size], st[100][max_size];
  float dist, len, bestd[N], vec[max_size];
  long long words, size, a, b, c, d, cn, bi[100];
  char ch;
  float *M;
  char *vocab;

  strcpy(file_name, file_name0);
  f = fopen(file_name, "rb");
  if (f == NULL) {
    printf("Input file not found\n");

  }
  if(fscanf(f, "%lld", &words)==1);
  if(fscanf(f, "%lld", &size)==1);
  vocab = (char *)malloc((long long)words * max_w * sizeof(char));
  M = (float *)malloc((long long)words * (long long)size * sizeof(float));
  if (M == NULL) {
    printf("Cannot allocate memory: %lld MB    %lld  %lld\n", (long long)words * size * sizeof(float) / 1048576, words, size);

  }
  for (b = 0; b < words; b++) {
    if(fscanf(f, "%s%c", &vocab[b * max_w], &ch)==1);
    for (a = 0; a < size; a++) if(fread(&M[a + b * size], sizeof(float), 1, f)==1);
    len = 0;
    for (a = 0; a < size; a++) len += M[a + b * size] * M[a + b * size];
    len = sqrt(len);
    for (a = 0; a < size; a++) M[a + b * size] /= len;
  }
  fclose(f);
  for (a = 0; a < N; a++) bestd[a] = 0;
  for (a = 0; a < N; a++) bestw[a][0] = 0;
  a = 0;

  strcpy(st1, word0);


  cn = 0;
  b = 0;
  c = 0;
  while (1) {
    st[cn][b] = st1[c];
    b++;
    c++;
    st[cn][b] = 0;
    if (st1[c] == 0) break;
    if (st1[c] == ' ') {
      cn++;
      b = 0;
      c++;
    }
  }
  cn++;
  for (a = 0; a < cn; a++) {
    for (b = 0; b < words; b++) if (!strcmp(&vocab[b * max_w], st[a])) break;
    if (b == words) b = -1;
    bi[a] = b;
    printf("\nWord: %s  Position in vocabulary: %lld\n", st[a], bi[a]);
    if (b == -1) {
      printf("Out of dictionary word!\n");
      break;
    }
  }
    
  for (a = 0; a < size; a++) vec[a] = 0;
  for (b = 0; b < cn; b++) {
    if (bi[b] == -1) continue;
    for (a = 0; a < size; a++) vec[a] += M[a + bi[b] * size];
  }
  len = 0;
  for (a = 0; a < size; a++) len += vec[a] * vec[a];
  len = sqrt(len);
  for (a = 0; a < size; a++) vec[a] /= len;
  for (a = 0; a < N; a++) bestd[a] = 0;
  for (a = 0; a < N; a++) bestw[a][0] = 0;
  for (c = 0; c < words; c++) {
    a = 0;
    for (b = 0; b < cn; b++) if (bi[b] == c) a = 1;
    if (a == 1) continue;
    dist = 0;
    for (a = 0; a < size; a++) dist += vec[a] * M[a + c * size];
    for (a = 0; a < N; a++) {
      if (dist > bestd[a]) {
        for (d = N - 1; d > a; d--) {
          bestd[d] = bestd[d - 1];
          strcpy(bestw[d], bestw[d - 1]);
        }
        bestd[a] = dist;
        strcpy(bestw[a], &vocab[c * max_w]);
        break;
      }
    }
  }
  for (a = 0; a < N; a++) {
//    printf("%50s\t\t%f\n", bestw[a], bestd[a]);
    returnw = strcat(returnw, " ");
    returnw = strcat(returnw, bestw[a]);
    returnd[a] = bestd[a];
  }

}
