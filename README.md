# Trabalho - árvores AVL, rubro-negra e B

## Disciplina: Projeto de Arquivos - TADS - UDESC

### Integrantes: Filipe Moisés, Gabriel Leite, Vinícius Bernardes

O objetivo deste trabalho consiste em analisar a complexidade algorítmica das operações de adição e remoção de nós (considerando o balanceamento) em árvores AVL, rubro-negra e B. No caso da árvore B, devem ser consideradas o parâmetro de ordem da árvore igual a 1, 5 e 10. A análise deve ser realizada considerando a geração de um conjunto de dados (chaves) com tamanho variando entre 1 e 10000. As chaves devem ser geradas reproduzindo o caso médio utilizando chaves aleatórias. Para geração das chaves aleatórias, sugere-se o uso da função rand em C considerando uma quantidade de amostra de 10 conjuntos para validade estatística e calculando a média do resultado dos 10 conjuntos.

O resultado final do experimento deve ser apresentado em um relatório contendo dois gráficos de linha (um para a operação de adição e outro para a operação de remoção), onde o eixo X representa o tamanho dos conjuntos de dados (1 a 10000) e o eixo Y representa o esforço computacional das operações considerando eventuais balanceamentos. Cada gráfico deve apresentar 5 linhas, as quais representam as respectivas operações para cada estrutura de dados avaliada (árvore AVL, rubro-negra e as três variações da árvore B). O relatório também deve conter uma discussão final sobre os resultados obtidos. Além do relatório, os códigos-fonte utilizados nos experimentos devem ser entregues também.