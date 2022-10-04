<h1>Minishell de bg</h1>



NOTES
Ne pas utiliser plus d’une variable globale. Réfléchissez-y car vous devrez justifier son utilisation.
Ne pas interpréter de quotes (guillemets) non fermés ou de caractères spéciaux non
demandés dans le sujet, tels que \ (le backslash) ou ; (le point-virgule).



PROMPT
	Afficher un prompt en l’attente d’une nouvelle commande
	Posséder un historique fonctionnel

PARSING
	LEXER
		Traiter l'input
			Gérer ’ (single quote) qui doit empêcher le shell d’interpréter les méta-caractères
			présents dans la séquence entre guillemets.
			Gérer " (double quote) qui doit empêcher le shell d’interpréter les méta-caractères
			présents dans la séquence entre guillemets sauf le $ (signe dollar).
			< doit rediriger l’entrée.
			> doit rediriger la sortie.
			<< doit recevoir un délimiteur et lire l’input donné jusqu’à rencontrer une ligne
			contenant le délimiteur. Cependant, l’historique n’a pas à être mis à jour !
			>> doit rediriger la sortie en mode append.
			Implémenter les pipes (caractère |). La sortie de chaque commande de la pipeline
			est connectée à l’entrée de la commande suivante grâce à un pipe.
		Splitter les elements pour les stocker dans une structure

	PARSER
		Classer les elements
		SI Wildcard *
			lister toutes les occurrences
		Chercher le bon path pour les commandes
		Definir les entrees et sorties

EXECUTEUR
	Parcourir la liste de struct
		Faire les dups
		Lancer les execve













Gérer les variables d’environnement (un $ suivi d’une séquence de caractères)
qui doivent être substituées par leur contenu.
Gérer $? qui doit être substitué par le statut de sortie de la dernière pipeline
exécutée au premier plan.
Gérer ctrl-C, ctrl-D et ctrl-\ qui doivent fonctionner comme dans bash.
En mode interactif :
◦ ctrl-C affiche un nouveau prompt sur une nouvelle ligne.
◦ ctrl-D quitte le shell.
◦ ctrl-\ ne fait rien.
Votre shell doit implémenter les builtins suivantes :
◦ echo et l’option -n
◦ cd uniquement avec un chemin relatif ou absolu
◦ pwd sans aucune option
◦ export sans aucune option
◦ unset sans aucune option
◦ env sans aucune option ni argument
◦ exit sans aucune option
La fonction readline() peut causer des fuites de mémoire. Vous n’avez pas à les
gérer. Attention, cela ne veut pas pour autant dire que votre code, oui celui que
vous avez écrit, peut avoir des fuites de mémoire.
Tenez-vous en à ce qui est demandé dans le sujet. Ce qui n’est pas
demandé n’est pas obligatoire.
Si vous avez un doute sur une consigne du sujet, prenez bash comme
référence.
5
Chapitre IV
Partie bonus
Votre programme doit implémenter :
&& et || avec des parenthèses pour les priorités.
Les wildcards * doivent fonctionner pour le répertoire courant.