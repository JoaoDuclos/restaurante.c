#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
// Foi criado o define meses do ano para testar com uma quantidade menor de meses.
#define meses_do_ano 12
// o quantidades de prato tem a mesma intenção do de cima.
#define quantidade_pratos 10

// O enum tipo da refeição organiza o struct por tipo. Além disso, facilita o entendimento do código, já que olhando para as linhas 106 e 115 o programador já entenderia que se trata do tipo da refeição.
enum tipo_refeicao{
	quentinha,
	quilo
};
// Essa é a estrutura que organiza as refeições.
struct refeicao{
	int numero;
	enum tipo_refeicao tipo;
	int quanti_quentinha;
	float peso;
	float preco_bebida;
	float preco;
	
};
// O struct relatório é chamado 2 vezes no código, na linha 78 como "relatorio_anual" e na linha 89 como "relatorio_mensal". Esse struct tem como função organizar os relatórios.
struct relatorio{
	// float tempo pode ser dia ou mês.
	int tempo;
	float valor;
};
// Essa função transforma o valor de grama para quilos.
float gramas_para_quilos(float gramas){
	return gramas/1000;
}
// Essa função tem como objetivo multiplicar a quantidade de peso e de pratos.
float preco_ref(float peso, float preco){
	return peso * preco;
}
// Esse array ajuda na hora de escreve o mês correto na linha 156.
const char* meses[] = {
	"Janeiro", 
	"Fevereiro", 
	"Março",
	"Abril",
	"Maio",
	"Junho",
	"Julho",
	"Agosto",
	"Setembro",
	"Outubro",
	"Novembro",
	"Dezembro"
};
// Esse array tem a função ser chamado na linha 86 para identificar a quantidade de dias que existe no respectivo mês.
const int dias_mes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
// Essa função ordena os valores.
void ordenar_relatorios(struct relatorio relatorio_anual[], int tamanho){
    int i, j, temp_mes;
    float temp;
    for(i = 0; i < tamanho; i++){
        for(j = i + 1; j < tamanho; j++){
            if(relatorio_anual[j].valor > relatorio_anual[i].valor){
                temp = relatorio_anual[i].valor;
                relatorio_anual[i].valor = relatorio_anual[j].valor;
                relatorio_anual[j].valor = temp;
                
                temp_mes = relatorio_anual[i].tempo;
                relatorio_anual[i].tempo = relatorio_anual[j].tempo;
                relatorio_anual[j].tempo = temp_mes;
            }            
        }
    }
}
int main() {
	// setlocale para poder usar acentuação
	setlocale(LC_ALL, "Portuguese");
	struct refeicao pratos[quantidade_pratos];
	struct relatorio relatorio_anual[meses_do_ano];
	float peso, preco;
	// i = prato(nem sempre é usado para isso), d = dia, m = mês. 
	int i, d, m, bebida, dias_mes_atual;
	// Valor total ganho no ano.
	float valor_total_ano = 0;
	for(m = 0; m < meses_do_ano; m++){
		// pega a quantidade de dias do mês atual.
		dias_mes_atual = dias_mes[m];
		// põem o número do respectivo mês dentro do struct.
		relatorio_anual[m].tempo = m+1;
		struct relatorio relatorio_mensal[dias_mes_atual];
		printf("Mês: %s (Esse mês tem %d dias)\n", meses[relatorio_anual[m].tempo-1], dias_mes_atual);
		for(d = 0; d < dias_mes_atual; d++){
			// Pega o valor total ganho no dia (Não achamos necessário fazer um relatório para ele).
			float total_dia = 0;
			// põem o dia dentro do struct.
			relatorio_mensal[d].tempo = d+1;
			printf("Dia %d\n", relatorio_mensal[d].tempo);
			for(i = 0; i < quantidade_pratos; i++){
				// põem o número do prato dentro do struct.
				pratos[i].numero = i+1;
				printf("Prato %d\n", pratos[i].numero);
				// Esse while tem como função não bugar o código caso o usuário digite outra opção que não 0 ou 1.
				int on_off = 0;
				while(on_off == 0){
					printf("É quentinha? [0]Sim [1]Não\n");
					scanf("%d", &pratos[i].tipo);
					if(pratos[i].tipo == quilo){
						// para facilitar a utilização do sistema, nós pedimos em gramas e depois convertemos para quilo.
						printf("Qual é o peso do prato (em gramas):\n");
			        	scanf("%f", &peso);
			        	pratos[i].peso = gramas_para_quilos(peso);
						printf("Digite o preco por quilo da refeição:\n");
			        	scanf("%f", &preco);
			        	pratos[i].preco = preco_ref(pratos[i].peso, preco);
			        	on_off = 1;
			    	} else if (pratos[i].tipo == quentinha){
			    		pratos[i].quanti_quentinha = 0;
			    		printf("Digite o numero de quentinhas:\n");
			    		scanf("%d", &pratos[i].quanti_quentinha);
			    		pratos[i].preco = pratos[i].quanti_quentinha * 20.5;
			    		on_off = 1;
					} else {
						printf("Essa opção não existe!\n");
					}
				}
				//Mesma função do while de cima.
				on_off = 0;
				while (on_off == 0){
					printf("Tem bebida? [0]Sim [1]Nao\n");
					scanf("%d", &bebida);
					if (bebida == 0){
						printf("Digite o preço total das bebidas?\n");
						scanf("%f", &pratos[i].preco_bebida);
						on_off = 1;
						pratos[i].preco += pratos[i].preco_bebida;
					} else if (bebida == 1){
						on_off = 1;
					} else {
						printf("Essa opção não existe!\n");
					}
				}
				total_dia += pratos[i].preco;
				printf("O preço dessa refeição foi: %.2f\n\n", pratos[i].preco);
			};
			printf("\nRelatório diário dia %d\n", relatorio_mensal[d].tempo);
			for(i = 0; i < quantidade_pratos; i++){
				if (pratos[i].tipo == quentinha){
					printf("Prato número %d | Quantidade de quentinhas: %d | Valor das bebidas: R$%.2f | Valor: R$%.2f\n", pratos[i].numero, pratos[i].quanti_quentinha, pratos[i].preco_bebida, pratos[i].preco);
				} else if (pratos[i].tipo == quilo){
					printf("Prato número %d | Peso do prato: %.3fKg | Valor das bebidas: R$%.2f | Valor: R$%.2f\n", pratos[i].numero, pratos[i].peso, pratos[i].preco_bebida, pratos[i].preco);
				}
				pratos[i].preco_bebida = 0;
		    }
			printf("O preço total foi: %.2f\n\n", total_dia);
			relatorio_mensal[m].valor += total_dia;
	    }
		printf("O valor total ganho no mês de %s foi de: %.2f\n\n", meses[relatorio_anual[m].tempo-1], relatorio_mensal[m].valor);
		valor_total_ano += relatorio_mensal[m].valor;
		relatorio_anual[m].valor = 0;
		relatorio_anual[m].valor = relatorio_mensal[m].valor;
	}
	ordenar_relatorios(relatorio_anual, meses_do_ano);
	for(i = 0; i < meses_do_ano; i++)
		printf("Mês: %s | Valor %R$%.2f\n", meses[relatorio_anual[i].tempo-1], relatorio_anual[i].valor);
	printf("O valor total ganho nesse ano foi de: %.2f\n\n", valor_total_ano);
	return 0;
}
