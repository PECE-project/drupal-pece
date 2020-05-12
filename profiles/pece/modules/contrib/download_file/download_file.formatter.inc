<?php
// $Id: download_file.formatter.inc,v 1.1.6.4 2010/12/03 12:00:25 xmattx Exp $

/**
 * Theming function for displaying the link to direct download the file.
 *
 * @param $element
 *   Element(s) to format.
 * @return
 *   A string containing the HTML ouput.
 */
function theme_download_file_formatter_direct_download($variables) {
  $output = '';

  foreach ($variables['items'] as $delta => $item) {
    if (!empty($item)) {
      $output .= theme('download_file_direct_download_item', 
                       array('file' => (object) $item));
    }
  }

  return $output;
}

/**
 * Theming function for displaying the link to direct download the file with the type icon.
 *
 * @param $element
 *   Element(s) to format.
 * @return
 *   A string containing the HTML ouput.
 */
function theme_download_file_formatter_direct_download_icon($variables) {
  $output = '';

  foreach ($variables['items'] as $delta => $item) {
    if (!empty($item)) {
      $output .= theme('download_file_direct_download_icon_item', 
                       array('file' => (object) $item));
    }
  }

  return $output;
}

/**
 * Theming function for displaying the link accessible to direct download the file.
 *
 * @param $element
 *   Element(s) to format.
 * @return
 *   A string containing the HTML ouput.
 */
function theme_download_file_formatter_direct_download_accessible($variables) {
  $output = '';

  foreach ($variables['items'] as $delta => $item) {
    if (!empty($item)) {
      $output .= theme('download_file_direct_download_item_accessible', 
                       array('file' => (object) $item));
    }
  }

  return ($output) ? '<ul class="download-file">' . $output . '</ul>' : $output;
}

/**
 * Theming function for displaying the link accessible to direct download the file with the type icon.
 *
 * @param $element
 *   Element(s) to format.
 * @return
 *   A string containing the HTML ouput.
 */
function theme_download_file_formatter_direct_download_accessible_icon($variables) {
  $output = '';

  foreach ($variables['items'] as $delta => $item) {
    if (!empty($item)) {
      $output .= theme('download_file_direct_download_icon_item_accessible', 
                       array('file' => (object) $item));
    }
  }

  return ($output) ? '<ul class="download-file">' . $output . '</ul>' : $output;
}

/**
 * Theming function for link with a thumbnail to direct download the image.
 *
 * @param $element
 *   Element(s) to format.
 * @return
 *   A string containing the HTML ouput.
 */
function theme_download_file_formatter_direct_download_thumbnail_image($variables) {
  $output = '';
  foreach ($variables['items'] as $delta => $item) {
    if (!empty($item)) {
      $output .= theme('download_file_direct_download_thumbnail_image', 
                       array('file' => (object) $item));
    }
  }

  return $output;
}

/**
 * Theme function for the 'direct_download' multiple file formatter.
 *
 * @param $file
 *   File to format.
 * @return
 *   A string containing the HTML ouput.
 */
function theme_download_file_direct_download_item($variables) {
  $file = $variables['file'];
  
  // Views may call this function with a NULL value, return an empty string.
  if (empty($file->fid)) {
    return '';
  }

  $url     = download_file_path($file->fid);
  $options = array();

  // Use the description or the title as the link text if available.
  if (empty($file->description) && empty($file->title)) {
    $link_text = $file->filename;
  }
  else {
    if (!empty($file->description)) {
      $link_text = $file->description;
    }
    elseif (!empty($file->title)) {
      $link_text = $file->title;
    }
    
    $options['attributes']['title'] = $file->filename;
  }

  return '<div class="download-file clear-block">' . l($link_text, $url, $options) . '</div>';
}

/**
 * Theme function for the 'direct_download_icon' multiple file formatter.
 *
 * @param $file
 *   File to format.
 * @return
 *   A string containing the HTML ouput.
 */
function theme_download_file_direct_download_icon_item($variables) {
  $file = $variables['file'];
  
  // Views may call this function with a NULL value, return an empty string.
  if (empty($file->fid)) {
    return '';
  }

  $url     = download_file_path($file->fid);
  $icon    = theme('file_icon', array('file' => $file));
  $options = array();

  // Use the description or the title as the link text if available.
  if (empty($file->description) && empty($file->title)) {
    $link_text = $file->filename;
  }
  else {
    if (!empty($file->description)) {
      $link_text = $file->description;
    }
    elseif (!empty($file->title)) {
      $link_text = $file->title;
    }
    
    $options['attributes']['title'] = $file->filename;
  }

  return '<div class="download-file clear-block">' . $icon . l($link_text, $url, $options) . '</div>';
}

