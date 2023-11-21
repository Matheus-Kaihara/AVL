#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdio>

//
//	TRABALHO DE OUTROS - Estrutura de Dados Não-Lineares: Árvore AVL
//
// 	UNISAGRADO - Universidade Sagrado Coração (Bauru - SP)
//
// 	Professor:
//		- Vinicius Santos Andrade
//
// 	Alunos:
//		- Leonardo Campos Guimarães
//		- Luis Felipe Filenga
//		- Matheus Ryoske Saito Kaihara
//

/*
	=---------------  PROBLEMA DE NULLPTR  ---------------=

	   O problema de NULLPTR é um problema do compilador.
	   Para corrigí-lo, assistir o seguinte vídeo:

		 https://www.youtube.com/watch?v=EPx7aEYatCQ

	=------------------------------------------------------=
*/


// Declarativa para evitar problemas com as bibliotecas
using namespace std;


// Declaração da estrutura
typedef int tipochave;

typedef struct aux {
    tipochave chave;
    int fb;
    aux *esq, *dir;
} no;

typedef no* pont;


// Função para Criar a Árvore AVL
pont criaArvore()
{
    return 0;
}
 
// Função para realizar a Busca
bool buscarElemento(struct aux* no, int chave){
    
    // Quando o nó não for encontrado
    if (no == NULL)
        return false;
 
    // Quando o nó for encontrado
    else if (no->chave == chave)
        return true;
 
    
    // Função de Recursão para percorrer a sub-árvore da Esquerda
    else if (no->chave > chave) {
        bool valor = buscarElemento(no->esq, chave);
        return valor;
    }
 
    
    // Função de Recursão para percorrer a sub-árvore da Direita
    else {
        bool valor = buscarElemento(no->dir, chave);
        return valor;
    }
}
 
// Função para inserção de elementos na Árvore
void inserir(pont &p, tipochave c)
{
	bool busca;
	busca = buscarElemento(p, c);
	
	if(busca){
		cout << endl << "O elemento ja existe, insira um valor diferente." << endl << endl; 
		system("pause");
	}
	else{
		if (!p) {
        	p = new no;
        	p->chave = c;
        	p->esq = nullptr;
        	p->dir = nullptr;
        } 
		else {
        	if (c < p->chave)
            	inserir(p->esq, c);
        	else
           	 inserir(p->dir, c);
    	}	
	}
	
    
}


// Função para fazer o Print da Árvore em leitura de Pré-Ordem
void mostrarPre(pont p)
{
    if (p) {
        cout << p->chave;
        cout << '(';
            mostrarPre(p->esq);
            mostrarPre(p->dir);
        cout << ')';
    }
}


// Função para fazer o Print da Árvore em leitura de Ordem Simétrica
void mostrarSimetrica(pont p)
{
    if (p) {
        cout << '(';
            mostrarSimetrica(p->esq);
            cout << p->chave;
            mostrarSimetrica(p->dir);
        cout << ')';
    }
}


// Função para fazer o Print da Árvore em leitura de Pós-Ordem
void mostrarPos(pont p)
{
    if (p) {
        cout << '(';
            mostrarPos(p->esq);
            mostrarPos(p->dir);
        cout << ')';
        cout << p->chave;
    }
}


/*
	Função para criação da Árvore visual em Grafos na horizontal
	
	- Nessa representação, a sub-árvore da direita fica acima do nodo,
	  já a sub-árvore da esquerda fica abaixo do nodo
	- Ou, seja, os valores menores ficarão "para baixo" e os valores
	  maiores ficarão "para cima"
*/
void funcMostrarHorizontal(pont arv, bool *mapa, int nivel = 0, bool esq = true)
{
    if (arv) {
        mapa[nivel] = true; // Define que a linha deste nível deve ser escrita

        if (nivel) // Vai para o nó da esquerda (e verifica se é da esquerda), então ele vai para a linha de baixo
            mapa[nivel-1] = (esq) ? false : true;

		
        funcMostrarHorizontal(arv->dir, mapa, nivel+1, true);

        cout << left;

        // Exibe as linhas antes do nó
        for (int i = 0; i < nivel; i++)
        {
            cout.width(4);
            if (i < nivel-1) {
                cout << (mapa[i] ? '|' : ' ');
            } else {
                cout.fill('-');
                cout << '+';
                cout.fill(' ');
            }
        }

        // Exibe o nó
        cout << arv->chave << " fb(" << arv->fb << ")" << endl;

        if (nivel) // Vai para o nó da direita (e verifica se é da direita, então ele vai para a linha de cima
            mapa[nivel-1] = (!esq) ? false : true;

        funcMostrarHorizontal(arv->esq, mapa, nivel+1, false);
    }
}


