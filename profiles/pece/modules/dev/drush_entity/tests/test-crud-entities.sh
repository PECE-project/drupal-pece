#!/bin/bash

# TODO This is a very simple test script
# Run this from the terminal from within a drupal root
# ~/.drush/drush_entity/tests/test-entities.sh

# We prefer properties as these are human readable
# TODO wait for drush to implement these
FORMAT=properties

function stamp {
  echo ==============
  echo timestamp : `date`
  echo ==============
}

stamp

echo Enabling devel_generate.
drush --yes en devel_generate

stamp
echo Creating 10 nodes with 5 comments each
drush genc 10 5

stamp
echo Reading node 6 IDS
IDS=`drush entity-read node | grep -v node | cut -f 1-6 -d " "`

stamp
echo read nodes as json
drush entity-read node $IDS --format=json

stamp
echo Deleting through entity-delete $IDS
drush entity-delete node $IDS

IDS=`drush entity-read node | grep -v node | cut -f 1 -d " "`
echo Getting first node $IDS in json
drush entity-read node $IDS --format=json

stamp
echo Deleting all comments by list of IDs
drush entity-delete comment `drush entity-read comment`

stamp
echo Delete all comments
drush entity-delete comment --yes

stamp
echo Deleting all nodes by list of IDs
drush entity-delete node `drush entity-read node`

stamp
echo Creating 20 nodes
drush genc 20

stamp
echo Read all nodes of type page
drush entity-read node --bundles=page

stamp
echo Delete all nodes of type page
drush entity-delete node --bundles=page --yes

stamp
echo Delete all nodes
drush entity-delete node --yes
