function loadHext()
{
  try
  {
    return require('hext');
  }
  catch( e )
  {
    return require('./../../index.js');
  }
}

const hext = loadHext();

test('extracts', () => {
  const html = new hext.Html(
    '<a href="one.html">  <img src="one.jpg" />  </a>' +
    '<a href="two.html">  <img src="two.jpg" />  </a>' +
    '<a href="three.html"><img src="three.jpg" />' +
                         '<img src="three-1.jpg" /></a>');

  const rule = new hext.Rule('<a href:link>' +
                             '  <img src:image />' +
                             '</a>');

  expect(rule.extract(html)).toEqual([
    {"image": "one.jpg", "link": "one.html"},
    {"image": "two.jpg", "link": "two.html"},
    {"image": ["three.jpg", "three-1.jpg"], "link": "three.html"}]);
});

test('throws on wrong argument types', () => {
  expect(() => new hext.Html({})).toThrow();
  expect(() => new hext.Rule({})).toThrow();
  const rule = new hext.Rule('<a />');
  expect(() => rule.extract({})).toThrow();
});

test('hext.Rule throws syntax error', () => {
  expect(() => new hext.Rule('<a')).toThrow();
});

test('matches and extracts utf8', () => {
  const html = new hext.Html('<html><body>💩</body></html>');
  const rule = new hext.Rule('<body @text="💩" @text:x />');
  expect(rule.extract(html)).toEqual([{"x": "💩"}]);
});

test('hext.Rule.extract max_searches throws', () => {
  const html = new hext.Html(
    '<html><body><div><span><span></span></span></div></body></html>');
  const rule = new hext.Rule('<*>{<*>{<*/>}</*>}</*>');
  expect(() => rule.extract(html, 1)).toThrow();
});

