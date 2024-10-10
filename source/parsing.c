#include "minishell.h"

//ATTENTION il faut FREE chaque string et aussi chaque token donc double free car double malloc



//recevoir le string
//checker les quotes
//checker les quotes et si elles ne sont pas fermer demander un nouvel input utilisateurs
//utiliser strjoin pour coller les input ensemble
//checker les quotes
//par argument on entend chaque commande+args
//si cest pas vide on cree une premiere commande
//on copie jusquau separateur
//la liste cest genre commande into commande
//le plus simple cest que les commandes se pointe lune vers la suivante mais aussi que elles aient un element qui dit si
//y a un redirecteur et donc quel pointe vers le bon out ou in en fonction


//on malloc et on accroche lancien sur le nouveau
void	parsing(char *input, t_command **command)
{
	t_parsing	*p;

	init_struct_parsing(&p);
	while (input[p->i] != '\0')
	{
		parsing2(input, p);
		convert_command(&(p->t), command, &(p->in), &(p->o), input[p->i]);
		if (input[p->i] == '|')
		{
			p->i++;
			p->j++;
			set_pipein(command);
		}
	}
	set_pipeout(command);
	print_command(command);
	p->j = 0;
	free(p);
}
void	init_struct_parsing(t_parsing **p)
{
	*p = malloc(sizeof(t_parsing));
	(*p)->t = NULL;
	(*p)->in = NULL;
	(*p)->o = NULL;
	(*p)->i = 0;
	(*p)->j = 0;
}

void	parsing2(char *input, t_parsing *p)
{
	while (input[p->i] != '|' && input[p->i] != '\0')
	{
		p->l = 0;
		while (is_white_space(input[p->i]))
			p->i++;
		if (input[p->i] == '\0' || input[p->i] == '|')
			break ;
		else if (is_redir(input[p->i]))
			p->l = create_redir(input + p->i, &(p->in), &(p->o), p->j);
		else 
			p->l = create_command(input + p->i, &(p->t));
		p->i = p->i + p->l;
		if (p->l == 0)
			p->i++;
	}
}

void print_command(t_command **head)
{
    t_command *current = *head;

	printf("TEST:\n");
    while (current != NULL)
    {
        // Imprimer les arguments
        printf("Arguments:\n");
        if (current->arg != NULL)
        {
            for (int i = 0; current->arg[i] != NULL; i++)
            {
                printf("  arg[%d] = %s\n", i, current->arg[i]);
            }
        }
        else
        {
            printf("  No arguments\n");
        }

        // Imprimer la redirection d'entrée
        if (current->inpath)
        {
            printf("  Input redirection: in\n");
        }
        else
        {
            printf("  No input redirection\n");
        }

        // Imprimer la redirection de sortie
        if (current->outpath)
            printf("  Output redirection: out\n");
        else
        {
            printf("  No output redirection\n");
        }

        // Passer à l'élément suivant
        current = current->next;
        printf("\n");  // Ajouter une ligne vide entre les commandes
    }
}

void	set_pipein(t_command **head)
{
    t_command *current;

	current = *head;
	if (current == NULL)
		return ;
	while (current->next != NULL)
		current = current->next;
	current->pipein = true;
	return ;
}

void	set_pipeout(t_command **head)
{
    t_command *current = *head;
	while (current != NULL)
	{
		if (current->pipein == true)
			current->next->pipeout = true;
		current = current->next;
	}
	return ;
}

void	initialize_command(t_command *new)
{
	new->arg = NULL;
	new->inpath = NULL;
	new->outpath = NULL;
	new->pipein = false;
	new->pipeout = false;
	new->next = NULL;
}
//on est deja envoyer au bon endroit

// /!\ ATTENTION GERER LES EXIT ET FREE ENCORE
//SI JAMAIS les outfile et infile ne
//sarrete pas a lespace mais copie tout jusqa la fin ou la pipe