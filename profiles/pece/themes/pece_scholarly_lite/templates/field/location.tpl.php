<?php

/**
 * @file
 * Template for displaying single location.
 */
?>
<div class="location vcard" itemscope itemtype="http://schema.org/PostalAddress">
  <div class="adr">
    <?php if (!empty($name)): ?>
      <span class="fn" itemprop="name"><?php print $name; ?></span>
    <?php endif; ?>

    <?php if (!empty($street) || !empty($additional)): ?>
      <div class="street-address">
        <?php if (!empty($street)): ?>
          <span itemprop="streetAddress"><?php print $street; ?></span>
        <?php endif; ?>

        <?php if (!empty($additional)): ?>
          <span class="additional" itemprop="streetAddress"><?php print (!empty($street) ? ' - ' : '') . $additional; ?></span>
        <?php endif; ?>
      </div>
    <?php endif; ?>

    <?php if (!empty($city) || !empty($province)): ?>
      <?php if (!empty($city)): ?>
        <span class="locality" itemprop="addressLocality">
          <?php print $city . (!empty($province) ? ', ' : ''); ?>
        </span>
      <?php endif; ?>
      <?php if (!empty($province)): ?>
        <span class="region" itemprop="addressRegion"><?php print $province_print; ?></span>
      <?php endif; ?>
    <?php endif; ?>

    <?php if (!empty($postal_code)): ?>
      <div class="postal-code" itemprop="postalCode"><?php print $postal_code; ?></div>
    <?php endif; ?>

    <?php if (!empty($country_name)): ?>
      <div class="country-name" itemprop="addressCountry"><?php print $country_name; ?></div>
    <?php endif; ?>

    <?php if (!empty($email)): ?>
      <div class="email">
        <abbr class="type" title="email"><?php print t("Email address"); ?>:</abbr>
        <span><a href="mailto:<?php print $email; ?>" itemprop="email"><?php print $email; ?></a></span>
      </div>
    <?php endif; ?>
    <?php if (!empty($phone)): ?>
      <div class="tel">
        <abbr class="type" title="voice"><?php print t("Phone"); ?>:</abbr>
        <span class="value" itemprop="telephone"><?php print $phone; ?></span>
      </div>
    <?php endif; ?>
    <?php if (!empty($fax)): ?>
      <div class="tel">
        <abbr class="type" title="fax"><?php print t("Fax"); ?>:</abbr>
        <span itemprop="faxNumber"><?php print $fax; ?></span>
      </div>
    <?php endif; ?>
  </div>

  <?php if (!empty($map_link)): ?>
    <div class="map-link">
      <?php print $map_link; ?>
    </div>
  <?php endif; ?>
</div>
