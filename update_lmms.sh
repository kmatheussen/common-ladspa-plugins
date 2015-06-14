#!/bin/sh

cd lmms

rm -fr lmms lmms-master

wget https://github.com/LMMS/lmms/archive/master.tar.gz
mv master.tar.gz lmms.tar.gz

tar xvzf lmms.tar.gz

mv lmms-master lmms

cd ..
