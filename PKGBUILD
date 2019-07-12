pkgname=nsopen
pkgver=1
pkgrel=1
pkgdesc='Intelligent and suckless replacement for xdg-open'
arch=('any')
url=''
license=('WTFPL')
source=('nsopen')

# Set this 1 to symlink /usr/bin/open to /usr/bin/xdg-open
# and conflict with xdg-utils
PROVIDE_XDG_OPEN=1

if [ $PROVIDE_XDG_OPEN -eq 1 ]; then
   provides=('xdg-utils')
   conflicts=('xdg-utils')
fi

package() {
   install -Dm755 "$srcdir/nsopen" "${pkgdir}/usr/bin/nsopen"

   if [ $PROVIDE_XDG_OPEN -eq 1 ]; then
      ln -s "/usr/bin/nsopen" "$pkgdir/usr/bin/xdg-open"
   fi
}

# vim: set ts=8 sw=3 tw=0 :
md5sums=('655479704058814f99f8e55ce8b8fd6d')
