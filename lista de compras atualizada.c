#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 100
#define MAX_STORES 5
#define MAX_NAME_LENGTH 50

typedef struct {
    char name[MAX_NAME_LENGTH];
    double price;
} Item;

typedef struct {
    char name[MAX_NAME_LENGTH];
    Item items[MAX_ITEMS];
    int itemCount;
} Store;

void suggestStore(Store stores[], int storeCount, char shoppingList[][MAX_NAME_LENGTH], int listSize) {
    int bestStoreIndex = -1;
    double lowestCost = -1.0;

    for (int i = 0; i < storeCount; i++) {
        double currentCost = 0.0;
        int allItemsAvailable = 1;

        for (int j = 0; j < listSize; j++) {
            int found = 0;
            for (int k = 0; k < stores[i].itemCount; k++) {
                if (strcmp(stores[i].items[k].name, shoppingList[j]) == 0) {
                    currentCost += stores[i].items[k].price;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                allItemsAvailable = 0;
                break;
            }
        }

        if (allItemsAvailable && (lowestCost == -1.0 || currentCost < lowestCost)) {
            bestStoreIndex = i;
            lowestCost = currentCost;
        }
    }

    if (bestStoreIndex != -1) {
        printf("\nMelhor loja: %s\n", stores[bestStoreIndex].name);
        printf("Custo total: R$%.2f\n", lowestCost);
    } else {
        printf("\nNenhuma loja possui todos os itens da lista de compras.\n");
    }
}

void addItemToList(char shoppingList[][MAX_NAME_LENGTH], int *listSize, const char *itemName) {
    if (*listSize < MAX_ITEMS) {
        strcpy(shoppingList[*listSize], itemName);
        (*listSize)++;
        printf("Item '%s' adicionado à lista de compras.\n", itemName);
    } else {
        printf("Não é possível adicionar mais itens à lista.\n");
    }
}

int main() {
    Store stores[MAX_STORES] = {
        {
            "Loja A",
            {
                {"Notebook", 2500.00}, {"Teclado", 150.00}, {"Mouse", 100.00},
                {"Monitor", 800.00}, {"Cadeira", 600.00}
            },
            5
        },
        {
            "Loja B",
            {
                {"Notebook", 2450.00}, {"Teclado", 140.00}, {"Mouse", 95.00},
                {"Monitor", 750.00}, {"Impressora", 1200.00}
            },
            5
        },
        {
            "Loja C",
            {
                {"Notebook", 2600.00}, {"Teclado", 160.00}, {"Mouse", 105.00},
                {"Monitor", 820.00}, {"Cadeira", 590.00}, {"Impressora", 1150.00}
            },
            6
        }
    };

    int storeCount = 3;

    char shoppingList[MAX_ITEMS][MAX_NAME_LENGTH];
    int listSize = 0;

    printf("Bem-vindo ao organizador de lista de compras!\n\n");

    int option;
    do {
        printf("\nMenu:\n");
        printf("1. Adicionar item a lista de compras\n");
        printf("2. Mostrar melhor loja\n");
        printf("3. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &option);
        getchar(); // Limpar buffer

        switch (option) {
            case 1: {
                char itemName[MAX_NAME_LENGTH];
                printf("Digite o nome do item: ");
                fgets(itemName, MAX_NAME_LENGTH, stdin);
                itemName[strcspn(itemName, "\n")] = 0; // Remover newline
                addItemToList(shoppingList, &listSize, itemName);
                break;
            }
            case 2:
                suggestStore(stores, storeCount, shoppingList, listSize);
                break;
            case 3:
                printf("Saindo do programa. Ate mais!\n");
                break;
            default:
                printf("Opção invalida. Tente novamente.\n");
        }
    } while (option != 3);

    return 0;
}

