/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: SharedUtility.h
-- Project: Shared
-- Author(s): m0niSx
-- Description: General utils definitions header file
=============================================================*/

#ifndef SHAREDUTILITY_H
#define SHAREDUTILITY_H

#include <math.h>
#include <windows.h>
#include <stdio.h>
#include <tlhelp32.h>

// Vector2 class
class CVector2
{
	public:
		float		fX;
		float		fY;

		// Class constructors
		CVector2()
		{
			fX = 0.0f;
			fY = 0.0f;
		};

		CVector2(float _fX, float _fY)
		{
			fX = _fX;
			fY = _fY;
		};

		CVector2 operator + ( const CVector2& vecRight ) const
		{
			return CVector2 ( fX + vecRight.fX, fY + vecRight.fY );
		}

		CVector2 operator - ( const CVector2& vecRight ) const
		{
			return CVector2 ( fX - vecRight.fX, fY - vecRight.fY );
		}

		CVector2 operator * ( const CVector2& vecRight ) const
		{
			return CVector2 ( fX * vecRight.fX, fY * vecRight.fY );
		}

		CVector2 operator * ( float fRight ) const
		{
			return CVector2 ( fX * fRight, fY * fRight );
		}

		CVector2 operator / ( const CVector2& vecRight ) const
		{
			return CVector2 ( fX / vecRight.fX, fY / vecRight.fY );
		}

		CVector2 operator - () const
		{
			return CVector2 ( -fX, -fY );
		}

		void operator += ( float fRight )
		{
			fX += fRight;
			fY += fRight;
		}

		void operator += ( const CVector2& vecRight )
		{
			fX += vecRight.fX;
			fY += vecRight.fY;
		}

		void operator -= ( float fRight )
		{
			fX -= fRight;
			fY -= fRight;
		}

		void operator -= ( const CVector2& vecRight )
		{
			fX -= vecRight.fX;
			fY -= vecRight.fY;
		}

		void operator *= ( float fRight )
		{
			fX *= fRight;
			fY *= fRight;
		}

		void operator *= ( const CVector2& vecRight )
		{
			fX *= vecRight.fX;
			fY *= vecRight.fY;
		}

		void operator /= ( float fRight )
		{
			fX /= fRight;
			fY /= fRight;
		}

		void operator /= ( const CVector2& vecRight )
		{
			fX /= vecRight.fX;
			fY /= vecRight.fY;
		}

		bool operator== ( const CVector2& param ) const
		{
			return ( ( fabs ( fX - param.fX ) < 0.0001f ) &&
					 ( fabs ( fY - param.fY ) < 0.0001f ) );
		}

		bool operator!= ( const CVector2& param ) const
		{
			return ( ( fabs ( fX - param.fX ) >= 0.0001f ) ||
					 ( fabs ( fY - param.fY ) >= 0.0001f ) );
		}
};

// Vector3 class
class CVector3
{
	public:
		float		fX;
		float		fY;
		float		fZ;

		// Class constructors
		CVector3()
		{
			fX = 0.0f;
			fY = 0.0f;
			fZ = 0.0f;
		};

		CVector3(float _fX, float _fY, float _fZ)
		{
			fX = _fX;
			fY = _fY;
			fZ = _fZ;
		};

		float Length ( void ) const
		{
			return sqrt ( (fX*fX) + (fY*fY) + (fZ*fZ) );
		}

		CVector3 operator + ( const CVector3& vecRight ) const
		{
			return CVector3 ( fX + vecRight.fX, fY + vecRight.fY, fZ + vecRight.fZ );
		}

		CVector3 operator - ( const CVector3& vecRight ) const
		{
			return CVector3 ( fX - vecRight.fX, fY - vecRight.fY, fZ - vecRight.fZ );
		}

		CVector3 operator * ( const CVector3& vecRight ) const
		{
			return CVector3 ( fX * vecRight.fX, fY * vecRight.fY, fZ * vecRight.fZ );
		}

		CVector3 operator * ( float fRight ) const
		{
			return CVector3 ( fX * fRight, fY * fRight, fZ * fRight );
		}

		CVector3 operator / ( const CVector3& vecRight ) const
		{
			return CVector3 ( fX / vecRight.fX, fY / vecRight.fY, fZ / vecRight.fZ );
		}
		CVector3 operator / ( float fRight ) const
		{
			return CVector3 ( fX / fRight, fY / fRight, fZ / fRight );
		}

		CVector3 operator - () const
		{
			return CVector3 ( -fX, -fY, -fZ );
		}

		void operator += ( float fRight )
		{
			fX += fRight;
			fY += fRight;
			fZ += fRight;
		}

		void operator += ( const CVector3& vecRight )
		{
			fX += vecRight.fX;
			fY += vecRight.fY;
			fZ += vecRight.fZ;
		}

		void operator -= ( float fRight )
		{
			fX -= fRight;
			fY -= fRight;
			fZ -= fRight;
		}

		void operator -= ( const CVector3& vecRight )
		{
			fX -= vecRight.fX;
			fY -= vecRight.fY;
			fZ -= vecRight.fZ;
		}

		void operator *= ( float fRight )
		{
			fX *= fRight;
			fY *= fRight;
			fZ *= fRight;
		}

		void operator *= ( const CVector3& vecRight )
		{
			fX *= vecRight.fX;
			fY *= vecRight.fY;
			fZ *= vecRight.fZ;
		}

