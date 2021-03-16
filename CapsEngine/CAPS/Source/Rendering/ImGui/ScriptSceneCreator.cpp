#include "ScriptSceneCreator.hpp"


    //system("cp fichier_clone_test.cpp test.cpp");
    //get_methode_name(76, &buffer);
    //printf("%s\n",buffer);

    //system("explorer.exe");
  //  set_name_classe();
//    system("cat test.cpp");


void ScriptSceneCreator::get_methode_name(int indice_curseur, char** buffer_methode)
{
    char buffer[256] = "";
    FILE* fichier_schema = NULL;
    fichier_schema = fopen("fichier_clone_test.cpp", "r");

    if (fichier_schema != NULL)
    {
        fseek(fichier_schema, indice_curseur, SEEK_SET);
        fgets(buffer, 14, fichier_schema);
        printf("%s\n", buffer);
        *buffer_methode = buffer;
    }
    else
    {
        printf("Impossible d'ouvrir le fichier...");
    }

}

void ScriptSceneCreator::set_name_classe() {

    int pas = 0;
    bool reading = true;
    FILE* fichier_schema = NULL;
    fichier_schema = fopen("test.cpp", "r+");
    char buffer[10] = "";
    char* buffer_methode;
    get_methode_name(76, &buffer_methode);
    //printf("%s\n",buffer_methode);

    if (fichier_schema != NULL)
    {
        //Acces


        while (fgets(buffer, 5, fichier_schema) != NULL)
        {
            pas++;
            std::cout << pas << std::endl;

        }

        fseek(fichier_schema, 76, SEEK_SET);
        fputs(" test::", fichier_schema);
        rewind(fichier_schema);
        fseek(fichier_schema, 136, SEEK_SET);
        fputs(" test::", fichier_schema);

        fclose(fichier_schema);


    }
    else
    {
        printf("Erreur ouverture...");
        exit(-1);
    }




}