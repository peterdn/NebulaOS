NebulaOS
========

## Overview

Just another hobby operating system project.

## Building and running

### Prerequisites

* Rust 0.13.0-dev
* Bochs (recommended)
* GRUB 2 (if building bootdisk from scratch; MUST have been patched with: http://savannah.gnu.org/bugs/?43443)

### Instructions

To build:

    make

To create bootdisk image:

    make bootdisk

To build everything and start in Bochs:

    make bochs

