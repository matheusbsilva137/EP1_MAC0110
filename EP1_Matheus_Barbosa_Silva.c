/****************************************************************
    Nome: Matheus Barbosa Silva
    NUSP: 11221741

    Fonte e comentarios: a biblioteca math.h foi inserida de modo
    a implementar as funcionalidades de escolha de jogada aleatorias
    do computador. Para calcular as posições das jogadas 'S', 'O'
	e ' ', utilizou-se o código da tabela transferido para a base 3.
****************************************************************/

#include <stdio.h>
#include <math.h>

int rand();
int inserirJogada(int lin, int col, int jogada, int cod_tab);
int valorPosicao(int lin, int col, int cod_tab);
int calcSosDiagonais(int cod_tab);
int calcSosLinhas(int cod_tab);
int calcSosColunas(int cod_tab);
int jogarJokempo(int j2);
char letraPosicao(int lin, int col, int cod_tab);

int main(){
	int cod_tab = 0;
	int quant_sos_ant = 0, quant_sos = 0, pontosj1 = 0, pontosj2 = 0;
	int valid = 0;
	int jog_at = 0, jog = 0, lin = 1, col = 1, jogar = 1, cont = 0;
	
	while(jogar == 1){

		cod_tab = 0;
		
		printf("*** Bem-vindo ao jogo do SOS ***\n");
		while ( jog_at < 1 || jog_at > 3 ){
			printf("Digite 1 caso voce deseje comecar, 2 caso queira que o computador comece ou 3 para decidir por Jokempo: ");
			scanf("%d", &jog_at);
		}
		
		if(jog_at == 3){
			jog_at = jogarJokempo((rand() % 2));
		}

		printf("  %1c  |  %1c  |  %1c  \n", letraPosicao(1, 1, cod_tab), letraPosicao(1, 2, cod_tab), letraPosicao(1, 3, cod_tab));
		printf("-----+-----+-----\n");
		printf("  %1c  |  %1c  |  %1c  \n", letraPosicao(2, 1, cod_tab), letraPosicao(2, 2, cod_tab), letraPosicao(2, 3, cod_tab));
		printf("-----+-----+-----\n");
		printf("  %1c  |  %1c  |  %1c  \n\n", letraPosicao(3, 1, cod_tab), letraPosicao(3, 2, cod_tab), letraPosicao(3, 3, cod_tab));
				
		printf("O tabuleiro tem %d SOS(s)\n", quant_sos);
		printf("Placar: Usuario %d X %d Computador\n", pontosj1, pontosj2);

		cont = 0;

		while(cont < 9){
			if(jog_at == 1){			
				while (valid == 0){
					printf("Digite sua jogada:\n");
					printf("Digite 1 para S, 2 para O: ");
					scanf("%d", &jog);
					printf("Digite a linha: ");
					scanf("%d", &lin);
					printf("Digite a coluna: ");
					scanf("%d", &col);

					if(valorPosicao(lin, col, cod_tab) == 0 && lin <=3 && col <= 3 && jog <= 2 && lin >=1 && col >= 1 && jog >= 1){
						cod_tab = inserirJogada(lin, col, jog, cod_tab);
						valid = 1;	
					}else{
						printf("Movimento invalido!\n");
					}
				}
				
				valid = 0;
			}else{
				while(valid == 0){
					jog = 1 + (rand() % 2);
					lin = 1 + (rand() % 3);
					col = 1 + (rand() % 3);
					
					if(valorPosicao(lin, col, cod_tab) == 0){
						cod_tab = inserirJogada(lin, col, jog, cod_tab);
						valid = 1;	
					}
				}
				
				valid = 0;
			}
			
			printf("\n\n");
			if(jog_at == 1)
				printf("Tabuleiro apos a sua jogada (%d, %d):\n\n", lin, col);
			else
				printf("Tabuleiro apos a minha jogada (%d, %d):\n\n", lin, col);
			
			//Soma a quantidade de linhas identificadas nas linhas, colunas e diagonais
			//para calcular o total de  SOSs
			quant_sos = calcSosColunas(cod_tab) + calcSosLinhas(cod_tab) + calcSosDiagonais(cod_tab);

			if(quant_sos > quant_sos_ant){
				if(jog_at == 1){
					pontosj1 += quant_sos - quant_sos_ant;
					printf("Voce marcou %d ponto(s). Jogue novamente!\n", quant_sos - quant_sos_ant);
				}else{
					pontosj2 += quant_sos - quant_sos_ant;
					printf("Marquei %d ponto(s). Vou jogar novamente!\n", quant_sos - quant_sos_ant);
				}
				quant_sos_ant = quant_sos;
			}else{
				if(jog_at == 1)
					jog_at = 2;
				else
					jog_at = 1;
			}
			
			printf("  %1c  |  %1c  |  %1c  \n", letraPosicao(1, 1, cod_tab), letraPosicao(1, 2, cod_tab), letraPosicao(1, 3, cod_tab));
			printf("-----+-----+-----\n");
			printf("  %1c  |  %1c  |  %1c  \n", letraPosicao(2, 1, cod_tab), letraPosicao(2, 2, cod_tab), letraPosicao(2, 3, cod_tab));
			printf("-----+-----+-----\n");
			printf("  %1c  |  %1c  |  %1c  \n\n", letraPosicao(3, 1, cod_tab), letraPosicao(3, 2, cod_tab), letraPosicao(3, 3, cod_tab));
				
			printf("O tabuleiro tem %d SOS(s)\n", quant_sos);
			printf("Placar: Usuario %d X %d Computador\n", pontosj1, pontosj2);
			cont++;
		}
		
		if(pontosj1 > pontosj2){
			printf("\nVoce venceu. Parabens!");
		}else if(pontosj2 > pontosj1){
			printf("\nEu venci! Tente novamente.");
		}else{
			printf("\nEmpatamos!");
		}
		
		quant_sos = 0; quant_sos_ant = 0; pontosj1 = 0; pontosj2 = 0; jog_at = 0;
		printf("\nQuer uma revanche? (1 - SIM, 0 - NAO): ");
		scanf("%d", &jogar);
	}
	return(0);
}

