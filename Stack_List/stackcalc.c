#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exprdef.h"
#include "exprlinkedstack.h"
#include "stackcalc.h"

int pushLSExprToken(LinkedStack* pStack, ExprToken data)
{
	StackNode node = { 0, };
	node.data = data;
	return pushLS(pStack, node);
}

void calcExpr(ExprToken* pExprTokens, int tokenCount)
{
	LinkedStack* pStack = NULL;
	StackNode* pNode1 = NULL, * pNode2 = NULL;
	Precedence tokenType;
	int i = 0;
	if (pExprTokens == NULL) {
		return;
	}

	pStack = createLinkedStack();
	if (pStack != NULL) {
		for (i = 0; i < tokenCount; i++) {
			tokenType = pExprTokens[i].type;

			if (tokenType == operand) {
				pushLSExprToken(pStack, pExprTokens[i]);
			}
			else {
				pNode2 = popLS(pStack);
				if (pNode2 != NULL) {
					pNode1 = popLS(pStack);
					if (pNode1 != NULL) {
						float op1 = pNode1->data.value;
						float op2 = pNode2->data.value;

						ExprToken newToken;
						newToken.type = operand;
						switch (tokenType) {
						case plus:
							newToken.value = op1 + op2;
							break;
						case minus:
							newToken.value = op1 - op2;
							break;
						case times:
							newToken.value = op1 * op2;
							break;
						case divide:
							newToken.value = op1 / op2;
							break;
						}
						pushLSExprToken(pStack, newToken);
						free(pNode1);
					}
					free(pNode2);
				}
			} // end-of-else
		}

		pNode1 = popLS(pStack);
		if (pNode1 != NULL) {
			printf("Result: [%f]\n",
				pNode1->data.value);
			free(pNode1);
		}
		else {
			printf("Error in Calculate\n");
		}
		deleteLinkedStack(pStack);
	}
}