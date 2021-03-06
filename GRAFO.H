/***************************************************************************
*
*  $MCD M�dulo de defini��o: GRF Grafo n�o orientado
*
*  Arquivo gerado:              GRAFO.h
*  Letras identificadoras:      GRF
*
*  Projeto: INF 1301 Automatiza��o dos testes de m�dulos C
*  Gestor:  DI/PUC-Rio
*  Autores: cs  -  Clara Szwarcman
*			gs  -  Guilherme Simas
*			lb  -  Lucas Borges
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1      csgslb 23/set/2014 in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Implementa grafos n�o orientados utilizando listas 
*	  gen�ricas duplamente encadeadas.
*     Podem existir n grafos em opera��o simultaneamente.
*     O grafo possui uma cabe�a encapsulando o seu estado.
*	  Cada v�rtice possui uma chave que o identifica. A chave
*	  tem de ser um n�mero inteiro n�o negativo. Dois v�rtices
*	  n�o podem ter a mesma chave.
*
*
*
*************************************************************************/


/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para um grafo */

typedef struct GRF_tagGrafo * GRF_tppGrafo ;

/***********************************************************************
*
*  $TC Tipo de dados: GRF Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es da lista
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
               /* Faltou mem�ria ao tentar criar um elemento de lista */

		 GRF_CondRetErroAoObterValor,
		       /*erro ao obter elemento de alguma das listas */

		 GRF_CondRetVerticesDesconexos,
		       /* nao existe caminho entre os vertices */

		 GRF_CondRetErroInserirVertice,
		      /* erro ao inserir o v�rtice */

		 GRF_CondRetErroInserirAresta
			  /* erro ao inserir a aresta */
		 
   } GRF_tpCondRet ;


/***********************************************************************
*
*  $FC Fun��o: GRF  &Criar Grafo
*
*  $ED Descri��o da fun��o
*		Cria um Grafo gen�rico e n�o direcionado, com uma lista duplamente encadeada
*		para seus v�rtices e uma para suas origens.
*		N�o existe identificador de tipo associado ao grafo.
*    
*  $EP Par�metros
*		ppGrafo - refer�ncia para ponteiro de grafo a ser criado
*
*		ExcluirValor  - ponteiro para a fun��o que processa a
*                     exclus�o do valor referenciado pelo elemento
*                     a ser exclu�do.
*                     Ver descri��o do m�dulo.
*
*  $FV Valor retornado
*		GRF_CondRetOK            - criou grafo sem problemas
*		GRF_CondRetFaltouMemoria - faltou mem�ria ao alocar espa�o  
*
*  $AE Assertivas de entrada
*     - O grafo n�o existe
*
*  $AS Assertivas de sa�da
*     - O grafo existe e � vazio
*	  - Valem as assertivas estruturais do grafo
*
***********************************************************************/

   GRF_tpCondRet GRF_CriarGrafo ( GRF_tppGrafo * ppGrafo , void ( * ExcluirValor ) ( void * pValor ) );


