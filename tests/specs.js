describe('PECE', function () {

	it('shoudl have posts on front page', function () {

		browser.get('/');

		var title = element(by.css('div.content article h2'));
		expect(title.isDisplayed()).toBe(true);
	});
});