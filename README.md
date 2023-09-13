# idj2023-2

Repositório criado para abrigar os códigos da disciplina Introdução ao Desenvolvimento de jogos da UnB.

# Requisitos

1. lSDL2
2. lSDL2_mixer
3. lSDL2_image
4. (Opcional) Make

# Como Rodar o Jogo do Pinguim

Obs.: Os métodos abaixo foram testados no Linux Ubuntu 22.04 e MacOS Sierra, porém devem funcionar em máquinas Windows

## Alternativa 1 (melhor)

(Make necessário)

Neste diretório (onde se encontra o arquivo Makefile), rode o comando

```bash
$ make run
```

Esse comando irá compilar os arquivos necessários e executá-los.

## ALternativa 2

(Make necessário)

No diretório onde encontra-se o Makefile, rode o comando

```bash
$ make
```

Ele gerará um executável `game.o` (Linux ou Mac) ou `game.exe` (Windows) na pasta `jogo_do_pinguim/bin`. Execute-o como preferir.

## Alternativa 3

TODO add new commands

Compile os arquivos pelo terminal

No Linux,

```bash
$ cd src
```

```bash
$ g++ Main.cpp Game.cpp State.cpp Sprite.cpp Music.cpp -w -lSDL2 -lSDL2_mixer -lSDL2_image -o game
```

Depois apenas execute o arquivo `game` gerado.

## Alternativa 4 ( O famoso "Confia!")

Há um arquivo `game.o` já compilado na pasta `jogo_do_pinguim/bin`. Se preferir, apenas execute-o.

## Clean

Para limpar os executáveis criados, basta rodar o comando

```bash
$ make clean
```

