mkdir -p iso_bin
mkdir -p iso_bin/boot
cp -p src/kernel.bin iso_bin/boot/kernel.bin
mkdir -p iso_bin/boot/grub
cp src/grub.cfg iso_bin/boot/grub
sudo grub-mkrescue -o BrenOS.iso iso_bin
