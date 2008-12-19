/*
    nxtd.h
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

#ifndef _NXTD_H_
#define _NXTD_H_

#include <usb.h>
#include <pthread.h>

#define NXTD_MAXNUM 256

typedef enum {
  NXTD_USB,
  NXTD_BT
} nxtd_conn_t;

struct nxtd_nxt {
  char *name;
  nxtd_conn_t conn_type;
  unsigned int i;
  time_t conn_timeout;
};

struct {
  pthread_mutex_t mutex;
  struct nxtd_nxt *list[NXTD_MAXNUM];
  unsigned int i;
} nxts;

int nxtd_nxt_reg(struct nxtd_nxt *nxt);
struct nxtd_nxt *nxtd_nxt_find(const char *name,nxtd_conn_t conn_type);
void nxtd_nxt_refresh(struct nxtd_nxt *nxt);

#endif /* _NXTD_H_ */
