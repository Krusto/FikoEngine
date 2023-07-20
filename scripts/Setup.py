"""
Python script to download Vcpkg and build it depending on the platform in the current directory,
and install required libraries if they are not already installed.
Written by Krasto
"""

import os
import sys
import subprocess
import re
from SetupPython import PythonConfiguration as PythonRequirements

# Make sure everything we need for the setup is installed
required_packages = ["urllib3", "zipfile", "shlex","shutil"]
PythonRequirements.Validate(required_packages)

import Utils

from colorama import *

init()

from SetupVcpkg import VcpkgSetup
VcpkgSetup.Validate()

from SetupVulkan import VulkanConfiguration as VulkanRequirements
os.chdir('./../') # Change from devtools/scripts directory to root

VulkanRequirements.Validate()

os.chdir("Vendor")
print(f"\n{Fore.BLUE}Getting Ninja...{Style.RESET_ALL}")
subprocess.call(["git","clone","https://github.com/ninja-build/ninja"])
print(f"\n{Fore.BLUE}Building Ninja...{Style.RESET_ALL}")
os.chdir("ninja")
subprocess.call(["cmake","-Bbuild-cmake"])
subprocess.call(["cmake","--build","build-cmake"])
os.chdir("../../")
print(f"\n{Fore.BLUE}Updating submodules...{Style.RESET_ALL}")
subprocess.call(["git", "submodule", "update", "--init", "--recursive"])

path = str(os.environ.get("VULKAN_SDK")).strip()
filedata = ""

path = re.sub(r"\\","/",path)

print(f"{Fore.BLUE}Replacing VulkanSDK path in CMakeLists.txt{Style.RESET_ALL}")
with open('CMakeLists.txt', 'r') as file :
    for line in file:
        filedata += re.sub(r"C:/VulkanSDK/\d.\d.\d\d\d.\d",path.strip(),line)

with open('CMakeLists.txt', 'w') as file :
    file.write(filedata)

# Done
print(f"{Fore.GREEN}Done!{Style.RESET_ALL}")