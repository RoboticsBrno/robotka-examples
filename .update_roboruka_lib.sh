#!/bin/sh

if [ -z "$1" ]; then
    echo "Specify version!"
    exit 1
fi

for f in $(find . -maxdepth 2 -type f -name platformio.ini); do
    echo "$f"
    sed -i "s=\(RB3204-RBCX-Robotka-library/archive/v\)[0-9.]\+\.zip=\1$1.zip=" "$f"
done

git commit -a -m "Update library to v$1"
git show
