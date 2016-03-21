<?php

/*
 * @file
 *   Tests for Drush Entity
 */

class EntityTestCase extends Drush_CommandTestCase {

  public static function setUpBeforeClass() {
    parent::setUpBeforeClass();
    // cwd == sandbox
    exec('ln -s ' .escapeshellarg('/home/vagrant/builds/helmo/drush_entity')
        . ' ' . escapeshellarg(getenv('HOME') . '/.drush/drush_entity'));
  }

  public static function tearDownAfterClass() {
    // Do our own cleanup - symlink from setUpBeforeClass()
    unlink(getenv('HOME') . '/.drush/drush_entity');
    parent::tearDownAfterClass();
  }

  /*
   * Test entity support for Node entities
   *
   * plan:
   * - create an entity with entity-create
   * - verify with entity-show
   * - delete with entity-delete
   * - verify with entity-show that it's no longer present
   */

  public function testEntityNode6() {
    $sites = $this->setUpDrupal(1, TRUE, 6);
    $uri = key($sites);
    $alias = '@' . $uri;

    $type = 'node';

    // Create a temp file with the content we wish to create
    $tmp_filename = tempnam(UNISH_TMP, 'entity_test');
    $data = '{"title":"Foo","type":"page","body":{"und":[{"value":"","format":"filtered_html"}]}}';
    file_put_contents($tmp_filename, $data);

    // Create
    $this->drush('entity-create', array($type, $tmp_filename), array('json' => 1), $alias);

    // List all, to determin the newly created id
    $this->drush('entity-read', array($type), array('format' => 'json'), $alias);
    $output = json_decode($this->getOutput());
    $id = end($output);
    $this->assertEquals(array($id), $output, 'The new id shows up in a listing');

    // Show as verification
    $this->drush('entity-read', array($type, $id), array('format' => 'json'), $alias);
    $output = json_decode($this->getOutput());
    $this->assertEquals($output->title, 'Foo', 'Title field is what we expected');

    // Delete
    $this->drush('entity-delete', array($type, $id), array(), $alias);

    // List to verify that the entity has really been deleted
    $this->drush('entity-read', array($type), array('format' => 'json'), $alias);
    $output = json_decode($this->getOutput());
    $this->assertEquals(FALSE, in_array($id, $output), 'The deleted entity is nolonger present in a listing');
  }

  public function testEntityNode7() {
    $sites = $this->setUpDrupal(1, TRUE, 7);
    $uri = key($sites);
    $alias = '@' . $uri;

    $type = 'node';

    // Create a temp file with the content we wish to create
    $tmp_filename = tempnam(UNISH_TMP, 'entity_test');
    $data = '{"title":"Foo","type":"page","body":{"und":[{"value":"","format":"filtered_html"}]}}';
    file_put_contents($tmp_filename, $data);

    // Create
    $this->drush('entity-create', array($type, $tmp_filename), array('json' => 1), $alias);

    // List all, to determin the newly created id
    $this->drush('entity-read', array($type), array('format' => 'json'), $alias);
    $output = json_decode($this->getOutput());
    $id = end($output);
    $this->assertEquals(array($id), $output, 'The new id shows up in a listing');

    // Show as verification
    $this->drush('entity-read', array($type, $id), array('format' => 'json'), $alias);
    $output = json_decode($this->getOutput());
    $this->assertEquals('Foo', $output->title, 'Title field is what we expected');

    // Delete
    $this->drush('entity-delete', array($type, $id), array(), $alias);

    // List to verify that the entity has really been deleted
    $this->drush('entity-read', array($type), array('format' => 'json'), $alias);
    $output = json_decode($this->getOutput());
    $this->assertEquals(FALSE, in_array($id, $output), 'The deleted entity is nolonger present in a listing');
  }


