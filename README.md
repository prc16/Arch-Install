## Update the system clock
timedatectl set-ntp true

## Partition the disks
cfdisk

mkfs.fat -F 32 /dev/efi_system_partition
mkswap /dev/swap_partition
swapon /dev/swap_partition

mkfs.btrfs -L arch /dev/sda3

mount /dev/sda3 /mnt
cd /mnt

btrfs subvolume create subvol_root
btrfs subvolume create subvol_var
btrfs subvolume create subvol_tmp
btrfs subvolume create subvol_home
btrfs subvolume create subvol_snapshots

umount /mnt

mount -o noatime,commit=120,compress=zstd,space_cache,subvol=subvol_root /dev/sda3 /mnt
### You need to manually create folder to mount the other subvolumes at
mkdir /mnt/{efi,home,var,tmp,toplevel}
mount -o noatime,commit=120,compress=zstd,space_cache,subvol=subvol_home      /dev/sda3 /mnt/home
mount -o noatime,commit=120,compress=zstd,space_cache,subvol=subvol_tmp       /dev/sda3 /mnt/tmp
mount -o noatime,commit=120,compress=zstd,space_cache,subvol=subvol_var       /dev/sda3 /mnt/var
mount -o noatime,commit=120,compress=zstd,space_cache,subvol=subvol_snapshots /dev/sda3 /mnt/snapshots
mount -o noatime,commit=120,compress=zstd,space_cache,subvol=/                /dev/sda3 /mnt/toplevel

### Mounting the boot partition at /boot folder
mount /dev/sda1 /mnt/efi

## Install Linux kernel, firmware and essential packages
pacstrap /mnt base linux linux-firmware

