/***************************************************************************
*  $MCI Módulo de implementação: TGRF Teste grafo
*
*  Arquivo gerado:              TESTGRF.c
*  Letras identificadoras:      TGRF
*
*  Projeto: INF 1301 Automatização dos testes de módulos C
*  Gestor:  DI/PUC-Rio
*  Autores: cs  -  Clara Szwarcman
*			gs  -  Guilherme Simas
*			lb  -  Lucas Borges
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*	  1      csgslb 23/set/2014 início desenvolvimento
*
*  $ED Descrição do módulo
*     Este modulo contém as funções específicas para o teste do
*     módulo grafo genérico. Ele trata de apenas um grafo de cada vez.
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo lista:
*
*     =comando <Parâmetro>
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
static const char CRIA_ARESTA_CMD	  [ ] = "=criaaresta" ;
static const char EXISTE_CAMINHO_CMD  [ ] = "=existecaminho" ;
static const char REMOVE_ARESTA_CMD   [ ] = "=removearesta";

GRF_tppGrafo pGrafo;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TGRF &Efetuar operações de teste específicas para grafo
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     grafo sendo testado.
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


	/* Testar COMANDO */
/*	if ( strcmp( ComandoTeste , COMANDO_CMD ) == 0 )
	{

		numLidos = LER_LerParametros( "i" ,
			&CondRetEsp ) ;

		if ( numLidos != 1 )
		{
			return TST_CondRetParm ;
		} /* if */

/*		CondRetObt=GRF_funcao(   ) ;

		return TST_CompararInt( CondRetEsp , CondRetObt ,
			"Retorno errado ao COMANDO." );

	} /* fim ativa: Testar COMANDO */

	
	/* Testar Criar Grafo */
/*	else */if( strcmp( ComandoTeste , CRIAR_GRAFO_CMD ) == 0 )
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
			"Retorno errado ao criar o vertice." );

	} /* fim ativa: Testar Cria Vertice */

	/* Testar Cria Aresta */
	else if ( strcmp( ComandoTeste , CRIA_ARESTA_CMD ) == 0 )
	{
		CHR_tppCaracter pChrA , pChrB ;
		char verticeA , verticeB ;
		
		numLidos = LER_LerParametros( "cci" ,
			&verticeA , &verticeB , &CondRetEsp ) ;

		if ( numLidos != 3 )
		{
			return TST_CondRetParm ;
		} /* if */

		pChrA = CHR_CriarCaracter ( verticeA ) ;
		pChrB = CHR_CriarCaracter ( verticeB ) ;

		CondRetObt = GRF_CriaAresta ( pChrA , pChrB , pGrafo ) ;

		return TST_CompararInt( CondRetEsp , CondRetObt ,
			"Retorno errado ao criar a aresta." );

	} /* fim ativa: Testar Cria Aresta */

	/*Testar Remove Aresta */
	else if ( strcmp( ComandoTeste, REMOVE_ARESTA_CMD) ==0)
	{
		CHR_tppCaracter pChrA , pChrB ;
		char verticeA , verticeB ;
		
		numLidos = LER_LerParametros( "cci" ,
			&verticeA , &verticeB , &CondRetEsp ) ;

		if ( numLidos != 3 )
		{
			return TST_CondRetParm ;
		} /* if */

		pChrA = CHR_CriarCaracter ( verticeA ) ;
		pChrB = CHR_CriarCaracter ( verticeB ) ;

		CondRetObt = GRF_RemoveAresta ( pChrA , pChrB , pGrafo ) ;

		return TST_CompararInt( CondRetEsp , CondRetObt ,
			"Retorno errado ao remover a aresta." );
	}

	/* fim ativa: Testar Criar Aresta */

	/* Testar Existe Caminho */
	else if ( strcmp( ComandoTeste , EXISTE_CAMINHO_CMD ) == 0 )
	{
		char verticeOrigem , verticeDestino ;
		CHR_tppCaracter origem , destino ; 
		
		numLidos = LER_LerParametros( "cci" ,
			&verticeOrigem , &verticeDestino , &CondRetEsp ) ;

		if ( numLidos != 3 )
		{
			return TST_CondRetParm ;
		} /* if */

		origem = CHR_CriarCaracter ( verticeOrigem ) ;
		destino = CHR_CriarCaracter ( verticeDestino ) ;

		CondRetObt=GRF_ExisteCaminho ( pGrafo , origem , destino ) ;

		return TST_CompararInt( CondRetEsp , CondRetObt ,
			"Retorno errado ao verificar se existe caminho entre os vertices." );

	} /* fim ativa: Testar Existe Caminho */

	return TST_CondRetNaoConhec;

} /* Fim função: TGRF &Testar Grafo */

/********** Fim do módulo de implementação: TGRF Teste grafo genérico **********/
