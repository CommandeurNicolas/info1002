# TP 1 : Commandeur & Verdant

## Question 1

``./main --md5 test --hash Salut`` -> af4fef1bc0861ca2824db7315f84432700000000000000000000000000000000<br>
``./main --sha1 test --hash Bob``  -> da6645f6e22bf5f75974dc7eed5fcd6160d6b51e000000000000000000000000<br>

## Question 2

***Pas de commandes de tests car sans elle la question 3 ne fonctionne pas et dans notre cas elle est opérationnelle***

## Question 3 

``./main --alphabet ABCDEFGHIJKLMNOPQRSTUVWXYZ --min-size 1 --max-size 3 --value 12345 test --i2c 12345`` --> RFV<br>
``./main --alphabet ABCDEFGHIJKLMNOPQRSTUVWXYZ --min-size 4 --max-size 4 test --i2c 1234`` --> ABVM<br>
``./main --alphabet ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz --min-size 4 --max-size 5 test --i2c 142678997`` --> Salut<br>
``./main test --i2c 142678997`` --> Salut<br>

## Question 4

La complexité en temps  d'une telle table est de O(nlogn), en utilisant la recherche dic<br>hotomique. En espace, elle est de O(n).<br>
La complexité de la recherche exhaustive est de O(n) en temps et O(1) en espace.<br>
La complexité de la recherche avec précalcul est de O(1) et O(n).<br>

## Question 5 :

``./main --alphabet abcdefghijklmnopqrstuvwxyz --min-size 4 --max-size 5 --md5 test --h2i oups 1`` --> 10419507<br>
``./main --alphabet abcdefghijklmnopqrstuvwxyz test --h2i oups 1`` --> 10419507<br>

## Question 7 :

Lors du remplissage de la table, si un hash est déjà présent dans la table (sans le `t`), la fin de la chaine sera la même.<br>
Avec le paramètre `t`, on ajoute *un peu d'aléatoire* dans le calcul de la chaine.<br>

# Note personnelles
***Pour voir toutes les commandes docker que j'ai fait***
```bash
    $ cat C:\Users\comco\AppData\Roaming\Microsoft\Windows\PowerShell\PSReadline\ConsoleHost_history.txt | findstr "docker"
```


***Pour lancer le docker avec un alpine***
```bash
    $ cd C:\Users\comco\Documents\FAC YOU\M2\info1002\TP
    $ docker rm info1002-container
    $ docker run -it --name info1002-container -v ${pwd}:/app frolvlad/alpine-gcc
    $ docker start info1002-container
    $ docker exec -it info1002-container sh
```


***Dans le docker***
```bash
    $ apk add make openssl libressl-dev g++
```




### Liens
    https://github.com/CLIUtils/CLI11