// Função para Print da Árvore em Grafos na horizontal
void mostrarHorizontal(pont arv) {
    bool mapa[255] = {};
    funcMostrarHorizontal(arv, mapa);
}


// Função de remoção de um elemento da Árvore
bool remover(pont &p, tipochave n)
{
    // Caso o nó não seja encontrado
    if (!p)
        return false;

    // Percorre a árvore em busca do nó
    if (n < p->chave)
        remover(p->esq, n);
    else if (n > p->chave)
        remover(p->dir, n);

    else
    {
        // Guardamos o nó encontrado em aux
        pont aux = p;

        /*
            O nó p é o que desejamos remover, ele é filho de um nó
            pai e por isso atribuimos null a ele antes de desalocar
            o espaço de memória.
         */

        if (!p->esq && !p->dir) {

            // Remoção de um nó folha
            p = nullptr;
            delete aux;

        } else if (!p->esq || !p->dir) {

            // Caso haja só um filho
            if (p->esq)
                p = p->esq;
            else
                p = p->dir;

            delete aux;

        } else {

            // Troca a chave do nó buscado e apaga o nó que substiui

            pont paiAux = p;
            aux = paiAux->dir;

            while (aux->esq) {
                paiAux = aux;
                aux = aux->esq;
            }

            if (paiAux->chave == n)
                paiAux->dir = aux->dir;
            else
                paiAux->esq = aux->dir;

            p->chave = aux->chave; // Troca a chave

            delete aux; // Libera a memória do endereço do nó

        }
    }
    return true;
}


/*
	Função para limpar a árvore completa 
	
	- Utiliza recursão para rodar nodo por nodo e deixando com valor Nulo
*/
pont limpar(pont &raiz)
{
    if (!raiz)
        return nullptr;

    raiz->esq = limpar(raiz->esq);
    raiz->dir = limpar(raiz->dir);

    delete raiz;
    return nullptr;
}




// ----- Funcões da árvore AVL -----

// Rotação Simples à Direita 
pont rotacionarEsqEsq(pont p)
{
    pont temp = p;
    pont esq = temp->esq;

    temp->esq = esq->dir;
    esq->dir = temp;

    return esq;
}

// Rotação Simples à Esquerda 
pont rotacionarDirDir(pont p) 
{
    pont temp = p;
    pont dir = temp->dir;

    temp->dir = dir->esq;
    dir->esq = temp;

    return dir;
}

// Rotação Dupla à Direita 
pont rotacionarEsqDir(pont p)
{
    pont temp = p;
    pont esq = temp->esq;
    pont dir = esq->dir;

    temp->esq = dir->dir;
    esq->dir = dir->esq;
    dir->esq = esq;
    dir->dir = temp;

    return dir;
}

// Rotação Dupla à Esquerda 
pont rotacionarDirEsq(pont p) 
{
    pont temp = p;
    pont dir = temp->dir;
    pont esq = dir->esq;

    temp->dir = esq->esq; 
    dir->esq = esq->dir;   
    esq->dir = dir; 
    esq->esq = temp;

    return esq;
}




// Função para garantia do Balanceamento através das Rotações
pont balancear(pont p)
{
    if (!p)
        return nullptr;
        
    pont balanceado = nullptr;
    if (p->esq)
        p->esq = balancear(p->esq);

    if (p->dir)
        p->dir = balancear(p->dir);

    int fator = p->fb;
    
    
    if (fator >= 2) {
        if (p->esq->fb <= -1)
        	// Rotação Dupla à Direita 
            balanceado = rotacionarEsqDir(p);
        else
        	// Rotação Simples à Direita 
            balanceado = rotacionarEsqEsq(p);

    } else if (fator <= -2) {
        if (p->dir->fb >= 1)
        	// Rotação Dupla à Esquerda 
            balanceado = rotacionarDirEsq(p);
        else
        	// Rotação Simples à Esquerda
            balanceado = rotacionarDirDir(p);
    } else {
        balanceado = p;
    }

    return balanceado;
}

// Função para calcular a altura da árvore e utilizar no balanceamento da árvore
int altura(pont raiz)
{
    if (!raiz)
        return -1;

    int esq, dir;

    esq = altura(raiz->esq);
    dir = altura(raiz->dir);

    if (esq > dir)
        return 1 + esq;
    else
        return 1 + dir;
}


