#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph_weighted_jrb.h"
#include "../../lib/include/dllist.h"
#include "huffman.h"
Coding huffmanTable[256];

void code(JRB tree, char c, char * hmcode, int length, int * found) {
    char check = jval_c(tree->val);
    // Need a better filter to check for the character
    if ((check >= 'a' && check <= 'z') || (check >= 'A' && check <= 'Z') || check == ' ' || check == '.') {
        if (check == c) {
            printf("FOUND %c: ", c);
            for (int i = 0; i < length; i++) {
                printf("%c", hmcode[i]);
            }
            printf("\n");
            * found = 1;
        }
    } else {
        tree = jval_v(tree->val);
        JRB branch;

        jrb_traverse(branch, tree) {
            if (*found) return; 
            if (branch == tree->flink) {
                hmcode[length] = '0';
            } else {
                hmcode[length] = '1';
            }
            code(branch, c, hmcode, length + 1, found);
        }
    }
}


Huffman_Tree makeHuffman(char *buffer, int size)
{
	Huffman_Tree hTree;
	hTree.graph = createGraph();

	JRB count = make_jrb();
	JRB node;

	Dllist queue = new_dllist();
	Dllist temp;

	int total = 0;
	Dllist queueTree = new_dllist();
	// Counting how many time each character appears in the string (Using JRB)
	for (int i = 0; i < size; i++)	{
		char c[1];
		c[0] = buffer[i];
		node = jrb_find_str(count, c);

		if (node == NULL) {
			jrb_insert_str(count, strdup(c), new_jval_i(1));
		} else {
			int value = jval_i(node->val);
			jrb_delete_node(node);
			jrb_insert_str(count, strdup(c), new_jval_i(value + 1));
		}
	}
	printf("COUNT:\n");
	jrb_traverse(node, count) {
		printf("%s, %d\n", jval_s(node->key), jval_i(node->val));
	}

	jrb_traverse(node, count) {
		int found = 0;

        // Find the appropriate position to insert the new node in the queue,
        // which is before the first node that appears more than the current node
		dll_traverse(temp, queue) {
			JRB head = jval_v(temp->val);
			int value = jval_i(head->val);
			if (jval_i(node->val) < value) {
				dll_insert_b(temp, new_jval_v(node));
				found = 1;
				break;
			}
		}

        // If said position can not be found, push the element at the end of the queue
		if (found == 0) {
			dll_append(queue, new_jval_v(node));
		}
	}
	printf("QUEUE: \n");
	dll_traverse(temp, queue) {	
		node = jval_v(temp->val);
		printf("%s, %d\n", jval_s(node->key), jval_i(node->val));
	}


    // Convert each node in the priority queue into a JRB tree
	dll_traverse(temp, queue) {
		JRB tree = make_jrb();
		JRB head = jval_v(temp->val);
		jrb_insert_int(tree, jval_i(head->val), new_jval_c(jval_s(head->key)[0]));
		dll_append(queueTree, new_jval_v(tree));
		total++;
	}
	for (int i = 0; i < total - 1; i++) {
		Dllist first, second;
		int key, leftKey, rightKey;
		JRB tree, head;
		JRB newTree = make_jrb();
		JRB subTree = make_jrb();

        // Take the first element
		first = dll_first(queueTree);
		tree = jval_v(first->val);
		head = tree->flink;
		leftKey = jval_i(head->key);
        // Add the first element as subtree of the new tree
		jrb_insert_int(subTree, leftKey, new_jval_v(head->val));

        // Take the second element
		second = dll_next(first);
		tree = jval_v(second->val);
		head = tree->flink;
		rightKey = jval_i(head->key);
        // Add the second element as subtree of the new tree
		jrb_insert_int(subTree, rightKey, new_jval_v(head->val));

		key = leftKey + rightKey;
		jrb_insert_int(newTree, key, new_jval_v(subTree));

        // Shift the first two elements out of the queue
		dll_delete_node(first);
		dll_delete_node(second);

        // Find the position to insert the new element
        // to maintain the queue's priority
		int found = 0;
		dll_traverse(temp, queueTree) {
			tree = jval_v(temp->val);
			head = tree->flink;
			if (key < jval_i(head->key)) {
				dll_insert_b(temp, new_jval_v(newTree));
				found = 1;
				break;
			}
		}

		if (found == 0) {
			dll_append(queueTree, new_jval_v(newTree));
		}

        // Uncomment to see the queue after each cycle
        dll_traverse(temp, queueTree) {
            JRB tree = jval_v(temp->val);
            jrb_traverse(node, tree) {
                printf("%d\t", jval_i(node->key));
            }
        }
        printf("\n"); // Try comment this line, lol
    }

    // Generate a Huffman Tree from the queue
    temp = dll_first(queueTree); // The only element left in the queue
    JRB root = jval_v(temp->val);

    root = root->flink;
    char * hmcode = malloc(10 * sizeof(char));
    dll_traverse(temp, queue) {
    	node = jval_v(temp->val);
    	int found = 0;
    	code(root, jval_s(node->key)[0], hmcode, 0, &found);
    }
    return hTree;
}