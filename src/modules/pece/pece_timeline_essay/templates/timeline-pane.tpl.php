<!-- 1 -->
<link title="timeline-styles" rel="stylesheet" href="https://cdn.knightlab.com/libs/timeline3/latest/css/timeline.css">

<!-- 2 -->
<script src="https://cdn.knightlab.com/libs/timeline3/latest/js/timeline.js"></script>

<!-- 3 -->
<script type="text/javascript">
    var sampleJSON = {
        "title": {
            "media": {
                "url": "//www.flickr.com/photos/tm_10001/2310475988/",
                "caption": "Whitney Houston performing on her My Love is Your Love Tour in Hamburg.",
                "credit": "flickr/<a href='http://www.flickr.com/photos/tm_10001/'>tm_10001</a>"
            },
            "text": {
                "headline": "Whitney Houston<br/> 1963 - 2012",
                "text": "<p>Houston's voice caught the imagination of the world propelling her to superstardom at an early age becoming one of the most awarded performers of our time. This is a look into the amazing heights she achieved and her personal struggles with substance abuse and a tumultuous marriage.</p>"
            },
            "background": {
                "color": 'transparent'
            },
        },
        "events": [
            {
                "media": {
                    "url": "{{ static_url }}/img/examples/houston/family.jpg",
                    "caption": "Houston's mother and Gospel singer, Cissy Houston (left) and cousin Dionne Warwick.",
                    "credit": "Cissy Houston photo:<a href='http://www.flickr.com/photos/11447043@N00/418180903/'>Tom Marcello</a><br/><a href='http://commons.wikimedia.org/wiki/File%3ADionne_Warwick_television_special_1969.JPG'>Dionne Warwick: CBS Television via Wikimedia Commons</a>"
                },
                "start_date": {
                    "month": "8",
                    "day": "9",
                    "year": "1963"
                },
                "text": {
                    "headline": "A Musical Heritage",
                    "text": "<p>Born in New Jersey on August 9th, 1963, Houston grew up surrounded by the music business. Her mother is gospel singer Cissy Houston and her cousins are Dee Dee and Dionne Warwick.</p>"
                }
            },
            {
                "media": {
                    "url": "https://youtu.be/fSrO91XO1Ck",
                    "caption": "",
                    "credit": "<a href=\"http://unidiscmusic.com\">Unidisc Music</a>"
                },
                "start_date": {
                    "year": "1978"
                },
                "text": {
                    "headline": "First Recording",
                    "text": "At the age of 15 Houston was featured on Michael Zager's song, Life's a Party."
                }
            },
        ]
    };
</script>

<div class="pece-timeline-pane">
  <div id='timeline-embed' style="width: 100%; height: 600px"></div>
  <script type="text/javascript">
    var timelineContent = { "events" : <?php print $events; ?> }
    , timeline = new TL.Timeline('timeline-embed', timelineContent,  <?php print $settings; ?>);
  </script>
</div>