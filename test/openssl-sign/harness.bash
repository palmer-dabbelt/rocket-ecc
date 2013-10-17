set -ex

CURVE="p256k1"
DIGEST="6b5dfcd5031a5fd18d9298421dfcf2da5320bea8524b26d2ca1419777207f2ea"
R="D40A527776011221FE2508454EA01208879893C5884C1490B6144FFDA540E93E"
S="E31D3B5D9C141338DA6AEA8C56500D82E3D1E995EC166FFE0A60F8E5B628FB08"

function verify()
{
    out="$($PTEST_BINARY --curve $CURVE --digest $DIGEST)"
    echo $out

    r="$(echo "$out" | grep "^--r" | cut -d' ' -f2)"
    s="$(echo "$out" | grep "^--s" | cut -d' ' -f2)"

    if [[ "$r" != "$R" ]]
    then
        exit 1
    fi

    if [[ "$s" != "$S" ]]
    then
        exit 1
    fi
}

trap verify EXIT
