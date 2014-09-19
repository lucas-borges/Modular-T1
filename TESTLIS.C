/***************************************************************************
*  $MCI Módulo de implementação: TLIS Teste lista de caracteres
*
*  Arquivo gerado:              TestLIS.c
*  Letras identificadoras:      TLIS
*
*  Projeto: INF 1301 Automatização dos testes de módulos C
*  Gestor:  DI/PUC-Rio
*  Autores: avs - Arndt von Staa
*			cs  -  Clara Szwarcman
*			gs  -  Guilherme Simas
*			lb  -  Lucas Borges
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*	  5      csgslb 03/set/2014 adaptações devido a padronização das funções
*								e passa a tratar apenas uma lista por vez
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
*  $ED Descrição do módulo
*     Este modulo contém as funções específicas para o teste do
*     módulo lista com caracteres em seus elementos. Ele trata de
*	  apenas uma lista de cada vez.
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo lista:
*
*     =criarlista <CondRetEsperada>
*					- cria uma lista vazia utilizando a função
*					LIS_CriarLista.
*					Obs. notação:
*					<CondRetEsperada> é a condição de retorno
*					que se espera do comando de teste. Estão
*					descritas no LISTA.H.
*
*     =esvaziarlista <CondRetEsperada>
*					- esvazia a lista utilizando a função
*					 LIS_EsvaziarLista.
*
*     =destruirlista <CondRetEsperada>
*					- destrói a lista utilizando a função
*					 LIS_DestruirLista.
*
*     =inselemantes <Char> <CondRetEsperada>
*					- Chama a função LIS_InserirElementoAntes
*					  para inserir um elemento contendo o caracter
*					  fornecido antes do elemento corrente
*					  da lista
*					Obs. notação:
*					<Char> é o caracter a ser inserido
*
*     =inselemapos <Char> <CondRetEsperada>
*					- Chama a função LIS_InserirElementoApos
*					  para inserir um elemento contendo o caracter
*					  fornecido após o elemento corrente
*					  da lista
*
*     =excluirelem <CondRetEsperada>
*					- Exclui o elemento corrente da lista
*					  utilizando a função LIS_ExcluirElemento.

*
*     =obtervalorelem <CharEsp> <CondRetEsperada>
*					- Obtém o conteúdo do elemento corrente da
*					  lista utilizando a função LIS_ObterValor.
*					Obs. notação:
*					<CharEsp> é o caracter que se espera estar
*					 contido no elemento corrente.
*
*     =irinicio <CondRetEsperada>
*					- Muda o elemento corrente para o primeiro
*					 elemento da lista utilizando a função
*					 LIS_IrInicioLista.
*
*     =irfinal <CondRetEsperada>
*					- Muda o elemento corrente para o último
*					 elemento da lista utilizando a função
*					 LIS_IrFinalLista.
*
*     =avancarelem <numElem> <CondRetEsperada>
*					- Avança o elemento corrente da lista
*					 tantas vezes quanto fornecido como 
*					 parâmetro utilizando a função 
*					 LIS_AvancarElementoCorrente.
*					Obs. notação:
*					<numElem> é o número de vezes que o 
*					 elemento corrente será avançado.
*
*	  =alterarvalor	<novoChar> <CondRetEsperada>
*					- Altera o valor do elemento corrente
*					  utilizando a função LIS_AlterarValor.
*					Obs. notação:
*					<novoChar> é o novo caracter a ser
*					 contido noelemento corrente.
*
***************************************************************************/
//Guilherme
#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Lista.h"
#include    "caracter.h"


