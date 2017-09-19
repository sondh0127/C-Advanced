#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "fields.h"
#include "dllist.h"
#include "jrb.h"

main()
{
  IS is;
  Dllist tmp, lines;
  JRB words, rtmp;
  int i, j;
  char *s;

  is = new_inputstruct(NULL);

  words = make_jrb();

  while (get_line(is) >= 0) {
    /* End words when you see punctuation: */
    for (i = 0; i < is->NF; i++) {
      s = is->fields[i];
      for (j = 0; j < strlen(s); j++) {
        if (ispunct(s[j]) && s[j] != '-' && s[j] != '\'') {
          s[j] = '\0';
        } else {
          s[j] = tolower(s[j]);
        }
      }
      if (strlen(s) > 0) {
        rtmp = jrb_find_str(words, s) ;
        if (rtmp == NULL) {
          rtmp = jrb_insert_str(words, strdup(s), new_jval_v(new_dllist()));
        }
        lines = (Dllist) rtmp->val.v;
        dll_append(lines, new_jval_i(is->line));
      }
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
