#ifndef GRANDS_ENTIERS
#define GRANDS_ENTIERS

#include <string>
#include <vector>

class GrandEntier {
private:
  std::vector<bool> m_bits;
public:
  // Construit un GrandEntier a partir d'un entier non signe
  GrandEntier(unsigned int petit_entier = 0);
  // Construit un Grandentier a partir d'un vecteur de bits
  GrandEntier(const std::vector<bool>& bits);
  // Constructeur de copie
  GrandEntier(const GrandEntier& grand_entier);

  std::string toString() const;	// Pour deboguer

  // Multiplie le grand entier par 2^shift. Fonctionne avec shift positif ou negatif
  void shiftBits(int shift);
  
  // Operateurs arithmetiques
  bool operator==(const GrandEntier& grand_entier) const;
  GrandEntier operator+(const GrandEntier& grand_entier) const;
  GrandEntier operator-(const GrandEntier& grand_entier) const;
  GrandEntier operator*(const GrandEntier& grand_entier) const;
};

#endif
