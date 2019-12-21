include .env

.PHONY: test lint install build e2e e2e-open

FILE_MATCH?=

stop:
	docker-compose stop

clean:
	docker-compose down

restart:
	docker-compose restart

install:
	docker-compose -f services-nuxt.yml run --rm install

build:
	docker-compose -f services-nuxt.yml run --rm build

lint:
	docker-compose -f services-nuxt.yml run --rm lint

test:
	docker-compose -f services-nuxt.yml run --rm test

test-single:
	docker-compose -f services-nuxt.yml run --rm unit_single

e2e:
	docker-compose -f services-nuxt.yml run --rm e2e

e2e-open:
	docker-compose -f services-nuxt.yml run --rm e2e_open

logs:
	docker-compose logs -f front

run:
	docker-compose up -d

in:
	docker-compose exec front /bin/bash

in-with-root:
	docker-compose exec --user root front /bin/bash

default: run