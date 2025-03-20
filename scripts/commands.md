# Setup

This process can be run inside of the DDEV container. If doing so, first install python3, pip, virtualenv, and mariadb libs:
`sudo apt update && sudo apt install python3 virtualenv pip libmariadb-dev`

Initial setup
```shell
$ python3 -m virtualenv .venv
$ source .venv/bin/activate
$ pip install -r requirements.txt
```
Source/activate the python environment is needed again any time shell is restarted and you need to run .py scripts

# Preparing a download & scrape script

1. Set up the dump_essays.sql with correct site information first:
```sql
SELECT CONCAT('wget --header "cookie: $SESSID=$SESSKEY" -O page-', nid, '.htm https://example.com/node/', nid, '/essay && ./sou.py page-', nid, '.htm > essay-', nid, '.htm') AS `#!/bin/env bash` FROM node WHERE type = 'pece_essay';
```
1. Use that to create the main script to download/parse all essay content (change `databasename` accordingly):
`ddev mysql d7 < dump_essays.sql > script.sh`
1. Ensure your environment contains the SESSID and SESSKEY from a logged in user in Drupal to retrieve any private pages (view storage->cookies in FireFox in DevTools).
```shell
$ export SESSID=SSESSxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
$ export SESSKEY=xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
```
1. Make the script executable and run it. This will save the essay content, first as page-{nodeID}.htm and then parse the essay out to essay-{nodeID}.htm, in the current folder:
`$ chmod +x script.sh && ./script.sh`
1. If needed, get your DB_PORT from `ddev describe`. You want the port for localhost/127.0.0.1 if running outside the container. Defaults are assumed for inside the container.
1. Import files into your DB: `DB_PORT={localhostport} DB_NAME={d7dbname} DB_HOST={dbserver} ./import.py <directory path to essays>`

# When that completes, get extra information about classes:

This step is entirely optional, but can be used to determine what styling was used in the essay's, in case that styling needs to be implemented for your destination.

1. Report the classes used in each essay (note this will take some time). If running this a second time, remove class.list beforehand:
`find -iname 'essay-*' -exec report-classes.py {} >> class.list \;`
1. Count the combined class usage:
`sort class.list | uniq -c > counted-classes.txt`

`counted-classes.txt` can be opened in LibreOffice calc, using space as a delimiter on opening it. Then it can be easily sorted by the first column which contains a count of times a class is used across all essays.
