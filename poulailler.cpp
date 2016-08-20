#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

class Coq
{
	string nom;
	int age;
	public:void saisie();
		   void affiche();
		   int getage(){return age;}
		   string getNom(){ return(nom);}
		   bool operator<(Coq a);
		   bool operator>(Coq a);
		   template<class A,class B> void cocorico(A tab,B &eggs);
		   template<class A,class B> void coco(A tab,B &eggs);
};

bool Coq::operator<(Coq a)
{
	if(age<a.getage())
		return true;
	else
		return false;
}

bool Coq::operator>(Coq a)
{
	if(age>a.getage())
		return true;
	else
		return false;
}

void Coq::saisie()
{
	cout<<"Nom ?"<<endl;
	cin>>nom;
	cout<<"Age ?"<<endl;
	cin>>age;
}

void Coq::affiche()
{
	cout<<"Nom : "<<nom<<endl;
	cout<<"Age : "<<age<<endl;
}

template<class A,class B> void Coq:: cocorico(A tab,B &eggs)
{
	cout<<"COCORICO !!!!!"<<endl;
	for(A::iterator it=tab.begin();it!=tab.end();it++){
		it->pondre(eggs);
	}
}

template<class A,class B> void Coq:: coco(A tab,B &eggs)
{
	cout<<"COCO !!!!!"<<endl;
	for(A::iterator it=tab.begin();it!=tab.end();it++)
	{
		it->pondre(eggs);
		it++;
		if(it==tab.end()){break;}
	}
}
class Poule
{
	string nom;
	float poids;
	public:
	void saisie();
	void affiche();
	float getpoids(){return poids;}
	template<class A> void pondre(A& tab);
	string getnom(){ return nom;}
	bool operator<(Poule a);
	bool operator>(Poule a);
	bool operator ==(Poule a);
};

bool Poule::operator==(Poule a)
{
	if(nom==a.nom && poids==a.poids)
		return true;
	else
		return false;
}

bool Poule::operator<(Poule a)
{
	if(poids<a.poids)
		return true;
	else
		return false;
}

bool Poule::operator>(Poule a)
{
	if(poids>a.poids)
		return true;
	else
		return false;
}

void Poule::saisie()
{
	cout<<"Nom ?"<<endl;
	cin>>nom;
	cout<<"Poids ?"<<endl;
	cin>>poids;
}

void Poule::affiche()
{
	cout<<"Nom : "<<nom<<endl;
	cout<<"Poids: "<<poids<<endl;
}

template<class T> void Poule:: pondre(T& tab)
{
	float poidsoeuf=poids/10;
	typedef typename T::value_type U;
	U temp;
	temp.poids=poidsoeuf;
	temp.saisie();
	tab.push_back(temp);
	cout<<"L oeuf a bien ete pondu et pese " <<temp.poids<<endl;
	temp.affiche();
}
class Oeuf:public Poule
{
	char qualité;
	public:
	void saisie();
	void affiche();
};

void Oeuf::saisie()
{
	cout<<"Qualite de l oeuf ?"<<endl;
	cin>>qualité;
}

void Oeuf::affiche(){cout<<"Qualite de l'oeuf (A, B, C) : "<<qualité<<endl;}

void menu(int &choix)
{
	do{
		cout<<"0 Tout afficher"<<endl;
		cout<<"1 saisie et affiche list de poules (insertion au debut)"<<endl;
		cout<<"2 saisie et affiche vector de coqs (insertion au debut)"<<endl;
		cout<<"3 somme des poids en kg des poules"<<endl;
		cout<<"4 moyenne des age des coqs"<<endl;
		cout<<"5 le coq le plus jeune et la poule la plus lourde forment un couple"<<endl;
		cout<<"6 le coq fait cocorico et toute les poules pondent(poids oeufs =0,1 poids poule)"<<endl;
		cout<<"7 le coq fait coco et une poule sur 2 pondent"<<endl;
		cout<<"8 suppression de la moitié de la list et du vector"<<endl;
		cout<<"9 Creer une poule dynamiquement et voir si elle existe dans la liste suivant son nom et son poids"<<endl;
		cout<<"1O Tri par ordre croissant du poids des poules"<<endl;
		cout<<"11 quitter"<<endl;
		cin>>choix;
		if(choix<0||choix>11)
			cout<<"Choix non valide"<<endl;
	}while(choix<0&&choix>11);
}

template<class A,class B> void saisie(A&t)
{
	int n;
	cout<<"Combien d element voulez vous ?"<<endl;
	cin>>n;
	for(int i=0;i<n;i++){
		B tab;
		tab.saisie();
		t.insert(t.begin(),tab);
	}
}

template<class A> void affiche(A tab)
{
	for(A::iterator it=tab.begin();it!=tab.end();it++){it->affiche();}
}

