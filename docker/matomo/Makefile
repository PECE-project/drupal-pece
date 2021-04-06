#!make
include matomo.env
export $(shell sed 's/=.*//' matomo.env)

.PHONY: in up run stop clean

in:
	docker ps
	docker-compose exec motomo /bin/bash

run:
	make up

up:
	docker-compose up -d
	docker-compose exec matomo bash -c "chown www-data:www-data /var/www/html -R"

stop:
	docker-compose stop

clean:
	docker-compose down
	sudo rm -rf ./database/matomo

## logs	:	View containers logs.
##		You can optinally pass an argument with the service name to limit logs
##		logs php	: View `php` container logs.
##		logs nginx php	: View `nginx` and `php` containers logs.
logs:
	@docker-compose logs -f $(filter-out $@,$(MAKECMDGOALS))


## shell	:	Access `matomo` container via shell.
##		You can optionally pass an argument with a service name to open a shell on the specified container
shell:
	docker-compose exec matomo /bin/bash
