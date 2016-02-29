/**
 * @file
 * Functionality for implementing the caption filter button in tinyMCE.
 */
var CaptionFilterButton = {
  init : function() {
    var ed = tinyMCEPopup.editor;
    var node = ed.selection.getNode();
    var p = ed.dom.getParents(node, 'DIV');
    var f = document.forms[0];

    // Only pre-populate values if we're inside an existing caption.
    if (p[0] && ed.dom.hasClass(p[0], 'caption-inner')
      && p[2] && ed.dom.hasClass(p[2], 'caption')) {
      // Parse the entire caption block to get the original [caption] tag.
      var tag = Drupal.captionFilter.toTag(p[2].outerHTML);

      // Filter the tag elements to have &quot; elements
      tag = tag.replace(/\\"/g, '&quot;');

      // Extract the caption from the [caption] attribute first, caption-text class second, raw text third.
      // fails default to the HTML.
      var caption_attribute = tag.match(/^\[caption.*caption=\"([^"]*)\".*\].*\[\/caption\]$/);
      var caption_wrapper = tag.match(/^\[caption.*\]\<img.*\><p class="caption-text">(.*)<\/p>\[\/caption\]$/);
      var caption_html = tag.match(/^\[caption.*\]\<img.*\>(.*)\[\/caption\]$/);
      if (caption_attribute && caption_attribute[1]) {
        f.caption.value = caption_attribute[1];
      }
      else if (caption_wrapper && caption_wrapper[1]) {
        f.caption.value = caption_wrapper[1];
      }
      else if (caption_html && caption_html[1]) {
        f.caption.value = caption_html[1];
      }

      // Filter the caption value to replace double quotes
      f.caption.value = f.caption.value.replace(/\&quot;/g, '"');

      // Extract the alignment.
      var align = tag.match(/^\[caption.*align=\"([^"]*)\".*\].*\[\/caption\]$/);
      if (align && align[1]) {
        f.align.value = align[1];
      }
    }
  },

  insert : function() {
    var ed = tinyMCEPopup.editor;
    var node = ed.selection.getNode();
    var p = ed.dom.getParents(node, 'DIV');
    var align = document.forms[0].align.value;
    var caption = document.forms[0].caption.value;
    var image;
    var tag;
    var replace = false;
    // If we're inside an existing caption...
    if (p[0] && ed.dom.hasClass(p[0], 'caption-inner')
      && p[2] && ed.dom.hasClass(p[2], 'caption')) {
      replace = true;
      // Recall the original [caption] tag.
      tag = Drupal.captionFilter.toTag(p[2].outerHTML);
      // Select the outer DIV so we can replace the entire thing.
      ed.selection.select(p[2]);
        // If we're in an existing caption, parse it from the [caption] tag.
        var parse = tag.match(/^\[caption.*\](\<img.*\>)(.*)\[\/caption\]$/);
        if (parse[1]) {
          image = parse[1];
        }
    }
    // Get the image HTML.
    else if (node.nodeName === 'IMG') {
      // If we're on the image, just use it.
      image = node.outerHTML;
    }
    var newtag = '[caption';
    if (align == 'right' || align == 'left') {
      newtag += ' align="' + align + '"';
    }
    if (caption) {
      newtag += ' caption="' + caption.replace(/"/g, '\\"') + '"';
    }
    newtag += ']' + image + '[/caption]';

    // Create the new [caption] tag.
    if (replace === true){
      ed.dom.remove(p[2], false);
      ed.execCommand('mceReplaceContent', false, newtag);
    } else {
        ed.execCommand('mceReplaceContent', false, newtag);
    }
    tinyMCEPopup.close();
  }
};

tinyMCEPopup.onInit.add(CaptionFilterButton.init, CaptionFilterButton);
