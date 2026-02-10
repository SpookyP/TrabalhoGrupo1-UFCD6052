#include <iostream>
#include <string>
#pragma warning(disable : 4996)
#include <ctime>
#include <cstdlib>
using namespace std;

//Variaveis Globais

int idProd = 0;             //Último ID Produtos
float iva = 0.23;
float precoCusto = 1.30;
int idCliente = 1;          //Número Cliente
int idFatura = 11111;       //Número Fatura

void limpaEcra() {
#ifdef _WIN32           //Windows
    system("cls");
#else                   //Outros
    system("clear");
#endif
}

bool nValidoInt(string i) {     //Validar conversão string -> int
    float aux;
    try
    {
        stoi(i);
        aux = stof(i);
        if (aux - stoi(i) > 0)
            return false;
        return true;
    }
    catch (exception&)
    {
        return false;
    }
}

bool nValidoFlo(string i) {     //Validar conversão string -> float
    try
    {
        stof(i);
        return true;
    }
    catch (exception&)
    {
        return false;
    }
}

bool validarProd(string** x) {       //Validar se existem produtos na matriz
    bool naoVazio = 0;
    if (idProd < 1) {   //Quando ID = 0 Quer dizer que nenhum item existe ainda
        limpaEcra();
        cout << "!!Nenhum produto encontrado!!";
        return 1;
    }
    for (int i = 1; i <= idProd; i++)   //Verificar se o tamanho do nome é maior que 0, se sim entao nao existem items
    {
        if (x[i][1].length() > 0) {
            naoVazio = 1;
        }
    }
    if (!(naoVazio)) {
        limpaEcra();
        cout << "!!Nenhum produto encontrado!!";
        return 1;
    }
    return 0;
}

//inicializar funções

void prodBase(string** x);                              //Produtos pré-definidos
char menu();                                            //Menu Padrão
int venda(string** x, string** carrinho);               //Opções de menu venda
char vendaUI();                                         //Menu Venda
int prodList(string * *x, bool utilizador);             //Listar produtos
int adicionarCarrinho(string** x, string** carrinho);   //Adicionar produtos ao carrinho
void checkout(string** x);                              //Checkout e Fatura
bool lotaria();                                         //Chance de ganhar oferta
void cancelarCarrinho(string** x, string** carrinho);   //Cancelar compra e limpar carrinho

int produto(string * *x);               //Opções de menu produto
char produtoUI();                       //Menu Produto
void inserir(string * *x);              //Inserir novo produto
int listEd(string** x, int aux);        //Listar produtos para Editar ou Eliminar
int editarOP(string op, string** x);    //Editar produto
int eliminar(string op, string** x);    //Eliminar produto

//Produtos e Menu

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

char menu() {       
    string op;
    cout << endl << "@@@@@@@@@@@@@@@@@@" << endl;
    cout << "@ # Musicaltec # @" << endl;
    cout << "@@@@@@@@@@@@@@@@@@" << endl;
    cout << "@                @" << endl;
    cout << "@  1 - Venda     @" << endl;
    cout << "@  2 - Produto   @" << endl;
    cout << "@  3 - Sair      @" << endl;
    cout << "@                @" << endl;
    cout << "@@@@@@@@@@@@@@@@@@" << endl;
    cin >> op;
    limpaEcra();
    if (op.length() > 1)
        return 0;
    return op[0];

}

//Venda

int venda(string** x, string** carrinho) {
    while (true) {
        switch (vendaUI()) {
        case '1':     //Listar
            prodList(x, 0);
            break;
        case '2':     //Adicionar ao carrinho
            adicionarCarrinho(x, carrinho);
            break;
        case '3':     //Carrinho
            prodList(carrinho, 0);
            break;
        case '4':     //Checkout
            if (validarProd(carrinho))
                break;
            checkout(carrinho);
            cancelarCarrinho(x, carrinho);
            limpaEcra();
            return 0;
            break;
        case '5':     //Voltar
            cancelarCarrinho(x, carrinho);
            limpaEcra();
            cout << "!!Compra foi cancelada!!";
            return 0;
        default:     //Erro
            limpaEcra();
            cout << "!!Opcao Invalida!!";
            break;
        }
    }
    limpaEcra();
}

