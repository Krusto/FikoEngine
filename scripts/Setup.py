
import os
import subprocess
import platform
import re
from SetupPython import PythonConfiguration as PythonRequirements

# Make sure everything we need for the setup is installed
PythonRequirements.Validate()

from SetupVulkan import VulkanConfiguration as VulkanRequirements
os.chdir('./../') # Change from devtools/scripts directory to root

VulkanRequirements.Validate()

print("\nUpdating submodules...")
subprocess.call(["git", "submodule", "update", "--init", "--recursive"])

path = str(os.environ.get("VULKAN_SDK")).strip()
filedata = ""

path = re.sub(r"\\","/",path)

print("Replacing VulkanSDK path in CMakeLists.txt")
with open('CMakeLists.txt', 'r') as file :
 for line in file:
        filedata += re.sub(r"C:/VulkanSDK/\d.\d.\d\d\d.\d",path.strip(),line)

with open('CMakeLists.txt', 'w') as file :
    file.write(filedata)

print("Done!")