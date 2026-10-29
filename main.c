#include <stdio.h>
#include <math.h>

float prever (float x, float peso, float b){
    float previsao = (x * peso) + b;
return previsao;
}
float calcular_mse(float quantidade[], float valor_real[], int n, float peso, float b){
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
void passo_gradiente(float quantidade[], float valor_real[], int n, float *peso, float *b, float taxa){
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
int ler_dados(const char *arquivo, float quantidade[], float valor_real[], int max){
    FILE *arq = fopen(arquivo, "r");
    if (arq == NULL)
    {
        printf("Problema no arquivo !\n");
        return 0;
    }
    int n = 0;
    while (n < max && fscanf(arq, "%f,%f", &quantidade[n], &valor_real[n]) == 2)
    {
        n++;
    }
    fclose(arq);
    return n;
}
void normalizar (float x[], int n, float *media, float *desvio){
    float soma = 0;
    float variancia = 0;
    for (int i = 0; i < n; i++)
    {
        soma += x[i];
    }
    *media = soma / n;
    for (int i = 0; i < n; i++)
    {
        variancia += (x[i] - *media) * (x[i] - *media);
    }
    *desvio = sqrtf(variancia / n);
    for (int i = 0; i < n; i++)
    {
        x[i] = (x[i] - *media) / *desvio;
    }
    printf("Media: %.3f\n", *media);
    printf("Desvio: %.3f\n", *desvio);
    for (int i = 0; i < n; i++)
    {
        printf("%.3f\n", x[i]);
    }
}
int main(){
    float quantidade [100];
    float valor_real [100];
    float peso = 0.0;
    float taxa_aprendizado = 0.5;
    float b = 0.0;
    float desvio, media;
    int n = ler_dados("dados.csv", quantidade, valor_real, 100);
    if (n == 0) return 0;
    normalizar(quantidade, n, &media, &desvio);
for (int epoca = 0; epoca <= 1000; epoca++)
    {
        if (epoca < 15 || epoca % 100 == 0)
        {
            printf("Época %d | MSE: %.4f | peso: %.3f | b: %.3f\n", epoca, calcular_mse(quantidade, valor_real, n, peso, b), peso, b);
        }
        passo_gradiente(quantidade, valor_real, n, &peso, &b, taxa_aprendizado);
    }
return 0;
}