char vendaUI() {
    string x;
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
    if (x.length() > 1)
        return 0;
    return x[0];
    limpaEcra();
}

int prodList(string** x, bool utilizador) {     
    limpaEcra();
    if (validarProd(x)) {
        return 0;
    }

    cout << endl << "@@@@@@@@@@@@@@@@@@" << endl;   //Inicio Lista

    for (int i = 1; i <= idProd; i++)
    {
        if (x[i][1] != "")
        {
            if (x[i][2] != "0")     //So mostrar produtos com stock
            {
                cout << "|" << endl;
                cout << "| " << i << " - " << x[i][1] << " - ";

                if (utilizador)     //0->Cliente 1->Admin
                    cout << x[i][3] << " € - " << x[i][2] << endl;
                else
                    cout << stod(x[i][3]) * precoCusto << " € - " << x[i][2] << endl;

            }
            else {
                cout << "|" << endl;
                cout << "| " << i << " - " << x[i][1] << " Fora de Stock " << endl;
            }
        }
    }
    cout << "|" << endl;
    cout << "@@@@@@@@@@@@@@@@@@" << endl;
    cout << "Prima Enter para continuar...";
    cin.ignore();
    cin.get();
    limpaEcra();
}

int adicionarCarrinho(string** x, string** carrinho) {
    bool naoVazio = 0;
    string op;
    int opAux = -1;
    int qtd;
    limpaEcra();
    if (validarProd(x)) {
        return 0;
    }

    do
    {
        cout << endl << "@@@@@@@@@@@@@@@@@@" << endl;   //Inicio Lista
        cout << "|" << endl;
        cout << "| 0 - Cancelar" << endl;

        for (int i = 1; i <= idProd; i++)
        {
            if (x[i][2] != "0") //So mostrar produtos com stock
            {
                cout << "|" << endl;
                cout << "| " << i << " - " << x[i][1] << " - " << x[i][3] << " € - " << x[i][2] << endl;
            }
            else {
                cout << "|" << endl;
                cout << "| " << i << " - " << x[i][1] << " Fora de Stock " << endl;
            }
        }

        cout << "|" << endl;
        cout << "@@@@@@@@@@@@@@@@@@" << endl;

        cout << "Escolha o produto: ";      
        cin >> op;
        limpaEcra();
        if (nValidoInt(op))             //Validar escolha
            opAux = stoi(op);
        else
        {
            op = "0";
            cout << "!!Opcao Invalida!!";
        }
        if (opAux == 0)
            return 0;
        if (stoi(op) > 99)
        {
            op = "0";
            cout << "!!Opcao Invalida!!";
        }
    } while (x[stoi(op)][2] < "0");

    do
    {
        cout << endl << "@@@@@@@@@@@@@@@@@@@@@@@" << endl;
        cout << "@                     @" << endl;
        cout << "@ Inserir Quantidade: @" << endl;
        cout << "@                     @" << endl;
        cout << "@@@@@@@@@@@@@@@@@@@@@@@" << endl;
        cin >> qtd;
        limpaEcra();
        if (qtd <= 0 || qtd > stoi(x[opAux][2]))
            cout << "!!Quantidade Invalida!!";
    } while (qtd <= 0 || qtd > stoi(x[opAux][2]));

    limpaEcra();

    int n = stoi(x[opAux][2]) - qtd;
    if (carrinho[opAux][2] > "0") {         //Existe no carrinho
        x[opAux][2] = to_string(n);         //Combinar os dois stocks
        carrinho[opAux][0] = x[opAux][0];
        carrinho[opAux][1] = x[opAux][1];
        qtd += stod(carrinho[opAux][2]);
        carrinho[opAux][2] = to_string(qtd);
        carrinho[opAux][3] = x[opAux][3];
    }
    else {                                  //Não existe no carrinho
        x[opAux][2] = to_string(n);         //Adicionar ao carrinho
        carrinho[opAux][0] = x[opAux][0];
        carrinho[opAux][1] = x[opAux][1];
        carrinho[opAux][2] = to_string(qtd);
        carrinho[opAux][3] = x[opAux][3];
    }
}

