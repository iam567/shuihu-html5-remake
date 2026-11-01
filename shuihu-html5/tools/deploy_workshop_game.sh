#!/bin/bash
# Publish dist/ for play-testing at https://game.areu.pro/shz/game/ (same password as the asset workshop).
# Only the game/ folder is replaced; the workshop next to it is untouched.
# Environment: SHUIHU_GAME_TARGET (default root@130.94.65.16:/var/www/game-downloads/shz/game)
set -euo pipefail
TARGET="${SHUIHU_GAME_TARGET:-root@130.94.65.16:/var/www/game-downloads/shz/game}"
HOST="${TARGET%%:*}";DIR="${TARGET#*:}"
cd "$(dirname "$0")/.."
ssh -o BatchMode=yes "$HOST" "mkdir -p '$DIR'"
rsync -a --delete --no-owner --no-group -e 'ssh -o BatchMode=yes' dist/ "$TARGET/"
ssh -o BatchMode=yes "$HOST" "chown -R 501:staff '$DIR' && du -sh '$DIR'"
