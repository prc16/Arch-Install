# Arch-Install

timedatectl set-ntp true
mkfs.fat -F 32 /dev/efi_system_partition
mkswap /dev/swap_partition
swapon /dev/swap_partition

mkfs.btrfs -L arch /dev/sda3

mount /dev/sda3 /mnt

cd /mnt
btrfs subvolume create /mnt/subvol_root
btrfs subvolume create /mnt/subvol_var
btrfs subvolume create /mnt/subvol_tmp
btrfs subvolume create /mnt/subvol_home

umount /mnt

mount -o noatime,commit=120,compress=zstd,space_cache,subvol=subvol_root /dev/sda3 /mnt
# You need to manually create folder to mount the other subvolumes at
mkdir /mnt/{efi,home,var,tmp,toplevel}
mount -o noatime,commit=120,compress=zstd,space_cache,subvol=subvol_home /dev/sda3 /mnt/home
mount -o noatime,commit=120,compress=zstd,space_cache,subvol=subvol_tmp /dev/sda3 /mnt/tmp
mount -o noatime,commit=120,compress=zstd,space_cache,subvol=/,subvol=/ /dev/sda3 /mnt/toplevel
mount -o noatime,commit=120,compress=zstd,space_cache,subvol=subvol_var /dev/sda3 /mnt/var

# Mounting the boot partition at /boot folder
mount /dev/sda1 /mnt/efi


































