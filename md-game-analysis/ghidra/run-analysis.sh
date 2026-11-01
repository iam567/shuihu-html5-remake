#!/bin/sh
set -eu
export JAVA_HOME="/Users/taoo/.local/share/rea-engines/jdk-21.0.13+9/Contents/Home"
export GHIDRA_INSTALL_DIR="/Users/taoo/.local/share/rea-engines/ghidra_12.1.4_PUBLIC"
TASK_DIR="/Users/taoo/Documents/ChatGPT/日常/md-game-analysis/ghidra"
mkdir -p "$TASK_DIR/project"
"$GHIDRA_INSTALL_DIR/support/analyzeHeadless" "$TASK_DIR/project" Shuihu -import "/Users/taoo/Documents/ChatGPT/日常/md-game-analysis/ghidra/shuihu-baseline.bin" -loader BinaryLoader -processor 68000:BE:32:default -cspec default -loader-baseAddr 0 -scriptPath "$TASK_DIR" -preScript PrepareMegaDrive.java -postScript ExportMegaDrive.java "$TASK_DIR" -analysisTimeoutPerFile 600 -max-cpu 4
