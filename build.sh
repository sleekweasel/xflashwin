#!/bin/bash

gcc -Wall xflashwin.c -lX11 -L/usr/X11/lib -o xflashwin &&
  echo SUCCEEDED NOW RUNNING &&
  ./xflashwin
