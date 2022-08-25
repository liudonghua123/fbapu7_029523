#include "tchar.h"
#include "windows.h"
#include "burnint.h"

#define BYTE3_TO_UINT(bp) \
     (((unsigned int)(bp)[0] << 16) & 0x00FF0000) | \
     (((unsigned int)(bp)[1] << 8) & 0x0000FF00) | \
     ((unsigned int)(bp)[2] & 0x000000FF)

#define BYTE2_TO_UINT(bp) \
    (((unsigned int)(bp)[0] << 8) & 0xFF00) | \
    ((unsigned int) (bp)[1] & 0x00FF)


char szPatchDataName[_MAX_PATH];

char IpsDirectory[]="Ips\\";

bool bCountIps=FALSE;

int nIps=0;

static void PatchFile(const char *p, UINT8 *base)
{
        int i;
        char buf[6];
        FILE *f;
        int Offset,Size;
        UINT8 *mem8;

        if ((f = fopen(p, "rb")) == NULL)
        {
                if (f == NULL) {
                        return;
                }
        }

        memset(buf, 0, sizeof buf);
        fread(buf,1,5,f);
        if (strcmp(buf, "PATCH"))
        {
                return;
        }
        else
        {
                while (!feof(f))
                {
                        UINT8 ch = 0;
                        int bRLE;

                        fread(buf,1,3,f);
                        buf[3] = 0;
                       if (!strcmp(buf, "EOF")) break;

                        Offset = BYTE3_TO_UINT(buf);

                        fread(buf,1,2,f);
                        Size = BYTE2_TO_UINT(buf);

            bRLE = Size == 0;
                        if (bRLE)
                        {
                                fread(buf,1,2,f);
                                Size = BYTE2_TO_UINT(buf);
                                ch = fgetc(f);
                        }
                        while (Size--)
                        {
                                i = Offset;
                                mem8 = base + Offset;
                                Offset++;
                                *mem8 = bRLE?ch:fgetc(f);

                        }
                }
        }
        fclose(f);
}

static void DoPatchGame(const char *patch_name, char *game_name, UINT8 *base)
{
	char s[_MAX_PATH];
	char *p;
	char *rom_name;
	char *ips_name;
	FILE *fpDat=NULL;

	if ((fpDat = fopen(patch_name, "rb")) != NULL)
	{
		if (!bCountIps)
		{
			while (!feof(fpDat))
		  {
			if (fgets(s, MAX_PATH, fpDat) != NULL)
			{
				nIps++;
			}
		  }
		  bCountIps=TRUE;
		}

		fseek(fpDat,0,SEEK_SET);

		while (!feof(fpDat))
		{
			if (fgets(s, MAX_PATH, fpDat) != NULL)
			{
				p = s;

				if (s[0] == (INT8)0xef && s[1] == (INT8)0xbb && s[2] == (INT8)0xbf)	//UTF-8 sig: EF BB BF
					p += 3;

				if (s[0] == (INT8)0x5b)	//'['
					break;

				rom_name = strtok(p, " \t\r\n");
				if (!rom_name)
					continue;
				if (*rom_name == '#')
					continue;
				if (_stricmp(rom_name, game_name))
					continue;

				ips_name = strtok(NULL, " \t\r\n");
				if (!ips_name)
					continue;

				strtok(NULL, "\r\n");
				char szIpsName[MAX_PATH];

				sprintf(szIpsName, "%s%s\\%s.ips",IpsDirectory , BurnDrvGetTextA(DRV_NAME),ips_name);

				PatchFile(szIpsName, base);

				nIps--;

				if (nIps==0) bDoPatch=FALSE;

			}
		}
		fclose(fpDat);
	}
}

/*void PatchGame(const char *patch_name, UINT8 *base)
{
	char *s = strdup(patch_name);
	char *p, *q;

	for (p = s; *p; p = q)
	{
		for (q = p; *q; q++)
			if (*q == ',')
			{
				*q++ = '\0';
				break;
			}*/

		//DoPatchGame(patch_name, base);
	/*}

	free(s);
}*/
int FindFileInDir(char *szName, char* strRet, const int patch_index)
{
	WIN32_FIND_DATA fd;
	ZeroMemory(&fd, sizeof(WIN32_FIND_DATA));

	HANDLE hSearch;
	char filePathName[256];
	ZeroMemory(filePathName, 256);

	sprintf(filePathName, "%s%s\\",IpsDirectory,szName);

	if( filePathName[strlen(filePathName) -1] != '\\' )
	{
		strcat(filePathName, "\\");
	}

	strcat(filePathName, "*.dat");

	hSearch = FindFirstFile(filePathName, &fd);

	if (hSearch)
	{
		int Done = 0;
		int Count = 0;

		while (!Done )
		{
			if (Count == patch_index)
			{
				strcpy(strRet, fd.cFileName);
				strRet[strlen(strRet)-4] = 0;	// To trim the ext ".dat"
				break;
			}
			Count++;
			Done = !FindNextFile(hSearch, &fd);
		}

	FindClose(hSearch);
	return 1;
	}
	return 0;
}
//================================================
int CountPatch(char* szName)
{
	WIN32_FIND_DATA fd;
	ZeroMemory(&fd, sizeof(WIN32_FIND_DATA));

	HANDLE hSearch;
	char filePathName[256];
	ZeroMemory(filePathName, 256);

	sprintf(filePathName, "%s%s\\",IpsDirectory,szName);

	int Count = 0;

	if( filePathName[strlen(filePathName) -1] != '\\' )
	{
		strcat(filePathName, "\\");
	}

	strcat(filePathName, "*.dat");

	hSearch = FindFirstFile(filePathName, &fd);

	if (hSearch!=INVALID_HANDLE_VALUE)
	{
		int Done = 0;

		while (!Done )
		{
			Count++;
			Done = !FindNextFile(hSearch, &fd);
		}

	FindClose(hSearch);
	}
	return Count;
}
//================================================
void DoPatch(UINT8 *base,char *game_name, const int patch_index)
{
	char DataName[_MAX_PATH];
	char IpsDataDirectory[_MAX_PATH];

	ZeroMemory(DataName, _MAX_PATH);
	//ZeroMemory(IpsDirectory, _MAX_PATH);

	sprintf(IpsDataDirectory, "%s%s\\",IpsDirectory,BurnDrvGetTextA(DRV_NAME));

	if(FindFileInDir(BurnDrvGetTextA(DRV_NAME), DataName, patch_index))
	{
	strcpy(szPatchDataName, DataName);

	strcat(IpsDataDirectory, DataName);
	strcat(IpsDataDirectory,".dat");

	DoPatchGame(IpsDataDirectory,game_name,base);
	}
}
