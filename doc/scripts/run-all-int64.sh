#!/usr/bin/env bash
# Runs all stress tests as if pasted under our contest template, i.e. with
# "#define int long long" after the includes and "int32_t main".
# Works on a temporary copy; the repository is not modified.
DIR=$(cd "${1:-.}" && pwd)
TMP=$(mktemp -d)
trap "rm -rf $TMP" EXIT
cp -r "$DIR/content" "$DIR/stress-tests" "$TMP/"
cd "$TMP"
# define int after the system includes of every test entry point
sed -i 's/^#include <cassert>$/#include <cassert>\n#include <bits\/extc++.h>\n#define int long long/' \
	stress-tests/utilities/template.h stress-tests/geometry/insidePolygon.cpp \
	stress-tests/geometry/PolygonUnion.cpp
grep -rlE '\bint main *\(' stress-tests | xargs sed -i -E 's/\bint main *\(/int32_t main(/'
ulimit -s 524288 # For 2-sat test
declare -i pass=0 fail=0
failTests=""
# MaximumClique is not in the notebook and does not support int = long long
for test in $(find stress-tests -name '*.cpp' | grep -v MaximumClique | sort); do
	echo "$(basename $test): "
	if g++ -std=c++17 -O2 -w -o a.out "$test" && ./a.out; then
		pass+=1
	else
		echo "Failed"; fail+=1; failTests="$failTests$test\n"
	fi
	rm -f a.out
done
echo "$pass/$(($pass+$fail)) tests passed with #define int long long"
if (($fail == 0)); then exit 0; fi
echo -e "These tests failed: \n $failTests"
exit 1
