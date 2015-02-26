#include "utilisateur.h"

/* 	Constructeur de Utilisateur
	Si fromBadgeOrId = 0, instancie depuis l'id
		sinon, depuis le badge
*/
Utilisateur::Utilisateur(bool fromBadge, int id)
{
    //On attribut un ID à la classe en fonction de l'utilisateur
    if (fromBadge)
    {
        m_id = getIdUtilisateurFromBadge(id);
        m_idBadge = id;
    }
    else
    {
        m_id = id;
        m_idBadge = getBadgeIdFromUtilisateur(id);
	}
}

Utilisateur::~Utilisateur()
{
    
}

unsigned int Utilisateur::getIdBadge()
{
    return m_idBadge;
}

unsigned int Utilisateur::getId()
{
    return m_id;
}

unsigned int Utilisateur::getBadgeIdFromUtilisateur(int id)
{
    
}

unsigned int Utilisateur::getIdUtilisateurFromBadge(int id)
{
    
}