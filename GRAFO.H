/***************************************************************************
*
*  $MCD Módulo de definição: GRF Grafo não orientado
*
*  Arquivo gerado:              GRAFO.h
*  Letras identificadoras:      GRF
*
*  Projeto: INF 1301 Automatização dos testes de módulos C
*  Gestor:  DI/PUC-Rio
*  Autores: cs  -  Clara Szwarcman
*			gs  -  Guilherme Simas
*			lb  -  Lucas Borges
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1      csgslb 16/abr/2003 início desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa grafos não orientados utilizando listas 
*	  genéricas duplamente encadeadas.
*     Podem existir n listas em operação simultaneamente.
*     O grafo possui uma cabeça encapsulando o seu estado.
*
*
*
*************************************************************************/


/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma lista */

typedef struct GRF_tagGrafo * GRF_tppGrafo ;


/***********************************************************************
*
*  $TC Tipo de dados: GRF Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da lista
*
***********************************************************************/

   typedef enum {

         GRF_CondRetOK ,
               /* Concluiu corretamente */

		 GRF_VerticeJaExiste ,
		       /* O vertice ja existe no grafo */

         GRF_VerticeNaoExiste,
               /* o vertice nao existe no grafo*/

         GRF_ArestaJaExiste ,
               /* a aresta ja existe no grafo */

         GRF_ArestaNaoExiste,
               /* a aresta nao existe */

		 GRF_CondRetGrafoNaoExiste ,
			   /* O grafo nao existe */

         GRF_CondRetFaltouMemoria ,
               /* Faltou memória ao tentar criar um elemento de lista */
		 
   } GRF_tpCondRet ;


/***********************************************************************
*
*  $FC Função: GRF  &Nome função
*
*  $ED Descrição da função
*    
*
*  $EP Parâmetros
*     
*
*  $FV Valor retornado
*     
*
***********************************************************************/


/***********************************************************************
*
*  $FC Função: GRF  &Criar Grafo
*
*  $ED Descrição da função
*		Cria um Grafo genérico e não direcionado, com uma lista duplamente encadeada
*		para seus vértices e uma para suas origens.
*		Não existe identificador de tipo associado ao grafo.
*    
*
*  $EP Parâmetros
*		ppGrafo - referência para ponteiro de grafo a ser criado
*
*
*		ComparaValor - ponteiro para a função que compara os valores
*					 referenciados por vértices do grafo.
*
*		ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
*                     Ver descrição do módulo.
*
*  $FV Valor retornado
*		GRF_CondRetOK            - criou grafo sem problemas
*		GRF_CondRetFaltouMemoria - faltou memória ao alocar espaço  
*
***********************************************************************/

   GRF_tpCondRet GRF_CriarGrafo ( GRF_tppGrafo * ppGrafo , int ( * ComparaValor ) ( void * pValorA , void * pValorB ) , void ( ExcluirValor * ) ( void * pValor ) );


/***********************************************************************
*
*  $FC Função: GRF  &Criar Vertice
*
*  $ED Descrição da função
*		Cria um vértice com uma chave genérica e o insere na lista
*		de vértices.
*    
*
*  $EP Parâmetros
*		pGrafo -  ponteiro para o grafo onde se deseja criar o vértice
*
*		pValor - ponteiro para chave do vértice a ser criado
*		
*
*  $FV Valor retornado
*		GRF_CondRetOK            - criou vértice sem problemas
*		GRF_CondRetFaltouMemoria - faltou memória ao alocar espaço  
*		GRF_CondRetGrafoNaoExiste - grafo passado como ponteiro não existe 
*		GRF_VerticeJaExiste - já existe um vértice com a chave passada 
*							  como ponteiro
*
***********************************************************************/

   GRF_tpCondRet GRF_CriaVertice ( GRF_tpGrafo * Grafo , void * pValor ) ;


   /***********************************************************************
*
*  $FC Função: GRF  &Criar Aresta
*
*  $ED Descrição da função
*		Cria uma aresta entre dois vértices do grafo.
*    
*
*  $EP Parâmetros
*		pGrafo -  ponteiro para o grafo onde se deseja criar o vértice
*
*		pValorA - ponteiro para chave de um dos vértice a ser criada a aresta
*
*		pValorB - ponteiro para chave de um dos vértice a ser criada a aresta		
*
*  $FV Valor retornado
*		GRF_CondRetOK            - criou aresta sem problemas
*		GRF_CondRetFaltouMemoria - faltou memória ao alocar espaço  
*		GRF_CondRetGrafoNaoExiste - grafo passado como ponteiro não existe 
*		GRF_ArestaJaExiste - já existe uma aresta entre os vértices passados 
*							  como ponteiro
*
***********************************************************************/


   GRF_tpCondRet GRF_CriaAresta(void * pValorA, void * pValorB, GRF_tpGrafo * pGrafo);


   /***********************************************************************
*
*  $FC Função: GRF  &Remove Aresta
*
*  $ED Descrição da função
*		Remove uma aresta entre dois vértices do grafo.
*    
*
*  $EP Parâmetros
*		pGrafo -  ponteiro para o grafo onde se deseja criar a aresta
*
*		pValorA - ponteiro para chave de um dos vértice a ser removida a aresta
*
*		pValorB - ponteiro para chave de um dos vértice a ser removida a aresta		
*
*  $FV Valor retornado
*		GRF_CondRetOK            - removeu aresta sem problemas
*		GRF_CondRetGrafoNaoExiste - grafo passado como ponteiro não existe 
*		GRF_ArestaNaoExiste - Não existe uma aresta com a chave passada 
*							  como ponteiro
*
***********************************************************************/

   GRF_tpCondRet GRF_RemoveAresta(void * pValorA, void * pValorB, GRF_tpGrafo * pGrafo);


    /***********************************************************************
*
*  $FC Função: GRF  &Destroi Grafo
*
*  $ED Descrição da função
*		Destrói o grafo fornecido
*
*  $EP Parâmetros
*		pGrafo -  ponteiro para o grafo a ser destruido
*	
*
*  $FV Valor retornado
*		GRF_CondRetOK     - destruiu grafo sem problemas
*
***********************************************************************/

   GRF_tpCondRet GRF_DestroiGrafo (GRF_tppGrafo pGrafo);
   
/********** Fim do módulo de definição: GRF Grafo não orientado **********/


