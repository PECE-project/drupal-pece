.PHONY: run
run:
	docker-compose -f docker-compose-dev.yml run --rm -p 8080:80 dev_pece

.PHONY: in
in:
	docker ps
	docker exec -it $(shell docker-compose ps | grep _dev_ | cut -d" " -f 1) /bin/bash

.PHONY: out
out:
	docker-compose -f docker-compose-dev.yml stop

.PHONY: up
up:
	docker-compose up -d --remove-orphans

.PHONY: stop
stop:
	docker-compose stop

.PHONY: clean
clean:
	docker-compose down
	rm -rf ./node_modules
	rm -rf ./cnf
	rm -rf ./builds
	rm -rf ./build

.PHONY: logs
logs:
	docker-compose logs $(filter-out $@,$(MAKECMDGOALS))

.PHONY: distro-clean
distro-clean:
	docker-compose down
	rm -rf ./build

.PHONY: drush
drush:
	docker exec $(shell docker-compose ps | grep _php | cut -d" " -f 1) bash -c 'drush -r build $(filter-out $@,$(MAKECMDGOALS))'

.PHONY: shell
shell:
	docker-compose exec php bash

.PHONY: install
install:
	docker-compose -f docker-compose-dev.yml run --rm dev_pece npm install

.PHONY: setup
setup:
	docker-compose -f docker-compose-dev.yml run --rm dev_pece gulp setup

.PHONY: build
build:
	docker-compose -f docker-compose-dev.yml run --rm dev_pece gulp build

.PHONY: site-install
site-install:
	docker-compose -f docker-compose-dev.yml run --rm dev_pece gulp site-install

.PHONY: build-dev
build-dev:
	docker-compose -f docker-compose-dev.yml run --rm dev_pece npm install && gulp setup && gulp build && gulp site-install

.PHONY: exec
exec:
	docker-compose exec php bash -c $(filter-out $@,$(MAKECMDGOALS))

.PHONY: prod
prod:
	docker-compose run --rm -p 8080:80 production

distro: distro-clean
	docker-compose run --rm production gulp pack-distro

.PHONY: run-prod
run-prod:
	docker-compose -f docker-compose-prod.yml -f docker-compose-prod.override.yml up -d --remove-orphans

.PHONY: stop-prod
stop-prod:
	docker-compose -f docker-compose-prod.yml stop

.PHONY: in-prod
in-prod:
	docker-compose -f docker-compose-prod.yml exec php_v1 /bin/bash

.PHONY: shell-prod
shell-prod: in-prod

.PHONY: drush-prod
drush-prod:
	docker exec $(shell docker-compose ps | grep _php_v1 | cut -d" " -f 1) bash -c 'drush -r build $(filter-out $@,$(MAKECMDGOALS))'

.PHONY: log-prod-nginx
log-prod-nginx:
	docker-compose -f docker-compose-prod.yml logs nginx_v1

.PHONY: log-prod-php
log-prod-php:
	docker-compose -f docker-compose-prod.yml logs php_v1

.PHONY: log-prod-mysql
log-prod-mysql:
	docker-compose -f docker-compose-prod.yml logs db_v1

.PHONY: run-matrix-permissions
run-matrix-permissions:
	docker-compose -f docker-compose-prod.yml exec php_v1 sh -c "cd build && php ./scripts/run-tests.sh --concurrency 3 --url http://v1.pece.local PECE"

%:
	@:
