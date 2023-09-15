#include <stdio.h>
#include <stdlib.h>
#include "Huffman.h"

int main(void)
{
	char str[] = "beep boop beer!";
	//We build the tree depending on the string
	htTree* codeTree = buildTree(str);
	//We build the table depending on the Huffman tree
	hlTable* codeTable = buildTable(codeTree);

	//We encode using the Huffman table
	encode(codeTable, str);
	//We decode using the Huffman tree
	//We can decode string that only use symbols from the initial string
	char code[] = "0011111000111";
	decode(codeTree, code);
	//Output : 0011 1110 1011 0001 0010 1010 1100 1111 1000 1001
	return 0;
}