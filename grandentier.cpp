#include "grandentier.hpp"

#include <algorithm>
#include <assert.h>
#include <iostream>

// Construit un GrandEntier a partir d'un entier non signe
// Theta(1) puisque la taille en bits de petier_entier est bornee par une constante
GrandEntier::GrandEntier(unsigned int petit_entier) {
  while (petit_entier != 0) {
    m_bits.push_back(petit_entier & 1);
    petit_entier = petit_entier >> 1;
  }
  assert(m_bits.empty() || m_bits.back());	// Le bit le plus fort est toujours allume
}
  
// Construit un Grandentier a partir d'un vecteur de bits
// Theta(bits.size())
GrandEntier::GrandEntier(const std::vector<bool>& bits)
  : m_bits(bits)
{
  // Suppression des zeros aux positions les plus hautes. Ex: 00110 -> 110
  unsigned int taille = m_bits.size();
  while (taille > 0 && !m_bits[taille - 1]) {
    taille--;
  }
  m_bits.resize(taille);
  assert(m_bits.empty() || m_bits.back());	// Le bit le plus fort est toujours allume
}

// Constructeur de copie
// Theta(n) ou n est le nombre de bits
GrandEntier::GrandEntier(const GrandEntier& grand_entier)
  :m_bits(grand_entier.m_bits)
{
  assert(m_bits.empty() || m_bits.back());	// Le bit le plus fort est toujours allume
}

// Multiplie le grand dentier par 2^shift. Fonctionne avec shift positif ou negatif
// Pire cas: Theta(n + shift) ou n est le nombre de bits et shift > 0
// Meilleur cas: Theta(1) lorsque shift = 0
void GrandEntier::shiftBits(int shift) {
  if (shift > 0) {
    if (!m_bits.empty()) {
      m_bits.insert(m_bits.begin(), shift, 0);
    }
  } else if (-shift >= m_bits.size()) {
    m_bits.clear();
  } else if (shift != 0) {
    m_bits.erase(m_bits.begin(), m_bits.begin() - shift);
  }
  assert(m_bits.empty() || m_bits.back());	// Le bit le plus fort est toujours allume
}

// Retourne une representation binaire du nombre facile a afficher
// Theta(n) ou n est le nombre de bits
std::string GrandEntier::toString() const {
  std::string resultat(m_bits.size(), 0);
  for (unsigned int i = 0; i < m_bits.size(); i++) {
    resultat[i] = (m_bits[m_bits.size() - i - 1] ? '1' : '0');
  }
  
  return resultat;
}

// Meilleur cas: Theta(1) lorsque les deux entiers n'ont pas le même nombre de bits
// Pire cas: Theta(n)     lorsque les deux entiers ont n bits et sont egaux
bool GrandEntier::operator==(const GrandEntier& grand_entier) const {
  return m_bits == grand_entier.m_bits;
}

// Temps pour additionner un nombre de n bits avec un nombre de m bits: Theta(n + m)
GrandEntier GrandEntier::operator+(const GrandEntier& grand_entier) const {
  std::vector<bool> somme;
  unsigned int taille = std::max(grand_entier.m_bits.size(), m_bits.size());
  somme.reserve(taille + 1);
  bool retenue = false;
  for (unsigned int i = 0; i < taille; i++) {
    const bool bit_gauche = (i < m_bits.size()) && m_bits[i];
    const bool bit_droite = (i < grand_entier.m_bits.size()) && grand_entier.m_bits[i];
    somme.push_back(retenue ^ bit_gauche ^ bit_droite);
    retenue = (retenue && (bit_gauche || bit_droite)) || (bit_gauche && bit_droite);
  }
  if (retenue) {
    somme.push_back(true);
  }
  return somme;
}

// Temps pour soustraire un nombre de n bits avec un nombre de m bits: Theta(n + m)
GrandEntier GrandEntier::operator-(const GrandEntier& grand_entier) const {
  assert(m_bits.size() >= grand_entier.m_bits.size());
  
  std::vector<bool> difference;
  unsigned int taille = std::max(grand_entier.m_bits.size(), m_bits.size());
  difference.reserve(taille);
  bool emprun = false;
  for (unsigned int i = 0; i < taille; i++) {
    const bool bit_gauche = (i < m_bits.size()) && m_bits[i];
    const bool bit_droite = (i < grand_entier.m_bits.size()) && grand_entier.m_bits[i];
    difference.push_back(bit_gauche ^ emprun ^ bit_droite);
    emprun = (emprun && bit_droite) || ((emprun || bit_droite) && !bit_gauche);
  }
  return difference;
}
