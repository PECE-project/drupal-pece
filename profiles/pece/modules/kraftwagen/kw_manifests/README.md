# Kraftwagen Manifests

Kraftwagen Manifests is a Drupal module that provides the means to register and
execute idempotent migrations. Usually migrations are intented to be only ran
once (Drupal already provides this with `hook_update_N`), but in quite a lot of
cases this isn't very usefull.

## Usage

An idempotent migration is called a manifest in Kraftwagen Manifests. You can
register a manifest by implementing `hook_kw_manifests_info` in your module's
`.install` file.

```php
/**
 * Implements hook_kw_manifests_info().
 */
function mymodule_kw_manifests_info() {
  $manifests = array();

  $manifests['my_manifest'] = array(
    'callback' => 'mymodule_manifest_my_manifest',
  );

  return $manifests;
}

function mymodule_manifest_my_manifest() {
  // some very trivial example
  variable_set('some_variable', 'desired value');
}
```

Take a look at `kw_manifests.api.php` for more information about registering 
manifests. The registration makes it for example possible to mark other 
manifests as a dependency, to make sure another manifest is executed before 
yours.

You can execute all the manifests that are registered in enabled modules by 
running the following command (requires [Drush](http://drupal.org/project/drush)
to be installed).

    drush kw-manifests

## Things to note

* It is hard, if not impossible to reliably determine which manifest will be ran
  first. The only promise Kraftwagen Manifests makes, is that the specified 
  dependencies of your manifest will be executed before yours. Do not rely on 
  the execution order of manifests that are not marked as dependency.
* Especially when your module contains a lot of manifests, they can become a 
  little hard to manage. Use the 'file' key in the `hook_kw_manifests_info` 
  implementation to keep your manifests in a seperate file, or maybe even
  a few seperate files to keep your `.install` file clean. Make smart use of 
  the 'callback arguments' key to prevent a lot of repetition in your manifests.
