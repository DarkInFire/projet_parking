/* 	Constructeur de Utilisateur
	Si fromBadgeOrId = 0, instancie depuis l'id
		sinon, depuis le badge
*/
Utilisateur::Utilisateur(bool fromBadgeOrId, int id)
{
    //On attribut un ID à la classe en fonction de l'utilisateur
	if (fromBadgeOrId)
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