/***********************************************************************
*
*  $FC Fun��o: GRF  &Criar Vertice
*
*  $ED Descri��o da fun��o
*		Cria um v�rtice com uma chave gen�rica e o insere na lista
*		de v�rtices.
*    
*  $EP Par�metros
*		pGrafo -  ponteiro para o grafo onde se deseja criar o v�rtice
*
*		pValor - ponteiro para o valor contido no v�rtice a ser criado
*
*		chave  - valor da chave do vertice, deve ser obrigatoriamente um inteiro n�o negativo
*		
*  $FV Valor retornado
*		GRF_CondRetOK                   - criou v�rtice sem problemas
*		GRF_CondRetFaltouMemoria        - faltou mem�ria ao alocar espa�o  
*		GRF_CondRetGrafoNaoExiste       - grafo passado como ponteiro n�o existe 
*		GRF_CondRetVerticeJaExiste      - j� existe um v�rtice com a chave passada 
*							              como ponteiro
*		GRF_CondRetErroAoInserirVertice - falhou ao inserir v�rtice na lista de v�rtices
*
*  $AE Assertivas de entrada
*	  - pGrafo � um ponteiro v�lido para um Grafo
*	  - Valem as assertivas estruturais do grafo
*	  - chave � um valor v�lido para uma chave (inteiro n�o negativo)
*
*  $AS Assertivas de sa�da
*	  - Se o grafo existe ele possui um vertice a mais
*     - O vertice criado ser� o vertice corrente do grafo
*       SOMENTE se o grafo era vazio
*	  - Valem as assertivas estruturais do grafo
*
***********************************************************************/

   GRF_tpCondRet GRF_CriaVertice ( GRF_tppGrafo pGrafo , void * pValor , int chave ) ;

   /***********************************************************************
*
*  $FC Fun��o: GRF  &Cria Aresta
*
*  $ED Descri��o da fun��o
*		Cria uma aresta entre dois v�rtices do grafo.
*    
*
*  $EP Par�metros
*		pGrafo -  ponteiro para o grafo onde se deseja criar o v�rtice
*
*		chaveA - chave de um dos v�rtice a ser criada a aresta
*
*		chaveB - chave de um dos v�rtice a ser criada a aresta		
*
*  $FV Valor retornado
*		GRF_CondRetOK                - criou aresta sem problemas
*		GRF_CondRetFaltouMemoria     - faltou mem�ria ao alocar espa�o  
*		GRF_CondRetGrafoNaoExiste    - grafo passado como ponteiro n�o existe 
*		GRF_ArestaJaExiste           - j� existe uma aresta entre os v�rtices passados 
*							           como ponteiro
*		GRF_CondRetVerticeNaoExiste  - ao menos um dos v�rtices n�o existe
*		GRF_CondRetErroInserirAresta - falhou ao inserir aresta
*
*  $AE Assertivas de entrada
*     - pGrafo � um ponteiro v�lido para um Grafo
*	  - As chaves A e B s�o v�lidas
*	  - Valem as assertivas estruturais do grafo
*
*  $AS Assertivas de sa�da
*     - Se o grafo existe, existe agora uma aresta entre os v�rtices
*	  - Valem as assertivas estruturais do grafo
*
***********************************************************************/


   GRF_tpCondRet GRF_CriaAresta( GRF_tppGrafo pGrafo , int chaveA, int chaveB);


   /***********************************************************************
*
*  $FC Fun��o: GRF  &Remove Aresta
*
*  $ED Descri��o da fun��o
*		Remove uma aresta entre dois v�rtices do grafo.
*    
*  $EP Par�metros
*		pGrafo -  ponteiro para o grafo onde se deseja criar a aresta
*
*		chaveA - chave de um dos v�rtice a ser removida a aresta
*
*		chaveB - chave de um dos v�rtice a ser removida a aresta		
*
*  $FV Valor retornado
*		GRF_CondRetOK               - removeu aresta sem problemas
*		GRF_CondRetGrafoNaoExiste   - grafo passado como ponteiro n�o existe 
*		GRF_CondRetArestaNaoExiste  - N�o existe uma aresta com a chave passada 
*							          como ponteiro
*		GRF_CondRetVerticeNaoExiste - ao menos um dos v�rtices n�o existe
*
*  $AE Assertivas de entrada
*     - pGrafo � um ponteiro v�lido para um Grafo
*	  - chaveA e chaveB s�o valores v�lidos de chaves
*	  - Valem as assertivas estruturais do grafo
*
*  $AS Assertivas de sa�da
*	  - Se o grafo existia, n�o existe mais aresta entre os v�rtices
*	  - Valem as assertivas estruturais do grafo
*
***********************************************************************/

   GRF_tpCondRet GRF_RemoveAresta(GRF_tppGrafo pGrafo, int chaveA , int chaveB);


/***********************************************************************
*
*  $FC Fun��o: GRF  &Destroi Grafo
*
*  $ED Descri��o da fun��o
*		Destr�i o grafo fornecido
*
*  $EP Par�metros
*		pGrafo -  ponteiro para o grafo a ser destruido
*
*  $AE Assertivas de entrada
*     - pGrafo � um ponteiro valido para um Grafo
*	  - Valem as assertivas estruturais do grafo
*
*  $AS Assertivas de sa�da
*     - O grafo n�o existe
*	  - O conte�do dos v�rtices foi desalocado
*
***********************************************************************/

   void GRF_DestroiGrafo (GRF_tppGrafo pGrafo);

