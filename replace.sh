# .bashrc
find . -type f -print0 | xargs -0 sed -i 's/EOS/UOS/g'
find . -type f -print0 | xargs -0 sed -i 's/Eos/Uos/g'
find . -type f -print0 | xargs -0 sed -i 's/uos/uos/g'
find . -exec rename 's/EOS/UOS/' {} ";"
find . -exec rename 's/eos/uos/' {} ";"
