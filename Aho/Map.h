#ifndef MAP_H
#define MAP_H

#include <cstddef>
#include <stdexcept>
using namespace std;

template <typename T, size_t TAMANHO = 500> class Map {
public:
  Map() {
    for (size_t i = 0; i < TAMANHO; ++i)
      presente[i] = false;
  }

  ~Map() = default;

  void definir(size_t chave, const T &valor) {
    if (chave >= TAMANHO)
      throw out_of_range("Chave fora do limite");
    dados[chave] = valor;
    presente[chave] = true;
  }

  bool contem(size_t chave) const {
    if (chave >= TAMANHO)
      return false;
    return presente[chave];
  }

  T &obter(size_t chave) {
    if (chave >= TAMANHO || !presente[chave])
      throw out_of_range("Chave não encontrada");
    return dados[chave];
  }

private:
  T dados[TAMANHO];
  bool presente[TAMANHO];
};

#endif // MAP_H
