# Final Project
Repositório com nosso Projeto Final, proposto na disciplina de Programação de Computadores, na linguagem C.

## Objetivo

Desenvolver um jogo, baseado em anagramas, inspirado no site [Racha Cuca](https://rachacuca.com.br/palavras/sopa-de-letras/).

## Descrição

- **Conjunto de letras** - no mínimo 20 letras embaralhadas;
- **Banco de Palavras** possíveis, formadas pelas letras do conjunto - pelo menos 30 palavras;

## Funcionamento

INÍCIO: 
- uma palavra é digitada:
1. Verificar se a palavra digitada pertence ao Banco de Palavras:
   - a. Se sim, verificar no Vetor de String: Acertos, se a palavra já foi  digitada:
   
      i. Se sim, ignorá-la e ir para nova leitura de palavra;
      
      ii. Se não, incluí-la em Acertos e ir para nova leitura;
      
   - b. Se não, ignorá-la e ir para nova leitura de palavras.
