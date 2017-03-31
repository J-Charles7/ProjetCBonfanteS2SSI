#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct 
{
	int longueur;
	char * ch;
} chaine;

int len (char * str)
{
	char * c;
	int lenght = 0;
	c = str;
	while (*c != '\0')
	{
		lenght += 1;
		c += 1;
	}
	return lenght;
};


chaine char2str (char * str)
{
	chaine ret;
    	int i, l = len(str);
	char * ch = malloc (l * sizeof(char));
	/*for (i = 0; i <= l + 3 ; i++)
	{
		printf("%c-%02x ", *(str + i), *(str + i));
	}
	printf("\n");*/
	for (i = 0; i < l; i++)
	{
		*(ch + i) = *(str + i);
	}
	/*for (i = 0; i <= l + 3; i++)
	{
		printf("%c-%02x ", *(ch + i), *(ch + i));
	}*/
	ret.longueur = l;
	ret.ch = str;
	return ret;
}

char * ch2char (chaine ch)
{
	char * str = malloc((sizeof(char) * ch.longueur)+1);
	int i;
	for (i = 0; i < ch.longueur; i++)
	{
		*(str + i) = *(ch.ch + i);
	}
	str[ch.longueur] = '\0';
	for (i = 0; i <= ch.longueur + 2; i++)
	{
		printf("%c-%02x ", *(str + i), *(str + i));
	}
	return str;
}

chaine concat(chaine ch1, chaine ch2)
{
	chaine ret;
	int j, i, l = ch1.longueur + ch2.longueur;
	char * strF = malloc(sizeof(char) * l);
	for (i = 0; i < l; i++)
	{
	
		if (i < ch1.longueur)
		{
			*(strF + i) = *(ch1.ch + i);
		}
		else
		{
			if(i == ch1.longueur)
				j = 0;
			*(strF + i) = *(ch2.ch + j);
			j += 1;
		}
	}
	ret.ch = strF;
	ret.longueur = l;
	return ret;
}

chaine strcopy (chaine ch)
{
	chaine ret;
	int i, l = ch.longueur;
	char * str = malloc(sizeof(char) * l);
	for (i = 0; i < l; i++)
	{
		*(str + i) = *(ch.ch + i);
	}
	ret.ch = str;
	ret.longueur = ch.longueur;
	return ret;
}

chaine subCh(chaine ch, int debut, int fin)//Début et fin sont obtennus en comptant les caractères dans la chaîne à partir de 0
{
	if(debut > fin)
		exit(1);
	else
	{
		chaine ret;
		ret.longueur = fin - debut;
		char * c = malloc(sizeof(char) * ret.longueur);
		int i, j = 0;
		for (i = debut - 1; i < fin; i++)
		{
			*(c + j++) = *(ch.ch + i);
		}
		ret.ch = c;
		return ret;
	}
}

int count (chaine ch1, chaine ch2)//Nombre d'occurrences de ch1 dans ch2
{
	int i, j, k, carCorresp, nbOcc = 0;
	char * c;
	if (ch1.longueur > ch2.longueur)
	 	return -1;
 	else
 	{
 		for (i = 0; i < ch2.longueur; i++)
 		{
 			if (ch2.ch[i] == ch1.ch[0])
 			{
 				carCorresp = 1;
 				k = 1;
 //				printf("Correspondance == 1 avec i=%d caractère = %c\n", i, ch2.ch[i]);
	 			for (j = i + 1; j < i + ch1.longueur; j++)
	 			{
	 				if (ch1.ch[k++] == ch2.ch[j])
	 				{
//                        	printf("Correspondance interne: ch1 = %c-%d et ch2 = %c-%d\n",ch1.ch[k-1], k,ch2.ch[j], j);
	 					carCorresp += 1;
	 				}
	 			}
	 			if(carCorresp == ch1.longueur)
				{
				    nbOcc += 1;
				}
 			}
 		}
 	}

 	return nbOcc;
}

int * charAt(chaine ch, char car, int * tailleTab)
{
	int * ret, i, nb = 0, p = 0;
	for (i = 0; i < ch.longueur; i++)
	{
		if (*(ch.ch + i) == car)
			nb += 1;
	}
	printf("Nombre du caractère : %d \n", nb);
	ret = malloc(sizeof(int) * nb);
	for (i = 0; i < ch.longueur; i++)
	{
		if (*(ch.ch + i) == car)
		{
			* (ret + p++) = i;
		}
	}
	printf("\n");
	* tailleTab = nb;
	return ret;
}

int contains(chaine a, chaine b)
{
	if (count(a, b) > 0)
		return 1;
	else
		return 0;	
}

