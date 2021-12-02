# Arch-Install

timedatectl set-ntp true
mkfs.fat -F 32 /dev/efi_system_partition
mkswap /dev/swap_partition
swapon /dev/swap_partition

mkfs.btrfs -L arch /dev/sda3

mount /dev/sda3 /mnt

cd /mnt
btrfs subvolume create /mnt/root
btrfs subvolume create /mnt/var
btrfs subvolume create /mnt/tmp
btrfs subvolume create /mnt/home
btrfs subvolume create /mnt/snapshots

umount /mnt

mkdir /mnt/{boot,home,var,opt,tmp,.snapshots}
mount -o noatime,commit=120,compress=zstd,space_cache,subvol=home /dev/sda3 /mnt/home
mount -o noatime,commit=120,compress=zstd,space_cache,subvol=tmp /dev/sda3 /mnt/tmp
mount -o noatime,commit=120,compress=zstd,space_cache,subvol=snapshots /dev/sda3 /mnt/.snapshots
mount -o subvol=@var /dev/sda3 /mnt/var
# Mounting the boot partition at /boot folder
mount /dev/sda1 /mnt/boot


































