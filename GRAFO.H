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

/* Tipo referência para um grafo */

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

		 GRF_CondRetVerticeJaExiste ,
		       /* O vertice ja existe no grafo */

         GRF_CondRetVerticeNaoExiste,
               /* o vertice nao existe no grafo*/

         GRF_CondRetArestaJaExiste ,
               /* a aresta ja existe no grafo */

         GRF_CondRetArestaNaoExiste,
               /* a aresta nao existe */

		 GRF_CondRetGrafoNaoExiste ,
			   /* O grafo nao existe */

         GRF_CondRetFaltouMemoria ,
               /* Faltou memória ao tentar criar um elemento de lista */

		 GRF_CondRetErroAoObterValor,
		       /*erro ao obter elemento de alguma das listas */

		 GRF_CondRetVerticesDesconexos,
		       /* nao existe caminho entre os vertices */

		 GRF_CondRetErroInserirVertice,
		      /* erro ao inserir o vértice */

		 GRF_CondRetErroInserirAresta
			  /* erro ao inserir a aresta */
		 
   } GRF_tpCondRet ;


/***********************************************************************
*
*  $FC Função: GRF  &Criar Grafo
*
*  $ED Descrição da função
*		Cria um Grafo genérico e não direcionado, com uma lista duplamente encadeada
*		para seus vértices e uma para suas origens.
*		Não existe identificador de tipo associado ao grafo.
*    
*  $EP Parâmetros
*		ppGrafo - referência para ponteiro de grafo a ser criado
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
*  $AE Assertivas de entrada
*     - O grafo não existe
*
*  $AS Assertivas de saída
*     - O grafo existe e é vazio
*	  - Valem as assertivas estruturais do grafo
*
***********************************************************************/

   GRF_tpCondRet GRF_CriarGrafo ( GRF_tppGrafo * ppGrafo , void ( * ExcluirValor ) ( void * pValor ) );


