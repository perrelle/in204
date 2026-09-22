Notes de cours complémentaires
==============================

Factorisation de code paramétrée par des types 
----------------------------------------------

Nous avons déjà exploré le principe de réutilisation / factorisation de code
dans le cadre des classes avec la notion de classe dérivée. L'exemple suivant,
contenu dans [min.cpp](exemples/min.cpp) illustre une autre famille de cas
classiques où on souhaiterait pouvoir réutiliser du code.

Considérons cette fonction qui calcule le minimum de deux entiers.

```c++
int min_int(int x, int y) {
  return x < y ? x : y;
}
```

Supposons ensuite que nous ayons besoin d'une fonction similaire sur les
flottants. Nous pouvons écrire exactement la même fonction au type des
paramètres et au type de retour près.

```c++
float min_float(float x, float y) {
  return x < y ? x : y;
}
```

Il n'est pas possible de conserver seulement l'une des deux fonctions. Si on
garde la version entière pour calculer le minimum de flottant,s on perd
les chiffres derrière la virgule.

```c++
  std::cout
    << "min_int(3.14f, 2.72f) = "
    << min_int(3.14f, 2.72f)
    << std::endl;
```

Ce code produit la sortie suivante.

```
min_int(3.14f, 2.72f) = 2
```

Inversement, utiliser la version flottantes avec des nombres entiers risque
de faire perdre les chiffres de moindre importance.

```c++
  std::cout
    << "min_float(1000000042, 2000000000) = "
    << min_float(1000000042, 2000000000)
    << std::endl;
```

Ce code produit la sortie suivante.

```
min_float(1000000042, 2000000000) = 1e+09
```

Le C++ introduit une solution qui permet de fabriquer les deux versions à partir
d'un seul code : les *modèles* ou *templates*. Un modèle est un code paramétré
par des variables et qui peut être instancié autant de fois que nécessaire en
fixant la valeur des variable. Ce qui est nouveau, c'est que ces variables
peuvent être des variables de type.

```c++
template <typename T>
T min(T x, T y) {
  return x < y ? x : y;
}
```

