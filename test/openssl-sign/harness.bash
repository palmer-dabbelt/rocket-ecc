set -ex

CURVE="p256k1"

function verify()
{
    out="$($PTEST_BINARY --curve $CURVE --pubkey $PUBKEY --privkey $PRIVKEY --digest $DIGEST --rp $RP --kinv $KINV)"
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
