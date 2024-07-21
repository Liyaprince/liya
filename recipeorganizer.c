#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECIPES 100
#define MAX_INGREDIENTS 20
#define MAX_NAME_LENGTH 50
#define MAX_INSTRUCTION_LENGTH 500

typedef struct {
    char name[MAX_NAME_LENGTH];
    char ingredients[MAX_INGREDIENTS][MAX_NAME_LENGTH];
    int num;
    char instrn[MAX_INSTRUCTION_LENGTH];
} Recipe;

typedef struct {
    Recipe recipes[MAX_RECIPES];
    int numofrecipes;
} RecipeBook;

void createRecipeBook(RecipeBook *book);
void addRecipe(RecipeBook *book);
void viewRecipes(RecipeBook *book);
void viewinstructions(RecipeBook *book);

int main() {
    RecipeBook book;
    createRecipeBook(&book);

    int choice;
    do {
        printf("\n");
        printf("1. Add a new recipe\n");
        printf("2. View all recipes\n");
        printf("3. View meal plan\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  

        switch (choice) {
            case 1:
                addRecipe(&book);
                break;
            case 2:
                viewRecipes(&book);
                break;
            case 3:
                viewinstructions(&book);
                break;
            case 4:
                printf("Exiting....\n");
                break;
            default:
                printf("Invalid choice...\n");
        }
    } while (choice!= 4);

    return 0;
}

void createRecipeBook(RecipeBook *book) {
    book->numofrecipes = 0;
}

void addRecipe(RecipeBook *book) {
    Recipe newRecipe;
    printf("Enter the name of the recipe: ");
    fgets(newRecipe.name, sizeof(newRecipe.name), stdin);
    newRecipe.name[strcspn(newRecipe.name, "\n")] = '\0'; 

    printf("Enter the number of ingredients: ");
    scanf("%d", &newRecipe.num);
    getchar();  

    printf("Enter the ingredients (one per line):\n");
    for (int i = 0; i < newRecipe.num;++i) {
        fgets(newRecipe.ingredients[i], sizeof(newRecipe.ingredients[i]), stdin);
        newRecipe.ingredients[i][strcspn(newRecipe.ingredients[i], "\n")] = '\0';  
    }

    printf("Enter the instructions for your recipe:\n");
    fgets(newRecipe.instrn, sizeof(newRecipe.instrn), stdin);
    newRecipe.instrn[strcspn(newRecipe.instrn, "\n")] = '\0';  

    book->recipes[book->numofrecipes++] = newRecipe;
    printf("Recipe added successfully!\n");
}

void viewRecipes(RecipeBook *book) {
    if (book->numofrecipes == 0) {
        printf("No recipes available. Add a recipe first.\n");
    } else {
        printf("Recipe List:\n");
        for (int i = 0; i < book->numofrecipes; ++i) {
            printf("%d. %s\n", i + 1, book->recipes[i].name);
        }
        printf("\n");
    }
}

void viewinstructions(RecipeBook *book) {
    if (book->numofrecipes == 0) {
        printf("No recipes available. Add a recipe first.\n");
    } else {
        viewRecipes(book);
        int choice;
        printf("Enter the number of the recipe you want to prepare: ");
        scanf("%d", &choice);
        getchar(); 

        if (choice >= 1 && choice <= book->numofrecipes) {
            printf("Preparing meal with recipe: %s\n", book->recipes[choice - 1].name);
            printf("Ingredients needed:\n");
            for (int i = 0; i < book->recipes[choice - 1].num; ++i) {
                printf("- %s\n", book->recipes[choice - 1].ingredients[i]);
            }
            printf("Instructions:\n%s\n", book->recipes[choice - 1].instrn);
        } else {
            printf("Invalid recipe number.\n");
        }
    }
}
