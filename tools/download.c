/*
    download.c
    aNXT - a NXt Toolkit
    Libraries and tools for LEGO Mindstorms NXT robots
    Copyright (C) 2008  Janosch Gräf <janosch.graef@gmx.net>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <nxt.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

void usage(char *cmd,int r) {
  fprintf(stderr,"Usage: %s [OPTION] INPUT [OUTPUT]\n",cmd);
  fprintf(stderr,"Download a file from NXT to computer\n");
  fprintf(stderr,"Options:\n");
  fprintf(stderr,"\t-h         Show help\n");
  fprintf(stderr,"\t-n NXTNAME Name of NXT (Default: first found) or bluetooth address\n");
  exit(r);
}

int main(int argc,char *argv[]) {
  char *name = NULL;
  char *src,*dest;
  int c;

  while ((c = getopt(argc,argv,":hn:"))!=-1) {
    switch(c) {
      case 'h':
        usage(argv[0],0);
        break;
      case 'n':
        name = strdup(optarg);
        break;
      case ':':
        fprintf(stderr,"Option -%c requires an operand\n",optopt);
        usage(argv[0],1);
        break;
      case '?':
        fprintf(stderr,"Unrecognized option: -%c\n", optopt);
        usage(argv[0],1);
        break;
    }
  }

  nxt_init();
  nxt_t *nxt = nxt_open(name);
  if (nxt==NULL) {
    fprintf(stderr,"Could not find NXT\n");
    return 1;
  }

  if (optind<argc) {
    src = argv[optind];

    optind++;
    if (optind<argc) dest = argv[optind];
    else dest = src;

    nxt_download(nxt,src,dest);
  }
  else {
    fprintf(stderr,"No input file\n");
    usage(argv[0],1);
  }

  int ret = nxt_error(nxt);
  if (name!=NULL) free(name);
  nxt_close(nxt);

  return ret;
}