// Função para o cálculo do Fator de Balanceamento (FB) de cada nodo
int fatorBalanceamento(pont raiz)
{
    return altura(raiz->esq) - altura(raiz->dir);
}


/* Função para atualizar o Fator de Balanceamento

	- Feita para garantir a propriedade de balanceamento 
	  após alguma alteração na árvore
	
*/
void atualizaFB(pont g)
{
    if (g) {
        g->fb = fatorBalanceamento(g);
        atualizaFB(g->esq);
        atualizaFB(g->dir);
    }
}


// --- MAIN ---
int main() {
	
	// Faz a criação da Árvore
    pont arv = criaArvore();
    int menu = -1;
    tipochave v;

	
    do {
    	
    	// MENU DO PROGRAMA
        system("cls");
        cout << "_____ Arvore AVL _____"  << endl << endl;

        cout << "| 0 | Sair            |" << endl;
        cout << "| 1 | Inserir         |" << endl;
        cout << "| 2 | Mostrar         |" << endl;
        cout << "| 3 | Buscar          |" << endl;
        cout << "| 4 | Excluir         |" << endl;
        cout << "| 5 | Limpar arvore   |" << endl << endl;
        cin >> menu;
        fflush(stdin);

        switch (menu)
        {
        	
        // CASE PARA FINALIZAR O PROGRAMA
        case 0:
            cout << endl << "Programa finalizado." << endl;
            system("pause");
            break;

		// CASE PARA INSERIR ELEMENTO
        case 1:
            cout << endl << "Informe o valor a ser inserido: ";
            cin >> v;
            inserir(arv, v);
            atualizaFB(arv);
            arv = balancear(arv);
            atualizaFB(arv);
            break;

		// CASE PARA PRINTAR ÁRVORE
        case 2:
            cout << endl << "1: Pre-Ordem" << endl;
            cout << "2: Ordem Simetrica" << endl;
            cout << "3: Pos-Ordem" << endl;
            cout << "4: Grafos - Horizontal" << endl << endl;
            cin >> menu;
            fflush(stdin);
            if (!arv) {
                cout << endl << "Arvore Vazia, insira valores para mostrar a arvore" << endl ;
                cout << endl;
            } else {
                cout << endl << "Elementos da Arvore: " << endl;
                switch (menu)
                {
                // Leitura Pré-Ordem
                case 1:
                    mostrarPre(arv);
                    break;

				// Leitura Ordem Simétrica
                case 2:
                    mostrarSimetrica(arv);
                    break;

				// Leitura Pós-Ordem
                case 3:
                    mostrarPos(arv);
                    break;

				// Print em Grafos na horizontal
                case 4:
                    cout << endl << endl ;
                    mostrarHorizontal(arv);
                    break;

                default:
                    cout << endl << "Opcao invalida, favor insira uma opcao correta." << endl << endl;
        			system("pause");
                    break;
                }
                cout << endl;
            }

            menu = 2;
            system("pause");
            break;

		// CASE PARA BUSCAR ELEMENTO
        case 3:
            cout << endl << "Informe o valor a ser buscado: ";
            cin >> v;    
			buscarElemento(arv, v);  
		
			bool busca;
            busca = buscarElemento(arv, v);
            
            if(busca){
            	cout << endl << "O elemento existe" << endl << endl;
			}
			else{
				cout << endl << "Elemento inexistente" << endl << endl; 
			}
			system("pause");
        	break;

		// CASE PARA EXCLUIR ELEMENTO
        case 4:
            cout << endl << "Informe o valor a ser removido: ";
            cin >> v;
            fflush(stdin);
            
            busca = buscarElemento(arv, v);
            
            if(busca){
            	remover(arv, v);
            	cout << endl << "Valor removido com sucesso." << endl << endl;
                atualizaFB(arv);
                arv = balancear(arv);
                atualizaFB(arv);
			}
			else{
				cout << endl << "Valor nao encontrado." << endl << endl;
			}

            system("pause");
            break;

		// CASE PARA LIMPAR A ÁRVORE
        case 5:
            arv = limpar(arv);
            cout << endl << "Arvore limpa com sucesso." << endl << endl;
            system("pause");
            break;

		// FILTRAGEM DO MENU
        default:
        	cout << endl << "Opcao invalida, favor insira uma opcao do Menu." << endl << endl;
        	system("pause");
            break;
        }
        
    } while (menu);

    return 0;
}