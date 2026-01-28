#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

int idProd=0;//ID Base Produtos

int Menu() {
    int x;
    cout << endl << "@@@@@@@@@@@@@@@@@@" << endl;
    cout << "@                @" << endl;
    cout << "@  1 - Venda     @" << endl;
    cout << "@  2 - Produto   @" << endl;
    cout << "@  3 - Sair      @" << endl;
    cout << "@                @" << endl;
    cout << "@@@@@@@@@@@@@@@@@@" << endl;
    cin >> x;
    system("cls");
    return x;
}

void Inserir(string** x) {
    string name;
    float preco;
    int stock;
    bool repetido;
    idProd++;
    x[idProd][0] = idProd;
    system("cls");
    do {
        repetido = 0;
        cout << endl << "@@@@@@@@@@@@@@@@@@" << endl;
        cout << "@                @" << endl;
        cout << "@  Inserir Nome: @" << endl;
        cout << "@                @" << endl;
        cout << "@@@@@@@@@@@@@@@@@@" << endl;
        cin >> name;
        system("cls");
        for (int i = 0; i <= idProd; i++)
        {
            if (name == x[i][1])
                repetido = 1;
        }

        x[idProd][1] = name;
        if (repetido)
            cout << "Nome Repetido" << endl;
    } while (repetido);
    //-----------
    do {
        cout << endl << "@@@@@@@@@@@@@@@@@@" << endl;
        cout << "@                @" << endl;
        cout << "@ Inserir Stock: @" << endl;
        cout << "@                @" << endl;
        cout << "@@@@@@@@@@@@@@@@@@" << endl;
        cin >> stock;
        system("cls");
        if (stock <= 0)
            cout << "Stock invalido";
    } while (stock <= 0);
    x[idProd][2] = stock;
    //-----------
    do{
        cout << endl << "@@@@@@@@@@@@@@@@@@" << endl;
        cout << "@                @" << endl;
        cout << "@ Inserir Preco: @" << endl;
        cout << "@                @" << endl;
        cout << "@@@@@@@@@@@@@@@@@@" << endl;
        cin >> preco;
        system("cls");
        if (preco <= 0)
            cout << "Preco invalido";
    } while (preco <= 0);

    x[idProd][3] = preco;
}

int EditarOP(int op, string** x) {
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
    system("cls");
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
            system("cls");
            for (int i = 0; i <= idProd; i++)
            {
                if (name == x[i][1])
                    repetido = 1;
            }

            x[op][1] = name;
            if (repetido)
                cout << "Nome Repetido" << endl;
        } while (repetido);
        break;
    case 2: //Editar o Stock
        do {
            cout << endl << "@@@@@@@@@@@@@@@@@@" << endl;
            cout << "@                @" << endl;
            cout << "@  Stock Atual:  @" << endl;
            cout << "@                @" << endl;
            cout << "@@@@@@@@@@@@@@@@@@" << endl;
            cin >> stock;
            system("cls");
            if (stock <= 0)
                cout << "Stock invalido";
        } while (stock <= 0);
        x[op][2] = stock;
        break;
    case 3: //Editar o Preco
        do {
            cout << endl << "@@@@@@@@@@@@@@@@@@" << endl;
            cout << "@                @" << endl;
            cout << "@ Inserir Preco: @" << endl;
            cout << "@                @" << endl;
            cout << "@@@@@@@@@@@@@@@@@@" << endl;
            cin >> preco;
            system("cls");
            if (preco <= 0)
                cout << "Preco invalido";
        } while (preco <= 0);

        x[op][3] = preco;
        break;
    default:
        system("cls");
        cout << "Opcao Invalida";
        break;
    }

}

void Eliminar(int op, string** x) {
    
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

int ListEd(string** x,int aux) {
    int op;
    bool notempty = 0;

    if (idProd < 1) {   //Quando ID = 0 Quer dizer que nenhum item existe ainda
        system("cls");
        cout << "Nenhum produto encontrado";
        return 0;
    }
    for (int i = 0; i <= idProd; i++)   //Verificar se o tamanho do nome é 0 em todos, se sim entao nao existem items
    {
        if (x[i][1].length()>0) {
            notempty = 1;
        }
    }
    if (!(notempty)) {
        system("cls");
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
    system("cls");
    switch (aux)
    {
        case 1:
            EditarOP(op, x);
            break;
        case 2:
            Eliminar(op, x);
            break;
        default:
        break;
    } 
    
}

void ProdBase(string** x) {
    idProd = 1;
    x[1][0] = 1;
    x[1][1] = "Bolachas";
    x[1][2] = 5;
    x[1][3] = 2.90;
}

int ProdList(string** x) {
    char index;
    bool notempty = 0;
    if (idProd < 1) {   //Quando ID = 0 Quer dizer que nenhum item existe ainda
        system("cls");
        cout << "Nenhum produto encontrado";
        return 0;
    }
    for (int i = 0; i <= idProd; i++)   //Verificar se o tamanho do nome é 0 em todos, se sim entao nao existem items
    {
        if (x[i][1].length() > 0) {
            notempty = 1;
        }
    }
    if (!(notempty)) {
        system("cls");
        cout << "Nenhum produto encontrado";
        return 0;
    }

    cout << endl << "@@@@@@@@@@@@@@@@@@" << endl;   //inicio Lista
    for (int i = 1; i <= idProd; i++)
    {
        cout << "|" << endl;
        cout << "| " << i << " - " << x[i][1] << endl;
    }
    cout << "|" << endl;
    cout << "@@@@@@@@@@@@@@@@@@" << endl;
    cout << "Prima 0";
    cin >> index;  // Esperar input do user
    system("cls");
}

int VendaUI() {
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
    system("cls");
}

int Venda(string** x) {
    while (true) {
        switch (VendaUI()) {
        case 1:     //Listar
            ProdList(x);
            break;
        case 2:     //Adicionar ao carrinho
            ListEd(x, 1);  // 1 - Para Editar
            break;
        case 3:     //Eliminar
            ListEd(x, 2); // 2 - Para Eliminar
            break;
        case 4:     //Voltar
            system("cls");
            return 0;
        default:     //Erro
            cout << " Invalid Result!";
            break;
        }
    }
    system("cls");
}

int ProdutoUI() { // User Interface
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
    system("cls");
}

int Produto(string** x) {     // Produto Manager Logic
    while (true) {
        switch (ProdutoUI()) {
        case 1:     //Inserir
            Inserir(x);
            break;
        case 2:     //Editar
            ListEd(x,1);  // 1 - Para Editar
            break;
        case 3:     //Eliminar
            ListEd(x,2); // 2 - Para Eliminar
            break;
        case 4:     //Voltar
            system("cls");
            return 0;
        default:     //Erro
            cout << " Invalid Result!";
            break;
        }
    }
    system("cls");
}



int main()
{
    string** prodlist = new string * [100]; // 0 - ID; 1 - Nome; 2 - Stock; 3 - Preco
    for (int i = 0; i < 100; ++i) {
        prodlist[i] = new string[4];
    }

    ProdBase(prodlist);

    bool flagProd = 0; // if = 0 dont leave loop
    while (true) {
        switch (Menu()) {
            case 1:     //Venda
                Venda(prodlist);
                break;
            case 2:     //Produto
                Produto(prodlist);
                break;
            case 3:     //Sair
                return 0;
            default:
                cout << "Resultado Invalido!";
                break;
        }
    }
}