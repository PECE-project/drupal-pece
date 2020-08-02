include docker.mk

.PHONY: test build

DRUPAL_VER ?= 8
PHP_VER ?= 7.2
FILE_MATCH ?=

BRANCH = $(shell git rev-parse --abbrev-ref HEAD)

test:
	@echo "Starting test containers for $(PROJECT_NAME)..."
	docker-compose -f docker-compose-tests.yml pull
	docker-compose -f docker-compose-tests.yml up -d
	@echo "Starting tests for $(PROJECT_NAME)..."
	docker-compose -f docker-compose-tests.yml exec pece-test bash -c "cd web && ../vendor/bin/phpunit --configuration core core/modules/datetime/tests/src/Unit/Plugin/migrate/field/DateFieldTest.php"
	@echo "Stopping test containers for $(PROJECT_NAME)..."
	docker-compose -f docker-compose-tests.yml stop


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