  public function testEntityFile7() {
    $sites = $this->setUpDrupal(1, TRUE, 7);
    $uri = key($sites);
    $alias = '@' . $uri;

    $type = 'file';

    // Create a real file for which we will create a file entity.
    file_put_contents($this->webroot() . '/sites/dev/files/foo.txt', "ABC");
    $public_path = 'public://foo.txt';
    //file_put_contents(drupal_realpath($public_path), 'ACB');

    // Create a temp file with the content we wish to create
    $tmp_filename = tempnam(UNISH_TMP, 'entity_test');
    $data = '{"uid":"1","filename":"foo.txt","uri":"' . $public_path . '","filemime":"text/plain","filesize":"3","status":"1","timestamp":"1320416219","rdf_mapping":[]}';
    file_put_contents($tmp_filename, $data);

    // Create
    $this->drush('entity-create', array($type, $tmp_filename), array('json' => 1), $alias);

    // List all, to determin the newly created id
    $this->drush('entity-read', array($type), array('format' => 'json'), $alias);
    $output = json_decode($this->getOutput());
    $id = end($output);
    $this->assertEquals(array($id), $output, 'The new id shows up in a listing');

    // Show as verification
    $this->drush('entity-read', array($type, $id), array('format' => 'json'), $alias);
    $output = json_decode($this->getOutput());
    $this->assertEquals('foo.txt', $output->filename, 'Filename field is what we expected');

    // Delete
    $this->drush('entity-delete', array($type, $id), array(), $alias);

    // List to verify that the entity has really been deleted
    $this->drush('entity-read', array($type), array('format' => 'json'), $alias);
    $output = json_decode($this->getOutput());
    $this->assertEquals(FALSE, in_array($id, $output), 'The deleted entity is nolonger present in a listing');
  }

  public function testEntityUpdate7() {
    $sites = $this->setUpDrupal(1, TRUE, 7);
    $uri = key($sites);
    $alias = '@' . $uri;

    $type = 'node';

    // Create a temp file with the content we wish to create
    $tmp_filename = tempnam(UNISH_TMP, 'entity_test');
    $data = '{"title":"Foo","type":"page","body":{"und":[{"value":"","format":"filtered_html"}]}}';
    file_put_contents($tmp_filename, $data);

    // Create
    $this->drush('entity-create', array($type, $tmp_filename), array('json' => 1), $alias);

    // List all, to determin the newly created id
    $this->drush('entity-read', array($type), array('format' => 'json'), $alias);
    $output = json_decode($this->getOutput());
    $id = end($output);
    $this->assertEquals(array($id), $output, 'The new id shows up in a listing');

    // Show as verification
    $this->drush('entity-read', array($type, $id), array('format' => 'json'), $alias);
    $output = json_decode($this->getOutput());
    $this->assertEquals('Foo', $output->title, 'Title field is what we expected');

    $output->title = 'Bar';
    file_put_contents($tmp_filename, json_encode($output));

    // Do an update
    $this->drush('entity-update', array($type, $id), array('json' => 1, 'json-input' => $tmp_filename), $alias);

    // Show as verification
    $this->drush('entity-read', array($type, $id), array('format' => 'json'), $alias);
    $output = json_decode($this->getOutput());
    $this->assertEquals('Bar', $output->title, 'Title field has changed as we expected');

    $data = '{"title":"Qux"}';
    file_put_contents($tmp_filename, $data);

    // Do an update
    $this->drush('entity-update', array($type, $id), array('json' => 1, 'json-input' => $tmp_filename, 'fields' => 'title'), $alias);

    // Show as verification
    $this->drush('entity-read', array($type, $id), array('format' => 'json'), $alias);
    $output = json_decode($this->getOutput());
    $this->assertEquals('Qux', $output->title, 'Title field has changed as we expected');

  }


  /*
   * Test entity support for User entities
   *
   * plan:
   * - create a user with entity-create
   * - verify with entity-show
   * - delete with entity-delete
   * - verify with entity-show that it's no longer present
   */

  public function testEntityUser6() {
    $sites = $this->setUpDrupal(1, TRUE, 6);
    $uri = key($sites);
    $alias = '@' . $uri;

    $type = 'user';

    // Create a temp file with the content we wish to create
    $tmp_filename = tempnam(UNISH_TMP, 'entity_test');
    $data = '{"name":"Mr. Foo","mail":"admin@example.com","status":"1"}';
    file_put_contents($tmp_filename, $data);

    // Create
    $this->drush('entity-create', array($type, $tmp_filename), array('json' => 1), $alias);

    // List all, to determin the newly created id
    $this->drush('entity-read', array($type), array('format' => 'json'), $alias);
    $output = json_decode($this->getOutput());
    $id = end($output);
    $this->assertEquals(array(0, 1, $id), $output, "New user $id created");

    // Show as verification
    $this->drush('entity-read', array($type, $id), array('format' => 'json'), $alias);
    $output = json_decode($this->getOutput());
    $this->assertEquals($output->name, 'Mr. Foo', 'name field is what we expected');

    // Delete
    $this->drush('entity-delete', array($type, $id), array(), $alias);

    // List to verify that the entity has really been deleted
    $this->drush('entity-read', array($type), array('format' => 'json'), $alias);
    $output = json_decode($this->getOutput());
    $this->assertEquals(FALSE, in_array($id, $output), 'The deleted entity is nolonger present in a listing');
  }

