/*
    nxtd_bt_dummy.c
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

#ifndef _NXTD_BT_BLUEZ_H_
#define _NXTD_BT_BLUEZ_H_

#include <sys/types.h>
#include <bluetooth/bluetooth.h>

#include "nxtd.h"

#define NXT_BT_DEVCLASS_BYTE0 4
#define NXT_BT_DEVCLASS_BYTE1 8
#define NXT_BT_DEVCLASS_BYTE2 0

#define NXT_BT_WAIT_TIMEOUT 5000 /* milliseconds */
#define NXT_BT_IDLE_TIMEOUT 60   /* seconds */

struct nxtd_nxt_bt {
  struct nxtd_nxt nxt;
  int bt_sock;
  bdaddr_t bt_addr;
  int connected;
};

int nxtd_bt_init();
void nxtd_bt_shutdown();
void nxtd_bt_close(struct nxtd_nxt_bt *nxt);
void nxtd_bt_scan();
int nxtd_bt_connect(struct nxtd_nxt_bt *nxt);
int nxtd_bt_disconnect(struct nxtd_nxt_bt *nxt);
ssize_t nxtd_bt_send(struct nxtd_nxt_bt *nxt,const void *data,size_t size);
ssize_t nxtd_bt_recv(struct nxtd_nxt_bt *nxt,void *data,size_t size);

#endif /* _NXTD_BT_BLUEZ_H_ */
