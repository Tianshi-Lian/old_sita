import sys

BUILD_CFG = "debug"
BUILD_PRJ_NAME = "sita"

PLATFORM = sys.platform

if 'linux' in PLATFORM: # we could be linux or linux2
    PLATFORM = 'linux'
elif 'win' in PLATFORM:
    PLATFORM = 'windows'
