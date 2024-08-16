#!/bin/bash
echo -e "\033[0;32mHow many CPU cores do you want to be used in compiling process? (Default is 1. Press enter for default.)\033[0m"
read -e CPU_CORES
if [ -z "$CPU_CORES" ]
then
    CPU_CORES=1
fi

# Clone code from official Github repository
    rm -rf BoldTechnologyCommerceUganda
    git clone https://github.com/Bold-Technology-Commerce-Uganda/BTCUG.git

# Entering directory
    cd BoldTechnologyCommerceUganda

# Compile dependencies
    cd depends
    mkdir SDKs
    cd SDKs
    wget -c https://cloudflare-ipfs.com/ipfs/QmYv9wHqKa5gZE1kL4ZpcVqKp1coS5tS9cYKGe4mUxxrqL/SDKs/MacOSX10.11.sdk.tar.xz
    tar -xf MacOSX10.11.sdk.tar.xz
    cd ..
    make -j$(echo $CPU_CORES) HOST=x86_64-apple-darwin14
    cd ..

# Compile
    ./autogen.sh
    ./configure --prefix=$(pwd)/depends/x86_64-apple-darwin14 --enable-cxx --enable-static --disable-shared --disable-debug --disable-tests --disable-bench --disable-online-rust
    make -j$(echo $CPU_CORES) HOST=x86_64-apple-darwin14
    make deploy
    cd ..

# Create zip file of binaries
    cp BoldTechnologyCommerceUganda/src/BoldTechnologyCommerceUgandad BoldTechnologyCommerceUganda/src/BoldTechnologyCommerceUganda-cli BoldTechnologyCommerceUganda/src/BoldTechnologyCommerceUganda-tx BoldTechnologyCommerceUganda/src/qt/BoldTechnologyCommerceUganda-qt BoldTechnologyCommerceUganda/BoldTechnologyCommerceUganda-Core.dmg .
    zip BoldTechnologyCommerceUganda-MacOS.zip BoldTechnologyCommerceUgandad BoldTechnologyCommerceUganda-cli BoldTechnologyCommerceUganda-tx BoldTechnologyCommerceUganda-qt BoldTechnologyCommerceUganda-Core.dmg
    rm -f BoldTechnologyCommerceUgandad BoldTechnologyCommerceUganda-cli BoldTechnologyCommerceUganda-tx BoldTechnologyCommerceUganda-qt BoldTechnologyCommerceUganda-Core.dmg