/***********************************************************************
*
*  $FC Função: GRF  &Criar Vertice
*
*  $ED Descrição da função
*		Cria um vértice com uma chave genérica e o insere na lista
*		de vértices.
*    
*  $EP Parâmetros
*		pGrafo -  ponteiro para o grafo onde se deseja criar o vértice
*
*		pValor - ponteiro para chave do vértice a ser criado
*		
*  $FV Valor retornado
*		GRF_CondRetOK                   - criou vértice sem problemas
*		GRF_CondRetFaltouMemoria        - faltou memória ao alocar espaço  
*		GRF_CondRetGrafoNaoExiste       - grafo passado como ponteiro não existe 
*		GRF_CondRetVerticeJaExiste      - já existe um vértice com a chave passada 
*							              como ponteiro
*		GRF_CondRetErroAoInserirVertice - falhou ao inserir vértice na lista de vértices
*
*  $AE Assertivas de entrada
*     - O grafo existe e não contém o vértice a ser inserido
*	  - Valem as assertivas estruturais do grafo
*
*  $AS Assertivas de saída
*     - O grafo existe e tem um vértice a mais
*	  - Valem as assertivas estruturais do grafo
*
***********************************************************************/

   GRF_tpCondRet GRF_CriaVertice ( GRF_tppGrafo pGrafo , void * pValor , int chave ) ;


   /***********************************************************************
*
*  $FC Função: GRF  &Cria Aresta
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
*		GRF_CondRetOK                - criou aresta sem problemas
*		GRF_CondRetFaltouMemoria     - faltou memória ao alocar espaço  
*		GRF_CondRetGrafoNaoExiste    - grafo passado como ponteiro não existe 
*		GRF_ArestaJaExiste           - já existe uma aresta entre os vértices passados 
*							           como ponteiro
*		GRF_CondRetVerticeNaoExiste  - ao menos um dos vértices não existe
*		GRF_CondRetErroInserirAresta - falhou ao inserir aresta
*
*  $AE Assertivas de entrada
*     - O grafo existe
*	  - Os vértices de chaves A e B existem
*	  - Não existe aresta entre os vértices
*	  - Valem as assertivas estruturais do grafo
*
*  $AS Assertivas de saída
*     - O grafo existe
*	  - Os vértices de chaves A e B existem
*	  - Existe aresta entre os vértices
*	  - Valem as assertivas estruturais do grafo
*
***********************************************************************/


   GRF_tpCondRet GRF_CriaAresta(GRF_tpGrafo * pGrafo , int chaveA, int chaveB);


   /***********************************************************************
*
*  $FC Função: GRF  &Remove Aresta
*
*  $ED Descrição da função
*		Remove uma aresta entre dois vértices do grafo.
*    
*  $EP Parâmetros
*		pGrafo -  ponteiro para o grafo onde se deseja criar a aresta
*
*		pValorA - ponteiro para chave de um dos vértice a ser removida a aresta
*
*		pValorB - ponteiro para chave de um dos vértice a ser removida a aresta		
*
*  $FV Valor retornado
*		GRF_CondRetOK               - removeu aresta sem problemas
*		GRF_CondRetGrafoNaoExiste   - grafo passado como ponteiro não existe 
*		GRF_CondRetArestaNaoExiste  - Não existe uma aresta com a chave passada 
*							          como ponteiro
*		GRF_CondRetVerticeNaoExiste - ao menos um dos vértices não existe
*
*  $AE Assertivas de entrada
*     - O grafo existe
*	  - Os vértices de chaves A e B existem
*	  - Existe aresta entre os vértices
*	  - Valem as assertivas estruturais do grafo
*
*  $AS Assertivas de saída
*     - O grafo existe
*	  - Os vértices de chaves A e B existem
*	  - Não existe aresta entre os vértices
*	  - Valem as assertivas estruturais do grafo
*
***********************************************************************/

   GRF_tpCondRet GRF_RemoveAresta(GRF_tppGrafo pGrafo, int chaveA , int chaveB);


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
*  $AE Assertivas de entrada
*     - O grafo existe
*	  - Valem as assertivas estruturais do grafo
*
*  $AS Assertivas de saída
*     - O grafo não existe
*	  - O conteúdo dos vértices do grafo são desalocados segundo
*		a função ExcluirValor fornecida
*
***********************************************************************/

   void GRF_DestroiGrafo (GRF_tppGrafo pGrafo);


/***********************************************************************
*
*  $FC Função: GRF  &Esvazia Grafo
*
*  $ED Descrição da função
*		Retorna o grafo ao seu estado original, sem nenhum vértice
*
*  $EP Parâmetros
*		pGrafo - ponteiro para o grafo que se deseja esvaziar	
*
*  $FV Valor retornado
*		GRF_CondRetOK             - grafo foi esvaziado com sucesso
*		GRF_CondRetGrafoNaoExiste - grafo passado como ponteiro não existe
*
*  $AE Assertivas de entrada
*		- O grafo existe
*		- Valem as assertivas estruturais do grafo
*
*  $AS Assertivas de saída
*		- O grafo nao possui nenhum vertice
*		- Valem as assertivas estruturais do grafo
*
***********************************************************************/

	GRF_tpCondRet GRF_EsvaziaGrafo ( GRF_tppGrafo pGrafo ) ;