/***********************************************************************
*
*  $FC Fun��o: GRF  &Esvazia Grafo
*
*  $ED Descri��o da fun��o
*		Retorna o grafo ao seu estado original, sem nenhum v�rtice
*
*  $EP Par�metros
*		pGrafo - ponteiro para o grafo que se deseja esvaziar	
*
*  $FV Valor retornado
*		GRF_CondRetOK             - grafo foi esvaziado com sucesso
*		GRF_CondRetGrafoNaoExiste - grafo passado como ponteiro n�o existe
*
*  $AE Assertivas de entrada
*		- pGrafo � um ponteiro v�lido para um Grafo
*		- Valem as assertivas estruturais do grafo
*
*  $AS Assertivas de sa�da
*		- Se o grafo existia, o grafo nao possui mais nenhum vertice
*		- Valem as assertivas estruturais do grafo
*
***********************************************************************/

	GRF_tpCondRet GRF_EsvaziaGrafo ( GRF_tppGrafo pGrafo ) ;


/***********************************************************************
*
*  $FC Fun��o: GRF  &Obtem Caminho
*
*  $ED Descri��o da fun��o
*		Procura um caminho entre dois v�rtices do grafo.
*    
*  $EP Par�metros
*		pGrafo       -  ponteiro para o grafo onde se deseja procurar o caminho
*
*		chaveOrigem  - chave de um dos v�rtices a procurar o caminho
*
*		chaveDestino - chave de um dos v�rtices a procurar o caminho		
*
*		buffer       - buffer de sa�da onde ser� armazenada a sequ�ncia de chaves 
*					   na ordem do caminho da origem at� a sa�da, NULL se n�o � necess�rio
*
*  $FV Valor retornado
*		GRF_CondRetOK                 - encontrou caminho entre os v�rtices
*		GRF_CondRetGrafoNaoExiste     - grafo passado como ponteiro n�o existe 
*		GRF_CondRetVerticeNaoExiste   - N�o existe v�rtice com a chave passada 
*									    como ponteiro
*		GRF_CondRetErroAoObterValor   - houve erro ao obter um elemento de uma 
*									    das listas
*		GRF_CondRetVerticesDesconexos - n�o h� caminho entre os v�rtices
*
*  $AE Assertivas de entrada
*     - pGrafo � um ponteiro v�lido para um Grafo
*	  - chaveOrigem e chaveDestino s�o tipos v�lidos de chave
*	  - Valem as assertivas estruturais do grafo
*     - buffer � um vetor de inteiros de tamanho suficiente para conter
*	  - todo o caminho ou NULL
*
*  $AS Assertivas de sa�da
*     - O grafo permanece inalterado
*	  - buffer cont�m as chaves na ordem do caminho da origem ate a saida
*	  - Valem as assertivas estruturais do grafo
*
***********************************************************************/

    GRF_tpCondRet GRF_ObtemCaminho ( GRF_tppGrafo pGrafo , int chaveOrigem , int chaveDestino , int * buffer );


/***********************************************************************
*
*  $FC Fun��o: GRF  &Existe Vertice
*
*  $ED Descri��o da fun��o
*		Verifica se o vertice passado como parametro esta contido no grafo
*		passado como parametro
*
*  $EP Par�metros
*		pGrafo - grafo aonde sera buscado o vertice
*		pValor - chave do vertice que se deseja buscar
*
*  $FV Valor retornado
*		GRF_CondRetGrafoNaoExiste   - grafo nao existe
*		GRF_CondRetVerticeJaExiste  - vertice esta contido no grafo
*		GRF_COndRetVerticeNaoExiste - vertice nao esta contido no grafo
*
*  $AE Assertivas de entrada
*		- pGrafo � um ponteiro v�lido para Grafo
*		- Valem as assertivas estruturais do grafo
*		- A chave passada e de um tipo valido de chave
*
*  $AS Assertivas de sa�da
*		- O grafo permanece inalterado
*		- Valem as assertivas estruturais do grafo
*
***********************************************************************/

	GRF_tpCondRet GRF_ExisteVertice ( GRF_tppGrafo pGrafo , int chave );


