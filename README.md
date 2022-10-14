# Técnicas de Programação para Sistemas Embarcados II

## O problema do SSH

### Error: "Connection reset by {ip_da_placa} port {número_da_sua_porta}"

## Buscando a solução
#### Eu estava com esse problema também quando decidir refazer o processo do *buildroot*. Fiquei procurando soluções na *internet* e não achava nada muito concreto, também recorri ao próprio manual *buildroot* e achei o seguinte ao procurar por SSH:

![SSH](ssh_buildroot.png)

#### Aparentemente, nessa configuração, o sshd (server) está atrelado a um pacote chamado *dropbear*. *Dropbear* é um serviço alternativo de SSH de cliente e servidor, [saiba mais](https://matt.ucc.asn.au/dropbear/dropbear.html). Procurei sobre isso no *buildroot* e tinha um pacote para isso.

## Possível solução (funcionou para mim)

#### Resolvi olhar o [repositório](https://git.buildroot.net/buildroot) da ferramenta para procurar por novas versões e o que havia sido atualizado ou consertado. De acordo com o PDF disponibilizado pelo professor, deveriámos usar a versão **2022.08**. Ao olhar o repositório, vejo que foi lançada um nova *tag/branch* chamada 2022.08.1, atualizada 12 dias atrás (momento em que estou digitando isso).

![TAG](tag.png)

#### Então resolvi conferir o *commit* que foi feito para essa atualização. Basta clicar no nome **2022.08.1** e depois clicar em ***commit***, terá o seguinte texto em cor verde. 

![COMMIT](commit.png)

#### Ao ler o texto podemos perceber que vários pacotes foram "*Updated/fixed*" incluindo o *openssh*, ao ver isso resolvi apostar na troca para essa versão e reconfigurar meu *buildroot* baseando-se nela. 

## Então vamos para o passo a passo

### 1. Atualizar a *branch* criada dentro do repositório com a *branch* mais atual.

#### Certfique-se que você está na *branch* que foi criada no começo da prática

```git
git branch
```
#### Vai listar as *branchs* criadas, a *master* e a sua, se a sua estiver com um * então tá tudo OK. Caso não esteja, execute:
```git
git checkout [nome_da_branch]
```

#### Após isso, vamos atualizar em relação ao repositório remoto, execute:
```git
git pull origin 2022.08.1
```

#### Este comando irá atualizar sua *branch* com a modificações de 2022.08.1

### 2. Reconfigurar o *buildroot*

#### No meu caso eu executei
```bash
make clean
```
#### e

```bash
make distclean
```