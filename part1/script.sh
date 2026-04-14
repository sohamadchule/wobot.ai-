#!/bin/bash

INPUT=$1
OUTPUT_DIR="frames"

mkdir -p $OUTPUT_DIR

gst-launch-1.0 filesrc location=$INPUT ! decodebin ! videoconvert ! videoscale ! video/x-raw,width=640,height=640 ! jpegenc ! multifilesink location="$OUTPUT_DIR/frame_%04d.jpg"