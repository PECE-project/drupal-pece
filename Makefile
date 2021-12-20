.PHONY: up run stop clean distro prod run-prod stop-prod


run:
	docker-compose run --rm -p 8080:80 dev_pece

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

prod:
	docker-compose run --rm -p 8080:80 production

distro: distro-clean
	docker-compose run --rm production gulp pack-distro

run-php7:
	docker-compose -f docker-compose-php7.2.yml run --rm -p 8080:80 dev_pece

run-prod:
	docker-compose -f docker-compose-prod.yml up -d

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
	docker-compose -f docker-compose-prod.yml exec php_v1 sh -c "cd build && php ./scripts/run-tests.sh --url http://v1.pece.local PECE"
