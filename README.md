### COMMANDES
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
    $ apk add git make openssl libressl-dev g++
```

### Liens
    https://github.com/CLIUtils/CLI11