include ./Makefile.docker-compose.inc

.PHONY: create
create:
	$(DCCREATE) $(c)

.PHONY: build
build:
	$(DCBUILD) $(c)

.PHONY: up
up: build
	$(DCUP) $(c)

.PHONY: down
down:
	@$(DCDOWN) $(c) --volume > /dev/null 2>&1

.PHONY: clean
clean: down
	@yes | docker image prune -a > /dev/null 2>&1

.PHONY: re
re: clean up
