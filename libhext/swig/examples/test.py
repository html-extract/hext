import pyhext
import urllib

hext = '''\
<article class="item" data-model-id={article_id}
  <div class="item-category-info"
    <span @text={publish_time}
    <a href={category_href}
  <div class="image-container"
    <a
      <img src={image}
  <div class="item-meta-information grid"
    <span class="author" @text={author}
      <?a href={author_href}
  <h2
    <a href={href} @text={heading}
  <p class="item-description" @text={teaser}
'''

url = "http://www.vice.com/en_us"
html = urllib.urlopen(url).read();

h = pyhext.Hext(hext)
result = h.extract(html)

for map in result:
    for key in map:
        print "%s: %s" % (key, map[key])
    print "-------------------------------------------------------"


