## Update the system clock  
timedatectl set-ntp true  

## Partition the disks  
cfdisk  

mkfs.fat -F 32 /dev/efi_system_partition  
mkswap /dev/swap_partition  
swapon /dev/swap_partition  

mkfs.btrfs -L arch /dev/sda2  

mount -o noatime,commit=120,compress=zstd,autodefrag,space_cache=v2 /dev/sda2 /mnt  

btrfs subvolume create /mnt/subvol_root  
btrfs subvolume create /mnt/subvol_var  
btrfs subvolume create /mnt/subvol_tmp  
btrfs subvolume create /mnt/subvol_home  

umount /mnt  

mount -o noatime,commit=120,compress=zstd,autodefrag,space_cache=v2,subvol=subvol_root /dev/sda2 /mnt  
### You need to manually create folder to mount the other subvolumes at  
mkdir /mnt/{efi,home,var,tmp,toplevel}  
mount -o noatime,commit=120,compress=zstd,autodefrag,space_cache=v2,subvol=subvol_home    /dev/sda2 /mnt/home  
mount -o noatime,commit=120,compress=zstd,autodefrag,space_cache=v2,subvol=subvol_var     /dev/sda2 /mnt/var  
mount -o noatime,commit=120,compress=zstd,autodefrag,space_cache=v2,subvol=/              /dev/sda2 /mnt/toplevel  

### Mounting the boot partition at /boot folder  
mount /dev/sda1 /mnt/efi  

## Install Linux kernel, firmware and essential packages  
pacstrap /mnt base linux linux-firmware vim  

## gen fstab  
genfstab -U /mnt >> /mnt/etc/fstab  

## Chroot into install
arch-chroot /mnt  

### set root password
passwd  

### Time zone  
ln -sf /usr/share/zoneinfo/Region/City /etc/localtime  
hwclock --systohc  

### Localization  
vim /etc/locale.gen  
locale-gen  
echo "LANG=en_US.UTF-8" >> /etc/locale.conf  

### Network configuration
echo "myhostname" >> /etc/hostname 
vim /etc/hosts  
>127.0.0.1        localhost  
>::1              localhost  
>127.0.1.1        myhostname  

## Install remaining essantial pakages
pacman -S grub grub-btrfs efibootmgr base-devel linux-headers networkmanager network-manager-applet wpa_supplicant mtools dosfstools reflector git

### Start services
systemctl enable NetworkManager  

## Initramfs (Add btrfs in MODULES=())  
vim /etc/mkinitcpio.conf  
mkinitcpio -P  

## Install grub
grub-install --target=x86_64-efi --efi-directory=/boot/efi  
grub-mkconfig -o /boot/grub/grub.cfg  

## System administration
useradd -mG wheel myusername  
passwd myusername  
EDITOR=vim visudo  

## Create a snapshot
btrfs subvolume snapshot -r / "/toplevel/subvol_root_01_fresh_install"  

### Regenareate gurb config
grub-mkconfig -o /boot/grub/grub.cfg  

## Reboot
reboot  
