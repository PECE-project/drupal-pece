#!/bin/bash
# Script to quickly create sub-theme.

echo '
+------------------------------------------------------------------------+
| With this script you could quickly create pece_bs sub-theme     |
| In order to use this:                                                  |
| - pece_bs theme (this folder) should be in the contrib folder   |
+------------------------------------------------------------------------+
'
echo 'The machine name of your custom theme? [e.g. mycustom_pece_bs]'
read CUSTOM_PECE_BS

echo 'Your theme name ? [e.g. My custom pece_bs]'
read CUSTOM_PECE_BS_NAME

if [[ ! -e ../../custom ]]; then
    mkdir ../../custom
fi
cd ../../custom
cp -r ../contrib/pece_bs $CUSTOM_PECE_BS
cd $CUSTOM_PECE_BS
for file in *pece_bs.*; do mv $file ${file//pece_bs/$CUSTOM_PECE_BS}; done
for file in config/*/*pece_bs.*; do mv $file ${file//pece_bs/$CUSTOM_PECE_BS}; done

# Remove create_subtheme.sh file, we do not need it in customized subtheme.
rm scripts/create_subtheme.sh

# mv {_,}$CUSTOM_PECE_BS.theme
grep -Rl pece_bs .|xargs sed -i -e "s/pece_bs/$CUSTOM_PECE_BS/"
sed -i -e "s/SASS Bootstrap Starter Kit Subtheme/$CUSTOM_PECE_BS_NAME/" $CUSTOM_PECE_BS.info.yml
echo "# Check the themes/custom folder for your new sub-theme."