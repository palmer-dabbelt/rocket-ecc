set -ex

CURVE="p256k1"

function verify()
{
    out="$($PTEST_BINARY --curve $CURVE --pubkey $PUBKEY --privkey $PRIVKEY --digest $DIGEST --r $R --s $S)"

    if [[ "$out" != "$RESULT" ]]
    then
        exit 1
    else
        exit 0
    fi
}

trap verify EXIT
