# idj2023-2 [EN]

Repository created to host the code for the Introduction to Game Development course at UnB: A Game engine made in SDL2 and the Penguin Game.

# Requirements

1. SDL2
2. SDL2_mixer
3. SDL2_image
4. (Optional) Make

# How to Run the Penguin Game

Note: The methods below have been tested on Linux Ubuntu 22.04 and MacOS Sierra but should work on Windows machines as well.

## Option 1 (best)

(Make required)

In this directory (where the Makefile is located), run the command

```bash
$ make run
```

This command will compile the necessary files and execute them.

## Option 2

(Make required)

In the directory where the Makefile is located, run the command

```bash
$ make
```

It will generate an executable `game` (Linux or Mac) or `game.exe` (Windows) in the `jogo_do_pinguim/bin` folder. Execute it as you prefer.

## Option 3

Compile the files through the terminal

On Linux,

```bash
$ cd jogo_do_pinguim/bin && ./game 
```

## Option 4 ("Trust me!")

There is an already compiled executable `game` in the `jogo_do_pinguim/bin` folder. If you prefer, just execute it.

## Clean

To clean the created executables, just run the command

```bash
$ make clean
```

---

# idj2023-2 [PT/BR]

Repositório criado para abrigar os códigos da disciplina Introdução ao Desenvolvimento de jogos da UnB: A Game engine feita em SDL2 e o Jogo do Pinguim.

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

Ele gerará um executável `game` (Linux ou Mac) ou `game.exe` (Windows) na pasta `jogo_do_pinguim/bin`. Execute-o como preferir.

## Alternativa 3

Compile os arquivos pelo terminal

No Linux,

```bash
$ cd jogo_do_pinguim/bin && ./game 
```


## Alternativa 4 ( O famoso "Confia!")

Há um arquivo executável `game` já compilado na pasta `jogo_do_pinguim/bin`. Se preferir, apenas execute-o.

## Clean

Para limpar os executáveis criados, basta rodar o comando

```bash
$ make clean
```
