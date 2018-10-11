#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

struct t_nodo
{
  int valor;
  struct t_nodo *pai;
  struct t_nodo *fillo1;
  struct t_nodo *fillo2;
};

struct t_nodo *nodo_raiz = NULL;

unsigned char e_nodo_raiz(struct t_nodo *nodo)
{
  return (!nodo->pai);
}

struct t_nodo *crear_nodo(int valor)
{
  struct t_nodo *nodo = (struct t_nodo *)malloc(sizeof(struct t_nodo));
  nodo->pai=NULL;
  nodo->fillo1=NULL;
  nodo->fillo2=NULL;
  nodo->valor = valor;

  return nodo;
}

void insertar_nodo_rec(struct t_nodo *p_nodo, int valor)
{
  struct t_nodo *nodo_novo = NULL;
  //struct t_nodo *p_nodo = *p_nodo_ref;

  if (!p_nodo)
  {
    nodo_novo = crear_nodo(valor);
    p_nodo = nodo_raiz = nodo_novo;
  }
  else if (valor < p_nodo->valor)
  {
    if (!p_nodo->fillo1)
    {
      nodo_novo = crear_nodo(valor);
      p_nodo->fillo1=nodo_novo;
      nodo_novo->pai=p_nodo;
    }
    else
    {
      insertar_nodo_rec(p_nodo->fillo1, valor);
    }
  }
  else
  {
    if (!p_nodo->fillo2)
    {
      nodo_novo = crear_nodo(valor);
      p_nodo->fillo2=nodo_novo;
      nodo_novo->pai=p_nodo;
    }
    else
    {
      insertar_nodo_rec(p_nodo->fillo2, valor);
    }
  }
}

void insertar_nodo(int valor)
{
  struct t_nodo *p_nodo = nodo_raiz;
  insertar_nodo_rec(p_nodo, valor);
}

void ler_arbol_rec(struct t_nodo *nodo)
{
  if (!nodo)
  {
    printf("nodo nulo\n");
    return;
  }
  if (nodo->fillo1)
  {
    ler_arbol_rec(nodo->fillo1);
    printf("%d ", nodo->valor);
  }
  else
  {
    printf("%d ", nodo->valor);
  }
  if (nodo->fillo2)
  {
    ler_arbol_rec(nodo->fillo2);
  }
}

void ler_arbol(struct t_nodo *nodo)
{
  ler_arbol_rec(nodo);
  printf("\n");
}

void imprimir_uso(char *nom_prog)
{
  printf("Uso: %s <valor1 valor2 ...>\n", nom_prog);
  exit(1);
}

void liberar_memoria(struct t_nodo *nodo)
{
  if (!nodo) return;
  free(nodo);
  if (nodo->fillo1) liberar_memoria(nodo->fillo1);
  if (nodo->fillo2) liberar_memoria(nodo->fillo2);
}

int main(int argc, char *argv[])
{
  int valor = 0;
  if (argc==1)
  {
    imprimir_uso(argv[0]);
  }
  else
  {
    for (int i = 1; i<argc; i++)
    {
      valor = atoi(argv[i]);
      insertar_nodo(valor);
    }
  }
  ler_arbol(nodo_raiz);
  liberar_memoria(nodo_raiz);
  //printf("%d %d %d\n",nodo_raiz->fillo1->valor, nodo_raiz->valor, nodo_raiz->fillo2->valor);

  return 0;
}

