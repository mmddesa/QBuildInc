#include <QCoreApplication>
//#include <QtDebug>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    // QBuildInc
    // Incrementa el número de versión
    // Formato QBuildInc.exe V[+|-]|S[+|-]|B[+|-]|R[+|-] [Fichero]

    #define FICH_VER "QMMDVer"

        char sFVer[256];         //Fichero de versión

        char sLinea[256];
        char *pTexto;
        char *sStop;

        int iOpc;   //Opción de línea de comando
        int iInc;   //Incremento/decremento

        long iVers;
        long iSubv;
        long iBuild;
        long iRev;

        FILE *fVer;

        iOpc = 0;   //Valores por defecto
        iInc = 0;
        strcpy(sFVer, FICH_VER);

        if (argc == 3)      //Si hay nombre de fichero
        {
            strcpy(sFVer, argv[2]);
        }


        if ((argc == 2) || (argc == 3))  //Opción [y fichero]
        {
            if (argv[1][1] == '+')
                iInc = 1;
            if (argv[1][1] == '-')
                iInc = 2;

            switch (argv[1][0])     //Opción
            {
            case 'v':
            case 'V':
                iOpc = 1;
                break;

            case 's':
            case 'S':
                iOpc = 2;
                break;

            case 'b':
            case 'B':
                iOpc = 3;
                break;

            case 'r':
            case 'R':
                iOpc = 4;
                break;

            }
        }

        fVer = fopen(sFVer, "r");


        if (fVer == NULL)	//Fichero inexistente
        {
            //Crea fichero nuevo

            fVer = fopen(sFVer, "w");

            fprintf(fVer, "MMD_VERV = 1\n");
            fprintf(fVer, "MMD_VERS = 1\n");
            fprintf(fVer, "MMD_VERB = 0\n");
            fprintf(fVer, "MMD_VERR = 0\n");

            iVers = 1;
            iSubv = 1;
            iBuild = 0;
            iRev = 0;

            fclose(fVer);

            if (iOpc == 0)
            {
                printf("Version %ld.%ld.%ld.%ld\n", iVers, iSubv, iBuild, iRev);
            }

        }
        else
        {
            //Leer la versión actual del fichero
            while (!feof(fVer))				//Lee líneas
            {
                fgets(sLinea, 256, fVer);

                pTexto = strstr(sLinea, "VERSION");	//Busca versión
                if (pTexto != NULL)
                {
                    continue;
                }

                pTexto = strstr(sLinea, "MMD_VERV");	//Busca versión
                if (pTexto != NULL)
                {
                    iVers = strtol(pTexto+10, &sStop, 10);
                    continue;
                }

                pTexto = strstr(sLinea, "MMD_VERS");	//Busca subversión
                if (pTexto != NULL)
                {
                    iSubv = strtol(pTexto+10, &sStop, 10);
                    continue;
                }

                pTexto = strstr(sLinea, "MMD_VERB");	//Busca build
                if (pTexto != NULL)
                {
                    iBuild = strtol(pTexto+10, &sStop, 10);
                    continue;
                }

                pTexto = strstr(sLinea, "MMD_VERR");	//Busca revisión
                if (pTexto != NULL)
                {
                    iRev = strtol(pTexto+10, &sStop, 10);
                    continue;
                }
            }

            fclose(fVer);	//Cierra el fichero

            switch (iOpc)
            {
            case 0:
                //Sin opciones incrementa build
                iBuild++;
                break;

            case 1:
                if (iInc == 1)
                    iVers++;
                else if (iInc == 2)
                    iVers--;
                printf("%ld", iVers);
                break;

            case 2:
                if (iInc == 1)
                    iSubv++;
                else if (iInc == 2)
                    iSubv--;
                printf("%ld", iSubv);
                break;

            case 3:
                if (iInc == 1)
                    iBuild++;
                else if (iInc == 2)
                    iBuild--;
                printf("%ld", iBuild);
                break;

            case 4:
                if (iInc == 1)
                    iRev++;
                else if (iInc == 2)
                    iRev--;
                printf("%ld", iRev);
                break;
            }

            fVer = fopen(sFVer, "w");	//Abre el nuevo fichero

            fprintf(fVer, "MMD_VERV = %ld\n", iVers);
            fprintf(fVer, "MMD_VERS = %ld\n", iSubv);
            fprintf(fVer, "MMD_VERB = %ld\n", iBuild);
            fprintf(fVer, "MMD_VERR = %ld\n", iRev);

            fclose(fVer);

            if (iOpc == 0)
            {
                printf("Version %ld.%ld.%ld.%ld\n", iVers, iSubv, iBuild, iRev);
            }
        }


        return 0;
}
