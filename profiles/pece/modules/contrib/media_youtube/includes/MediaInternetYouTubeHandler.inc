<?php

/**
 * @file
 * Extends the MediaInternetBaseHandler class to handle YouTube videos.
 */

/**
 * Implementation of MediaInternetBaseHandler.
 *
 * @see hook_media_internet_providers().
 */
class MediaInternetYouTubeHandler extends MediaInternetBaseHandler {

  public function parse($embedCode) {
    $list_patterns = array(
      '@youtube\.com/playlist[#\?].*?list=([^"#\& ]+)@i',
      '@youtube\.com/view_play_list[#\?].*?p=([^"#\& ]+)@i',
    );

    foreach ($list_patterns as $pattern) {
      preg_match($pattern, $embedCode, $matches);

      if (isset($matches[1]) && $this->validId($matches[1], 'l')) {
        return file_stream_wrapper_uri_normalize('youtube://l/' . $matches[1]);
      }
    }
    // https://youtube.com/watch/*
    // https://youtube.com/embed/*
    // https://youtube.com/v/*
    // https://youtube.com/?v=*
    // https://youtu.be/*
    // https://gdata.youtube.com/feeds/api/videos/*
    $patterns = array(
      '@youtube\.com/watch[#\?].*?v=([^"#\& ]+).*&list=([^"#\& ]+)@i',
      '@youtu\.be/([^"#\&\? ]+)\?list=([^"#\& ]+)@i',
      '@youtube\.com/embed/([^"#\&\? ]+)\?list=([^"#\& ]+)@i',
      '@youtube\.com/watch[#\?].*?v=([^"#\& ]+)@i',
      '@youtube\.com/embed/([^"#\&\? ]+)@i',
      '@youtube\.com/v/([^"#\&\? ]+)@i',
      '@youtube\.com/\?v=([^"#\& ]+)@i',
      '@youtu\.be/([^"#\&\? ]+)@i',
      '@gdata\.youtube\.com/feeds/api/videos/([^"#\&\? ]+)@i',
    );

    foreach ($patterns as $pattern) {
      preg_match_all($pattern, $embedCode, $matches);
      // @TODO: Parse is called often. Refactor so that valid ID is checked
      // when a video is added, but not every time the embedCode is parsed.
      if (isset($matches[1][0]) && $this->validId($matches[1][0])) {
        $uri = 'youtube://v/' . $matches[1][0];
        if (isset($matches[2][0]) && $this->validId($matches[2][0], 'l')) {
          $uri .= '/l/' . $matches[2][0];
        }
        return file_stream_wrapper_uri_normalize($uri);
      }
    }
  }

  public function claim($embedCode) {
    if ($this->parse($embedCode)) {
      return TRUE;
    }
  }

  public function getFileObject() {
    $uri = $this->parse($this->embedCode);
    $file = file_uri_to_object($uri, TRUE);

    // Try to default the file name to the video's title.
    if (empty($file->fid) && $info = $this->getOEmbed()) {
      $file->filename = truncate_utf8($info['title'], 255);
    }

    return $file;
  }

  /**
   * Returns information about the media.
   *
   * See http://www.oembed.com.
   *
   * @return
   *   If oEmbed information is available, an array containing 'title', 'type',
   *   'url', and other information as specified by the oEmbed standard.
   *   Otherwise, NULL.
   */
  public function getOEmbed() {
    $uri = $this->parse($this->embedCode);
    $external_url = file_create_url($uri);
    $oembed_url = url('https://www.youtube.com/oembed', array('query' => array('url' => $external_url, 'format' => 'json')));
    $response = drupal_http_request($oembed_url);

    if (!isset($response->error)) {
      return drupal_json_decode($response->data);
    }
    else {
      throw new Exception("Error Processing Request. (Error: {$response->code}, {$response->error})");
    }
  }

  /**
   * Check if a YouTube video ID is valid.
   *
   * @return boolean
   *   TRUE if the video ID is valid, or throws a
   *   MediaInternetValidationException otherwise.
   */
  public function validId($id, $type = 'v') {
    $uri = file_stream_wrapper_uri_normalize('youtube://' . $type . '/' . check_plain($id));
    $external_url = file_create_url($uri);
    $oembed_url = url('https://www.youtube.com/oembed', array('query' => array('url' => $external_url, 'format' => 'json')));
    $response = drupal_http_request($oembed_url);

    if (!isset($response->error)) {
      $data = drupal_json_decode($response->data);
      if (!empty($data)) {
        return TRUE;
      }
      else {
        $error_data = t('Unspecific');
        if (is_string($response->data)) {
          $error_data = $response->data;
        }
        throw new MediaInternetValidationException("The YouTube video ID is invalid, video was deleted or is disabled for embedding. Error: {$error_data}");
      }
    }
    elseif ($response->code == 401) {
      $message = t("There was an error, please check the video settings. Embedding, and playback on other websites, may have been disabled by the video owner. (Error: @code, @error)", ['@code' => $response->code, '@error' => $response->error]);
      throw new MediaInternetValidationException($message);
    }
    elseif ($response->code == 403) {
      $message = t("There was an error, please check the video settings. The video may be private, disabled or unavailable. (Error: @code, @error)", ['@code' => $response->code, '@error' => $response->error]);
      throw new MediaInternetValidationException($message);
    }
    else {
      $message = t("There was an error with this YouTube video. Please check the URL and video settings and try again. (Error: @code, @error)", ['@code' => $response->code, '@error' => $response->error]);
      throw new MediaInternetValidationException($message);
    }
  }
}