/**
 * Theme function for the 'direct_download_accessible' multiple file formatter.
 *
 * @param $file
 *   File to format.
 * @return
 *   A string containing the HTML ouput.
 */
function theme_download_file_direct_download_item_accessible($variables) {
  $file = $variables['file'];
  
  // Views may call this function with a NULL value, return an empty string.
  if (empty($file->fid)) {
    return '';
  }

  $url             = download_file_path($file->fid);
  $accessibility   = theme('download_file_detail_accessible', array('file' => $file));
  $options['html'] = TRUE;

  // Use the description or the title as the link text if available.
  if (empty($file->description) && empty($file->title)) {
    $link_text = $file->filename;
  }
  else {
    if (!empty($file->description)) {
      $link_text = $file->description;
    }
    elseif (!empty($file->title)) {
      $link_text = $file->title;
    }
    
    $options['attributes']['title'] = $file->filename;
  }

  return '<li>' . l($link_text . ' ' . $accessibility, $url, $options) . '</li>';
}

/**
 * Theme function for the 'direct_download_accessible_icon' multiple file formatter.
 *
 * @param $file
 *   File to format.
 * @return
 *   A string containing the HTML ouput.
 */
function theme_download_file_direct_download_icon_item_accessible($variables) {
  $file = $variables['file'];
  
  // Views may call this function with a NULL value, return an empty string.
  if (empty($file->fid)) {
    return '';
  }

  $url             = download_file_path($file->fid);
  $icon            = theme('file_icon', array('file' => $file));
  $accessibility   = theme('download_file_detail_accessible', array('file' => $file));
  $options['html'] = TRUE;

  // Use the description or the title as the link text if available.
  if (empty($file->description) && empty($file->title)) {
    $link_text = $file->filename;
  }
  else {
    if (!empty($file->description)) {
      $link_text = $file->description;
    }
    elseif (!empty($file->title)) {
      $link_text = $file->title;
    }
    
    $options['attributes']['title'] = $file->filename;
  }

  return '<li>' . $icon . l($link_text . ' ' . $accessibility, $url, $options) . '</li>';
}
/**
 * Theme function for the 'direct_download__thumbnail_image' multiple file formatter.
 *
 * @param $file
 *   File to format.
 * @return
 *   A string containing the HTML ouput.
 */
function theme_download_file_direct_download_thumbnail_image($variables) {
  $file = $variables['file'];
  
  // Views may call this function with a NULL value, return an empty string.
  if (empty($file->fid)) {
    return '';
  }
  
  $image_url       = $variables['file']->uri;
  $image_alt       = $variables['file']->alt;
  $image_title     = $variables['file']->title;
  $style           = 'thumbnail';
  $image_path      = image_style_url($style, $image_url);
  $url             = download_file_path($file->fid);
  $image           = "<img src='$image_path' alt='$image_alt' title='$image_title' />";
  $options['html'] = TRUE;
  
  return '<div class="download-file clear-block">' . l($image, $url, $options) . '</div>';
}

/**
 * Theme function for the link accessible.
 *
 * @param $file
 *   File to format.
 * @return
 *   A string containing the HTML ouput.
 */
function theme_download_file_detail_accessible($variables) {
  $file = $variables['file'];

  $extension = theme('download_file_extension_accessible', 
                    array('extension' => download_file_format_extension($file)));
  $file_size = theme('download_file_bytes_accessible', array('filesize' => $file->filesize));
  $format = variable_get('download_file_accessible_format', '(format !extension / !file_size)');

  return '<span class="detail">' . t($format, array('!extension' => $extension, '!file_size' => $file_size)) . '</span>';
}

/**
 * Theme function for the extension accessible.
 *
 * @param $extension
 *   File extension to format.
 * @return
 *   A string containing the HTML ouput.
 */
function theme_download_file_extension_accessible($variables) {
  $extension = $variables['extension'];
  
  if (is_array($extension)) {
    $extension = '<acronym title="' . $extension['definition'] . '">' . $extension['name'] . '</acronym>';
  }
  
  return $extension;
}

/**
 * Theme function for the size format accessible.
 *
 * @param $filesize
 *   File size to format.
 * @return
 *   A string containing the HTML ouput.
 */
function theme_download_file_bytes_accessible($variables) {
  $filesize = $variables['filesize'];
  
  if (empty($filesize)) {
    return '';
  }

  list($size, $unit) = download_file_format_bytes($filesize, 0);
  $acronyms          = array(t('B') => t('Bytes'),
                            t('KB') => t('Kilo Bytes'),
                            t('MB') => t('Mega Bytes'),
                            t('GB') => t('Giga Bytes'),
                            t('TB') => t('Tera Bytes'),
                            t('PB') => t('Peta Bytes'));

  return $size . ' <acronym title="' . $acronyms[$unit] . '">' . $unit . '</acronym>';
}
