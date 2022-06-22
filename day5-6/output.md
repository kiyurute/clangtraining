t.nakajima@fb13538-t-nakajima CLangPractice % brew tap LouisBrunner/valgrind                    
Running `brew update --auto-update`...
==> Auto-updated Homebrew!
Updated 2 taps (homebrew/core and homebrew/cask).

You have 1 outdated cask installed.
You can upgrade it with brew upgrade
or list it with brew outdated.

t.nakajima@fb13538-t-nakajima CLangPractice % brew install --HEAD LouisBrunner/valgrind/valgrind
==> Cloning https://github.com/LouisBrunner/valgrind-macos.git
Updating /Users/t.nakajima/Library/Caches/Homebrew/valgrind--git
==> Checking out branch master
Already on 'master'
Your branch is up to date with 'origin/master'.
HEAD is now at 6ff08b6e3 fix: disable pth_mutex_signal on macOS (#50)
==> Installing valgrind from louisbrunner/valgrind
==> ./autogen.sh
==> ./configure --prefix=/opt/homebrew/Cellar/valgrind/HEAD-6ff08b6 --enable-only64bit --build=amd64-darwin
Last 15 lines from /Users/t.nakajima/Library/Logs/Homebrew/valgrind/02.configure:
checking for perl... /usr/bin/perl
checking for gdb... /no/gdb/was/found/at/configure/time
checking dependency style of clang... none
checking for diff -u... yes
checking for xcrun... yes
checking for Xcode SDK and includes... /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk (includes: /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include)
checking for a supported version of gcc... ok (Apple LLVM version 13.1.6)
checking build system type... x86_64-pc-darwin
checking host system type... x86_64-pc-darwin
checking for a supported CPU... ok (x86_64)
checking for a 64-bit only build... yes
checking for a 32-bit only build... no
checking for a supported OS... ok (darwin)
checking for the kernel version... unsupported (21.4.0)
configure: error: Valgrind works on Darwin 10.x-20.x (Mac OS X 10.6-10.11 and macOS 10.12-11.0)

If reporting this issue please do so at (not Homebrew/brew or Homebrew/core):
  https://github.com/louisbrunner/homebrew-valgrind/issues

These open issues may also help:
Trying to download valgrind on macOS Catalina 10.15.3 and getting 2 errors https://github.com/LouisBrunner/homebrew-valgrind/issues/4
Please create pull requests instead of asking for help on Homebrew's GitHub,
Twitter or any other official channels.