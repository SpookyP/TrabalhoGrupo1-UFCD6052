#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

int idProd=0;//ID Base Produtos

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
        limpaEcra();
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
        limpaEcra();
        if (preco <= 0)
            cout << "Preco invalido";
    } while (preco <= 0);

    x[idProd][3] = preco;
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
            limpaEcra();
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
            limpaEcra();
            if (preco <= 0)
                cout << "Preco invalido";
        } while (preco <= 0);

        x[op][3] = preco;
        break;
    default:
        limpaEcra();
        cout << "Opcao Invalida";
        break;
    }

}

void eliminar(int op, string** x) {
    
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

    if (idProd < 1) {   //Quando ID = 0 Quer dizer que nenhum item existe ainda
        limpaEcra();
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
        limpaEcra();
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
            eliminar(op, x);
            break;
        default:
        break;
    } 
    
}

void prodBase(string** x) {
    idProd = 1;
    x[1][0] = "1";
    x[1][1] = "Bolachas";
    x[1][2] = "5";
    x[1][3] = "2.90";
}

int prodList(string** x) {
    bool notempty = 0;
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
            cout << "| " << i << " - " << x[i][1] << " - " << x[i][3] << " € - " << x[i][2] << endl;
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
    x[op][2] = stoi(x[op][2]) - qtd;
    carrinho[op][1] = x[op][1];
    cout << stoi(x[op][2]);
}


int venda(string** x, string** carrinho) {
    while (true) {
        switch (vendaUI()) {
        case 1:     //Listar
            prodList(x);
            break;
        case 2:     //Adicionar ao carrinho
            adicionarCarrinho(x, carrinho);  
            break;
        case 3:     //Carrinho
            limpaEcra(); 
            break;
        case 4:     //Checkout
            limpaEcra();
            break;
        case 5:     //Voltar
        limpaEcra();
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
    cout << "@  1 - inserir   @" << endl;
    cout << "@  2 - Editar    @" << endl;
    cout << "@  3 - eliminar  @" << endl;
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
        carrinho[i] = new string[2];
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