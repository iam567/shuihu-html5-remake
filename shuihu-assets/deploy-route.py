from pathlib import Path
import shutil,datetime,subprocess,os
root=Path('/var/www/game-downloads/shz')
assert (root/'index.html').is_file()
for p in root.rglob('*'):p.chmod(0o755 if p.is_dir() else 0o644)
root.chmod(0o755)
p=Path('/etc/nginx/sites-enabled/game.areu.pro').resolve()
s=p.read_text();marker='    # Shuihu asset overview: original collection, generation is not enabled.\n'
if marker not in s:
 assert 'location ^~ /shz/' not in s and 'location = /shz ' not in s
 block='''    # Shuihu asset overview: original collection, generation is not enabled.
    location = /shz { return 301 /shz/; }
    location ^~ /shz/ {
        auth_basic "Rich4 private assets";
        auth_basic_user_file /etc/nginx/rich4-image.htpasswd;
        index index.html;
        try_files $uri $uri/ =404;
        add_header X-Robots-Tag "noindex, nofollow, noarchive" always;
        add_header Cache-Control "private, no-cache" always;
        add_header X-Content-Type-Options nosniff always;
    }

'''
 needle='    # Rich4 extracted original assets:'
 assert s.count(needle)==1
 backup=Path('/var/backups/shuihu-assets')/datetime.datetime.now(datetime.timezone.utc).strftime('%Y%m%dT%H%M%SZ');backup.mkdir(parents=True,exist_ok=True);shutil.copy2(p,backup/'nginx-game.areu.pro.conf')
 p.write_text(s.replace(needle,block+needle))
 check=subprocess.run(['nginx','-t'],capture_output=True,text=True)
 if check.returncode:
  p.write_text(s);print('Configuration check failed; original restored.');raise SystemExit(1)
 subprocess.run(['systemctl','reload','nginx'],check=True)
 print('Private /shz/ route installed; original routes preserved.')
else:print('Private route already installed.')
