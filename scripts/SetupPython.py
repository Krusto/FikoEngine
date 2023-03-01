import sys
import subprocess
import importlib.util as importlib_util
try:
    from colorama import *
except ImportError:
    print("colorama not found, installing...")
    subprocess.run(["pip", "install", "colorama"])
    from colorama import *

class PythonConfiguration:
    @classmethod
    def Validate(cls):
        if not cls.__ValidatePython():
            return # cannot validate further
        if not cls.__ValidatePackage("conan"):
            return
            
        for packageName in ["requests"]:
            if not cls.__ValidatePackage(packageName):
                return # cannot validate further

    @classmethod
    def __ValidatePython(cls, versionMajor = 3, versionMinor = 3):
        if sys.version is not None:
            print(f"{Fore.BLUE}Python version {0:d}.{1:d}.{2:d} detected.{Style.RESET_ALL}".format( \
                sys.version_info.major, sys.version_info.minor, sys.version_info.micro))
            if sys.version_info.major < versionMajor or (sys.version_info.major == versionMajor and sys.version_info.minor < versionMinor):
                print(f"{Fore.YELLOW}Python version too low, expected version {0:d}.{1:d} or higher.{Style.RESET_ALL}".format( \
                    versionMajor, versionMinor))
                return False
            return True

    @classmethod
    def __ValidatePackage(cls, packageName):
        if importlib_util.find_spec(packageName) is None:
            return cls.__InstallPackage(packageName)
        return True

    @classmethod
    def __InstallPackage(cls, packageName):
        permissionGranted = False
        while not permissionGranted:
            reply = str(input(f"{Fore.YELLOW}Would you like to install Python package '{0:s}'? [Y/N]: {Style.RESET_ALL}".format(packageName))).lower().strip()[:1]
            if reply == 'n':
                return False
            permissionGranted = (reply == 'y')
        
        print(f"Installing {packageName} module...")
        subprocess.check_call(['python', '-m', 'pip', 'install', packageName])

        return cls.__ValidatePackage(packageName)

if __name__ == "__main__":
    PythonConfiguration.Validate()
