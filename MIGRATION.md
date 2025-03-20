## Process
- Install the upgraded version of the site
- Make sure the queue table exists (I just `ddev drush uli` and click uli)
- bump the sql auto-incrementers `ddev mysql < scripts/alter.sql`
- import default content `ddev content-import-all`
- import the source database `ddev import-db --database=d7 --file=backups/yourbackup.sql.gz`
- run the sql helpers: `ddev mysql d7 < scripts/panel_mapper.sql` and `ddev mysql d7 < scripts/token_parser.sql`
- rsync the files directory to wherever the migration will run (prevent timeout of video files moving during migration, and required for private files anyway) `rsync -av user@example.com:/var/www/html/sites/default/files/ web/sites/default/files`
- scrape/collect the essay pages (see scripts/commands.md)
- rebuild the cache `ddev drush cr`
- run the migration `ddev drush mim --tag='PECE v1'`
- note that completed files locations will be split between public and private. For example, when syncing to a target from the project root, use:
`rsync -rlptvz --exclude /php --exclude /js --exclude /css --exclude /styles --exclude /twig ./private-files/ new-server:/path/to/private` (by default, in `../private-files` in relation to web/)
`rsync -rlptvz --exclude /php --exclude /js --exclude /css --exclude /styles --exclude /twig --exclude /private web/sites/default/files/ new-server:/path/to/sites/default/files`

