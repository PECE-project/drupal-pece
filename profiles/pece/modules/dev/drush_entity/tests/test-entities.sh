#!/bin/bash

# TODO This is a very simple test script
# Run this from the terminal from within a drupal root
# ~/.drush/drush_entity/tests/test-entities.sh

# We write output to a file so errors pop up easily.
OUTPUT=$TMPDIR/drush.entity.log

# We prefer properties as these are human readable
# TODO wait for drush to implement these
FORMAT=properties

function stamp {
  echo ============== >> $OUTPUT
  echo timestamp : `date` >> $OUTPUT
}

function log {
  echo $1
  echo ============== >> $OUTPUT
  echo $1 >> $OUTPUT
  echo -------------- >> $OUTPUT
}

echo > $OUTPUT
stamp

log "List of available entities."
drush --format=$FORMAT entity-type-read >> $OUTPUT
stamp

log "List of available entities with json."
drush --format=json entity-type-read >> $OUTPUT
stamp

log "Reading all entity types information."
drush --format=$FORMAT entity-type-read `drush entity-type-read` >> $OUTPUT
stamp

log "Reading all entity types */bundle values."
drush --format=$FORMAT entity-type-read `drush entity-type-read` --fields="*/bundle" >> $OUTPUT
stamp

log "Next command fails generating an error or output."
drush --format=$FORMAT el >> $OUTPUT
stamp

log "Listing entities in table format."
drush el >> $OUTPUT
stamp

log "Next command contains same info needed for drush el"
drush etr `drush etr` --fields="bundles/*/label,label,base table,revision table,fieldable,entity class,controller class,drush/count" >> $OUTPUT
stamp

log "Read all entity type info"
drush entity-type-read `drush entity-type-read` >> $OUTPUT
stamp

log "Read all entity label and base tables as json"
drush entity-type-read --fields="label,base table" --format=json `drush entity-type-read` >> $OUTPUT
stamp

log "Reading node type info."
drush entity-type-read node >> $OUTPUT
stamp

log "Reading node ids."
drush entity-read node `drush er node`>> $OUTPUT
stamp

log "Reading users info."
drush entity-type-read user `drush er user` >> $OUTPUT
stamp

log "Reading files info."
drush entity-read file `drush er file`>> $OUTPUT
stamp

less $OUTPUT

rm $OUTPUT
