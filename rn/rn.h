enum coloracao { Vermelho, Preto }; 
typedef enum coloracao Cor; 

typedef struct noRN { 
    struct noRN* pai; 
    struct noRN* esquerda; 
    struct noRN* direita; 
    Cor cor; 
    int valor; 
} NoRN; 

typedef struct arvoreRN { 
    struct noRN* raiz; 
    struct noRN* nulo;  
} ArvoreRN; 


ArvoreRN* criarArvoreRN(); 
int adicionarValorRN(ArvoreRN* arvore, int valor);