/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2021                           **/
/**   <turma> - Prof. Luciano Antonio Digiampietri                  **/
/**                                                                 **/
/**   EP 1 - Lista Ligada de Produtos                               **/
/**                                                                 **/
/**   <Juliana de Faria Duarte Ribeiro>         <12684969>          **/
/**                                                                 **/
/*********************************************************************/
#include "listadeprodutos.h"

PLISTA criarLista(){
  PLISTA res = (PLISTA) malloc(sizeof(LISTADEPRODUTOS));
  int x;
  for (x=0;x<NUMTIPOS;x++){
    res->LISTADELISTAS[x]=(PONT) malloc(sizeof(REGISTRO));
    res->LISTADELISTAS[x]->id=-1;
    res->LISTADELISTAS[x]->quantidade=0;
    res->LISTADELISTAS[x]->valorUnitario=0;
    res->LISTADELISTAS[x]->proxProd=NULL;
  }
  return res;
}


int tamanho(PLISTA l){
  int tam = 0;
  int x;
  PONT atual;
  for (x=0;x<NUMTIPOS;x++){
    atual = l->LISTADELISTAS[x]->proxProd;
    while (atual) {
      atual = atual->proxProd;
      tam++;
    }
  }
  return tam;
}

PONT buscarID(PLISTA l, int id){
  int x;
  PONT atual;
  for (x=0;x<NUMTIPOS;x++){
    atual = l->LISTADELISTAS[x]->proxProd;
    while (atual) {
      if (atual->id == id) return atual;
      atual = atual->proxProd;
    }
  }
  return NULL;
}

PONT buscarIDTipo(PLISTA l, int id, int tipo){
  if (tipo<0 || tipo>=NUMTIPOS) return NULL;
  PONT atual = l->LISTADELISTAS[tipo]->proxProd;
  while (atual) {
    if (atual->id == id) return atual;
    atual = atual->proxProd;
  }
  return NULL;
}

void exibirLog(PLISTA f){
  int numElementos = tamanho(f);
  printf("Log lista [elementos: %i]\n", numElementos);
  int x;
  PONT atual;
  for (x=0;x<NUMTIPOS;x++){
    printf("  #TIPO: %i -> ", x);
    atual = f->LISTADELISTAS[x]->proxProd;
    while (atual){
      printf(" [%i;%i;%i;$%i]", atual->id, atual->quantidade, atual->valorUnitario, atual->quantidade*atual->valorUnitario);
      atual = atual->proxProd;
    }
    printf("\n");
  }
  printf("\n");
}

int consultarValorUnitario(PLISTA l, int id){
  int x;
  PONT atual;
  for (x=0;x<NUMTIPOS;x++){
    atual = l->LISTADELISTAS[x]->proxProd;
    while (atual) {
      if (atual->id == id) return atual->valorUnitario;
      atual = atual->proxProd;
    }
  }
  return 0;
}

/*
//Função auxiliar busca o id e retorna o valor dele
int buscarValorID(PLISTA l, int id){
  int x;
  PONT atual;
  for (x=0;x<NUMTIPOS;x++){
    atual = l->LISTADELISTAS[x]->proxProd;
    while (atual) {
      if (atual->id == id) 
        return atual->id;
      atual = atual->proxProd;
    }
  }
  return -1;
}*/

int consultarValorTotal(PLISTA l, int id)
{
  int x, valorTotal;
  PONT atual;
  for (x=0;x<NUMTIPOS;x++){
    atual = l->LISTADELISTAS[x]->proxProd;
    while (atual) {
      if (atual->id == id)
      {
        valorTotal = atual->valorUnitario * atual->quantidade;
        return valorTotal;
      } 
      atual = atual->proxProd;
    }
  }
  return 0;
}

int consultarQuantidade(PLISTA l, int id)
{
  int x, quantidade;
  PONT atual;
  for (x=0;x<NUMTIPOS;x++){
    atual = l->LISTADELISTAS[x]->proxProd;
    while (atual) {
      if (atual->id == id)
      {
        quantidade = atual->quantidade;
        return quantidade;
      } 
      atual = atual->proxProd;
    }
  }
  return 0;
}

int retornaTipo(PLISTA l, int id)
{
  int x;
  PONT atual;
  for (x=0;x<NUMTIPOS;x++){
    atual = l->LISTADELISTAS[x]->proxProd;
    while (atual) {
      if (atual->id == id)
      {
        return x;
      } 
      atual = atual->proxProd;
    }
  }
  return 0;
}

