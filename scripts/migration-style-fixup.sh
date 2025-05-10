#!/usr/bin/env bash
private_path=/data/server-private/styles
public_path=/data/server-public/styles

move_styles=('apps_logo' 'panopoly_*' 'pece_[afm]*')
all_styles=('panopoly_*' 'media_thumbnail' 'pece_artifact_image_large' 'pece_mini_teaser' 'pece_most_recent' 'pece_thumbnail')

for style in "${move_styles[@]}"; do
	echo "move $public_path/$style to $private_path/$style"
done
for style in "${all_styles[@]}"; do
	echo "chmod -w $private_path/$style"
done
