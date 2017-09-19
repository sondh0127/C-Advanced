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
  JRB wordfreq, rtmp2, second_level;
  int i, j, freq;
  char *s;

  is = new_inputstruct(NULL);

  words = make_jrb();

  while (get_line(is) >= 0) {

    for (i = 0; i < is->NF; i++) {
      s = is->fields[i];
      for (j = 0; j < strlen(s); j++) {
        if (s[j] == '(' && j == 0) {       
          s++; 
          j--;
        } else if (ispunct(s[j]) && s[j] != '-' && s[j] != '\'') {
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
        if (dll_empty(lines) || lines->blink->val.i != is->line) {
          dll_append(lines, new_jval_i(is->line));
        }
      }
    }
  }

  wordfreq = make_jrb();

  jrb_traverse(rtmp, words) {
    lines = (Dllist) rtmp->val.v;
    freq = 0;
    dll_traverse(tmp, lines) freq++;
    rtmp2 = jrb_find_int(wordfreq, freq);
    if (rtmp2 == NULL) {
      rtmp2 = jrb_insert_int(wordfreq, freq, new_jval_v(make_jrb()));
    }
    second_level = (JRB) rtmp2->val.v;
    jrb_insert_str(second_level, rtmp->key.s, new_jval_v(lines));
  }

  jrb_rtraverse(rtmp, wordfreq) {
    second_level = (JRB) rtmp->val.v;
    jrb_traverse(rtmp2, second_level) {
      printf("%15s:", rtmp2->key.s);
      lines = (Dllist) rtmp2->val.v;
      dll_traverse(tmp, lines) {
        if (tmp != dll_first(lines)) printf(",");
        printf(" %d", tmp->val.i);
      }
      printf("\n");
    }
  }
}
