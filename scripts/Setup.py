"""
Python script to download Vcpkg and build it depending on the platform in the current directory,
and install required libraries if they are not already installed.
Written by [Your Name Here]
"""

import os
import sys
import platform
import shutil
import subprocess
import urllib.request
import zipfile
import shlex
import re
from SetupPython import PythonConfiguration as PythonRequirements

try:
    from colorama import *
except ImportError:
    print("colorama not found, installing...")
    subprocess.run(["pip", "install", "colorama"])
    from colorama import *

# Get the platform (Windows, Linux, or macOS)
platform_system = platform.system()
if platform_system == "Windows":
    vcpkg_url = "https://github.com/microsoft/vcpkg/archive/master.zip"
    vcpkg_dir = "vcpkg-master"
    vcpkg_exe = "vcpkg.exe"
else:
    vcpkg_url = "https://github.com/microsoft/vcpkg/archive/master.zip"
    vcpkg_dir = "vcpkg-master"
    vcpkg_exe = "vcpkg"

init()
# Check if required Python packages are installed
print(f"{Fore.BLUE}Checking required Python packages...{Style.RESET_ALL}")
required_packages = ["urllib3", "zipfile", "shlex"]
for package in required_packages:
    try:
        __import__(package)
    except ImportError:
        print(f"{Fore.YELLOW}{package} not found, installing...{Style.RESET_ALL}")
        subprocess.run(["pip", "install", package])

# Download Vcpkg
print(f"{Fore.BLUE}Downloading Vcpkg from {vcpkg_url}...{Style.RESET_ALL}")

urllib.request.urlretrieve(vcpkg_url, "vcpkg.zip")

# Extract Vcpkg
print(f"\n{Fore.BLUE}Extracting Vcpkg to {vcpkg_dir}...{Style.RESET_ALL}")
with zipfile.ZipFile("vcpkg.zip", "r") as zip_ref:
    zip_ref.extractall(".")

# Build Vcpkg
print(f"{Fore.BLUE}Building Vcpkg in {vcpkg_dir}...{Style.RESET_ALL}")
os.chdir(vcpkg_dir)
if os.name == "nt":  # Windows
    subprocess.run(shlex.split("bootstrap-vcpkg.bat"))
else:  # Linux and macOS
    subprocess.run(shlex.split("./bootstrap-vcpkg.sh"))

# Check if libraries are installed and install them if necessary
libraries = ["assimp:x64-windows","pthreads:x64-windows","glfw3:x64-windows"]
for lib in libraries:
    result = subprocess.run(shlex.split(f"./{vcpkg_exe} list {lib}"), capture_output=True, text=True)
    if f"{lib}:{os.linesep}    Installed" not in result.stdout:
        print(f"{Fore.YELLOW}Installing {lib}...{Style.RESET_ALL}")
        subprocess.run(shlex.split(f"./{vcpkg_exe} install {lib}"))

# Clean up
os.chdir("..")
os.remove("vcpkg.zip")

# Make sure everything we need for the setup is installed
PythonRequirements.Validate()

from SetupVulkan import VulkanConfiguration as VulkanRequirements
os.chdir('./../') # Change from devtools/scripts directory to root

VulkanRequirements.Validate()

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