La déclaration d'un modèle commence par le mot clé `template` suivi d'une
liste de paramètres entre chevrons (`<` et `>`). Elle précède une déclaration
d'une fonction, d'un type (en particulier, d'une classe) ou plus rarement
(depuis C++14) d'une variable.  Le mot clé `typename` permet de préciser que le
paramètre `T` représente un type, par exemple `int` ou `float`.

L'appel d'une fonction modèle est le même que l'appel d'une fonction
classique.

```c++
  std::cout
    << "min(3.14f, 2.72f) = "
    << min(3.14f, 2.72f)
    << std::endl;
```

Le compilateur cherche quelle valeur donner aux paramètres du modèle pour
que l'appel puisse avoir du sens. Ici, il va fixer la contrainte `T = float`.
Si on veut forcer la valeur d'un paramètre, on peut les donner explicitement
entre des chevrons. Si on écrit

```c++
min<double>(3.14f, 2.72f)
```

alors le compilateur va utiliser `T = double` malgré des paramètres de type
`float` et générera donc des conversions de `float` vers `double` avant
l'appel.

Complexifions un peu l'exemple pour que le calcul de minimum ne soit pas
entre deux valeurs mais entre toutes les valeurs d'un tableau d'entiers.

```c++
#include <climits>

int min_int_array(int* array, size_t size) {
  int m = INT_MAX;
  for (size_t i = 0 ; i < size ; i++) {
    if (array[i] < m)
      m = array[i];
  }
  return m;
}
```

Le type `size_t` est un type standard du C++ pour décrire la taille des
tableaux. On utilise `INT_MAX` (défini dans `climits`) comme valeur initiale de
`m`. Dès qu'on rencontre une autre valeur dans le tableau, on mettra `m` à jour
avec cette valeur.

Grâce aux modèles, on peut rendre cette fonction plus générique et
la rendre utilisable avec un tableau de n'importe quel type sur lequel `<` a
du sens.

```c++
#include <limits>

template <typename T>
T min(T* array, size_t size) {
  T m = std::numeric_limits<T>::max();
  for (size_t i = 0 ; i < size ; i++) {
    if (array[i] < m)
      m = array[i];
  }
  return m;
}
```

Pour rester générique, on utilise `std::numeric_limits<T>::max()` (défini dans
`limits`) qui est la manière en C++ d'obtenir la valeur maximum possible pour le
type `T`. Pour le moment, acceptons cette expression sans s'y attarder ; elle
aura plus de sens quand nous aborderons les traits.

Les modèles sont souvent utilisés pour la déclaration de classes. Continuons
sur l'exemple précédent. Remarquons qu'il est peu pratique de passer un tableau
en paramètre de fonction, puisqu'il faut systématiquement accompagner le
pointeur sur le début du tableau d'une variable indiquant le nombre de cellules
du tableau. En outre, c'est une source d'erreur possible : qu'arrivera t-il
si le pointeur se retrouver pour une raison ou une autre décorrélé de la taille
? Le paradigme orienté objet résout ce problème en encapsulant dans la même
classe le pointeur, sa taille et les méthodes pour les manipuler. On peut
définir une telle classe de manière générique en écrivant un modèle qui dépend
du type des éléments du tableau.

```c++
template <typename T>
class array {
  size_t allocated_size;
  T *contents;

public:
  explicit array(size_t size) :
    allocated_size(size),
    contents(new T[size])
  {}

  array(array &other) :
    allocated_size(other.allocated_size),
    contents(new T[other.allocated_size])
  {
    for (int i = 0; i < allocated_size; i++) {
      contents[i] = other.contents[i];
    }
  }

  ~array() {
    delete [] contents;
  }

  T get(size_t index) const {
    return contents[index];
  }

  void set(size_t index, T value) {
    contents[index] = value;
  }

  size_t size() {
    return allocated_size;
  }
};
```

Nous pouvons enfin surcharger la fonction `min` pour qu'elle puisse être
utilisée avec cette nouvelle classe.

```c++
template <typename T>
T min(array<T> array) {
  T m = std::numeric_limits<T>::max();
  for (size_t i = 0 ; i < array.size() ; i++) {
    T x = array.get(i);
    if (x < m)
      m = x;
  }
  return m;
}
```

Les paramètres des modèles peuvent aussi être des constantes. Nous aurions pu,
à titre d'exemple, déclarer la taille des tableaux comme un paramètre de
modèle plutôt que comme une propriété de la classe `array`. Ceci aurait eu
l'avantage d'éviter l'allocation dynamique et de réduire le stockage nécessaire
aux instances de la classe. Notez que c'est ce dernier choix qui a été fait dans
la bibliothèque standard pour `std::array`.

```c++
template <typename T, size_t array_size>
class array {
  T contents[array_size];

public:
  array() {}

  T get(size_t index) const {
    return contents[index];
  }

  void set(size_t index, T value) {
    contents[index] = value;
  }

  static size_t size() {
    return array_size;
  }
};
```

La spécialisation des modèles
-----------------------------

Les modèles peuvent être spécialisés pour décrire un comportement particulier
quand un paramètre est affecté à une valeur fixée. Supposons que l'on souhaite
donner un sens à `min<T>` dans le cas `T = bool`. Considérons par exemple que
`false < true`, nous pouvons implémenter `bool min(bool, bool)` comme la
fonction qui retourne `false` dès qu'un de ses arguments est `false`, c'est à
dire exactement comme l'opérateur booléen `ET`. Voici comment nous pourrions
faire.

```c++
template<>
bool min(bool x, bool y) {
  return x && y;
}
```

Il s'agit toujours d'un modèle, mais comme on a fixé `T = bool`, la liste
des arguments du modèle est maintenant vide.

La spécialisation peut être utilisée pour donner une implémentation optimisée
dans certains cas bien choisis. Par exemple `std::vector<bool>` est une
spécialisation de `std::vector<T>` présente dans la plupart des bibliothèque
standard et qui permet de représenter un tableau de booléen en utilisant
un seul bit pour chaque booléen plutôt qu'une cellule de type entier qui
prendrait nécessairement un octet ou plus en mémoire.


Les traits
----------

Les traits sont un concept de programmation dont le but est l'extension d'un
type existant. Ils sont implémentés à travers une classe modèle `trait<T>` qu'on
introduit afin de définir des nouvelles méthodes pour manipuler `T`. Nous avons
déjà rencontré le trait `std::numeric_limits<T>` qui définit des méthodes
permettant d'obtenir des informations sur des types numériques `T`.

Nous pouvons rendre la fonction `min` de l'exemple encore plus générique.
Par exemple, fixons-nous comme objectif de pouvoir travailler aussi sur des
chaînes de caractères, de sorte que la fonction `min` retourne la chaîne
la plus petite pour l'ordre lexicographique (par exemple `min("ac", "ab") == "ab"`).

D'abord, nous définissons le trait `Comparable<T>` qui permet d'étendre
n'importe quel type `T` en lui ajoutant les deux fonctions nécessaire à
l'implémentation de `min` :

- une fonction `max` qui donne une valeur maximale pour le type `T` et
- une fonction `compare` qui permet de dire si un élément de type `T` est
  strictement plus petit qu'un autre.

On donne également une implémentation à ces deux fonctions pour les types
numériques en utilisant respectivement `std::numeric_limits` et l'opérateur `<`.

```c++
template<typename T>
class Comparable
{
public:
  static T max() {
    return std::numeric_limits<T>::max();
  }

  static bool compare(T &x, T &y) {
    return x < y;
  }
};
```


Le mot clé `static` permet de dire que ces méthodes ne s'appliquent pas 
à une instance en particulier. Pour les appeler sans faire référence à une
instance, on utilisera l'opérateur de résolution de portée.

```c++
Comparable<int>::max()
```

On peut aussi définir une spécialisation de `Comparable` pour le type des
chaînes de caractères C, `char const*`.

```c++
template<>
class Comparable<char const*> {
public:
  static char const* max() {
    return "\x7f"; // biggest ascii char
  }

  static bool compare(char const* &x, char const* &y) {
    return strcmp(x, y) < 0;
  }
};
```

Enfin, on peut réécrire la fonction `min` pour qu'elle utilise ce nouveau
trait.

```c++
template <typename T>
T min(array<T> array) {
  T m = Comparable<T>::max();
  for (size_t i = 0 ; i < array.size() ; i++) {
    T x = array.get(i);
    if (Comparable<T>::compare(x,m))
      m = x;
  }
  return m;
}
```

Nous pouvons aussi tester cette nouvelle version.

```c++
  array<char const*> a3(4);
  a3.set(0, "lorem");
  a3.set(1, "ipsum");
  a3.set(2, "dolor");
  a3.set(3, "sit");
  std::cout
    << "min{ \"lorem\", \"ipsum\", \"dolor\", \"sit\" } = "
    << min(a3)
    << std::endl;
```

Ce code produira la sortie suivante.

```
min{ "lorem", "ipsum", "dolor", "sit" } = dolor
```

Pour finir, nous pouvons aller plus loin en faisant en sorte que le trait
utilisé pour manipuler les éléments du tableau soit lui même un paramètre `C`.
Ceci permettra au programmeur appelant la fonction `min` de choisir comment
il souhaite que ses données soient manipulées. Par exemple, il pourra
choisir d'inverser l'ordre pour que `std::min` retourne le plus grand élément
du tableau et non pas le plus petit. On donnera à ce nouveau paramètre une
valeur par défaut afin qu'il ne soit pas nécessaire de préciser ce paramètre
dans les cas les plus courants.

```c++
template <typename T, typename C=Comparable<T>>
T min(array<T> array) {
  T m = C::max();
  for (size_t i = 0 ; i < array.size() ; i++) {
    T x = array.get(i);
    if (C::compare(x,m))
      m = x;
  }
  return m;
}
```

### Conclusion

Les traits permettent d'étendre des types fondamentaux (`int`, `float`, `bool`)
ou des types définis par des classes qu'on ne peut/veut plus modifier avec
des nouvelles fonctionnalités.

Dans la bibliothèque standard, il y a deux traits notables.

- **Les traits de caractères** (`std::char_traits`) permettent de décrire
  comment manipuler les caractères dans les chaînes selon qu'il s'agisse
  de caractères sur un octet `char` ou de caractères sur plusieurs octets
  `wchar_t`. Ils sont utilisés notamment par `std::string` et
  `std::basic_stream` (par exemple `std::cout`).
- **Les traits pour les itérateurs** permettent de décrire de manière générique
  comment parcourir des structures de données comme des tableaux, des listes,
  des arbres, etc.


Espaces de nommage
------------------

Les *espaces de nommages* ou *namespaces* sont un moyen d'organiser le code qui
permet d'éviter les situations de conflit de nommage, c'est à dire deux
variables, deux fonctions ou deux types qui porteraient le même nom et qui
rendraient par conséquent le code confus ou impossible à compiler.

[namespaces.cpp](exemples/namespaces.cpp) donne un exemple d'usage.
