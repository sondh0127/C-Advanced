#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	// "c_flags" : [ "-std=gnu99" ],
		jrb_insert_str(b, strdup(is->text1), new_jval_v());
		//(void) jrb_insert_str(b, strdup(is->text1),new_jval_v(NULL));
	}

	jrb_traverse(bn, b) {
		printf("%s", jval_s(bn->key));
	}
}
