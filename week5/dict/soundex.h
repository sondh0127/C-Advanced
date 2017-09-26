#include "../../lib/btree/btree.h"
#ifndef SOUNDEX_H
#define SOUNDEX_H
void readFile(BTA **root,char *filename);

void creatSoundexTree(BTA *Dic, BTA **soundexTree);
int suggestion(BTA *soundexTree, char *word, char s[][100]);

#endif /* SOUNDEX_H */
