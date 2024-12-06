<?php
#$wodby['files_dir'] = '/mnt/files';

$databases['default']['default']['database'] = $wodby['db']['name'];
$databases['default']['default']['username'] = $wodby['db']['username'];
$databases['default']['default']['password'] = $wodby['db']['password'];
$databases['default']['default']['host'] = $wodby['db']['host'];
$databases['default']['default']['driver'] = $wodby['db']['driver'];
$settings['hash_salt'] = $wodby['hash_salt'];
$settings['file_private_path'] = $app_root . '/../private/';
#$wodby['redis']['host'] = '';
#$wodby['redis']['port'] = '6379';
#$wodby['redis']['password'] = '';
#
#$wodby['valkey']['host'] = '';
#$wodby['valkey']['port'] = '6379';
#$wodby['valkey']['password'] = '';
#
#$wodby['varnish']['host'] = '';
#$wodby['varnish']['terminal_port'] = '6082';
#$wodby['varnish']['secret'] = '';
#$wodby['varnish']['version'] = '';
#
#$wodby['memcached']['host'] = '';
#$wodby['memcached']['port'] = '11211';

