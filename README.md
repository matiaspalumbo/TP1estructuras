# TP1estructuras

Comando para ejecutar programa1: 
./programa1 nombres1.txt paises.txt personas.txt numero_personas

Comando para ejecutar programa2:
./programa2 personas.txt


GList gdclist_intercambiar(GList lista, int posicion1, int posicion2) {
  assert(!gdclist_es_vacia(lista));
  assert(posicion1 >= 0 && posicion1 < gdclist_longitud(lista));
  assert(posicion2 >= 0 && posicion2 < gdclist_longitud(lista));

  GNodo *nodoA, *nodoB;
  if (posicion1 != posicion2) {
    int menor = (posicion1 <= posicion2) ? posicion1 : posicion2;
    int mayor = (posicion1 <= posicion2) ? posicion2 : posicion1;
    GNodo *temp = lista;
    for (int i = 0; i < mayor+1; i++) {
      if (i == menor) nodoA = temp;
      if (i == mayor) nodoB = temp;
      temp = temp->sig;
    } /* ahora nodoA apunta al nodo en la menor posicion y nodoB al nodo en la posicion mayor */

    if (menor == 0 && mayor == gdclist_longitud(lista)-1) {
      nodoA->ant = nodoB->ant;
      nodoB->ant->sig = nodoA;
      GNodo *aux = nodoA->sig;
      nodoA->sig = nodoB;
      nodoB->sig = aux;
      aux->ant = nodoB;
      nodoB->ant = nodoA;
    } else { 
      if (menor == mayor - 1) {
        nodoA->ant->sig = nodoB;
        nodoB->sig->ant = nodoA;
        GNodo* nodoAux = nodoA->ant;
        nodoA->ant = nodoB;
        nodoA->sig = nodoB->sig;
        nodoB->sig = nodoA;
        nodoB->ant = nodoAux;
      } else {
        GNodo *auxAsig = nodoA->sig;
        GNodo *auxAant = nodoA->ant;
        nodoA->sig = nodoB->sig;
        nodoA->ant = nodoB->ant;
        nodoB->sig->ant = nodoA;
        nodoB->ant->sig = nodoA;
        auxAsig->ant = nodoB;
        nodoB->sig = auxAsig;
        nodoB->ant = auxAant;
        auxAant->sig = nodoB;
      }
    }
    if (menor == 0) lista = nodoB;
  }
  return lista;
}
