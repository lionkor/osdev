#!/bin/sh
if grub-file --is-x86-multiboot $1; then
  echo $1 multiboot confirmed
  true
else
  echo $1 is not multiboot
  false
fi
