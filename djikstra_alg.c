#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int destino, origem, vertices = 0;
int custo, *custos = NULL;

void dijkstra(int vertices,int origem,int destino,int *custos);
void busca_no_grafo(void);
void criar_grafo(void);


int main() {
 int flag = -1;
 
 do {  
 printf("Menu:\n");
 printf("1 - Adicionar um Grafo\n");
 printf("2 - Aplicar algoritmo Djikstra\n");
 printf("0 - Sair do programa\n");
 scanf("%d", &flag);
   if(flag == 1) {
       criar_grafo();
   }
   else if( flag == 2){   
       if (vertices > 0) {
         busca_no_grafo();
       }
   }
 } while (flag != 0);
 return 0;
}

void dijkstra(int vertices,int origem,int destino,int *custos){
 int i, v, cont = 0;
 int *ant, *aux;
 int *vert_aux; 
 double min;
 double peso[vertices];

 ant = (int*) calloc (vertices, sizeof(int *));  
 aux = (int*) calloc (vertices, sizeof(int *));
 vert_aux = (int *) calloc (vertices, sizeof(int *));

 for (i = 0; i < vertices; i++) {
   if (custos[(origem - 1) * vertices + i] !=- 1) { //testa se existe valor processável
       ant[i] = origem - 1;
       peso[i] = custos[(origem-1)*vertices+i];
   }
   else {
       ant[i]= -1;  //indicadores de valores não processáveis
       peso[i] = HUGE_VAL; // D(V) = infinito
   }
   vert_aux[i]=0;
 }
 vert_aux[origem-1] = 1;
 peso[origem-1] = 0;

 do {
	 printf("oi\n");
   min = HUGE_VAL;
   for (i=0;i<vertices;i++){
       if (!vert_aux[i]){
           if (peso[i]>=0 && peso[i]<min) { //verifica os pesos das arestas
               min=peso[i];
			   v=i;
           }
       }
   }  

   if (min != HUGE_VAL && v != destino - 1) {
       vert_aux[v] = 1;
       for (i = 0; i < vertices; i++){
           if (!vert_aux[i]) {
               if (custos[v*vertices+i] != -1 && peso[v] + custos[v*vertices+i] < peso[i]) { //verifica se é o menor caminho
                   peso[i] = peso[v] + custos[v*vertices+i];
                   ant[i] =v;
               }
           }
       }
   }

 }while (v != destino - 1 && min != HUGE_VAL);

 printf("\tDe %d para %d: \t", origem, destino);
 if (min == HUGE_VAL) {
   printf("Erro: vertice indefinido\n");
   printf("\tCusto: \t- \n");
 }

 else {

   i = destino;
   i = ant[i-1];
   while (i != -1) {
       aux[cont] = i+1;
       cont++;
       i = ant[i];
   }

   for (i = cont; i > 0 ; i--) {
       printf("%d -> ", aux[i-1]);
   }

   printf("%d", destino);
   printf("\n\tCusto:  %d\n",(int) peso[destino-1]);

 }
}

void criar_grafo(void){

 do {
   printf("\nInforme o numero de vertices (até 20): ");
   scanf("%d", &vertices);
 } while (vertices > 20 );

 custos = (int *) malloc(sizeof(int)*vertices*vertices);

 for (int i = 0; i <= vertices * vertices; i++){
   custos[i] = -1;
   }
 do {
   printf("Entre com as Arestas:\n");
   do {
       printf("digite a origem (de 1 ate %d) ou 100 para sair: ", vertices);
       scanf("%d", &origem);
   } while (origem < 0);
   if (origem != 100) {
       do {
           printf("Digite o destino (diferente de %d): ", vertices);
           scanf("%d", &destino);
       } while (destino < 1 || destino > vertices || destino == origem);
       do {
           printf("Digite o custo do vertice %d para o vertice %d: ",origem, destino);
           scanf("%d",&custo);
       } while (custo < 0);
       custos[(origem-1) * vertices + destino - 1] = custo; //guarda o valor dos custos em uma posição do vetor relacionando os vertices origem e destino
   }
 } while (origem != 100);
}

void busca_no_grafo(void){
 int start, end;
 printf("Insira o nodo origem: \n");
 scanf("%d", &start);
 printf("Insira o nodo destino: \n");
 scanf("%d", &end);
 printf("O algoritmo encontrou este menor caminho: \n");
     dijkstra(vertices, start,end, custos);
   printf("\n");
}
