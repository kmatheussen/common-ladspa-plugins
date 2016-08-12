# common-ladspa-plugins

Ideally, it should be enough to write './build_all.sh', but you might want to edit some scripts to make it work.
Anyhow, running ./build_all.sh is supposed to compile the most common LADSPA plugins for linux64, mingw64, mingw32,
and darwin64. You need cross compilers from mxe (http://mxe.cc) and osxcross (https://github.com/tpoechtrager/osxcross).


The calf, caps, cmt and swh plugins are copied from lmms (https://lmms.io/), and the build_lmms.sh
script also uses the lmms' building environment to build these plugins.


The kokkinizita plugins (made by Fons Adriaensen) are copied from http://kokkinizita.linuxaudio.org.


The TAP plugins (made by Tom Szilagyi) are copied from https://github.com/kmatheussen/tap-plugins .
