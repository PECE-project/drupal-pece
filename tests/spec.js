// Not an AngularJS environment.
browser.ignoreSynchronization = true;

describe('PECE', function () {

  it('shoudl have posts on front page', function () {

    browser.get('/');

    var title = element.all(by.css('div.content article h2')).first();
    expect(title.isDisplayed()).toBe(true);
  });
});