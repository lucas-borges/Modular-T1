/***************************************************************************
*  $MCI M�dulo de implementa��o: TGRF Teste grafo
*
*  Arquivo gerado:              TESTGRF.c
*  Letras identificadoras:      TGRF
*
*  Projeto: INF 1301 Automatiza��o dos testes de m�dulos C
*  Gestor:  DI/PUC-Rio
*  Autores: cs  -  Clara Szwarcman
*			gs  -  Guilherme Simas
*			lb  -  Lucas Borges
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*	  1      csgslb 23/set/2014 in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este modulo cont�m as fun��es espec�ficas para o teste do
*     m�dulo grafo gen�rico. Ele trata de apenas um grafo de cada vez.
*
*  $EIU Interface com o usu�rio pessoa
*     Comandos de teste espec�ficos para testar o m�dulo lista:
*
*     =comando <Par�metro>
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include	"GRAFO.H"

#include	"CARACTER.H"

static const char COMANDO_CMD         [ ] = "=comando"     ;


static const char CRIAR_GRAFO_CMD	  [ ] = "=criagrafo"  ;
static const char DESTROI_GRAFO_CMD   [ ] = "=destroigrafo" ;
static const char INSERE_VERTICE_CMD  [ ] = "=inserevertice" ;

GRF_tppGrafo pGrafo;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TGRF &Efetuar opera��es de teste espec�ficas para grafo
*
*  $ED Descri��o da fun��o
*     Efetua os diversos comandos de teste espec�ficos para o m�dulo
*     grafo sendo testado.
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


	/* Testar COMANDO */
	if ( strcmp( ComandoTeste , COMANDO_CMD ) == 0 )
	{

		numLidos = LER_LerParametros( "i" ,
			&CondRetEsp ) ;

		if ( numLidos != 1 )
		{
			return TST_CondRetParm ;
		} /* if */

		CondRetObt=GRF_funcao(   ) ;

		return TST_CompararInt( CondRetEsp , CondRetObt ,
			"Retorno errado ao COMANDO." );

	} /* fim ativa: Testar COMANDO */

	
	/* Testar Criar Grafo */
	else if( strcmp( ComandoTeste , CRIAR_GRAFO_CMD ) == 0 )
	{
		numLidos = LER_LerParametros ( "i" ,
			 &CondRetEsp ) ;
		
		if ( numLidos != 1 )
		{
			return TST_CondRetParm ;
		}/* if */

		CondRetObt = GRF_CriarGrafo ( &pGrafo , CHR_ComparaCaracter , CHR_DestruirCaracter ) ;

		return TST_CompararInt ( CondRetEsp , CondRetObt , 
				"Retorno errado ao criar grafo.") ;

	} /* fim ativa: Testar Criar Grafo */

	/* Testar Destroi Grafo */
	else if ( strcmp( ComandoTeste , DESTROI_GRAFO_CMD ) == 0 )
	{

		numLidos = LER_LerParametros( "i" ,
			&CondRetEsp ) ;

		if ( numLidos != 1 )
		{
			return TST_CondRetParm ;
		} /* if */

		CondRetObt=GRF_DestroiGrafo ( pGrafo ) ;

		pGrafo = NULL ;

		return TST_CompararInt( CondRetEsp , CondRetObt ,
			"Retorno errado ao destruir o Grafo." );

	} /* fim ativa: Testar Destroi Grafo */

	/* Testar Insere Vertice */
	else if ( strcmp( ComandoTeste , INSERE_VERTICE_CMD ) == 0 )
	{

		CHR_tppCaracter pCaracter ;
		char ValorVertice ;

		numLidos = LER_LerParametros( "ci" ,
			&ValorVertice , &CondRetEsp ) ;

		if ( numLidos != 2 )
		{
			return TST_CondRetParm ;
		} /* if */

		pCaracter = CHR_CriarCaracter ( ValorVertice ) ;

		if ( pCaracter == NULL )
		{
			return TST_CondRetMemoria ;
		}

		CondRetObt = GRF_CriaVertice ( pGrafo , pCaracter ) ;

		return TST_CompararInt( CondRetEsp , CondRetObt ,
			"Retorno errado ao COMANDO." );

	} /* fim ativa: Testar Cria Vertice */

	return TST_CondRetNaoConhec;

} /* Fim fun��o: TGRF &Testar Grafo */

/********** Fim do m�dulo de implementa��o: TGRF Teste grafo gen�rico **********/