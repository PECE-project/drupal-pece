include .env

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

logs:
	docker-compose logs -f front

run:
	docker-compose up -d

in:
	docker-compose exec front /bin/bash

in-with-root:
	docker-compose exec --user root front /bin/bash

default: run