		void operator /= ( float fRight )
		{
			fX /= fRight;
			fY /= fRight;
			fZ /= fRight;
		}

		void operator /= ( const CVector3& vecRight )
		{
			fX /= vecRight.fX;
			fY /= vecRight.fY;
			fZ /= vecRight.fZ;
		}

		bool operator== ( const CVector3& param ) const
		{
			return ( ( fabs ( fX - param.fX ) < 0.0001f ) &&
					 ( fabs ( fY - param.fY ) < 0.0001f ) &&
					 ( fabs ( fZ - param.fZ ) < 0.0001f ) );
		}

		bool operator!= ( const CVector3& param ) const
		{
			return ( ( fabs ( fX - param.fX ) >= 0.0001f ) ||
					 ( fabs ( fY - param.fY ) >= 0.0001f ) ||
					 ( fabs ( fZ - param.fZ ) >= 0.0001f ) );
		}
};

class CMatrix
{
	public:
		char pad0[16];					// 0x0000 - 0x0010
		CVector2 vecRotation;			// 0x0010 - 0x0018
		char pad1[24];					// 0x0018 - 0x0030
		CVector3 vecPosition;			// 0x0030 - 0x003C
};

static void CopyString(char *szInputString, char *szOutputString, int iLength)
{
	// Rest the output string
	strcpy(szOutputString, "");
	// Loop through the input length
	for(int i = 0; i < iLength; i++)
	{
		// Get the input string current letter
		char szLetter[2];
		sprintf(szLetter, "%c", szInputString[i]);
		// Add the letter to the output string
		strcat(szOutputString, szLetter);
	}
	// End string
	szOutputString[strlen(szOutputString)] = '\0';
}

static int FindString(char *szInput, char *szStr)
{
	char szCheck[64];
	// Loop through the input length
	for(unsigned int i = 0; i < strlen(szInput); i++)
	{
		// Copy string until the finding length
		CopyString(szInput+i, szCheck, strlen(szStr));
		// Is is the name same as szStr ?
		if(!strcmp(szCheck, szStr))
			return i;
	}
	return -1;
}

static bool IsReadable(char cChar)
{
	if((cChar >= 'a' && cChar <= 'z') || (cChar >= 'A' && cChar <= 'Z') || (cChar >= '0' && cChar <= '9') || cChar == '_' || cChar == '.')
		return true;

	return false;
}

static bool FileExists(char *szFile)
{
	// Try to read the file
	FILE *pFile = fopen(szFile, "rb");
	if(!pFile)
		return false;

	// Close the file and return
	fclose(pFile);
	return true;
}

static int Split(char *szInputString, char *szOutputString, char *szSplit, int iIndex)
{
	// Copy from the index
	char *szString = (char *)malloc(strlen(szInputString));
	strcpy(szString, szInputString + iIndex);
	// Try to find the split 
	int iPlace = FindString(szString, szSplit);
	// Copy until the place
	CopyString(szString, szOutputString, iPlace != -1 ? iPlace : strlen(szString));
	// Free the allocated memory
	free(szString);
	return iPlace;
}

static bool GetProcessIdFromProcessName(char * szProcessName, DWORD * dwProcessId)
{
	bool bReturn = false;
	// Create a tool help 32 process snapshot
	HANDLE hProcessSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(!hProcessSnapShot)
		return false;

	// Create the PROCESSENTRY32 structure
	PROCESSENTRY32 ProcessEntry;
	ProcessEntry.dwSize = sizeof(ProcessEntry);
	// Process the first process
	if(Process32First(hProcessSnapShot, &ProcessEntry))
	{
		// Enumerate through all processes
		while(Process32Next(hProcessSnapShot, &ProcessEntry))
		{
			// Check the process name to see if it matches szProcessName
			if(!strcmp(ProcessEntry.szExeFile, szProcessName))
			{
				// It matches, set the process id and return true
				*dwProcessId = ProcessEntry.th32ProcessID;
				bReturn = true;
				break;
			}
		}
	}
	// Close the snapshot handle
	CloseHandle(hProcessSnapShot); 
	return bReturn;
}

static bool IsProcessRunning(char * szProcessName)
{
	// Simply return the value of GetProcessIdFromProcessName
	DWORD dwProcessId = 0;
	return GetProcessIdFromProcessName(szProcessName, &dwProcessId);
}

static bool InjectLibrary(HANDLE hProcess, char *szLibrary)
{
	if(!hProcess)
		return false;

	// Get the "LoadLibrary" function address
	FARPROC fLoadLibrary = GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
	// If address is invalid
	if(!fLoadLibrary)
		return false;

	// Allocate some memory for the call
	LPVOID lpvLoad = (LPVOID)VirtualAllocEx(hProcess, NULL, strlen(szLibrary)+1, MEM_COMMIT, PAGE_READWRITE);
	// Write to the process
	WriteProcessMemory(hProcess, lpvLoad, szLibrary, strlen(szLibrary)+1, NULL);
	// Create remote thread into the process
	HANDLE hThread = CreateRemoteThread(hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)fLoadLibrary, lpvLoad, NULL, NULL);
	// Is it created ?
	if(!hThread)
		return false;

	// Wait for the remote thread
	WaitForSingleObject(hThread, INFINITE);
	// Close the thread handle
	CloseHandle(hThread);
	// Free the allocated memory
	VirtualFreeEx(hProcess, lpvLoad, strlen(szLibrary)+1, MEM_RELEASE); 
	// Return true
	return true;
}

#endif