#!/usr/bin/env python3

# External command, intended to be called with custom_target() in meson.build.

# dummy-header.py <output_file>

import os
import sys

output_file = sys.argv[1]

# A dummy header file is created if it does not exist, but it's never updated.
if not os.path.isfile(output_file):
  with open(output_file, 'w') as f:
    f.write('// Dummy header file. Created and used by meson.build\n')
