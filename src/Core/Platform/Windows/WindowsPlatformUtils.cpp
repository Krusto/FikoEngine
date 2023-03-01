#include "WindowsPlatformUtils.h"
#include <commdlg.h>
#include <ShlObj.h>

std::filesystem::path SearchFolder( TCHAR * path, HWND hwnd)
{     
	std::filesystem::path output;
    //Declare all needed handles     
    WIN32_FIND_DATA FindFileData;     
    HANDLE hFind;     
    TCHAR filename[ MAX_PATH + 256 ];     
    TCHAR pathbak[ MAX_PATH ];     

    //Make a backup of the directory the user chose         
    strcpy( pathbak, path );

    //Find the first file in the directory the user chose     
    hFind = FindFirstFile ( "*.*", &FindFileData );

    //Use a do/while so we process whatever FindFirstFile returned     
    do     
    {         
        //Is it valid?         
        if ( hFind != INVALID_HANDLE_VALUE )         
        {             
            //Is it a . or .. directory? If it is, skip, or we'll go forever.             
            if ( ! ( strcmp( FindFileData.cFileName, "." ) ) || 
                ! ( strcmp( FindFileData.cFileName, ".." ) ) )             
            {                 
                continue;             
            }             
            //Restore the original directory chosen by the user             
            strcpy( path, pathbak );

            //Append the file found on to the path of the 
            //directory the user chose             
            sprintf( path, "%s\\%s", path, FindFileData.cFileName );

            //If SetCurrentDirectory Succeeds ( returns 1 ), the 
            //current file is a directory. Pause this function,             
            //and have it call itself. This will begin the whole 
            //process over in a sub directory.
			output = std::filesystem::path(pathbak);
            if ( ( SetCurrentDirectory( path ) ) )             
            {                 
                output = SearchFolder( path, hwnd);
            } 
        }     
    }    
    while ( FindNextFile ( hFind, &FindFileData ) 
        && hFind != INVALID_HANDLE_VALUE );     
    FindClose ( hFind );

    return output;
}//SEARCH FOLDER


std::filesystem::path FileDialogs::OpenFolder(GLFWwindow* window)
{
	TCHAR path[MAX_PATH] = "./";
	BROWSEINFO bi = { 0 };
	bi.lpszTitle = ("All Folders Automatically Recursed.");
	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
	std::filesystem::path output;
	if (pidl != 0)
	{
		// get the name of the folder and put it in path
		SHGetPathFromIDList(pidl, path);

		//Set the current directory to path
		SetCurrentDirectory(path);

		//Begin the search
		output = SearchFolder(path,glfwGetWin32Window(window));

		// free memory used
		IMalloc* imalloc = 0;
		if (SUCCEEDED(SHGetMalloc(&imalloc)))
		{
			imalloc->Free(pidl);
			imalloc->Release();
		}
	}
	return output;
}

std::filesystem::path FileDialogs::OpenFile(GLFWwindow* window,const char * filter)
{
	OPENFILENAME ofn;       // common dialog box structure
	TCHAR szFile[260] = { 0 };       // if using TCHAR macros

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = glfwGetWin32Window(window);
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = ("All\0*.*\0Text\0*.TXT\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn) == TRUE)
	{
		return std::filesystem::path(ofn.lpstrFile);
	}
	return std::filesystem::current_path();
}

std::string FileDialogs::SaveFile(const char* filter)
{
	return std::string();
}
