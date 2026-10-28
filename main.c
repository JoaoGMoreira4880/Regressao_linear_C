#include <stdio.h>

int main(){
    int quantidade [2];
    float peso = 10.0;
    float previsao = 0; 
    float erro = 0;
    float valor_real [2];
    int i = 0;
    float soma_erros = 0.0;
    float soma_erros_2 = 0.0;
    float media = 0.0;
    float soma_produtos = 0.0;
    float gradiente = 0.0;
    float taxa_aprendizado = 0.1;
    float b = 0.0;
    float soma_erros_b = 0.0;
    float gradiente_b = 0.0;

    for (i = 0; i < 2; i++)
    {
        printf("Digite a quantidade: \n");
        scanf("%d", &quantidade[i]);
        printf("Digite o valor real: \n");
        scanf("%f", &valor_real[i]);
        previsao = quantidade[i] * peso + b;
        erro = valor_real[i] - previsao;
        soma_erros += (erro * erro);
        soma_produtos += quantidade[i] * erro;
        soma_erros_b += erro;
    }
    media = soma_erros /2;
    gradiente = (-2 * soma_produtos) / 2;
    gradiente_b = (-2 * soma_erros_b) / 2;
    peso = peso - (taxa_aprendizado * gradiente );
    b = b - (taxa_aprendizado * gradiente_b);
    soma_erros = 0;
    for (i = 0; i < 2; i++)
    {
        previsao = quantidade[i] * peso + b;
        erro = valor_real[i] - previsao;
        soma_erros += (erro * erro);
    }
    media = soma_erros /2;
    printf("O peso é igual a: %.2f\n", peso);
    printf("B é igual a: %.2f\n", b);
    printf("A soma dos produtos é igual a: %.2f\n", soma_produtos);
    printf("O gradiente é igual a: %.2f\n", gradiente);
    printf("Gradiente de B: %.2f\n", gradiente_b);
    printf("a MSE é igual a: %.2f\n A soma dos erros é igual a: %.2f\n", media, soma_erros);
return 0;
}
