@echo off
xmake f -y --vs=2022
xmake project -k vsxmake -y -m "debug, release" -a "x64" ./build