void checkout(string** x) {
    string moedas;
    float moedasAux = -1, total = 0, tiva = 0;
    bool gratis = 0;
    limpaEcra();

    cout << endl << "@@@@@@@@@@@@@@@@@@" << endl;   //Inicio Lista

    for (int i = 1; i <= idProd; i++)
    {
        if (x[i][0] != "") {
            cout << "|" << endl;
            cout << "| " << x[i][0] << " - " << x[i][1] << " - " << stod(x[i][3]) * precoCusto << " € - " << x[i][2] << endl;

            total = total + (stod(x[i][3]) * precoCusto * stoi(x[i][2]));
            tiva = total + (total * iva);
        }
    }

    if (lotaria() != 1)
    {
        do
        {
            cout << "|" << endl;
            cout << "@@@@@@@@@@@@@@@@@@" << endl;
            cout << "| Total c/IVA:" << tiva << endl;
            cout << "@@@@@@@@@@@@@@@@@@" << endl;
            cout << "Insira o montante do pagamento ou 0 para cancelar:" << endl;
            cin >> moedas;              // valor inserido
            if (nValidoFlo(moedas))
                moedasAux = stof(moedas);
            limpaEcra();
        } while (moedasAux <= tiva && moedasAux != 0);        // verificar se é suficiente
    }
    else
    {
        limpaEcra();
        gratis = 1;
        cout << endl << "@@@@@@@@@@@@@@@@@@" << endl;
        cout << "@    Parabens    @" << endl;
        cout << "@ A compra sera  @" << endl;
        cout << "@  !!Gratuita!!  @" << endl;
        cout << "@@@@@@@@@@@@@@@@@@" << endl;
        cin.ignore();
        cin.get();
        limpaEcra();
    }
    if (moedasAux != 0 || gratis == 1) {                 //se pagamento bem sucedido
        cout << endl << "@@@@@@@@@@@@@@@@@@" << endl;
        cout << "@     Fatura     @" << endl;
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
            if (x[i][0] != "") {
                cout << "|" << endl;
                cout << "| " << i << " - " << x[i][1] << " - " << x[i][3] << "€ x " << x[i][2] << endl;
            }
        }
        if (gratis == 0)
        {
            cout << "|" << endl;
            cout << "@@@@@@@@@@@@@@@@@@" << endl;
            cout << "| Inserido     :   " << moedasAux << endl;
            cout << "| Total        :   " << total << endl;         //total sem iva
            cout << "| IVA          :   " << tiva - total << endl;  //só iva
            cout << "| Total a Pagar:   " << tiva << endl;           //prob needs change
            cout << "| Troco        :   " << moedasAux - tiva << endl; //resto
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
        cout << "@ Compra Anulada @" << endl;
        cout << "@@@@@@@@@@@@@@@@@@" << endl;
        cout << "Prima Enter para continuar...";
        cin.ignore();
        cin.get();
    }
    limpaEcra();
}

bool lotaria() {
    srand(time(NULL));
    int numeroAlt = rand() % 2;
    if (numeroAlt == 1)
        return 1;
    else
        return 0;
}

void cancelarCarrinho(string** x, string** carrinho) {

    for (int i = 1; i <= idProd; i++)
    {
        for (int j = 1; j <= idProd; j++)
        {
            if (x[j][1] == carrinho[i][1]) {

                int aux = stoi(carrinho[i][2]);
                aux += stoi(x[j][2]);
                x[j][2] = to_string(aux);
            }
        }
    }
    for (int i = 0; i <= idProd; i++)
    {
        carrinho[i][0] = "";
        carrinho[i][1] = "";
        carrinho[i][2] = "";
        carrinho[i][3] = "";
    }
}

//Produto

int produto(string** x) {     
    while (true) {
        switch (produtoUI()) {
        case '1':     //Inserir
            inserir(x);
            break;
        case '2':     //Editar
            listEd(x, 1);  // 1 - Para Editar
            break;
        case '3':     //Eliminar
            listEd(x, 2); // 2 - Para Eliminar
            break;
        case '4':     //Voltar
            limpaEcra();
            return 0;
        default:     //Erro
            limpaEcra();
            cout << "!!Opcao Invalida!!";
            break;
        }
    }
}

