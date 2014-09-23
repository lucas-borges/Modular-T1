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

static const char COMANDO_CMD         [ ] = "=comando"     ;

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

	} /* fim ativa: Testar CriarLista */

	return TST_CondRetNaoConhec;

} /* Fim função: TGRF &Testar Grafo */

/********** Fim do módulo de implementação: TGRF Teste grafo genérico **********/
