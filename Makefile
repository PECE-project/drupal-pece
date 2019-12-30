.PHONY: run stop clean distro prod


run:
	docker-compose run --rm -p 8080:80 dev_pece

in:
	docker ps
	docker exec -it $(shell docker-compose ps | grep _dev_ | cut -d" " -f 1) /bin/bash

drush:
	docker exec $(shell docker-compose ps | grep _dev_ | cut -d" " -f 1) bash -c 'cd build && drush $(argument)'

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
