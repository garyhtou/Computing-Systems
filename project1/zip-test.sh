echo "=== MAKE ==="
eval "make"
echo

echo "[wzip] zipping..."
eval "./wzip $1 > $1.zip"
echo

echo "[wunzip] unzipping..."
eval "./wunzip $1.zip > $1.unzip"
echo

echo "=== BIN '$1' ==="
eval "xxd -b -c 5 $1.zip"
echo

echo "=== BIN '$1.unzip' ==="
eval "xxd -b -c 5 $1.unzip"
echo

echo "=== COMPARING ==="
eval "diff $1 $1.unzip"
DIFF=$(diff $1 $1.unzip)
if [ "$DIFF" == "" ]; then
	echo "they're the same!"
fi
