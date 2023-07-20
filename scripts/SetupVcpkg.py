import sys
import subprocess
import importlib.util as importlib_util
import importlib
import os
import platform
import shlex
import Utils
from colorama import *

class VcpkgSetup:
    @classmethod
    def Validate(cls):
        if not cls.CheckVcpkgManagerInstalled(cls):
            cls.InstallVcpkgManager(cls)
        # Check if libraries are installed and install them if necessary
        print(f"{Fore.BLUE}Selecting library tripplet ...{Style.RESET_ALL}")
        cls.triplet = "x64-mingw-static"
        cls.libraries = ["zlib","glm", "assimp", "pthreads", "glfw3", "yaml-cpp"]
        
        print(f"{Fore.BLUE}Selected {cls.triplet} library triplet...{Style.RESET_ALL}")
        cls.InstallLibraries(cls,cls.libraries,cls.triplet)

    def GetVcpkgManagerExecutableName(cls):
        platform_system = platform.system()
        if platform_system == "Windows":
            vcpkg_exe = "vcpkg.exe"
        else:
            vcpkg_exe = "vcpkg"
        return vcpkg_exe

    def GetVcpkgManagerDir(cls):
        return "vcpkg"

    def CheckVcpkgManagerInstalled(cls):
        print(f"{Fore.BLUE}Checking if Vcpkg exist...{Style.RESET_ALL}")
        return os.access(f"{cls.GetVcpkgManagerDir(cls)}/{cls.GetVcpkgManagerExecutableName(cls)}", os.F_OK)

    def InstallVcpkgManager(cls):
        vcpkg_url = "https://github.com/microsoft/vcpkg/archive/master.zip"
        vcpkg_dir = cls.GetVcpkgManagerDir(cls)

        # Download Vcpkg
        print(f"{Fore.BLUE}Downloading Vcpkg from {vcpkg_url}...{Style.RESET_ALL}")
        Utils.DownloadFile(vcpkg_url,"vcpkg.zip")

        # Extract Vcpkg
        Utils.UnzipFile("vcpkg.zip",True)
        os.rename("vcpkg-master",vcpkg_dir)

        # Install Vcpkg
        print(f"{Fore.BLUE}Installing Vcpkg in {vcpkg_dir}...{Style.RESET_ALL}")
        platform_system = platform.system()
        if platform_system == "Windows":
            os.chdir(f"{vcpkg_dir}")
            subprocess.call([f"bootstrap-vcpkg.bat"])
            os.chdir("../")
        else:  # other platforms
            subprocess.call([f"./{vcpkg_dir}/bootstrap-vcpkg.sh"])
        
        # Clean up
        if os.access("vcpkg.zip", os.F_OK):
            os.remove("vcpkg.zip")

    def InstallLibraries(cls,libraryList,triplet):
        for lib in libraryList:
            print(f"./{cls.GetVcpkgManagerDir(cls)}/{cls.GetVcpkgManagerExecutableName(cls)} list {lib}")
            result = subprocess.run(shlex.split(f"./{cls.GetVcpkgManagerDir(cls)}/{cls.GetVcpkgManagerExecutableName(cls)} list {lib}"), capture_output=True, text=True)
            if f"{lib}:{os.linesep}    Installed" not in result.stdout:
                print(f"{Fore.YELLOW}Installing {lib}...{Style.RESET_ALL}")
                subprocess.run(shlex.split(f"./{cls.GetVcpkgManagerDir(cls)}/{cls.GetVcpkgManagerExecutableName(cls)} install {lib} --host-triplet={triplet} --triplet={triplet}"))


if __name__ == "__main__":
    VcpkgSetup.Validate()
