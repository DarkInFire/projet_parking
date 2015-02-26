#ifndef UTILISATEUR
#define UTILISATEUR

class Utilisateur
{
    private:
        unsigned int m_id;
        unsigned int m_idBadge;
        char m_nom[3];
        char m_prenom;
	
    public:
        Utilisateur(bool fromBadge, int id);
        ~Utilisateur();

        unsigned int getIdBadge();
        unsigned int getId();
        
        unsigned int getBadgeIdFromUtilisateur(int id);
        unsigned int getIdUtilisateurFromBadge(int id);
};

#endif