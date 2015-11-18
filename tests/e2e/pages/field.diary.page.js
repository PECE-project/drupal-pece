/**
* @file field.diary.page.js
*/

var FieldDiaryPage = function() {

  this.emptyResult = $('.view-pece-group-field-diary .view-empty');

  this.get = function (url) {
    browser.get(url);
  };

};

module.exports = new FieldDiaryPage();
