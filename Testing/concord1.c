#include <stdio.h>
#include <string.h>
#include "fields.h"
#include "dllist.h"
#include "jrb.h"

main()
{
  IS is;
  Dllist tmp, lines;
  JRB words, rtmp;
  int i;

  is = new_inputstruct(NULL);

  words = make_jrb();

  while (get_line(is) >= 0) {
    for (i = 0; i < is->NF; i++) {
      rtmp = jrb_find_str(words, is->fields[i]) ;
      if (rtmp == NULL) {
        rtmp = jrb_insert_str(words, strdup(is->fields[i]), 
                                     new_jval_v(new_dllist()));
      }
      lines = (Dllist) rtmp->val.v;
      dll_append(lines, new_jval_i(is->line));
    }
  }

  jrb_traverse(rtmp, words) {
    printf("%15s:", rtmp->key.s);
    lines = (Dllist) rtmp->val.v;
    dll_traverse(tmp, lines) {
      if (tmp != dll_first(lines)) printf(",");
      printf(" %d", tmp->val.i);
    }
    printf("\n");
  }
}
    
