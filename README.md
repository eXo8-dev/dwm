
```bash
sudo pacmans -S firefox telegram-desktop make pcmanfm jdk21-openjdk jdk17-openjdk jdk8-openjdk intellij-idea-community-edition discord xorg base-devel git intel-ucode os-prober kitty pavucontrol
sudo os-prober
sudo grub-mkconfig -o /boot/grub/grub.cfg

git clone https://github.com/eXo8-dev/dwm.git
cd dwm
sudo make clean install