chaine * split (chaine ch, char car, int * nbreTokens)
{
	chaine * ret;
	longu len = strlen;
	int i, j, trouves, k = 0, *occ, debut;
	occ = charAt(ch, car, &trouves);
	ret = malloc(sizeof(chaine) * trouves + 1);
	if(trouves == 0)
	{
		return NULL;
	}

	else
	{
        if(occ[0] == 0)//La 1re lettre de ch est le caractère de séparation
        {
            debut = 0;
            * nbreTokens  = 0;
        }
        else//La 1re lettre de ch n'est pas le caractère de séparation
        {
            ret[0].ch = malloc(sizeof(char) * occ[0]);
            for (i = 0; i < occ[0]; i++)
            {
                *(ret[0].ch + i) = *(ch.ch + i);
            }
            ret[0].longueur = occ[0];
            printf("Premier token : %s\n", ret[0].ch);
            debut = 1;
            * nbreTokens  = 1;
        }
        int borneSup, z, consecutifs = 0;
        //Parcours de ch pour créer les tokens
        for (i = 0; i < trouves; i++)
        {
            k = 0;

            if (i == trouves - 1)
            {
                if(occ[i] == ch.longueur - 1)
                {
                    printf("I'm taking a break :)\n");
                   break;
                }
                else
                {
                    borneSup = ch.longueur;
                    ret[debut].ch = malloc(sizeof(char) * (ch.longueur - occ[i] - 1));
                    ret[debut].longueur = ch.longueur - occ[i] - 1;
                }
            }
            else
            {
                borneSup = occ[i + 1];
                ret[debut].ch = malloc(sizeof(char) * (occ[i + 1] - occ[i] - 1));
                ret[debut].longueur = occ[i + 1] - occ[i] - 1;
            }


            if(occ[i] + 1 != occ[i + 1] /*&& occ[trouves - 1] != ch.longueur - 1*/)
            {
                for (j = occ[i] + 1; j < borneSup; j++)
                {
                    ret[debut].ch[k++] = ch.ch[j];
                    //printf("RET = %c; CH = %c\n", ret[debut].ch[k-1], ch.ch[j]);

                }
                * nbreTokens  += 1;
                //printf("Nombre de tokens = %d et token %d = %s\n", * nbreTokens, debut, ret[debut].ch);
                debut += 1;
            }

        }


	}
	return ret;
}

int isAt(chaine ch1, chaine ch2)//Indique si ch1 est dans ch2
{
    int ret = 0, * occ, trouves, i, j, compteur;//Compteur de nombres de lettres correspondant de ch1 dans ch2
    occ = charAt(ch2, ch1.ch[0], &trouves);
    if (trouves == 0)
        return -1;
    while (ret == 0)
    {
        j = 0;
        compteur = 0;
        for (i = 0; i < ch1.longueur; i++)
        {
            if(ch1.ch[i] == ch2.ch[occ[j] + i])
                compteur += 1;
        }
        j += 1;
        if (compteur == ch1.longueur)
            ret += 1;
    }
    return ret;
}

int * tokenIndexes(chaine chCible, chaine motif, int * matchingMotifs)
{
    int val = isAt(motif, chCible), i, j, * occ, trouves, compteur, k, * ret;
    occ = charAt(chCible, motif.ch[0], &trouves);
    ret = malloc(sizeof(char) * trouves);
    * matchingMotifs = 0;
    for (i = 0; i < trouves; i++)
    {
        k = 0;
        compteur = 0;
        for (j = 0; j < motif.longueur; j++)
        {
            if(motif.ch[k++] == chCible.ch[j + occ[i]])
                compteur += 1;
        }
        if(compteur == motif.longueur)
        {
            k = 0;
            ret[* matchingMotifs] = occ[i];
            * matchingMotifs += 1;
        }
    }
    printf("Nombre de tokens = %d\n", * matchingMotifs);
    return ret;
}

void afficherChaine(chaine ch)
{
	printf("%s-%d\n", ch.ch, ch.longueur);
}


void afficherIncices(int * ch, int * taille)
{
	int i;
	printf("Indices d'occurences du car : ");
	for (i = 0; i < *taille; i++)
	{
		printf("%d ", ch[i]);
	}
	printf("\n");
} 

int lower(chaine ch1, chaine ch2)//La question est ch1 est-il lower que ch2
{
    int status = 1, i, lenght;
    lenght = ch1.longueur < ch2.longueur ? ch1.longueur : ch2.longueur;
    for (i = 0; i < lenght; i++)
    {
        if (toupper(ch1.ch[i]) > toupper(ch2.ch[i]))
        {
            status = 0;
            break;
        }

        if((toupper(ch1.ch[i]) == toupper(ch2.ch[i])) && (ch2.longueur < ch1.longueur) && (i == lenght - 1))
            status = 0;
    }
    return status;
}

int main (int argc, char * argv[])
{
/*	chaine c = char2str("Jean Charles");
	printf("%s - %d\n", c.ch, c.longueur);*/
	chaine c = {.longueur = 3, .ch ="Rap"};
	chaine d = {.longueur = 4, .ch ="peur"};
	chaine e = concat(c, d);
	//printf("%s - %d\n", e.ch, e.longueur);
	chaine f = strcopy (e);
	printf("%s - %d\n", f.ch, f.longueur);
	chaine g = {.longueur = len("agggffgfdgdfgfgfgfgfgggggfffga"), .ch ="agggffgfdgdfgfgfgfgfgggggfffga"};
	chaine h = {.longueur = 2, .ch ="fg"};
	//printf("Il y a %d -%s- dans -%s-\n", count(h, g), h.ch, g.ch);
	chaine j = subCh(e, 2, 6);
	//printf("%s-%d\n", j.ch, j.longueur);
	int i = 0, *ma, m;
	ma = charAt(e,'p', &m);
	printf("Dans le main\n");
	for (i=0; i < m; i++)
	{
		printf("%d ", ma[i]);
	}
	printf("\n");
	return 0;
}









