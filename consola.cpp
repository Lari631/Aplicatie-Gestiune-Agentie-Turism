#include "consola.h"
#include "oferta.h"
#include "repo.h"
#include <iostream>

using std::cin;
using std::cout;

void UI::afisare_oferte() {
    vector <Oferta> oferte=service.get_all();
    //VectorDinamic<Oferta> oferte=service.get_all();
    for (const Oferta &o:oferte)
    {
        cout<<o.get_denumire()<<" "<<o.get_destinatie()<<" "<<o.get_tip()<<" "<<o.get_pret();
        cout<<"\n";
    }
}

void UI::afisare_wishlist(){
    vector <Oferta> oferte= service.get_elemente_wishlist();
    for (const Oferta &o:oferte)
    {
        cout<<o.get_denumire()<<" "<<o.get_destinatie()<<" "<<o.get_tip()<<" "<<o.get_pret();
        cout<<"\n";
    }
}

void UI::afisare_nr_elem_cos(){
    cout << "Numarul de elemente din cos este " << service.get_elemente_wishlist().size() << "\n";
}

void UI::start_ui()
{
    while(true)
    {
        cout<<"Meniu:\n";
        cout<<"1. Adaugare oferta\n";
        cout<<"2. Stergere oferta\n";
        cout<<"3. Cautare oferta\n";
        cout<<"4. Modificare oferta\n";
        cout<<"5. Ordonare oferte\n";
        cout<<"6. Filtrare oferte\n";

        cout<<"7. Adauga in wishlist\n";
        cout<<"8. Goleste wishlist\n";
        cout<<"9. Genereaza wishlist\n";
        cout<<"10. Export\n";

        cout<<"11. Afisare oferte\n";
        cout<<"12. Afisare wishlist\n";

        cout<<"13. Afisare nr oferte din fiecare tip\n";

        cout<<"14. Undo\n";

        cout<<"0.Iesire din program\n";
        int cmd=0;
        cout<<"Alegeti comanda: ";
        cin>>cmd;
        if (cmd==0)
            break;
        else
        {
            if(cmd==1)
            {
                double pret;
                string tip,denumire,destinatie;
                cout<<"Introduceti denumirea ofertei: ";
                cin>>denumire;
                cout<<"Introduceti destinatia calatoriei: ";
                cin>>destinatie;
                cout<<"Introduceti tipul ofertei: ";
                cin>>tip;
                cout<<"Introduceti pretul ofertei: ";
                cin>>pret;
                try {
                    service.add_oferta(denumire,destinatie,tip,pret);
                    cout<<"Oferta adaugata cu succces!\n";
                }
                catch(RepoException &ex)
                {
                    cout<<ex.get_mesaj();
                }

            }
            else if(cmd==2)
            {
                double pret;
                string tip,denumire,destinatie;
                cout<<"Introduceti denumirea ofertei: ";
                cin>>denumire;
                cout<<"Introduceti destinatia calatoriei: ";
                cin>>destinatie;
                cout<<"Introduceti tipul ofertei: ";
                cin>>tip;
                cout<<"Introduceti pretul ofertei: ";
                cin>>pret;
                try{
                    service.delete_oferta(denumire,destinatie,tip,pret);
                    cout<<"Oferta stearsa cu succces!\n";
                }
                catch (RepoException &ex)
                {
                    cout<<ex.get_mesaj();
                }

            }
            else if(cmd==3)
            {
                double pret;
                string tip,denumire,destinatie;
                cout<<"Introduceti denumirea ofertei: ";
                cin>>denumire;
                cout<<"Introduceti destinatia calatoriei: ";
                cin>>destinatie;
                cout<<"Introduceti tipul ofertei: ";
                cin>>tip;
                cout<<"Introduceti pretul ofertei: ";
                cin>>pret;
                if(service.find_oferta_nou(denumire,destinatie,tip,pret)){
                    cout<<"Oferta existenta!\n";
                }
                else cout<<"Oferta inexistenta!\n";
            }
            else if(cmd==4)
            {
                double pret;
                string tip,denumire,destinatie;
                cout<<"Introduceti datele ofertei care vreti sa fie modificata: \n";
                cout<<"Introduceti denumirea ofertei: ";
                cin>>denumire;
                cout<<"Introduceti destinatia calatoriei: ";
                cin>>destinatie;
                cout<<"Introduceti tipul ofertei: ";
                cin>>tip;
                cout<<"Introduceti pretul ofertei: ";
                cin>>pret;
                if(!service.find_oferta_nou(denumire,destinatie,tip,pret))
                    cout<<"Oferta inexistenta:(\n";
                else
                {
                    double pret_nou;
                    string tip_nou,denumire_noua,destinatie_noua;
                    cout<<"Introduceti datele noi ale ofertei: \n";
                    cout<<"Introduceti denumirea ofertei: ";
                    cin>>denumire_noua;
                    cout<<"Introduceti destinatia calatoriei: ";
                    cin>>destinatie_noua;
                    cout<<"Introduceti tipul ofertei: ";
                    cin>>tip_nou;
                    cout<<"Introduceti pretul ofertei: ";
                    cin>>pret_nou;
                    service.modify_oferta(denumire,destinatie,tip,pret,denumire_noua,destinatie_noua,tip_nou,pret_nou);

                    cout<<"Oferta modificata cu succes!\n";
                }
            }
            else if(cmd==5){
                vector<Oferta> oferte_ordonate=service.ordonare_dupa_pret();
                cout<<"Oferte sortate dupa pret: \n";
                for (const Oferta &o:oferte_ordonate)
                {
                    cout<<o.get_denumire()<<" "<<o.get_destinatie()<<" "<<o.get_tip()<<" "<<o.get_pret();
                    cout<<"\n";
                }

            }
            else if(cmd==6){
                string destinatie;
                cout<<"Introduceti destinatia dupa care se filtreaza: \n";
                cin>>destinatie;
                vector<Oferta> oferte_filtrate=service.filtrare_dupa_destinatie(destinatie);
                if(oferte_filtrate.size()==0)
                    cout<<"Nu exista oferte cu destinatia data\n";
                else{
                    cout<<"Oferte cu destinatia dorita: \n";
                    for (const Oferta &o:oferte_filtrate)
                    {
                        cout<<o.get_denumire()<<" "<<o.get_destinatie()<<" "<<o.get_tip()<<" "<<o.get_pret();
                        cout<<"\n";
                    }
                }
            }
            else if(cmd==7){
                cout<<"Introduceti denumirea ofertei: \n";
                string denumire;
                cin>>denumire;
                //service.add_to_wishlist(denumire);
                afisare_nr_elem_cos();
            }
            else if(cmd==8){
                service.empty_wishlist();
                cout<<"Wishlist-ul a fost golit";
                afisare_nr_elem_cos();
            }
            else if(cmd==9){
                cout<<"Introduceti numarul de elemente din wishlist: ";
                int capacitate;
                cin>>capacitate;
                service.generare_wishlist(capacitate);
                afisare_wishlist();
                afisare_nr_elem_cos();
            }
            else if(cmd==10){
                string nume_fisier;
                cout<<"Introduceti numele fisierului in care se salveaza cosul: ";
                cin>>nume_fisier;
                service.export_fisier(nume_fisier);
                cout<<"Salvare efectuata cu succes!\n";
            }
            else if (cmd==11)
            {
                afisare_oferte();
            }
            else if(cmd==12){
                afisare_wishlist();
            }
            else if(cmd==13){
                map<string,int> dictionar=service.frecventa_tipuri();
                //afisare elemente din map
                for(auto const &x:dictionar){
                    cout<<x.first<<" -> "<<x.second;
                    cout<<"\n";
                }
            }
            else if(cmd==14){
                service.undo();
                cout<<"Gata\n";
            }
            else cout<<"Comanda invalida!\n";

        }

    }

}
