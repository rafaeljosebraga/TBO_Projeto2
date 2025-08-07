# TBO_Projeto2

# Projeto 2 - Algoritmos de Busca em Texto

Este projeto contém implementações de dois algoritmos eficientes para busca de padrões em texto:

1. **Aho-Corasick** (pasta `Aho`)
2. **KMP (Knuth-Morris-Pratt)** com variações (pasta `KMP`)
3. KMP Com wildscore

## Estrutura do Projeto

TBO_Projeto2/
├── Aho/
│ ├── EstruturasAuxiliares/ # Bibliotecas do Aho-Corasick
│ │ ├── AhoCorasick.h
│ │ ├── Hash.h
│ │ ├── Map.h
│ │ └── Node.h
│ ├── entrada.txt # Arquivo de entrada padrão
│ └── main.cpp # Programa principal
├── KMP/
│ ├── entrada.txt # Arquivo de entrada padrão
│ ├── mainCaractereCoringa.cpp # KMP com caracteres curinga
│ ├── mainWild.cpp # KMP com wildcards (alternativo)
│ └── KMPsemWildScore/ # KMP padrão (sem curingas)
│ ├── entrada.txt
│ └── main.cpp
└── README.md

# Programas Principais

## Cada `main.cpp` é um programa independente que pode ser compilado separadamente

cd Aho && g++ -O3 -o aho main.cpp  

cd KMP && g++ -O3 -o kmp_curinga mainWild.cpp  

cd KMP/KMPsemWildScore && g++ -O3 -o kmp_simples main.cpp  

./nome_do_executavel  # Lê automaticamente o arquivo `entrada.txt` do diretório  
