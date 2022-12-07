include docker.mk

.PHONY: test install build build-dev site-install distro-install nuxt-install nuxt-build nuxt-lint nuxt-run start-automation

DRUPAL_VER ?= 8
PHP_VER ?= 8.1
FILE_MATCH ?=

BRANCH = $(shell git rev-parse --abbrev-ref HEAD)
PHP_CONTAINER = $(shell docker ps --filter name='^/$(PROJECT_NAME)_php' --format "{{ .ID }}")

## hlp	:	Print commands help.
hlp : Makefile
	@sed -n 's/^##//p' $<

## test	: 	Run test automation.
test:
	cd ./tests/$(DRUPAL_VER) && PHP_VER=$(PHP_VER) ./run.sh

## install	:	Install project dependencies.
##		Set ENVIRONMENT variable as prod to skip development dependencies.
##		By default it will install dev dependencies if ENVIRONMENT is not set. 
install:
	@echo "Install $(PROJECT_NAME) dependencies..."
ifeq ($(ENVIRONMENT), prod)
	docker exec -t $(PHP_CONTAINER) composer install --no-dev
else
	docker exec -t $(PHP_CONTAINER) composer install
endif
	@echo "Finished installing $(PROJECT_NAME) dependencies..."

## build	:	Build the project.
build:
	@echo "Build $(PROJECT_NAME)..."
	@make install
# TODO: Add drush config:import -y when there are settings files 
	docker exec -t $(PHP_CONTAINER) bash -c 'vendor/bin/drush updb -y'
	@echo "Finished building $(PROJECT_NAME)"

## build-dev	:	Build development environment.
##		Setup settings.php and copy profiles, modules and themes into web/. 
build-dev:
	@echo "Build $(PROJECT_NAME) Development environment..."
	@make install
	docker exec -t $(PHP_CONTAINER) bash -c 'vendor/bin/run toolkit:build-dev'
	@echo "Finished build development $(PROJECT_NAME)"

## site-install	:	(Re)Install PECE profile.
site-install:
	@echo "Starting $(PROJECT_NAME) install phase..."
	docker exec -t $(PHP_CONTAINER) bash -c 'vendor/bin/drush si -y'
	@echo "Finish $(PROJECT_NAME) Install phase"

distro-install:
	docker-compose -f services-drupal.yml run --rm install

nuxt-install:
	cd $(FRONT_DIR) && make install

nuxt-build:
	cd $(FRONT_DIR) && make build

nuxt-lint:
	cd $(FRONT_DIR) && make lint

nuxt-run:
	cd $(FRONT_DIR) && make run

start-automation:
	docker exec $(shell docker ps --filter name='^/$(PROJECT_NAME)_n8n' --format "{{ .ID }}") python /root/.pece/startWorkflows.py
