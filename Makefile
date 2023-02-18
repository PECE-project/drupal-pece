.PHONY: up run stop clean install setup build site-install build-dev exec distro prod run-prod stop-prod


run:
	docker-compose -f docker-compose.dev.yml run --rm -p 8080:80 dev_pece

in:
	docker ps
	docker exec -it $(shell docker-compose ps | grep _dev_ | cut -d" " -f 1) /bin/bash

drush:
	docker exec $(shell docker-compose ps | grep _dev_ | cut -d" " -f 1) bash -c 'cd build && drush $(argument)'

up:
	docker-compose up -d --remove-orphans

stop:
	docker-compose stop

clean:
	docker-compose down
	rm -rf ./node_modules
	rm -rf ./cnf
	rm -rf ./builds
	rm -rf ./build

distro-clean:
	docker-compose down
	rm -rf ./build

install:
	docker-compose -f docker-compose-dev.yml run --rm dev_pece npm install

setup:
	docker-compose -f docker-compose-dev.yml run --rm dev_pece gulp setup

build:
	docker-compose -f docker-compose-dev.yml run --rm dev_pece gulp build

site-install:
	docker-compose -f docker-compose-dev.yml run --rm dev_pece gulp site-install

build-dev:
	docker-compose -f docker-compose-dev.yml run --rm dev_pece npm install && gulp setup && gulp build && gulp site-install

exec:
	docker-compose exec php bash -c $(filter-out $@,$(MAKECMDGOALS))

prod:
	docker-compose run --rm -p 8080:80 production

distro: distro-clean
	docker-compose run --rm production gulp pack-distro

run-prod:
	docker-compose -f docker-compose-prod.yml -f docker-compose-prod.override.yml up -d

stop-prod:
	docker-compose -f docker-compose-prod.yml stop

in-prod:
	docker-compose -f docker-compose-prod.yml exec php_v1 /bin/bash

log-prod-nginx:
	docker-compose -f docker-compose-prod.yml logs nginx_v1

log-prod-php:
	docker-compose -f docker-compose-prod.yml logs php_v1

log-prod-mysql:
	docker-compose -f docker-compose-prod.yml logs db_v1

run-matrix-permissions:
	docker-compose -f docker-compose-prod.yml exec php_v1 sh -c "cd build && php ./scripts/run-tests.sh --concurrency 3 --url http://v1.pece.local PECE"

%:
	@:
