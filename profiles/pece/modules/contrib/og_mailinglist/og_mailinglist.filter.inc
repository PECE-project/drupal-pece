<?php
/**
 * @file
 * OG Mailinglist filter to remove or hide quotes in emails.
 **/

require_once 'og_mailinglist_common.inc';

/**
 * Implements hook_filter_info().
 */
function og_mailinglist_filter_info() {
  $filters['filter_email_quote_hider'] = array(
    'title' => t('Hide quotations in emails'),
    'description' => t('Finds quoted text from comments created via email and adds Show / Hide link. This works only when it is followed with "Limit allowed HTML" tags filter, which needs to have div, p and br tags allowed.'),
    'process callback' => '_og_mailinglist_filter_quotes',
    'tips callback' => '_og_mailinglist_filter_tips',
    'settings callback' => '_og_mailinglist_filter_settings',
    'default settings' => array(
      'og_mailinglist_filter_quotations' => 'hidden',
      'og_mailinglist_filter_quotations_length' => '2',
      'og_mailinglist_filter_email' => 1,
      'og_mailinglist_filter_footer' => 1,
    ),
  );
  return $filters;
}

function _og_mailinglist_filter_settings($form, &$form_state, $filter, $format, $defaults) {
  $filter->settings += $defaults;

  $settings['og_mailinglist_filter_quotations'] = array(
    '#title' => t('Quotations style'),
    '#type' => 'radios',
    '#options' => array(
      'hidden' => t('Quotations will be hidden with a JavaScript "Show" link. (default)'),
      'removed' => t('Quotations will be removed altogether.'),
    ),
    '#default_value' => $filter->settings['og_mailinglist_filter_quotations'],
    '#description' => t('E-mail style quotations are lines starting with ">" marks.'),
  );
  $settings['og_mailinglist_filter_quotations_length'] = array(
    '#title' => t('Quotations\' minimum length'),
    '#type' => 'textfield',
    '#default_value' => $filter->settings['og_mailinglist_filter_quotations_length'],
    '#description' => t('Only quotations with more lines than specified value will be removed or hidden. Shorter quotations are either shown or not hidden by default. Default is 2. Values less than 2 are treated as 2.'),
  );
  $settings['og_mailinglist_filter_email'] = array(
    '#title' => t('Hide email addresses.'),
    '#type' => 'checkbox',
    '#default_value' => $filter->settings['og_mailinglist_filter_email'],
    '#description' => t('If checked, email addresses will be replaced with ***@***.*** (enabled by default)'),
  );
  $settings['og_mailinglist_filter_footer'] = array(
    '#title' => t('Remove mailinglist footer.'),
    '#type' => 'checkbox',
    '#default_value' => $filter->settings['og_mailinglist_filter_footer'],
    '#description' => t('If checked, mailinglist footer will be removed from the output.'),
  );
  return $settings;
}

function _og_mailinglist_filter_tips($filter, $format, $long = FALSE) {
  if ($long) {
    $output = t('Email quotation hider hides all quotations by default and provides a link to show quoted text.');
    $output .= '<br />';
    $output .= t('It also replaces all e-mail addresses with ***@***.***');
    return $output;
  }
  else {
    return t('Email quotation hider makes quotations in emails hidden by default and replaces all email addresses with ***@***.***');
  }
}

function _og_mailinglist_remove_quotes($text) {
  $filter = new stdClass();
  $filter->settings['og_mailinglist_filter_quotations'] = 'removed';
  $filter->settings['og_mailinglist_filter_quotations_length'] = 2;
  $filter->settings['og_mailinglist_filter_footer'] = 1;
  // Don't remove emails.
  $filter->settings['og_mailinglist_filter_email'] = 0;

  return _og_mailinglist_filter_quotes($text, $filter);
}

/**
 * Surround quotes within an email text to make the text hidden by default.
 * Or remove quotes entirely.
 *
 * @param string $text
 *  Text where to hide or remove quotes.
 *
 * @param $filter
 *  Filter passes on e.g settings.
 *
 * @return
 *  Text with hidden or removed quotes, contains HTML tags <div><br><p>.
 */
function _og_mailinglist_filter_quotes($text, $filter) {
  // Fetch settings.
  $filter_type = $filter->settings['og_mailinglist_filter_quotations'];
  $quote_min_length = max(2, $filter->settings['og_mailinglist_filter_quotations_length']);

  // Replace legacy operating systems' line break characters.
  $text = str_replace(array("\r\n", "\r"), "\n", $text);
  $lines = explode("\n", $text);

  // Remove footer.
  if ($filter->settings['og_mailinglist_filter_footer'] == 1) {
    $start = $end = -1;
    foreach ($lines as $line_number => $line) {
      // We assume that all footers start with > -- characters
      // and will continue with any number of lines which have server address.
      if ($start != -1) {
        if (stripos($line, og_mailinglist_server()) != -1) {
          $end = $line_number;
        }
        else {
          break;
        }
      }

      if (substr($line, 0, 4) == '> --' or substr($line, 0, 7) == '&gt; --') {
        $start = $end = $line_number;
      }
    }

    // Remove footer lines if at least two lines are found.
    if ($start != -1 and $end - $start + 1 >= 2) {
      for ($i = $end; $i >= $start; $i--) {
        unset($lines[$i]);
      }
    }
  }

  // This value is used to determine if quoted section can be relied on.
  // If not, then we rather will not remove the section but hide it as
  // usual. Such a behaviour might be surprising to some. Maybe needs fixing.
  $valid_quotes = TRUE;
  // Find the quotes.
  $quote_ranges = _og_mailinglist_find_quoted_sections($lines);
  if (empty($quote_ranges)) {
    $quote_ranges = _og_mailinglist_find_unusual_quoted_sections($lines);
    $valid_quotes = FALSE;
  }

  $current_line = 0;
  $text = '';

  // We expect quote_ranges to be non-overlapping and sorted.
  foreach ($quote_ranges as $quote) {
    $start = $quote['start'];
    $end = $quote['end'];
    $quote_length = $end - $start + 1;

    // First we append text before the quote.
    // Run the quote through the Line break filter before replacing it in the text.
    // Otherwise the HTML Converter input filter will bork the HTML. This *could* be a
    // potential problem if someone doesn't want the Line Break filter run.
    $text .= _filter_autop(implode("\n", array_slice($lines, $current_line, $start - 1)));

    // Now we prepare the text inside the quote.
    $quote_text = _filter_autop(implode("\n", array_slice($lines, $start, $end)));

    // This quote is not long enough.
    if ($quote_length < $quote_min_length) {
      if ($filter_type == 'hidden') {
        $text .= '<div class="quoted-text visible">' . $quote_text . '</div>';
      }
      else {
        $text .= $quote_text;
      }
    }
    // This is normal size quote.
    else {
      if ($filter_type == 'removed' and $valid_quotes) {
        // We do nothing
      }
      else {
        $text .= '<div class="toggle-quoted-text">'
          . t('- Show quoted text -') . '</div>'
          . '<div class="quoted-text hidden">' . $quote_text . '</div>';
      }
    }
  }

  // Now we append any text after the last quote.
  $text .= _filter_autop(implode("\n", array_slice($lines, $end + 1)));

  // Remove email addresses, if needed.
  if ($filter->settings['og_mailinglist_filter_email'] == 1) {
    // Regex borrowed from valid_email_address().
    $regex = "([a-zA-Z0-9_\-\.\+\^!#\$%&*+\/\=\?\`\|\{\}~\']+@(?:(?:[a-zA-Z0-9]|[a-zA-Z0-9][a-zA-Z0-9\-]*[a-zA-Z0-9])\.?)+)";
    $text = preg_replace($regex, '***@***.***', $text);
  }

  return $text;
}

/**
 * Loops through the text line by line and tries to determine which lines are
 * quoted. If no '>' is found at start of line, then it is considered as
 * email from bad client and it searches for special title lines. If one is
 * found, everything starting for that one is considered a quote.
 * This assumes that people with bad email clients tend to top-post as well.
 */
function _og_mailinglist_find_quoted_sections(&$lines) {
  $quotes = array();
  $in_quote = FALSE;
  $start = $end = NULL;

  foreach ($lines as $line_number => $line) {
    if (!$in_quote and substr(ltrim($line), 0, 1) == '>') {
      $in_quote = TRUE;
      $start = $end = $line_number;
    }
    elseif ($in_quote and (
      substr(ltrim($line), 0, 1) == '>'
      // An empty line does not break a quote.
      || trim($line) == ''
      // Email address is brought down to the next line so < starts the line.
      || substr(trim($line), 0, 1) == '<'
      // Long email addresses sometimes get truncated leaving the second part
      // of the line on the next line. See if previous line ended with a "<".
      || ($line_number > 1 and substr(trim($lines[$line_number-1]), -1) == "<")
      )) {
      // Do nothing. We are still in a quote.
    }
    elseif ($in_quote) {
      $quotes[] = array('start' => $start, 'end' => $line_number - 1);
      $in_quote = FALSE;
      $start = NULL;
    }
  }
  if ($start !== NULL) {
    $quotes[] = array('start' => $start, 'end' => $line_number);
  }

  // If the line before usual > quote range is title/reference line,
  // then include that line into quote as well.
  foreach ($quotes as $key => $range) {
    $new_start = _og_mailinglist_check_quote_start($lines, $range['start']);
    if ($new_start !== NULL) {
      $quotes[$key]['start'] = $new_start;
    }
  }
  return $quotes;
}

function _og_mailinglist_check_quote_start(&$lines, $start) {
  if ($start == 0) {
    return NULL;
  }
  $new_start = $start - 1;
  $text = trim($lines[$new_start]);
  // If text is less than 10 characters, then it might be split
  // and we add one more line.
  if (strlen($text) < 10 and $start >= 2) {
    $new_start--;
    $text = trim($lines[$new_start]) . ' ' . $text;
  }

  $is_title = 0;
  // Count all digits in the string
  preg_match_all('/[0-9]/', $text, $match);
  $is_title += (count($match [0]) > 4) ? 0.1 : 0;
  // If the line contains time.
  preg_match('/[0-9]{1,2}:[0-9]{2}/', $text, $match);
  $is_title += (!empty($match)) ? 0.2 : 0;
  // If the line contains date.
  preg_match('/[0-9]{2,4}[.\/][0-9]{2,4}/', $text, $match);
  $is_title += (!empty($match)) ? 0.2 : 0;
  // Starts with 'On ' or contains 'wrote'. Sorry, non-english speakers.
  $is_title += (strtolower(substr($text, 0, 3)) == 'on ') ? 0.2 : 0;
  $is_title += (strpos($text, 'wrote') != -1) ? 0.1 : 0;
  // Whether the line ends with colon.
  $is_title += (substr($text, -1) == ':') ? 0.2 : 0;

  // Let's see, if it looks enough like a title.
  if ($is_title >= 0.5 ) {
    return $new_start;
  }
  return NULL;
}

/**
 * Go over lines array line by line and determine if that line might start
 * a quoted section.
 */
function _og_mailinglist_find_unusual_quoted_sections(&$lines) {
  // These are starting lines for quotes which need special treatment, since
  // these clients do not place > marks to starting lines inside quote.
  // Boo for any listed client.
  $unusual_quote_starting = array(
    // hotmail.com
    "/Date:\s\w{3},\s\d{1,2}\s\w{3}\s\d{4}\s\d{2}:\d{2}:\d{2}\s-\d{4}.Subject:\s.*?From:.*?To:\s.*/s",
    "/From:\s\w+\s\w+.+?\[mailto:\w+.+?Sent:\s\w+,\s\w+\s\d{2},\s\d{4}\s\d{1,2}:\d{1,2}\s[AM|PM]+.To:\s.+?Subject:\s.*/s",
    // Android's GMail client
    "/On\s\w{3}\s\d{1,2},\s\d{4}\s\d{1,2}:\d{2}\s[PM|AM]+,\s.*/s",
    // something other
    "/From:\s\".*?\"\s<.*?@.*?>.Date:\s\w{3},.*?To:.*?<.*?@.*?>.*?Cc:\s.*?<.*?@.*?>.*?Subject:.*/s",
    "/From:\s.*?<.*?@.*?>.To:.*?@.*?Sent:\s\w{3},\s.*?\d{1,2},\s\d{4}\s.*?Subject:\s.*/s",
    "/From:\s.*?\[.*?@.*?\].*?Sent:\s\w*?,\s\w*?\s\d{1,2},\s\d{4}\s\d{1,2}:\d{2}\s(PM|AM).*?To:\s.*?Subject:.*/s",
    "/From:\s.*?\[.*?@.*?\].*?Sent:\s\w*?,\s\d{1,2}\s\w*?\s\d{4}\s\d{1,2}:\d{2}\s(PM|AM).*?To:\s.*?Subject:.*/s",
    "/-----Original\sMessage-----.*?From:\s.*?@.*?Date:\s\w{3},\s\d{1,2}\s.*?:.*?:.*?To:.*?@.*?Subject:.*/s",
    "/-----Original\sMessage-----.*?From:\s.*?@.*?Sent:\s\w{3,9},\s\d{1,2}\s.*?:.*?:.*?To:.*?@.*?Subject:.*/s",
    "/-----\sOriginal\sMessage\s-----.*?From:\s.*?\<.*?@.*?\>.*?To:\s.*?Subject:\s.*?Date:\s\w*?,\s\d{1,2}\s\w*?\s\d{4}\s\d{1,2}:\d{2}:\d{2}\s.*/s",
    "/On\s\d{1,2}\s\w.*?\s\d{4}\s\d{2}:\d{2},\s.*?@.*?\s.*?wrote:.*/s",
  );

  $quotes = array();
  foreach ($lines as $line_number => $line) {
    foreach ($unusual_quote_starting as $regex) {
      preg_match($regex, $line, $matches);
      if (!empty($matches)) {
        $quotes[] = array('start' => $line_number, 'end' => count($lines) - 1);
        return $quotes;
      }
    }
  }

  // If still no quotes, search for Outlook 14.0 style stupid ones,
  // e.g starting with the following:
  // From: Shai [mailto:shai@example.com]
  // Sent: Wednesday, March 06, 2013 7:46 PM
  // To: John Smith
  // Subject: Re: [meta] silly thought
  if (empty($quotes)) {
    foreach ($lines as $line_number => $line) {
      if (preg_match('/^\s*From\:/', $line)
	      and count($lines) > $line_number + 3
        and preg_match('/^\s*Sent\:/', $lines[$line_number + 1])
		    and preg_match('/^\s*To\:/', $lines[$line_number + 2])
		    and preg_match('/^\s*Subject\:/', $lines[$line_number + 3])
        and $line_number != 0
        ) {
        // A quote starts here.
        $quotes[] = array('start' => $line_number, 'end' => count($lines) - 1);
      }
    }
  }

  return $quotes;
}
