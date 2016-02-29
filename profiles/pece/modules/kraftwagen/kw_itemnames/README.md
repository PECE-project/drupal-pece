# Kraftwagen Itemnames

Kraftwagen Itemnames is a Drupal module that allows developers to assign string
identifiers to items in the database that have numeric primary key. The API 
provides a way to _ensure_ that items exist, a way to _remove_ items and a way
to _load_ the items.

## Packages

The package contains some modules. A brief overview over their purpose and
relation.

* **kw_itemnames** The main module that provides the public API to _ensure_, 
  _remove_ and _load_ items. Furthermore it provides an API for other modules to
  register _types_ of items, like _nodes_ or _menu links_.
* **kw_itemnames_entity** Type implementation for all entities. Core entities 
  are _node_, _comment_, _user_, _taxonomy_term_ and _taxonomy_vocabulary_. This 
  module depends on the [Entity API](http://drupal.org/project/entity) for the 
  CRUD operations on entities.
* **kw_itemnames_deletion_prevention** (To be added) Implements logic to prevent
  deletion of named items of supported types. There will at least be support
  for _nodes_.

## Usage

### Ensuring and removing

Using the API items can be created and updated (`kw_itemnames_ensure`) and 
deleted if they still exist (`kw_itemnames_remove`). Although these operations are
primarily intended to be ran from 
[Kraftwagen Manifests](http://github.com/Kraftwagen/kw-manifests), they can be
ran from anywhere. 

The code example below shows how to create or update an item. It assumes that
both `kw_itemnames` and `kw_itemnames_entity` are enabled. 

```php
kw_itemnames_ensure(
  'node', 
  'homepage', 
  array(
    'title' => 'Welcome!', 
  ),
  array(
    'type' => 'page', 
    'language' => LANGUAGE_NONE,
    'body' => array(
      LANGUAGE_NONE => array(array(
        'value' => '<p>Welcome to my site!</p>',
        'format' => 'filtered_html',
      ))
    )
  )
);
```

When this code is ran for the first time, it will create a new language neutral
node of type _Page_ with the specified title and body text. The second time, it
will update the existing node. At this update, it will only change the _title_.
The `kw_itemnames_ensure` function accepts two arrays of properties. The first is
called _required properties_ and the second _default properties_. The required
properties will be set on update, while the default properties will only be used
at initial creation. If somehow the node is deleted, running this function will
recreate the node.

When you once had an item ensured, and you want it to be removed, you can run 
something like the code below.

```php
kw_itemnames_remove('node','homepage');
```

### Get ID and loading

When you have ensured an item, you usually do that because you want to use that
item somewhere. In that case you can call `kw_itemnames_item_id` to get the ID of
an item, or `kw_itemnames_load` to get the loaded item.

You can for example do this in a manifest.

```php
variable_set('site_frontpage', 'node/' . kw_itemnames_item_id('node', 'homepage'));
```