void somme(list<Poule> tab)
{
	float somme =0;
	for(list<Poule>::iterator it=tab.begin();it!=tab.end();it++)
	{
		somme+=it->getpoids();
	}
	cout<<"La somme des poids des poules en kg = "<<somme/1000<<endl;
}

void moyenne(vector<Coq> tab)
{
	float	agetot=0;
	int		nbr=0;
	for(vector<Coq>::iterator it=tab.begin();it!=tab.end();it++)
	{
		agetot+=it->getage();
		nbr++;
	}
	float moy=agetot/nbr;
	cout<<"La moyenne des ages des coq vaut : "<<moy<<endl;
}

template<class T>bool bigger(T a,T b){return(a>b);}

Coq couplage(list<Poule> po, vector<Coq> co)
{
	sort(co.begin(),co.end());
	po.sort(bigger<Poule>);
	cout<<"Le coq le plus jeune : "<<endl;
	co.begin()->affiche();
	cout<<"La poule la plus lourde "<<endl;
	po.begin()->affiche();
	cout<<" forment un couple"<<endl;
	return(*(co.begin()));
}

template<class A>
void suppression(A & tab)
{
	int s =tab.size()/2;
	A::iterator it = tab.begin(); 
	for(int i=0;i<s;i++)
	{it++;}
	tab.erase(tab.begin(),it);
}
/*template<class A,class B,class C> //Version template complète au cas ou il faut chercher dans la liste et le vecteur
  void recherche(A tab,B tab2)
  {cout<<"Quel element voulez vous rechercher ?"<<endl;
  C*p;
  p=new C:
  p->saisie();
  A::iterator it=find(tab.begin(),tab.end(),*p);
  if(it==tab.end())
  {cout<<"L element n est pas dans la liste"<<endl;}
  else
  {cout<<"Voici l element "<<endl; 
  p->affiche();
  }
  B::iterator it=find(tab2.begin(),tab2.end(),*p);
  if(it==tab2.end())
  {cout<<"L element n est pas dans le vecteur"<<endl;}
  else
  {cout<<"Voici l element "<<endl; 
  p->affiche();
  }
  }
  */
void recherche(list<Poule> tab)//Version juste pour la liste ou le vecteur
{
	cout<<"Quel element voulez vous rechercher ?"<<endl;
	Poule *p;
	p=new Poule;
	p->saisie();
	list<Poule>::iterator it=find(tab.begin(),tab.end(),*p);
	if(it==tab.end())
		cout<<"L element n est pas dans la liste"<<endl;
	else
	{	cout<<"Voici l element "<<endl;
		p->affiche();
	}
}
void main()
{
	list<Poule>po;
	vector<Coq>co;
	list<Oeuf>o;
	int choix;
	Coq young;
	do{
		menu(choix);
		switch(choix)
		{
			case 0:
				if(po.size()==0)
					cout<<"La liste est vide"<<endl;
			else
				affiche<list<Poule>>(po);
			if(co.size()==0)
				cout<<"Le vecteur est vide"<<endl;
			else
				affiche<vector<Coq>>(co);
			break;
			case 1:
				saisie<list<Poule>,Poule>(po);
				affiche<list<Poule>>(po);
				break;
			case 2:
				saisie<vector<Coq>,Coq>(co);
				affiche<vector<Coq>>(co);
				break;
			case 3 :
					if(po.size()==0)
						 cout<<"La liste est vide"<<endl;
					else
						somme(po);
				break;
			case 4:
						if(co.size()==0)
							cout<<"Le vecteur est vide"<<endl;
						else
							moyenne(co);
				break;
			case 5:
						if(co.size()==0)
							cout<<"Le vecteur est vide"<<endl;
						else
							young=couplage(po,co);
				break;
			case 6:
				if(co.size()==0)
					cout<<"Le vecteur est vide"<<endl;
				else
					young.cocorico(po,o);
				break;
			case 7 :
				if(co.size()==0)
					cout<<"Le vecteur est vide"<<endl;
				else
					young.coco(po,o);
				break;
			case 8:
				if(po.size()==0)
					cout<<"La liste est vide"<<endl;
				else
					suppression(po);
				affiche<list<Poule>>(po);
				if(co.size()==0)
					cout<<"Le vecteur est vide"<<endl;
				else
					suppression(co);
				affiche<vector<Coq>>(co);
				 break;
			case 9:
				if(po.size()==0)
					cout<<"La liste est vide"<<endl;
					else
						recherche(po);
				break;
			case 10:
				if(po.size()==0)
					cout<<"La liste est vide"<<endl;
				else
					po.sort();
				affiche<list<Poule>>(po);
				break;
		} 
	}while(choix!=11);
}
//Examen fait par Thomas Bozzini (Bozzi)
