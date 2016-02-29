<?php

class AmberStatus {

  function get_summary($url, $preferred_providers) {
    if ($url == "http://nodata.example.com") {
      return array();
    } else {
      return array(
        'default' => array(
          'date' => '1395590225',
          'location' => 'Amber/cache/0a137b375cc3881a70e186ce2172c8d1',
          'status' => 1,
          'size' => 3453,
        )
      );
    }
  }
}
