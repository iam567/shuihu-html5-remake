#!/bin/sh
# Copies the HTML5 build into the app bundle's www folder (no service worker needed inside the app).
cd "$(dirname "$0")" && rsync -a --delete --exclude sw.js --exclude 'data/playthrough.json' ../../shuihu-html5/dist/ Shuihu/www/ &&
  sed -n "s/^const CACHE='shuihu-native-\(v[0-9]*\)'.*/\1/p" ../../shuihu-html5/dist/sw.js > Shuihu/www/version.txt &&   # build number for the title screen
  du -sh Shuihu/www
