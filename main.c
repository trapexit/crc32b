/*
  ISC License

  Copyright (c) 2023, Antonio SJ Musumeci <trapexit@spawn.link>

  Permission to use, copy, modify, and/or distribute this software for any
  purpose with or without fee is hereby granted, provided that the above
  copyright notice and this permission notice appear in all copies.

  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#include "crc32b.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 4096

int
main(int    argc_,
     char **argv_)
{
  FILE *fp;
  size_t n;
  crc32b_t crc;
  char buf[BUF_SIZE];

  for(int i = 1; i < argc_; i++)
    {
      const char *filepath = argv_[i];

      crc = crc32b_start();

      fp = fopen(filepath,"r");
      if(fp == NULL)
        {
          fprintf(stderr,"crc32b: %s: %s\n",filepath,strerror(errno));
          continue;
        }

      while(!feof(fp))
        {
          n = fread(buf,1,BUF_SIZE,fp);

          crc = crc32b_continue(buf,n,crc);
        }

      fclose(fp);

      crc = crc32b_finish(crc);

      printf("%08x %s\n",crc,filepath);
    }

  return 0;
}
