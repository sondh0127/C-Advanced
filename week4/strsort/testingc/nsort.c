#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include "../../lib/libfdr/jrb.h"
#include "../../lib/libfdr/fields.h"

int main()
{
  JRB b;
  JRB bn;
  IS is;

  is = new_inputstruct(NULL);
  b = make_jrb();

  while (get_line(is) >= 0) {
    (void) jrb_insert_int(b, atoi(is->text1), new_jval_s(strdup(is->text1)));
  }
  int found = 0;
  JRB node = jrb_find_gte_int(b, 5, &found);
  if(found)
    printf("%s", jval_s(node->val));
  else {
    printf("Not Found!\nThe smallest one greater\n%s", jval_s(node->val));
  }

  // jrb_traverse(bn, b) {
  //   printf("%d\n", jval_i(bn->key));
  //   //printf("%s", jval_s(bn->val));
  // }
}
