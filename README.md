# common-ladspa-plugins

Ideally, it should be enough to write './build_all.sh', but the scripts are not quite finished yet.

The calf, caps, cmt, swh and tap plugins are copied from lmms (https://lmms.io/), and the build_lmms.sh
script also uses the lmms' building environment to build these plugins.

The kokkinizita plugins (made by Fons Adriaensen) are copied from http://kokkinizita.linuxaudio.org.
All of these plugins uses well written Makefiles, which are simple to automatically
modify on the fly with a sed script in order to compile for windows and osx.