char produtoUI() { 
    string x;
    cout << endl << "@@@@@@@@@@@@@@@@@@" << endl;
    cout << "@                @" << endl;
    cout << "@  1 - Inserir   @" << endl;
    cout << "@  2 - Editar    @" << endl;
    cout << "@  3 - Eliminar  @" << endl;
    cout << "@  4 - Voltar    @" << endl;
    cout << "@                @" << endl;
    cout << "@@@@@@@@@@@@@@@@@@" << endl;
    cin >> x;
    if (x.length() > 1)
        return 0;
    return x[0];
    limpaEcra();
}

void inserir(string** x) {
    string nome, preco, stock;
    float precoAux = -1;
    int stockAux = -1;
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
        cin >> nome;
        limpaEcra();

        //Verificar Nome Repetido
        for (int i = 0; i <= idProd; i++)
        {
            string nomeExiste = x[i][1];
            if (nomeExiste.length() == nome.length()) {
                repetido = 1;
                for (size_t j = 0; j < nome.length(); j++) {
                    if (tolower(nomeExiste[j]) != tolower(nome[j])) {
                        repetido = 0;
                        break;
                    }
                }
            }
        }

        x[idProd][1] = nome;
        if (repetido)
            cout << "!!Nome Repetido!!" << endl;
    } while (repetido);

    do {
        cout << endl << "@@@@@@@@@@@@@@@@@@" << endl;
        cout << "@                @" << endl;
        cout << "@ Inserir Stock: @" << endl;
        cout << "@                @" << endl;
        cout << "@@@@@@@@@@@@@@@@@@" << endl;
        cin >> stock;
        limpaEcra();
        if (nValidoInt(stock))
            stockAux = stoi(stock);
        if (stockAux < 0)
            cout << "!!Stock invalido!!";
    } while (stockAux < 0);


    x[idProd][2] = stock;

    do {
        cout << endl << "@@@@@@@@@@@@@@@@@@" << endl;
        cout << "@                @" << endl;
        cout << "@ Inserir Preco: @" << endl;
        cout << "@                @" << endl;
        cout << "@@@@@@@@@@@@@@@@@@" << endl;
        cin >> preco;
        limpaEcra();
        if (nValidoFlo(preco))
            precoAux = stof(preco);
        if (precoAux <= 0)
            cout << "!!Preco invalido!!";
    } while (precoAux <= 0);

    x[idProd][3] = preco;
}

