#!/usr/bin/env bash
# Generate a named replay trace from a Matrix-tests workload.
#
# Usage: scripts/gen_trace.sh <isa/xxx.c> <trace_name> [m k n]
#
#   <isa/xxx.c>   workload source, relative to Matrix-tests/
#   <trace_name>  output name -> tl-test-new-matrix/traces/<trace_name>.txt
#   [m k n]       optional matrix sizes written into configuration.ini before
#                 the build (the workload must read generated_matrix_config.h)
#
# Flow: rewrite [matrix] sizes -> run.sh -m (workload + rootfs + kernel +
# opensbi repack) -> run.sh -t (NEMU full-system run + addr.py) -> copy the
# trace under traces/ and print a size/op-type histogram.
set -euo pipefail

BASE=$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)
cd "$BASE"
# run.sh needs CROSS_COMPILE & co from env.sh (without it the kernel build
# silently falls back to the host gcc and dies on -mabi=lp64).
source ./env.sh

if [[ $# -ne 2 && $# -ne 5 ]]; then
    echo "usage: $0 <isa/xxx.c> <trace_name> [m k n]" >&2
    exit 2
fi
workload_src=$1   # e.g. isa/xs_share_pingpong.c
trace_name=$2

if [[ ! -f "Matrix-tests/$workload_src" ]]; then
    echo "error: Matrix-tests/$workload_src not found" >&2
    exit 2
fi

if [[ $# -eq 5 ]]; then
    m=$3; k=$4; narg=$5
    echo "********** set matrix size m=$m k=$k n=$narg **********"
    sed -i -E \
        -e "s/^[[:space:]]*m[[:space:]]*=.*/m = $m/" \
        -e "s/^[[:space:]]*k[[:space:]]*=.*/k = $k/" \
        -e "s/^[[:space:]]*n[[:space:]]*=.*/n = $narg/" \
        configuration.ini
fi

echo "********** build workload + fw_payload (MATRIX_WORKLOAD=$workload_src) **********"
MATRIX_WORKLOAD=$workload_src bash run.sh -m

echo "********** run NEMU + addr.py **********"
bash run.sh -t

mkdir -p tl-test-new-matrix/traces
trace_out=tl-test-new-matrix/traces/${trace_name}.txt
cp NEMU-Matrix/line_trace.txt "$trace_out"

echo "********** trace summary: $trace_out **********"
total=$(wc -l < "$trace_out")
echo "total lines: $total"
awk '$1 ~ /^(LD|ST|EV|IF|MR|MW|CR|FE)$/ {cnt[$1]++} END {for (t in cnt) printf "%6d %s\n", cnt[t], t}' \
    "$trace_out" | sort -rn
records=$(awk '$1 ~ /^(LD|ST|EV|IF|MR|MW|CR|FE)$/ {n++} END {print n+0}' "$trace_out")
if [[ "$records" -gt 40000 ]]; then
    echo "WARNING: $records replay records (>40000); consider shrinking sizes/passes to bound VCS sim time" >&2
fi
if [[ "$records" -eq 0 ]]; then
    echo "error: no replay records in trace — did the workload emit TRACE_DUMP/TRACE_END traps?" >&2
    exit 1
fi
echo "OK: $trace_name ($records records)"
