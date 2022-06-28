DC_FILE = -f ./srcs/docker-compose.yml
DC = docker-compose $(DC_FILE)

DCCREATE= $(DC) create
DCBUILD= $(DC) build
DCUP = $(DC) up
DCDOWN = $(DC) down
DCLOGS = $(DC) logs