int listEd(string** x, int aux) {
    string op;
    int opAux = -1;
    bool naoVazio = 0;
    limpaEcra();
    if (idProd < 1) {   //Quando ID = 0 Quer dizer que nenhum item existe ainda
        cout << "Nenhum produto encontrado";
        return 0;
    }
    for (int i = 0; i <= idProd; i++)   //Verificar se o tamanho é maior que 0, se sim entao nao existem items
    {
        if (x[i][1].length() > 0) {
            naoVazio = 1;
        }
    }
    if (!(naoVazio)) {
        cout << "Nenhum produto encontrado";
        return 0;
    }
    do
    {
        cout << endl << "@@@@@@@@@@@@@@@@@@" << endl;   //inicio Lista
        cout << "| Selecione um ID:" << endl;
        cout << "|" << endl;
        cout << "| 0 - Cancelar" << endl;
        for (int i = 1; i <= idProd; i++)
        {
            if (x[i][2] != "0") // So mostrar produtos com stock
            {
                cout << "|" << endl;
                cout << "| " << i << " - " << x[i][1] << " - " << x[i][3] << " € - " << x[i][2] << endl;
            }
            else {
                cout << "|" << endl;
                cout << "| " << i << " - " << x[i][1] << " Fora de Stock " << endl;
            }
        }
        cout << "|" << endl;
        cout << "@@@@@@@@@@@@@@@@@@" << endl;
        cout << "Escolha o produto: ";
        cin >> op;
        limpaEcra();
        if (nValidoInt(op))
            opAux = stoi(op);
        else
        {
            op = "0";
            cout << "!!Opcao Invalida!!";
        }
        if (opAux == 0)
            return 0;
        if (stoi(op) > 99) 
        {
            op = "0";
            cout << "!!Opcao Invalida!!";
        }
    } while (x[stoi(op)][2] < "0");

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

int editarOP(string op, string** x) {
    string nome, aux, preco, stock;
    float precoAux = -1;
    int stockAux = -1;
    bool repetido;

    if (stoi(op) > idProd)
    {
        cout << "!!Opcao Invalida!!";
        return 0;
    }

    cout << endl << "@@@@@@@@@@@@@@@@@@" << endl; //UI
    cout << "@                @" << endl;
    cout << "@  1 - Nome      @" << endl;
    cout << "@  2 - Stock     @" << endl;
    cout << "@  3 - Preco     @" << endl;
    cout << "@                @" << endl;
    cout << "@@@@@@@@@@@@@@@@@@" << endl;
    cin >> aux;
    limpaEcra();
    if (aux.length() > 1)
    {
        cout << "!!Opcao Invalida!!";
        return 0;
    }

    switch (aux[0]) {
    case '1': //Editar o nome
        do {
            repetido = 0;
            cout << endl << "@@@@@@@@@@@@@@@@@@" << endl;
            cout << "@                @" << endl;
            cout << "@   Novo Nome:   @" << endl;
            cout << "@                @" << endl;
            cout << "@@@@@@@@@@@@@@@@@@" << endl;
            cin >> nome;
            limpaEcra();
            //Verificar Nome Repetido
            for (int i = 0; i <= idProd; i++)
            {
                string nomeExiste = x[i][1];
                if (nomeExiste.length() == nome.length()) {
                    repetido = 1;
                    for (int j = 0; j < nome.length(); j++) {
                        if (tolower(nomeExiste[j]) != tolower(nome[j])) {
                            repetido = 0;
                            break;
                        }
                    }
                }
            }
            if (repetido)
                cout << "!!Nome Repetido!!";
        } while (repetido);
        x[stoi(op)][1] = nome;
        break;

    case '2': //Editar o Stock
        do {
            cout << endl << "@@@@@@@@@@@@@@@@@@" << endl;
            cout << "@                @" << endl;
            cout << "@  Stock Atual:  @" << endl;
            cout << "@                @" << endl;
            cout << "@@@@@@@@@@@@@@@@@@" << endl;
            cin >> stock;
            limpaEcra();
            if (nValidoInt(stock))
                stockAux = stoi(stock);
            if (stockAux < 0)
                cout << "!!Stock invalido!!";
        } while (stockAux < 0);
        x[stoi(op)][2] = stock;
        break;

    case '3': //Editar o Preco
        do {
            cout << endl << "@@@@@@@@@@@@@@@@@@" << endl;
            cout << "@                @" << endl;
            cout << "@ Inserir Preco: @" << endl;
            cout << "@                @" << endl;
            cout << "@@@@@@@@@@@@@@@@@@" << endl;
            cin >> preco;
            limpaEcra();
            if (nValidoFlo(preco))
                precoAux = stof(preco);
            if (precoAux <= 0)
                cout << "!!Preco invalido!!";
        } while (precoAux <= 0);
        x[stoi(op)][3] = preco;
        break;

    default:
        limpaEcra();
        cout << "!!Opcao Invalida!!";
        break;
    }

}

int eliminar(string op, string** x) {
    limpaEcra();
    cout << endl << "@@@@@@@@@@@@@@@@@@" << endl;   //Confirmacao de Eliminar dados - tem de receber S/s para poder Eliminar
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
        if (i > stoi(op)) {
            x[i - 1][0] = i - 1;
            x[i - 1][1] = x[i][1];
            x[i - 1][2] = x[i][2];
            x[i - 1][3] = x[i][3];
        }
    }
    x[idProd][1] = "";
    idProd--; // Esquecer ultimo item
}


int main()
{

    string** proddb = new string * [100]; // 0 - ID; 1 - Nome; 2 - Stock; 3 - Preco
    for (int i = 0; i < 100; ++i) {
        proddb[i] = new string[4];
    }

    string** carrinho = new string * [100]; // 0 - ID; 1 - Nome;
    for (int i = 0; i < 100; ++i) {
        carrinho[i] = new string[4];
    }

    prodBase(proddb);

    while (true) {
        switch (menu()) {
        case '1':     //Venda
            venda(proddb, carrinho);
            break;
        case '2':     //Produto
            produto(proddb);
            break;
        case '3':     //Sair
            return 0;
        default:
            cout << "!!Opcao Invalida!!";
            break;
        }
    }
}