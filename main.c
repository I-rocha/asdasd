#include <stdio.h>
#include <stdlib.h>

#include "ast/ast.h"
#include "parser.tab.h"
#include "lexical/symtab.h"
#include "semantic/semantic.h"
#include  "cgen/cgen.h"
#include "environment/environment.h"

extern FILE* yyin;
FILE* fl;

astNo* astTree;
extern symTable *headEnv;
int main(int argc, char** argv){
	FILE *fp;
	
	
	if(argc <=1){
		printf("Please follow pattern: <exe> <file>\n");
		return 0;
	}

	if(!(fp = fopen(argv[1], "r"))){
		printf("Error openning file of argument\n");
		return 0;
	}
	
	if(!(fl = fopen("output/lexical.txt", "w"))){
		printf("Error oppening file of lexical output\n");
		return 0;
	}

	yyin = fp;


	// Parser + Lexical
	yyparse();
	astSave(astTree, "output/ast.txt");
	//printf("End parser\n");

	/*	Symbol Table	*/
	semantic(astTree);

	symTSave(headEnv, "output/symbolTable.txt");

	quad* code;
	code = gen(astTree);
	// Intermediate Code
	printQuad(code);

	saveCI(code, "output/cgen.txt");

	printf("------ END CGEN --------\n");	
	printf("------ BEGIN ENV --------\n");	
	/* ENVIRONMENT */
	
	envInitGlobal();
	toAssembly(code);
	saveAssembly("output/assembly.txt");
	saveAssemblyPretty("output/assembly_pretty.txt");
	
	// Close files
	if(fp)
		fclose(fp);
	if(fl)
		fclose(fl);

	// Free pointers
	astFree(astTree);

	printf("------ END PROCESSING --------\n");	
	return 1;
}
