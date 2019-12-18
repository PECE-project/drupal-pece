include .env

.PHONY: test lint install build e2e e2e-open

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