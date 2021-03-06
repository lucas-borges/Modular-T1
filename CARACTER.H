/***************************************************************************
*
*  $MCD M�dulo de defini��o: CHR Estrutura de caracter
*
*  Arquivo gerado:              CARACTER.h
*  Letras identificadoras:      CHR
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  
*  Autores: cs -  Clara Szwarcman
*			gs -  Guilherme Simas
*			lb -  Lucas Borges
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*       1    csgslb 29/ago/2014 in�cio desenvolvimento 
*
*  $ED Descri��o do m�dulo
*    Implementa uma estrutura simples contendo um caracter.
*	 Podem existir n caracteres em opera��o simultaneamente.
*
***************************************************************************/

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para um caracter */

typedef struct CHR_tagCaracter * CHR_tppCaracter ;

/***********************************************************************
*
*  $FC Fun��o: CHR Criar Caracter
*
*  $ED Descri��o da fun��o
*     Cria um caracter.
*
*  $EP Par�metros
*     ValorParm  - Valor do caracter
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para o caracter.
*     Este ponteiro ser� utilizado pelas fun��es que manipulem este caracter.
*
*     Se ocorreu algum erro, por exemplo falta de mem�ria ou dados errados,
*     a fun��o retornar� NULL.
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
***********************************************************************/

	CHR_tppCaracter CHR_CriarCaracter( char ValorParm );

/***********************************************************************
*
*  $FC Fun��o: CHR Destruir Caracter
*
*  $ED Descri��o da fun��o
*     Destr�i o caracter fornecido.
*
*  $EP Par�metros
*     pCaracter  - ponteiro para o caracter a ser destruido
*
***********************************************************************/

	void CHR_DestruirCaracter (  void * pCaracter );

/***********************************************************************
*
*  $FC Fun��o: CHR Obt�m valor do caracter
*
*  $ED Descri��o da fun��o
*     Obtem o valor do caracter fornecido.
*
*  $EP Par�metros
*     pCaracter - ponteiro para o caracter de qual se quer o valor
*
*  $FV Valor retornado
*     Caracter contido na estrutura.
*
***********************************************************************/

	char CHR_ObterValor(  CHR_tppCaracter pCaracter);

/***********************************************************************
*
*  $FC Fun��o: CHR Compara Caracter
*
*  $ED Descri��o da fun��o
*     Compara dois ponteiros para um caracter.
*
*  $EP Par�metros
*     pValorA    - Ponteiro para valor de um caracter
*     pValorB    - Ponteiro para valor de um caracter
*
*  $FV Valor retornado
*     Se valor de ambos caracteres for igual, a fun�ao retorna 0.
*     
*     Caso sejam diferentes, a fun��o retorna 1.
*
***********************************************************************/

	int CHR_ComparaCaracter( void * pCaracterA , void * pCaracterB ) ;

/********** Fim do m�dulo de defini��o: CHR Estrutura de caracter **********/