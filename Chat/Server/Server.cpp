// Server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Server.h"
#include "afxsock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		nRetCode = 1;
	}
	else
	{
		// TODO: code your application's behavior here.
		CSocket server, s;
		char s_str[100], r_str[100];

		AfxSocketInit(NULL);

		server.Create(1234);
		server.Listen(1);

		if (server.Accept(s))
		{
			do
			{
				printf("\nServer: ");
				gets(s_str);
				s.Send(s_str,strlen(s_str),0);

				s.Receive(r_str,100,0);
				printf("\nCleint: %s",r_str);
			}while (1);

			s.Close();

		}

		server.Close();
	}

	return nRetCode;
}