/***********************************************************************
*
*  $FC Fun��o: GRF  &Altera Corrente
*
*  $ED Descri��o da fun��o
*		altera o elemento corrente do grafo para o elemento de chave passada
*		como parametro, independentemente se est�o interconectados.
*    
*  $EP Par�metros
*		pGrafo -  ponteiro para o grafo onde se deseja alterar o elemento corrente
*
*		chave  - chave do elemento que deseja que se torne corrente
*
*  $FV Valor retornado
*		GRF_CondRetOK                 - alterou corrente sem problemas  
*		GRF_CondRetGrafoNaoExiste     - grafo passado como ponteiro n�o existe 
*		GRF_VerticeNaoExiste          - nao existe um v�rtice com a chave passada
*
*  $AE Assertivas de entrada
*     - pGrafo � um ponteiro valido para Grafo
*	  - A chave passada � de um tipo valido de chave
*	  - Valem as assertivas estruturais do grafo
*
*  $AS Assertivas de sa�da
*     - Se o grafo existe, seu elemento corrente agora � o da chave passada como parametro
*	  - Valem as assertivas estruturais do grafo
*
***********************************************************************/

   GRF_tpCondRet GRF_AlteraCorrente ( GRF_tppGrafo pGrafo , int chave ) ;

   /***********************************************************************
*
*  $FC Fun��o: GRF  &Existe Aresta
*
*  $ED Descri��o da fun��o
*		verifica se a aresta entre os vertices de chaves passadas como parametro
*		existe.       
*    
*  $EP Par�metros
*		pGrafo -  ponteiro para o grafo onde se procurar a aresta      
*
*		chaveA - chave de um dos vertices pertencentes � aresta
*
*       chaveB - chave de um dos vertices pertencentes � aresta
*
*  $FV Valor retornado
*		GRF_CondRetVerticesDesconexos - Nao existe aresta entre os vertices
*		GRF_CondRetArestaJaExiste     - Existe aresta entre os vertices
*		GRF_CondRetGrafoNaoExiste     - grafo passado como ponteiro n�o existe 
*		GRF_CondRetVerticeNaoExiste   - o vertice de uma das chaves passadas como
*							            parametro nao existe     
*
*  $AE Assertivas de entrada
*     - pGrafo � um ponteiro v�lido para Grafo
*     - as chaves passadas como parametro s�o de um tipo v�lido
*	  - Valem as assertivas estruturais do grafo
*
*  $AS Assertivas de sa�da
*     - O grafo permanece inalterado
*	  - Valem as assertivas estruturais do grafo
*
***********************************************************************/

   GRF_tpCondRet GRF_ExisteAresta ( GRF_tppGrafo pGrafo , int chaveA , int chaveB ) ;

   /***********************************************************************
*
*  $FC Fun��o: GRF  &Ir Vizinho
*
*  $ED Descri��o da fun��o
*		altera o elemento corrente do grafo passado como parametro para
*		o vertice vizinho correspondente � chave passada como parametro
*    
*  $EP Par�metros
*		pGrafo -  ponteiro para o grafo onde se deseja inserir a origem
*
*		chave  -  chave do v�rtice a ser o novo elemento corrente do grafo
*
*  $FV Valor retornado
*		GRF_CondRetOK                 - alterou o elemento corrente sem problemas
*		GRF_CondRetVerticesDesconexos - o vertice da chave passada como parametro n�o
*										� vizinho do vertice corrente
*		GRF_CondRetGrafoNaoExiste     - grafo passado como ponteiro n�o existe 
*		GRF_CondRetVerticeNaoExiste   - o vertice correspondente � chave passada 
*							            como parametro nao existe
*
*  $AE Assertivas de entrada
*     - pGrafo � um ponteiro v�lido para Grafo
*	  - <chave> � um tipo v�lido de chave
*	  - Valem as assertivas estruturais do grafo
*
*  $AS Assertivas de sa�da
*     - Se o grafo existia seu elemento corrente agora � o vertice de chave <chave>
*	  - Valem as assertivas estruturais do grafo
*
***********************************************************************/

   GRF_tpCondRet GRF_IrVizinho (GRF_tppGrafo pGrafo , int chave) ;

 /***********************************************************************
*
*  $FC Fun��o: GRF  &Obter Corrente
*
*  $ED Descri��o da fun��o
*		obtem o valor contido no vertice elemento corrente do grafo assim
*		como sua chave
*    
*  $EP Par�metros
*		pGrafo  - ponteiro para o grafo onde se deseja obter o valor contido na corrente
*
*		ppValor - endere�o de um ponteiro que ir� receber o valor contido no vertice corrente
*
*		pChave  - endere�o da variavel que receber� o valor da chave do elemento corrente
*
*  $FV Valor retornado
*		GRF_CondRetOK                 - obteve valores com sucesso 
*		GRF_CondRetVerticeNaoExiste   - vertice da chave passada como parametro nao existe
*		GRF_CondRetGrafoNaoExiste     - grafo passado como ponteiro n�o existe 
*
*  $AE Assertivas de entrada
*     - pGrafo � um ponteiro v�lido para Grafo
*	  - ppValor � um ponteiro para uma variavel de tipo v�lido para um valor contido em um vertice
*     - pChave � um ponteiro v�lido para uma variavel de tipo int
*	  - Valem as assertivas estruturais do grafo
*
*  $AS Assertivas de sa�da
*     - O grafo permanece inalterado
*	  - Se o grafo existia e n�o era vazio, pValor agora aponta para o valor do vertice corrente
*	    e pChave agora aponta para o valor da chave do vertice corrente
*	  - Valem as assertivas estruturais do grafo
*
***********************************************************************/
 
   GRF_tpCondRet GRF_ObterCorr ( GRF_tppGrafo pGrafo , int * pChave , void ** ppValor );

   /***********************************************************************
*
*  $FC Fun��o: GRF  &Alterar Valor Corrente
*
*  $ED Descri��o da fun��o
*		altera valor contido no vertice corrente desalocando o valor atual
*    
*  $EP Par�metros
*		pGrafo -  ponteiro para o grafo onde se deseja alterar o valor do vertice corrente
*
*		pValor - ponteiro para o valor a ser inserido no vertice corrente
*
*  $FV Valor retornado
*		GRF_CondRetOK                 - alterou valor do vertice sem problemas
*		GRF_CondRetGrafoNaoExiste     - grafo passado como ponteiro n�o existe 
*		GRF_CondVerticeNaoExiste      - o vertice corrente nao existe
*
*  $AE Assertivas de entrada
*     - pGrafo � um ponteiro v�lido para Grafo
*	  - pValor � um ponteiro v�lido para o tipo de valor a ser inserido no Grafo
*	  - Valem as assertivas estruturais do grafo
*
*  $AS Assertivas de sa�da
*     - Se o grafo e o vertice corrente existiam, o valor do vertice corrente agora � pValor
*       e o valor contido anteriormente foi desalocado
*	  - Valem as assertivas estruturais do grafo
*
***********************************************************************/

   GRF_tpCondRet GRF_AlterarValorCorr ( GRF_tppGrafo pGrafo , void * pValor );

   /***********************************************************************
*
*  $FC Fun��o: GRF  &Caminhar
*
*  $ED Descri��o da fun��o
*		altera o vertice corrente do grafo para um elemento vertice de chave
*		conectado ao vertice corrente atual
*		
*    
*  $EP Par�metros
*		pGrafo       - ponteiro para o grafo onde se deseja alterar o vertice corrente
*
*		chaveDestino - chave do v�rtice a ser vertice corrente
*
*  $FV Valor retornado
*		GRF_CondRetOK                 - alterou vertice corrente sem problemas
*		GRF_CondRetVerticeNaoExiste   - vertice corrente nao existe ou vertice da 
*                                       chave de destino nao existe  
*		GRF_CondRetGrafoNaoExiste     - grafo passado como ponteiro n�o existe 
*		GRF_CondRetVerticesDesconexos - vertice corrente e o vertice da chave de destino 
*							            s�o desconexos
*
*  $AE Assertivas de entrada
*     - pGrafo � um ponteiro v�lido para Grafo
*	  - chaveDestino � de um tipo v�lido de chave
*	  - Valem as assertivas estruturais do grafo
*
*  $AS Assertivas de sa�da
*     - Se o grafo existe, o vertice corrente existe, e os vertices estavam 
*       conectados, o vertice corrente do grafo agora � o da chaveDestino
*	  - Valem as assertivas estruturais do grafo
*
***********************************************************************/

   GRF_tpCondRet GRF_Caminhar ( GRF_tppGrafo pGrafo , int chaveDestino ) ;


/********** Fim do m�dulo de defini��o: GRF Grafo n�o orientado **********/


