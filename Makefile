include docker.mk

.PHONY: test build

DRUPAL_VER ?= 8
PHP_VER ?= 7.2

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

distro-install:
	docker-compose -f services-drupal.yml run --rm install

