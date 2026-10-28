#include <stdio.h>

float prever (float x, float peso, float b){
    float previsao = (x * peso) + b;
return previsao;
}
float calcular_mse(int quantidade[], float valor_real[], int n, float peso, float b){
    int i = 0;
    float soma_erro = 0;
    for (i = 0; i < n; i++)
    {
        float chute= prever(quantidade[i], peso, b);
        float erro = valor_real[i] - chute;
        soma_erro = soma_erro + (erro * erro);
    }
return soma_erro/n;
}
void passo_gradiente(int quantidade[], float valor_real[], int n, float *peso, float *b, float taxa){
    float soma_produtos = 0.0;
    float soma_erro_b = 0.0;
    int i = 0;
    for (i = 0; i < n; i++)
    {
        float chute = prever(quantidade[i], *peso, *b);
        float erro = valor_real[i] - chute;
        soma_produtos += quantidade[i] * erro;
        soma_erro_b += erro;
    }
    float gradiente_peso = (-2 * soma_produtos) / n;
    float gradiente_b = (-2 * soma_erro_b) / n;
    *peso = *peso - taxa * gradiente_peso;
    *b = *b - taxa * gradiente_b;
}
int main(){
    int n = 2;
    float valor_real [2] = {2,4};
    int quantidade [2] = {1,2};
    float peso = 0.0;
    float taxa_aprendizado = 0.1;
    float b = 0.0;
    for (int epoca = 0; epoca <= 1000; epoca++)
    {
        if (epoca % 100 == 0)
        {
            printf("Época %d | MSE: %.4f | peso: %.3f | b: %.3f\n", epoca, calcular_mse(quantidade, valor_real, n, peso, b), peso, b);
        }
        passo_gradiente(quantidade, valor_real, n, &peso, &b, taxa_aprendizado);
    }
return 0;
}
