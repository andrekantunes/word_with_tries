# word_with_tries

Algoritmo para contagem de palavras em documentos de texto por meio da estratégia de tries. O arquivo recebe um arquivo do tipo .txt, e insere cada palavra na árvore de tries. Cada letra da palavra ficará lotada em um nó da árvore, e o último nó conterá informações sobre quantas vezes aquela palavra foi repetida no texto. Assim em um ramo as letras ficaram ordenadas na ordem em que aparecerem na palavra.

O arquivo deverá ser compilado a partir do comando MAKE, que irá gerar um arquivo executável com nome indexer. Este poderá ser executado por meio de ./indexer (parametros).

Opções:
--freq N ARQUIVO
    Número de ocorrência das N palavras que mais aparecem em ARQUIVO, em
    ordem decrescente de ocorrência.
    
  --freq-word PALAVRA ARQUIVO
    Exibe o número de ocorrências de PALAVRA em ARQUIVO. 
    
  --search TERMO ARQUIVO [ARQUIVO ...]
    Não implementado.

Alunos: André K. Antunes, Cassiano K. Vidal