/***********************************************************************
*
*  $FC Função: GRF  &Existe Caminho
*
*  $ED Descrição da função
*		Procura um caminho entre dois vértices do grafo.
*    
*  $EP Parâmetros
*		pGrafo         -  ponteiro para o grafo onde se deseja procurar o caminho
*
*		verticeOrigem  - ponteiro para chave de um dos vértices a procurar o caminho
*
*		verticeDestino - ponteiro para chave de um dos vértices a procurar o caminho		
*
*  $FV Valor retornado
*		GRF_CondRetOK            - encontrou caminho entre os vértices
*		GRF_CondRetGrafoNaoExiste - grafo passado como ponteiro não existe 
*		GRF_CondRetVerticeNaoExiste - Não existe vértice com a chave passada 
*									como ponteiro
*		GRF_CondRetErroAoObterValor - houve erro ao obter um elemento de uma 
*									das listas
*		GRF_CondRetVerticesDesconexos - não há caminho entre os vértices
*
*  $AE Assertivas de entrada
*     - O grafo existe
*	  - Os vértices de origem e destino existem
*	  - Valem as assertivas estruturais do grafo
*
*  $AS Assertivas de saída
*     - O grafo permanece inalterado
*	  - Valem as assertivas estruturais do grafo
*
***********************************************************************/

    GRF_tpCondRet GRF_ExisteCaminho ( GRF_tppGrafo pGrafo , int chaveOrigem , int chaveDestino , int * buffer );


/***********************************************************************
*
*  $FC Função: GRF  &Existe Vertice
*
*  $ED Descrição da função
*		Verifica se o vertice passado como parametro esta contido no grafo
*		passado como parametro
*
*  $EP Parâmetros
*		pGrafo - grafo aonde sera buscado o vertice
*		pValor - chave do vertice que se deseja buscar
*
*  $FV Valor retornado
*		GRF_CondRetGrafoNaoExiste   - grafo nao existe
*		GRF_CondRetVerticeJaExiste  - vertice esta contido no grafo
*		GRF_COndRetVerticeNaoExiste - vertice nao esta contido no grafo
*
*  $AE Assertivas de entrada
*		- O grafo existe
*		- Valem as assertivas estruturais do grafo
*		- A chave passada e de um tipo valido
*
*  $AS Assertivas de saída
*		- O grafo permanece inalterado
*		- Valem as assertivas estruturais do grafo
*
***********************************************************************/

	GRF_tpCondRet GRF_ExisteVertice ( GRF_tppGrafo pGrafo , int chave );


/***********************************************************************
*
*  $FC Função: GRF  &Criar Vertice Origem
*
*  $ED Descrição da função
*		insere o vértice na lista de origens, se ainda não existir o vértice
*		também o cria.
*    
*  $EP Parâmetros
*		pGrafo -  ponteiro para o grafo onde se deseja inserir a origem
*
*		pValor - ponteiro para chave do vértice a ser origem
*
*  $FV Valor retornado
*		GRF_CondRetOK                 - criou vértice sem problemas
*		GRF_CondRetFaltouMemoria      - faltou memória ao alocar espaço  
*		GRF_CondRetGrafoNaoExiste     - grafo passado como ponteiro não existe 
*		GRF_VerticeJaExiste           - já existe um vértice com a chave passada 
*							            como ponteiro como origem
*		GRF_CondRetErroInserirVertice - falhou ao inserir vértice na lista de origens
*
*  $AE Assertivas de entrada
*     - O grafo existe e não contém o vértice a ser inserido como origem
*	  - Valem as assertivas estruturais do grafo
*
*  $AS Assertivas de saída
*     - O grafo existe e tem um vértice a mais como origem
*	  - Valem as assertivas estruturais do grafo
*
***********************************************************************/

   GRF_tpCondRet GRF_AlteraCorrente ( GRF_tppGrafo pGrafo , int chave ) ;

   GRF_tpCondRet GRF_ExisteAresta ( GRF_tppGrafo pGrafo , int chaveA , int chaveB ) ;

   GRF_tpCondRet GRF_IrVizinho (GRF_tppGrafo pGrafo , int chave) ;

   GRF_tpCondRet GRF_ObterCorr ( GRF_tppGrafo pGrafo , int * pChave , void ** ppValor );

   GRF_tpCondRet GRF_AlterarValorCorr ( GRF_tppGrafo pGrafo , void * pValor );

   GRF_tpCondRet GRF_Caminhar ( GRF_tppGrafo pGrafo , int chaveDestino ) ;


/********** Fim do módulo de definição: GRF Grafo não orientado **********/


