include docker.mk

.PHONY: test

DRUPAL_VER ?= 8
PHP_VER ?= 7.2

test:
	cd ./tests/$(DRUPAL_VER) && PHP_VER=$(PHP_VER) ./run.sh

build:
	@echo "Build $(PROJECT_NAME)..."
	git pull origin "$(git branch | grep \* | cut -d ' ' -f2)"
	docker exec $(shell docker ps --filter name='^/$(PROJECT_NAME)_php' --format "{{ .ID }}") cd $(DRUPAL_ROOT) && drush updb -y && drush cim -y
	@echo "Finish build $(PROJECT_NAME)"
