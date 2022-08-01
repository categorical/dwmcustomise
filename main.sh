#!/bin/bash
set -euo pipefail

thisdir="$(cd "$(dirname "$0")"&&pwd)"
releaseid="$(sed -n 's/^ID=//p' '/etc/os-release')"

_copysource(){ local d="$1"
    _action(){ tar xzf "$1" -C "$d" --strip-components=1;}
    _withdist '_action'
}
_copydist(){ local d="$1"
    _action(){ install -m644 -t "$d" "$1";}
    _withdist '_action'
}
_withdist(){ local action=$1
    (cd "$thisdir"&&make dist)        
    local f;f="$(find "$thisdir" -maxdepth 1 -type f -name 'dwm-*.tar.gz'|head -n1)"
    declare -F $action >/dev/null&&$action "$f"
    (cd "$thisdir"&&make clean)
}

_devel(){
    pushd "$thisdir" &>/dev/null
    trap 'popd>/dev/null;trap - RETURN' RETURN
    local stage="$thisdir/stage"
    local prefix='/usr/local'
    [ -d "$stage" ]&&(set -x;rm -r "$stage")
    make
    DESTDIR="$stage" make install PREFIX="$prefix"
    make clean
}
_develupdate(){
    local pkgname='dwm'
    if [ "$releaseid" = 'arch' ];then
        pacman -Q $pkgname &>/dev/null \
            &&sudo pacman --noconfirm -Rns $pkgname
        local f="$HOME/devel/xcustomise/machine/$HOSTNAME/packages.sh"
        "$f" --aur -c $pkgname
        "$f" --aur -s $pkgname
    elif [ "$releaseid" = 'slackware' ];then
        local f="$HOME/devel/slackwarepkg/main.sh"
        "$f" "-oi$pkgname"
        pkill -f '/usr/bin/dwm' 
    fi
}
_setdwm(){
    local f='/usr/local/bin/dwm'
    sudo install -Tm755 /dev/null "$f"
    cat<<-EOF|sudo tee "$f">/dev/null
	#!/bin/bash
	while :;do /usr/bin/dwm &>"\$HOME/.dwmlog";done
	EOF
}

_main(){ _usage(){ cat<<-EOF
	SYNOPSIS
	    $0 --copysource|--copydist directory
	EOF
    exit $1;}
    [ $# -gt 0 ]||_usage 1;while [ $# -gt 0 ];do case $1 in
        --copysource)_copysource "$2";break;;
        --copydist)_copydist "$2";break;;
        --setdwm)_setdwm;break;;
        --devel)_devel "$@";break;;
        -u)_develupdate;break;;
        -h)_usage 0;;*)_usage 1;;
    esac;shift;done
};_main "$@"
