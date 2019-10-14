#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAXLINE 80

struct redirecting
{
	char command[MAXLINE];
	int tinhChatTapTin; //
};
typedef struct redirecting redirecting;

int tachChuoi(char* command, char** daTach)
{
	char* chuoiCanTach = strdup(command);
	char* token = strtok(chuoiCanTach, " ");	 //tach den gap khoang trang
	daTach[0] = token;
	int i = 1;
	while (token != NULL)
	{
		token = strtok(NULL, " "); //tach tiep theo den khoang trang ke
		daTach[i] = token;
		i++;
	}
	daTach[i] = NULL;
	return i - 1;
}

void themKiTuKetThuc(char* chuoi)
{
	int doDai = strlen(chuoi);
	while (chuoi[doDai - 1] == '\n' || chuoi[doDai -1] ==' ')
	{
		chuoi[doDai - 1] = '\0';
	}
}



redirecting rCommand(char toanTu, char* command)
{
	int doDaiDongLenh = strlen(command);
	int i;
	redirecting ketQua;
	int tinhChatTapTin;
	char dauToanTu;
	if (strstr(command, ">") != NULL)
	{
		dauToanTu = '>';
		tinhChatTapTin = 1;
	}
	else
	{
		dauToanTu = '<';
		tinhChatTapTin = '2';
	}
	int viTri = 0;
	char* lenhThucThi = (char*)malloc(MAXLINE);
	char* tenFile = (char*)malloc(MAXLINE);
	for (i = 0; i < doDaiDongLenh; i++)
	{
		if (command[i] == dauToanTu) //lay tu dau den toan tu~
		{
			if (lenhThucThi[i - 1] == ' ')
			{
				lenhThucThi[i - 1] = '\0';
			}
			else lenhThucThi[i] = '\0';
			viTri = i;
			break;
		}
		lenhThucThi[i] = command[i];
	}
	viTri++;
	while (command[viTri] == ' ') //Bo qua cac khoang trang
	{
		viTri++;
	}

	//================ COPY REDIRECT ===================
	int k = 0;
	for (i = viTri; i < doDaiDongLenh; i++)
	{
		tenFile[k] = command[i];
		k++;
	}
	themKiTuKetThuc(tenFile);

	char* file = strdup(tenFile);
	command = strdup(lenhThucThi);

	//Mo file va lay tinh chat file
	if (dauToanTu == '>') //Set quyen chi ghi
	{
		//xoa file cu tao file moi
		remove(file);
		tinhChatTapTin = open(file, O_WRONLY | O_CREAT, S_IRWXU);
	}
	else //Set quyen chi doc
	{
		remove(file);
		tinhChatTapTin  = open(file, O_RDONLY | O_CREAT, S_IRWXU);
	}
	strcpy(ketQua.command,command);
    	ketQua.tinhChatTapTin = tinhChatTapTin;
    	return ketQua;

}


int main()
{
	char* args[MAXLINE / 2 + 1]; /* command line arguments */
	int shouldrun = 1; /* flag to determine when to exit program */
	char* command = (char*)malloc(MAXLINE * sizeof(char));
	char* cauLenhTruoc = (char*)malloc(MAXLINE * sizeof(char));
	cauLenhTruoc = NULL;
	while (shouldrun)
	{
		printf("osh> ");
		fflush(stdin);
		fflush(stdout);
		fgets(command, 1000, stdin);
		themKiTuKetThuc(command);

		// ====================== THOAT NEU NHAP EXIT ===========================
		if (strcmp(command, "exit") == 0)
		{
			shouldrun = 0;
		}
		// ====================== LUU LICH SU ===========================
		if (strcmp(command, "!!") == 0) //Co yeu cau !!
		{
			if (cauLenhTruoc == NULL) //neu khong co cau lenh truoc
			{
				printf("No commands in history.\n");
				cauLenhTruoc = strdup(command);
			}
			else //neu co cau lenh truoc
			{
				command = cauLenhTruoc;
				printf("%s\n", cauLenhTruoc);
			}
		}
		else //khong co yeu cau !! thi luu cau lenh
		{
			cauLenhTruoc = strdup(command);

		}
		
		// ====================== KIEM TRA XEM CO & KHONG ===========================


		//======================= REDIRECTING ============================
	}


	return 0;
}