//adiciona o valor correspondente a jogada ao codigo da tabela
int inserirJogada(int lin, int col, int jogada, int cod_tab){
	int exp, pot3 = 1;

	if( lin == 1){
		exp = col - lin;
	}else if ( lin == 2 ){
		exp = lin + col;
	}else{
		exp = lin + col + 2;
	}
	
	while (exp > 0){
		pot3 *= 3;
		exp--;
	}

	jogada = jogada*pot3;
	cod_tab += jogada;
	return cod_tab;
}

//transforma o valor do cod da tabela em base 3 e identifica o digito da posicao desejada
int valorPosicao(int lin, int col, int cod_tab){
	int a = 8, pot3 = 6561, exp;

	if( lin == 1){
		exp = col - lin;
	}else if ( lin == 2 ){
		exp = lin + col;
	}else{
		exp = lin + col + 2;
	}

	while (a >= 0){
		if( 2 * pot3 <= cod_tab ){
			if( a == exp )
				return 2;
			cod_tab -= 2 * pot3;
		}else if( pot3 <= cod_tab ){
			if( a == exp )
				return 1;
			cod_tab -= pot3;
		} else if( pot3 > cod_tab && a == exp){
			return 0;
		}
		a--;
		pot3 /= 3;
	}
	return 0;
}

//utiliza a funcao valorPosicao para identificar a letra correspondente a cada digito 0, 1 ou 2
char letraPosicao(int lin, int col, int cod_tab){
	if( valorPosicao( lin, col, cod_tab ) == 1 ){
		return 'S';
	}else if( valorPosicao( lin, col, cod_tab ) == 2 ){
		return 'O';
	}else{
		return ' ';
	}
}

//verifica se o codigo da tabela contem os valores correspondentes aos sos completos nas diagonais
int calcSosDiagonais(int cod_tab){
	int quant_sos_d = 0;
	int celCentro = 81 * valorPosicao(2, 2, cod_tab);
	if((valorPosicao(1, 1, cod_tab) + celCentro + valorPosicao(3, 3, cod_tab)*6561 ) == 6724){
		quant_sos_d++;
	}if( valorPosicao(1, 3, cod_tab)*9 + celCentro +  valorPosicao(3, 1, cod_tab)*729 == 900  ) {
		quant_sos_d++;
	}
	return quant_sos_d;
}

//verifica se o codigo da tabela contem os valores correspondentes aos sos completos (mod 784) nas colunas
int calcSosColunas(int cod_tab){
	int quant_sos_c = 0, val_col = 0, i, pot3 = 1;
	for (i=1; i<=3; i++){
		val_col = valorPosicao(1, i, cod_tab) * pot3 + valorPosicao(2, i, cod_tab) * pot3 * 27 + valorPosicao(3, i, cod_tab) * pot3 * 729;
			
		if (val_col % 784 == 0 && val_col != 0){
			quant_sos_c++;
		}
		pot3 = pot3*3;
	}
	return quant_sos_c;
}

//verifica se o codigo da tabela contem os valores correspondentes aos sos completos (mod 16) nas linhas
int calcSosLinhas(int cod_tab){
	int quant_sos_l = 0, val_linha = 0, i, pot3 = 1;
	for (i=1; i<=3; i++){
		val_linha = (valorPosicao(i, 1, cod_tab) * pot3 + ( valorPosicao(i, 2, cod_tab) * pot3 ) * 3 + ( valorPosicao(i , 3, cod_tab) * pot3 ) * 9);
				
		if (val_linha % 16 == 0 && val_linha != 0){
			quant_sos_l++;
		}
		pot3 = pot3 * 27;
	}
	return quant_sos_l;
}

int jogarJokempo( int j2 ){
	int j1;
	while(j1>2 || j1<0){
		printf("Digite sua jogada (0 - pedra, 1 - tesoura, 2 - papel): ");
		scanf("%d", &j1);
		if(j1>2 || j1<0){
			printf("Dados invalidos! Informe um número entre 0 e 2.\n");				
		}
	}

	while(j1 == j2){
		j2 = (rand() % 2);
	}

	if( j2 == 0 ){
		printf("O computador jogou pedra!\n");
	}else if( j2 == 1 ){
		printf("O computador jogou tesoura!\n");
	}else{
		printf("O computador jogou papel!\n");
	}

	if((j1 == 0 && j2==1) || (j1==1 && j2 == 2) || (j1 == 2 && j2 == 0)){
		printf("Você venceu e começa o jogo\n");
		return 1;
	}else{
		printf("O computador venceu e começa o jogo\n");
		return 2;
	}

	printf("\n");
}