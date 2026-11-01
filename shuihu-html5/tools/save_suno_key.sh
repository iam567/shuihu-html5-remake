#!/bin/sh
# Asks for the sunoapi.org key without echoing it and stores it in ~/.config/shuihu/suno.env (mode 600).
# The music tools read SUNO_API_KEY from that file; the key never appears in the project or in logs.
mkdir -p "$HOME/.config/shuihu" && chmod 700 "$HOME/.config/shuihu"
printf '粘贴 sunoapi.org 的 API 密钥后按回车（输入时不显示）：'
stty -echo; IFS= read -r key; stty echo; echo
[ -n "$key" ] || { echo '没有输入，未保存。'; exit 1; }
umask 077; printf 'SUNO_API_KEY=%s\n' "$key" > "$HOME/.config/shuihu/suno.env"
echo '已保存到 ~/.config/shuihu/suno.env（仅本账户可读）。可以关闭这个窗口了。'
