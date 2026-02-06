#include <iostream>
#include <string>
#pragma warning(disable : 4996)
#include <ctime>
#include <cstdlib>
using namespace std;

int idProd=0;//ID Base Produtos
float iva = 0.23;
float precoCusto = 1.30;
int idCliente = 1;
int idFatura = 11111;

void limpaEcra(){
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int menu() {
    int x;
    cout << endl << "@@@@@@@@@@@@@@@@@@" << endl;
    cout << "@                @" << endl;
    cout << "@  1 - Venda     @" << endl;
    cout << "@  2 - Produto   @" << endl;
    cout << "@  3 - Sair      @" << endl;
    cout << "@                @" << endl;
    cout << "@@@@@@@@@@@@@@@@@@" << endl;
    cin >> x;
    limpaEcra();
    return x;
}

void inserir(string** x) {
    string name;
    float preco;
    int stock;
    bool repetido;

    idProd++;
    x[idProd][0] = idProd;
    limpaEcra();

    do {
        repetido = 0;
        cout << endl << "@@@@@@@@@@@@@@@@@@" << endl;
        cout << "@                @" << endl;
        cout << "@  Inserir Nome: @" << endl;
        cout << "@                @" << endl;
        cout << "@@@@@@@@@@@@@@@@@@" << endl;
        cin >> name;
        limpaEcra();
        //Verificar Nome Repetido
        for (int i = 0; i <= idProd; i++)
        {
            string nomeExiste = x[i][1];
            if (nomeExiste.length() == name.length()) {
                repetido = 1;
                for (size_t j = 0; j < name.length(); j++) {
                    if (tolower(nomeExiste[j]) != tolower(name[j])) {
                        repetido = 0;
                        break;
                    }
                }
            }
		}

        x[idProd][1] = name;
        if (repetido)
            cout << "Nome Repetido" << endl;
    } while (repetido);

    do {
        cout << endl << "@@@@@@@@@@@@@@@@@@" << endl;
        cout << "@                @" << endl;
        cout << "@ Inserir Stock: @" << endl;
        cout << "@                @" << endl;
        cout << "@@@@@@@@@@@@@@@@@@" << endl;
        cin >> stock;
        limpaEcra();

        if (stock <= 0)
            cout << "Stock invalido";
    } while (stock <= 0);


    x[idProd][2] = to_string(stock);

    do{
        cout << endl << "@@@@@@@@@@@@@@@@@@" << endl;
        cout << "@                @" << endl;
        cout << "@ Inserir Preco: @" << endl;
        cout << "@                @" << endl;
        cout << "@@@@@@@@@@@@@@@@@@" << endl;
        cin >> preco;
        limpaEcra();
        if (preco <= 0)
            cout << "Preco invalido";
    } while (preco <= 0);

    x[idProd][3] = to_string(preco);
}

int editarOP(int op, string** x) {
    int i;
    string name;
    float preco;
    int stock;
    bool repetido;
    
    if (op > idProd)
    {
        cout << "Opcao Invalida";
        return 0;
    }

    cout << endl << "@@@@@@@@@@@@@@@@@@" << endl; //UI
    cout << "@                @" << endl;
    cout << "@  1 - Nome      @" << endl;
    cout << "@  2 - Stock     @" << endl;
    cout << "@  3 - Preco     @" << endl;
    cout << "@                @" << endl;
    cout << "@@@@@@@@@@@@@@@@@@" << endl;
    cin >> i;
    limpaEcra();
    switch (i) {
    case 1: //Editar o nome
        do {
            repetido = 0;
            cout << endl << "@@@@@@@@@@@@@@@@@@" << endl;
            cout << "@                @" << endl;
            cout << "@   Novo Nome:   @" << endl;
            cout << "@                @" << endl;
            cout << "@@@@@@@@@@@@@@@@@@" << endl;
            cin >> name;
            limpaEcra();
            //Verificar Nome Repetido
            for (int i = 0; i <= idProd; i++)
            {
                string nomeExiste = x[i][1];
                if (nomeExiste.length() == name.length()) {
                    repetido = 1;
                    for (size_t j = 0; j < name.length(); j++) {
                        if (tolower(nomeExiste[j]) != tolower(name[j])) {
                            repetido = 0;
                            break;
                        }
                    }
                }
            }
            if (repetido)
                cout << "Nome Repetido" << endl;
        } while (repetido);
        x[op][1] = name;
        break;

    case 2: //Editar o Stock
        do {
            cout << endl << "@@@@@@@@@@@@@@@@@@" << endl;
            cout << "@                @" << endl;
            cout << "@  Stock Atual:  @" << endl;
            cout << "@                @" << endl;
            cout << "@@@@@@@@@@@@@@@@@@" << endl;
            cin >> stock;
            limpaEcra();
            if (stock <= 0)
                cout << "Stock invalido";
        } while (stock <= 0);
        x[op][2] = to_string(stock);
        break;

    case 3: //Editar o Preco
        do {
            cout << endl << "@@@@@@@@@@@@@@@@@@" << endl;
            cout << "@                @" << endl;
            cout << "@ Inserir Preco: @" << endl;
            cout << "@                @" << endl;
            cout << "@@@@@@@@@@@@@@@@@@" << endl;
            cin >> preco;
            limpaEcra();
            if (preco <= 0)
                cout << "Preco invalido";
        } while (preco <= 0);
        x[op][3] = to_string(preco);
        break;

    default:
        limpaEcra();
        cout << "Opcao Invalida";
        break;
    }

}

void cancelarCarrinho(string** x,string** carrinho) {

    for (int i = 1; i <= idProd; i++)
    {
        for (int j = 1; j <= idProd; j++)
        {                                   
            if (x[j][1] == carrinho[i][1]) {
                
                int n = stoi(carrinho[i][2]);
                n += stoi(x[j][2]);
                x[j][2] = to_string(n);
            }
        }

        carrinho[i][0] = "";
        carrinho[i][1] = "";
        carrinho[i][2] = "";
        carrinho[i][3] = "";
    }
}

int eliminar(int op, string** x) {
    limpaEcra();
    cout << endl << "@@@@@@@@@@@@@@@@@@" << endl;
    cout << "@                @" << endl;
    cout << "@ Tem a Certeza? @" << endl;
    cout << "@      S/N       @" << endl;
    cout << "@                @" << endl;
    cout << "@@@@@@@@@@@@@@@@@@" << endl;

    string resposta;
    cin.ignore();
    cin >> resposta;
    limpaEcra();
    if (tolower(resposta[0]) != tolower('s')) {
        return 0;
    }   
    
    for (int i = 0; i <= idProd; i++) // Eliminar = trocar tudo a frente do ID a ser apagado
    {
        if (i > op) {
            x[i - 1][0] = i - 1;
            x[i - 1][1] = x[i][1];
            x[i - 1][2] = x[i][2];
            x[i - 1][3] = x[i][3];
        }
    }
    x[idProd][1] = "";
    idProd--; // Esquecer ultimo item
}

int listEd(string** x,int aux) {
    int op;
    bool notempty = 0;
    limpaEcra();
    if (idProd < 1) {   //Quando ID = 0 Quer dizer que nenhum item existe ainda
        cout << "Nenhum produto encontrado";
        return 0;
    }
    for (int i = 0; i <= idProd; i++)   //Verificar se o tamanho do nome � 0 em todos, se sim entao nao existem items
    {
        if (x[i][1].length()>0) {
            notempty = 1;
        }
    }
    if (!(notempty)) {
        cout << "Nenhum produto encontrado";
        return 0;
    }
    
    cout << endl << "@@@@@@@@@@@@@@@@@@" << endl;   //inicio Lista
    cout << "| Selecione um ID:" << endl;
    for (int i = 1; i <= idProd; i++)
    {
        cout << "|" << endl;
        cout << "| " << i << " - " << x[i][1] << endl;
    }
    cout << "|" << endl;
    cout << "@@@@@@@@@@@@@@@@@@" << endl;
    cin >> op;  // ID a ser Editado ou Eliminado
    limpaEcra();
    switch (aux)
    {
        case 1:
            editarOP(op, x);
            break;
        case 2:
            limpaEcra();
            eliminar(op, x);
            break;
        default:
        break;
    } 
    
}

void prodBase(string** x) {
    idProd = 4;
    x[1][0] = "1";
    x[1][1] = "Meteora - Linkin Park";
    x[1][2] = "5";
    x[1][3] = "10";
    x[2][0] = "2";
    x[2][1] = "Piss in the River - Joji";
    x[2][2] = "10";
    x[2][3] = "15";
    x[3][0] = "3";
    x[3][1] = "Anjo da Guarda - Antonio Variacoes";
    x[3][2] = "3";
    x[3][3] = "18";
    x[4][0] = "4";
    x[4][1] = "The Darkside of the Moon - Pink Floid";
    x[4][2] = "6";
    x[4][3] = "14.30";
}

int prodList(string** x, bool user) {           //0 -> Cliente | 1 -> Admin
    bool notempty = 0;
    limpaEcra();
    if (idProd < 1) {   //Quando ID = 0 Quer dizer que nenhum item existe ainda
        limpaEcra();
        cout << "Nenhum produto encontrado";
        return 0;
    }
    for (int i = 0; i <= idProd; i++)   //Verificar se o tamanho do nome � 0 em todos, se sim entao nao existem items
    {
        if (x[i][1].length() > 0) {
            notempty = 1;
        }
    }
    if (!(notempty)) {
        limpaEcra();
        cout << "Nenhum produto encontrado";
        return 0;
    }

    cout << endl << "@@@@@@@@@@@@@@@@@@" << endl;   //inicio Lista

    for (int i = 1; i <= idProd; i++)
    {
        if (x[i][2] != "0") // So mostrar produtos com stock
        {
            cout << "|" << endl;
            cout << "| " << i << " - " << x[i][1] << " - ";
            
            if (user)   
                cout << x[i][3] << " € - " << x[i][2] << endl;
            else 
                cout << stod(x[i][3]) * precoCusto << " € - " << x[i][2] << endl;

        }else {
            cout << "|" << endl;
            cout << "| " << i << " - " << x[i][1] << " Fora de Stock " << endl;
        }
    }
    cout << "|" << endl;
    cout << "@@@@@@@@@@@@@@@@@@" << endl;
    cout << "Prima Enter";
    cin.ignore();
    cin.get(); 
    limpaEcra();
}

int vendaUI() {
    int x;
    cout << endl << "@@@@@@@@@@@@@@@@@@" << endl;
    cout << "@                @" << endl;
    cout << "@  1 - Produtos  @" << endl;
    cout << "@  2 - Adicionar @" << endl;
    cout << "@  3 - Carrinho  @" << endl;
    cout << "@  4 - Checkout  @" << endl;
    cout << "@  5 - Cancelar  @" << endl;
    cout << "@                @" << endl;
    cout << "@@@@@@@@@@@@@@@@@@" << endl;
    cin >> x;
    return x;
    limpaEcra();
}

int adicionarCarrinho(string** x, string** carrinho) {
    bool notempty = 0;
    int op;
    int qtd;
    limpaEcra();
    if (idProd < 1) {   //Quando ID = 0 Quer dizer que nenhum item existe ainda
        limpaEcra();
        cout << "Nenhum produto encontrado";
        return 0;
    }
    for (int i = 0; i <= idProd; i++)   //Verificar se o tamanho do nome � 0 em todos, se sim entao nao existem items
    {
        if (x[i][1].length() > 0) {
            notempty = 1;
        }
    }
    if (!(notempty)) {
        limpaEcra();
        cout << "Nenhum produto encontrado";
        return 0;
    }

    cout << endl << "@@@@@@@@@@@@@@@@@@" << endl;   //inicio Lista

    do 
    {
        for (int i = 1; i <= idProd; i++)
        {
            if (x[i][2] != "0") // So mostrar produtos com stock
            {
                cout << "|" << endl;
                cout << "| " << i << " - " << x[i][1] << " - " << x[i][3] << " € - " << x[i][2] << endl;
            }else {
                cout << "|" << endl;
                cout << "| " << i << " - " << x[i][1] << " Fora de Stock " << endl;
            }
        }
        cout << "|" << endl;
        cout << "@@@@@@@@@@@@@@@@@@" << endl;
        
        cout << "Escolha o produto: ";
        cin >> op;
        limpaEcra();
    } while (x[op][2] < "0");
    do
    {
        cout << endl << "@@@@@@@@@@@@@@@@@@@@@@@" << endl;
        cout << "@                     @" << endl;
        cout << "@ Inserir Quantidade: @" << endl;
        cout << "@                     @" << endl;
        cout << "@@@@@@@@@@@@@@@@@@@@@@@" << endl;
        cin >> qtd;
        limpaEcra();
        if (qtd <= 0 || qtd > stoi(x[op][2]))
            cout << "Quantidade Invalida";
    } while (qtd <= 0 || qtd > stoi(x[op][2]));

    limpaEcra();
    
    
    int n = stoi(x[op][2]) - qtd;
    if (carrinho[op][2] > "0") {
        x[op][2] = to_string(n);
        carrinho[op][0] = x[op][0];
        carrinho[op][1] = x[op][1];
        qtd += stod(carrinho[op][2]);
        carrinho[op][2] = to_string(qtd);
        carrinho[op][3] = x[op][3];
    }
    else {
        x[op][2] = to_string(n);
        carrinho[op][0] = x[op][0];
        carrinho[op][1] = x[op][1];
        carrinho[op][2] = to_string(qtd);
        carrinho[op][3] = x[op][3];
    }
}

bool lotaria() {
    srand(time(NULL));
    int randomNum = rand() % 2;
    if (randomNum == 1)
        return 1;
    else
        return 0;
}

int checkout(string** x) {
    bool notempty = 0;
    double moedas = -1,total = 0 ,tiva=0;
    bool free = 0;
    
    limpaEcra();
    if (idProd < 1) {   //Quando ID = 0 Quer dizer que nenhum item existe ainda
        limpaEcra();
        cout << "Nenhum produto encontrado";
        return 0;
    }
    for (int i = 0; i <= idProd; i++)   //Verificar se o tamanho do nome � 0 em todos, se sim entao nao existem items
    {
        if (x[i][1].length() > 0) {
            notempty = 1;
        }
    }
    if (!(notempty)) {
        limpaEcra();
        cout << "Nenhum produto encontrado";
        return 0;
    }

    cout << endl << "@@@@@@@@@@@@@@@@@@" << endl;   //inicio Lista
    for (int i = 1; i <= idProd; i++)
    {
        if (x[i][2] != "0") // So mostrar produtos com stock
        {
            cout << "|" << endl;
            cout << "| " << i << " - " << x[i][1] << " - " << stod(x[i][3]) * precoCusto << " € - " << x[i][2] << endl;

            total = total + (stod(x[i][3]) * precoCusto * stoi(x[i][2]));
            tiva = total + (total * iva);
        }
        else {
            cout << "|" << endl;
            cout << "| " << i << " - " << x[i][1] << " Fora de Stock " << endl;
        }
    }

    if (lotaria() != 1)
    {
        do
        {
            cout << "@@@@@@@@@@@@@@@@@@" << endl;
            cout << "| Total c/IVA:" << tiva << endl;
            cout << "@@@@@@@@@@@@@@@@@@" << endl;
            cout << "Insira o montante do pagamento: ";
            cin >> moedas;              // valor inserido
            limpaEcra();
        } while (moedas <= tiva && moedas != 0);        // verificar se é suficiente
    }
    else
    {
        limpaEcra();
        free = 1;
        cout <<endl << "@@@@@@@@@@@@@@@@@@" << endl;
        cout << "@    Parabens    @" << endl;
        cout << "@ A compra sera  @" << endl;
        cout << "@  !!Gratuita!!  @" << endl;
        cout << "@@@@@@@@@@@@@@@@@@" << endl;
        cin.ignore();
        cin.get();
        limpaEcra();
    }
    if (moedas != 0 || free == 1) {                 //se pagamento bem sucedido
        cout << endl << "@@@@@@@@@@@@@@@@@@" << endl;
        cout  << "@     Fatura     @" << endl;
        cout << "@@@@@@@@@@@@@@@@@@" << endl;
        cout << "|" << endl;
        cout << "| Nº Fatura:   " << idFatura << endl;
        idFatura++;
        cout << "| Nº Cliente:  " << idCliente << endl;
        idCliente++;

        time_t t = time(0);

        cout << "| Data:" << ctime(&t);          //diahora



        cout << "@@@@@@@@@@@@@@@@@@" << endl;
        
        for (int i = 1; i <= idProd; i++)
        {
            cout << "|" << endl;
            cout << "| " << i << " - " << x[i][1] << " - " << x[i][3] << "€ x " << x[i][2] << endl;
        }
        if (free == 0)
        {
            cout << "|" << endl;
            cout << "@@@@@@@@@@@@@@@@@@" << endl;
            cout << "| Inserido     :   " << moedas << endl;
            cout << "| Total        :   " << total << endl;         //total sem iva
            cout << "| IVA          :   " << tiva - total << endl;  //só iva
            cout << "| Total a Pagar:   " << tiva << endl;           //prob needs change
            cout << "| Troco        :   " << moedas - tiva << endl; //resto
            cout << "@@@@@@@@@@@@@@@@@@" << endl;
            cout << "Prima Enter para continuar...";
            cin.ignore();
            cin.get();
        }
        else 
        {
            cout << "|" << endl;
            cout << "@@@@@@@@@@@@@@@@@@" << endl;
            cout << "|" << endl;
            cout << "| Oferta da Casa " << endl;
            cout << "|" << endl;
            cout << "@@@@@@@@@@@@@@@@@@" << endl;
            cout << "Prima Enter para continuar...";
            cin.ignore();
            cin.get();
        }
        for (int i = 1; i <= idProd; i++)
        {
            x[i][0] = "";
            x[i][1] = "";
            x[i][2] = "";
            x[i][3] = "";
        }
    }
    else {                  //cancelar compra e limpar carrinho (Falta Eliminar)
        limpaEcra();
        cout << "@@@@@@@@@@@@@@@@@@" << endl;
        cout << "@ Compra Anulada @";
        cout << "@@@@@@@@@@@@@@@@@@" << endl;
        cout << "Prima Enter para continuar...";
        cin.ignore();
        cin.get();
    }
}

int venda(string** x, string** carrinho) {
    while (true) {
        switch (vendaUI()) {
        case 1:     //Listar
            prodList(x, 0);
            break;
        case 2:     //Adicionar ao carrinho
            adicionarCarrinho(x, carrinho);  
            break;
        case 3:     //Carrinho
            prodList(carrinho, 0);
            limpaEcra(); 
            break;
        case 4:     //Checkout
            checkout(carrinho);
            limpaEcra();
            break;
        case 5:     //Voltar
            cancelarCarrinho(x,carrinho);
            limpaEcra();
            cout << "Compra foi cancelada";
        return 0;
        default:     //Erro
            cout << " Invalid Result!";
            break;
        }
    }
    limpaEcra();
}

int produtoUI() { // User Interface
    int x;
    cout << endl << "@@@@@@@@@@@@@@@@@@" << endl;
    cout << "@                @" << endl;
    cout << "@  1 - Inserir   @" << endl;
    cout << "@  2 - Editar    @" << endl;
    cout << "@  3 - Eliminar  @" << endl;
    cout << "@  4 - Voltar    @" << endl;
    cout << "@                @" << endl;
    cout << "@@@@@@@@@@@@@@@@@@" << endl;
    cin >> x;
    return x;
    limpaEcra();
}

int produto(string** x) {     // Produto Manager Logic
    while (true) {
        switch (produtoUI()) {
        case 1:     //Inserir
            inserir(x);
            break;
        case 2:     //Editar
            listEd(x,1);  // 1 - Para Editar
            break;
        case 3:     //Eliminar
            listEd(x,2); // 2 - Para Eliminar
            break;
        case 4:     //Voltar
            limpaEcra();
            return 0;
        default:     //Erro
            cout << " Invalid Result!";
            break;
        }
    }
    limpaEcra();
}



int main()
{
    string** prodlist = new string * [100]; // 0 - ID; 1 - Nome; 2 - Stock; 3 - Preco
    for (int i = 0; i < 100; ++i) {
        prodlist[i] = new string[4];
    }

    string** carrinho = new string * [100]; // 0 - ID; 1 - Nome;
    for (int i = 0; i < 100; ++i) {
        carrinho[i] = new string[4];
    }

    prodBase(prodlist);

    while (true) {
        switch (menu()) {
            case 1:     //Venda
                venda(prodlist, carrinho);
                break;
            case 2:     //Produto
                produto(prodlist);
                break;
            case 3:     //Sair
                return 0;
            default:
                cout << "Resultado Invalido!";
                break;
        }
    }
}