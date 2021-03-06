import glob
import os
import re
import shutil

fromRootPath = '../01_platformio/'
toRootPath = '../00_arduino_ide/'

# Clear toRootPath
for root, dirs, files in os.walk(toRootPath, topdown = False):
  for name in files:
    os.remove(os.path.join(root, name))
  for name in dirs:
    os.rmdir(os.path.join(root, name))

# Copy platformio to arduino_ide
li = glob.glob(fromRootPath + '/**/src/', recursive = True)
for fromSrcPath in li:
  # Exception 1: Avoid projects in each directories.
  if fromSrcPath == '../01_platformio/01_button/01_alternate/src/'\
    or fromSrcPath == '../01_platformio/04_sensor/acceleration_2d_1/src/'\
    or fromSrcPath == '../01_platformio/04_sensor/acceleration_2d_2/src/'\
    or fromSrcPath == '../01_platformio/04_sensor/acceleration_2d_3/src/'\
    or fromSrcPath == '../01_platformio/04_sensor/direction_1/src/'\
    or fromSrcPath == '../01_platformio/04_sensor/rich_bmm150_calibrator/src/'\
    or fromSrcPath == '../01_platformio/99_others/interaction/direction_1/src/'\
    or fromSrcPath == '../01_platformio/99_others/interaction/rest_1/src/'\
    or fromSrcPath == '../01_platformio/99_others/interaction/rest_2/src/'\
    or fromSrcPath == '../01_platformio/99_others/interaction/rest_2_ema/src/':
    continue
  # Exception 1: End
  toDirPath = fromSrcPath.replace(fromRootPath, toRootPath)
  toDirPath = toDirPath.replace('src/', '')
  os.makedirs(toDirPath, exist_ok = True)
  for fromFilePath in glob.glob(fromSrcPath + '*.*'):
    fileName = fromFilePath.split('/')[-1]
    # Exception 2: Avoid files in each directories.
    if fileName == 'config.h':
      continue
    # Exception 2: End
    fromFileName = fileName
    toFileName = fileName
    if fileName == 'main.cpp':
      toFileName = toDirPath.split('/')[-2] + '.ino'
    fromFilePath = fromSrcPath + fromFileName
    toFilePath = toDirPath + toFileName
    shutil.copyfile(fromFilePath, toFilePath)
    print('Copy from')
    print(fromFilePath)
    print('Copy to')
    print(toFilePath)
    print('\n')
    # Exception 3: Replace words in each files.
    if fileName == 'main.cpp':
      with open(toFilePath) as f:
        data_lines = f.read()
      data_lines = data_lines.replace(
        '\n\n#include "./config.h"\n\n', '\n\n')
      data_lines = data_lines.replace('#include "./config.h"\n', '')
      with open(toFilePath, mode="w") as f:
        f.write(data_lines)
    # Exception 3: End
