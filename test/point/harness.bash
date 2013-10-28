set -ex

ARCHIVE="$(awk '/^__ARCHIVE_BELOW__/ {print NR + 1; exit 0; }' $0)"
I="$(tail -n+$ARCHIVE $0 | head -n1)"
O="$(tail -n+$ARCHIVE $0 | tail -n1)"

out="$($PTEST_BINARY $I)"

if [[ "$out" != "$O" ]]
then
    exit 1
fi

exit 0
__ARCHIVE_BELOW__
