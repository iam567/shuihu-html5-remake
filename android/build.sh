#!/bin/sh
# Builds android/build/Shuihu.apk without Gradle: the game (shuihu-html5/dist, minus the service worker) goes in as
# assets/www, the one activity is compiled with javac + d8, and the APK is aligned and signed.
# Needs a JDK 17 and an Android SDK with platforms;android-35 and build-tools;35.0.0:
#   JAVA_HOME (default ~/.local/opt/android-build/jdk/Contents/Home), ANDROID_SDK (default ~/.local/opt/android-build/sdk)
# Signing key: ANDROID_KEYSTORE (default ~/.config/shuihu/android-release.jks), password in ~/.config/shuihu/android.env
# (KEYSTORE_PASS=...). The key is created on the first run; keep it, or later builds will not install over earlier ones.
set -e
cd "$(dirname "$0")"
TOOLS=${TOOLS:-$HOME/.local/opt/android-build}
JAVA_HOME=${JAVA_HOME:-$TOOLS/jdk/Contents/Home}; SDK=${ANDROID_SDK:-$TOOLS/sdk}
BT=$SDK/build-tools/35.0.0; JAR=$SDK/platforms/android-35/android.jar
KEY=${ANDROID_KEYSTORE:-$HOME/.config/shuihu/android-release.jks}; ENV=$HOME/.config/shuihu/android.env
export PATH="$JAVA_HOME/bin:$PATH"
rm -rf build && mkdir -p build/gen build/classes build/dex build/www/www build/res
VERSION=$(sed -n "s/^const CACHE='shuihu-native-\(v[0-9]*\)'.*/\1/p" ../shuihu-html5/dist/sw.js); CODE=${VERSION#v}
rsync -a --exclude sw.js --exclude 'data/playthrough.json' ../shuihu-html5/dist/ build/www/www/
echo "$VERSION" > build/www/www/version.txt   # build number for the title screen
# Launcher icons from the iOS app icon
for d in mdpi:48 hdpi:72 xhdpi:96 xxhdpi:144 xxxhdpi:192; do
  mkdir -p build/res/mipmap-${d%%:*}
  sips -z ${d##*:} ${d##*:} -s format png ../ios/Shuihu/Shuihu/Assets.xcassets/AppIcon.appiconset/icon-1024.png --out build/res/mipmap-${d%%:*}/ic_launcher.png >/dev/null
done
sed -e "s/android:versionCode=\"[0-9]*\"/android:versionCode=\"$CODE\"/" -e "s/android:versionName=\"[^\"]*\"/android:versionName=\"1.0 ($VERSION)\"/" AndroidManifest.xml > build/AndroidManifest.xml
"$BT/aapt2" compile --dir build/res -o build/res.zip
"$BT/aapt2" link -I "$JAR" --manifest build/AndroidManifest.xml -R build/res.zip -A build/www --java build/gen \
  -0 webp -0 png -0 jpg -0 mp3 -0 ogg -0 m4a -0 woff2 -o build/unsigned.apk
javac -source 17 -target 17 -nowarn -classpath "$JAR" -d build/classes src/pro/areu/shuihu/*.java build/gen/pro/areu/shuihu/R.java
"$BT/d8" --release --min-api 24 --lib "$JAR" --output build/dex $(find build/classes -name '*.class')
(cd build/dex && zip -q ../unsigned.apk classes.dex)
"$BT/zipalign" -f -p 4 build/unsigned.apk build/aligned.apk
if [ ! -f "$KEY" ]; then
  mkdir -p "$(dirname "$KEY")"; PASS=$(openssl rand -hex 16); umask 077; echo "KEYSTORE_PASS=$PASS" > "$ENV"
  keytool -genkeypair -keystore "$KEY" -alias shuihu -keyalg RSA -keysize 4096 -validity 36500 -storepass "$PASS" -keypass "$PASS" -dname "CN=Shuihu" >/dev/null 2>&1
fi
. "$ENV"; export KEYSTORE_PASS
"$BT/apksigner" sign --ks "$KEY" --ks-key-alias shuihu --ks-pass env:KEYSTORE_PASS --out build/Shuihu.apk build/aligned.apk
"$BT/apksigner" verify build/Shuihu.apk && du -h build/Shuihu.apk
