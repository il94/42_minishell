<h1 align="center">Minishell de bg</h1>

<h2 align="center">NOTES</h2>

	Token "<>"
	()  == unexpected token "("
	Gerer parenthese vides

	
	Remplacer les "ERROR" par les bons message d'erreur

	Une seule variable globale autorisée, et justifier son utilisation.
	Ne pas interpréter de caractères spéciaux non demandés dans le sujet, tels que \
	(le backslash) ou ; (le point-virgule).

<h2 align="center">PROMPT</h2>
	
	Afficher un prompt en l’attente d’une nouvelle commande
	Posséder un historique fonctionnel
	Pouvoir quitter le programme proprement


<h2 align="center">SIGNAUX</h2>
	
	Se renseigner sur le "mode interactif"

	Signaux à prendre en compte :
		ctrl-C affiche un nouveau prompt sur une nouvelle ligne.
		ctrl-D quitte le shell.
		ctrl-\ ne fait rien.



<h2 align="center">BUILTINS</h2>

	[echo et l’option -n] = int echo(char *str, char **args)
		Vérifier que les arguments sont valides (NULL ou n uniquement)
		Write sur la sortie standard la string donnée en paramètre
		SI args[0] != n
			Write un saut de ligne

	[cd uniquement avec un chemin relatif ou absolu] = int cd(char *path)
		Vérifier que les arguments sont valides (path existant et à portée)
		Chdir (vérifier que la commande a fonctionné)

	[pwd sans aucune option] = int pwd(void)
		Getcwd (vérifier que la commande a fonctionné)
		Write le retour de getcwd

	[export sans aucune option] = int export(AUCUNE IDEE MON REUF)
		Tester les dernières fonctions et comparer avec la commande de base

	[unset sans aucune option] = int unset(PAREIL)
		Tester les dernières fonctions et comparer avec la commande de base

	[env sans aucune option ni argument] = int env(char **envp)
		(Vérifier le comportement en cas d'envp NULL)
		Write l'ensemble de envp.

	[exit sans aucune option] = int exit(ENCORE PAREIL)
		Tester les dernières fonctions et comparer avec la commande de base



<h2 align="center">PARSING</h2>
<h3>LEXER</h3>

	Splitter les elements pour les stocker dans une liste de struct suivante :
		char *command
		char **arguments
		char delimiter[2]

	Liste des délimiteurs pour le Lexer :
		[<], [>], [<<], [>>], [|], [&&], [||]

	Cas spéciaux pour le Lexer :
		['] doit empêcher le shell d’interpréter les méta-caractères
			présents dans la séquence entre guillemets.
			Ne pas interpréter de quotes non fermés 
		["] doivent empêcher le shell d’interpréter les méta-caractères
			présents dans la séquence entre guillemets sauf le $ (signe dollar).
			Ne pas interpréter de quotes non fermés

<h3>PARSER</h3>

	Chercher le bon path pour les commandes
	Definir les entrees et sorties

	Cas spéciaux pour le Parser :
		SI on a une variable d’environnement, remplacer par son contenu
		SI on a $?, remplacer par le statut de sortie de la dernière pipeline
		exécutée au premier plan.
		SI on a un * (wildcard), lister toutes les occurrences



<h2 align="center">EXECUTEUR</h2>

	Parcourir la liste de struct
		Faire les dups
		Lancer les execve

	Liste des redirections pour l'Executeur :
		[<] doit rediriger l’entrée.
		[>] doit rediriger la sortie.
		[<<] doit recevoir un délimiteur et lire l’input donné jusqu’à
		rencontrer une ligne contenant le délimiteur. ATTENTION, ne pas mettre
		à jour l’historique.
		[>>] doit rediriger la sortie en mode append.
		[|] doit rediriger la sortie d'une commande vers la suivante
		[&&] doit permettre un enchaînement de commandes sans redirections
		[||] doit permettre d'executer une seconde commande uniquement si la
		première n'aboutit pas. ATTENTION, prendre en compte les parenthèses
		pour les priorités