static const char CRIAR_LISTA_CMDguilherme         [ ] = "=criarlista"     ;
static const char DESTRUIR_LISTA_CMDbla      [ ] = "=destruirlista"  ;
static const char ESVAZIAR_LISTA_CMD      [ ] = "=esvaziarlista"  ;
static const char INS_ELEM_ANTES_CMD      [ ] = "=inselemantes"   ;
static const char INS_ELEM_APOS_CMD       [ ] = "=inselemapos"    ;
static const char OBTER_VALOR_CMD         [ ] = "=obtervalorelem" ;
static const char EXC_ELEM_CMD            [ ] = "=excluirelem"    ;
static const char IR_INICIO_CMD           [ ] = "=irinicio"       ;
static const char IR_FIM_CMD              [ ] = "=irfinal"        ;
static const char AVANCAR_ELEM_CMD        [ ] = "=avancarelem"    ;
static const char ALTERAR_VALOR_CMD       [ ] = "=alterarvalor"    ;


LIS_tppLista pLista;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS &Efetuar operações de teste específicas para lista
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     lista sendo testado.
*
*  $EP Parâmetros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int numLidos   = -1 , 
          CondRetEsp = -1 ,
		  CondRetObt = -1 ,
		  numElem    = -1 ;
						/* Inicializa para qualquer coisa */
      
	  TST_tpCondRet Ret ;

	  char Dado;
	  void * pDado;


      /* Testar CriarLista */

         if ( strcmp( ComandoTeste , CRIAR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &CondRetEsp ) ;

            if ( numLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

           CondRetObt=LIS_CriarLista( &pLista, CHR_DestruirCaracter ) ;

            return TST_CompararInt( CondRetEsp , CondRetObt ,
                                    "Retorno errado ao criar lista." );

         } /* fim ativa: Testar CriarLista */

      /* Testar Esvaziar lista lista */

         else if ( strcmp( ComandoTeste , ESVAZIAR_LISTA_CMD ) == 0 )
         {

             numLidos = LER_LerParametros( "i" ,
                               &CondRetEsp ) ;

            if ( numLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObt=LIS_EsvaziarLista( pLista ) ;

			return TST_CompararInt( CondRetEsp , CondRetObt ,
                                    "Retorno errado ao esvaziar lista.")  ;

         } /* fim ativa: Testar Esvaziar lista lista */

      /* Testar Destruir lista */

         else if ( strcmp( ComandoTeste , DESTRUIR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &CondRetEsp ) ;

            if ( numLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

           
			LIS_DestruirLista( pLista ) ;
			pLista=NULL;
			CondRetObt=LIS_CondRetOK;

			return TST_CompararInt( CondRetEsp , CondRetObt ,
                                    "Retorno errado ao destruir lista.") ;

         } /* fim ativa: Testar Destruir lista */

      /* Testar inserir elemento antes */

         else if ( strcmp( ComandoTeste , INS_ELEM_ANTES_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ci" ,
                       &Dado , &CondRetEsp ) ;

            if ( numLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            pDado=CHR_CriarCaracter( Dado );

            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */


            CondRetObt = LIS_InserirElementoAntes( pLista , pDado ) ;

            if ( CondRetObt != LIS_CondRetOK ) /* Destrói caracter se não consegue inserir */
            {
               CHR_DestruirCaracter( ( CHR_tppCaracter)pDado ) ;
            } /* if */

			return TST_CompararInt( CondRetEsp , CondRetObt ,
                     "Condicao de retorno errada ao inserir antes.") ;

         } /* fim ativa: Testar inserir elemento antes */

      /* Testar inserir elemento apos */

         else if ( strcmp( ComandoTeste , INS_ELEM_APOS_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ci" ,&Dado , &CondRetEsp ) ;

            if ( numLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            pDado=CHR_CriarCaracter( Dado );

            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

            CondRetObt = LIS_InserirElementoApos( pLista , pDado ) ; 

			if ( CondRetObt != LIS_CondRetOK ) /* Destrói caracter se não consegue inserir */
            {
               CHR_DestruirCaracter( (CHR_tppCaracter)pDado ) ;
            } /* if */

			return TST_CompararInt( CondRetEsp , CondRetObt ,
                     "Condicao de retorno errada ao inserir apos.") ;

         } /* fim ativa: Testar inserir elemento apos */

      /* Testar excluir elemento */

         else if ( strcmp( ComandoTeste , EXC_ELEM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i", &CondRetEsp ) ;

            if ( numLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp ,
                      LIS_ExcluirElemento( pLista ) ,
                     "Condição de retorno errada ao excluir elemento.") ;

         } /* fim ativa: Testar excluir simbolo */

      /* Testar obter valor do elemento corrente */

         else if ( strcmp( ComandoTeste , OBTER_VALOR_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ci" ,
                       &Dado , &CondRetEsp ) ;

            if ( numLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObt = LIS_ObterValor( pLista,&pDado ) ;

			Ret=TST_CompararInt( CondRetEsp , CondRetObt,
                     "Condição de retorno errada ao obter valor corrente." ) ;
			
			if( Ret!=TST_CondRetOK) /* Interrompe caso condição de retorno obtida é 
			                           diferente da esperada */ 
			{
				return Ret;
			} 
			else if ( CondRetEsp!= LIS_CondRetOK)  /* Interrompe caso não é para 
												      checar se valor contido no
													  elemento é igual ao esperado */
			{
				return TST_CondRetOK;
			} /* if */
			
			
			return TST_CompararChar( Dado , CHR_ObterValor( (CHR_tppCaracter) pDado) ,
                         "Valor do elemento errado." ) ;

         } /* fim ativa: Testar obter valor do elemento corrente */

      /* Testar ir para o elemento inicial */

         else if ( strcmp( ComandoTeste , IR_INICIO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" , &CondRetEsp) ;

            if ( numLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObt=LIS_IrInicioLista(pLista ) ;

            return TST_CompararInt( CondRetEsp , CondRetObt ,
                     "Condição de retorno errada ao ir para o elemento inicial." ) ;

         } /* fim ativa: Testar ir para o elemento inicial */

      /* Testar ir para o elemento final */

         else if ( strcmp( ComandoTeste , IR_FIM_CMD ) == 0 )
         {

			 numLidos = LER_LerParametros( "i" , &CondRetEsp) ;

            if ( numLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObt=LIS_IrFinalLista(pLista ) ;

            return TST_CompararInt( CondRetEsp , CondRetObt ,
                     "Condição de retorno errada ao ir para o elemento final." ) ;

         } /* fim ativa: Testar ir para o elemento final */

      /* Testar avançar elemento */

         else if ( strcmp( ComandoTeste , AVANCAR_ELEM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" , &numElem ,
                                &CondRetEsp ) ;

            if ( numLidos != 2  )
            {
               return TST_CondRetParm ;
            } /* if */
			
			return TST_CompararInt( CondRetEsp ,
                      LIS_AvancarElementoCorrente( pLista , numElem ) ,
                      "Condicao de retorno errada ao avancar" ) ;

         } /* fim ativa: Testar avançar elemento */

	  /* Testar alterar valor do elemento corrente */

         else if ( strcmp( ComandoTeste , ALTERAR_VALOR_CMD ) == 0 )
         {

			void * pTemp;
            numLidos = LER_LerParametros( "ci" , &Dado, &CondRetEsp) ;

            if ( numLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

			pDado=CHR_CriarCaracter( Dado );

			if ( pDado == NULL )
			{
				return TST_CondRetMemoria;
			} /* if */

			LIS_ObterValor( pLista,&pTemp ) ; /* Desaloca espaço referenciado por elemento */
			CHR_DestruirCaracter(pTemp) ;

            CondRetObt = LIS_AlterarValor ( pLista , pDado ) ;
			
            return TST_CompararInt( CondRetEsp , CondRetObt ,
                     "Condição de retorno errada ao ir para o elemento inicial." ) ;

         } /* fim ativa: Testar alterar valor do elemento corrente */

      return TST_CondRetNaoConhec ;

   } /* Fim função: TLIS &Testar lista */




/********** Fim do módulo de implementação: TLIS Teste lista de caracteres **********/

