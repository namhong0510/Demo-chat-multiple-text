// Server_chat.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Server_chat.h"
#include "afxsock.h"
#include "conio.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// initialize MFC and print and error on failure
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: change error code to suit your needs
			_tprintf(_T("Fatal Error: MFC initialization failed\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: code your application's behavior here.
			CSocket server,client;
			char s_str[1000],r_str[1000];
			AfxSocketInit(NULL);
			server.Create(1234);

			server.Listen();
			printf("Dang cho mot ket noi ...");
			
			if(server.Accept(client))
			{
						
				client.Send("\nChuc mung ban da ket noi thanh cong",1000,0);
				do
				{
					client.Receive(r_str,1000,0);
					int len = strlen(r_str);
					r_str[len] = 0;
					printf("%s",r_str);
					while(len!=0)
					{					
						
						client.Receive(r_str,1000,0);
						len = strlen(r_str);
						r_str[len] = 0;
						if(strcmp(r_str,"stop")!=1)
							break;						
						else
							printf("\nClient: %s",r_str);				
						
					}					
					char c=10;
					while(c==10)
					{
						printf("\nServer: ");
						gets(s_str);
						client.Send(s_str,1000,0);
						c = getch();
						if(c==27)
						{
							client.Send("stop",1000,0);
							break;
						}
					}	


				}while(strcmp(s_str,"exit") && strcmp(r_str,"exit"));
				client.Close();
			}
			server.Close();






		}
	}
	else
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: GetModuleHandle failed\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
