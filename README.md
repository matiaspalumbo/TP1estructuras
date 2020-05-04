void* gdclist_leer(GList lista, int pos) { //BORRAAAAAR
  // Función que dada una lista y una posición, lee el dato de la lista en la posición indicada.
  assert(0 <= pos && pos < gdclist_longitud(lista)); // Verifico que la posición sea valida.
  GNodo *temp = lista; // Defino un nodo para recorrer la lista.
  for (int i = 0; i != pos; i++) temp = temp->sig; 
  // Ahora 'temp' apunta al nodo en la posicion pos.
  return temp->dato; // Retorno el dato de ese nodo.
}# TP1estructuras

Comando para ejecutar programa1: 
./programa1 nombres1.txt paises.txt personas.txt 20000

Comando para ejecutar programa2:
./programa2 personas.txt





/* Compara los nombres de dos personas alfabéticamente. Si hay una letra Ñ presente en un nombre,
al almacenarla en el string la memoria ocupada por el char 'Ñ' desborda la provista por el char 
destinado a su almacenamiento, por lo que aparece un número negativo al acceder a ese caracter, y además, 
ocupa dos char en el string, ambos negativos. Por esta razón (y por el hecho de que esto sucede sólo con ese caracter),
en convertir_letra se asume que si el código del char a convertir es negativo se trata de una Ñ. Para evitar conflictos
con los dos espacios de char ocupados por cada letra Ñ, si el char anterior al char que se compara es negativo, se omite.*/
int comp_nombres(void *persona1, void *persona2) {
  char *s1 = ((Persona*)persona1)->nombre, *s2 = ((Persona*)persona2)->nombre; // Strings a comparar.
  int val = 0, prevChar1 = 0, prevChar2 = 0;
  int char1, char2; // Variables utilizadas en la comparación.
  int i = 0, j = 0; // índices de s1 y s2, respectivamente.
  // int len1 = strlen(s1), len2 = strlen(s2);
  while (s1[i] != '\0' && s2[j] != '\0' && val == 0) { // El bucle itera hasta que los strings dejen de ser iguales o alguno termine.
    // if (prevChar1 < 0) {
    //   prevChar1 = 1;
    //   i++;
    // }
    // else if (prevChar2 < 0) {
    //   prevChar2 = 1;
    //   j++;
    // }
    // else {
      char1 = convertir_letra(s1[i]);
      char2 = convertir_letra(s2[j]);
      if (char1 < char2) val = -1;
      else if (char1 > char2) val = 1;
      else val = 0;
      // prevChar1 = s1[i];
      // prevChar2 = s2[j];
      if (char1 < 0 && s1[i+1] != '\0')
        i = i + 2;
      else i++;
      if (char2 < 0 && s2[j+1] != '\0')
        j = j + 2;
      else j++;
    // }
  }
  return val;
}



// Dada una lista y una función visitante, recorre la lista y aplica visit a cada nodo.
void gdclist_recorrer(GList lista, FuncionVisitante visit); // BORRAR

// BORRAR
void gdclist_recorrer(GList lista, FuncionVisitante visit) {
  GNodo *nodo = lista; // Defino un nodo para recorrer la lista.
  for (; nodo->sig != lista; nodo = nodo->sig) 
    visit(nodo->dato); // Llamo la función visitante con cada nodo de la lista.
  visit(nodo->dato); 
}


// Lee el dato en la posición pos de una lista.
void *gdclist_leer(GList lista, int pos); // BORRAR

void* gdclist_leer(GList lista, int pos) { //BORRAAAAAR
  // Función que dada una lista y una posición, lee el dato de la lista en la posición indicada.
  assert(0 <= pos && pos < gdclist_longitud(lista)); // Verifico que la posición sea valida.
  GNodo *temp = lista; // Defino un nodo para recorrer la lista.
  for (int i = 0; i != pos; i++) temp = temp->sig; 
  // Ahora 'temp' apunta al nodo en la posicion pos.
  return temp->dato; // Retorno el dato de ese nodo.
}


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
