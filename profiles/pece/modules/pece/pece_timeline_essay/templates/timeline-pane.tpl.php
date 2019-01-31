<div class="pece-timeline-pane">
  <div id='timeline-embed' style="width: 100%; height: 600px"></div>
  <script type="text/javascript">
    var timelineContent = { "events" : <?php print $events; ?> }
    , timeline = new TL.Timeline('timeline-embed', timelineContent,  <?php print $settings; ?>);
  </script>
</div>