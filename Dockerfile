FROM gcc:4.9
COPY . /src/
WORKDIR /src/

# COMMANDE : docker exec -it info1002-container sh