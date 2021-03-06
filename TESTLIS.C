/***************************************************************************
*  $MCI M�dulo de implementa��o: TLIS Teste lista de caracteres
*
*  Arquivo gerado:              TestLIS.c
*  Letras identificadoras:      TLIS
*
*  Projeto: INF 1301 Automatiza��o dos testes de m�dulos C
*  Gestor:  DI/PUC-Rio
*  Autores: avs - Arndt von Staa
*			cs  -  Clara Szwarcman
*			gs  -  Guilherme Simas
*			lb  -  Lucas Borges
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*	  5      csgslb 03/set/2014 adapta��es devido a padroniza��o das fun��es
*								e passa a tratar apenas uma lista por vez
*     4       avs   01/fev/2006 criar linguagem script simb�lica
*     3       avs   08/dez/2004 uniformiza��o dos exemplos
*     2       avs   07/jul/2003 unifica��o de todos os m�dulos em um s� projeto
*     1       avs   16/abr/2003 in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este modulo cont�m as fun��es espec�ficas para o teste do
*     m�dulo lista com caracteres em seus elementos. Ele trata de
*	  apenas uma lista de cada vez.
*
*  $EIU Interface com o usu�rio pessoa
*     Comandos de teste espec�ficos para testar o m�dulo lista:
*
*     =criarlista <CondRetEsperada>
*					- cria uma lista vazia utilizando a fun��o
*					LIS_CriarLista.
*					Obs. nota��o:
*					<CondRetEsperada> � a condi��o de retorno
*					que se espera do comando de teste. Est�o
*					descritas no LISTA.H.
*
*     =esvaziarlista <CondRetEsperada>
*					- esvazia a lista utilizando a fun��o
*					 LIS_EsvaziarLista.
*
*     =destruirlista <CondRetEsperada>
*					- destr�i a lista utilizando a fun��o
*					 LIS_DestruirLista.
*
*     =inselemantes <Char> <CondRetEsperada>
*					- Chama a fun��o LIS_InserirElementoAntes
*					  para inserir um elemento contendo o caracter
*					  fornecido antes do elemento corrente
*					  da lista
*					Obs. nota��o:
*					<Char> � o caracter a ser inserido
*
*     =inselemapos <Char> <CondRetEsperada>
*					- Chama a fun��o LIS_InserirElementoApos
*					  para inserir um elemento contendo o caracter
*					  fornecido ap�s o elemento corrente
*					  da lista
*
*     =excluirelem <CondRetEsperada>
*					- Exclui o elemento corrente da lista
*					  utilizando a fun��o LIS_ExcluirElemento.

*
*     =obtervalorelem <CharEsp> <CondRetEsperada>
*					- Obt�m o conte�do do elemento corrente da
*					  lista utilizando a fun��o LIS_ObterValor.
*					Obs. nota��o:
*					<CharEsp> � o caracter que se espera estar
*					 contido no elemento corrente.
*
*     =irinicio <CondRetEsperada>
*					- Muda o elemento corrente para o primeiro
*					 elemento da lista utilizando a fun��o
*					 LIS_IrInicioLista.
*
*     =irfinal <CondRetEsperada>
*					- Muda o elemento corrente para o �ltimo
*					 elemento da lista utilizando a fun��o
*					 LIS_IrFinalLista.
*
*     =avancarelem <numElem> <CondRetEsperada>
*					- Avan�a o elemento corrente da lista
*					 tantas vezes quanto fornecido como 
*					 par�metro utilizando a fun��o 
*					 LIS_AvancarElementoCorrente.
*					Obs. nota��o:
*					<numElem> � o n�mero de vezes que o 
*					 elemento corrente ser� avan�ado.
*
*	  =alterarvalor	<novoChar> <CondRetEsperada>
*					- Altera o valor do elemento corrente
*					  utilizando a fun��o LIS_AlterarValor.
*					Obs. nota��o:
*					<novoChar> � o novo caracter a ser
*					 contido noelemento corrente.
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Lista.h"
#include    "caracter.h"


static const char CRIAR_LISTA_CMD         [ ] = "=criarlista"     ;
static const char DESTRUIR_LISTA_CMD      [ ] = "=destruirlista"  ;
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

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TLIS &Efetuar opera��es de teste espec�ficas para lista
*
*  $ED Descri��o da fun��o
*     Efetua os diversos comandos de teste espec�ficos para o m�dulo
*     lista sendo testado.
*
*  $EP Par�metros
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

            if ( CondRetObt != LIS_CondRetOK ) /* Destr�i caracter se n�o consegue inserir */
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

			if ( CondRetObt != LIS_CondRetOK ) /* Destr�i caracter se n�o consegue inserir */
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
                     "Condi��o de retorno errada ao excluir elemento.") ;

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
                     "Condi��o de retorno errada ao obter valor corrente." ) ;
			
			if( Ret!=TST_CondRetOK) /* Interrompe caso condi��o de retorno obtida � 
			                           diferente da esperada */ 
			{
				return Ret;
			} 
			else if ( CondRetEsp!= LIS_CondRetOK)  /* Interrompe caso n�o � para 
												      checar se valor contido no
													  elemento � igual ao esperado */
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
                     "Condi��o de retorno errada ao ir para o elemento inicial." ) ;

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
                     "Condi��o de retorno errada ao ir para o elemento final." ) ;

         } /* fim ativa: Testar ir para o elemento final */

      /* Testar avan�ar elemento */

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

         } /* fim ativa: Testar avan�ar elemento */

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

			LIS_ObterValor( pLista,&pTemp ) ; /* Desaloca espa�o referenciado por elemento */
			CHR_DestruirCaracter(pTemp) ;

            CondRetObt = LIS_AlterarValor ( pLista , pDado ) ;
			
            return TST_CompararInt( CondRetEsp , CondRetObt ,
                     "Condi��o de retorno errada ao ir para o elemento inicial." ) ;

         } /* fim ativa: Testar alterar valor do elemento corrente */

      return TST_CondRetNaoConhec ;

   } /* Fim fun��o: TLIS &Testar lista */




/********** Fim do m�dulo de implementa��o: TLIS Teste lista de caracteres **********/

