<?php
namespace Drupal\Tests\pece_migrate\Kernel\AccessMatrix;

use Drupal\Core\Database\Database;
use Drupal\Core\DrupalKernel;
use Drupal\Core\Routing\RouteObjectInterface;
use Drupal\Core\Site\Settings;
use Drupal\Core\Test\TestDatabase;
use Drupal\Tests\node\Kernel\NodeAccessTestBase;
use Drupal\TestTools\Comparator\MarkupInterfaceComparator;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\Routing\Route;

/**
 * Tests the access matrix.
 */
class AccessMatrix extends NodeAccessTestBase {

  protected $webUser = null;
  /**
   * {@inheritdoc}
   */
  protected static $modules = [
    'pece_access',
    'user',
    'pece_migrate',
  ];

  /**
   * {@inheritdoc}
   */
  protected function setUp() {

    // Allow tests to compare MarkupInterface objects via assertEquals().
    $this->registerComparator(new MarkupInterfaceComparator());

    $this->root = static::getDrupalRoot();
    $this->initFileCache();
    $this->bootEnvironment();
    $this->bootKernel();
  }
  /**
   * Bootstraps a kernel for a test.
   */
  private function bootKernel() {
    $this->setSetting('container_yamls', []);
    // Allow for test-specific overrides.
//    $settings_services_file = $this->root . '/sites/default/testing.services.yml';
//    if (file_exists($settings_services_file)) {
//      // Copy the testing-specific service overrides in place.
//      $testing_services_file = $this->siteDirectory . '/services.yml';
//      copy($settings_services_file, $testing_services_file);
//      $this->setSetting('container_yamls', [$testing_services_file]);
//    }

    // Allow for global test environment overrides.
//    if (file_exists($test_env = $this->root . '/sites/default/testing.services.yml')) {
//      $GLOBALS['conf']['container_yamls']['testing'] = $test_env;
//    }
    // Add this test class as a service provider.
    $GLOBALS['conf']['container_service_providers']['test'] = $this;

    // When a module is providing the database driver, then enable that module.
    $connection_info = Database::getConnectionInfo();
    $driver = $connection_info['default']['driver'];
    $namespace = $connection_info['default']['namespace'] ?? '';
    $autoload = $connection_info['default']['autoload'] ?? '';

    // Bootstrap the kernel. Do not use createFromRequest() to retain Settings.
    $kernel = new DrupalKernel('testing', $this->classLoader, FALSE);
    $kernel->setSitePath($this->siteDirectory);


    // DrupalKernel::boot() is not sufficient as it does not invoke preHandle(),
    // which is required to initialize legacy global variables.
    $request = Request::create('/');
    $kernel->boot();
    $request->attributes->set(RouteObjectInterface::ROUTE_OBJECT, new Route('<none>'));
    $request->attributes->set(RouteObjectInterface::ROUTE_NAME, '<none>');
    $kernel->preHandle($request);
//
//    $this->container = $kernel->getContainer();
//
//    // Ensure database tasks have been run.
//    require_once '/var/www/html/web/core/includes/install.inc';
////    $errors = db_installer_object($driver, $namespace)->runTasks();
////    if (!empty($errors)) {
////      $this->fail('Failed to run installer database tasks: ' . implode(', ', $errors));
////    }
////
////    //if ($modules) {
////      $this->container->get('module_handler')->loadAll();
////    //}
//
//    // Setup the destination to the be frontpage by default.
//    \Drupal::destination()->set('/');
//
//    $settings = Settings::getAll();
//    $settings['php_storage']['default'] = [
//      'class' => '\Drupal\Component\PhpStorage\FileStorage',
//    ];
//    new Settings($settings);
//
//    // Manually configure the test mail collector implementation to prevent
//    // tests from sending out emails and collect them in state instead.
//    // While this should be enforced via settings.php prior to installation,
//    // some tests expect to be able to test mail system implementations.
//    $GLOBALS['config']['system.mail']['interface']['default'] = 'test_mail_collector';
//
//    // Manually configure the default file scheme so that modules that use file
//    // functions don't have to install system and its configuration.
//    // @see file_default_scheme()
//    $GLOBALS['config']['system.file']['default_scheme'] = 'public';
  }



  /**
   * Override bootEnvironment() for connect in the real database.
   * {@inheritdoc}
   */
  protected function bootEnvironment() {
    $this->streamWrappers = [];
    \Drupal::unsetContainer();

    $this->classLoader = require $this->root . '/autoload.php';

    // Set up virtual filesystem.
    Database::addConnectionInfo('default', 'test-runner', $this->getDatabaseConnectionInfo()['default']);
    //$test_db = new TestDatabase();
    $this->siteDirectory = 'sites/default';

    // Ensure that all code that relies on drupal_valid_test_ua() can still be
    // safely executed. This primarily affects the (test) site directory
    // resolution (used by e.g. LocalStream and PhpStorage).
    //$this->databasePrefix = $test_db->getDatabasePrefix();
    //drupal_valid_test_ua($this->databasePrefix);

    $settings = [
      'hash_salt' => static::class,
      'file_public_path' => $this->siteDirectory . '/files',
      // Disable Twig template caching/dumping.
      'twig_cache' => FALSE,
      // @see \Drupal\KernelTests\KernelTestBase::register()
    ];
    new Settings($settings);

    $this->setUpFilesystem();

    foreach (Database::getAllConnectionInfo() as $key => $targets) {
      Database::removeConnection($key);
    }
    Database::addConnectionInfo('default', 'default', $this->getDatabaseConnectionInfo()['default']);
  }
}

