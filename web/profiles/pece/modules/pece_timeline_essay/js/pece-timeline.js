var timelineContent = JSON.parse(drupalSettings.slides);
window.timeline = new TL.Timeline('timeline-embed', timelineContent, drupalSettings.slideSettings);
