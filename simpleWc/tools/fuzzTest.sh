#!/bin/sh
set -eu

BIN=${1:-./simpleWc/simplewc}

if [ ! -x "$BIN" ]; then
  echo "Binary not found/executable: $BIN"
  exit 1
fi

TMPDIR=$(mktemp -d)
cleanup() { rm -rf "$TMPDIR"; }
trap cleanup EXIT

echo "== Functional tests (compare with system wc) =="

make_file() {
  name="$1"
  content="$2"
  printf "%s" "$content" > "$TMPDIR/$name"
}

make_file f1 ""
make_file f2 "hello world\n"
make_file f3 "one two"
make_file f4 "a  b\n\tc\n\n"
make_file f5 "   \t  \n"
make_file f6 "punct,uation!!  ok\nnext"

for f in "$TMPDIR"/f*; do
  # our program output: L W B filename
  ours=$("$BIN" "$f" | awk '{print $1,$2,$3}')
  sys=$(wc "$f" | awk '{print $1,$2,$3}')

  if [ "$ours" != "$sys" ]; then
    echo "Mismatch on $f"
    echo "  ours: $ours"
    echo "  sys : $sys"
    exit 1
  fi
done

echo "Functional tests OK."

echo "== Fuzz tests (random files + weird args) =="

# fuzz: random file contents
i=1
while [ $i -le 50 ]; do
  f="$TMPDIR/rand_$i.bin"
  # create random file between 0 and 2048 bytes
  n=$((RANDOM % 2049))
  head -c "$n" /dev/urandom > "$f"

  "$BIN" "$f" >/dev/null 2>&1 || {
    echo "Crash/fail on random file: $f (size=$n)"
    exit 1
  }
  i=$((i+1))
done

# fuzz: weird arguments (should not crash)
"$BIN" >/dev/null 2>&1 || true
"$BIN" --help >/dev/null 2>&1 || true
"$BIN" -h >/dev/null 2>&1 || true
"$BIN" "" >/dev/null 2>&1 || true
"$BIN" "does_not_exist_123.txt" >/dev/null 2>&1 || true

echo "Fuzz tests OK."
echo "ALL OK"
