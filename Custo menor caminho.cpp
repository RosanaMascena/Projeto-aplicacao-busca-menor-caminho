//Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Variaveis
int destino, origem, vertices = 0;
float custo, customediogasolina, *custos = NULL;

//Prototipacao
void dijkstra(int vertices,int origem,float destino,float *custos);
void menu_mostrar(void);
void grafo_procurar(void);
void grafo_gasolina(void);
void grafo_criar(void);

//Funcao principal
int main(int argc, char **argv) {
 int opt = -1;
 //Laco principal do menu
 do {
 //Desenha o menu na tela
 menu_mostrar();
 scanf("%d", &opt);
 switch (opt) {
 case 1:
 //cria um novo grafo
 grafo_criar();
 break;
 case 2:
 //procura os caminhos
 if (vertices > 0) {
 grafo_procurar();
 }
 break;
 }
 } while (opt != 0);
 printf("\nAlgoritmo de Dijkstra finalizado...\n\n");
 system("pause");
 return 0;
}

//Implementacao do algoritmo de Dijkstra
void dijkstra(int vertices,int origem,float destino,float *custos)
{
 int i, v, cont = 0;
 int *ant, *tmp;
 int *z; /* vertices para os quais se conhece o caminho minimo */
 double min;
 double dist[vertices]; /* vetor com os custos dos caminhos */
 /* aloca as linhas da matriz */
 ant = (int*) calloc (vertices, sizeof(int *));
 if (ant == NULL) {
 system("color fc");
 printf ("** Erro: Memoria Insuficiente **");
 exit(-1);
 }
 tmp = (int*) calloc (vertices, sizeof(int *));
 if (tmp == NULL) {
   system("color fc");
 printf ("** Erro: Memoria Insuficiente **");
 exit(-1);
 }
 z = (int *) calloc (vertices, sizeof(int *));
 if (z == NULL) {
 system("color fc");
 printf ("** Erro: Memoria Insuficiente **");
 exit(-1);
 }
 for (i = 0; i < vertices; i++) {
 if (custos[(origem - 1) * vertices + i] !=- 1) {
 ant[i] = origem - 1;
 dist[i] = custos[(origem-1)*vertices+i];
 }
 else {
 ant[i]= -1;
 dist[i] = HUGE_VAL;
 }
 z[i]=0;
 }
 z[origem-1] = 1;
 dist[origem-1] = 0;
 /* Laco principal */
 do {
 /* Encontrando o vertice que deve entrar em z */
 min = HUGE_VAL;
 for (i=0;i<vertices;i++){
 if (!z[i]){
 if (dist[i]>=0 && dist[i]<min) {
 min=dist[i];v=i;
 }
 }
 }
 /* Calculando as distancias dos novos vizinhos de z */
 if (min != HUGE_VAL && v != destino - 1) {
 z[v] = 1;
 for (i = 0; i < vertices; i++){
 if (!z[i]) {
 if (custos[v*vertices+i] != -1 && dist[v]
 + custos[v*vertices+i] < dist[i]) {
 dist[i] = dist[v] + custos[v*vertices+i];
 ant[i] =v;
    }
 }
 }
 }
 } while (v != destino - 1 && min != HUGE_VAL);
 /* Mostra o Resultado da busca */
 printf("\tDe %d para %g: \t", origem, destino);
 if (min == HUGE_VAL) {
 printf("Nao Existe\n");
 printf("\tCusto: \t- \n");
 }
 else {
 i = destino;
 i = ant[i-1];
 while (i != -1) {
 tmp[cont] = i+1;
 cont++;
 i = ant[i];
 }
 for (i = cont; i > 0 ; i--) {
 printf("%d -> ", tmp[i-1]);
 }
 printf("%g", destino);
   int a = destino;
 printf("\n\tCusto: %g\n",(float) dist[(int)a -1]);
 }
}
void grafo_criar(void){
 do {
 printf("\nInforme o numero de pontos do grafo (no minimo 5): ");
 scanf("%d", &vertices);
 } while (vertices < 5 );
 if (!custos) {
 free(custos);
 }
 printf("\nInforme o custo medio da gasolina: ");
 scanf("%g", &customediogasolina);
 custos = (float *) malloc(sizeof(float)*vertices*vertices);
 //Se o compilador falhou em alocar espaco na memoria
 if (custos == NULL) {
 system("color fc");
 printf ("** Erro: Memoria Insuficiente **");
 exit(-1);
 } 
 //Preenchendo a matriz com -1
 for (int i = 0; i <= vertices * vertices; i++){
 custos[i] = -1;
 }
 do {
 system("cls");
 printf("Entre com os pontos de conexao:\n");
 do {
 printf("Origem (entre 1 e %d ou '0' para sair): ", vertices);
 scanf("%d", &origem);
 } while (origem < 0 || origem > vertices);
 if (origem) {
 do {
 printf("Destino (entre 1 e %d, menos %d): ", vertices,
origem);
 scanf("%d", &destino);
 } while (destino < 1 || destino > vertices || destino ==
origem);
 do {
 printf("Para o calculo do Custo (positivo) entre %d e %d, insira o digito do seu RA: ",
 origem, destino);
 scanf("%g", &custo);
   custo = custo*customediogasolina;
 } while (custo < 0);
 custos[(origem-1) * vertices + destino - 1] = custo;
 }
 } while (origem);
}
//Busca os menores caminhos entre os vertices
void grafo_procurar(void){
 int i, j;
 system("cls");
 system("color 03");
 printf("Lista dos Menores Caminhos no Grafo Dado: \n");
 for (i = 1; i <= vertices; i++) {
 for (j = 1; j <= vertices; j++) {
 dijkstra(vertices, i,j, custos);
 }
 printf("\n");
 }
 system("pause");
 system("color 07");
}
void menu_mostrar(void){
 system("cls");
 printf("Implementacao do Algoritmo de Dijasktra\n\n MAPA - Caminho de menor custo entre Restaurante e Local de Entrega\n\n");
 printf("Opcoes:\n");
 printf("\t 1 - Adicionar um Grafo + Custo Medio Gasolina\n");
 printf("\t 2 - Procura Os Menores Caminhos no Grafo\n");
 printf("\t 0 - Sair do programa\n");
 printf("? ");
}
