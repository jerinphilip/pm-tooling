#!/bin/bash

TAG=xiaomi-cereus

function pm-build {
  pmbootstrap checksum linux-$TAG
  pmbootstrap checksum device-$TAG

  pmbootstrap build linux-$TAG
  pmbootstrap build device-$TAG
}

function pm-clean-build {
  pmbootstrap shutdown
  sudo rm -rfv ws
  rm -v $HOME/.config/pmbootstrap.cfg
  cat xc.prompt | pmbootstrap init
  pushd ws/cache_git/pmaports
  rm -rv device/testing/{linux,device}-$TAG
  git remote add jp git@github.com:jerinphilip/pmaports.git
  git fetch jp -a && git checkout $TAG
  popd
  pmbootstrap install
  pmbootstrap initfs hook_add debug-shell
}

function flash {
  pmbootstrap flasher flash_rootfs
  pmbootstrap flasher flash_kernel
}
