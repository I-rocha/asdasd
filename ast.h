#ifndef AST_H
#define AST_H

#define AST_ERR_0 "ERROR-0: Fail to allocate no\n"
#define AST_ERR_1 "ERROR-1: Impossible to allocate child space\n"
#define AST_ERR_2 "ERROR-2: Grammar ID unknow\n"
#define TAB 3

typedef struct ast* ast;
typedef enum  grammID grammID ;

enum grammID{
	kact, karg_lista, kterm, kmult, ksum, kfact, ksoma_exp, krel, ksimple_exp, kvar,	// 0-9
	kexp, kretorno_decl, kiteracao_decl, kselecao_decl, kexp_decl, kstatement_lista, klocal_decl, kcomposto_decl, kparam,	
	kcomposto_decl_match, klocal_decl_match, kstatement_lista_match, kselecao_decl_match, kiteracao_decl_match,
	kparam_lista, kparams, kfun_decl, ktipo_esp, kvar_decl, kdecl_lista,  NIL, terminal
};


struct ast{

	grammID tok;
	ast* children;
	int n_child;
};

// TODO: Change tokens

ast createNo(grammID mytk);
int childrenSpace(ast no, int n_child);
void printTree(ast no, int depth);
void printSpace(int nSpace);
void freeTree(ast no);
void print(grammID sym);

#endif
