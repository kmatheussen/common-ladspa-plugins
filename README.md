# common-ladspa-plugins

Ideally, it should be enough to write './build_all.sh', but the scripts are not quite finished yet.

The calf, caps, cmt and swh plugins are copied from lmms (https://lmms.io/), and the build_lmms.sh
script also uses the lmms' building environment to build these plugins.

The kokkinizita plugins (made by Fons Adriaensen) are copied from http://kokkinizita.linuxaudio.org.
The TAP plugins (made by Tom Szilagyi) are copied from https://sourceforge.net/projects/tap-plugins/files/tap-plugins/
All of these plugins uses well written Makefiles, which are simple to automatically
modify on the fly with a sed script in order to compile for windows and osx.

