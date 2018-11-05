# .bashrc
find . -type f -print0 | xargs -0 sed -i 's/EOS/UOS/g'
ulord@host-10-186-11-220:~/EOSDevHelper$ find . -type f -print0 | xargs -0 sed -i 's/Eos/Uos/g'
ulord@host-10-186-11-220:~/EOSDevHelper$ find . -type f -print0 | xargs -0 sed -i 's/uos/uos/g'
ulord@host-10-186-11-220:~/EOSDevHelper$ find . -exec rename 's/EOS/UOS/' {} ";"
ulord@host-10-186-11-220:~/EOSDevHelper$ find . -exec rename 's/eos/uos/' {} ";"