  public function testEntityUser7() {
    $sites = $this->setUpDrupal(1, TRUE, 7);
    $uri = key($sites);
    $alias = '@' . $uri;

    $type = 'user';

    // Create a temp file with the content we wish to create
    $tmp_filename = tempnam(UNISH_TMP, 'entity_test');
    $data = '{"name":"Mr. Foo","mail":"admin@example.com","status":"1"}';
    file_put_contents($tmp_filename, $data);

    // Create
    $this->drush('entity-create', array($type, $tmp_filename), array('json' => 1), $alias);

    // List all, to determin the newly created id
    $this->drush('entity-read', array($type), array('format' => 'json'), $alias);
    $output = json_decode($this->getOutput());
    $id = end($output);
    $this->assertEquals(array(0,1,$id), $output);

    // Show as verification
    $this->drush('entity-read', array($type, $id), array('format' => 'json'), $alias);
    $output = json_decode($this->getOutput());
    $this->assertEquals('Mr. Foo', $output->name, 'name field is what we expected');

    // Delete
    $this->drush('entity-delete', array($type, $id), array(), $alias);

    // List to verify that the entity has really been deleted
    $this->drush('entity-read', array($type), array('format' => 'json'), $alias);
    $output = json_decode($this->getOutput());
    $this->assertEquals(FALSE, in_array($id, $output), 'The deleted entity is nolonger present in a listing');
  }

  public function testEntityTypeRead6() {
    $sites = $this->setUpDrupal(1, TRUE, 6);
    $uri = key($sites);
    $alias = '@' . $uri;

    $type = 'node';
    $this->drush('entity-type-read', array(), array('format' => 'json'), $alias);
    $this->assertEquals('["node","user","taxonomy_vocabulary","taxonomy_term"]', $this->getOutput(), 'list of entity types in json');

    $this->drush('entity-type-read', array($type), array('format' => 'json'), $alias);
    $expected = '{"node":{"entity keys":{"id":"nid","revision":"vid","label":"title"},"drush":{"defaults":{"type":"","title":""},"new":["nid","vid"]},"load list sql":"select nid id from {node}"}}';
    $this->assertEquals($expected, $this->getOutput(), 'details of the entity type node in json');

  }

  public function testEntityTypeRead7() {
    $sites = $this->setUpDrupal(1, TRUE, 7);
    $uri = key($sites);
    $alias = '@' . $uri;

    $type = 'node';
    $this->drush('entity-type-read', array(), array('format' => 'json'), $alias);
    $this->assertEquals('["node","file","user"]', $this->getOutput(), 'list of entity types in json');

    $this->drush('entity-type-read', array($type), array('format' => 'json'), $alias);
    $expected = '{"node":{"label":"Node","controller class":"NodeController","base table":"node","revision table":"node_revision","uri callback":"node_uri","fieldable":true,"entity keys":{"id":"nid","revision":"vid","bundle":"type","label":"title"},"bundle keys":{"bundle":"type"},"bundles":[],"view modes":{"full":{"label":"Full content","custom settings":false},"teaser":{"label":"Teaser","custom settings":true},"rss":{"label":"RSS","custom settings":false}},"static cache":true,"field cache":true,"load hook":"node_load","translation":[],"schema_fields_sql":{"base table":["nid","vid","type","language","title","uid","status","created","changed","comment","promote","sticky","tnid","translate"],"revision table":["nid","vid","uid","title","log","timestamp","status","comment","promote","sticky"]},"drush":{"defaults":{"type":"","title":"","language":"und","body":{"und":[{"value":"","format":"plain_text"}]}},"new":["nid","vid"]}}}';
    $this->assertEquals($expected, $this->getOutput(), 'details of the entity type node in json');

  }
}
