
/**
 * @file node_access_rebuild_bonus.js.
 */

(function ($) {
  /**
   * Perform the ajax request.
   */
  function node_access_rebuild_bonus_ajax_request() {
    // Generate the URI from the basePath and path plus a random token to bypass caching.
    var uri = Drupal.settings.basePath
            + "?q="
            + 'node_access_rebuild_bonus/ajax/'
            + Math.floor((1000000000 * Math.random())).toString(16);
    // Perform ajax request.
    $.get(uri, node_access_rebuild_bonus_ajax_response);
  }

  /**
   * Handle the ajax request.
   */
  function node_access_rebuild_bonus_ajax_response(data) {
    if (data == 'true') {
      node_access_rebuild_bonus_ajax_request();
    }
  }

  Drupal.behaviors.nodeAccessRebuildBonus = {
    attach: function(context) {
      // Start the ajax.
      node_access_rebuild_bonus_ajax_request();
    }
  };
})(jQuery);
