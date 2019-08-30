include docker.mk

.PHONY: test build

DRUPAL_VER ?= 8
PHP_VER ?= 7.2
FILE_MATCH ?= 

BRANCH = $(shell git rev-parse --abbrev-ref HEAD)

test:
	cd ./tests/$(DRUPAL_VER) && PHP_VER=$(PHP_VER) ./run.sh

build:
	@echo "Build $(PROJECT_NAME)..."
ifeq ($(ENVIRONMENT), prod)
	docker exec $(shell docker ps --filter name='^/$(PROJECT_NAME)_php' --format "{{ .ID }}") composer install --no-dev
else
	docker exec $(shell docker ps --filter name='^/$(PROJECT_NAME)_php' --format "{{ .ID }}") composer install
endif
# TODO: Need drush cim -y when have settings files
	docker exec $(shell docker ps --filter name='^/$(PROJECT_NAME)_php' --format "{{ .ID }}") bash -c 'cd $(DRUPAL_ROOT) && drush updb -y'
	@echo "Finish build $(PROJECT_NAME)"

nuxt-install:
	docker-compose -f services-nuxt.yml run --rm install

nuxt-build:
	docker-compose -f services-nuxt.yml run --rm build

nuxt-lint:
	docker-compose -f services-nuxt.yml run --rm lint

nuxt-e2e-test:
	docker-compose -f services-nuxt.yml run --rm e2e

nuxt-e2e-open-test:
	docker-compose -f services-nuxt.yml run --rm e2e_open

nuxt-unit-test:
	docker-compose -f services-nuxt.yml run --rm unit

nuxt-unit-snap:
	docker-compose -f services-nuxt.yml run --rm unit_snap

nuxt-unit-single:
	docker-compose -f services-nuxt.yml run --rm unit_single