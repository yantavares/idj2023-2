# Requisitos

- lSDL2
- lSDL2_mixer
- lSDL2_image

# COMO RODAR O TRABALHO 1

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

Ele gerará um executável `game.o` (Linux ou Mac) ou `game.exe` na pasta `src`. Execute-o como preferir.

## Alternativa 3

Compile os arquivos direto pelo terminal na pasta `trab1/src`.

No Linux,

```bash
$ cd src
```

```bash
$ g++ Main.cpp Game.cpp State.cpp Sprite.cpp Music.cpp -w -lSDL2 -lSDL2_mixer -lSDL2_image -o game
```

Depois apenas execute o arquivo `game` gerado.
