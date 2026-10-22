mkdir -p build
FILE="$1"
# Our template has "#define int long long", so system headers that a file
# needs (pb_ds, cassert) must come first, as they would in a real solution.
echo "
#include <bits/extc++.h>
#include <cassert>
#include \"../content/contest/template.cpp\"
#include \"../$FILE\"
" >build/temp.cpp
g++ -Wall -Wextra -Wfatal-errors -Wconversion -std=c++17 build/temp.cpp && rm a.out build/temp.cpp