//busca auxiliar para descobrir o anterior
PONT buscaSequencialExc(PLISTA l, int id, int tipo, int quantidade, int valor, PONT* ant)
{
  int valorTotal;
  valorTotal = quantidade * valor;
  *ant = l->LISTADELISTAS[tipo]; //anterior do elemento atual (ao inicio é null)
  PONT atual = l->LISTADELISTAS[tipo]->proxProd; //começa do primeiro elemento
  while((atual != NULL) && ((atual->quantidade * atual->valorUnitario) < valorTotal))
  {
      *ant = atual;
      atual = atual->proxProd;
  }
  return atual;
  // if((atual != NULL) && (atual->quantidade * atual->valorUnitario == valorTotal))
  //     return atual;

  //return NULL;
}
void ordenar(PLISTA l, int tipo)
{
  PONT i, j, aux;
  PONT fim = NULL;

  if(l->LISTADELISTAS[tipo]->proxProd == NULL)
    return false;
  for(i = l->LISTADELISTAS[tipo]->proxProd; i->proxProd != NULL; i = i->proxProd)
  {
    for(j = l->LISTADELISTAS[tipo]->proxProd; j->proxProd != fim; j = j->proxProd)
    {
      if((j->quantidade * j->valorUnitario) > (j->proxProd->quantidade * j->proxProd->valorUnitario))
      {
        aux = j;
        j = j->proxProd;
        j->proxProd = aux;
      }
    }
    fim = j;
  }
}


bool inserirNovoProduto(PLISTA l, int id, int tipo, int quantidade, int valor)
{
  if(buscarID(l, id) != NULL) //se ja existe
    return false;
  if(id < 0 || tipo < 0 || tipo > NUMTIPOS-1 || quantidade <= 0 || valor <= 0)
     return false;
  
  PONT novo, ant;
  novo = (PONT) malloc(sizeof(REGISTRO));
  
  novo->id = id;
  novo->quantidade = quantidade;
  novo->valorUnitario = valor;

  if(l->LISTADELISTAS[tipo]->proxProd == NULL) //se for o único elemento da lista
  {
    novo->proxProd = l->LISTADELISTAS[tipo]->proxProd;
    l->LISTADELISTAS[tipo]->proxProd = novo;
  }
  else //se já existir produto
  {
    buscaSequencialExc(l, id, tipo, quantidade, valor, &ant);

    novo->proxProd = ant->proxProd;
    ant->proxProd = novo;
  }

  return true;
}

bool removerItensDeUmProduto(PLISTA l, int id, int quantidade)
{
  PONT remover, ant, aux;

  remover = buscarID(l, id);

  if(remover == NULL) //se não existe
    return false;
  if(quantidade <= 0 || quantidade > consultarQuantidade(l, id))
    return false;

  int tipo;

  tipo = retornaTipo(l, id);

  buscaSequencialExc(l, id, tipo, quantidade, remover->valorUnitario, &ant);

  remover->quantidade = remover->quantidade - quantidade;

  if(remover->quantidade == 0) //será apagado
  {
      if(ant == l->LISTADELISTAS[tipo]) //se o anterior for o nó cabeça
        l->LISTADELISTAS[tipo]->proxProd = remover->proxProd;
      else //se o anterior for outro produto
        ant->proxProd = remover->proxProd;
    free(remover);
  }
  else 
  {
    int valorTotalAtual, valorTotalAnt;
    valorTotalAtual = remover->quantidade * remover->valorUnitario;
    valorTotalAnt = ant->quantidade * ant->valorUnitario;
    if(remover->quantidade * remover->valorUnitario < ant->quantidade * ant->valorUnitario)
    {
     //troca de poisção (só deus sabe como)
    }
  }
  return true;
}


bool atualizarValorDoProduto(PLISTA l, int id, int valor){

  /* COMPLETAR */

  return false;
}


int main()
{
  PLISTA f = criarLista();
  // int id;
  // int tipo;
  // int quantidade;
  // int valor;
   int valortotal = 0;
   int tipo = -1;
  // bool res;
  
  if(inserirNovoProduto(f, 0, 1, 10, 50) == true)
    printf("true\n");
  else
    printf("false\n");

 if(inserirNovoProduto(f, 1, 1, 10, 60) == true)
    printf("true\n");
  else
    printf("false\n");

  if(inserirNovoProduto(f, 2, 1, 10, 40) == true)
    printf("true\n");
  else
    printf("false\n");

  if(inserirNovoProduto(f, 2, 1, 10, 40) == true)
    printf("true\n");
  else
    printf("false\n");

  if(inserirNovoProduto(f, 3, 1, 20, 40) == true)
    printf("true\n");
  else
    printf("false\n");

  valortotal = consultarValorTotal(f, 3);
  printf("%i\n", valortotal);

  tipo = retornaTipo(f, 3);
  printf("%i\n", tipo);




  PONT end = f->LISTADELISTAS[1]->proxProd; //começando do primeiro endereço válido
    printf("Lista: \" ");
    while(end != NULL) //enquanto o endereço for diferente de null
    {
        printf("%i ", end->id); //imprime a chave atual
        printf("%i ", end->quantidade);
        printf("%i ", end->valorUnitario);
        end = end->proxProd; //o endereço recebe o próximo
    }
    printf("\"\n");

  if(removerItensDeUmProduto(f, 0, 9) == true)
    printf("true\n");
  else
    printf("false\n");

  end = f->LISTADELISTAS[1]->proxProd; //começando do primeiro endereço válido
    printf("Lista: \" ");
    while(end != NULL) //enquanto o endereço for diferente de null
    {
        printf("%i ", end->id); //imprime a chave atual
        printf("%i ", end->quantidade);
        printf("%i ", end->valorUnitario);
        end = end->proxProd; //o endereço recebe o próximo
    }
    printf("\"\n");

  return 0;
}
