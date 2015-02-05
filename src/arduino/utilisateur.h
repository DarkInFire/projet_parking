#IFNDEF UTILISATEUR
#DEFINE UTILISATEUR
#include <stdio>

class Utilisateur
{
    private:
        unsigned short int m_id;
		unsigned short int m_idBadge;
		char[3] m_nom;
		char[3] m_prenom;
		
	public:
		Utilisateur(bool fromBadgeOrId, int id);
		~Utilisateur();
		
		int getIdBadge();
		unsigned short int getIdBadge();
};

#ENDIF